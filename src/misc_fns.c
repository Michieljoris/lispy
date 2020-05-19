#include "misc_fns.h"

#include "assert.h"
#include "eval.h"
#include "grammar.h"
#include "lval.h"
#include "mpc.h"
#include "print.h"
#include "read.h"

Lval* env_put(Lenv* env, Lval* sexpr, char* fn_name, int ROOT_OR_LOCAL) {
  LASSERT_CELL_TYPE(sexpr, 0, LVAL_QEXPR, fn_name)

  Lval* syms = sexpr->node[0];
  for (int i = 0; i < syms->count; ++i) {
    LASSERT(sexpr, syms->node[i]->type == LVAL_SYM,
            "Function %s cannot define a non-symbol"
            "Got %s, expected %",
            fn_name, lval_type_to_name(syms->node[i]->type),
            lval_type_to_name(LVAL_SYM));
  }

  LASSERT(sexpr, syms->count == sexpr->count - 1,
          "Function %s cannot define incorrect number of values to symbols."
          "Got %i, expected %i",
          fn_name, syms->count, sexpr->count - 1);

  if (ROOT_OR_LOCAL == ROOT_ENV) {
    env = get_root_env(env);
  }

  for (int i = 0; i < syms->count; ++i) {
    bool is_not_internal_var = lenv_put(env, syms->node[i], sexpr->node[i + 1]);
    LASSERT(sexpr, is_not_internal_var,
            "Can't redefine internal variable '%s' ", syms->node[i]->sym);
  }
  lval_del(sexpr);
  return make_lval_sexpr();
}

Lval* def_fn(Lenv* env, Lval* sexpr) {
  return env_put(env, sexpr, "def", ROOT_ENV);
}

Lval* set_fn(Lenv* env, Lval* sexpr) {
  return env_put(env, sexpr, "set", LOCAL_ENV);
}

Lval* print_env_fn(Lenv* e, Lval* sexpr) {
  lenv_print(e);
  lval_del(sexpr);
  return make_lval_sexpr();
}

bool exit_repl = false;

Lval* exit_fn(Lenv* e, Lval* sexpr) {
  lval_del(sexpr);
  exit_repl = true;
  return make_lval_sexpr();
}

Lval* lambda_fn(Lenv* env, Lval* sexpr) {
  LASSERT_CELL_COUNT(sexpr, 2, "fn");
  LASSERT_CELL_TYPE(sexpr, 0, LVAL_QEXPR, "fn");
  LASSERT_CELL_TYPE(sexpr, 1, LVAL_QEXPR, "fn");

  for (int i = 0; i < sexpr->node[0]->count; ++i) {
    LASSERT(sexpr, sexpr->node[0]->node[i]->type == LVAL_SYM,
            "Canot define non-symbol. Got %s, expected %s.",
            lval_type_to_name(sexpr->node[0]->node[i]->type),
            lval_type_to_name(LVAL_SYM));
  }

  Lval* formals = lval_pop(sexpr, 0);
  Lval* body = lval_pop(sexpr, 0);
  lval_del(sexpr);

  return make_lval_lambda(formals, body);
}

Lval* if_fn(Lenv* env, Lval* sexpr) {
  LASSERT_CELL_COUNT(sexpr, 3, "if");
  LASSERT_CELL_TYPE(sexpr, 0, LVAL_NUM, "if");
  LASSERT_CELL_TYPE(sexpr, 1, LVAL_QEXPR, "if");
  LASSERT_CELL_TYPE(sexpr, 2, LVAL_QEXPR, "if");

  Lval* x;
  sexpr->node[1]->type = LVAL_SEXPR;
  sexpr->node[2]->type = LVAL_SEXPR;

  if (sexpr->node[0]->num) {
    x = lval_eval(env, lval_pop(sexpr, 1));
  } else {
    x = lval_eval(env, lval_pop(sexpr, 2));
  }
  lval_del(sexpr);
  return x;
}

Lval* load_fn(Lenv* env, Lval* sexpr_args) {
  LASSERT_CELL_COUNT(sexpr_args, 1, "load");
  LASSERT_CELL_TYPE(sexpr_args, 0, LVAL_STR, "load");

  mpc_result_t result;
  if (mpc_parse_contents(sexpr_args->node[0]->str, Lispy, &result)) {
    Lval* expr = lval_read(result.output);
    mpc_ast_delete(result.output);
    while (expr->count) {
      Lval* x = lval_eval(env, lval_pop(expr, 0));
      if (x->type == LVAL_ERR) {
        lval_println(x);
      }
      lval_del(x);
    }
    lval_del(expr);
    lval_del(sexpr_args);
    return make_lval_sexpr();
  } else {
    char* err_msg = mpc_err_string(result.error);
    mpc_err_delete(result.error);
    Lval* err = make_lval_err("Could load library %s", err_msg);
    free(err_msg);
    lval_del(sexpr_args);
    return err;
  }
}

Lval* print_fn(Lenv* env, Lval* sexpr_args) {
  for (int i = 0; i < sexpr_args->count; ++i) {
    lval_print(sexpr_args->node[i]);
    putchar(' ');
  }
  putchar('\n');
  lval_del(sexpr_args);

  return make_lval_sexpr();
}

void lenv_add_misc_fns(Lenv* env) {
  lenv_add_builtin(env, "def", def_fn);
  lenv_add_builtin(env, "set", set_fn);
  lenv_add_builtin(env, "print-env", print_env_fn);
  lenv_add_builtin(env, "exit", exit_fn);
  lenv_add_builtin(env, "fn", lambda_fn);
  lenv_add_builtin(env, "if", if_fn);
  lenv_add_builtin(env, "load", load_fn);
  lenv_add_builtin(env, "print", print_fn);
}
