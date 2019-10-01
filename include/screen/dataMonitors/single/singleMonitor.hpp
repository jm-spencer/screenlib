#ifndef SINGLE_MONITOR_HPP_
#define SINGLE_MONITOR_HPP_
#include "okapi/api/control/controllerOutput.hpp"
#include "screen/util/baseObject.hpp"
#include <memory>

namespace screen {

class SingleMonitor : public BaseObject, public okapi::ControllerOutput<double> {
public:

 SingleMonitor(lv_obj_t *parent, lv_style_t *bgStyle, std::shared_ptr<okapi::ControllerOutput<double>> ioutput = nullptr):
  output(ioutput), BaseObject(parent, bgStyle){}

 virtual void controllerSet(double ivalue) = 0;

protected:
  virtual void align() = 0;

  std::shared_ptr<okapi::ControllerOutput<double>> output;
};

}

#endif
