/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
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
 * SOFTWARE. 
 *
 * @file      driver_ads1110_basic.c
 * @brief     driver ads1110 basic source file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2025-08-15
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2025/08/15  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#include "driver_ads1110_basic.h"

static ads1110_handle_t gs_handle;        /**< ads1110 handle */

/**
 * @brief     basic example init
 * @param[in] addr iic device address
 * @return    status code
 *            - 0 success
 *            - 1 init failed
 * @note      none
 */
uint8_t ads1110_basic_init(ads1110_address_t addr)
{
    uint8_t res;
    
    /* link interface function */
    DRIVER_ADS1110_LINK_INIT(&gs_handle, ads1110_handle_t); 
    DRIVER_ADS1110_LINK_IIC_INIT(&gs_handle, ads1110_interface_iic_init);
    DRIVER_ADS1110_LINK_IIC_DEINIT(&gs_handle, ads1110_interface_iic_deinit);
    DRIVER_ADS1110_LINK_IIC_READ_COMMAND(&gs_handle, ads1110_interface_iic_read_cmd);
    DRIVER_ADS1110_LINK_IIC_WRITE_COMMAND(&gs_handle, ads1110_interface_write_cmd);
    DRIVER_ADS1110_LINK_DELAY_MS(&gs_handle, ads1110_interface_delay_ms);
    DRIVER_ADS1110_LINK_DEBUG_PRINT(&gs_handle, ads1110_interface_debug_print);
    
    /* set addr pin */
    res = ads1110_set_addr_pin(&gs_handle, addr);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set addr failed.\n");
        
        return 1;
    }
    
    /* ads1110 init */
    res = ads1110_init(&gs_handle);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: init failed.\n");
        
        return 1;
    }
    
    /* set default rate */
    res = ads1110_set_rate(&gs_handle, ADS1110_BASIC_DEFAULT_RATE);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set rate failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* set default gain */
    res = ads1110_set_gain(&gs_handle, ADS1110_BASIC_DEFAULT_GAIN);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set compare failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    
    /* start continuous read */
    res = ads1110_start_continuous_read(&gs_handle);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: start continuous read mode failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }

    return 0;
}

/**
 * @brief      basic example read
 * @param[out] *s pointer to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
uint8_t ads1110_basic_read(float *s)
{
    int16_t raw;
  
    /* read data */
    if (ads1110_continuous_read(&gs_handle, (int16_t *)&raw, s) != 0)
    {
        return 1;
    }
    
    return 0;
}

/**
 * @brief  basic example deinit
 * @return status code
 *         - 0 success
 *         - 1 deinit failed
 * @note   none
 */
uint8_t ads1110_basic_deinit(void)
{
    uint8_t res;
    
    /* stop continuous read */
    res = ads1110_stop_continuous_read(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    /* deinit ads1110 */
    res = ads1110_deinit(&gs_handle);
    if (res != 0)
    {
        return 1;
    }
    
    return 0;
}
