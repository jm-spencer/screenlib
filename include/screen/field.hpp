#ifndef SCREEN_FIELD_HPP_
#define SCREEN_FIELD_HPP_
#include <vector>
#include "screen/resources.hpp"

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

/**
 * See Field.png on https://github.com/SpencerJ21/screenlib
 *
 * Each of the cube group names are in screen::cubeGroup,
 * each of the tower names are in screen::tower, and
 * each of the scoring zone names are in screen::scoringZone
 *
 * The numbers on the cube show the bit that represents them in their bitfield:
 * a 0 means it's looking at bit 0: 0b0000X
 * a 1 means it's looking at bit 1: 0b000X0
 * and so on.
 *
 * This is done so the presence of every cube in a group can be given by a number
 * say you want the cubes labeled 3, 1, and 0, the bitfield would be 0b01011
 *
 * For the stacks near the middle, the cubes in the stack but not on top, are still represented by
 * the bits that follow the top cube's bit (the 3 cubes under a cube on bit 3 are represented by
 * bits 2, 1, and 0)
 *
 * Alternatively, macros can be used for more verbose code; here is the equivalent of the previous
 * example: field.draw(screen::cubeGroup::right4, CUBE_HIGHEST + CUBE_2LOWEST);
 *
 * CUBE_HIGHEST represents the highest cube in the stack, followed by CUBE_2HIGHEST (the 2nd
 * highest), followed by CUBE_2LOWEST (the 2nd lowest), and finally CUBE_LOWEST As the 4 cube stacks
 * on the left and right are in the same order but slightly different positions
 *
 * CUBE_FAR and CUBE_NEAR are for the cube Groups farLeft and farRight
 *
 * CUBE_TOP_NEAR, CUBE_FAR_LEFT, CUBE_NEAR_LEFT, CUBE_FAR_RIGHT, and CUBE_NEAR_RIGHT are used for
 * the five cube stack on the near side
 *
 * and finally, all macros starting with TOWER_CUBE_ refer to the cubes around a tower
 *
 *
 * Scored cubes are drawn along with where they are, either in a tower or a scoring zone. In a tower
 * the second parameter describes the color of the cube, (screen::color::). In a scoring zone the
 * second parameter does the same however, two colors can be placed in an array to denote two
 * stacks. In addition, a third parameter is used to display "stack height", a number printed on top
 * to describe how many cubes are in the stack. Note: use `screen::color::none` to abstain from
 * printing a scored cube in that position
 */

namespace screen {

class Field {
 public:
  /**
   * A struct that controls the drawing of numbers on cubes (which represent height)
   *
   * deltaX how far to move the number horizontally from default
   * deltaY how far to move the number vertically from default
   * fontStyle which style to use; can be used to change the font, color, etc. of the number
   */
  struct NumberConfig {
    int deltaX, deltaY;
    lv_style_t *fontStyle;
  };

  /**
   * Field generator for the screen
   *
   * @param parent LVGL object to place upon
   * @param ilength the side length of the field (in both directions)
   * @param iautoInit print colored tiles / taped lines immediately, and after each clean
   * @param iconfig a configuration for the numbers on the cubes,
   *    use deltaX and deltaY to adjust the position of the number, and set a different
   *    style using fontStyle
   */
  Field(lv_obj_t *parent, double ilength = 240, bool iautoInit = true,
        NumberConfig iconfig = {1, -1, &littleWhiteText});
  ~Field();

  /**
   * Remove all objects from the field, and reset to default
   */
  void clean();

  /**
   * Set new x position of the field on the screen
   *
   * @param x new x-value of the distance from the leftmost side of the screen
   *    (screen is 480 pixels wide)
   */
  void setX(int x);

  /**
   * Set new y position of the field on the screen
   *
   * @param y new y-value of the distance from the top side of the field
   *    (screen is 240 pixels tall)
   */
  void setY(int y);

  /**
   * Set new position of the field on the screen
   *
   * note: the default(if this is never called) is 120,0 (centered)
   *
   * @param x new x-value of the distance from the leftmost side of the screen
   *    (screen is 480 pixels wide)
   * @param y new y-value of the distance from the top side of the field
   *    (screen is 240 pixels tall)
   */
  void setPos(int x, int y);

  /**
   * Set the new width and height of the field
   *
   * this will clean the screen and remove all existing objects
   *
   * note: you can make the field larger than the screen,
   *    but you would then need a way to move the screen around in order to see it
   */
  void setSideLength(uint ilength);

  /**
   * draw a group of cubes
   *
   * @param pos which group of cubes to print - see resources.hpp
   * @param presence a bitfield of present cubes. Starts at highest cube as the highest bit,
   *    or furthest, or leftmost, depending on which group. See the README for more information
   */
  void draw(cubeGroup pos, uint8_t presence = UINT8_MAX);

  /**
   * draw a tower and group of cubes around it
   *
   * @param pos which tower to print - see resources.hpp
   * @param contents what color cube is inside, set color::none for no cube
   * @param presence a bitfield of present cubes. Starts with furthest and moves clockwise
   *    See the README for more information
   */
  void draw(tower pos, color contents = color::none, uint8_t cubePresence = UINT8_MAX);

  /**
   * draw a scoring zone (and cubes inside)
   *
   * @param pos which zone to print
   * @param contents what color cube is inside, set color::none for no cube
   * @param stackHeight how many cubes are in the zone vertically (puts number on top)
   *    See the README for more information
   */
  void draw(scoringZone pos, color contents = color::none, uint8_t stackHeight = 0);

  /**
   * draw a scoring zone (and cubes inside)
   *
   * @param pos which zone to print
   * @param contents what colors of cubes are inside, use other function for 0 or 1 cubes
   * @param stackHeight how many cubes are in the zone vertically (puts number on top)
   *    for both stacks. See the README for more information
   */
  void draw(scoringZone pos, std::pair<color, color> contents,
            std::pair<uint8_t, uint8_t> stackHeight);

  /**
   * draw the four colored tiles
   *
   * called automatically by default
   */
  void drawColoredTiles();

  /**
   * draw the zone lines
   *
   * called automatically by default
   */
  void drawLines();

  /**
   * re-print the perimeter to make it look nice
   *
   * called automatically assuming you are drawing the whole field
   * calling this manually is not advised
   *
   * note: should be called after drawcoloredTiles(), drawLines(), and draw()s,
   * but before draw()s
   */
  void reinforcePerimeter();

  /**
   * draw the robot on the screen
   *
   * @param red true for red, false for blue
   * @param pos y-value of the midpoint of the robot
   *    note: every 40 given to pos represents 1 field tile
   */
  void drawRobot(bool red, uint8_t pos);

  /**
   * to be called after drawing all towers, cubes, and scoring zones
   * this will automatically print all other game elements
   *
   * this is the suggested way to finish the field, as it will ensure everything is drawn in the
   * correct order
   */
  void finishDrawing();

 private:
  // Cubes should be drawn automatically by the above functions
  void drawCube(std::pair<uint8_t, uint8_t> pos, color color, uint8_t stackHeight, bool targeted);

  static void drawCube(lv_obj_t *parent, std::pair<uint8_t, uint8_t> pos, double scalar,
                       color color, uint8_t stackHeight, NumberConfig config, bool targeted);

  int scale(int original);

  void resetVectors();

  const uint numOfBits[16] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};

  lv_obj_t *obj;

  bool autoInit;
  double scalar;

  bool wallDrawn;
  std::pair<color, color> allianceTowerContents;

  std::vector<cubeGroup> cubesToDraw;
  std::vector<tower> towersToDraw;
  std::vector<scoringZone> zonesToDraw;

  NumberConfig config;
};

}  // namespace screen

#endif
