(module
 (type $i32_i32_=>_i32 (func (param i32 i32) (result i32)))
 (type $i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32) (result i32)))
 (type $i32_=>_i32 (func (param i32) (result i32)))
 (type $i32_=>_none (func (param i32)))
 (type $i32_i32_i32_=>_i32 (func (param i32 i32 i32) (result i32)))
 (type $i32_i32_=>_none (func (param i32 i32)))
 (type $none_=>_i32 (func (result i32)))
 (type $i32_i32_i32_=>_none (func (param i32 i32 i32)))
 (type $i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32) (result i32)))
 (type $none_=>_none (func))
 (type $i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32 (func (param i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32 i32) (result i32)))
 (import "env" "memory" (memory $0 2 65536))
 (data (global.get $data_offset) "\0f\0f\0f\0fnot a fn\00fn_name???\00\01\00\00\00\00\00\00\00\00\00\00\00(\00\00\00\19\ff\19\00\02\00\00\00\00\00\00\00\00\00\00\00\18\00\00\00\18\00\00\00<\00\00\00\00\00\00\00<\00\00\00\00\00\00\00<\00\00\00\01\00\00\00\18\00\00\00")
 (import "env" "fn_table" (table $0 100000 1000000 funcref))
 (elem (global.get $fn_table_offset) $call#0 $call#1 $call#2 $call#3 $call#4 $call#5 $call#6 $call#7 $call#8 $call#9 $call#10 $call#11 $call#12 $call#13 $call#14 $call#15 $call#16 $call#17 $call#18 $call#19 $call#20 $validate_fn $partial $apply $copy_and_retain $main_0)
 (import "env" "__data_end" (global $__data_end i32))
 (import "env" "stack_pointer" (global $stack_pointer (mut i32)))
 (import "env" "data_offset" (global $data_offset i32))
 (import "env" "fn_table_offset" (global $fn_table_offset i32))
 (import "env" "fn:test.test-partial/test-partial_10" (global $fn:test.test-partial/test-partial_10 i32))
 (import "env" "log_int" (func $log_int (param i32)))
 (import "env" "log_string" (func $log_string (param i32)))
 (import "env" "log_string_n" (func $log_string_n (param i32 i32)))
 (import "env" "runtime_error" (func $runtime_error (param i32 i32)))
 (import "env" "lval_print" (func $lval_print (param i32)))
 (import "env" "lval_println" (func $lval_println (param i32)))
 (import "env" "printf_" (func $printf_ (param i32 i32) (result i32)))
 (import "env" "make_lval_num" (func $make_lval_num (param i32) (result i32)))
 (import "env" "make_lval_nil" (func $make_lval_nil (result i32)))
 (import "env" "make_lval_true" (func $make_lval_true (result i32)))
 (import "env" "make_lval_false" (func $make_lval_false (result i32)))
 (import "env" "make_lval_str" (func $make_lval_str (param i32) (result i32)))
 (import "env" "make_lval_list" (func $make_lval_list (result i32)))
 (import "env" "new_lval_list" (func $new_lval_list (param i32) (result i32)))
 (import "env" "make_lval_sym" (func $make_lval_sym (param i32) (result i32)))
 (import "env" "new_lval_vector" (func $new_lval_vector (param i32) (result i32)))
 (import "env" "lalloc_size" (func $lalloc_size (param i32) (result i32)))
 (import "env" "lalloc_type" (func $lalloc_type (param i32) (result i32)))
 (import "env" "retain" (func $retain (param i32) (result i32)))
 (import "env" "release" (func $release (param i32)))
 (import "env" "prefix_list" (func $prefix_list (param i32 i32) (result i32)))
 (import "env" "_strcpy" (func $_strcpy (param i32 i32) (result i32)))
 (import "env" "print_slot_size" (func $print_slot_size))
 (import "env" "wval_print" (func $wval_print (param i32)))
 (import "env" "make_lval_wasm_lambda" (func $make_lval_wasm_lambda (param i32 i32 i32 i32 i32 i32) (result i32)))
 (import "env" "get_wval_type" (func $get_wval_type (param i32) (result i32)))
 (import "env" "get_wval_subtype" (func $get_wval_subtype (param i32) (result i32)))
 (import "env" "get_wval_fn_table_index" (func $get_wval_fn_table_index (param i32) (result i32)))
 (import "env" "get_wval_param_count" (func $get_wval_param_count (param i32) (result i32)))
 (import "env" "get_wval_min_param_count" (func $get_wval_min_param_count (param i32) (result i32)))
 (import "env" "get_wval_has_rest_arg" (func $get_wval_has_rest_arg (param i32) (result i32)))
 (import "env" "get_wval_rest_arg_index" (func $get_wval_rest_arg_index (param i32) (result i32)))
 (import "env" "get_wval_closure" (func $get_wval_closure (param i32) (result i32)))
 (import "env" "get_wval_partials" (func $get_wval_partials (param i32) (result i32)))
 (import "env" "get_wval_partial_count" (func $get_wval_partial_count (param i32) (result i32)))
 (import "env" "bundle_rest_args" (func $bundle_rest_args (param i32 i32)))
 (import "env" "check_args_count" (func $check_args_count (param i32 i32 i32) (result i32)))
 (import "env" "rewrite_pointers" (func $rewrite_pointers (param i32 i32 i32)))
 (import "env" "new_cell" (func $new_cell (param i32 i32) (result i32)))
 (import "env" "dbg" (func $dbg (param i32)))
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
 (import "env" "is_nil_fn" (func $is_nil_fn (param i32 i32) (result i32)))
 (import "env" "foo_fn" (func $foo_fn (param i32 i32) (result i32)))
 (import "env" "print_fn" (func $print_fn (param i32 i32) (result i32)))
 (import "env" "pr_fn" (func $pr_fn (param i32 i32) (result i32)))
 (import "env" "debug_fn" (func $debug_fn (param i32 i32) (result i32)))
 (import "env" "boolean_fn" (func $boolean_fn (param i32 i32) (result i32)))
 (import "env" "hash_fn" (func $hash_fn (param i32 i32) (result i32)))
 (import "env" "str_fn" (func $str_fn (param i32 i32) (result i32)))
 (import "env" "read_string_fn" (func $read_string_fn (param i32 i32) (result i32)))
 (export "main" (func $main_0))
 (export "stack_pointer" (global $stack_pointer))
 (export "mem" (memory $0))
 (func $call#0 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_=>_i32)
   (local.get $0)
   (local.get $1)
  )
 )
 (func $call#1 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#2 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#3 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#4 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#5 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#6 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#7 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#8 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#9 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#10 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#11 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (i32.load offset=40 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#12 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (i32.load offset=40 align=2
    (local.get $2)
   )
   (i32.load offset=44 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#13 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (i32.load offset=40 align=2
    (local.get $2)
   )
   (i32.load offset=44 align=2
    (local.get $2)
   )
   (i32.load offset=48 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#14 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (i32.load offset=40 align=2
    (local.get $2)
   )
   (i32.load offset=44 align=2
    (local.get $2)
   )
   (i32.load offset=48 align=2
    (local.get $2)
   )
   (i32.load offset=52 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#15 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (i32.load offset=40 align=2
    (local.get $2)
   )
   (i32.load offset=44 align=2
    (local.get $2)
   )
   (i32.load offset=48 align=2
    (local.get $2)
   )
   (i32.load offset=52 align=2
    (local.get $2)
   )
   (i32.load offset=56 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#16 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (i32.load offset=40 align=2
    (local.get $2)
   )
   (i32.load offset=44 align=2
    (local.get $2)
   )
   (i32.load offset=48 align=2
    (local.get $2)
   )
   (i32.load offset=52 align=2
    (local.get $2)
   )
   (i32.load offset=56 align=2
    (local.get $2)
   )
   (i32.load offset=60 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#17 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (i32.load offset=40 align=2
    (local.get $2)
   )
   (i32.load offset=44 align=2
    (local.get $2)
   )
   (i32.load offset=48 align=2
    (local.get $2)
   )
   (i32.load offset=52 align=2
    (local.get $2)
   )
   (i32.load offset=56 align=2
    (local.get $2)
   )
   (i32.load offset=60 align=2
    (local.get $2)
   )
   (i32.load offset=64 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#18 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (i32.load offset=40 align=2
    (local.get $2)
   )
   (i32.load offset=44 align=2
    (local.get $2)
   )
   (i32.load offset=48 align=2
    (local.get $2)
   )
   (i32.load offset=52 align=2
    (local.get $2)
   )
   (i32.load offset=56 align=2
    (local.get $2)
   )
   (i32.load offset=60 align=2
    (local.get $2)
   )
   (i32.load offset=64 align=2
    (local.get $2)
   )
   (i32.load offset=68 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#19 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (i32.load offset=40 align=2
    (local.get $2)
   )
   (i32.load offset=44 align=2
    (local.get $2)
   )
   (i32.load offset=48 align=2
    (local.get $2)
   )
   (i32.load offset=52 align=2
    (local.get $2)
   )
   (i32.load offset=56 align=2
    (local.get $2)
   )
   (i32.load offset=60 align=2
    (local.get $2)
   )
   (i32.load offset=64 align=2
    (local.get $2)
   )
   (i32.load offset=68 align=2
    (local.get $2)
   )
   (i32.load offset=72 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $call#20 (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (call_indirect (type $i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_i32_=>_i32)
   (local.get $0)
   (i32.load align=2
    (local.get $2)
   )
   (i32.load offset=4 align=2
    (local.get $2)
   )
   (i32.load offset=8 align=2
    (local.get $2)
   )
   (i32.load offset=12 align=2
    (local.get $2)
   )
   (i32.load offset=16 align=2
    (local.get $2)
   )
   (i32.load offset=20 align=2
    (local.get $2)
   )
   (i32.load offset=24 align=2
    (local.get $2)
   )
   (i32.load offset=28 align=2
    (local.get $2)
   )
   (i32.load offset=32 align=2
    (local.get $2)
   )
   (i32.load offset=36 align=2
    (local.get $2)
   )
   (i32.load offset=40 align=2
    (local.get $2)
   )
   (i32.load offset=44 align=2
    (local.get $2)
   )
   (i32.load offset=48 align=2
    (local.get $2)
   )
   (i32.load offset=52 align=2
    (local.get $2)
   )
   (i32.load offset=56 align=2
    (local.get $2)
   )
   (i32.load offset=60 align=2
    (local.get $2)
   )
   (i32.load offset=64 align=2
    (local.get $2)
   )
   (i32.load offset=68 align=2
    (local.get $2)
   )
   (i32.load offset=72 align=2
    (local.get $2)
   )
   (i32.load offset=76 align=2
    (local.get $2)
   )
   (local.get $1)
  )
 )
 (func $validate_fn (param $0 i32) (param $1 i32)
  (local $2 i32)
  (if
   (i32.ne
    (call $get_wval_type
     (local.get $0)
    )
    (i32.const 25)
   )
   (call $runtime_error
    (i32.const 2)
    (i32.add
     (global.get $data_offset)
     (i32.const 4)
    )
   )
   (nop)
  )
  (if
   (call $get_wval_has_rest_arg
    (local.get $0)
   )
   (if
    (i32.lt_u
     (local.get $1)
     (call $get_wval_min_param_count
      (local.get $0)
     )
    )
    (call $runtime_error
     (i32.const 0)
     (i32.add
      (global.get $data_offset)
      (i32.const 13)
     )
    )
    (nop)
   )
   (if
    (i32.gt_u
     (local.get $1)
     (local.tee $2
      (call $get_wval_param_count
       (local.get $0)
      )
     )
    )
    (call $runtime_error
     (i32.const 1)
     (i32.add
      (global.get $data_offset)
      (i32.const 13)
     )
    )
    (if
     (i32.lt_u
      (local.get $1)
      (local.get $2)
     )
     (call $runtime_error
      (i32.const 0)
      (i32.add
       (global.get $data_offset)
       (i32.const 13)
      )
     )
     (nop)
    )
   )
  )
 )
 (func $partial (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (result i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local.set $4
   (i32.load align=2
    (local.get $2)
   )
  )
  (local.set $8
   (call $lalloc_size
    (i32.mul
     (local.tee $7
      (i32.add
       (local.tee $6
        (call $get_wval_partial_count
         (local.get $4)
        )
       )
       (local.tee $5
        (i32.sub
         (local.get $3)
         (i32.const 1)
        )
       )
      )
     )
     (i32.const 4)
    )
   )
  )
  (drop
   (call_indirect (type $i32_i32_i32_=>_i32)
    (i32.add
     (local.get $2)
     (i32.const 4)
    )
    (local.get $5)
    (call_indirect (type $i32_i32_i32_=>_i32)
     (call $get_wval_partials
      (local.get $4)
     )
     (local.get $6)
     (local.get $8)
     (i32.const 24)
    )
    (i32.const 24)
   )
  )
  (call $make_lval_wasm_lambda
   (call $get_wval_fn_table_index
    (local.get $4)
   )
   (call $get_wval_param_count
    (local.get $4)
   )
   (call $get_wval_has_rest_arg
    (local.get $4)
   )
   (call $retain
    (call $get_wval_closure
     (local.get $4)
    )
   )
   (local.get $8)
   (local.get $7)
  )
 )
 (func $apply (param $0 i32) (param $1 i32) (param $2 i32)
  (nop)
 )
 (func $copy_and_retain (param $0 i32) (param $1 i32) (param $2 i32) (result i32)
  (loop $copy_and_retain_514 (result i32)
   (if (result i32)
    (local.get $1)
    (block
     (i32.store align=2
      (local.get $2)
      (call $retain
       (i32.load align=2
        (local.get $0)
       )
      )
     )
     (local.set $1
      (i32.sub
       (local.get $1)
       (i32.const 1)
      )
     )
     (local.set $0
      (i32.add
       (local.get $0)
       (i32.const 4)
      )
     )
     (local.set $2
      (i32.add
       (local.get $2)
       (i32.const 4)
      )
     )
     (br $copy_and_retain_514)
    )
    (local.get $2)
   )
  )
 )
 (func $main_0 (param $0 i32) (param $1 i32) (param $2 i32) (result i32)
  (local $3 i32)
  (block $do_516 (result i32)
   (block $lambda_call_515 (result i32)
    (local.set $3
     (call_indirect (type $i32_=>_i32)
      (i32.const 0)
      (global.get $fn:test.test-partial/test-partial_10)
     )
    )
    (local.get $3)
   )
  )
 )
 ;; custom section "symbol_table", size 26
 ;; custom section "deps", size 37
 ;; custom section "data_size", size 2, contents: "92"
 ;; custom section "fn_table_size", size 2, contents: "26"
)
