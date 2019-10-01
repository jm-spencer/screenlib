#ifndef MULTI_MONITOR_HPP_
#define MULTI_MONITOR_HPP_
#include "okapi/api/control/controllerOutput.hpp"
#include "screen/util/baseObject.hpp"
#include <memory>
#include <vector>

namespace screen {

class MonitorEntry : public okapi::ControllerOutput<double> {
protected:

  std::shared_ptr<okapi::ControllerOutput<double>> output{nullptr};

};

template <typename T>
class MultiMonitor : public BaseObject {
public:

  MultiMonitor(lv_obj_t *parent, lv_style_t *bgStyle):
    BaseObject(parent, bgStyle){}

  virtual T *makeEntry() = 0;

protected:

  std::vector<T*> entries;

};

}

#endif
