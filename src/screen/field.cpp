#include "screen/field.hpp"

namespace screen{

Field::Field(lv_obj_t *parent, const uint8_t x, const bool iautoInit):
  autoInit(iautoInit){

  obj = lv_obj_create(parent, NULL);
  lv_obj_set_style(obj, &fieldStyle);
  lv_obj_set_size(obj, 240, 240);
  lv_obj_set_pos(obj, x, 0);

  this->resetVectors();

  if(autoInit){
    this->drawColoredTiles();
    this->drawLines();
  }
}

Field::~Field(){
  lv_obj_del(obj);
}

void Field::clean(){
  lv_obj_clean(obj);
  this->resetVectors();

  if(autoInit){
    this->drawColoredTiles();
    this->drawLines();
  }
}

void Field::setX(uint8_t x){
  lv_obj_set_x(obj, x);
}

void Field::drawCubeGroup(const CubeSector pos, const uint8_t presence){
  bool targeted = presence != UINT8_MAX;

  for(int i = 0; i < cubesToDraw.size(); i++){
    if(cubesToDraw[i] == pos){
      cubesToDraw.erase(cubesToDraw.begin() + i);
      break;
    }
  }

  switch(pos){
    case CubeSector::FarLeft:
      if(presence & 0b11100001){
        drawCube({40, 30}, Color::Orange, 1, targeted);
      }
      if(presence & 0b11100010){
        drawCube({40, 70}, Color::Orange, 1, targeted);
      }
      break;
    case CubeSector::FarRight:
      if(presence & 0b11100001){
        drawCube({190, 30}, Color::Green, 1, targeted);
      }
      if(presence & 0b11100010){
        drawCube({190, 70}, Color::Green, 1, targeted);
      }
      break;
    case CubeSector::FarPurple:
      if(presence){
        drawCube({115, 3}, Color::Purple, 1, targeted);
      }
      break;
    case CubeSector::Left1:
      if(presence){
        drawCube({80, 70}, (presence >= 8 ? Color::Orange : (presence >= 2 ? Color::Green : Color::Purple)), numOfBits[presence & 0b00001111], targeted);
      }
      break;
    case CubeSector::Left2:
      if(presence & 0b11101110){
        drawCube({80, 110}, (presence >= 8 ? Color::Orange : Color::Green), numOfBits[presence & 0b00001110], targeted);
      }
      if(presence & 0b11100001){
        drawCube({70, 110}, Color::Purple, 1, targeted);
      }
      break;
    case CubeSector::Left3:
      if(presence & 0b11101100){
        drawCube({80, 150}, (presence >= 8 ? Color::Orange : Color::Green), numOfBits[presence & 0b00001100], targeted);
      }
      if(presence & 0b11100010){
        drawCube({70, 150}, Color::Green, 1, targeted);
      }
      if(presence & 0b11100001){
        drawCube({60, 150}, Color::Purple, 1, targeted);
      }
      break;
    case CubeSector::Left4:
      if(presence & 0b11101000){
        drawCube({80, 190}, Color::Orange, 1, targeted);
      }
      if(presence & 0b11100100){
        drawCube({70, 190}, Color::Green, 1, targeted);
      }
      if(presence & 0b11100010){
        drawCube({60, 190}, Color::Green, 1, targeted);
      }
      if(presence & 0b11100001){
        drawCube({50, 190}, Color::Purple, 1, targeted);
      }
      break;
    case CubeSector::Right1:
      if(presence){
        drawCube({150, 70}, (presence >= 8 ? Color::Green : (presence >= 2 ? Color::Orange : Color::Purple)), numOfBits[presence & 0b00001111], targeted);
      }
      break;
    case CubeSector::Right2:
      if(presence & 0b11101110){
        drawCube({150, 110}, (presence >= 8 ? Color::Green : Color::Orange), numOfBits[presence & 0b00001110], targeted);
      }
      if(presence & 0b11100001){
        drawCube({160, 110}, Color::Purple, 1, targeted);
      }
      break;
    case CubeSector::Right3:
      if(presence & 0b11101100){
        drawCube({150, 150}, (presence >= 8 ? Color::Green : Color::Orange), numOfBits[presence & 0b00001100], targeted);
      }
      if(presence & 0b11100010){
        drawCube({160, 150}, Color::Orange, 1, targeted);
      }
      if(presence & 0b11100001){
        drawCube({170, 150}, Color::Purple, 1, targeted);
      }
      break;
    case CubeSector::Right4:
      if(presence & 0b11101000){
        drawCube({150, 190}, Color::Green, 1, targeted);
      }
      if(presence & 0b11100100){
        drawCube({160, 190}, Color::Orange, 1, targeted);
      }
      if(presence & 0b11100010){
        drawCube({170, 190}, Color::Orange, 1, targeted);
      }
      if(presence & 0b11100001){
        drawCube({180, 190}, Color::Purple, 1, targeted);
      }
      break;
    case CubeSector::Near:
      if(presence & 0b11100001){
        drawCube({110, 217}, Color::Green, 1, targeted);
      }
      if(presence & 0b11100010){
        drawCube({110, 227}, Color::Green, 1, targeted);
      }
      if(presence & 0b11100100){
        drawCube({120, 217}, Color::Orange, 1, targeted);
      }
      if(presence & 0b11101000){
        drawCube({120, 227}, Color::Orange, 1, targeted);
      }
      if(presence & 0b11110000){
        drawCube({115, 222}, Color::Purple, 1, targeted);
      }
      break;
  }
}

void Field::drawTower(const TowerPos pos, const Color contents, const uint8_t cubePresence){
  bool targeted = cubePresence != UINT8_MAX;

  for(int i = 0; i < towersToDraw.size(); i++){
    if(towersToDraw[i] == pos){
      towersToDraw.erase(towersToDraw.begin() + i);
      break;
    }
  }

  lv_obj_t* tower = lv_obj_create(obj, NULL);
  lv_obj_set_size(tower, 16, 16);

  switch(pos){
    case TowerPos::Left:
      lv_obj_set_style(tower, &neutralTower);
      lv_obj_set_pos(tower, 32, 112);

      drawCube(tower, {3, 3}, contents, 1, true);

      if(cubePresence & 0b11110100){
        drawCube({35, 101}, Color::Purple, 1, targeted);
      }
      if(cubePresence & 0b11110010){
        drawCube({35, 129}, Color::Purple, 1, targeted);
      }
      if(cubePresence & 0b11110001){
        drawCube({21, 115}, Color::Orange, 1, targeted);
      }
      break;
    case TowerPos::Right:
      lv_obj_set_style(tower, &neutralTower);
      lv_obj_set_pos(tower, 192, 112);

      drawCube(tower, {3, 3}, contents, 1, true);

      if(cubePresence & 0b11110100){
        drawCube({195, 101}, Color::Purple, 1, targeted);
      }
      if(cubePresence & 0b11110010){
        drawCube({209, 115}, Color::Green, 1, targeted);
      }
      if(cubePresence & 0b11110001){
        drawCube({195, 129}, Color::Purple, 1, targeted);
      }
      break;
    case TowerPos::Center:
      lv_obj_set_style(tower, &neutralTower);
      lv_obj_set_pos(tower, 112, 112);

      drawCube(tower, {3, 3}, contents, 1, true);
      if(cubePresence & 0b11111000){
        drawCube({115, 101}, Color::Purple, 1, targeted);
      }
      if(cubePresence & 0b11110100){
        drawCube({129, 115}, Color::Green, 1, targeted);
      }
      if(cubePresence & 0b11110010){
        drawCube({115, 129}, Color::Purple, 1, targeted);
      }
      if(cubePresence & 0b11110001){
        drawCube({101, 115}, Color::Orange, 1, targeted);
      }
      break;
    case TowerPos::Far:
      lv_obj_set_style(tower, &neutralTower);
      lv_obj_set_pos(tower, 112, 52);

      drawCube(tower, {3, 3}, contents, 1, true);
      if(cubePresence & 0b11111000){
        drawCube({115, 41}, Color::Purple, 1, targeted);
      }
      if(cubePresence & 0b11110100){
        drawCube({129, 55}, Color::Green, 1, targeted);
      }
      if(cubePresence & 0b11110010){
        drawCube({115, 69}, Color::Purple, 1, targeted);
      }
      if(cubePresence & 0b11110001){
        drawCube({101, 55}, Color::Orange, 1, targeted);
      }
      break;
    case TowerPos::Near:
      lv_obj_set_style(tower, &neutralTower);
      lv_obj_set_pos(tower, 112, 172);

      drawCube(tower, {3, 3}, contents, 1, true);
      if(cubePresence & 0b11111000){
        drawCube({115, 161}, Color::Purple, 1, targeted);
      }
      if(cubePresence & 0b11110100){
        drawCube({129, 175}, Color::Green, 1, targeted);
      }
      if(cubePresence & 0b11110010){
        drawCube({115, 189}, Color::Purple, 1, targeted);
      }
      if(cubePresence & 0b11110001){
        drawCube({101, 175}, Color::Orange, 1, targeted);
      }
      break;
    case TowerPos::Red:
      lv_obj_set_style(tower, &redTower);
      lv_obj_set_pos(tower, 54, 228);

      drawCube(tower, {3, 3}, contents, 1, true);
      break;
    case TowerPos::Blue:
      lv_obj_set_style(tower, &blueTower);
      lv_obj_set_pos(tower, 174, 228);

      drawCube(tower, {3, 3}, contents, 1, true);
      break;
  }
}

void Field::drawScoringZone(const ZonePos pos, const Color contents, const uint8_t stackHeight){
   drawScoringZone(pos, {contents, Color::None}, {stackHeight, 0});
}

void Field::drawScoringZone(const ZonePos pos, const std::pair<Color,Color> contents, const std::pair<uint8_t,uint8_t> stackHeight){
  bool targeted = contents.first != Color::None;

  for(int i = 0; i < zonesToDraw.size(); i++){
    if(zonesToDraw[i] == pos){
      zonesToDraw.erase(zonesToDraw.begin() + i);
      break;
    }
  }

  lv_obj_t* zone = lv_obj_create(obj, NULL);

  switch(pos){
    case ZonePos::FarRed:
      lv_obj_set_style(zone, targeted ? &redZoneHighlighted : &redZone);
      lv_obj_set_size(zone, 29, 20);
      lv_obj_set_pos(zone, 0, 0);

      if(targeted){
        drawCube(zone, {4, 5}, contents.first, stackHeight.first, false);
        drawCube(zone, {15, 5}, contents.second, stackHeight.second, false);
      }
      break;
    case ZonePos::FarBlue:
      lv_obj_set_style(zone, targeted ? &blueZoneHighlighted : &blueZone);
      lv_obj_set_size(zone, 29, 20);
      lv_obj_set_pos(zone, 211, 0);

      if(targeted){
        drawCube(zone, {15, 5}, contents.first, stackHeight.first, false);
        drawCube(zone, {4, 5}, contents.second, stackHeight.second, false);
      }
      break;
    case ZonePos::NearRed:
      lv_obj_set_style(zone, targeted ? &redZoneHighlighted : &redZone);
      lv_obj_set_size(zone, 20, 20);
      lv_obj_set_pos(zone, 0, 220);

      if(targeted){
        drawCube(zone, {5, 5}, contents.first, stackHeight.first, false);
      }
      break;
    case ZonePos::NearBlue:
      lv_obj_set_style(zone, targeted ? &blueZoneHighlighted : &blueZone);
      lv_obj_set_size(zone, 20, 20);
      lv_obj_set_pos(zone, 220, 220);

      if(targeted){
        drawCube(zone, {5, 5}, contents.first, stackHeight.first, false);
      }
      break;
  }

  if(!zonesToDraw.size()){
    this->reinforcePerimeter();
  }
}

void Field::drawColoredTiles(){
  lv_obj_t* redLeft1 = lv_obj_create(obj, NULL);
  lv_obj_set_style(redLeft1, &redAlliance);
  lv_obj_set_size(redLeft1, 40, 40);
  lv_obj_set_pos(redLeft1, 0, 40);
  lv_obj_t* redLeft2 = lv_obj_create(obj, redLeft1);
  lv_obj_set_pos(redLeft2, 40, 0);

  lv_obj_t* blueLeft1 = lv_obj_create(obj, redLeft1);
  lv_obj_set_style(blueLeft1, &blueAlliance);
  lv_obj_set_pos(blueLeft1, 200, 40);
  lv_obj_t* blueLeft2 = lv_obj_create(obj, blueLeft1);
  lv_obj_set_pos(blueLeft2, 160, 0);
}

void Field::drawLines(){
  lv_obj_t* middleLine1 = lv_obj_create(obj, NULL);
  lv_obj_set_style(middleLine1, &lineStyle);
  lv_obj_set_pos(middleLine1, 117, 3);
  lv_obj_set_size(middleLine1, 2, 234);
  lv_obj_t* middleLine2 = lv_obj_create(obj, middleLine1);
  lv_obj_set_x(middleLine1, 121);

  lv_obj_t* innerRedZone = lv_line_create(obj, NULL);
  lv_line_set_style(innerRedZone, &lineStyle);
  static lv_point_t irzPts[3] = {{0,40}, {40,40}, {40,0}};
  lv_line_set_points(innerRedZone, irzPts, 3);

  lv_obj_t* outerRedZone = lv_line_create(obj, innerRedZone);
  static lv_point_t orzPts[4] = {{0,80}, {40,80}, {80,40}, {80,0}};
  lv_line_set_points(outerRedZone, orzPts, 4);

  lv_obj_t* innerBlueZone = lv_line_create(obj, innerRedZone);
  static lv_point_t ibzPts[3] = {{200,0}, {200,40}, {240,40}};
  lv_line_set_points(innerBlueZone, ibzPts, 3);

  lv_obj_t* outerBlueZone = lv_line_create(obj, innerRedZone);
  static lv_point_t obzPts[4] = {{160,0}, {160,40}, {200,80}, {240,80}};
  lv_line_set_points(outerBlueZone, obzPts, 4);
}

void Field::reinforcePerimeter(){
  lv_obj_t* perimeter = lv_obj_create(obj, NULL);
  lv_obj_set_style(perimeter, &perimeterStyle);
  lv_obj_set_size(perimeter, 240, 240);
  lv_obj_set_pos(perimeter, 0, 0);
}

void Field::drawRobot(const bool red, const uint8_t pos){
  lv_obj_t* robot = lv_obj_create(obj, NULL);
  lv_obj_set_style(robot, red ? &redAllianceHighlighted : &blueAllianceHighlighted);
  lv_obj_set_size(robot, 30, 30);
  lv_obj_set_pos(robot, red ? 3 : 207, pos - 15);
}

void Field::finishDrawing(){
  while(zonesToDraw.size()){
    drawScoringZone(zonesToDraw[0]);
  }

  while(cubesToDraw.size()){
    drawCubeGroup(cubesToDraw[0]);
  }

  while(towersToDraw.size()){
    drawTower(towersToDraw[0]);
  }
}

void Field::drawCube(const std::pair<uint8_t, uint8_t> pos, const Color color, const uint8_t stackHeight, const bool targeted){
  drawCube(obj, pos, color, stackHeight, targeted);
}

void Field::drawCube(lv_obj_t *parent, const std::pair<uint8_t, uint8_t> pos, const Color color, const uint8_t stackHeight, const bool targeted){
  if(color == Color::None) return;

  lv_obj_t* cube = lv_obj_create(parent, NULL);
  lv_obj_set_style(cube, (color == Color::Orange ? (targeted ? &orangeStyleHighlighted : &orangeStyle) :
                          color == Color::Green  ? (targeted ? &greenStyleHighlighted  : &greenStyle ) :
                                                   (targeted ? &purpleStyleHighlighted : &purpleStyle)));
  lv_obj_set_pos(cube, pos.first, pos.second);
  lv_obj_set_size(cube, 10, 10);

  if(stackHeight > 1){
    lv_obj_t* cubeLabel = lv_label_create(cube, NULL);
    lv_label_set_style(cubeLabel, &littleWhiteText);
    lv_obj_align(cubeLabel, NULL, LV_ALIGN_CENTER, -1, -1);
    lv_label_set_align(cubeLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(cubeLabel, (" "+std::to_string(stackHeight)).c_str());
  }
}

void Field::resetVectors(){
  //fully occupy
  cubesToDraw = {CubeSector::FarLeft, CubeSector::FarRight, CubeSector::FarPurple, CubeSector::Left1, CubeSector::Left2, CubeSector::Left3, CubeSector::Left4, CubeSector::Right1, CubeSector::Right2, CubeSector::Right3, CubeSector::Right4, CubeSector::Near};
  towersToDraw = {TowerPos::Left, TowerPos::Right, TowerPos::Center, TowerPos::Far, TowerPos::Near, TowerPos::Red, TowerPos::Blue};
  zonesToDraw = {ZonePos::FarRed, ZonePos::FarBlue, ZonePos::NearRed, ZonePos::NearBlue};
}

}//namespace screen
