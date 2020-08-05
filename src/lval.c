#include "lval.h"

#include "cell.h"

/* #include "hash.h" */
#include "io.h"
#include "lib.h"
#include "lispy_mempool.h"

/* SYMBOL */

int seed = 123;
int str_seed = 124;
int sym_seed = 125;

int lval_hash(Lval* lval) {
  int hash = -1;
  switch (lval->type) {
    case LVAL_FUNCTION:
    case LVAL_ERR:
      /* hash = murmur3_int(long_hash((unsigned long)lval), seed); */
      break;
    case LVAL_SYMBOL:
      /* hash = murmur3_str(lval->str, _strlen(lval->str), sym_seed); */
      break;
    case LVAL_LITERAL:
      switch (lval->subtype) {
        case STRING:
          /* hash = murmur3_str(lval->str, _strlen(lval->str), str_seed);  // */
          break;
        case NUMBER:
          /* hash = murmur3_int(long_hash_munge(lval->num), seed); */
          break;
        case LNIL:
          hash = 0;
          break;
        case LTRUE:
          hash = 1;
          break;
        case LFALSE:
          hash = 2;
          break;
        default:
          printf("OOPS, can't calculate hash of uknown collection subtype %d\n",
                 lval->subtype);
      }
      break;

    case LVAL_COLLECTION:
      switch (lval->subtype) {
        case LIST:
        case VECTOR:
          hash = 3;
          break;
        case MAP:
          hash = 4;
          break;
        default:
          printf("OOPS, can't calculate hash of uknown collection subtype %d\n",
                 lval->subtype);
      }
      break;
    default:
      printf("OOPS, can't calculate hash of uknown type %d\n", lval->type);
  }
  return hash;
}

Lval* make_lval_sym(char* s) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_SYMBOL, .subtype = -1, .str = retain(s)};
  lval->hash = lval_hash(lval);
  return lval;
}

/* COLLECTION */

Lval* make_lval_list(void) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_COLLECTION, .subtype = LIST};
  lval->hash = lval_hash(lval);
  return lval;
}

Lval* new_lval_list(void* head) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_COLLECTION, .subtype = LIST, .head = head};
  lval->hash = lval_hash(lval);
  return lval;
}

Lval* make_lval_vector(void) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_COLLECTION, .subtype = VECTOR};
  lval->hash = lval_hash(lval);
  return lval;
}

Lval* make_lval_map(void) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_COLLECTION, .subtype = MAP};
  lval->hash = lval_hash(lval);
  return lval;
}

/* LITERAL */

Lval* make_lval_nil() {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_LITERAL, .subtype = LNIL};
  lval->hash = lval_hash(lval);
  return lval;
}

Lval* make_lval_true() {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_LITERAL, .subtype = LTRUE};
  lval->hash = lval_hash(lval);
  return lval;
}

Lval* make_lval_false() {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_LITERAL, .subtype = LFALSE};
  lval->hash = lval_hash(lval);
  return lval;
}

Lval* make_lval_num(long x) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_LITERAL, .subtype = NUMBER, .num = x};
  lval->hash = lval_hash(lval);
  return lval;
}

Lval* make_lval_str(char* s) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){
      .type = LVAL_LITERAL,
      .subtype = STRING,
      .str = retain(s),
  };
  lval->hash = lval_hash(lval);
  return lval;
}

/* FUNCTION */

// SYSTEM and SPECIAL
Lval* make_lval_fun(Lbuiltin func, char* func_name, int subtype) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_FUNCTION,
                 .subtype = subtype,
                 .fun = func,
                 .str = retain(func_name)};
  lval->hash = lval_hash(lval);
  return lval;
}

// LAMBDA and MACRO
Lval* make_lval_lambda(Lenv* env, Lval* params, Lval* body, int subtype) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_FUNCTION,
                 .subtype = subtype,
                 .closure = env,
                 .params = params,
                 .body = body};
  lval->hash = lval_hash(lval);
  return lval;
}

Lval* make_lval_wasm_lambda(int fn_table_index, int param_count,
                            int has_rest_arg, Lval** closure, Lval** partials,
                            int partial_count) {
  Wval* wval = lalloc_type(LVAL);
  *wval = (Wval){.type = LVAL_WASM_LAMBDA,
                 .subtype = -1,
                 .fn_table_index = fn_table_index,
                 .param_count = param_count,
                 .has_rest_arg = has_rest_arg,
                 .closure = closure,
                 .partials = partials,
                 .partial_count = partial_count};
  return (Lval*)wval;
}

/* ERROR */

// System error
Lval* make_lval_err(char* fmt, ...) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_ERR, .subtype = SYS, .str = lalloc_size(512)};

  va_list va;
  va_start(va, fmt);
  vsnprintf(lval->str, 511, fmt, va);
  lval->str = lrealloc(lval->str, _strlen(lval->str) + 1);
  va_end(va);
  lval->hash = lval_hash(lval);
  return lval;
}

// User error
Lval* make_lval_exception(char* msg) {
  Lval* lval = make_lval_err(msg);
  lval->subtype = USER;
  return lval;
}

char* lval_type_constant_to_name(int t) {
  switch (t) {
    case LVAL_LITERAL:
      return "Literal";
    case NUMBER:
      return "Number";
    case LVAL_SYMBOL:
      return "Symbol";
    case LVAL_COLLECTION:
      return "Collection";
    case LVAL_ERR:
      return "Error";
    case LVAL_FUNCTION:
      return "Function";
    case STRING:
      return "String";
    case LIST:
      return "List";
    case VECTOR:
      return "Vector";
    case MAP:
      return "Map";

    case LTRUE:
      return "true";
    case LFALSE:
      return "false";
    case LNIL:
      return "nil";
    case LVAL_WASM_REF:
      return "Local ref";
    default:
      return "Unknown";
  }
}

char* lval_type_to_name(Lval* lval) {
  switch (lval->type) {
    case LVAL_SYMBOL:
      return "Symbol";
    case LVAL_COLLECTION:
      switch (lval->subtype) {
        case LIST:
          return "List (coll)";
        case VECTOR:
          return "Vector (coll)";
        case MAP:
          return "Map (coll)";
        default:
          return "unknown collection subtype";
      }
    case LVAL_LITERAL:
      switch (lval->subtype) {
        case NUMBER:
          return "Number";
        case STRING:
          return "String";
        case LTRUE:
          return "true";
        case LFALSE:
          return "false";
        case LNIL:
          return "nil";
      }
    case LVAL_FUNCTION:
      switch (lval->subtype) {
        case SYS:
          return "System Function";
        case LAMBDA:
          return "User Function";
        case SPECIAL:
          return "Special form";
        case MACRO:
          return "Macro";
      }
    case LVAL_ERR:
      return "Error";
    default:
      return "Unknown";
  }
}
