#ifndef __LVAL_MEMPOOL_H_
#define __LVAL_MEMPOOL_H_

#include "mempool.h"

// The order and number of these types needs to match!!
enum {
  LVAL,
  LENV,
  CELL,
  ITER,
  INTERNAL,
  CHAR8,
  CHAR16,
  CHAR32,
  CHAR64,
  CHAR128,
  CHAR256,
  CHAR512,
  SLOT_TYPE_COUNT
};

#define MAX_CHAR_SIZE 512

void clean_up(void* data);
#define scoped __attribute__((__cleanup__(clean_up)))

Mempool* lval_mempool;
void init_lispy_mempools(uint lval_count, int lenv_count, int cell_count);
void free_lispy_mempools();

void* lalloc_type(int type);
void* lalloc_size(int size);
void* lrealloc(void* data_p, int size);
void* retain(void* data_p);
void release(void* data_p);
typedef void (*Destructor)(void*);

void print_mempool_free(int type);
int get_free_slot_count(int type);
int get_taken_slot_count(int type);
void print_mempool_counts();
int get_ref_count(void* data_p);
#endif  // __LVAL_MEMPOOL_H_
