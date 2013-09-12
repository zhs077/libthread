#include "un.h"
#include <stdio.h>
int share_num=0;
un_mutex_t mutex;
un_rwlock_t rwlock;

//Ð´½ø³Ì
void writer(void* arg)
{
	
	int num = *(int *)arg;
	int i;
	for (i = 0; i < 5; i++)
	{
		//un_mutex_lock(&mutex);
		un_rwlock_wrlock(&rwlock);
		printf("Writer  %d: acquired lock\n", num);
		
		++share_num;
		printf("Writer  %d: shared num = %d\n", num, share_num);
		un_rwlock_wrunlock(&rwlock);
		//un_mutex_unlock(&mutex);
		printf("Writer  %d: released lock\n", num);

	}

}

void reader(void* arg)
{
	int num = *(int *)arg;
	int i;
	for (i = 0; i < 5; i++)
	{
		//un_mutex_lock(&mutex);
		un_rwlock_rdlock(&rwlock);
		printf("Reader %d: acquired lock\n", num);
		printf("Reader %d: shared num = %d\n", num, share_num);
		un_rwlock_rdunlock(&rwlock);
		printf("Reader %d: released lock\n", num);
		//un_mutex_unlock(&mutex);

	}
}

void test_rwlock() 
{	un_thread_t tid1,tid2,tid3;
	int numbers[]={1,2,3};

	un_mutex_init(&mutex);
	un_rwlock_init(&rwlock);
	un_thread_create(&tid1,writer,&numbers[0]);
	un_thread_create(&tid2,reader,&numbers[1]);
	un_thread_create(&tid3,writer,&numbers[2]);

	un_thread_join(&tid1);
	un_thread_join(&tid2);
	un_thread_join(&tid3);
	un_mutex_destroy(&mutex);
	un_rwlock_destroy(&rwlock);
}


//int main()
//{
//	
//	test_rwlock();
//
//	return 0;
//}