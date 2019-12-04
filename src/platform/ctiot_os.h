/************************************************************************

            (c) Copyright 2018 by 中国电信上海研究院. All rights reserved.

**************************************************************************/

#ifndef __CTIOT_OS_H
#define __CTIOT_OS_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <semaphore.h> 
#include <pthread.h> 

typedef sem_t           T_SEM_ID;

#define OS_CREATE_THREAD(ID,ATTR,ENTRY, ARG) pthread_create(ID,ATTR,ENTRY, ARG)
#define OS_CREATE_EXIT(ARG) pthread_exit( ARG)

//#define MEM_TEST
#define OS_GET_MEM(PTR,TYPE,SIZE) {(PTR) = (void*)(long)ctiot_heap_malloc(SIZE);if(PTR != NULL){ctiot_mem_get(SIZE,PTR); /*CTIOT_LOG(LOG_INFO,"OS_GET_MEM %p,size:%u,%s,line:%u",PTR,SIZE,__FILE__,__LINE__)*/;}}
#define OS_PUT_MEM(PTR) {if(PTR != NULL){ if(!ctiot_mem_put(PTR)){ctiot_heap_free(PTR); /*CTIOT_LOG(LOG_INFO,"os_put_mem %p,%s,line:%u",PTR,__FILE__,__LINE__)*/; PTR = NULL;}else{CTIOT_LOG(LOG_WARNING,"OS_PUT_MEM ERROR, %p,%s,line:%u",PTR,__FILE__,__LINE__);}}}

#define OS_CREATE_SEMOPHORE(SEM, ARG,VAL) sem_init(SEM,ARG,VAL)
#define OS_PUT_SEMOPHORE(SEM) sem_post(SEM)
#define OS_GET_SEMOPHORE(SEM) sem_wait(SEM)
#define OS_CLOSE_SEMOPHORE(SEM) sem_destroy(SEM)

#define OS_SLEEP(MS) usleep(MS*1000)

#if defined(MEM_TEST)
int ctiot_mem_get(int mem,void *p);
int ctiot_mem_put(void *p);
#endif

void* OS_MALLOC(int size);
void OS_FREE(void *p);

#endif
