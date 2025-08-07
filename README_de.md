[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver ADS1110

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ads1110/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der ADS1110 ist ein präziser, kontinuierlich selbstkalibrierender Analog-Digital-Wandler (A/D) mit Differenzeingängen und bis zu 16 Bit Auflösung in einem kleinen SOT23-6-Gehäuse. Die integrierte 2,048-V-Referenz bietet einen Eingangsbereich von ±2,048 V differentiell. Der ADS1110 verwendet eine I2C-kompatible serielle Schnittstelle und wird mit einer einzelnen Stromversorgung von 2,7 V bis 5,5 V betrieben. Der ADS1110 kann Wandlungen mit Raten von 15, 30, 60 oder 240 Samples pro Sekunde durchführen. Der integrierte programmierbare Verstärkungsverstärker (PGA), der Verstärkungen von bis zu 8 bietet, ermöglicht die Messung kleinerer Signale mit hoher Auflösung. Im Einzelwandlungsmodus schaltet sich der ADS1110 nach einer Wandlung automatisch ab, wodurch der Stromverbrauch während Leerlaufzeiten erheblich reduziert wird. Der ADS1110 ist für Anwendungen konzipiert, die hochauflösende Messungen erfordern und bei denen Platz und Stromverbrauch wichtige Faktoren sind. Typische Anwendungen sind tragbare Instrumente, industrielle Prozesssteuerung und intelligente Sender.

LibDriver ADS1110 ist ein voll funktionsfähiger Treiber für ADS1110, der von LibDriver eingeführt wurde. LibDriver ADS1110 bietet kontinuierliche A/D-Konvertierung, Singlemode-A/D-Konvertierung und weitere Funktionen. LibDriver ist MISRA-konform.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
    - [example shot](#example-shot)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver ADS1110-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver ADS1110 IIC.

/test enthält den Testcode des LibDriver ADS1110-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver ADS1110-Beispielcode.

/doc enthält das LibDriver ADS1110-Offlinedokument.

/Datenblatt enthält ADS1110-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/ads1110/index.html](https://www.libdriver.com/docs/ads1110/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.