#pragma once
#include "api.h"

// this file contains general resources for screenlib

namespace screen {

/**
 * Initializes all styles declared in this header, MUST be run before anything is
 * done with the screen, I suggest calling it in initialize()
 */

void initializeGeneralStyles();

// styles

extern lv_style_t blankStyle;
extern lv_style_t listStyle;
extern lv_style_t blueAlliance;
extern lv_style_t redAlliance;
extern lv_style_t lineStyle;
extern lv_style_t whiteText;
extern lv_style_t blueText;
extern lv_style_t redText;
extern lv_style_t greenBox;
extern lv_style_t pressedButton;
extern lv_font_t  smallFont;
extern lv_style_t littleWhiteText;


}
