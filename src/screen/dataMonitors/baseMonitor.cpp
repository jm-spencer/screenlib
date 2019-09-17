#include "screen/dataMonitors/baseMonitor.hpp"

namespace screen {

BaseMonitor::BaseMonitor(lv_obj_t *parent, uint32_t ilength,
                         std::shared_ptr<okapi::ControllerOutput<double>> ioutput)
    : output(ioutput), scalar(ilength / 40.0)
{
  obj = lv_cont_create(parent, NULL);
  lv_obj_set_size(obj, ilength, ilength);
}

BaseMonitor::~BaseMonitor()
{
  lv_obj_del(obj);
}

void BaseMonitor::setX(int x)
{
  lv_obj_set_x(obj, x);
}

void BaseMonitor::setY(int y)
{
  lv_obj_set_y(obj, y);
}

void BaseMonitor::setPos(int x, int y)
{
  lv_obj_set_pos(obj, x, y);
}

void BaseMonitor::hide(bool hide)
{
  lv_obj_set_hidden(obj, hide);
}

void BaseMonitor::setSideLength(uint32_t ilength)
{
  lv_obj_set_size(obj, ilength, ilength);
  scalar = ilength / 40.0;
}

}  // namespace screen
