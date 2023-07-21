/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-05     lizd       the first version
 */

#include <rtthread.h>
#include "io_input_filter.h"


#define IO_IN1  GET_PIN(D, 11)
#define IO_IN2  GET_PIN(D, 12)
#define IO_IN3  GET_PIN(D, 13)
#define IO_IN4  GET_PIN(D, 14)

int iif_example(void)
{
    iif_init();

    iif_add_pin(IO_IN1);
    iif_add_pin(IO_IN2);
    iif_add_pin(IO_IN3);
    iif_add_pin(IO_IN4);

    while (1)
    {
        if(iif_read_pin(IO_IN1) == PIN_HIGH)
            rt_kprintf("IO_IN1 Changed to HIGH\n");
        else
            rt_kprintf("IO_IN1 Changed to LOW\n");

        if(iif_read_pin(IO_IN2) == PIN_HIGH)
            rt_kprintf("IO_IN2 Changed to HIGH\n");
        else
            rt_kprintf("IO_IN2 Changed to LOW\n");

        if(iif_read_pin(IO_IN3) == PIN_HIGH)
            rt_kprintf("IO_IN3 Changed to HIGH\n");
        else
            rt_kprintf("IO_IN3 Changed to LOW\n");

        if(iif_read_pin(IO_IN4) == PIN_HIGH)
            rt_kprintf("IO_IN4 Changed to HIGH\n");
        else
            rt_kprintf("IO_IN4 Changed to LOW\n");

        rt_thread_mdelay(100);
    }

    return RT_EOK;
}
