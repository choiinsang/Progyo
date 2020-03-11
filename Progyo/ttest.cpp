#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

pthread_cond_t g_condition;  // 조건변수는 단지 상태정보만을 알리기 위해서 사용되며, (※ 조건변수는 Lock 기능 없음.)
pthread_mutex_t g_mutex1;     // 상태정보를 원자적(atomic)으로 주고받기 위해서는 뮤텍스와 함께 사용해야 한다.
pthread_mutex_t g_mutex2;     // 상태정보를 원자적(atomic)으로 주고받기 위해서는 뮤텍스와 함께 사용해야 한다.
bool isStop  = false; 


void *ThWaitSig(void*)
{
    struct timeval now;
    struct timespec ts;

    printf("(start ThWaitSig..)\n");
    gettimeofday(&now, NULL);
    ts.tv_sec = now.tv_sec + 5;
    ts.tv_nsec = now.tv_usec * 1000;

    //usleep(1000000);
    //printf("Thread Lock\n");
    pthread_mutex_lock(&g_mutex1);
    //printf("now waiting wakeup signal about 5 sec..\n");
    pthread_cond_timedwait(&g_condition, &g_mutex1, &ts);
    //printf("ok, i'm wakeup..\n");
    pthread_mutex_unlock(&g_mutex1);
    printf("Thread1  call(1)!\n");
    pthread_mutex_lock(&g_mutex1);
    //printf("now waiting wakeup signal about 5 sec..\n");
    pthread_cond_timedwait(&g_condition, &g_mutex1, &ts);
    //printf("ok, i'm wakeup..\n");
    pthread_mutex_unlock(&g_mutex1);
    printf("Thread1  call(2)!\n");
    //isStop =true;
    //printf("isStop trun :%d\n", isStop);
    printf("Thread  - End ThWaitSig\n");
    return NULL;
}

void *ThTimer(void*){
   int i=0;
   struct timeval now;
   struct timespec ts;

   printf("(start Timer..)\n");
   gettimeofday(&now, NULL);
   ts.tv_sec = now.tv_sec + 5;
   ts.tv_nsec = now.tv_usec * 1000;

//   while(true){
//    pthread_mutex_lock(&g_mutex);
//     pthread_cond_timedwait(&g_condition, &g_mutex, &ts);
//    pthread_mutex_unlock(&g_mutex);
//     printf("[%d]| %d\n", i++, isStop);
//     if (isStop == true){
//       printf("Stop~~\n");
//       break;
//     }
//     else
//       printf("while run~~\n");
//
//     usleep(1000000);
//   }
   pthread_mutex_lock(&g_mutex2);
   pthread_cond_timedwait(&g_condition, &g_mutex2, &ts);
   pthread_mutex_unlock(&g_mutex2);
   printf("Thread2  call(1)!\n");

   pthread_mutex_lock(&g_mutex2);
   pthread_cond_timedwait(&g_condition, &g_mutex2, &ts);
   pthread_mutex_unlock(&g_mutex2);
   printf("Thread2  call(2)!\n");

   printf("Thread2  - End ThTimer\n");

   return NULL;
}


char gMessageKey[50] = "";

void Set_MessageKey(char *_pStr)
{
	char *m_p = strchr(_pStr, '.');
	bool m_IsInput = false;

	if(m_p != NULL)
	{
		m_p = strchr(m_p+1, '.');

		if(m_p != NULL)
		{
			srand(time(0));
			int m_RandNuem = rand();
			//char m_TmpStr[50];

			sprintf(gMessageKey, "%d-%s", m_RandNuem, m_p+1);
			m_IsInput = true;

			//strcpy(gMessageKey, m_p+1);
		}
	}

	if(m_IsInput == false)
	{
		srand(time(0));
		int m_RandNuem = rand();
		sprintf(gMessageKey, "%d", m_RandNuem);
	}
}

int main(int argc, char **argv)
{
//	char teststring[] = {"127.0.0.1"};
//	Set_MessageKey(teststring);
//	
//	printf("%s\n", gMessageKey);
//	return 0;
#define DEF_VAL  0
	#if DEF_VAL
	printf("#if is 1 Start\n");
	/*
	#else
	printf("#if is 0 Start\n");
	#endif
	
	#if DEF_VAL
	*/
	printf("#if is 1 End\n");
	#else
	printf("#if is 0 End\n");
	#endif
	
	
    pthread_t thread;
    pthread_t thread2;

    pthread_mutex_init(&g_mutex1, NULL);
    pthread_mutex_init(&g_mutex2, NULL);
    pthread_cond_init(&g_condition, NULL);

    pthread_create(&thread, NULL, ThWaitSig, NULL);
    printf ("TID1 : %ul\n", (int)thread);
    pthread_create(&thread2, NULL, ThTimer, NULL);
		printf ("TID2 : %ul\n", (int)thread2);

    printf("Main Lock\n");
 //   pthread_mutex_lock(&g_mutex);
    usleep(1000000);
//    printf("now send wakeup signal.. \n");
//    printf("1) now send wakeup signal.. \n");
    pthread_cond_signal(&g_condition);
//    pthread_mutex_unlock(&g_mutex);
		
		printf("1)====>\n");
		
		usleep(1000000);
//    pthread_mutex_lock(&g_mutex);
//    printf("2) now send wakeup signal.. \n");
    pthread_cond_signal(&g_condition);
    printf("2)====>\n");
//    pthread_mutex_unlock(&g_mutex);

		usleep(1000000);
    pthread_cond_signal(&g_condition);
    printf("3)====>\n");

		usleep(1000000);
    pthread_cond_signal(&g_condition);
    printf("4)====>\n");


    pthread_join(thread, NULL);
    pthread_join(thread2, NULL);
    
    printf("thread's working is done.\n");

    pthread_cond_destroy(&g_condition);
    pthread_mutex_destroy(&g_mutex1);
    pthread_mutex_destroy(&g_mutex2);
    return 0;
}


