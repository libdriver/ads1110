[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1110

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1110/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

The ADS1110 is a precision, continuously self−calibrating Analog-to-Digital (A/D) converter with differential inputs and up to 16 bits of resolution in a small SOT23-6 package. The onboard 2.048V reference provides an input range of ±2.048V differentially. The ADS1110 uses an I2C-compatible serial interface and operates from a single power supply ranging from 2.7V to 5.5V. The ADS1110 can perform conversions at rates of 15, 30, 60, or 240 samples per second. The onboard programmable gain amplifier (PGA), which offers gains of up to 8, allows smaller signals to be measured with high resolution. In single-conversion mode, the ADS1110 automatically powers down after a conversion, greatly reducing current consumption during idle periods. The ADS1110 is designed for applications requiring high-resolution measurement, where space and power consumption are major considerations. Typical applications include portable instrumentation, industrial process control, and smart transmitters.

LibDriver ADS1110 is a full-featured driver for ADS1110, launched by LibDriver. It provides continuous reading, single reading and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver ADS1110 source files.

/interface includes LibDriver ADS1110 IIC platform independent template.

/test includes LibDriver ADS1110 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver ADS1110 sample code.

/doc includes LibDriver ADS1110 offline document.

/datasheet includes ADS1110 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_ads1110_basic.h"

uint8_t res;
uint32_t i;
float s;

/* basic init */
res = ads1110_basic_init(ADS1110_ADDRESS0);
if (res != 0)
{
    ads1110_interface_debug_print("ads1110: basic init failed.\n");

    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    /* read the data */
    res = ads1110_basic_read((float *)&s);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: basic read failed.\n");
        (void)ads1110_basic_deinit();

        return 1;
    }
    ads1110_interface_debug_print("ads1110: %d/%d.\n", i + 1, 3);
    ads1110_interface_debug_print("ads1110: adc is %0.4fV.\n", s);
    ads1110_interface_delay_ms(1000);
    
    ...
}

...
    
(void)ads1110_basic_deinit();

return 0;
```

#### example shot

```C
#include "driver_ads1110_shot.h"

uint8_t res;
uint32_t i;
float s;

/* shot init */
res = ads1110_shot_init(ADS1110_ADDRESS0);
if (res != 0)
{
    ads1110_interface_debug_print("ads1110: shot init failed.\n");

    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    /* read the data */
    res = ads1110_shot_read((float *)&s);
    if (res != 0)
    {
        ads1110_interface_debug_print("ads1110: shot read failed.\n");
        (void)ads1110_shot_deinit();

        return 1;
    }
    ads1110_interface_debug_print("ads1110: %d/%d.\n", i + 1, 3);
    ads1110_interface_debug_print("ads1110: adc is %0.4fV.\n", s);
    ads1110_interface_delay_ms(1000);
    
    ...
}

...
    
(void)ads1110_shot_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/ads1110/index.html](https://www.libdriver.com/docs/ads1110/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.