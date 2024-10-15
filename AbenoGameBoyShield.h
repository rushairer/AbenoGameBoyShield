#ifndef __ABENO_GAME_BOY_SHIELD_H__
#define __ABENO_GAME_BOY_SHIELD_H__
#include <U8g2lib.h>
#include <Adafruit_NeoPixel.h>
#include <RCSwitch.h>

#define AGBS_BUTTON_1_PIN 4
#define AGBS_BUTTON_2_PIN 5
#define AGBS_BUTTON_3_PIN 6
#define AGBS_BUTTON_4_PIN 7
#define AGBS_BUTTON_UP_PIN A0
#define AGBS_BUTTON_LEFT_PIN A1
#define AGBS_BUTTON_DOWN_PIN A2
#define AGBS_BUTTON_RIGHT_PIN A3
#define AGBS_BUTTON_CENTER_PIN 3
#define AGBS_RGB_PIN 9
#define AGBS_BUZZER_PIN 11
#define AGBS_RCSWITCH_PIN 12

namespace AbenoGameBoyShield
{
    typedef enum
    {
        Button1,
        Button2,
        Button3,
        Button4,
        ButtonUp,
        ButtonLeft,
        ButtonDown,
        ButtonRight,
        ButtonCenter
    } Button;

    class Shield
    {
    public:
        Shield();
        Shield(U8G2 *oled);

        virtual ~Shield();

        void setup();
        void loop(
            void (*checkButtonStatesFunc)(),
            void (*drawPageFunc)(),
            void (*useEffectFunc)());

        uint8_t buttons[9];
        bool buttonStates[9];
        bool isButtonPressed(Button button);

        U8G2 *oled;

        Adafruit_NeoPixel *rgb;
        void setCustomRgb(Adafruit_NeoPixel *rgb);

        RCSwitch *rcSwitch;
        void setCustomRCSwitch(RCSwitch *rcSwitch);
        void enableRCSwitch(int rcSwitchPin);

    private:
        void _initButtons();
        void _setupButtons();
        void _readButtons();
    };
}

#endif // !__ABENO_GAME_BOY_SHIELD_H__