#ifndef BASE_MONITOR_HPP_
#define BASE_MONITOR_HPP_
#include <memory>
#include "okapi/api/control/controllerOutput.hpp"
#include "screen/resources.hpp"

namespace screen {

class BaseMonitor : okapi::ControllerOutput<double> {
 public:
  /**
   * Base class for anything that displays changing data
   *
   * @param parent  an object which will contain the monitor
   * @param ilength the side length of the monitor
   * @param ioutput will passthrough the input value to this
   */
  BaseMonitor(lv_obj_t *parent, std::shared_ptr<okapi::ControllerOutput<double>> ioutput = nullptr);

  ~BaseMonitor();

  /**
   * Set new x position of the monitor on the screen
   *
   * @param x new x-value of the distance from the leftmost side of the screen
   *    (screen is 480 pixels wide)
   */
  void setX(int x);

  /**
   * Set new y position of the monitor on the screen
   *
   * @param y new y-value of the distance from the top side of the screen
   *    (screen is 240 pixels tall)
   */
  void setY(int y);

  /**
   * Set new position of the monitor on the screen
   *
   * note: the default(if this is never called) is 120,0 (centered)
   *
   * @param x new x-value of the distance from the leftmost side of the screen
   *    (screen is 480 pixels wide)
   * @param y new y-value of the distance from the top side of the screen
   *    (screen is 240 pixels tall)
   */
  void setPos(int x, int y);

  /* Hide the monitor
   *
   * @param hide whether to hide the monitor
   */
  void hide(bool hide);

  /**
   * Set the new width of the monitor
   */
  void setWidth(uint32_t iwidth);

  /**
   * Set the new height of the monitor
   */
  void setHeight(uint32_t iheight);

  /**
   * Set the new width and height of the monitor
   */
  void setSize(uint32_t iwidth, uint32_t iheight);

  /**
   * Give the monitor its next value
   * Will pass the value through to its output, if it exists
   *
   * @param ivalue the new value
   */
  virtual void controllerSet(double ivalue) = 0;

 protected:
  std::shared_ptr<okapi::ControllerOutput<double>> output{nullptr};

  lv_obj_t *obj;

  double xScalar, yScalar;
};

}  // namespace screen
#endif
