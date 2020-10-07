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
* \brief This file implements platform abstraction layer configurations for ifx i2c protocol.
*
* \ingroup  grPAL
* @{
*/

/**********************************************************************************************************************
 * HEADER FILES
 *********************************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>

#if defined(CONFIG_USE_OPTIGA)

#include "optiga/pal/pal_gpio.h"
#include "optiga/pal/pal_i2c.h"
#include "optiga/ifx_i2c/ifx_i2c_config.h"

#include "pal_platform.h"

#include "xmc_gpio.h"
// Uncomment the following line if Optiga Shield2Go connected to Socket2/3 of MyIoT Shield2Go Adapter
//#define OPTIGA_RESET_PIN P1_8
// Uncomment the following line if Optiga Shield2Go connected to Socket1 of MyIoT Shield2Go Adapter
#define OPTIGA_RESET_PIN P1_11

#include "Driver_I2C.h"
extern ARM_DRIVER_I2C            Driver_I2C3;

const XMC_GPIO_CONFIG_t optiga_reset_gpio_config =
{
  .mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL,
  .output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH,
  .output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM
};

static void optiga_reset_gpio_init(void)
{
  XMC_GPIO_Init(OPTIGA_RESET_PIN, &optiga_reset_gpio_config);
}

static void optiga_reset_set_high(void)
{
  XMC_GPIO_SetOutputHigh(OPTIGA_RESET_PIN);
}

static void optiga_reset_set_low(void)
{
  XMC_GPIO_SetOutputLow(OPTIGA_RESET_PIN);
}

pal_platform_gpio_t optiga_reset =
{
  .gpio_init = optiga_reset_gpio_init,
  .set_high = optiga_reset_set_high,
  .set_low = optiga_reset_set_low
};

/*********************************************************************************************************************
 * pal ifx i2c instance
 *********************************************************************************************************************/
/**
 * \brief PAL I2C configuration for OPTIGA. 
 */
pal_i2c_t optiga_pal_i2c_context_0 =
{
  /// Pointer to I2C master platform specific context
  (void*)&Driver_I2C3,
  /// Slave address
  0x30,
  /// Upper layer context
  NULL,
  /// Callback event handler
  NULL
};

/**
* \brief PAL vdd pin configuration for OPTIGA. 
 */
pal_gpio_t optiga_vdd_0 =
{
	NULL
};

/**
 * \brief PAL reset pin configuration for OPTIGA.
 */
pal_gpio_t optiga_reset_0 =
{
    &optiga_reset
};

#endif

/**
* @}
*/

