[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1110

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1110/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ADS1110是一种精密、连续自校准模数（A/D）转换器，在小型SOT23-6封装中具有差分输入和高达16位分辨率。芯片2.048V参考电压提供±2.048V的差分输入范围。ADS1110使用I2C兼容串行接口，并在2.7V至5.5V的单个电源下工作。ADS1110可以每秒15、30、60或240个采样的速率执行转换。芯片可编程增益放大器（PGA）提供高达8的增益，允许以高分辨率测量较小的信号。在单次转换模式下，ADS1110在转换后自动断电，大大降低了空闲期间的电流消耗。ADS1110专为需要高分辨率测量的应用而设计，其中空间和功耗是主要考虑因素。典型应用包括便携式仪表、工业过程控制和智能变送器。

LibDriver ADS1110是LibDriver推出的ADS1110的全功能驱动，该驱动提供连续模式模数转换、单次模式模数转换等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver ADS1110的源文件。

/interface目录包含了LibDriver ADS1110与平台无关的IIC总线模板。

/test目录包含了LibDriver ADS1110驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver ADS1110编程范例。

/doc目录包含了LibDriver ADS1110离线文档。

/datasheet目录包含了ADS1110数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的IIC总线模板，完成指定平台的IIC总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

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

### 文档

在线文档: [https://www.libdriver.com/docs/ads1110/index.html](https://www.libdriver.com/docs/ads1110/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。