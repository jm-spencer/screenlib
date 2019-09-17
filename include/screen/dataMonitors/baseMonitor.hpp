#ifndef BASE_MONITOR_HPP_
#define BASE_MONITOR_HPP_
#include "okapi/api/control/controllerOutput.hpp"
#include "screen/resources.hpp"
#include <memory>

namespace screen {

class BaseMonitor : okapi::ControllerOutput<double>{
public:

  /**
   * Base class for anything that displays changing data
   *
   * @param parent  an object which will contain the monitor
   * @param ioutput will passthrough the input value to this
   */
  BaseMonitor(lv_obj_t *parent, std::shared_ptr<okapi::ControllerOutput<double>> ioutput = nullptr);

  ~BaseMonitor();
  
  /* Hide the monitor
   *
   * @param hide whether to hide the field
   */
  void hide(bool hide);

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
};

}
#endif
