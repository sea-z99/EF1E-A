/*
 * timer.c
 *
 *  Created on: 2020-12-17
 *      Author: Rick
 */


/*
 * Copyright (c) 2016 Zibin Zheng <znbin@qq.com>
 * All rights reserved
 */

#include "timer.h"

//timer handle list head.

static struct Timer* head_handle;
//Timer ticks
static uint64_t _timer_ticks = 0;
void pointer_init(void)
{
	head_handle = 0;
}
/**
  * @brief  Initializes the timer struct handle.
  * @param  handle: the timer handle strcut.
  * @param  timeout_cb: timeout callback.
  * @param  repeat: repeat interval time.
  * @retval None
  */
void timer_init(struct Timer* handle, void(*timeout_cb)(), uint64_t timeout, uint64_t repeat)
{
	pointer_init();
	// memset(handle, sizeof(struct Timer), 0);
	handle->timeout_cb = timeout_cb;
	handle->timeout = _timer_ticks + timeout;
	handle->repeat = repeat;
}

/**
  * @brief  Start the timer work, add the handle into work list.
  * @param  btn: target handle strcut.
  * @retval 0: succeed. -1: already exist.
  */
int timer_start(struct Timer* handle)
{
	struct Timer* target = head_handle;
	while(target) {
		if(target == handle) return -1;	//already exist.
		target = target->next;
	}
	handle->next = head_handle;
	head_handle = handle;
	return 0;
}

/**
  * @brief  Stop the timer work, remove the handle off work list.
  * @param  handle: target handle strcut.
  * @retval None
  */
void timer_stop(struct Timer* handle)
{
	struct Timer** curr;
	for(curr = &head_handle; *curr; ) {
		struct Timer* entry = *curr;
		if (entry == handle) {
			*curr = entry->next;
//			free(entry);
		} else
			curr = &entry->next;
	}
}

/**
  * @brief  main loop.
  * @param  None.
  * @retval None
  */
void timer_loop()
{
	struct Timer* target;
	for(target=head_handle; target; target=target->next) {
		if(_timer_ticks >= target->timeout) {
			if(target->repeat == 0) {
				timer_stop(target);
			} else {
				target->timeout = _timer_ticks + target->repeat;
			}
			target->timeout_cb();
		}
	}
}

/**
  * @brief  background ticks, timer repeat invoking interval 1ms.
  * @param  None.
  * @retval None.
  */
void timer_ticks()
{
	_timer_ticks++;
}
