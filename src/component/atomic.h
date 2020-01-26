#ifndef _ATOMIC_H_
#define _ATOMIC_H_

typedef volatile long atomic_t;
typedef volatile long long atomic64_t;



# define ATOMIC_INC(var) 		__sync_add_and_fetch (&var, 1)
# define ATOMIC_DEC(var) 		__sync_sub_and_fetch(&var,-1)
# define ATOMIC_ASSIGN(tar,val) __sync_lock_test_and_set(&tar,val)
# define ATOMIC_ADD(tar,val)	__sync_add_and_fetch (&tar, val)
# define ATOMIC_SUB(tar,val)	__sync_sub_and_fetch(&tar,val)

  
# define ATOMIC64_INC(var)			__sync_add_and_fetch (&var, 1)
# define ATOMIC64_DEC(var) 			__sync_sub_and_fetch(&var,-1)
# define ATOMIC64_ASSIGN(tar,val)	__sync_lock_test_and_set(&tar,val)
# define ATOMIC64_ADD(tar,val)		__sync_add_and_fetch (&tar, val)
# define ATOMIC64_SUB(tar,val)		__sync_sub_and_fetch(&tar,val)



#endif //_ATOMIC_H_