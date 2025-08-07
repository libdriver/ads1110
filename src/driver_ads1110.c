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
 * @file      driver_ads1110.c
 * @brief     driver ads1110 source file
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

#include "driver_ads1110.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "Texas Instruments ADS1110"        /**< chip name */
#define MANUFACTURER_NAME         "Texas Instruments"                /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        2.7f                               /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                               /**< chip max supply voltage */
#define MAX_CURRENT               0.35f                              /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                             /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                              /**< chip max operating temperature */
#define DRIVER_VERSION            1000                               /**< driver version */

/**
 * @brief      read bytes
 * @param[in]  *handle pointer to an ads1110 handle structure
 * @param[out] *buf pointer to a data buffer
 * @param[in]  len buffer length
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 * @note       none
 */
static uint8_t a_ads1110_iic_read(ads1110_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle->iic_read_cmd(handle->iic_addr, (uint8_t *)buf, len) != 0)        /* read data */
    {
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

/**
 * @brief     write bytes
 * @param[in] *handle pointer to an ads1110 handle structure
 * @param[in] *buf pointer to a data buffer
 * @param[in] len buffer length
 * @return    status code
 *            - 0 success
 *            - 1 write failed
 * @note      none
 */
static uint8_t a_ads1110_iic_write(ads1110_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle->iic_write_cmd(handle->iic_addr, (uint8_t *)buf, len) != 0)       /* write data */
    {
        return 1;                                                                /* return error */
    }
    
    return 0;                                                                    /* success return 0 */
}

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
uint8_t ads1110_init(ads1110_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->debug_print == NULL)                                 /* check debug_print */
    {
        return 3;                                                    /* return error */
    }
    if (handle->iic_init == NULL)                                    /* check iic_init */
    {
        handle->debug_print("ads1110: iic_init is null.\n");         /* iic_init is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_deinit == NULL)                                  /* check iic_deinit */
    {
        handle->debug_print("ads1110: iic_deinit is null.\n");       /* iic_deinit is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_read_cmd == NULL)                                /* check iic_read_cmd */
    {
        handle->debug_print("ads1110: iic_read_cmd is null.\n");     /* iic_read_cmd is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->iic_write_cmd == NULL)                               /* check iic_write_cmd */
    {
        handle->debug_print("ads1110: iic_write_cmd is null.\n");    /* iic_write_cmd is null */
        
        return 3;                                                    /* return error */
    }
    if (handle->delay_ms == NULL)                                    /* check delay_ms */
    {
        handle->debug_print("ads1110: delay_ms is null.\n");         /* delay_ms is null */
        
        return 3;                                                    /* return error */
    }
    
    if (handle->iic_init() != 0)                                     /* iic init */
    {
        handle->debug_print("ads1110: iic init failed.\n");          /* iic init failed */
        
        return 1;                                                    /* return error */
    }
    
    res = a_ads1110_iic_read(handle, buf, 3);                        /* read config */
    if (res != 0)                                                    /* check the result */
    {
        handle->debug_print("ads1110: read failed.\n");              /* read failed */
        (void)handle->iic_deinit();                                  /* iic deinit */
        
        return 1;                                                    /* return error */
    }
    buf[2] &= ~(1 << 4);                                             /* clear settings */
    buf[2] |= (1 << 4);                                              /* set single conversion mode */
    res = a_ads1110_iic_write(handle, &buf[2], 1);                   /* write config */
    if (res != 0)                                                    /* check the result */
    {
        handle->debug_print("ads1110: write failed.\n");             /* write failed */
        (void)handle->iic_deinit();                                  /* iic deinit */
        
        return 1;                                                    /* return error */
    }
    handle->inited = 1;                                              /* flag inited */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t ads1110_deinit(ads1110_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                                /* check handle */
    {
        return 2;                                                      /* return error */
    }
    if (handle->inited != 1)                                           /* check handle initialization */
    {
        return 3;                                                      /* return error */
    }
    
    res = a_ads1110_iic_read(handle, buf, 3);                          /* read config */
    if (res != 0)                                                      /* check the result */
    {
        handle->debug_print("ads1110: power down failed.\n");          /* power down failed */
        
        return 4;                                                      /* return error */
    }
    buf[2] &= ~(1 << 4);                                               /* clear settings */
    buf[2] |= (1 << 4);                                                /* set single conversion mode */
    res = a_ads1110_iic_write(handle, &buf[2], 1);                     /* write config */
    if (res != 0)                                                      /* check the result */
    {
        handle->debug_print("ads1110: power down failed.\n");          /* power down failed */
        
        return 4;                                                      /* return error */
    }
    res = handle->iic_deinit();                                        /* close iic */
    if (res != 0)                                                      /* check the result */
    {
        handle->debug_print("ads1110: iic deinit failed.\n");          /* iic deinit failed */
        
        return 1;                                                      /* return error */
    }
    handle->inited = 0;                                                /* flag close */
    
    return 0;                                                          /* success return 0 */
}

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
uint8_t ads1110_set_rate(ads1110_handle_t *handle, ads1110_rate_t rate)
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_ads1110_iic_read(handle, buf, 3);                         /* read config */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("ads1110: read config failed.\n");        /* read config failed */
        
        return 1;                                                     /* return error */
    }
    buf[2] &= ~(3 << 2);                                              /* clear settings */
    buf[2] |= rate << 2;                                              /* set rate */
    res = a_ads1110_iic_write(handle, &buf[2], 1);                    /* write config */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("ads1110: write config failed.\n");       /* write config failed */
        
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return */
}

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
uint8_t ads1110_get_rate(ads1110_handle_t *handle, ads1110_rate_t *rate)
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_ads1110_iic_read(handle, buf, 3);                         /* read config */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("ads1110: read config failed.\n");        /* read config failed */
        
        return 1;                                                     /* return error */
    }
    *rate = (ads1110_rate_t)((buf[2] >> 2) & 0x03);                   /* set rate */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ads1110_set_gain(ads1110_handle_t *handle, ads1110_gain_t gain)
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_ads1110_iic_read(handle, buf, 3);                         /* read config */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("ads1110: read config failed.\n");        /* read config failed */
        
        return 1;                                                     /* return error */
    }
    buf[2] &= ~(3 << 0);                                              /* clear settings */
    buf[2] |= gain << 0;                                              /* set gain */
    res = a_ads1110_iic_write(handle, &buf[2], 1);                    /* write config */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("ads1110: write config failed.\n");       /* write config failed */
        
        return 1;                                                     /* return error */
    }
    
    return 0;                                                         /* success return */
}

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
uint8_t ads1110_get_gain(ads1110_handle_t *handle, ads1110_gain_t *gain)
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                               /* check handle */
    {
        return 2;                                                     /* return error */
    }
    if (handle->inited != 1)                                          /* check handle initialization */
    {
        return 3;                                                     /* return error */
    }
    
    res = a_ads1110_iic_read(handle, buf, 3);                         /* read config */
    if (res != 0)                                                     /* check the result */
    {
        handle->debug_print("ads1110: read config failed.\n");        /* read config failed */
        
        return 1;                                                     /* return error */
    }
    *gain = (ads1110_gain_t)((buf[2] >> 0) & 0x03);                   /* set gain */
    
    return 0;                                                         /* success return 0 */
}

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
uint8_t ads1110_set_addr_pin(ads1110_handle_t *handle, ads1110_address_t addr_pin)
{
    if (handle == NULL)                            /* check handle */
    {
        return 2;                                  /* return error */
    }
    
    handle->iic_addr = (uint8_t)(addr_pin);        /* set address pin */
    
    return 0;                                      /* success return 0 */
}

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
uint8_t ads1110_get_addr_pin(ads1110_handle_t *handle, ads1110_address_t *addr_pin)
{
    if (handle == NULL)                                       /* check handle */
    {
        return 2;                                             /* return error */
    }
    
    *addr_pin = (ads1110_address_t)(handle->iic_addr);        /* set address pin */

    return 0;                                                 /* success return 0 */
}

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
uint8_t ads1110_single_read(ads1110_handle_t *handle, int16_t *raw, float *v)
{
    uint8_t res;
    uint8_t pga;
    uint8_t rate;
    uint8_t n;
    uint8_t buf[3];
    uint16_t timeout;
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_ads1110_iic_read(handle, buf, 3);                             /* read config */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("ads1110: read config failed.\n");            /* read config failed */
        
        return 1;                                                         /* return error */
    }
    buf[2] &= ~(1 << 4);                                                  /* clear settings */
    buf[2] |= 1 << 4;                                                     /* set single config */
    buf[2] |= 1 << 7;                                                     /* set start */
    res = a_ads1110_iic_write(handle, &buf[2], 1);                        /* write config */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("ads1110: write config failed.\n");           /* write config failed */
        
        return 1;                                                         /* return error */
    }
    timeout = 5 * 1000;                                                   /* max 5 seconds */
    while (timeout != 0)                                                  /* check timeout */
    {
        handle->delay_ms(1);                                              /* wait 1 ms */
        res = a_ads1110_iic_read(handle, buf, 3);                         /* read config */
        if (res != 0)                                                     /* check the result */
        {
            handle->debug_print("ads1110: read config failed.\n");        /* read config failed */
            
            return 1;                                                     /* return error */
        }
        if ((buf[2] & (1 << 7)) == 0)                                     /* check finished */
        {
            break;                                                        /* break */
        }
        timeout--;                                                        /* timeout-- */
    }
    if (timeout == 0)                                                     /* check timeout */
    {
        handle->debug_print("ads1110: read timeout.\n");                  /* timeout */
        
        return 1;                                                         /* return error */
    }
    *raw = (int16_t)(((uint16_t)buf[0] << 8) | buf[1]);                   /* set raw */
    rate = (buf[2] >> 2) & 0x03;                                          /* set rate */
    pga = buf[2] & 0x03;                                                  /* set pga */
    if (pga == 0)                                                         /* 0 */
    {
        n = 1;                                                            /* gain 1 */
    }
    else if (pga == 1)                                                    /* 1 */
    {
        n = 2;                                                            /* gain 2 */
    }
    else if (pga == 2)                                                    /* 2 */
    {
        n = 4;                                                            /* gain 4 */
    }
    else                                                                  /* 3 */
    {
        n = 8;                                                            /* gain 8 */
    }
    if (rate == 0)                                                        /* 240 sps */
    {
        *v = (float)(*raw) / (2048.0f * (float)(n)) * 2.048f;             /* convert */
    }
    else if (rate == 1)                                                   /* 60 sps */
    {
        *v = (float)(*raw) / (8192.0f * (float)(n)) * 2.048f;             /* convert */
    }
    else if (rate == 2)                                                   /* 30 sps */
    {
        *v = (float)(*raw) / (16384.0f * (float)(n)) * 2.048f;            /* convert */
    }
    else                                                                  /* 15 sps */
    {
        *v = (float)(*raw) / (32768.0f * (float)(n)) * 2.048f;            /* convert */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ads1110_continuous_read(ads1110_handle_t *handle,int16_t *raw, float *v)
{
    uint8_t res;
    uint8_t pga;
    uint8_t rate;
    uint8_t n;
    uint8_t buf[3];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_ads1110_iic_read(handle, buf, 3);                             /* read config */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("ads1110: read config failed.\n");            /* read config failed */
        
        return 1;                                                         /* return error */
    }
    *raw = (int16_t)(((uint16_t)buf[0] << 8) | buf[1]);                   /* set raw */
    rate = (buf[2] >> 2) & 0x03;                                          /* set rate */
    pga = buf[2] & 0x03;                                                  /* set pga */
    if (pga == 0)                                                         /* 0 */
    {
        n = 1;                                                            /* gain 1 */
    }
    else if (pga == 1)                                                    /* 1 */
    {
        n = 2;                                                            /* gain 2 */
    }
    else if (pga == 2)                                                    /* 2 */
    {
        n = 4;                                                            /* gain 4 */
    }
    else                                                                  /* 3 */
    {
        n = 8;                                                            /* gain 8 */
    }
    if (rate == 0)                                                        /* 240 sps */
    {
        *v = (float)(*raw) / (2048.0f * (float)(n)) * 2.048f;             /* convert */
    }
    else if (rate == 1)                                                   /* 60 sps */
    {
        *v = (float)(*raw) / (8192.0f * (float)(n)) * 2.048f;             /* convert */
    }
    else if (rate == 2)                                                   /* 30 sps */
    {
        *v = (float)(*raw) / (16384.0f * (float)(n)) * 2.048f;            /* convert */
    }
    else                                                                  /* 15 sps */
    {
        *v = (float)(*raw) / (32768.0f * (float)(n)) * 2.048f;            /* convert */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ads1110_start_continuous_read(ads1110_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_ads1110_iic_read(handle, buf, 3);                             /* read config */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("ads1110: read config failed.\n");            /* read config failed */
        
        return 1;                                                         /* return error */
    }
    buf[2] &= ~(1 << 4);                                                  /* clear settings */
    res = a_ads1110_iic_write(handle, &buf[2], 1);                        /* write config */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("ads1110: write config failed.\n");           /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ads1110_stop_continuous_read(ads1110_handle_t *handle)
{
    uint8_t res;
    uint8_t buf[3];
    
    if (handle == NULL)                                                   /* check handle */
    {
        return 2;                                                         /* return error */
    }
    if (handle->inited != 1)                                              /* check handle initialization */
    {
        return 3;                                                         /* return error */
    }
    
    res = a_ads1110_iic_read(handle, buf, 3);                             /* read config */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("ads1110: read config failed.\n");            /* read config failed */
        
        return 1;                                                         /* return error */
    }
    buf[2] &= ~(1 << 4);                                                  /* clear settings */
    buf[2] |= 1 << 4;                                                     /* set single config */
    res = a_ads1110_iic_write(handle, &buf[2], 1);                        /* write config */
    if (res != 0)                                                         /* check the result */
    {
        handle->debug_print("ads1110: write config failed.\n");           /* write config failed */
        
        return 1;                                                         /* return error */
    }
    
    return 0;                                                             /* success return 0 */
}

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
uint8_t ads1110_set_reg(ads1110_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                 /* check handle */
    {
        return 2;                                       /* return error */
    }
    if (handle->inited != 1)                            /* check handle initialization */
    {
        return 3;                                       /* return error */
    }
    
    return a_ads1110_iic_write(handle, buf, len);       /* write reg */
}

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
uint8_t ads1110_get_reg(ads1110_handle_t *handle, uint8_t *buf, uint16_t len)
{
    if (handle == NULL)                                /* check handle */
    {
        return 2;                                      /* return error */
    }
    if (handle->inited != 1)                           /* check handle initialization */
    {
        return 3;                                      /* return error */
    }
    
    return a_ads1110_iic_read(handle, buf, len);       /* read reg */
}

/**
 * @brief      get chip's information
 * @param[out] *info pointer to an ads1110 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t ads1110_info(ads1110_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(ads1110_info_t));                        /* initialize ads1110 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "IIC", 8);                             /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
