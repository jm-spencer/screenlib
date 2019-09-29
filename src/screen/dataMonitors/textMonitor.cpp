#include "screen/dataMonitors/textMonitor.hpp"
#include <iomanip>

namespace screen {

TextMonitor::TextMonitor(lv_obj_t *parent, const char *icaption, std::string iunit,
                         lv_style_t *captionStyle, lv_style_t *dataStyle,
                         std::shared_ptr<okapi::ControllerOutput<double>> ioutput)
    : unit(iunit), prec(3), BaseMonitor(parent, ioutput)
{
  lv_obj_set_style(obj, captionStyle);

  cap = lv_label_create(obj, NULL);
  lv_label_set_long_mode(cap, LV_LABEL_LONG_CROP);
  lv_label_set_align(cap, LV_LABEL_ALIGN_CENTER);
  lv_label_set_style(cap, captionStyle);
  lv_label_set_text(cap, icaption);

  data = lv_label_create(obj, cap);
  lv_obj_set_style(data, dataStyle);

  align();
}

TextMonitor::~TextMonitor()
{
  lv_obj_del(cap);
  lv_obj_del(data);
}

void TextMonitor::controllerSet(double ivalue)
{
  dataStr.str("");
  dataStr << std::setprecision(prec) << ivalue << unit;
  lv_label_set_text(data, dataStr.str().c_str());

  if (output) output->controllerSet(ivalue);
}

void TextMonitor::setPrecision(uint8_t iprec){
  prec = iprec;
}

void TextMonitor::align(){
  lv_obj_set_width(cap, 100 * xScalar);
  lv_obj_align(cap, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_obj_set_width(data, 100 * xScalar);
  lv_obj_align(data, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
}

}  // namespace screen
