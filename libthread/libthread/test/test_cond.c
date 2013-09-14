
#include <stdio.h>
#include <assert.h>
#include "un.h"

#define  SIZE 4
un_mutex_t mutex;
un_cond_t cond_full;
un_cond_t cond_empty;
un_mutex_t mutex_full;
un_mutex_t mutex_empty;

 int buf[SIZE];//存放数据的缓冲区
 int pos = -1;


//存
void put(int data)
{
	un_mutex_lock(&mutex);
	if(pos + 1 > SIZE -1 )
		un_cond_wait(&cond_full,&mutex);
	pos++;
	buf[pos] = data;
	un_cond_signal(&cond_empty);
	 printf("Thread put a data:%d to pos%d\n",data,pos);       
	un_mutex_unlock(&mutex);
	

}

void get(int data)
{
	un_mutex_lock(&mutex);
	if(pos < 0 )
		un_cond_wait(&cond_empty,&mutex);
	  printf("Thread  get a data:%d from pos%d\n",buf[pos],pos);
		pos--;
	un_cond_signal(&cond_full);
      
	un_mutex_unlock(&mutex);


}

void putter(void* arg)
{

	int n;

	for(n=0;n<8;n++) //循环8次放数据
		put(n);

}



void getter(void* arg)

{

	int n;

	for(n=0;n<8;n++) //循环8次取数据

		get(n);

}

void testcond() 
{
	un_thread_t tid[4];
	init_winapi();
	assert(un_mutex_init(&mutex) == 0);
	assert(un_mutex_init(&mutex_full) == 0);
	assert(un_mutex_init(&mutex_empty) == 0);
	assert(un_cond_init(&cond_empty) == 0);
	assert(un_cond_init(&cond_full) == 0);

	un_thread_create(&tid[0],putter,NULL);
	un_thread_create(&tid[1],putter,NULL);
	un_thread_create(&tid[2],getter,NULL);
	un_thread_create(&tid[3],getter,NULL);

	un_thread_join(&tid[0]);
	un_thread_join(&tid[1]);
	un_thread_join(&tid[2]);
	un_thread_join(&tid[3]);
	un_mutex_destroy(&mutex);
	un_cond_destroy(&cond_empty);
	un_cond_destroy(&cond_full);
}
//int main()
// {
//	 testcond();
//
//
//
// 	
// 
// 	return 0;
// }
