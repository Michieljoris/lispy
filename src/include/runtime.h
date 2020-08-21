#ifndef __RUNTIME_H_
#define __RUNTIME_H_

#include "ltypes.h"

Lval* make_lval_wasm_lambda(int fn_table_index, int param_count,
                            int has_rest_arg, Lval** closure, Lval** partials,
                            int partial_count);

void init_rest_args(Lval** lval_array, int rest_arg_length);

void wval_print(Wval* wval);

int check_args_count(int param_count, int args_count, int has_rest_arg);

#endif  // __RUNTIME_H_