#pragma once
#include "api.h"

// this file contains additional resources for the tower takeover (2019-2020) field

namespace screen {

/**
 * Initializes all styles declared in this header, MUST be run before anything is
 * done with fields, I suggest calling it in initialize()
 */

void initializeTTFieldStyles();

// styles
extern lv_style_t perimeterStyle;
extern lv_style_t orangeStyleHighlighted;
extern lv_style_t orangeStyle;
extern lv_style_t greenStyleHighlighted;
extern lv_style_t greenStyle;
extern lv_style_t purpleStyleHighlighted;
extern lv_style_t purpleStyle;
extern lv_style_t neutralTower;
extern lv_style_t redTower;
extern lv_style_t blueTower;
extern lv_style_t redZone;
extern lv_style_t blueZone;
extern lv_style_t redZoneHighlighted;
extern lv_style_t blueZoneHighlighted;


// enums
enum class color { none, orange, green, purple };

enum class cubeGroup {
  farLeft,
  farRight,
  farPurple,
  left1,
  left2,
  left3,
  left4,
  right1,
  right2,
  right3,
  right4,
  near
};

enum class tower { left, right, center, far, near, red, blue };

enum class scoringZone { farRed, farBlue, nearRed, nearBlue };

}
