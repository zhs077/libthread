#include "un.h"
#include <stdio.h>
void thread_function(void* arg)
{
	int *count = (int*)arg;
	printf("child thread running: %d\n",*count);
	


}

void test_thread() 
{
	un_thread_t tid1;
	un_thread_t tid2;
	un_thread_t tid3;
	un_thread_t tid4;
	int count = 100;
	un_thread_create(&tid1,thread_function,&count);
	un_thread_create(&tid2,thread_function,&count);
	un_thread_create(&tid3,thread_function,&count);
	un_thread_create(&tid4,thread_function,&count);
	Sleep(100);
	printf("main thread running\n");

	un_thread_join(&tid1);
	un_thread_join(&tid2);
	un_thread_join(&tid3);
	un_thread_join(&tid4);
}
//int main()
//{
//	test_thread();
//
//
//	return 0;
//
//}