#ifndef SCREEN_FIELD_HPP_
#define SCREEN_FIELD_HPP_
#include "screen/resources.hpp"
#include <vector>

#define TOWER_CUBE_FAR 8
#define TOWER_CUBE_RIGHT 4
#define TOWER_CUBE_NEAR 2
#define TOWER_CUBE_LEFT 1

#define CUBE_HIGHEST 8
#define CUBE_2HIGHEST 4
#define CUBE_2LOWEST 2
#define CUBE_LOWEST 1

#define CUBE_FAR 2
#define CUBE_NEAR 1

#define CUBE_TOP_NEAR 16
#define CUBE_NEAR_RIGHT 8
#define CUBE_FAR_RIGHT 4
#define CUBE_NEAR_LEFT 2
#define CUBE_FAR_LEFT 1


namespace screen{

class Field{
  public:
  /**
   * Field generator for the screen
   *
   * @param parent LVGL object to place upon
   * @param x x-value from 0-240 of the leftmost side of the field, default is centered
   * @param iautoInit print colored tiles / taped lines immediately, and after each clean
   */
  Field(lv_obj_t *parent, uint8_t x = 120, bool iautoInit = true);
  ~Field();

  /**
   * Remove all objects from the field
   */
  void clean();

  /**
   * Set new x position on the screen
   * note: Y cannot be changed, as the field takes up the entire screen vertically
   *
   * @param x new x-value from 0-240 of the leftmost side of the field
   */
  void setX(uint8_t x);

  /**
   * draw a group of cubes
   *
   * @param pos which group of cubes to print - see resources.hpp
   * @param presence a bitfield of present cubes. Starts at highest cube as the highest bit,
   *    or furthest, or leftmost, depending on which group
   */
  void drawCubeGroup(cubeSector pos, uint8_t presence = UINT8_MAX);

  /**
   * draw a tower and group of cubes around it
   *
   * @param pos which tower to print - see resources.hpp
   * @param contents what color cube is inside, set color::none for no cube
   * @param presence a bitfield of present cubes. Starts with furthest and moves clockwise
   */
  void drawTower(towerPos pos, color contents = color::none, uint8_t cubePresence = UINT8_MAX);

  /**
   * draw a scoring zone (and cubes inside)
   *
   * @param pos which zone to print
   * @param contents what color cube is inside, set color::none for no cube
   * @param stackHeight how many cubes are in the zone vertically (puts number on top)
   */
  void drawScoringZone(zonePos pos, color contents = color::none, uint8_t stackHeight = 0);

  /**
   * draw a scoring zone (and cubes inside)
   *
   * @param pos which zone to print
   * @param contents what colors of cubes are inside, use other function for 0 or 1 cubes
   * @param stackHeight how many cubes are in the zone vertically (puts number on top)
   *    for both stacks
   */
  void drawScoringZone(zonePos pos, std::pair<color,color> contents, std::pair<uint8_t,uint8_t> stackHeight);

  /**
   * draw the four colored tiles
   */
  void drawcoloredTiles();

  /**
   * draw the zone lines
   */
  void drawLines();

  /**
   * re-print the perimeter to make it look nice
   *
   * note: should be called after drawcoloredTiles(), drawLines(), and drawScoringZone()s,
   * but before drawtowers()s
   */
  void reinforcePerimeter();

  /**
   * draw the robot on the screen
   *
   * @param red true for red, false for blue
   * @param pos y-value of the midpoint of the robot
   * note: there are 40 pixels for each field tile
   */
  void drawRobot(bool red, uint8_t pos);

  /**
   * to be called after drawing all towers, cubes, and scoring zones
   * this will automatically print all other game elements
   */
  void finishDrawing();

  private:
  //Do not try and draw cubes youself, use the above functions
  void drawCube(std::pair<uint8_t, uint8_t> pos, color color, uint8_t stackHeight, bool targeted);
  static void drawCube(lv_obj_t *parent, std::pair<uint8_t, uint8_t> pos, color color, uint8_t stackHeight, bool targeted);

  void resetVectors();

  const uint numOfBits[16] = {0,1,1,2,1,2,2,3,
                              1,2,2,3,2,3,3,4};

  lv_obj_t *obj;

  bool autoInit;

  bool wallDrawn;
  std::pair<color, color> allianceTowerContents;

  std::vector<cubeSector> cubesToDraw;
  std::vector<towerPos> towersToDraw;
  std::vector<zonePos> zonesToDraw;
};

}//namespace screen

#endif
