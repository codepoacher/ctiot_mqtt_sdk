/************************************************************************

            (c) Copyright 2018 by 中国电信上海研究院. All rights reserved.

**************************************************************************/
#include "ctiot_os.h"
#include "ctiot_log.h"

/* 包含的头文件 */
#include <stdio.h>
#include <stdlib.h>

/* 定义一个表示链表的结构体指针 */
struct list {
	int mem;			/* 内存大小 */
	void* p;		/* 指针地址 */
	struct list *next;	/* 指向下一个链表的指针 */
};
 
/* 定义一个链表头部 */
struct list list_head = {0};

int max_mem = 0;

static void list_add(struct list *list)
{
	struct list *temp;
    struct list * head = &list_head;

    if(head->next == NULL)
    {
        head->next = list;
        list->next = NULL;
    }
    else{
        temp = head->next;
        while(temp)
        {
            if(NULL == temp->next)
            {
                temp->next = list;
                list->next = NULL;
            }
            temp = temp->next;
        }
    }	
}

static int list_del(void* p){
    struct list *temp = NULL;
    struct list *pp = NULL;
    struct list * head = &list_head;
    if(head->next == NULL){
        return -1;
    }
    temp = head->next;
    if(temp->p == p){
        head->next = temp->next;
        return 0;
    }else{
        while(temp->next){
            if(temp->next->p == p){
                pp = temp->next;
                temp->next = temp->next->next;
                free(pp);
                return 0;
            }
            temp = temp->next;
        }
    }
    return -1;
}
 
static int get_count_mem()
{	
	struct list *temp;
    struct list * head = &list_head;
 
	temp = head;
    int count  = 0;
	while(temp)
	{
		count += temp->mem;
		temp = temp->next;
	}
    return count;
}

int ctiot_mem_count = 0;
int ctiot_mem_size = 0;
int ctiot_mem_get(int mem,void *p){
    struct list * list = NULL;
    list = (struct list *)malloc(sizeof(struct list));
    list->mem = mem;
    list->p = p;
    list->next = NULL;
    list_add(list);

#if defined(MEM_TEST)
    int use_mem = get_count_mem();
    if(use_mem > max_mem){
        max_mem = use_mem;
    }
    CTIOT_LOG(LOG_INFO,"use_mem: %d",use_mem);
    CTIOT_LOG(LOG_INFO,"max_mem: %d",max_mem);
#endif

    return 0;
}
int ctiot_mem_put(void *p){
    int result = list_del(p);
    if(result < 0)
    {
#if defined(MEM_TEST)
        CTIOT_LOG(LOG_WARNING,"can not free addr: %p",p);
#endif
        return result;
    }

#if defined(MEM_TEST)
    int use_mem = get_count_mem();
    if(use_mem > max_mem){
        max_mem = use_mem;
    }
    CTIOT_LOG(LOG_INFO,"use_mem: %d",use_mem);
    CTIOT_LOG(LOG_INFO,"max_mem: %d",max_mem);
#endif

    return 0;
}   

void* OS_MALLOC(int size)
{
    void* p = NULL;
    OS_GET_MEM(p,char,size);
    return p;
}

void OS_FREE(void *p)
{
    OS_PUT_MEM(p);
}
