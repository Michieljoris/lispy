#include "misc_fns.h"

#include "assert.h"
#include "cell.h"
#include "compile.h"
#include "eval.h"
#include "io.h"
#include "iter.h"
#include "lispy_mempool.h"
#include "list.h"
#include "lval.h"
#include "namespace.h"
#include "platform.h"
#include "print.h"
#include "read.h"
#include "state.h"

int is_lval_type(Lval* lval, int type, int subtype) {
  return lval->type == type && lval->subtype == subtype;
}

Lval* macroexpand(Lenv* env, Lval* lval, int do_recurse) {
  /* Check we have non-empty list where the first expr is a symbol */
  if (is_lval_type(lval, LVAL_COLLECTION, LIST) && list_count(lval->head) > 0 &&
      ((Lval*)(lval->head->car))->type == LVAL_SYMBOL) {
    /* Have a peek at the eval of that symbol */
    scoped Lval* lval_fun = lenv_get_or_error(env, lval->head->car);
    /* If it's a macro then eval it with the lval args */
    if (is_lval_type(lval_fun, LVAL_FUNCTION, MACRO)) {
      scoped Lval* arg_list = make_lval_list();
      arg_list->head = retain(lval->head->cdr);
      /* Bind the macro with its args */
      Lval* bound_macro = expand_macro(lval_fun, arg_list);
      /* info("\nbound_macro *******************************************\n"); */
      /* lval_println(bound_macro); */
      /* info("*******************************************\n"); */
      // release fun and args
      if (bound_macro->type == LVAL_ERR) {
        return bound_macro;
      }
      /* Recursively expand  */
      if (do_recurse) {
        Lval* ret = macroexpand(env, bound_macro, do_recurse);
        release(bound_macro);
        return ret;
      } else {
        return bound_macro;
      }
    }
  }

  return retain(lval);
}

Lval* macroexpand_1_fn(Lenv* env, Lval* arg_list) {
  ITER_NEW_N("macroexpand-1", 1)
  ITER_NEXT
  Lval* lval = arg;
  ITER_END
  return macroexpand(env, lval, 0);
}

Lval* macroexpand_fn(Lenv* env, Lval* arg_list) {
  ITER_NEW_N("macroexpand", 1)
  ITER_NEXT
  Lval* lval = arg;
  ITER_END
  return macroexpand(env, lval, 1);
}

Lval* eval_fn(Lenv* env, Lval* arg_list) {
  ITER_NEW_N("eval", 1)
  ITER_NEXT
  Lval* lval = arg;
  ITER_END
  return lval_eval(env, lval);
}

Lval* print_env_fn(Lenv* env, Lval* arg_list) {
  ddebug("print_env:\n");
  env_print(env);
  return make_lval_nil();
}

int exit_repl = 0;

Lval* exit_fn(Lenv* e, Lval* arg_list) {
  exit_repl = 1;
  return make_lval_nil();
}

#ifndef WASM

char* read_file(char* file_name) {
  // Open file and check it exists
  FILE* f = fopen(file_name, "rb");
  if (f == NIL) return NIL;

  // Read file contents into string
  fseek(f, 0, SEEK_END);
  long length = ftell(f);
  fseek(f, 0, SEEK_SET);
  char* str = calloc(length + 1, 1);
  fread(str, 1, length, f);
  fclose(f);
  return str;
}
#else

char* read_file(char* file_name) { return NULL; }

#endif

Lval* load(Lenv* _, char* file_name) {
#ifndef WASM
  int error = 0;
  char* str = read_file(file_name);
  if (!str) return make_lval_err("Could not load file %s", file_name);
  int pos = 0;
  Lval* lval = NULL;
  Lval* result = NULL;
  /* printf("Loading: %s\n", file_name); */
  do {
    lval = read_expr(str, &pos, '\0');
    if (!lval) break;
    release(result);
    if (lval->type == LVAL_ERR) {
      lval_println(lval);
      result = retain(lval);
      break;
    } else {
      Namespace* current_ns = get_current_ns();
      result = lval_eval(current_ns->env, lval);
      if (result->type == LVAL_ERR) {
        printf("Encountered error while evalling expression: \n");
        lval_println(lval);
        lval_println(result);
        error = 1;
      }
    }
    release(lval);
  } while (1);

  printf("Loaded: %s \n", file_name);
  free(str);
  if (error) return make_lval_err("Errors encountered loading file\n");
  return result ? result : make_lval_nil();
#else
  return NULL;
#endif
}

Lval* load_fn(Lenv* _, Lval* arg_list) {
  ddebug("\nload_fn: ");
  ITER_NEW_N("load", 1)
  ITER_NEXT_TYPE(LVAL_LITERAL, STRING)
  return load(NULL, arg->str);
}

/* Lval* compile_fn(Lenv* env, Lval* arg_list) { */
/*   ddebug("\ncompile_fn: "); */
/*   ITER_NEW_N("compile", 1) */
/*   ITER_NEXT_TYPE(LVAL_LITERAL, STRING) */
/*   compile(arg->str); */
/*   return make_lval_nil(); */
/* } */

Lval* in_ns(char* namespace_str) {
  Namespace* ns = make_or_get_namespace(namespace_str);
  set_current_ns(ns);
  /* Lenv* stdlib_env = get_stdlib_env(); */
  /* scoped Lval* lval_ns_symbol = make_lval_ns_symbol(); */
  /* Lval* lval_ns = make_lval_namespace(ns); */

  /* lenv_put(stdlib_env, lval_ns_symbol, lval_ns); */
  /* return lval_ns; */
  return make_lval_nil();
}

Lval* in_ns_fn(Lenv* _, Lval* arg_list) {
  ITER_NEW_N("in-ns", 1);
  ITER_NEXT_TYPE(LVAL_SYMBOL, -1)
  Lval* lval_symbol = arg;
  ITER_END
  /* Namespace* ns = alist_get(state->namespaces, is_eq_str, lval_symbol->str);
   */
  /* if (!ns) { */
  /*   ns = lalloc_type(NAMESPACE); */
  /*   *ns = (Namespace){.namespace = retain(lval_symbol->str), .env =
   * lenv_new()}; */
  /*   state->namespaces = alist_prepend(state->namespaces, lval_symbol->str,
   * ns); */
  /* } */

  Namespace* ns = make_or_get_namespace(lval_symbol->str);
  set_current_ns(ns);
  return make_lval_nil();
  /* Namespace* ns = make_or_get_namespace(lval_symbol->str); */
  /* Lenv* stdlib_env = get_stdlib_env(); */
  /* scoped Lval* lval_ns_symbol = make_lval_ns_symbol(); */
  /* Lval* lval_ns = make_lval_namespace(ns); */

  /* lenv_put(stdlib_env, lval_ns_symbol, lval_ns); */
  /* return lval_ns; */
}

Lval* require_ns(Lenv* _, char* ns) {
  Namespace* current_namespace = get_current_ns();
  scoped char* file_name = ns_to_src(ns);
  Lval* result = load(NULL, file_name);

  set_current_ns(current_namespace);
  return result;
}

struct require_info {
  char* namespace_str;
  char* as;
  Lval* refer;
  Lval* error;
};

struct require_info parse_require_vector(Lval* vector) {
  struct require_info ret = {};

  Cell* head = vector->head;
  if (list_count(vector->head) > 5) {
    ret.error = make_lval_err("Too many args passed to require (>5)");
    return ret;
  } else if (head && ((Lval*)head->car)->type == LVAL_SYMBOL) {
    ret.namespace_str = ((Lval*)head->car)->str;
  } else {
    ret.error = make_lval_err(
        "Expecting namespace symbol as first element of quoted vector passed "
        "to require.");
    return ret;
  }

  // Loop through require vector and assign values to 'as' and 'refer' if found.
  head = head->cdr;
  while (head) {
    Lval* lval = head->car;
    if (lval->subtype != KEYWORD) {
      ret.error = make_lval_err(
          "Expecting a keyword such as :as or :refer in quoted vector passed "
          "to require");
      return ret;
    }
    Lval* kw = lval;
    head = head->cdr;
    if (!head) {
      ret.error =
          make_lval_err("Expecting arg after keyword :%s in require", kw->str);
      return ret;
    }
    lval = head->car;
    if (_strcmp(kw->str, "as") == 0) {
      if (ret.as) {
        ret.error =
            make_lval_err("Expecting only one :as keyword in require vector");
        return ret;
      }
      ret.as = lval->str;
    } else if (_strcmp(kw->str, "refer") == 0) {
      if (ret.refer) {
        ret.error = make_lval_err(
            "Expecting only one :refer keyword in require vector");
        return ret;
      }
      ret.refer = lval;
    } else {
      ret.error = make_lval_err(
          "Expecting only :as and :refer keywords in require vector, "
          "not :%s",
          kw->str);
      return ret;
    }
    head = head->cdr;
  }

  if (ret.refer) {
    if (ret.refer->subtype != VECTOR) {
      ret.error = make_lval_err(
          "Expecting arg to refer to be a vector in require vector");
      return ret;
    }
  }
  return ret;
}

// A more limited and restricted version of clojure's require.
Lval* require_fn(Lenv* _, Lval* arg_list) {
  ITER_NEW_N("require", 1);
  ITER_NEXT_TYPE(LVAL_COLLECTION, VECTOR)
  Lval* vector = arg;
  ITER_END

  Namespace* current_namespace = get_current_ns();
  /* printf("in require_fn: %s\n", current_namespace->namespace); */

  // If we haven't required the ns yet we require it now, otherwise we use a
  // cached one.
  struct require_info info = parse_require_vector(vector);
  Namespace* required_ns = get_namespace(info.namespace_str);
  if (!required_ns) {
    Lval* ret = require_ns(NULL, info.namespace_str);
    if (ret->type == LVAL_ERR) return ret;
    release(ret);
    required_ns = get_namespace(info.namespace_str);

    if (!required_ns)
      return make_lval_err("Loaded %s, but haven't found namespace %s",
                           ns_to_src(info.namespace_str), info.namespace_str);
  }

  current_namespace->required =
      alist_put(current_namespace->required, is_eq_str, required_ns->namespace,
                required_ns);
  current_namespace->as = alist_put(current_namespace->as, is_eq_str,
                                    info.namespace_str, info.namespace_str);

  /* printf("current_namespace->required len: %d\n", */
  /*        list_count(current_namespace->required)); */

  // Add the required namespace to deps as a alternative ns str mapped to the
  // same env.
  if (info.as) {
    char* ns_str = alist_get(current_namespace->as, is_eq_str, info.as);
    if (ns_str) warn("%s is already an alias for %s\n", info.as, ns_str);
    current_namespace->as = alist_prepend(
        current_namespace->as, retain(info.as), retain(info.namespace_str));
  }

  // Add the referred symbols to the refer env of the current namespace
  if (info.refer) {
    Cell* head = info.refer->head;
    while (head) {
      Lval* lval_sym = head->car;
      Lval* lval = lenv_get_or_error(required_ns->env, lval_sym);
      if (lval->type == LVAL_ERR) return lval;
      release(lval);
      lval = lenv_get_or_error(current_namespace->env, lval_sym);
      if (lval->type != LVAL_ERR) {
        release(lval);
        return make_lval_err(
            "%s can't refer to %s/%s because it's already bound in the current "
            "namespace",
            lval_sym->str, required_ns->namespace, lval_sym->str);
      }
      char* ns_str =
          alist_get(current_namespace->refer, is_eq_str, lval_sym->str);
      if (ns_str) {
        warn("Symbol %s is referring already to a value in %s\n", lval_sym->str,
             ns_str);
      }
      release(lval);

      /* printf("REQUIRE: adding %s to current_namespace->refer as %s\n", */
      /*        lval_sym->str, required_namespace_sym->str); */
      current_namespace->refer =
          alist_prepend(current_namespace->refer, retain(lval_sym->str),
                        retain(info.namespace_str));
      head = head->cdr;
    }
  }
  return make_lval_nil();
}

void print_lval(void* lval) { lval_print(lval); }

Lval* partial_fn(Lenv* env, Lval* arg_list) {
  ITER_NEW_MIN("partial", 1)
  ITER_NEXT_TYPE(LVAL_FUNCTION, -1)
  Lval* lval_fun = arg;
  if (lval_fun->subtype == MACRO || lval_fun->subtype == SPECIAL)
    return make_lval_err(
        "Can't take value of a macro or special form such as %s",
        lval_fun->str);
  int rest_arg_index = lval_fun->rest_arg_index;  // 1 based
  int param_count = lval_fun->param_count;
  int arg_list_count =
      list_count(lval_fun->partials) + list_count(arg_list->head) - 1;
  if (!rest_arg_index && lval_fun->subtype != SYS &&
      arg_list_count > param_count)
    return make_lval_err("Too many args, expected not more than %i, got %i.",
                         param_count, arg_list_count);

  /* printf("Current partials: "); */
  /* list_print(lval_fun->partials, print_lval, ", "); */

  Lval* partial_fn =
      make_lval_lambda(retain(lval_fun->closure), retain(lval_fun->params),
                       retain(lval_fun->body), LAMBDA);
  partial_fn->fun = lval_fun->fun;
  partial_fn->subtype = lval_fun->subtype;
  partial_fn->param_count = lval_fun->param_count;
  partial_fn->rest_arg_index = lval_fun->rest_arg_index;
  partial_fn->partials = list_concat(lval_fun->partials, arg_list->head->cdr);

  return partial_fn;
}

Lval* apply_fn(Lenv* env, Lval* arg_list) {
  ITER_NEW_MIN("partial", 2)
  ITER_NEXT_TYPE(LVAL_FUNCTION, -1)
  Lval* lval_fun = arg;
  if (lval_fun->subtype == MACRO || lval_fun->subtype == SPECIAL)
    return make_lval_err(
        "Can't take value of a macro or special form such as %s",
        lval_fun->str);
  ITER_NEXT
  Lval* args = make_lval_list();
  Cell** cdr = &args->head;
  Cell* head = iter_current_cell(i);
  while (head) {
    arg = head->car;
    if (!head->cdr) {
      switch (arg->subtype) {
        case LNIL:
          break;
        case LIST:;
          head = arg->head;
          while (head) {
            arg = head->car;
            Cell* c = make_cell();
            c->car = retain(arg);
            *cdr = c;
            cdr = &c->cdr;
            head = head->cdr;
          }
          continue;
        case MAP:
        case SET:
        case VECTOR:
        default:
          return make_lval_err("Don't know how to make a list of %s",
                               lval_type_to_name(arg));
      }
    } else {
      Cell* c = make_cell();
      c->car = retain(arg);
      *cdr = c;
      cdr = &c->cdr;
    }
    head = head->cdr;
  }
  return eval_lambda_call(lval_fun, args);
}

RuntimeFn misc_builtins[] = {{"eval", eval_fn},
                             {"print-env", print_env_fn},
                             {"exit", exit_fn},
                             {"load", load_fn},
                             /* {"mpc_load", mpc_load_fn}, */
                             {"macroexpand", macroexpand_fn},
                             {"macroexpand-1", macroexpand_1_fn},
                             /* {"compile", compile_fn}, */
                             {"in-ns", in_ns_fn},
                             {"require", require_fn},
                             {"partial", partial_fn, "partial_fn", 2, 1},
                             {"apply", apply_fn, "apply", 2, 1},
                             {NIL}

};
