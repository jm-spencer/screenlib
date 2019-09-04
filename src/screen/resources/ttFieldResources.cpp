#include "screen/resources/ttFieldResources.hpp"

namespace screen {

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

void initializeTTFieldStyles(){
  lv_style_copy(&perimeterStyle, &lv_style_plain);
  perimeterStyle.body.empty  = true;
  perimeterStyle.body.radius = 0;

  perimeterStyle.body.border.color = LV_COLOR_BLACK;
  perimeterStyle.body.border.width = 3;

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

}
