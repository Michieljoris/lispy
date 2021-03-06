#ifndef __MAKE_WASM_FN_H_
#define __MAKE_WASM_FN_H_

#include "ltypes.h"
#include "wasm.h"

Ber switch_on_args_count(Wasm* wasm, Lval* lval_fn, int args_count_param,
                         LambdaBer get_lambda_ber);

enum { ABI_ARGS_BLOCK, ABI_PARAMS };

FunctionData add_wasm_function(Wasm* wasm, Lenv* env, char* fn_name,
                               Lambda* lambda, Cell* symbol_to_ref,
                               int wajure_args);

char* add_arity_to_fn_name(char* fn_name, int index);
int add_root_fn(Wasm* wasm, Lval* lval_fn);
Ber make_local_lambda(Wasm* wasm, Lval* lval_fn, int arity);
FunctionData add_local_lambda(Wasm* wasm, Lval* lval_fn);
#endif  // __MAKE_WASM_FN_H_
