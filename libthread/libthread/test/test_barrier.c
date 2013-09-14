#include "un.h"
#include <stdio.h>
#include <assert.h>
#include <windows.h>
un_barrier_t barrier;

un_thread_t tid[3];

void thread1(void* arg)
{
	int i;
	for (i = 0; i < 20; i++)
	{
		Sleep(45);
	}
	printf("%s\n","thread1 ready");
	un_barrier_wait(&barrier);
	printf("%s\n","thread1 end");
}
void thread2(void* arg)
{
	int i;
	for (i = 0; i < 20; i++)
	{
		Sleep(55);
	}
	printf("%s\n","thread2 ready");
	un_barrier_wait(&barrier);
	printf("%s\n","thread2 end");

}
void thread3(void* arg)
{
	int i;
	for (i = 0; i < 20; i++)
	{
		Sleep(65);
	}
	printf("%s\n","thread3 ready");
	un_barrier_wait(&barrier);
	printf("%s\n","thread3 end");
}

void testbarrier() 
{
	int i;
	assert (0 ==un_barrier_init(&barrier,3));
	un_thread_create(&tid[0],thread1,NULL);
	un_thread_create(&tid[1],thread2,NULL);
	un_thread_create(&tid[2],thread3,NULL);

	for (i = 0; i < 10; i++) 
	{  

		printf("timer in main thread:%d\n", i);  
		Sleep(200);  
	}  
	printf("end of main thread\n");  
	//un_barrier_wait(&barrier);
	printf("%s\n","Finish");
	un_barrier_destroy(&barrier);

}
//int main()
//{
//	testbarrier();
//
//
//	return 0;
//
//}