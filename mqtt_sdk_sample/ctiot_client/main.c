/************************************************************************

            (c) Copyright 2018 by 中国电信上海研究院. All rights reserved.

**************************************************************************/
#include <stdio.h>
#include "ctiot_mqtt_demo.h"
#include "ctiot_memory.h"

void main()
{
    printf("start!\n");
    ctiot_init_heap(1024, 30);
	ctiot_mqtt_demo_entry();
    ctiot_free_all_heap();
}
