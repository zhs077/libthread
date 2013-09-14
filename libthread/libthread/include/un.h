#ifndef _UN_H_
#define _UN_H_
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "un_common.h"
#ifdef WIN32
#include "un-win.h"
#endif
#ifdef __cplusplus
extern "C"{
#endif

	int un_thread_create(un_thread_t* thread,void(*entery)(void*arg),void* arg);
	int un_thread_join(un_thread_t* tid);
	//����
	int un_mutex_init(un_mutex_t* mutex);
	void un_mutex_destroy(un_mutex_t* mutex);
	void un_mutex_lock(un_mutex_t* mutex);
	void un_mutex_unlock(un_mutex_t* mutex);
	int un_mutex_trylock(un_mutex_t* mutex);
	//��д��
	int un_rwlock_init(un_rwlock_t* rwlock);
	void un_rwlock_destroy(un_rwlock_t* rwlock);
	void un_rwlock_rdlock(un_rwlock_t* rwlock);
	int un_rwlock_tryrdlock(un_rwlock_t* rwlock);
	void un_rwlock_rdunlock(un_rwlock_t* rwlock);
	void un_rwlock_wrlock(un_rwlock_t* rwlock);
	int un_rwlock_trywrlock(un_rwlock_t* rwlock);
	void un_rwlock_wrunlock(un_rwlock_t* rwlock);
	//��������
	int un_cond_init(un_cond_t* cond);
	void un_cond_destroy(un_cond_t* cond);
	void un_cond_wait(un_cond_t* cond,un_mutex_t* mutex);
	void un_cond_signal(un_cond_t* cond);
	void un_cond_broadcast (un_cond_t* cond);
	//�ź���
	int un_sem_init(un_sem_t* sem, unsigned int count);
	void un_sem_destroy(un_sem_t* sem);
	void un_sem_post(un_sem_t* sem);
	void un_sem_wait(un_sem_t* sem);
	int un_sem_trywait(un_sem_t* sem);

	//����

	int un_barrier_init(un_barrier_t* barrier,unsigned int wait_count_);
	void un_barrier_destroy(un_barrier_t* barrier);
	void un_barrier_wait(un_barrier_t* barrier);

	void un_sleep(uint64_t millseconds);
	unsigned long  un_thread_self();






#ifdef __cplusplus
}
#endif
//



#endif