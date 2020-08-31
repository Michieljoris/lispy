#include "wasm_util.h"

#include <binaryen-c.h>

#include "compile.h"
#include "env.h"
#include "fns.h"
#include "lib.h"
#include "lispy_mempool.h"
#include "list.h"
#include "ltypes.h"
#include "misc_fns.h"
#include "platform.h"
#include "print.h"
#include "wasm.h"

CResult wasm_retain(Wasm* wasm, Ber wval) {
  BinaryenModuleRef module = wasm->module;
  Ber operands[] = {wval};
  return cresult(
      BinaryenCall(module, "retain", operands, 1, BinaryenTypeInt32()));
}

CResult wasm_retain_and_drop(Wasm* wasm, Ber wval) {
  BinaryenModuleRef module = wasm->module;
  Ber operands[] = {wval};
  return cresult(BinaryenDrop(module, BinaryenCall(module, "retain", operands,
                                                   1, BinaryenTypeInt32())));
}

CResult wasm_release(Wasm* wasm, Ber wval) {
  BinaryenModuleRef module = wasm->module;
  Ber operands[] = {wval};
  return cresult(
      BinaryenCall(module, "release", operands, 1, BinaryenTypeInt32()));
}

void write_string(char* file_name, char* str) {
  FILE* f = fopen(file_name, "wb");
  fputs(str, f);
  fclose(f);
}
void write_binary(char* file_name, void* bin, size_t size) {
  FILE* f = fopen(file_name, "wb");
  fwrite(bin, 1, size, f);
  fclose(f);
}

void write_wat(Wasm* wasm, char* file_name) {
  BinaryenSetColorsEnabled(0);
  char* output = BinaryenModuleAllocateAndWriteText(wasm->module);
  /* printf("%s %d\n", output, _strlen(output)); */
  write_string(file_name, output);
  free(output);
  BinaryenSetColorsEnabled(1);
}

void write_wasm(Wasm* wasm, char* file_name) {
  BinaryenModuleRef module = wasm->module;
  BinaryenModuleAllocateAndWriteResult result =
      BinaryenModuleAllocateAndWrite(module, NULL);

  void* binary = result.binary;
  size_t binaryBytes = result.binaryBytes;
  char* sourceMap = result.sourceMap;
  /* printf("%s \n%zu \n%s\n", binary, binaryBytes, sourceMap); */
  write_binary(file_name, binary, binaryBytes);
  free(binary);
  free(sourceMap);
}

BinaryenExpressionRef make_int32(BinaryenModuleRef module, int x) {
  return BinaryenConst(module, BinaryenLiteralInt32(x));
}

BinaryenExpressionRef wasm_log_int(Wasm* wasm, int int32) {
  BinaryenModuleRef module = wasm->module;

  BinaryenExpressionRef operands[] = {make_int32(module, int32)};

  BinaryenExpressionRef log_int =
      BinaryenCall(module, "log_int", operands, 1, BinaryenTypeNone());

  return log_int;
}

BinaryenExpressionRef wasm_offset(Wasm* wasm, int offset) {
  return make_int32(wasm->module, wasm->__data_end + offset);
}

BinaryenExpressionRef wasm_log_string(Wasm* wasm, int offset) {
  BinaryenModuleRef module = wasm->module;

  BinaryenExpressionRef operands[] = {wasm_offset(wasm, offset)};

  BinaryenExpressionRef log_string =
      BinaryenCall(module, "log_string", operands, 1, BinaryenTypeNone());

  return log_string;
}

CResult wasm_runtime_error(Wasm* wasm, int err_no, char* msg) {
  /* va_list va; */
  /* va_start(va, fmt); */
  /* char* err_msg = lalloc_size(512); */
  /* vsnprintf(err_msg, 511, fmt, va); */
  /* /\* err_msg = lrealloc(err_msg, _strlen(err_msg) + 1); *\/ */
  /* va_end(va); */
  int msg_offset = add_string_to_data(wasm, msg);
  /* release(err_msg); */

  BinaryenModuleRef module = wasm->module;

  BinaryenExpressionRef operands[] = {make_int32(wasm->module, err_no),
                                      wasm_offset(wasm, msg_offset)};

  BinaryenExpressionRef runtime_error =
      BinaryenCall(module, "runtime_error", operands, 2, BinaryenTypeNone());

  return cresult(runtime_error);
}

BinaryenExpressionRef wasm_log_string_n(Wasm* wasm, int offset, int n) {
  BinaryenModuleRef module = wasm->module;

  BinaryenExpressionRef operands[] = {wasm_offset(wasm, offset),
                                      make_int32(module, n)};

  BinaryenExpressionRef log_string_n =
      BinaryenCall(module, "log_string_n", operands, 2, BinaryenTypeNone());

  return log_string_n;
}

BinaryenExpressionRef wasm_printf(Wasm* wasm, int offset) {
  BinaryenModuleRef module = wasm->module;

  BinaryenExpressionRef operands[] = {wasm_offset(wasm, offset),
                                      make_int32(module, 0)};

  BinaryenExpressionRef printf =
      BinaryenCall(module, "printf", operands, 2, BinaryenTypeNone());

  BinaryenExpressionRef drop = BinaryenDrop(module, printf);
  return drop;
}

int add_bytes_to_data(Wasm* wasm, char* data, int len) {
  int offset = wasm->data_offset;
  /* printf("%d %d\n", wasm->strings_offset, len); */
  wasm->data = realloc(wasm->data, offset + len);
  _memmove(wasm->data + offset, data, len);

  wasm->data_offset += len;
  /* printf("strings_offset: %d\n", wasm->strings_offset); */
  return offset;
}

int add_string_to_data(Wasm* wasm, char* str) {
  int* ret = (int*)alist_get(wasm->string_pool, is_eq_str, str);
  if (!ret) {
    int len = _strlen(str) + 1;
    int offset = wasm->data_offset;
    wasm->data = realloc(wasm->data, offset + len);
    _strncpy(wasm->data + offset, str, len);

    wasm->data_offset += len;
    ret = malloc(sizeof(int));
    *ret = offset;
    wasm->string_pool = alist_prepend(wasm->string_pool, str, ret);
  }
  return *ret;
}

int add_fn_to_table(Wasm* wasm, char* fn_name) {
  int free_fn_slot = wasm->fns_count;
  wasm->fns_count++;
  wasm->fn_names = realloc(wasm->fn_names, wasm->fns_count * sizeof(char*));
  int len = _strlen(fn_name) + 1;
  wasm->fn_names[free_fn_slot] = malloc(len);
  _strncpy(wasm->fn_names[free_fn_slot], fn_name, len);
  return free_fn_slot;
}

Lenv* load_stdlib() {
  Lenv* root_env = lenv_new();
  lenv_add_builtin_fns(root_env);

  Lenv* stdlib_env = lenv_new();
  stdlib_env->parent_env = retain(root_env);

  stdlib_env->is_user_env = 1;
  slurp(stdlib_env, "lispy/stdlib.lispy");
  stdlib_env->is_user_env = 0;
  return stdlib_env;
}

Lenv* interprete_file(char* file_name) {
  Lenv* stdlib_env = load_stdlib();
  Lenv* user_env = lenv_new();
  user_env->parent_env = retain(stdlib_env);
  stdlib_env->is_user_env = 0;
  user_env->is_user_env = 1;

  Lval* result = slurp(user_env, file_name);
  if (result->type == LVAL_ERR) exit(1);
  release(result);
  return user_env;
}

Lenv* require_file(Lenv* env, char* file_name) {
  Lenv* user_env = lenv_new();
  user_env->parent_env = env;
  user_env->is_user_env = 1;
  Lval* result = slurp(user_env, file_name);
  if (result->type == LVAL_ERR) exit(1);
  release(result);
  user_env->parent_env = NULL;
  return user_env;
}

void release_env(Lenv* env) {
  release(env->kv);
  env->kv = NIL;
  Lenv* parent_env = env->parent_env;
  release(env);
  if (parent_env) release_env(parent_env);
}

void add_test_fn(Wasm* wasm) {
  BinaryenModuleRef module = wasm->module;

  add_string_to_data(wasm, "foo3");
  add_string_to_data(wasm, "bar");
  /* printf("strings_data: %s\n", wasm->strings); */
  /* printf("strings_data: %s\n", wasm->strings + _strlen("foo3") + 1); */

  BinaryenType localTypes[] = {};
  /* BinaryenType localTypes[] = {BinaryenTypeInt32(), BinaryenTypeInt32()}; */

  /* int offset = 5; */
  /* BinaryenExpressionRef printf = wasm_printf(wasm, offset); */
  /* BinaryenExpressionRef log_int = wasm_log_int(wasm, 123); */
  /* BinaryenExpressionRef log_string = wasm_log_string(wasm, offset); */
  /* BinaryenExpressionRef log_string_n = wasm_log_string_n(wasm, offset, 2); */

  /* BinaryenExpressionRef my_value_list[] = {printf, log_int, log_string, */
  /*                                          log_string_n}; */
  BinaryenType TypeNone = BinaryenTypeNone();
  BinaryenType TypeInt32x1 = make_type_int32(1);
  BinaryenExpressionRef my_value_list[] = {};
  BinaryenExpressionRef body =
      BinaryenBlock(module, "my-block", my_value_list,
                    sizeof(my_value_list) / sizeof(BinaryenExpressionRef),
                    BinaryenTypeAuto());

  BinaryenAddFunction(module, "test", TypeNone, TypeInt32x1, localTypes,
                      sizeof(localTypes) / sizeof(BinaryenType), body);
  BinaryenAddFunctionExport(wasm->module, "test", "test");
}

BinaryenType* make_type_int32_array(int count) {
  BinaryenType* types = malloc(count * sizeof(BinaryenTypeInt32()));
  while (count--) types[count] = BinaryenTypeInt32();
  return types;
}

BinaryenType make_type_int32(int count) {
  BinaryenType* _type = make_type_int32_array(count);
  BinaryenType ret = BinaryenTypeCreate(_type, count);
  free(_type);
  return ret;
}

Wasm* enter_context(Wasm* wasm) {
  Context* prev_context = wasm->context->car;
  Cell* cell = malloc(sizeof(Cell));
  cell->cdr = wasm->context;
  wasm->context = cell;
  Context* new_context = malloc(sizeof(Context));
  wasm->context->car = new_context;
  new_context->function_context = prev_context->function_context;
  return wasm;
}

void leave_context(Wasm* wasm) {
  Context* context = wasm->context->car;
  Cell* prev_context_cell = wasm->context->cdr;
  /* printf("leaving context %s\n", context->msg); */
  /* if (prev_context_cell && */
  /*     context->local_count !=
   * ((Context*)(prev_context_cell->car))->local_count) */
  /*   free(context->local_count); */

  if (prev_context_cell &&
      context->function_context !=
          ((Context*)(prev_context_cell->car))->function_context) {
    release(context->function_context->closure);
    free(context->function_context);
  }

  free(context);
  free(wasm->context);
  wasm->context = prev_context_cell;
}

void _leave_context(void* data) { leave_context(*(void**)data); }

void print_cell(void* cell) {
  printf("CELL");
  lval_print((Lval*)((Cell*)cell)->car);
}

void print_context(Context* c) {
  if (c) {
    printf("msg: %s\n", c->msg);
    printf("fn_name: %s\n", c->function_context->fn_name);
    printf("fn closure:\n");
    env_print(c->function_context->closure);
    if (c->lval) lval_println(c->lval);

    if (c->cell) {
      putchar('(');
      Cell* cell = c->cell;
      while (cell) {
        lval_print(cell->car);
        cell = cell->cdr;
        if (cell) putchar(' ');
      }
      putchar(')');
      putchar('\n');
    }
  }
}

void print_wasm_context(Wasm* wasm) {
  Context* c = wasm->context->car;
  print_context(c);
}

Lenv* enter_env(Wasm* wasm) {
  Lenv* new_env = lenv_new();
  new_env->parent_env = retain(wasm->env);
  wasm->env = new_env;
  return new_env;
}

void leave_env(Wasm* wasm) {
  Lenv* env = wasm->env;
  wasm->env = env->parent_env;
  release(env->kv);
  env->kv = NIL;
  /* release(env); */
}

Lval* make_lval_compiler(Context* context, int subtype, int offset) {
  Lval* lval = lalloc_type(LVAL);
  *lval = (Lval){.type = LVAL_COMPILER,
                 .subtype = subtype,
                 .offset = offset,
                 .context = context};
  return lval;
}

int id = 1;

char* uniquify_name(Wasm* wasm, char* name) {
  char* str = malloc(1024);
  if (_strlen(name) > 512)
    quit(wasm, "ERROR: Can't uniquify names longer than 512 chars");
  _strcpy(str, name);
  _strcat(str, "_");
  itostr(str + _strlen(str), id++);
  return str;
}

#define MAX_LOCAL_INDICES 128

LocalIndices* li_init() {
  LocalIndices* li = malloc(sizeof(LocalIndices));
  *li = (LocalIndices){.local_indices = malloc(MAX_LOCAL_INDICES * 4),  // 512
                       .local_indices_count = 0};
  return li;
}

int li_new(Wasm* wasm) {
  Context* context = wasm->context->car;
  return context->function_context->local_count++;
}

int li_get(Wasm* wasm) {
  Context* context = wasm->context->car;
  return context->function_context->local_count;
}

int li_track(Wasm* wasm, LocalIndices* li, int index) {
  int ret = li->local_indices[li->local_indices_count++] = index;
  if (li->local_indices_count == MAX_LOCAL_INDICES)
    quit(wasm, "ERROR: Can't keep track of more than %d local indices",
         MAX_LOCAL_INDICES);
  return ret;
}

/* int li_get_and_track(Wasm* wasm, LocalIndices* li) { */
/*   int index = li->local_indices[li->local_indices_count++] = li_new(wasm); */
/*   printf("LI: %d %d", li->local_indices_count, */
/*          li->local_indices[li->local_indices_count - 1]); */
/*   if (li->local_indices_count == MAX_LOCAL_INDICES) */
/*     quit(wasm, "ERROR: Can't keep track of more than %d local indices", */
/*          MAX_LOCAL_INDICES); */
/*   return index; */
/* } */

CResult li_release(Wasm* wasm, LocalIndices* li, char* name) {
  if (li->local_indices_count == 0) {
    return cnull();
  }
  BinaryenModuleRef module = wasm->module;
  Ber release_locals[li->local_indices_count];
  Ber get_local[1];
  for (int i = 0; i < li->local_indices_count; i++) {
    get_local[0] =
        BinaryenLocalGet(module, li->local_indices[i], BinaryenTypeInt32());
    release_locals[i] =
        BinaryenCall(module, "release", get_local, 1, BinaryenTypeNone());
  }

  Ber release_locals_block =
      BinaryenBlock(module, uniquify_name(wasm, name), release_locals,
                    li->local_indices_count, BinaryenTypeNone());
  return cresult(release_locals_block);
}

CResult li_result_with_release(Wasm* wasm, LocalIndices* li, char* name,
                               Ber release_locals, Ber result) {
  if (!release_locals) return cresult(result);
  BinaryenModuleRef module = wasm->module;
  int result_index = li_new(wasm);
  Ber set_local_to_result = BinaryenLocalSet(module, result_index, result);
  Ber get_result_from_local =
      BinaryenLocalGet(module, result_index, BinaryenTypeInt32());
  Ber body_result[] = {set_local_to_result, release_locals,
                       get_result_from_local};
  return cresult(BinaryenBlock(module, uniquify_name(wasm, name), body_result,
                               3, BinaryenTypeInt32()));
}

void li_close(LocalIndices* li) {
  free(li->local_indices);
  free(li);
}

CResult cresult(Ber ber) {
  CResult cr = {.ber = ber};
  return cr;
}

CResult cnull() {
  CResult cr = {};
  return cr;
}

CResult wasm_lalloc_type(Wasm* wasm, int type) {
  Ber operands[1] = {make_int32(wasm->module, type)};
  return cresult(BinaryenCall(wasm->module, "lalloc_type", operands, 1,
                              make_type_int32(1)));
}

CResult wasm_lalloc_size(Wasm* wasm, int size) {
  Ber operands[1] = {make_int32(wasm->module, size)};
  return cresult(BinaryenCall(wasm->module, "lalloc_size", operands, 1,
                              make_type_int32(1)));
}
