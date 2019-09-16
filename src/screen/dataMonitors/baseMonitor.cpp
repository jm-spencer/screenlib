#include "screen/dataMonitors/baseMonitor.hpp"

namespace screen {

BaseMonitor::BaseMonitor(lv_obj_t *parent, std::shared_ptr<okapi::ControllerOutput<double>> ioutput):
  output(ioutput)
{
  obj = lv_cont_create(parent, NULL);
}

void BaseMonitor::hide(bool hide)
{
  lv_obj_set_hidden(obj, hide);
}

}
