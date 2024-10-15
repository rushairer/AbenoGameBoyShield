#include "AbenoGameBoyShield.h"
#include <U8g2lib.h>

namespace AbenoGameBoyShield
{
    Shield::Shield()
    {
        oled = new U8G2_SSD1306_128X64_NONAME_F_HW_I2C(U8G2_R0);
        rgb = new Adafruit_NeoPixel(2, AGBS_RGB_PIN, NEO_GRB + NEO_KHZ800);
        rcSwitch = RCSwitch();
        _initButtons();
    }

    Shield::Shield(U8G2 *oled) : oled(oled)
    {
        _initButtons();
    }

    Shield::~Shield()
    {
    }

    void Shield::setup()
    {
        _setupButtons();
        oled->begin();

        if (rgb != nullptr)
        {
            rgb->begin();
            rgb->setBrightness(100);
        }
    }

    void Shield::loop(void (*checkButtonStatesFunc)(),
                      void (*drawPageFunc)(),
                      void (*useEffectFunc)())
    {
        _readButtons();

        if (checkButtonStatesFunc != nullptr)
        {
            checkButtonStatesFunc();
        }
        oled->firstPage();
        do
        {

            if (drawPageFunc != nullptr)
            {
                drawPageFunc();
            }

        } while (oled->nextPage());
        if (useEffectFunc != nullptr)
        {
            useEffectFunc();
        }
    }

    bool Shield::isButtonPressed(Button button)
    {
        return buttonStates[button];
    }

    void Shield::_initButtons()
    {
        buttons[Button1] = AGBS_BUTTON_1_PIN;
        buttons[Button2] = AGBS_BUTTON_2_PIN;
        buttons[Button3] = AGBS_BUTTON_3_PIN;
        buttons[Button4] = AGBS_BUTTON_4_PIN;
        buttons[ButtonUp] = AGBS_BUTTON_UP_PIN;
        buttons[ButtonLeft] = AGBS_BUTTON_LEFT_PIN;
        buttons[ButtonDown] = AGBS_BUTTON_DOWN_PIN;
        buttons[ButtonRight] = AGBS_BUTTON_RIGHT_PIN;
        buttons[ButtonCenter] = AGBS_BUTTON_CENTER_PIN;
    }

    void Shield::_setupButtons()
    {
        for (uint8_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
        {
            pinMode(buttons[i], INPUT_PULLUP);
        }
    }

    void Shield::_readButtons()
    {
        for (uint8_t i = 0; i < sizeof(buttons) / sizeof(buttons[0]); i++)
        {
            buttonStates[i] = digitalRead(buttons[i]) == LOW;
        }
    }

    void Shield::setCustomRgb(Adafruit_NeoPixel *customRgb)
    {
        rgb = customRgb;
    }

    void Shield::setCustomRCSwitch(RCSwitch *customRCSwitch)
    {
        rcSwitch = customRCSwitch;
    }

    void Shield::enableRCSwitch(int rcSwitchPin = AGBS_RCSWITCH_PIN)
    {
        if (rcSwitch != nullptr)
        {
            rcSwitch->enableTransmit(rcSwitchPin);
        }
    }
}