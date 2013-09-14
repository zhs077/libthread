
#include <stdio.h>
#include "un.h"

#define N 10	//�����������߸���
#define M 10	//������Ŀ
int in = 0;		//�����߲�Ʒ��λ��
int out = 0;	//������ȡ��Ʒ��λ��
int buffer[10]={0};
un_sem_t empty_sem;	//��ֹempty����ȡ
un_sem_t full_sem;	//��ֹfull������
un_mutex_t mutex;	//�ٽ���

int product_id = 0;
int prochase_id = 0;

//������������ģ��
void print() 
{  
	int i;  
	printf("��Ʒ����Ϊ");  
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
		printf("������%d�ڲ�Ʒ�����з����%d����Ʒ\t",id, in);
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
		 printf("������%d�Ӳ�Ʒ������ȡ����%d����Ʒ\t",id, out);  
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
	printf("�����ߺ���������Ŀ��Ϊ5,��Ʒ����Ϊ10,������ÿ2������һ����Ʒ��������ÿ5������һ����Ʒ,Ctrl+�˳�����\n");



	r = un_sem_init(&empty_sem,M);
	r = un_sem_init(&full_sem,0);
	r = un_mutex_init(&mutex);


	// ����N���������߳� 
	for ( i = 0; i < N; i++)
	{
		r = un_thread_create(&tid1[i],product,&i);

	}

	//����N���������߳�  
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
