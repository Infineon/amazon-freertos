/**
* MIT License
*
* Copyright (c) 2018 Infineon Technologies AG
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE
*
*
* \file
*
* \brief This file implements the platform abstraction layer APIs for os event/scheduler.
*
* \ingroup  grPAL
* @{
*/

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include "stdio.h"
#include "esp_types.h"
#include "esp_log.h"
#include "esp_timer.h"

#include "optiga/pal/pal.h"
#include "optiga/pal/pal_os_event.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/
 
/*********************************************************************************************************************
 * LOCAL DATA
 *********************************************************************************************************************/
/// @cond hidden 
static volatile register_callback callback_registered = NULL;
static void * callback_ctx = NULL;

/*
 * Timer Callback
 *
 */
void prvTimerCallback(void* arg)
{
	register_callback callback;

	if (callback_registered)
    {
        callback = callback_registered;
        callback_registered = NULL;
        callback((void*)callback_ctx);
    }
}

/*
 * Initialize selected timer of the timer group 0
 *
 * timer_idx - the timer number to initialize
 * timer_interval_sec - the interval of alarm to set
 */
static void vTimerSet(uint32_t timer_interval_usec)
{
	esp_timer_handle_t oneshot_timer;
	
	const esp_timer_create_args_t oneshot_timer_args = {
            .callback = &prvTimerCallback,
            /* argument specified here will be passed to timer callback function */
            .arg = NULL,
            .name = "one-shot"
    };

    ESP_ERROR_CHECK(esp_timer_create(&oneshot_timer_args, &oneshot_timer));
	
	ESP_ERROR_CHECK(esp_timer_start_once(oneshot_timer, (uint64_t)timer_interval_usec));
	
}


/// @endcond


/**
* Platform specific event init function.
* <br>
*
* <b>API Details:</b>
*         This function initialise all required event related variables.<br>
*
*
*/
pal_status_t pal_os_event_init(void)
{
	pal_status_t status = PAL_STATUS_FAILURE;
				
	return status;
}
/**
* Platform specific event call back registration function to trigger once when timer expires.
* <br>
*
* <b>API Details:</b>
*         This function registers the callback function supplied by the caller.<br>
*         It triggers a timer with the supplied time interval in microseconds.<br>
*         Once the timer expires, the registered callback function gets called.<br>
* 
* \param[in] callback              Callback function pointer
* \param[in] callback_args         Callback arguments
* \param[in] time_us               time in micro seconds to trigger the call back
*
*/
void pal_os_event_register_callback_oneshot(register_callback callback, 
                                            void* callback_args, 
                                            uint32_t time_us)
{
	if (time_us < 1000) {
		time_us = 1000;
	}
	
    callback_registered = callback;
    callback_ctx = callback_args;
	
	vTimerSet(time_us);
}

/**
* Platform specific task delay function.
* <br>
*
* <b>API Details:</b>
*         This function produces delay only for the. <br>
*         If you don't need this functionality just leave it empty.<br>
*         n this case a compiler should optimize this function out.<br>
* 
* \param[in] time_ms               time in milli seconds to delay
*
*/
void pal_os_event_delayms(uint32_t time_ms)
{
	const TickType_t xDelay = time_ms / portTICK_PERIOD_MS;
	vTaskDelay(xDelay);
}

/**
* @}
*/

