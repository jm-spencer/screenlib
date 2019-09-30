#include "screen/dataMonitors/textBarMonitor.hpp"
#include <iomanip>
#include <iostream>

namespace screen {

TextBarMonitor::TextBarMonitor(lv_obj_t *parent, const char *icaption, std::string iunit,
                               double min, double max, uint16_t ianimTime, double ibarSize,
                               lv_style_t *captionStyle, lv_style_t *dataStyle,
                               std::shared_ptr<okapi::ControllerOutput<double>> ioutput):
    unit(iunit), prec(3), animTime(ianimTime), barSize(ibarSize), BaseMonitor(parent, captionStyle, ioutput){

  cap = lv_label_create(obj, NULL);
  lv_label_set_long_mode(cap, LV_LABEL_LONG_CROP);
  lv_label_set_align(cap, LV_LABEL_ALIGN_CENTER);
  lv_label_set_style(cap, captionStyle);
  lv_label_set_text(cap, icaption);

  data = lv_label_create(obj, cap);
  lv_obj_set_style(data, dataStyle);

  bar = lv_bar_create(obj, NULL);
  lv_bar_set_style(bar, LV_BAR_STYLE_BG, captionStyle);
  lv_bar_set_style(bar, LV_BAR_STYLE_INDIC, dataStyle);
  lv_bar_set_range(bar, min, max);

  align();
}

TextBarMonitor::~TextBarMonitor()
{
  lv_obj_del(cap);
  lv_obj_del(data);
  lv_obj_del(bar);
}

void TextBarMonitor::controllerSet(double ivalue)
{
  dataStr.str("");
  dataStr << std::setprecision(prec) << ivalue << unit;
  lv_label_set_text(data, dataStr.str().c_str());

  lv_bar_set_value_anim(bar, ivalue, animTime);

  if (output) output->controllerSet(ivalue);
}

void TextBarMonitor::setPrecision(uint8_t iprec){
  prec = iprec;
}

void TextBarMonitor::align(){
  lv_obj_set_width(cap, 100 * xScalar);
  lv_obj_align(cap, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);
  lv_obj_set_size(bar, 100 * xScalar, barSize * yScalar);
  lv_obj_align(bar, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_obj_set_width(data, 100 * xScalar);
  lv_obj_align(data, bar, LV_ALIGN_OUT_TOP_MID, 0, 0);
}


}
