#ifndef BASE_OBJECT_HPP_
#define BASE_OBJECT_HPP_
#include "screen/resources.hpp"

namespace screen {

class BaseObject {
 public:
  /**
   * Base class for anything that displays changing data
   *
   * @param parent  an object which will contain the object
   * @param ilength the side length of the object
   * @param ioutput will passthrough the input value to this
   */
  BaseObject(lv_obj_t *parent, lv_style_t *bgStyle);

  ~BaseObject();

  /**
   * Set new x position of the object on the screen
   *
   * @param x new x-value of the distance from the leftmost side of the screen
   *    (screen is 480 pixels wide)
   */
  void setX(int x);

  /**
   * Set new y position of the object on the screen
   *
   * @param y new y-value of the distance from the top side of the screen
   *    (screen is 240 pixels tall)
   */
  void setY(int y);

  /**
   * Set new position of the object on the screen
   *
   * note: the default(if this is never called) is 120,0 (centered)
   *
   * @param x new x-value of the distance from the leftmost side of the screen
   *    (screen is 480 pixels wide)
   * @param y new y-value of the distance from the top side of the screen
   *    (screen is 240 pixels tall)
   */
  void setPos(int x, int y);

  /* Hide the object
   *
   * @param hide whether to hide the object
   */
  void hide(bool hide);

  /**
   * Set the new width of the object
   */
  void setWidth(uint32_t iwidth);

  /**
   * Set the new height of the object
   */
  void setHeight(uint32_t iheight);

  /**
   * Set the new width and height of the object
   */
  void setSize(uint32_t iwidth, uint32_t iheight);

protected:
  virtual void align() = 0;

  lv_obj_t *obj;

  double xScalar, yScalar;
};

}  // namespace screen
#endif
