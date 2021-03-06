/**********************************************************************

  debug_counter.h -

  created at: Tue Feb 21 16:51:18 2017

  Copyright (C) 2017 Koichi Sasada

**********************************************************************/

#ifndef USE_DEBUG_COUNTER
#define USE_DEBUG_COUNTER 0
#endif

#ifdef RB_DEBUG_COUNTER

/*
 * method cache (mc) counts.
 *
 * * mc_inline_hit/miss: inline mc hit/miss counts (VM send insn)
 * * mc_global_hit/miss: global method cache hit/miss counts
 *                       two types: (1) inline cache miss (VM send insn)
 *                                  (2) called from C (rb_funcall).
 * * mc_global_state_miss: inline mc miss by global_state miss.
 * * mc_class_serial_miss:            ... by mc_class_serial_miss
 * * mc_cme_complement: cme complement counts.
 * * mc_cme_complement_hit: cme cache hit counts.
 * * mc_search_super: search_method() call counts.
 */
RB_DEBUG_COUNTER(mc_inline_hit)
RB_DEBUG_COUNTER(mc_inline_miss)
RB_DEBUG_COUNTER(mc_global_hit)
RB_DEBUG_COUNTER(mc_global_miss)
RB_DEBUG_COUNTER(mc_global_state_miss)
RB_DEBUG_COUNTER(mc_class_serial_miss)
RB_DEBUG_COUNTER(mc_cme_complement)
RB_DEBUG_COUNTER(mc_cme_complement_hit)
RB_DEBUG_COUNTER(mc_search_super)

/* instance variable counts
 *
 * * ivar_get_ic_hit/miss: ivar_get inline cache (ic) hit/miss counts (VM insn)
 * * ivar_get_ic_miss_serial: ivar_get ic miss reason by serial (VM insn)
 * * ivar_get_ic_miss_unset:                      ... by unset (VM insn)
 * * ivar_get_ic_miss_noobject:                   ... by "not T_OBJECT" (VM insn)
 * * ivar_set_...: same counts with ivar_set (VM insn)
 * * ivar_get/set_base: call counts of "rb_ivar_get/set()".
 *                      because of (1) ic miss.
 *                                 (2) direct call by C extensions.
 */
RB_DEBUG_COUNTER(ivar_get_ic_hit)
RB_DEBUG_COUNTER(ivar_get_ic_miss)
RB_DEBUG_COUNTER(ivar_get_ic_miss_serial)
RB_DEBUG_COUNTER(ivar_get_ic_miss_unset)
RB_DEBUG_COUNTER(ivar_get_ic_miss_noobject)
RB_DEBUG_COUNTER(ivar_set_ic_hit)
RB_DEBUG_COUNTER(ivar_set_ic_miss)
RB_DEBUG_COUNTER(ivar_set_ic_miss_serial)
RB_DEBUG_COUNTER(ivar_set_ic_miss_unset)
RB_DEBUG_COUNTER(ivar_set_ic_miss_oorange)
RB_DEBUG_COUNTER(ivar_set_ic_miss_noobject)
RB_DEBUG_COUNTER(ivar_get_base)
RB_DEBUG_COUNTER(ivar_set_base)

/* local variable counts
 *
 * * lvar_get: total lvar get counts (VM insn)
 * * lvar_get_dynamic: lvar get counts if accessing upper env (VM insn)
 * * lvar_set*: same as "get"
 * * lvar_set_slowpath: counts using vm_env_write_slowpath()
 */
RB_DEBUG_COUNTER(lvar_get)
RB_DEBUG_COUNTER(lvar_get_dynamic)
RB_DEBUG_COUNTER(lvar_set)
RB_DEBUG_COUNTER(lvar_set_dynamic)
RB_DEBUG_COUNTER(lvar_set_slowpath)

/* object allocation counts:
 *
 * * obj_newobj: newobj counts
 * * obj_newobj_slowpath: newobj with slowpath counts
 * * obj_newobj_wb_unprotected: newobj for wb_unprotecte.
 * * obj_free: obj_free() counts
 * * obj_promote: promoted counts (oldgen)
 * * obj_wb_unprotect: wb unprotect counts
 *
 * * obj_[type]_[attr]: free'ed counts for each type.
 * * [type]
 *   * _obj: T_OBJECT
 *   * _str: T_STRING
 *   * _ary: T_ARRAY
 *   * _hash: T_HASH
 *   * _struct: T_STRUCT
 *
 * * [attr]
 *   * _ptr: R?? is not embed.
 *   * _embed: R?? is embed.
 * * type specific attr.
 *   * str_shared: str is shared.
 *   * str_nofree:        nofree
 *   * str_fstr:          fstr
 *   * hash_empty: hash is empty
 *   * hash_under4:     has under 4 entries
 *   * hash_ge4:        has n entries (4<=n<8)
 *   * hash_ge8:        has n entries (8<=n)
 */
RB_DEBUG_COUNTER(obj_newobj)
RB_DEBUG_COUNTER(obj_newobj_slowpath)
RB_DEBUG_COUNTER(obj_newobj_wb_unprotected)
RB_DEBUG_COUNTER(obj_free)
RB_DEBUG_COUNTER(obj_promote)
RB_DEBUG_COUNTER(obj_wb_unprotect)

RB_DEBUG_COUNTER(obj_obj_ptr)
RB_DEBUG_COUNTER(obj_obj_embed)

RB_DEBUG_COUNTER(obj_str_ptr)
RB_DEBUG_COUNTER(obj_str_embed)
RB_DEBUG_COUNTER(obj_str_shared)
RB_DEBUG_COUNTER(obj_str_nofree)
RB_DEBUG_COUNTER(obj_str_fstr)

RB_DEBUG_COUNTER(obj_ary_ptr)
RB_DEBUG_COUNTER(obj_ary_embed)

RB_DEBUG_COUNTER(obj_hash_empty)
RB_DEBUG_COUNTER(obj_hash_under4)
RB_DEBUG_COUNTER(obj_hash_ge4)
RB_DEBUG_COUNTER(obj_hash_ge8)

RB_DEBUG_COUNTER(obj_struct_ptr)
RB_DEBUG_COUNTER(obj_struct_embed)

/* heap function counts
 *
 * * heap_xmalloc/realloc/xfree: call counts
 */
RB_DEBUG_COUNTER(heap_xmalloc)
RB_DEBUG_COUNTER(heap_xrealloc)
RB_DEBUG_COUNTER(heap_xfree)

/* load (not implemented yet) */
/*
RB_DEBUG_COUNTER(load_files)
RB_DEBUG_COUNTER(load_path_is_not_realpath)
*/
#endif

#ifndef RUBY_DEBUG_COUNTER_H
#define RUBY_DEBUG_COUNTER_H 1

#if !defined(__GNUC__) && USE_DEBUG_COUNTER
#error "USE_DEBUG_COUNTER is not supported by other than __GNUC__"
#endif

enum rb_debug_counter_type {
#define RB_DEBUG_COUNTER(name) RB_DEBUG_COUNTER_##name,
#include __FILE__
    RB_DEBUG_COUNTER_MAX
#undef RB_DEBUG_COUNTER
};

#if USE_DEBUG_COUNTER
#include "ruby/ruby.h"

extern size_t rb_debug_counter[];

inline static int
rb_debug_counter_add(enum rb_debug_counter_type type, int add, int cond)
{
    if (cond) {
	rb_debug_counter[(int)type] += add;
    }
    return cond;
}

#define RB_DEBUG_COUNTER_INC(type)                rb_debug_counter_add(RB_DEBUG_COUNTER_##type, 1, 1)
#define RB_DEBUG_COUNTER_INC_UNLESS(type, cond) (!rb_debug_counter_add(RB_DEBUG_COUNTER_##type, 1, !(cond)))
#define RB_DEBUG_COUNTER_INC_IF(type, cond)       rb_debug_counter_add(RB_DEBUG_COUNTER_##type, 1, (cond))

#else
#define RB_DEBUG_COUNTER_INC(type)              ((void)0)
#define RB_DEBUG_COUNTER_INC_UNLESS(type, cond) (cond)
#define RB_DEBUG_COUNTER_INC_IF(type, cond)     (cond)
#endif

void rb_debug_counter_show_results(const char *msg);

#endif /* RUBY_DEBUG_COUNTER_H */
