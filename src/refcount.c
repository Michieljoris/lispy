#include "refcount.h"

#include "io.h"

void mempool_debug(Mempool* mp);

// Allocates a new slot in the mempool.
void* alloc_rc_slot(Mempool* mempool, Destructor destroy) {
  Slot* slot_p = alloc_slot(mempool);
  *slot_p = (Slot){.destroy = destroy,
                   .data_p = ((char*)slot_p + PAD(sizeof(Slot))),
                   .ref_count = 1,
                   .mempool = mempool};
  /* if (debug) ddebug("+%s: ", type_to_name(type)); */
  /* mempool_debug(mp); */
  return slot_p->data_p;
}

void free_rc_slot(Slot* slot) {
  // Zeroing out will catch errors that happen when the slot is freed, but
  // still works as before because it's not been reassigned.
  Mempool* mp = slot->mempool;
  memset(slot, 0, mp->slot_size);
  free_slot(mp, slot);
  /* if (debug) ddebug("-%s: ", type_to_name(type)); */
  /* mempool_debug(mp); */
  /* printf("done %d\n", type); */
}

Slot* get_slot_p(void* data_p) {
  return (Slot*)((char*)data_p - PAD(sizeof(Slot)));
}

// Ups refcount for slot
void* retain(void* data_p) {
  /* Slot* slot = get_slot_p(data_p); */
  /* printf("retain: %s-%li, ref count is %d\n", type_to_name(slot->type), */
  /*        (long int)data_p, slot->ref_count); */
  if (!data_p) {
    /* debug("Trying to retain NULL;\n"); */
  } else {
    ++get_slot_p(data_p)->ref_count;
  }
  return data_p;
}

// Decrease refcount, free slot if 0
void release(void* data_p) {
  if (!data_p) {
    /* printf("Warning: trying to release data with a NULL pointer."); */
    return;
  }
  Slot* slot = get_slot_p(data_p);

  if (data_p != slot->data_p) {
    /* printf("releasing:"); */
    /* lval_println(data_p); */
    warn("Warning: trying to release data that's not managed by ref_count.");
#ifndef WASM
    exit(1);
#endif
    return;
  };

  /* printf("release: %s-%li, ref count is %d\n", type_to_name(slot->type), */
  /*        (long int)data_p, slot->ref_count); */
  if (--slot->ref_count) /* still referenced */ {
    if (slot->ref_count < 0) {
      /* warn("Warning: ref count for a %s has gone negative: %d\n", */
      /*      type_to_name(slot->mempool->type), slot->ref_count); */

      warn(
          "Warning: ref count for a mempool with type %d has gone negative: "
          "%d\n",
          slot->mempool->type, slot->ref_count);
      /* lval_debugln(data_p); */
#ifndef WASM
      exit(1);
#endif
    }
    return;
  }
  /* if (debug) { */
  /*   if (slot->type == LVAL) { */
  /*     ddebug("freeing: (i%d): ", i); */
  /*     lval_debugln(data_p); */
  /*   } else { */
  /*     ddebug("freeing: (i%d) %s: ", i, type_to_name(slot->type)); */
  /*   } */
  /* } */
  if (slot->destroy) slot->destroy(data_p);
  /* if (debug) ddebug("\nactually now freeing slot for i%d ", call_id); */
  free_rc_slot(slot);
}

void clean_up(void* data) {
  /* if (debug) { */
  /*   ddebug("\nCleaning up: "); */
  /*   if (*(void**)data) { */
  /*     lval_debug(*(void**)data); */
  /*     ddebug("\n"); */
  /*   } else */
  /*     ddebug("NIL\n"); */
  /* } */
  release(*(void**)data);
}

int get_free_slot_count(Mempool* mp) { return mp->free_slot_count; }

int get_taken_slot_count(Mempool* mp) {
  return mp->total_slot_count - mp->free_slot_count;
}

/* int get_free_slot_count(int type) { */
/*   Mempool* mp = mempools[type]; */
/*   return mp->free_slot_count; */
/* } */

/* int get_taken_slot_count(int type) { */
/*   Mempool* mp = mempools[type]; */
/*   return mp->total_slot_count - mp->free_slot_count; */
/* } */

int get_ref_count(void* data_p) { return get_slot_p(data_p)->ref_count; }

void mempool_debug(Mempool* mp) {
  /* printf("Total slot count: %i\n", mp->total_slot_count); */
  /* printf("Free slot count: %i\n", mp->free_slot_count); */
  /* printf("Data block count: %i\n", mp->data_block_count); */
  /* printf("Free slot pointer: %p\n", mp->free_slot_p); */
  /* printf("Initialised count: %i\n", mp->initialised_count); */
  ddebug("%d | ", mp->total_slot_count - mp->free_slot_count);
}