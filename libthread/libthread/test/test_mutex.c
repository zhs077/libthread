#include "un.h"
#include <stdio.h>
int count=0;
un_mutex_t mutex;
void thread_function2(void* arg)
{
	
	char* pstr = (char*)arg;
	int r;
	Sleep(2);
	un_mutex_lock(&mutex);
	

		while(strcmp("end\n",pstr) != 0)
		{
			printf("You input %s characters\n",pstr);
			un_mutex_unlock(&mutex);
			Sleep(2);
			un_mutex_lock(&mutex);
		}
		un_mutex_unlock(&mutex);  

	
}

int test_mutex() 
{
	un_thread_t tid;
	char msg[100] = {'\0'};
	int r;
	un_mutex_init(&mutex);
	r= un_thread_create(&tid,thread_function2,(void*)msg);
	if(r)
	{
		printf("create thread error");
		return -1;
	}
	printf("Input some test. Enter 'end' to finish\n");
	un_mutex_lock(&mutex);
	while(strcmp(msg,"end\n") != 0)
	{
		fgets(msg, 100, stdin); 
		un_mutex_unlock(&mutex);
		Sleep(2);
		un_mutex_lock(&mutex);
	}
	un_mutex_unlock(&mutex);

	un_thread_join(&tid);
	un_mutex_destroy(&mutex);
}
//int main()
//{
//	
//	return test_mutex();
//
//	return 0;
//
//}