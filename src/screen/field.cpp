#include "screen/field.hpp"

namespace screen {

Field::Field(lv_obj_t *parent, const double ilength, const bool iautoInit,
             const NumberConfig iconfig):
             scalar(ilength / 240), autoInit(iautoInit), config(iconfig),
             wallDrawn(false), allianceTowerContents(color::none, color::none)
{
  obj = lv_obj_create(parent, NULL);
  lv_obj_set_style(obj, &fieldStyle);
  lv_obj_set_size(obj, ilength, ilength);
  lv_obj_set_pos(obj, 120, 0);

  resetVectors();

  if (autoInit) {
    drawColoredTiles();
    drawLines();
  }
}

Field::~Field()
{
  lv_obj_del(obj);
}

void Field::clean()
{
  lv_obj_clean(obj);
  resetVectors();

  wallDrawn             = false;
  allianceTowerContents = {color::none, color::none};

  if (autoInit) {
    drawColoredTiles();
    drawLines();
  }
}

void Field::setX(int x)
{
  lv_obj_set_x(obj, x);
}

void Field::setY(int y)
{
  lv_obj_set_y(obj, y);
}

void Field::setPos(int x, int y)
{
  lv_obj_set_pos(obj, x, y);
}

void Field::setSideLength(uint ilength){
  scalar = ilength / 240.0;
  lv_obj_set_size(obj, ilength, ilength);
  clean();
}

void Field::draw(const cubeGroup pos, const uint8_t presence)
{
  bool targeted = presence != UINT8_MAX;

  for (int i = 0; i < cubesToDraw.size(); i++) {
    if (cubesToDraw[i] == pos) {
      cubesToDraw.erase(cubesToDraw.begin() + i);
      break;
    }
  }

  switch (pos) {
    case cubeGroup::farLeft:
      if (presence & 0b11100001) {
        drawCube({40, 30}, color::orange, 1, targeted);
      }
      if (presence & 0b11100010) {
        drawCube({40, 70}, color::orange, 1, targeted);
      }
      break;
    case cubeGroup::farRight:
      if (presence & 0b11100001) {
        drawCube({190, 30}, color::green, 1, targeted);
      }
      if (presence & 0b11100010) {
        drawCube({190, 70}, color::green, 1, targeted);
      }
      break;
    case cubeGroup::farPurple:
      if (presence) {
        drawCube({115, 3}, color::purple, 1, targeted);
      }
      break;
    case cubeGroup::left1:
      if (presence) {
        drawCube({80, 70},
                 presence >= 8 ? color::orange : (presence >= 2 ? color::green : color::purple),
                 numOfBits[presence & 0b00001111], targeted);
      }
      break;
    case cubeGroup::left2:
      if (presence & 0b11101110) {
        drawCube({80, 110}, presence >= 8 ? color::orange : color::green,
                 numOfBits[presence & 0b00001110], targeted);
      }
      if (presence & 0b11100001) {
        drawCube({70, 110}, color::purple, 1, targeted);
      }
      break;
    case cubeGroup::left3:
      if (presence & 0b11101100) {
        drawCube({80, 150}, presence >= 8 ? color::orange : color::green,
                 numOfBits[presence & 0b00001100], targeted);
      }
      if (presence & 0b11100010) {
        drawCube({70, 150}, color::green, 1, targeted);
      }
      if (presence & 0b11100001) {
        drawCube({60, 150}, color::purple, 1, targeted);
      }
      break;
    case cubeGroup::left4:
      if (presence & 0b11101000) {
        drawCube({80, 190}, color::orange, 1, targeted);
      }
      if (presence & 0b11100100) {
        drawCube({70, 190}, color::green, 1, targeted);
      }
      if (presence & 0b11100010) {
        drawCube({60, 190}, color::green, 1, targeted);
      }
      if (presence & 0b11100001) {
        drawCube({50, 190}, color::purple, 1, targeted);
      }
      break;
    case cubeGroup::right1:
      if (presence) {
        drawCube({150, 70},
                 presence >= 8 ? color::green : (presence >= 2 ? color::orange : color::purple),
                 numOfBits[presence & 0b00001111], targeted);
      }
      break;
    case cubeGroup::right2:
      if (presence & 0b11101110) {
        drawCube({150, 110}, presence >= 8 ? color::green : color::orange,
                 numOfBits[presence & 0b00001110], targeted);
      }
      if (presence & 0b11100001) {
        drawCube({160, 110}, color::purple, 1, targeted);
      }
      break;
    case cubeGroup::right3:
      if (presence & 0b11101100) {
        drawCube({150, 150}, presence >= 8 ? color::green : color::orange,
                 numOfBits[presence & 0b00001100], targeted);
      }
      if (presence & 0b11100010) {
        drawCube({160, 150}, color::orange, 1, targeted);
      }
      if (presence & 0b11100001) {
        drawCube({170, 150}, color::purple, 1, targeted);
      }
      break;
    case cubeGroup::right4:
      if (presence & 0b11101000) {
        drawCube({150, 190}, color::green, 1, targeted);
      }
      if (presence & 0b11100100) {
        drawCube({160, 190}, color::orange, 1, targeted);
      }
      if (presence & 0b11100010) {
        drawCube({170, 190}, color::orange, 1, targeted);
      }
      if (presence & 0b11100001) {
        drawCube({180, 190}, color::purple, 1, targeted);
      }
      break;
    case cubeGroup::near:
      if (presence & 0b11101000) {
        drawCube({120, 227}, color::orange, 1, targeted);
      }
      if (presence & 0b11100100) {
        drawCube({120, 217}, color::orange, 1, targeted);
      }
      if (presence & 0b11100010) {
        drawCube({110, 227}, color::green, 1, targeted);
      }
      if (presence & 0b11100001) {
        drawCube({110, 217}, color::green, 1, targeted);
      }
      if (presence & 0b11110000) {
        drawCube({115, 222}, color::purple, 1, targeted);
      }
      break;
  }
}

void Field::draw(const tower pos, const color contents, const uint8_t cubePresence)
{
  bool targeted = cubePresence != UINT8_MAX;

  for (int i = 0; i < towersToDraw.size(); i++) {
    if (towersToDraw[i] == pos) {
      towersToDraw.erase(towersToDraw.begin() + i);
      break;
    }
  }

  // alliance towers shouldn't be drawn until after the border is drawn;
  // store the value and print later unless the border is already drawn
  if (!wallDrawn) {
    if (pos == tower::red) {
      allianceTowerContents.first = contents;
      return;
    } else if (pos == tower::blue) {
      allianceTowerContents.second = contents;
      return;
    }
  }

  lv_obj_t *tower = lv_obj_create(obj, NULL);
  lv_obj_set_size(tower, scale(16), scale(16));

  switch (pos) {
    case tower::left:
      lv_obj_set_style(tower, &neutralTower);
      lv_obj_set_pos(tower, scale(32), scale(112));

      drawCube(tower, {3, 3}, scalar, contents, 1, config, true);

      if (cubePresence & 0b11111000) {
        drawCube({35, 101}, color::purple, 1, targeted);
      }
      if (cubePresence & 0b11110010) {
        drawCube({35, 129}, color::purple, 1, targeted);
      }
      if (cubePresence & 0b11110001) {
        drawCube({21, 115}, color::orange, 1, targeted);
      }
      break;
    case tower::right:
      lv_obj_set_style(tower, &neutralTower);
      lv_obj_set_pos(tower, scale(192), scale(112));

      drawCube(tower, {3, 3}, scalar, contents, 1, config, true);

      if (cubePresence & 0b11111000) {
        drawCube({195, 101}, color::purple, 1, targeted);
      }
      if (cubePresence & 0b11110100) {
        drawCube({209, 115}, color::green, 1, targeted);
      }
      if (cubePresence & 0b11110010) {
        drawCube({195, 129}, color::purple, 1, targeted);
      }
      break;
    case tower::center:
      lv_obj_set_style(tower, &neutralTower);
      lv_obj_set_pos(tower, scale(112), scale(112));

      drawCube(tower, {3, 3}, scalar, contents, 1, config, true);
      if (cubePresence & 0b11111000) {
        drawCube({115, 101}, color::purple, 1, targeted);
      }
      if (cubePresence & 0b11110100) {
        drawCube({129, 115}, color::green, 1, targeted);
      }
      if (cubePresence & 0b11110010) {
        drawCube({115, 129}, color::purple, 1, targeted);
      }
      if (cubePresence & 0b11110001) {
        drawCube({101, 115}, color::orange, 1, targeted);
      }
      break;
    case tower::far:
      lv_obj_set_style(tower, &neutralTower);
      lv_obj_set_pos(tower, scale(112), scale(52));

      drawCube(tower, {3, 3}, scalar, contents, 1, config, true);
      if (cubePresence & 0b11111000) {
        drawCube({115, 41}, color::purple, 1, targeted);
      }
      if (cubePresence & 0b11110100) {
        drawCube({129, 55}, color::green, 1, targeted);
      }
      if (cubePresence & 0b11110010) {
        drawCube({115, 69}, color::purple, 1, targeted);
      }
      if (cubePresence & 0b11110001) {
        drawCube({101, 55}, color::orange, 1, targeted);
      }
      break;
    case tower::near:
      lv_obj_set_style(tower, &neutralTower);
      lv_obj_set_pos(tower, scale(112), scale(172));

      drawCube(tower, {3, 3}, scalar, contents, 1, config, true);
      if (cubePresence & 0b11111000) {
        drawCube({115, 161}, color::purple, 1, targeted);
      }
      if (cubePresence & 0b11110100) {
        drawCube({129, 175}, color::green, 1, targeted);
      }
      if (cubePresence & 0b11110010) {
        drawCube({115, 189}, color::purple, 1, targeted);
      }
      if (cubePresence & 0b11110001) {
        drawCube({101, 175}, color::orange, 1, targeted);
      }
      break;
    case tower::red:
      lv_obj_set_style(tower, &redTower);
      lv_obj_set_pos(tower, scale(54), scale(228));

      drawCube(tower, {3, 3}, scalar, contents, 1, config, true);
      break;
    case tower::blue:
      lv_obj_set_style(tower, &blueTower);
      lv_obj_set_pos(tower, scale(174), scale(228));

      drawCube(tower, {3, 3}, scalar, contents, 1, config, true);
      break;
  }
}

void Field::draw(const scoringZone pos, const color contents, const uint8_t stackHeight)
{
  draw(pos, {contents, color::none}, {stackHeight, 0});
}

void Field::draw(const scoringZone pos, const std::pair<color, color> contents,
                            const std::pair<uint8_t, uint8_t> stackHeight)
{
  bool targeted = contents.first != color::none;

  for (int i = 0; i < zonesToDraw.size(); i++) {
    if (zonesToDraw[i] == pos) {
      zonesToDraw.erase(zonesToDraw.begin() + i);
      break;
    }
  }

  lv_obj_t *zone = lv_obj_create(obj, NULL);

  switch (pos) {
    case scoringZone::farRed:
      lv_obj_set_style(zone, targeted ? &redZoneHighlighted : &redZone);
      lv_obj_set_size(zone, scale(29), scale(20));
      lv_obj_set_pos(zone, 0, 0);

      if (targeted) {
        drawCube(zone, {4, 5}, scalar, contents.first, stackHeight.first, config, false);
        drawCube(zone, {15, 5}, scalar, contents.second, stackHeight.second, config, false);
      }
      break;
    case scoringZone::farBlue:
      lv_obj_set_style(zone, targeted ? &blueZoneHighlighted : &blueZone);
      lv_obj_set_size(zone, scale(29), scale(20));
      lv_obj_set_pos(zone, scale(211), 0);

      if (targeted) {
        drawCube(zone, {15, 5}, scalar, contents.first, stackHeight.first, config, false);
        drawCube(zone, {4, 5}, scalar, contents.second, stackHeight.second, config, false);
      }
      break;
    case scoringZone::nearRed:
      lv_obj_set_style(zone, targeted ? &redZoneHighlighted : &redZone);
      lv_obj_set_size(zone, scale(20), scale(20));
      lv_obj_set_pos(zone, 0, scale(220));

      if (targeted) {
        drawCube(zone, {5, 5}, scalar, contents.first, stackHeight.first, config, false);
      }
      break;
    case scoringZone::nearBlue:
      lv_obj_set_style(zone, targeted ? &blueZoneHighlighted : &blueZone);
      lv_obj_set_size(zone, scale(20), scale(20));
      lv_obj_set_pos(zone, scale(220), scale(220));

      if (targeted) {
        drawCube(zone, {5, 5}, scalar, contents.first, stackHeight.first, config, false);
      }
      break;
  }

  if (!zonesToDraw.size()) {
    reinforcePerimeter();
  }
}

void Field::drawColoredTiles()
{
  lv_obj_t *redLeft1 = lv_obj_create(obj, NULL);
  lv_obj_set_style(redLeft1, &redAlliance);
  lv_obj_set_size(redLeft1, scale(40), scale(40));
  lv_obj_set_pos(redLeft1, 0, scale(40));
  lv_obj_t *redLeft2 = lv_obj_create(obj, redLeft1);
  lv_obj_set_pos(redLeft2, scale(40), 0);

  lv_obj_t *blueLeft1 = lv_obj_create(obj, redLeft1);
  lv_obj_set_style(blueLeft1, &blueAlliance);
  lv_obj_set_pos(blueLeft1, scale(200), scale(40));
  lv_obj_t *blueLeft2 = lv_obj_create(obj, blueLeft1);
  lv_obj_set_pos(blueLeft2, scale(160), 0);
}

void Field::drawLines()
{

  short s40, s80, s160, s200, s240;

  static lv_point_t irzPts[3];
  static lv_point_t orzPts[4];
  static lv_point_t ibzPts[3];
  static lv_point_t obzPts[4];

  lv_obj_t *middleLine1 = lv_obj_create(obj, NULL);
  lv_obj_set_style(middleLine1, &lineStyle);
  lv_obj_set_pos(middleLine1, scale(117), 3);
  lv_obj_set_size(middleLine1, scale(2), scale(234));
  lv_obj_t *middleLine2 = lv_obj_create(obj, middleLine1);
  lv_obj_set_x(middleLine1, scale(121));

  lv_obj_t *innerRedZone = lv_line_create(obj, NULL);
  lv_line_set_style(innerRedZone, &lineStyle);

  s40 = static_cast<short>(scale(40));
  s80 = static_cast<short>(scale(80));
  s160 = static_cast<short>(scale(160));
  s200 = static_cast<short>(scale(200));
  s240 = static_cast<short>(scale(240));

  irzPts[0] = {0, s40}; irzPts[1] = {s40, s40}; irzPts[2] = {s40, 0};
  lv_line_set_points(innerRedZone, irzPts, 3);

  lv_obj_t *outerRedZone      = lv_line_create(obj, innerRedZone);
  orzPts[0] = {0, s80}; orzPts[1] = {s40, s80}; orzPts[2] = {s80, s40}; orzPts[3] = {s80, 0};
  lv_line_set_points(outerRedZone, orzPts, 4);

  lv_obj_t *innerBlueZone     = lv_line_create(obj, innerRedZone);
  ibzPts[0] = {s200, 0}; ibzPts[1] = {s200, s40}; ibzPts[2] = {s240, s40};
  lv_line_set_points(innerBlueZone, ibzPts, 3);

  lv_obj_t *outerBlueZone     = lv_line_create(obj, innerRedZone);
  obzPts[0] = {s160, 0}; obzPts[1] = {s160, s40}; obzPts[2] = {s200, s80}; obzPts[3] = {s240, s80};
  lv_line_set_points(outerBlueZone, obzPts, 4);
}

void Field::reinforcePerimeter()
{
  lv_obj_t *perimeter = lv_obj_create(obj, NULL);
  lv_obj_set_style(perimeter, &perimeterStyle);
  lv_obj_set_size(perimeter, scale(240), scale(240));
  lv_obj_set_pos(perimeter, 0, 0);

  wallDrawn = true;

  if (allianceTowerContents.first != color::none)
    draw(tower::red, allianceTowerContents.first);
  if (allianceTowerContents.second != color::none)
    draw(tower::blue, allianceTowerContents.second);
}

void Field::drawRobot(const bool red, const uint8_t pos)
{
  lv_obj_t *robot = lv_obj_create(obj, NULL);
  lv_obj_set_style(robot, red ? &redAllianceHighlighted : &blueAllianceHighlighted);
  lv_obj_set_size(robot, scale(30), scale(30));
  lv_obj_set_pos(robot, red ? 3 : scale(210) - 3, scale(pos - 15));
}

void Field::finishDrawing()
{
  while (zonesToDraw.size()) {
    draw(zonesToDraw[0]);
  }

  while (cubesToDraw.size()) {
    draw(cubesToDraw[0]);
  }

  while (towersToDraw.size()) {
    draw(towersToDraw[0]);
  }
}

void Field::drawCube(const std::pair<uint8_t, uint8_t> pos, const color color,
                     const uint8_t stackHeight, const bool targeted)
{
  drawCube(obj, pos, scalar, color, stackHeight, config, targeted);
}

void Field::drawCube(lv_obj_t *parent, const std::pair<uint8_t, uint8_t> pos, double scalar,
                     const color color, const uint8_t stackHeight, const NumberConfig config,
                     const bool targeted)
{
  if (color == color::none)
    return;

  lv_obj_t *cube = lv_obj_create(parent, NULL);
  lv_obj_set_style(
      cube, (color == color::orange
                 ? (targeted ? &orangeStyleHighlighted : &orangeStyle)
                 : color == color::green ? (targeted ? &greenStyleHighlighted : &greenStyle)
                                         : (targeted ? &purpleStyleHighlighted : &purpleStyle)));
  lv_obj_set_pos(cube, scalar * pos.first, scalar * pos.second);
  lv_obj_set_size(cube, scalar * 10, scalar * 10);

  if (stackHeight > 1) {
    lv_obj_t *cubeLabel = lv_label_create(cube, NULL);
    lv_label_set_style(cubeLabel, config.fontStyle);
    lv_obj_align(cubeLabel, NULL, LV_ALIGN_CENTER, config.deltaX, config.deltaY);
    lv_label_set_align(cubeLabel, LV_LABEL_ALIGN_CENTER);
    lv_label_set_text(cubeLabel, std::to_string(stackHeight).c_str());
  }
}

int Field::scale(int original)
{
  return scalar * original;
}

void Field::resetVectors()
{
  // fully populate the vectors
  cubesToDraw  = {cubeGroup::farLeft, cubeGroup::farRight, cubeGroup::farPurple,
                 cubeGroup::left1,   cubeGroup::left2,    cubeGroup::left3,
                 cubeGroup::left4,   cubeGroup::right1,   cubeGroup::right2,
                 cubeGroup::right3,  cubeGroup::right4,   cubeGroup::near};

  towersToDraw = {tower::left, tower::right, tower::center, tower::far,
                  tower::near, tower::red,   tower::blue};

  zonesToDraw  = {scoringZone::farRed, scoringZone::farBlue,
                  scoringZone::nearRed, scoringZone::nearBlue};
}

}  // namespace screen
