[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1110

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1110/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

ADS1110是一種精密、連續自校準模數（A/D）轉換器，在小型SOT23-6封裝中具有差分輸入和高達16比特分辯率。 晶片2.048V參攷電壓提供±2.048V的差分輸入範圍。 ADS1110使用I2C相容序列介面，並在2.7V至5.5V的單個電源下工作。 ADS1110可以每秒15、30、60或240個採樣的速率執行轉換。 晶片可程式設計增益放大器（PGA）提供高達8的增益，允許以高解析度量測較小的訊號。 在單次轉換模式下，ADS1110在轉換後自動斷電，大大降低了空閒期間的電流消耗。 ADS1110專為需要高解析度量測的應用而設計，其中空間和功耗是主要考慮因素。 典型應用包括可擕式儀錶、工業過程控制和智慧變送器。

LibDriver ADS1110是LibDriver推出的ADS1110的全功能驅動，該驅動提供連續模式模數轉換、單次模式模數轉換等功能並且它符合MISRA標準。

### 目錄

  - [說明](#說明)
  - [安裝](#安裝)
  - [使用](#使用)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [文檔](#文檔)
  - [貢獻](#貢獻)
  - [版權](#版權)
  - [聯繫我們](#聯繫我們)

### 說明

/src目錄包含了LibDriver ADS1110的源文件。

/interface目錄包含了LibDriver ADS1110與平台無關的IIC總線模板。

/test目錄包含了LibDriver ADS1110驅動測試程序，該程序可以簡單的測試芯片必要功能。

/example目錄包含了LibDriver ADS1110編程範例。

/doc目錄包含了LibDriver ADS1110離線文檔。

/datasheet目錄包含了ADS1110數據手冊。

/project目錄包含了常用Linux與單片機開發板的工程樣例。所有工程均採用shell腳本作為調試方法，詳細內容可參考每個工程裡面的README.md。

/misra目錄包含了LibDriver MISRA程式碼掃描結果。

### 安裝

參考/interface目錄下與平台無關的IIC總線模板，完成指定平台的IIC總線驅動。

將/src目錄，您使用平臺的介面驅動和您開發的驅動加入工程，如果您想要使用默認的範例驅動，可以將/example目錄加入您的工程。

### 使用

您可以參考/example目錄下的程式設計範例完成適合您的驅動，如果您想要使用默認的程式設計範例，以下是它們的使用方法。

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

### 文檔

在線文檔: [https://www.libdriver.com/docs/ads1110/index.html](https://www.libdriver.com/docs/ads1110/index.html)。

離線文檔: /doc/html/index.html。

### 貢獻

請參攷CONTRIBUTING.md。

### 版權

版權 (c) 2015 - 現在 LibDriver 版權所有

MIT 許可證（MIT）

特此免費授予任何獲得本軟件副本和相關文檔文件（下稱“軟件”）的人不受限制地處置該軟件的權利，包括不受限制地使用、複製、修改、合併、發布、分發、轉授許可和/或出售該軟件副本，以及再授權被配發了本軟件的人如上的權利，須在下列條件下：

上述版權聲明和本許可聲明應包含在該軟件的所有副本或實質成分中。

本軟件是“如此”提供的，沒有任何形式的明示或暗示的保證，包括但不限於對適銷性、特定用途的適用性和不侵權的保證。在任何情況下，作者或版權持有人都不對任何索賠、損害或其他責任負責，無論這些追責來自合同、侵權或其它行為中，還是產生於、源於或有關於本軟件以及本軟件的使用或其它處置。

### 聯繫我們

請聯繫lishifenging@outlook.com。