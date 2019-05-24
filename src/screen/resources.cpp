#include "screen/resources.hpp"

namespace screen {

lv_style_t blankStyle;
lv_style_t listStyle;
lv_style_t fieldStyle;
lv_style_t blueAlliance;
lv_style_t blueAllianceHighlighted;
lv_style_t redAlliance;
lv_style_t redAllianceHighlighted;
lv_style_t lineStyle;
lv_style_t blueCap;
lv_style_t whiteText;
lv_style_t blueText;
lv_style_t redText;
lv_style_t greenBox;
lv_style_t pressedButton;

lv_style_t littleWhiteText;
lv_style_t perimeterStyle;

lv_style_t orangeStyleHighlighted;
lv_style_t orangeStyle;
lv_style_t greenStyleHighlighted;
lv_style_t greenStyle;
lv_style_t purpleStyleHighlighted;
lv_style_t purpleStyle;
lv_style_t neutralTower;
lv_style_t redTower;
lv_style_t blueTower;
lv_style_t redZone;
lv_style_t blueZone;
lv_style_t redZoneHighlighted;
lv_style_t blueZoneHighlighted;

void initializeStyles()
{
  lv_style_copy(&blankStyle, &lv_style_plain);
  blankStyle.body.main_color   = LV_COLOR_GRAY;
  blankStyle.body.grad_color   = LV_COLOR_GRAY;
  blankStyle.body.border.width = 0;

  lv_style_copy(&listStyle, &lv_style_plain);
  listStyle.body.main_color   = LV_COLOR_SILVER;
  listStyle.body.grad_color   = LV_COLOR_SILVER;
  listStyle.body.border.width = 3;
  listStyle.body.radius       = 0;

  listStyle.body.border.color = LV_COLOR_BLACK;
  listStyle.body.border.width = 3;

  lv_style_copy(&fieldStyle, &listStyle);
  fieldStyle.body.main_color = LV_COLOR_GRAY;
  fieldStyle.body.grad_color = LV_COLOR_GRAY;

  lv_style_copy(&perimeterStyle, &fieldStyle);
  perimeterStyle.body.empty = true;

  lv_style_copy(&blueAlliance, &fieldStyle);
  blueAlliance.body.main_color   = LV_COLOR_BLUE;
  blueAlliance.body.grad_color   = LV_COLOR_BLUE;
  blueAlliance.body.border.width = 0;

  lv_style_copy(&blueAllianceHighlighted, &blueAlliance);
  blueAllianceHighlighted.body.border.width = 3;
  blueAllianceHighlighted.body.border.color = LV_COLOR_WHITE;

  lv_style_copy(&redAlliance, &blueAlliance);
  redAlliance.body.main_color = LV_COLOR_RED;
  redAlliance.body.grad_color = LV_COLOR_RED;

  lv_style_copy(&redAllianceHighlighted, &redAlliance);
  redAllianceHighlighted.body.border.width = 3;
  redAllianceHighlighted.body.border.color = LV_COLOR_WHITE;

  lv_style_copy(&lineStyle, &lv_style_plain);
  lineStyle.body.main_color = LV_COLOR_WHITE;
  lineStyle.body.grad_color = LV_COLOR_WHITE;
  lineStyle.line.color      = LV_COLOR_WHITE;
  lineStyle.line.width      = 3;

  lv_style_copy(&whiteText, &lv_style_plain);
  whiteText.text.color        = LV_COLOR_WHITE;
  whiteText.text.font         = &lv_font_dejavu_20;
  whiteText.text.letter_space = 2;
  whiteText.text.line_space   = 1;

  lv_style_copy(&littleWhiteText, &whiteText);
  littleWhiteText.text.font = &::smallFont;

  lv_style_copy(&blueText, &whiteText);
  blueText.text.color = LV_COLOR_BLUE;

  lv_style_copy(&redText, &whiteText);
  redText.text.color = LV_COLOR_RED;

  lv_style_copy(&greenBox, &listStyle);
  greenBox.body.main_color = LV_COLOR_MAKE(0x00, 0xDD, 0x00);
  greenBox.body.grad_color = LV_COLOR_MAKE(0x00, 0xDD, 0x00);

  lv_style_copy(&pressedButton, &listStyle);
  pressedButton.body.main_color = LV_COLOR_GRAY;
  pressedButton.body.grad_color = LV_COLOR_GRAY;

  lv_style_copy(&orangeStyle, &lv_style_plain);
  orangeStyle.body.radius       = 0;
  orangeStyle.body.main_color   = LV_COLOR_MAKE(0xFF, 0x80, 0x00);
  orangeStyle.body.grad_color   = LV_COLOR_MAKE(0xFF, 0x80, 0x00);
  orangeStyle.body.border.color = LV_COLOR_WHITE;
  orangeStyle.body.border.width = 0;

  lv_style_copy(&orangeStyleHighlighted, &orangeStyle);
  orangeStyleHighlighted.body.border.width = 1;

  lv_style_copy(&greenStyle, &orangeStyle);
  greenStyle.body.main_color = LV_COLOR_GREEN;
  greenStyle.body.grad_color = LV_COLOR_GREEN;

  lv_style_copy(&greenStyleHighlighted, &greenStyle);
  greenStyleHighlighted.body.border.width = 1;

  lv_style_copy(&purpleStyle, &orangeStyle);
  purpleStyle.body.main_color = LV_COLOR_PURPLE;
  purpleStyle.body.grad_color = LV_COLOR_PURPLE;

  lv_style_copy(&purpleStyleHighlighted, &purpleStyle);
  purpleStyleHighlighted.body.border.width = 1;

  lv_style_copy(&neutralTower, &lv_style_plain);
  neutralTower.body.main_color   = LV_COLOR_GRAY;
  neutralTower.body.grad_color   = LV_COLOR_GRAY;
  neutralTower.body.border.color = LV_COLOR_BLACK;
  neutralTower.body.border.width = 2;
  neutralTower.body.radius       = LV_RADIUS_CIRCLE;

  lv_style_copy(&redTower, &neutralTower);
  redTower.body.main_color = LV_COLOR_RED;
  redTower.body.grad_color = LV_COLOR_RED;

  lv_style_copy(&blueTower, &neutralTower);
  blueTower.body.main_color = LV_COLOR_BLUE;
  blueTower.body.grad_color = LV_COLOR_BLUE;

  lv_style_copy(&redZone, &fieldStyle);
  redZone.body.border.width = 3;
  redZone.body.radius       = 3;
  redZone.body.border.color = LV_COLOR_RED;

  lv_style_copy(&redZoneHighlighted, &redZone);
  redZoneHighlighted.body.main_color = LV_COLOR_WHITE;
  redZoneHighlighted.body.grad_color = LV_COLOR_WHITE;

  lv_style_copy(&blueZone, &redZone);
  blueZone.body.border.color = LV_COLOR_BLUE;

  lv_style_copy(&blueZoneHighlighted, &blueZone);
  blueZoneHighlighted.body.main_color = LV_COLOR_WHITE;
  blueZoneHighlighted.body.grad_color = LV_COLOR_WHITE;
}

}  // namespace screen
