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
 * @file      driver_ads1110_read_test.c
 * @brief     driver ads1110 read test source file
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

#include "driver_ads1110_read_test.h"

static ads1110_handle_t gs_handle;        /**< ads1110 handle */

/**
 * @brief     read test
 * @param[in] addr iic device address
 * @param[in] times test times
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ads1110_read_test(ads1110_address_t addr, uint32_t times)
{
    uint8_t res;
    uint32_t i;
    uint32_t j;
    uint32_t k;
    ads1110_info_t info;
    
    /* link interface function */
    DRIVER_ADS1110_LINK_INIT(&gs_handle, ads1110_handle_t); 
    DRIVER_ADS1110_LINK_IIC_INIT(&gs_handle, ads1110_interface_iic_init);
    DRIVER_ADS1110_LINK_IIC_DEINIT(&gs_handle, ads1110_interface_iic_deinit);
    DRIVER_ADS1110_LINK_IIC_READ_COMMAND(&gs_handle, ads1110_interface_iic_read_cmd);
    DRIVER_ADS1110_LINK_IIC_WRITE_COMMAND(&gs_handle, ads1110_interface_write_cmd);
    DRIVER_ADS1110_LINK_DELAY_MS(&gs_handle, ads1110_interface_delay_ms);
    DRIVER_ADS1110_LINK_DEBUG_PRINT(&gs_handle, ads1110_interface_debug_print);
    
    /* get information */
    res = ads1110_info(&info);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get info failed.\n");
        
        return 1;
    }
    else
    {
        /* print chip info */
        ads1110_interface_debug_print("ads1110: chip is %s.\n", info.chip_name);
        ads1110_interface_debug_print("ads1110: manufacturer is %s.\n", info.manufacturer_name);
        ads1110_interface_debug_print("ads1110: interface is %s.\n", info.interface);
        ads1110_interface_debug_print("ads1110: driver version is %d.%d.\n", info.driver_version / 1000, (info.driver_version % 1000) / 100);
        ads1110_interface_debug_print("ads1110: min supply voltage is %0.1fV.\n", info.supply_voltage_min_v);
        ads1110_interface_debug_print("ads1110: max supply voltage is %0.1fV.\n", info.supply_voltage_max_v);
        ads1110_interface_debug_print("ads1110: max current is %0.2fmA.\n", info.max_current_ma);
        ads1110_interface_debug_print("ads1110: max temperature is %0.1fC.\n", info.temperature_max);
        ads1110_interface_debug_print("ads1110: min temperature is %0.1fC.\n", info.temperature_min);
    }
    
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
    
    for (j = 0; j < 4; j++)
    {
        switch (j)
        {
            case 0 :
            {
                /* set gain 1 */
                res = ads1110_set_gain(&gs_handle, ADS1110_GAIN_1);
                if (res != 0)
                {
                    ads1110_interface_debug_print("ads1110: set gain failed.\n");
                    (void)ads1110_deinit(&gs_handle);
                    
                    return 1;
                }
                
                ads1110_interface_debug_print("ads1110: set gain 1.\n");
                
                break;
            }
            case 1 :
            {
                /* set gain 2 */
                res = ads1110_set_gain(&gs_handle, ADS1110_GAIN_2);
                if (res != 0)
                {
                    ads1110_interface_debug_print("ads1110: set gain failed.\n");
                    (void)ads1110_deinit(&gs_handle);
                    
                    return 1;
                }
                
                ads1110_interface_debug_print("ads1110: set gain 2.\n");
                
                break;
            }
            case 3 :
            {
                /* set gain 4 */
                res = ads1110_set_gain(&gs_handle, ADS1110_GAIN_4);
                if (res != 0)
                {
                    ads1110_interface_debug_print("ads1110: set gain failed.\n");
                    (void)ads1110_deinit(&gs_handle);
                    
                    return 1;
                }
                
                ads1110_interface_debug_print("ads1110: set gain 4.\n");
                
                break;
            }
            default :
            {
                /* set gain 8 */
                res = ads1110_set_gain(&gs_handle, ADS1110_GAIN_8);
                if (res != 0)
                {
                    ads1110_interface_debug_print("ads1110: set gain failed.\n");
                    (void)ads1110_deinit(&gs_handle);
                    
                    return 1;
                }
                
                ads1110_interface_debug_print("ads1110: set gain 8.\n");
                
                break;
            }
        }
        
        for (k = 0; k < 4; k++)
        {
            switch (k)
            {
                case 0 :
                {
                    /* set 15sps rate */
                    res = ads1110_set_rate(&gs_handle, ADS1110_RATE_15SPS);
                    if (res != 0)
                    {
                        ads1110_interface_debug_print("ads1110: set rate failed.\n");
                        (void)ads1110_deinit(&gs_handle);
                        
                        return 1;
                    }
                    
                    ads1110_interface_debug_print("ads1110: set 15sps rate.\n");
                    
                    break;
                }
                case 1 :
                {
                    /* set 30sps rate */
                    res = ads1110_set_rate(&gs_handle, ADS1110_RATE_30SPS);
                    if (res != 0)
                    {
                        ads1110_interface_debug_print("ads1110: set rate failed.\n");
                        (void)ads1110_deinit(&gs_handle);
                        
                        return 1;
                    }
                    
                    ads1110_interface_debug_print("ads1110: set 30sps rate.\n");
                    
                    break;
                }
                case 2 :
                {
                    /* set 60sps rate */
                    res = ads1110_set_rate(&gs_handle, ADS1110_RATE_60SPS);
                    if (res != 0)
                    {
                        ads1110_interface_debug_print("ads1110: set rate failed.\n");
                        (void)ads1110_deinit(&gs_handle);
                        
                        return 1;
                    }
                    
                    ads1110_interface_debug_print("ads1110: set 60sps rate.\n");
                    
                    break;
                }
                default :
                {
                    /* set 240sps rate */
                    res = ads1110_set_rate(&gs_handle, ADS1110_RATE_240SPS);
                    if (res != 0)
                    {
                        ads1110_interface_debug_print("ads1110: set rate failed.\n");
                        (void)ads1110_deinit(&gs_handle);
                        
                        return 1;
                    }
                    
                    ads1110_interface_debug_print("ads1110: set 240sps rate.\n");
                    
                    break;
                }
            }
            
            /* start continuous read */
            ads1110_interface_debug_print("ads1110: continuous read test.\n");
            res = ads1110_start_continuous_read(&gs_handle);
            if (res != 0)
            {
                ads1110_interface_debug_print("ads1110: start continues read mode failed.\n");
                (void)ads1110_deinit(&gs_handle);
                
                return 1;
            }
            
            /* delay 100 ms */
            ads1110_interface_delay_ms(100);
            for (i = 0; i < times; i++)
            {
                int16_t raw;
                float s;
              
                /* continuous read */
                res = ads1110_continuous_read(&gs_handle, (int16_t *)&raw, (float *)&s);
                if (res != 0)
                {
                    ads1110_interface_debug_print("ads1110: read failed.\n");
                    (void)ads1110_deinit(&gs_handle);
                    
                    return 1;
                }
                ads1110_interface_debug_print("ads1110: continues mode %0.3fV.\n", s);
                ads1110_interface_delay_ms(1000);
            }
            
            /* stop continuous read */
            res = ads1110_stop_continuous_read(&gs_handle);
            if (res != 0)
            {
                ads1110_interface_debug_print("ads1110: stop continues read mode failed.\n");
                (void)ads1110_deinit(&gs_handle);
                
                return 1;
            }
            
            /* start single read */
            ads1110_interface_debug_print("ads1110: single read test.\n");
            for (i = 0; i < times; i++)
            {
                int16_t raw;
                float s;
             
                /* single read */
                res = ads1110_single_read(&gs_handle, (int16_t *)&raw, (float *)&s);
                if (res != 0)
                {
                    ads1110_interface_debug_print("ads1110: read failed.\n");
                    (void)ads1110_deinit(&gs_handle);
                    
                    return 1;
                }
                ads1110_interface_debug_print("ads1110: single mode %0.3fV.\n", s);
                ads1110_interface_delay_ms(1000);
            }
        }
    }
    
    /* finish read test */
    ads1110_interface_debug_print("ads1110: finish read test.\n");
    (void)ads1110_deinit(&gs_handle);
    
    return 0;
}
