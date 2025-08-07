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
 * @file      driver_ads1110_register_test.c
 * @brief     driver ads1110 register test source file
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
 
#include "driver_ads1110_register_test.h"

static ads1110_handle_t gs_handle;        /**< ads1110 handle */

/**
 * @brief     register test
 * @param[in] addr iic device address
 * @return    status code
 *            - 0 success
 *            - 1 test failed
 * @note      none
 */
uint8_t ads1110_register_test(ads1110_address_t addr)
{
    uint8_t res;
    ads1110_info_t info;
    ads1110_rate_t rate;
    ads1110_gain_t gain;
    ads1110_address_t addr_pin;

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
    
    /* start register test */
    ads1110_interface_debug_print("ads1110: start register test.\n");

    /* ads1110_set_addr_pin/ads1110_get_addr_pin test */
    ads1110_interface_debug_print("ads1110: ads1110_set_addr_pin/ads1110_get_addr_pin test.\n");
    
    /* set addr pin 0 */
    res = ads1110_set_addr_pin(&gs_handle, ADS1110_ADDRESS0);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set addr pin 0.\n");
    res = ads1110_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check addr pin %s.\n", addr_pin == ADS1110_ADDRESS0 ? "ok" : "error");
    
    /* set addr pin 1 */
    res = ads1110_set_addr_pin(&gs_handle, ADS1110_ADDRESS1);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set addr pin 1.\n");
    res = ads1110_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check addr pin %s.\n", addr_pin == ADS1110_ADDRESS1 ? "ok" : "error");
    
    /* set addr pin 2 */
    res = ads1110_set_addr_pin(&gs_handle, ADS1110_ADDRESS2);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set addr pin 2.\n");
    res = ads1110_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check addr pin %s.\n", addr_pin == ADS1110_ADDRESS2 ? "ok" : "error");
    
    /* set addr pin 3 */
    res = ads1110_set_addr_pin(&gs_handle, ADS1110_ADDRESS3);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set addr pin 3.\n");
    res = ads1110_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check addr pin %s.\n", addr_pin == ADS1110_ADDRESS3 ? "ok" : "error");
    
    /* set addr pin 4 */
    res = ads1110_set_addr_pin(&gs_handle, ADS1110_ADDRESS4);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set addr pin 4.\n");
    res = ads1110_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check addr pin %s.\n", addr_pin == ADS1110_ADDRESS4 ? "ok" : "error");
    
    /* set addr pin 5 */
    res = ads1110_set_addr_pin(&gs_handle, ADS1110_ADDRESS5);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set addr pin 5.\n");
    res = ads1110_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check addr pin %s.\n", addr_pin == ADS1110_ADDRESS5 ? "ok" : "error");
    
    /* set addr pin 6 */
    res = ads1110_set_addr_pin(&gs_handle, ADS1110_ADDRESS6);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set addr pin 6.\n");
    res = ads1110_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check addr pin %s.\n", addr_pin == ADS1110_ADDRESS6 ? "ok" : "error");
    
    /* set addr pin 7 */
    res = ads1110_set_addr_pin(&gs_handle, ADS1110_ADDRESS7);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set addr pin 7.\n");
    res = ads1110_get_addr_pin(&gs_handle, &addr_pin);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get addr pin failed.\n");
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check addr pin %s.\n", addr_pin == ADS1110_ADDRESS7 ? "ok" : "error");
    
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
    
    /* ads1110_set_rate/ads1110_get_rate test */
    ads1110_interface_debug_print("ads1110: ads1110_set_rate/ads1110_get_rate test.\n");
    
    /* set 15SPS */
    res = ads1110_set_rate(&gs_handle, ADS1110_RATE_15SPS);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set rate failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set rate 15 sps.\n");
    res = ads1110_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get rate failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check rate %s.\n", rate == ADS1110_RATE_15SPS ? "ok" : "error");
    
    /* set 30SPS */
    res = ads1110_set_rate(&gs_handle, ADS1110_RATE_30SPS);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set rate failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set rate 30 sps.\n");
    res = ads1110_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get rate failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check rate %s.\n", rate == ADS1110_RATE_30SPS ? "ok" : "error");
    
    /* set 60SPS */
    res = ads1110_set_rate(&gs_handle, ADS1110_RATE_60SPS);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set rate failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set rate 60 sps.\n");
    res = ads1110_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get rate failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check rate %s.\n", rate == ADS1110_RATE_60SPS ? "ok" : "error");
    
    /* set 240SPS */
    res = ads1110_set_rate(&gs_handle, ADS1110_RATE_240SPS);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set rate failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set rate 240 sps.\n");
    res = ads1110_get_rate(&gs_handle, &rate);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get rate failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check rate %s.\n", rate == ADS1110_RATE_240SPS ? "ok" : "error");
    
    /* ads1110_set_gain/ads1110_get_gain test */
    ads1110_interface_debug_print("ads1110: ads1110_set_gain/ads1110_get_gain test.\n");
    
    /* set gain 1 */
    res = ads1110_set_gain(&gs_handle, ADS1110_GAIN_1);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set gain failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set gain 1.\n");
    res = ads1110_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get gain failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check gain %s.\n", gain == ADS1110_GAIN_1 ? "ok" : "error");
    
    /* set gain 2 */
    res = ads1110_set_gain(&gs_handle, ADS1110_GAIN_2);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set gain failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set gain 2.\n");
    res = ads1110_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get gain failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check gain %s.\n", gain == ADS1110_GAIN_2 ? "ok" : "error");
    
    /* set gain 4 */
    res = ads1110_set_gain(&gs_handle, ADS1110_GAIN_4);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set gain failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set gain 4.\n");
    res = ads1110_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get gain failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check gain %s.\n", gain == ADS1110_GAIN_4 ? "ok" : "error");
    
    /* set gain 8 */
    res = ads1110_set_gain(&gs_handle, ADS1110_GAIN_8);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: set gain failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: set gain 8.\n");
    res = ads1110_get_gain(&gs_handle, &gain);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: get gain failed.\n");
        (void)ads1110_deinit(&gs_handle);
        
        return 1;
    }
    ads1110_interface_debug_print("ads1110: check gain %s.\n", gain == ADS1110_GAIN_8 ? "ok" : "error");
    
    /* finish register */
    ads1110_interface_debug_print("ads1110: finish register test.\n");
    (void)ads1110_deinit(&gs_handle);
    
    return 0;
}
