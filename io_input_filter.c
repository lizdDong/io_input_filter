/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-04     lizd       the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

/* Input Filter Times */
#ifndef IIF_TIMES
#define IIF_TIMES     10
#endif

/* Input Filter Period */
#ifndef IIF_PERIOD
#define IIF_PERIOD    5
#endif

#ifdef IIF_DEBUG_MODE
#ifndef IIF_DEBUG
#define IIF_DEBUG(...) rt_kprintf(__VA_ARGS__)
#endif
#else
#define IIF_DEBUG(...)
#endif

typedef struct io_input_filter
{
    uint8_t pin_id;
    uint8_t pin_status;
    uint8_t filter_counts;
    struct io_input_filter *next;
} iif_t;

static iif_t iif;
static rt_timer_t iif_timer;

static void iif_list_append(iif_t *l, iif_t *n);
static void iif_handle(void *parameter);

void iif_init(void)
{
    iif.next = NULL;

    iif_timer = rt_timer_create("iif_handle", iif_handle, RT_NULL, IIF_PERIOD,
            RT_TIMER_FLAG_PERIODIC | RT_TIMER_FLAG_SOFT_TIMER);
    rt_timer_start(iif_timer);
}

int iif_add_pin(rt_base_t pin)
{
    iif_t *iif_new;

    iif_new = rt_malloc(sizeof(iif_t));
    if (iif_new == RT_NULL)
    {
        rt_kprintf("error: iif_add_pin() failed, no free memory was found!");
        return -1;
    }

    rt_pin_mode(pin, PIN_MODE_INPUT);
    iif_new->pin_id = pin;
    iif_new->filter_counts = 0;
    iif_new->pin_status = rt_pin_read(pin);

    iif_list_append(&iif, iif_new);
    return 0;
}

int iif_read_pin(rt_base_t pin)
{
    iif_t *note = iif.next;
    while(note)
    {
        if(note->pin_id == pin)
        {
            return note->pin_status;
        }
        note = note->next;
    }
    return -1;
}

static void iif_handle(void *parameter)
{
    iif_t *note = iif.next;
    while(note)
    {
        if(rt_pin_read(note->pin_id) == PIN_LOW)
        {
            if(note->pin_status == PIN_HIGH)
            {
                if(note->filter_counts > 0)
                {
                    note->filter_counts--;
                }
                else
                {
                    note->pin_status = PIN_LOW;
                    IIF_DEBUG("pin %d changed to %d\n", note->pin_id, note->pin_status);
                }
            }
            else
            {
                note->filter_counts = 0;
            }
        }
        else
        {
            if(note->pin_status == PIN_LOW)
            {
                if(note->filter_counts < IIF_TIMES)
                {
                    note->filter_counts++;
                }
                else
                {
                    note->pin_status = PIN_HIGH;
                    IIF_DEBUG("pin %d changed to %d\n", note->pin_id, note->pin_status);
                }
            }
            else
            {
                note->filter_counts = IIF_TIMES;
            }
        }
        note = note->next;
    }
}

static void iif_list_append(iif_t *l, iif_t *n)
{
    iif_t *node = l;

    while (node->next)
    {
        node = node->next;
    }
    node->next = n;
    n->next = NULL;
}
