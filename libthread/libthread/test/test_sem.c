
#include <stdio.h>
#include "un.h"

#define N 10	//生产者消费者个数
#define M 10	//缓冲数目
int in = 0;		//生产者产品的位置
int out = 0;	//消费者取产品的位置
int buffer[10]={0};
un_sem_t empty_sem;	//阻止empty继续取
un_sem_t full_sem;	//阻止full继续放
un_mutex_t mutex;	//临界区

int product_id = 0;
int prochase_id = 0;

//生成者消费者模型
void print() 
{  
	int i;  
	printf("产品队列为");  
	for(i = 0; i < M; i++)  
		printf("%d", buffer[i]);  
	printf("\n");  
}  
void product(void* arg)
{
	int id = ++ product_id;
	while(1)
	{
		Sleep(5000);
		un_sem_wait(&empty_sem);
		un_mutex_lock(&mutex);
		in = in % M;
		printf("生产者%d在产品队列中放入第%d个产品\t",id, in);
		buffer[in] =1 ;
		print();
		in++;
		un_mutex_unlock(&mutex);
		un_sem_post(&full_sem);


	}

}
void prochase(void* arg)
{
	int id = ++prochase_id;
	while(1)
	{
		Sleep(1000);
		un_sem_wait(&full_sem);
		un_mutex_lock(&mutex);
		out = out % M;
		 printf("消费者%d从产品队列中取出第%d个产品\t",id, out);  
		 buffer[out] = 0;
		 print();
		 ++out;
		un_mutex_unlock(&mutex);
		un_sem_post(&empty_sem);
	}

}

void testSem() 
{
	un_thread_t tid1[N];
	un_thread_t tid2[N];
	int i;
	int r;
	printf("生产者和消费者数目都为5,产品缓冲为10,生产者每2秒生产一个产品，消费者每5秒消费一个产品,Ctrl+退出程序\n");



	r = un_sem_init(&empty_sem,M);
	r = un_sem_init(&full_sem,0);
	r = un_mutex_init(&mutex);


	// 创建N个生产者线程 
	for ( i = 0; i < N; i++)
	{
		r = un_thread_create(&tid1[i],product,&i);

	}

	//创建N个消费者线程  
	for(i = 0; i < N; i++) 
	{  
		r = un_thread_create(&tid2[i],  prochase,NULL);  

	}  

	for(i = 0; i < N; i++) 
	{  
		un_thread_join(&tid1[i]);  
		un_thread_join(&tid2[i]);  
	}  
	un_mutex_destroy(&mutex);
	un_sem_destroy(&full_sem);
	un_sem_destroy(&empty_sem);
}
//int main()
//{
//
//	testSem();
//
//	return 0;
//}
