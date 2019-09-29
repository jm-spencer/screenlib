#include "screen/dataMonitors/baseMonitor.hpp"

namespace screen {

BaseMonitor::BaseMonitor(lv_obj_t *parent, std::shared_ptr<okapi::ControllerOutput<double>> ioutput)
    : output(ioutput), xScalar(1), yScalar(1)
{
  obj = lv_cont_create(parent, NULL);
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

void BaseMonitor::setWidth(uint32_t iwidth)
{
  lv_obj_set_width(obj, iwidth);
  xScalar = iwidth / 100.0;
  align();
}

void BaseMonitor::setHeight(uint32_t iheight)
{
  lv_obj_set_height(obj, iheight);
  yScalar = iheight / 100.0;
  align();
}

void BaseMonitor::setSize(uint32_t iwidth, uint32_t iheight)
{
  lv_obj_set_size(obj, iwidth, iheight);
  xScalar = iwidth / 100.0;
  yScalar = iheight / 100.0;
  align();
}

}  // namespace screen
