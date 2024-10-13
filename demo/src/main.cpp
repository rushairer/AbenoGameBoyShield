#include <Arduino.h>
#include <U8g2lib.h>
#include <AbenoGameBoyShield.h>
#include "images.h"

using namespace AbenoGameBoyShield;

Shield shield;

typedef enum
{
    ACTION_UNKNOWN = 0,
    ACTION_ROCK = 1,
    ACTION_SCISSORS = 2,
    ACTION_PAPER = 3,
} Action;

typedef enum
{
    GAME_STATE_WAITING = 0,
    GAME_STATE_COMPARE = 1,
    GAME_STATE_END = 2,
} GameState;

typedef enum
{
    RESULT_UNKNOWN = 0,
    RESULT_TIE = 1,
    RESULT_WIN = 2,
    RESULT_LOSE = 3,
} Result;

typedef enum
{
    PLAY_SOUNDS_STATE_WAITING = 0,
    PLAY_SOUNDS_STATE_END = 1,
} PlaySoundsState;

GameState gameState = GAME_STATE_WAITING;
Action opAction = ACTION_ROCK;
Action playerAction = ACTION_UNKNOWN;
PlaySoundsState playSoundsState = PLAY_SOUNDS_STATE_WAITING;
Result result = RESULT_UNKNOWN;

int opSeed = 0;
void checkButtonStates();
void drawPage();
void useEffect();
Result checkResult(Action play, Action op);

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
    if (gameState == GAME_STATE_WAITING)
    {
        if (shield.isButtonPressed(Button1))
        {
            playerAction = ACTION_ROCK;
            gameState = GAME_STATE_COMPARE;
        }
        if (shield.isButtonPressed(Button2))
        {
            playerAction = ACTION_SCISSORS;
            gameState = GAME_STATE_COMPARE;
        }
        if (shield.isButtonPressed(Button4))
        {
            playerAction = ACTION_PAPER;
            gameState = GAME_STATE_COMPARE;
        }
    }
    else if (gameState == GAME_STATE_END)
    {
        if (shield.isButtonPressed(Button3))
        {
            playerAction = ACTION_UNKNOWN;
            gameState = GAME_STATE_WAITING;
        }
    }
}

void drawPage()
{
    // background
    shield.oled->drawLine(70, 0, 58, 64);
    shield.oled->drawStr(20, 0, "Abeno");
    shield.oled->drawStr(90, 0, "You");

    switch (gameState)
    {
    case GAME_STATE_WAITING:
        if (opSeed % 3 == 0)
        {
            opAction = static_cast<Action>((opSeed / 3) % 3 + 1);
        }
        break;
    case GAME_STATE_COMPARE:
        opAction = static_cast<Action>(random(1, 4));
        gameState = GAME_STATE_END;
        playSoundsState = PLAY_SOUNDS_STATE_WAITING;
        result = RESULT_UNKNOWN;
        break;
    default:
        break;
    }

    switch (opAction)
    {
    case ACTION_ROCK:
        shield.oled->drawXBMP(10, 16, 36, 48, rock);
        break;
    case ACTION_SCISSORS:
        shield.oled->drawXBMP(10, 16, 36, 48, scissors);
        break;
    case ACTION_PAPER:
        shield.oled->drawXBMP(10, 16, 36, 48, paper);
        break;
    default:
        break;
    }

    switch (playerAction)
    {
    case ACTION_ROCK:
        shield.oled->drawXBMP(82, 16, 36, 48, rock);
        break;
    case ACTION_SCISSORS:
        shield.oled->drawXBMP(82, 16, 36, 48, scissors);
        break;
    case ACTION_PAPER:
        shield.oled->drawXBMP(82, 16, 36, 48, paper);
        break;
    default:
        shield.oled->drawXBMP(82, 16, 36, 48, unknown);
    }

    if (gameState == GAME_STATE_END)
    {
        result = checkResult(playerAction, opAction);

        shield.oled->drawRBox(30, 20, 70, 28, 4);
        shield.oled->setDrawColor(0);
        switch (result)
        {
        case RESULT_TIE:
            shield.oled->drawStrX2(50, 24, "TIE");
            shield.rgb->setPixelColor(0, shield.rgb->Color(0, 0, 255));
            shield.rgb->setPixelColor(1, shield.rgb->Color(0, 0, 255));
            shield.rgb->show();
            break;
        case RESULT_LOSE:
            shield.oled->drawStrX2(40, 24, "LOSE");
            shield.rgb->setPixelColor(0, shield.rgb->Color(0, 255, 0));
            shield.rgb->setPixelColor(1, shield.rgb->Color(0, 255, 0));
            shield.rgb->show();
            break;
        case RESULT_WIN:
            shield.oled->drawStrX2(45, 24, "WIN");
            shield.rgb->setPixelColor(0, shield.rgb->Color(255, 0, 0));
            shield.rgb->setPixelColor(1, shield.rgb->Color(255, 0, 0));
            shield.rgb->show();
            break;
        default:
            break;
        }
        shield.oled->setDrawColor(1);
    }
    else
    {
        shield.rgb->show();
        shield.rgb->clear();
    }
}

void useEffect()
{
    if (playSoundsState == PLAY_SOUNDS_STATE_WAITING)
    {
        if (result == RESULT_WIN)
        {
            tone(AGBS_BUZZER_PIN, 262, 200);
            delay(300);
            tone(AGBS_BUZZER_PIN, 294, 200);
            delay(300);
            tone(AGBS_BUZZER_PIN, 330, 200);
            delay(300);
        }

        playSoundsState = PLAY_SOUNDS_STATE_END;
    }

    opSeed++;
}

Result checkResult(Action play, Action op)
{
    if (play == op)
    {
        return RESULT_TIE;
    }

    if ((play == ACTION_PAPER && op == ACTION_ROCK) || (play == ACTION_SCISSORS && op == ACTION_PAPER) || (play == ACTION_ROCK && op == ACTION_SCISSORS))
    {
        return RESULT_WIN;
    }

    return RESULT_LOSE;
}
