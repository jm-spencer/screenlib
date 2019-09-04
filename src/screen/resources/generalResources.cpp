#include "screen/resources/generalResources.hpp"

namespace screen {

lv_style_t blankStyle;
lv_style_t listStyle;
lv_style_t blueAlliance;
lv_style_t redAlliance;
lv_style_t lineStyle;
lv_style_t blueCap;
lv_style_t whiteText;
lv_style_t blueText;
lv_style_t redText;
lv_style_t greenBox;
lv_style_t pressedButton;
lv_font_t  smallFont;
lv_style_t littleWhiteText;
lv_style_t fieldStyle;
lv_style_t blueAllianceHighlighted;
lv_style_t redAllianceHighlighted;

void initializeGeneralStyles(){
  lv_style_copy(&blankStyle, &lv_style_plain);
  blankStyle.body.main_color   = LV_COLOR_GRAY;
  blankStyle.body.grad_color   = LV_COLOR_GRAY;
  blankStyle.body.border.width = 0;

  lv_style_copy(&listStyle, &lv_style_plain);
  listStyle.body.main_color   = LV_COLOR_SILVER;
  listStyle.body.grad_color   = LV_COLOR_SILVER;
  listStyle.body.radius       = 0;

  listStyle.body.border.color = LV_COLOR_BLACK;
  listStyle.body.border.width = 3;

  lv_style_copy(&blueAlliance, &listStyle);
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
  littleWhiteText.text.font = &smallFont;

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

  lv_style_copy(&fieldStyle, &listStyle);
  fieldStyle.body.main_color = LV_COLOR_GRAY;
  fieldStyle.body.grad_color = LV_COLOR_GRAY;
}

}
