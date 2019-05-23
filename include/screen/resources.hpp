/**
 * Contains the resources for printing the field
 */

#ifndef SCREEN_RESOURCES_HPP_
#define SCREEN_RESOURCES_HPP_
#include "main.h"

extern lv_font_t smallFont;

namespace screen {

/**
 * These styles are used for the objects on the field, along with
 * some other, such as blueText and redText that are probably going
 * to be useful to anyone making an auton selector around it
 */

/**
 * This frist group of styles are likely to be used in every game,
 * and therefore are kept seperate for when this is updated
 */

extern lv_style_t blankStyle;
extern lv_style_t listStyle;
extern lv_style_t fieldStyle;
extern lv_style_t blueAlliance;
extern lv_style_t blueAllianceHighlighted;
extern lv_style_t redAlliance;
extern lv_style_t redAllianceHighlighted;
extern lv_style_t lineStyle;
extern lv_style_t whiteText;
extern lv_style_t blueText;
extern lv_style_t redText;
extern lv_style_t greenBox;
extern lv_style_t pressedButton;

/**
 * This group has not been needed in the past,
 * but could be useful in future games
 */

extern lv_style_t littleWhiteText;
extern lv_style_t perimeterStyle;

/**
 * This group only pertains to the current game
 */

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

/**
 * Initializes all styles, MUST be run before anything is
 * done with the screen, I suggest calling it in initialize()
 */

void initializeStyles();

/**
 * Various enums for more readable parameters
 */

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

}  // namespace screen

#endif
