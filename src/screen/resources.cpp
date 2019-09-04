#include "screen/resources.hpp"

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

void initializeStyles()
{


  lv_style_copy(&perimeterStyle, &fieldStyle);
  perimeterStyle.body.empty = true;




  
}

}  // namespace screen
