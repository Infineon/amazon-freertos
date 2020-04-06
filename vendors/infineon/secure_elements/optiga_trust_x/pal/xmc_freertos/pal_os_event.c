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

#include <stdio.h>

#include "FreeRTOS.h"
#include "timers.h"

#include "optiga/pal/pal_os_event.h"
#include "optiga/pal/pal.h"

typedef struct event_cb
{
  register_callback callback;
  void* callback_args;
} event_cb_t;

/**********************************************************************************************************************
 * MACROS
 *********************************************************************************************************************/

/*********************************************************************************************************************
 * LOCAL DATA
 *********************************************************************************************************************/
/// @cond hidden 

static TimerHandle_t xTimer = NULL;

static void vTimerCallback(TimerHandle_t xTimer)
{
  /* Optionally do something if the pxTimer parameter is NULL. */
  configASSERT(xTimer);

  event_cb_t *event_cb = (event_cb_t *)pvTimerGetTimerID( xTimer );

  event_cb->callback(event_cb->callback_args);

  vPortFree(event_cb);
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
  return PAL_STATUS_SUCCESS;
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

  event_cb_t *event_cb = pvPortMalloc(sizeof(event_cb_t));
  if (event_cb != NULL)
  {
    event_cb->callback = callback;
    event_cb->callback_args = callback_args;

    if (xTimer != NULL)
    {
      xTimerDelete(xTimer, 0);
    }

    TickType_t ticks = ((time_us / 1000) / portTICK_PERIOD_MS);
    xTimer = xTimerCreate(NULL, (ticks > 0) ? ticks : 1, pdFALSE, event_cb, vTimerCallback);
    if (xTimer != NULL)
    {
	  xTimerStart(xTimer, 0);
    }
  }
}

/**
* @}
*/

