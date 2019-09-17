#include "screen/dataMonitors/textMonitor.hpp"

namespace screen {

TextMonitor::TextMonitor(lv_obj_t *parent, std::string icaption, std::string iunit,
                         lv_style_t *captionStyle, lv_style_t *dataStyle,
                         std::shared_ptr<okapi::ControllerOutput<double>> ioutput)
    : unit(iunit), BaseMonitor(parent, ioutput)
{
  lv_obj_set_style(obj, captionStyle);

  cap = lv_label_create(obj, NULL);
  lv_label_set_style(cap, captionStyle);
  lv_obj_align(cap, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_label_set_align(cap, LV_LABEL_ALIGN_CENTER);
  lv_label_set_text(cap, icaption.c_str());

  data = lv_label_create(obj, NULL);
  lv_obj_set_style(data, dataStyle);
  lv_obj_align(data, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_label_set_align(data, LV_LABEL_ALIGN_CENTER);
}

TextMonitor::~TextMonitor()
{
  lv_obj_del(cap);
  lv_obj_del(data);
}

void TextMonitor::controllerSet(double ivalue)
{
  lv_label_set_text(data, (std::to_string(ivalue) + unit).c_str());

  output->controllerSet(ivalue);
}

}  // namespace screen
