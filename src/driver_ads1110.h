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
 * @file      driver_ads1110.h
 * @brief     driver ads1110 header file
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

#ifndef DRIVER_ADS1110_H
#define DRIVER_ADS1110_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup ads1110_driver ads1110 driver function
 * @brief    ads1110 driver modules
 * @{
 */

/**
 * @addtogroup ads1110_base_driver
 * @{
 */

/**
 * @brief ads1110 address enumeration definition
 */
typedef enum
{
    ADS1110_ADDRESS0 = 0x90,        /**< A2A1A0 000 */
    ADS1110_ADDRESS1 = 0x92,        /**< A2A1A0 001 */
    ADS1110_ADDRESS2 = 0x94,        /**< A2A1A0 010 */
    ADS1110_ADDRESS3 = 0x96,        /**< A2A1A0 011 */
    ADS1110_ADDRESS4 = 0x98,        /**< A2A1A0 100 */
    ADS1110_ADDRESS5 = 0x9A,        /**< A2A1A0 101 */
    ADS1110_ADDRESS6 = 0x9C,        /**< A2A1A0 110 */
    ADS1110_ADDRESS7 = 0x9E,        /**< A2A1A0 111 */
} ads1110_address_t;

/**
 * @brief ads1110 gain enumeration definition
 */
typedef enum
{
    ADS1110_GAIN_1 = 0x00,        /**< gain 1 */
    ADS1110_GAIN_2 = 0x01,        /**< gain 2 */
    ADS1110_GAIN_4 = 0x02,        /**< gain 4 */
    ADS1110_GAIN_8 = 0x03,        /**< gain 8 */
} ads1110_gain_t;

/**
 * @brief ads1110 rate enumeration definition
 */
typedef enum
{
    ADS1110_RATE_15SPS  = 0x03,        /**< 15 samples per second */
    ADS1110_RATE_30SPS  = 0x02,        /**< 30 samples per second */
    ADS1110_RATE_60SPS  = 0x01,        /**< 60 samples per second */
    ADS1110_RATE_240SPS = 0x00,        /**< 240 samples per second */
} ads1110_rate_t;

/**
 * @brief ads1110 handle structure definition
 */
typedef struct ads1110_handle_s
{
    uint8_t iic_addr;                                                          /**< iic device address */
    uint8_t (*iic_init)(void);                                                 /**< point to an iic_init function address */
    uint8_t (*iic_deinit)(void);                                               /**< point to an iic_deinit function address */
    uint8_t (*iic_read_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);         /**< point to an iic_read_cmd function address */
    uint8_t (*iic_write_cmd)(uint8_t addr, uint8_t *buf, uint16_t len);        /**< point to an iic_write_cmd function address */
    void (*delay_ms)(uint32_t ms);                                             /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);                           /**< point to a debug_print function address */
    uint8_t inited;                                                            /**< inited flag */
} ads1110_handle_t;

/**
 * @brief ads1110 information structure definition
 */
typedef struct ads1110_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} ads1110_info_t;

/**
 * @}
 */
 
/**
 * @defgroup ads1110_link_driver ads1110 link driver function
 * @brief    ads1110 link driver modules
 * @ingroup  ads1110_driver
 * @{
 */

/**
 * @brief     initialize ads1110_handle_t structure
 * @param[in] HANDLE pointer to an ads1110 handle structure
 * @param[in] STRUCTURE ads1110_handle_t
 * @note      none
 */
#define DRIVER_ADS1110_LINK_INIT(HANDLE, STRUCTURE)           memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link iic_init function
 * @param[in] HANDLE pointer to an ads1110 handle structure
 * @param[in] FUC pointer to an iic_init function address
 * @note      none
 */
#define DRIVER_ADS1110_LINK_IIC_INIT(HANDLE, FUC)            (HANDLE)->iic_init = FUC

/**
 * @brief     link iic_deinit function
 * @param[in] HANDLE pointer to an ads1110 handle structure
 * @param[in] FUC pointer to an iic_deinit function address
 * @note      none
 */
#define DRIVER_ADS1110_LINK_IIC_DEINIT(HANDLE, FUC)          (HANDLE)->iic_deinit = FUC

/**
 * @brief     link iic_read_cmd function
 * @param[in] HANDLE pointer to an ads1110 handle structure
 * @param[in] FUC pointer to an iic_read_cmd function address
 * @note      none
 */
#define DRIVER_ADS1110_LINK_IIC_READ_COMMAND(HANDLE, FUC)    (HANDLE)->iic_read_cmd = FUC

/**
 * @brief     link iic_write_cmd function
 * @param[in] HANDLE pointer to an ads1110 handle structure
 * @param[in] FUC pointer to an iic_write_cmd function address
 * @note      none
 */
#define DRIVER_ADS1110_LINK_IIC_WRITE_COMMAND(HANDLE, FUC)   (HANDLE)->iic_write_cmd = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE pointer to an ads1110 handle structure
 * @param[in] FUC pointer to a delay_ms function address
 * @note      none
 */
#define DRIVER_ADS1110_LINK_DELAY_MS(HANDLE, FUC)            (HANDLE)->delay_ms = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE pointer to an ads1110 handle structure
 * @param[in] FUC pointer to a debug_print function address
 * @note      none
 */
#define DRIVER_ADS1110_LINK_DEBUG_PRINT(HANDLE, FUC)         (HANDLE)->debug_print = FUC

/**
 * @}
 */
 
/**
 * @defgroup ads1110_base_driver ads1110 base driver function
 * @brief    ads1110 base driver modules
 * @ingroup  ads1110_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an ads1110 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ads1110_info(ads1110_info_t *info);

/**
 * @brief     set the iic address pin
 * @param[in] *handle pointer to an ads1110 handle structure
 * @param[in] addr_pin iic address pin
 * @return    status code
 *            - 0 success
 *            - 1 set addr pin failed
 *            - 2 handle is NULL
 * @note      none
 */
uint8_t ads1110_set_addr_pin(ads1110_handle_t *handle, ads1110_address_t addr_pin);

/**
 * @brief      get the iic address pin
 * @param[in]  *handle pointer to an ads1110 handle structure
 * @param[out] *addr_pin pointer to a chip iic address pin buffer
 * @return     status code
 *             - 0 success
 *             - 1 get addr pin failed
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ads1110_get_addr_pin(ads1110_handle_t *handle, ads1110_address_t *addr_pin);

/**
 * @brief     initialize the chip
 * @param[in] *handle pointer to an ads1110 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic initialization failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t ads1110_init(ads1110_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle pointer to an ads1110 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 iic deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 *            - 4 power down failed
 * @note      none
 */
uint8_t ads1110_deinit(ads1110_handle_t *handle);

/**
 * @brief      read data from the chip once
 * @param[in]  *handle pointer to an ads1110 handle structure
 * @param[out] *raw pointer to a raw adc buffer
 * @param[out] *v pointer to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 single read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1110_single_read(ads1110_handle_t *handle, int16_t *raw, float *v);

/**
 * @brief      read data from the chip continuously
 * @param[in]  *handle pointer to an ads1110 handle structure
 * @param[out] *raw pointer to a raw adc buffer
 * @param[out] *v pointer to a converted adc buffer
 * @return     status code
 *             - 0 success
 *             - 1 continuous read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       this function can be used only after run ads1110_start_continuous_read
 *             and can be stopped by ads1110_stop_continuous_read
 */
uint8_t ads1110_continuous_read(ads1110_handle_t *handle,int16_t *raw, float *v);

/**
 * @brief     start the chip reading
 * @param[in] *handle pointer to an ads1110 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 start continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1110_start_continuous_read(ads1110_handle_t *handle);

/**
 * @brief     stop the chip reading
 * @param[in] *handle pointer to an ads1110 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 stop continuous read failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1110_stop_continuous_read(ads1110_handle_t *handle);

/**
 * @brief     set the sample rate
 * @param[in] *handle pointer to an ads1110 handle structure
 * @param[in] rate adc sample rate
 * @return    status code
 *            - 0 success
 *            - 1 set rate failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1110_set_rate(ads1110_handle_t *handle, ads1110_rate_t rate);

/**
 * @brief      get the sample rate
 * @param[in]  *handle pointer to an ads1110 handle structure
 * @param[out] *rate pointer to an adc sample rate buffer
 * @return     status code
 *             - 0 success
 *             - 1 get rate failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1110_get_rate(ads1110_handle_t *handle, ads1110_rate_t *rate);

/**
 * @brief     set adc gain
 * @param[in] *handle pointer to an ads1110 handle structure
 * @param[in] gain adc gain
 * @return    status code
 *            - 0 success
 *            - 1 set gain failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1110_set_gain(ads1110_handle_t *handle, ads1110_gain_t gain);

/**
 * @brief      get adc gain
 * @param[in]  *handle pointer to an ads1110 handle structure
 * @param[out] *gain pointer to an adc gain buffer
 * @return     status code
 *             - 0 success
 *             - 1 get gain failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1110_get_gain(ads1110_handle_t *handle, ads1110_gain_t *gain);

/**
 * @}
 */

/**
 * @defgroup ads1110_extend_driver ads1110 extend driver function
 * @brief    ads1110 extend driver modules
 * @ingroup  ads1110_driver
 * @{
 */

/**
 * @brief     set the chip register
 * @param[in] *handle pointer to an ads1110 handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t ads1110_set_reg(ads1110_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @brief      get the chip register
 * @param[in]  *handle pointer to an ads1110 handle structure
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t ads1110_get_reg(ads1110_handle_t *handle, uint8_t *buf, uint16_t len);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
