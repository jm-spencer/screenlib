#include "screen/dataMonitors/textMonitor.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

namespace screen {

TextMonitor::TextMonitor(lv_obj_t *parent, const char *icaption, std::string iunit,
                         lv_style_t *captionStyle, lv_style_t *dataStyle,
                         std::shared_ptr<okapi::ControllerOutput<double>> ioutput)
    : unit(iunit), BaseMonitor(parent, ioutput)
{
  lv_obj_set_style(obj, captionStyle);

  cap = lv_label_create(obj, NULL);
  lv_label_set_style(cap, captionStyle);
  lv_label_set_align(cap, LV_LABEL_ALIGN_LEFT);
  lv_label_set_text(cap, icaption);

  data = lv_label_create(obj, NULL);
  lv_obj_set_style(data, dataStyle);
  lv_label_set_align(data, LV_LABEL_ALIGN_LEFT);

  align();
}

TextMonitor::~TextMonitor()
{
  lv_obj_del(cap);
  lv_obj_del(data);
}

void TextMonitor::controllerSet(double ivalue)
{
  lv_label_set_text(data, (std::to_string(ivalue).substr(0, 3) + unit).c_str());
  //std::stringstream dataStr;
  //dataStr << std::setprecision(3) << ivalue << unit;
  //lv_label_set_text(data, dataStr.str().c_str());

  if (output) output->controllerSet(ivalue);
}

void TextMonitor::align(){
  lv_obj_align(cap, NULL, LV_ALIGN_IN_TOP_LEFT, 5, 0);
  lv_obj_align(data, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 5, 0);
}

}  // namespace screen
