(module
 (type $i32_i32_=>_i32 (func (param i32 i32) (result i32)))
 (type $i32_=>_i32 (func (param i32) (result i32)))
 (type $i32_=>_none (func (param i32)))
 (type $none_=>_i32 (func (result i32)))
 (type $none_=>_none (func))
 (type $i32_i32_=>_none (func (param i32 i32)))
 (type $i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32) (result i32)))
 (import "env" "memory" (memory $0 2 65536))
 (data (i32.const 4088) "HELLO!!!!\00\01\00\00\00\00\00\00\00\00\00\00\00\12\10\00\00\02\t\00\00\00\00\00\00\f8\0f\00\00\00\00\00\00\ff\ff\ff\ff\01\00\00\00\00\00\00\00\00\00\00\006\10\00\00\02\08\00\00\02\00\00\00\f8\0f\00\00\00\00\00\00\ff\ff\ff\ff\01\00\00\00\00\00\00\00\00\00\00\00Z\10\00\00\02\08\00\00\03\00\00\00\f8\0f\00\00\00\00\00\00\ff\ff\ff\ff\01\00\00\00\00\00\00\00\00\00\00\00~\10\00\00\02\08\00\00\01\00\00\00\f8\0f\00\00\00\00\00\00\ff\ff\ff\ff")
 (import "env" "printf_" (func $printf_ (param i32 i32) (result i32)))
 (import "env" "log_int" (func $log_int (param i32)))
 (import "env" "log_string" (func $log_string (param i32)))
 (import "env" "log_string_n" (func $log_string_n (param i32 i32)))
 (import "env" "lval_print" (func $lval_print (param i32)))
 (import "env" "lval_println" (func $lval_println (param i32)))
 (import "env" "make_lval_num" (func $make_lval_num (param i32) (result i32)))
 (import "env" "make_lval_nil" (func $make_lval_nil (result i32)))
 (import "env" "make_lval_true" (func $make_lval_true (result i32)))
 (import "env" "make_lval_false" (func $make_lval_false (result i32)))
 (import "env" "make_lval_str" (func $make_lval_str (param i32) (result i32)))
 (import "env" "make_lval_list" (func $make_lval_list (result i32)))
 (import "env" "new_lval_list" (func $new_lval_list (param i32) (result i32)))
 (import "env" "make_lval_sym" (func $make_lval_sym (param i32) (result i32)))
 (import "env" "make_lval_wasm_lambda" (func $make_lval_wasm_lambda (param i32 i32 i32 i32 i32 i32) (result i32)))
 (import "env" "lalloc_size" (func $lalloc_size (param i32) (result i32)))
 (import "env" "lalloc_type" (func $lalloc_type (param i32) (result i32)))
 (import "env" "list_cons" (func $list_cons (param i32 i32) (result i32)))
 (import "env" "_strcpy" (func $_strcpy (param i32 i32) (result i32)))
 (import "env" "print_slot_size" (func $print_slot_size))
 (import "env" "add_fn" (func $add_fn (param i32 i32) (result i32)))
 (import "env" "sub_fn" (func $sub_fn (param i32 i32) (result i32)))
 (import "env" "mul_fn" (func $mul_fn (param i32 i32) (result i32)))
 (import "env" "div_fn" (func $div_fn (param i32 i32) (result i32)))
 (import "env" "gt_fn" (func $gt_fn (param i32 i32) (result i32)))
 (import "env" "lt_fn" (func $lt_fn (param i32 i32) (result i32)))
 (import "env" "gte_fn" (func $gte_fn (param i32 i32) (result i32)))
 (import "env" "lte_fn" (func $lte_fn (param i32 i32) (result i32)))
 (import "env" "eq_fn" (func $eq_fn (param i32 i32) (result i32)))
 (import "env" "not_eq_fn" (func $not_eq_fn (param i32 i32) (result i32)))
 (import "env" "cons_fn" (func $cons_fn (param i32 i32) (result i32)))
 (import "env" "first_fn" (func $first_fn (param i32 i32) (result i32)))
 (import "env" "list_fn" (func $list_fn (param i32 i32) (result i32)))
 (import "env" "rest_fn" (func $rest_fn (param i32 i32) (result i32)))
 (import "env" "concat_fn" (func $concat_fn (param i32 i32) (result i32)))
 (import "env" "count_fn" (func $count_fn (param i32 i32) (result i32)))
 (import "env" "nth_fn" (func $nth_fn (param i32 i32) (result i32)))
 (import "env" "is_list_fn" (func $is_list_fn (param i32 i32) (result i32)))
 (import "env" "print_fn" (func $print_fn (param i32 i32) (result i32)))
 (import "env" "pr_fn" (func $pr_fn (param i32 i32) (result i32)))
 (import "env" "debug_fn" (func $debug_fn (param i32 i32) (result i32)))
 (import "env" "boolean_fn" (func $boolean_fn (param i32 i32) (result i32)))
 (import "env" "hash_fn" (func $hash_fn (param i32 i32) (result i32)))
 (table $0 5 5 funcref)
 (elem (i32.const 0) $test_1_1 $test_1 $test $log_int $printf_)
 (global $stack_pointer (mut i32) (i32.const 69632))
 (export "test" (func $test))
 (export "mem" (memory $0))
 (func $test_1_1 (param $0 i32) (result i32)
  (block $body (result i32)
   (call $add_fn
    (i32.const 0)
    (call $new_lval_list
     (call $list_cons
      (i32.const 4222)
      (call $list_cons
       (i32.load
        (local.get $0)
       )
       (call $list_cons
        (i32.load offset=4
         (local.get $0)
        )
        (call $list_cons
         (i32.load offset=8
          (local.get $0)
         )
         (call $list_cons
          (i32.load offset=12
           (local.get $0)
          )
          (call $list_cons
           (i32.load
            (global.get $stack_pointer)
           )
           (i32.const 0)
          )
         )
        )
       )
      )
     )
    )
   )
  )
 )
 (func $test_1 (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (block $body (result i32)
   (block $let (result i32)
    (local.set $1
     (i32.const 4186)
    )
    (block $test_1_1 (result i32)
     (local.set $2
      (call $lalloc_size
       (i32.const 16)
      )
     )
     (i32.store offset=12
      (local.get $2)
      (local.get $1)
     )
     (i32.store offset=8
      (local.get $2)
      (i32.load
       (global.get $stack_pointer)
      )
     )
     (i32.store offset=4
      (local.get $2)
      (i32.load
       (local.get $0)
      )
     )
     (i32.store
      (local.get $2)
      (i32.load offset=4
       (local.get $0)
      )
     )
     (call $make_lval_wasm_lambda
      (i32.const 0)
      (i32.const 1)
      (i32.const 0)
      (local.get $2)
      (i32.const 0)
      (i32.const 0)
     )
    )
   )
  )
 )
 (func $test (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (block $body (result i32)
   (drop
    (call $print_fn
     (i32.const 0)
     (call $new_lval_list
      (call $list_cons
       (i32.const 4114)
       (i32.const 0)
      )
     )
    )
   )
   (block $let (result i32)
    (local.set $1
     (i32.const 4150)
    )
    (block $test_1 (result i32)
     (local.set $2
      (call $lalloc_size
       (i32.const 8)
      )
     )
     (i32.store offset=4
      (local.get $2)
      (i32.load
       (global.get $stack_pointer)
      )
     )
     (i32.store
      (local.get $2)
      (local.get $1)
     )
     (call $make_lval_wasm_lambda
      (i32.const 1)
      (i32.const 1)
      (i32.const 0)
      (local.get $2)
      (i32.const 0)
      (i32.const 0)
     )
    )
   )
  )
 )
)
