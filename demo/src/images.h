#include <Arduino.h>
#include <U8g2lib.h>

static const unsigned char rock[] U8X8_PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x80, 0x07, 0x00, 0x00, 0x00,
    0xc0, 0xcf, 0x03, 0x00, 0x00,
    0x60, 0x38, 0xe6, 0x00, 0x00,
    0x20, 0x10, 0x34, 0x01, 0x00,
    0x20, 0x10, 0x08, 0x72, 0x00,
    0x20, 0x10, 0x08, 0x8e, 0x01,
    0x20, 0x10, 0x08, 0x04, 0x01,
    0x20, 0x10, 0x08, 0x04, 0x01,
    0x20, 0x10, 0x08, 0x04, 0x01,
    0x20, 0x10, 0x08, 0x04, 0x01,
    0xe0, 0xff, 0x1f, 0x04, 0x01,
    0xf0, 0xff, 0x7f, 0x04, 0x01,
    0x18, 0x00, 0x80, 0x04, 0x01,
    0x08, 0x00, 0x80, 0x06, 0x01,
    0x08, 0x00, 0x80, 0x06, 0x01,
    0x08, 0xf0, 0xff, 0x07, 0x01,
    0x08, 0x10, 0xe0, 0x8c, 0x01,
    0x08, 0x10, 0x00, 0x70, 0x01,
    0x08, 0xf0, 0x00, 0x00, 0x01,
    0x08, 0x00, 0x03, 0x00, 0x01,
    0x08, 0x00, 0x06, 0x00, 0x01,
    0x08, 0x00, 0x0c, 0x00, 0x01,
    0x08, 0x00, 0x18, 0x00, 0x01,
    0x08, 0x00, 0x10, 0x00, 0x01,
    0x08, 0x00, 0x10, 0x00, 0x01,
    0x18, 0x00, 0x10, 0x80, 0x00,
    0x30, 0x00, 0x10, 0x80, 0x00,
    0xe0, 0x00, 0x00, 0x40, 0x00,
    0x00, 0x01, 0x00, 0x60, 0x00,
    0x00, 0x03, 0x00, 0x20, 0x00,
    0x00, 0x06, 0x00, 0x18, 0x00,
    0x00, 0x0c, 0x00, 0x0c, 0x00,
    0x00, 0x30, 0x00, 0x03, 0x00,
    0x00, 0xc0, 0xe3, 0x00, 0x00,
    0x00, 0x00, 0x1e, 0x00, 0x00};

static const unsigned char scissors[] U8X8_PROGMEM = {
    0xf8, 0x00, 0x1f, 0x00, 0x00,
    0x8c, 0x81, 0x21, 0x00, 0x00,
    0x04, 0x81, 0x20, 0x00, 0x00,
    0x04, 0x81, 0x40, 0x00, 0x00,
    0x04, 0x83, 0x40, 0x00, 0x00,
    0x04, 0x82, 0x20, 0x00, 0x00,
    0x04, 0x42, 0x20, 0x00, 0x00,
    0x04, 0x42, 0x20, 0x00, 0x00,
    0x04, 0x42, 0x20, 0x00, 0x00,
    0x04, 0x42, 0x30, 0x00, 0x00,
    0x0c, 0x42, 0x10, 0x00, 0x00,
    0x0c, 0x26, 0x10, 0x00, 0x00,
    0x0c, 0x26, 0x10, 0x00, 0x00,
    0x0c, 0x26, 0x10, 0x00, 0x00,
    0x08, 0x26, 0x08, 0x00, 0x00,
    0x08, 0x36, 0xf8, 0x00, 0x00,
    0x08, 0x14, 0x98, 0x01, 0x00,
    0x08, 0x14, 0x08, 0x79, 0x00,
    0x08, 0x14, 0x08, 0xc6, 0x00,
    0x08, 0x14, 0x04, 0x82, 0x00,
    0x18, 0x1c, 0x04, 0x82, 0x01,
    0x10, 0x0c, 0x04, 0x02, 0x01,
    0x10, 0x08, 0x04, 0x02, 0x01,
    0xf0, 0xff, 0x1f, 0x02, 0x01,
    0xf8, 0xff, 0x7f, 0x02, 0x01,
    0x08, 0x00, 0xc0, 0x02, 0x01,
    0x0c, 0x00, 0x80, 0x02, 0x01,
    0x0c, 0x00, 0xc0, 0x03, 0x01,
    0x0c, 0xf8, 0xff, 0x83, 0x01,
    0x0c, 0x18, 0x60, 0xc4, 0x01,
    0x0c, 0x18, 0x00, 0xf8, 0x01,
    0x0c, 0xf0, 0x00, 0x00, 0x01,
    0x0c, 0x80, 0x01, 0x00, 0x01,
    0x0c, 0x00, 0x02, 0x00, 0x01,
    0x0c, 0x00, 0x04, 0x80, 0x01,
    0x0c, 0x00, 0x08, 0x80, 0x00,
    0x04, 0x00, 0x08, 0x80, 0x00,
    0x0c, 0x00, 0x08, 0x80, 0x00,
    0x08, 0x00, 0x08, 0xc0, 0x00,
    0x18, 0x00, 0x08, 0xc0, 0x00,
    0xe0, 0x00, 0x00, 0x60, 0x00,
    0x80, 0x01, 0x00, 0x20, 0x00,
    0x00, 0x01, 0x00, 0x10, 0x00,
    0x00, 0x03, 0x00, 0x08, 0x00,
    0x00, 0x0c, 0x00, 0x06, 0x00,
    0x00, 0x38, 0x80, 0x03, 0x00,
    0x00, 0xe0, 0xf1, 0x00, 0x00,
    0x00, 0x00, 0x1e, 0x00, 0x00};

static const unsigned char paper[] U8X8_PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x0f, 0x00, 0x00,
    0x00, 0x80, 0x10, 0x00, 0x00,
    0x00, 0x80, 0x10, 0x00, 0x00,
    0x00, 0x80, 0xa0, 0x07, 0x00,
    0x00, 0x80, 0xa0, 0x08, 0x00,
    0x00, 0x80, 0x60, 0x08, 0x00,
    0x00, 0x9c, 0x60, 0x08, 0x00,
    0x00, 0xa2, 0x60, 0x08, 0x00,
    0x00, 0xa2, 0x60, 0x08, 0x00,
    0x00, 0xa1, 0x60, 0x08, 0x00,
    0x00, 0xa1, 0x60, 0xc8, 0x00,
    0x00, 0xa1, 0x60, 0x28, 0x01,
    0x00, 0xa1, 0x60, 0x28, 0x02,
    0x00, 0xa1, 0x60, 0x28, 0x02,
    0x00, 0xa1, 0x60, 0x28, 0x02,
    0x00, 0xa1, 0x60, 0x28, 0x02,
    0x00, 0xa1, 0x60, 0x28, 0x02,
    0x00, 0xa1, 0x60, 0x28, 0x02,
    0x00, 0xa1, 0x60, 0x28, 0x02,
    0x00, 0xa1, 0x60, 0x28, 0x02,
    0x00, 0xa1, 0x60, 0x28, 0x02,
    0x00, 0x61, 0x60, 0x30, 0x02,
    0x1c, 0x01, 0x00, 0x00, 0x02,
    0x23, 0x01, 0x00, 0x00, 0x02,
    0x41, 0x01, 0x00, 0x00, 0x04,
    0x81, 0x01, 0x00, 0x00, 0x04,
    0x81, 0x01, 0x00, 0x00, 0x04,
    0x01, 0x01, 0x00, 0x00, 0x04,
    0x06, 0x00, 0x00, 0x00, 0x04,
    0x0c, 0x00, 0x00, 0x00, 0x04,
    0x18, 0x00, 0x00, 0x00, 0x04,
    0x30, 0x00, 0x00, 0x00, 0x04,
    0x60, 0x00, 0x00, 0x00, 0x04,
    0x40, 0x00, 0x00, 0x00, 0x04,
    0x80, 0x00, 0x00, 0x00, 0x04,
    0x00, 0x01, 0x00, 0x00, 0x04,
    0x00, 0x02, 0x00, 0x00, 0x02,
    0x00, 0x02, 0x00, 0x00, 0x02,
    0x00, 0x04, 0x00, 0x00, 0x02,
    0x00, 0x04, 0x00, 0x00, 0x01,
    0x00, 0x08, 0x00, 0x80, 0x00,
    0x00, 0x10, 0x00, 0xc0, 0x00,
    0x00, 0x30, 0x00, 0x60, 0x00,
    0x00, 0x40, 0x00, 0x10, 0x00,
    0x00, 0x80, 0x03, 0x0c, 0x00,
    0x00, 0x00, 0xfe, 0x03, 0x00};

static const unsigned char unknown[] U8X8_PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x1f, 0x00, 0x00,
    0x00, 0xe0, 0x7f, 0x00, 0x00,
    0x00, 0xf0, 0xff, 0x00, 0x00,
    0x00, 0xf8, 0xf8, 0x01, 0x00,
    0x00, 0x3c, 0xe0, 0x03, 0x00,
    0x00, 0x1c, 0xc0, 0x03, 0x00,
    0x00, 0x3c, 0xc0, 0x03, 0x00,
    0x00, 0x7c, 0xc0, 0x03, 0x00,
    0x00, 0x7c, 0xc0, 0x03, 0x00,
    0x00, 0x7c, 0xe0, 0x03, 0x00,
    0x00, 0x7c, 0xf0, 0x03, 0x00,
    0x00, 0x00, 0xf0, 0x01, 0x00,
    0x00, 0x00, 0xf8, 0x00, 0x00,
    0x00, 0x00, 0x7c, 0x00, 0x00,
    0x00, 0x00, 0x3e, 0x00, 0x00,
    0x00, 0x00, 0x1e, 0x00, 0x00,
    0x00, 0x00, 0x0f, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x07, 0x00, 0x00,
    0x00, 0xc0, 0x0f, 0x00, 0x00,
    0x00, 0xc0, 0x0f, 0x00, 0x00,
    0x00, 0xc0, 0x0f, 0x00, 0x00,
    0x00, 0x80, 0x07, 0x00, 0x00,
    0x00, 0x00, 0x03, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00};