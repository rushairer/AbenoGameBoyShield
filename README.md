# AbenoGameBoyShield

[Abeno GameBoy Shield](https://oshwhub.com/rushairer/arduinogameboyshield) 驱动库。

## 示例

demo 目录下是一个基于本库开发的石头剪刀布游戏。

## 启动模板

```c++
#include <Arduino.h>
#include <AbenoGameBoyShield.h>

using namespace AbenoGameBoyShield;

Shield shield;

void checkButtonStates();
void drawPage();
void useEffect();

void setup()
{
    Serial.begin(115200);

    shield.setup();
    shield.oled->setFontPosTop();
    shield.oled->setFont(u8g2_font_timR08_tf);
    shield.oled->setFontMode(1);
    shield.oled->setBitmapMode(1);
    shield.oled->setFontPosTop();
    shield.oled->enableUTF8Print();
}

void loop()
{
    shield.loop(checkButtonStates, drawPage, useEffect);
}

void checkButtonStates()
{
}

void drawPage()
{
}

void useEffect()
{
}
```
