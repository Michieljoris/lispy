#ifndef __LVAL_H_
#define __LVAL_H_
#include <stdbool.h>

struct lenv;
struct lval;

typedef struct lenv Lenv;

typedef struct lval Lval;

typedef Lval* (*lbuiltin)(Lenv*, Lval*);

struct lval {
  int type;
  char* sym;
  long num;
  char* err;
  char* str;

  /* function */
  lbuiltin fun;
  char* func_name;
  Lenv* env;
  Lval* formals;
  Lval* body;

  /* list of lval */
  int count;
  Lval** node;
};

struct lenv {
  Lenv* parent_env;
  int count;
  char** syms;
  Lval** lvals;
};

/* lval types */
enum {
  LVAL_NUM,
  LVAL_QUOTE,
  LVAL_ERR,
  LVAL_SYM,
  LVAL_SEXPR,
  LVAL_VECTOR,
  LVAL_QEXPR,
  LVAL_FUN,
  LVAL_STR,
  LVAL_MAP
};

Lval* make_lval_num(long x);
Lval* make_lval_quote(void);
Lval* make_lval_sym(char* s);
Lval* make_lval_str(char* s);
Lval* make_lval_sexpr(void);
Lval* make_lval_qexpr(void);
Lval* make_lval_vector(void);
Lval* make_lval_fun(lbuiltin func, char* func_name);
Lval* make_lval_lambda(Lval* formals, Lval* body);
Lval* make_lval_err(char* fmt, ...);

char* lval_type_to_name(int t);

Lval* lval_add_child(Lval* v, Lval* x);
void lval_del(Lval* v);
Lval* make_lval_copy(Lval* v);
Lval* lval_pop(Lval* v, int i);
Lval* lval_take(Lval* v, int i);

#endif  // __LVAL_H_
