#include "screen/dataMonitors/verBarMonitor.hpp"
#include <iomanip>


namespace screen {

VerBarMonitor::VerBarMonitor(lv_obj_t *parent, std::string iunit, double imin, double imax,
                             lv_style_t *style, uint16_t ibarWidth,
                             std::shared_ptr<okapi::ControllerOutput<double>> ioutput):
                             unit(iunit), prec(3), barWidth(ibarWidth), min(imin), range(.01 * (imax - imin)), BaseMonitor(parent, ioutput){

  bar = lv_obj_create(obj, NULL);
  lv_obj_set_style(bar, style);
  lv_obj_set_width(bar, barWidth);

  data = lv_label_create(obj, NULL);
  lv_label_set_long_mode(data, LV_LABEL_LONG_CROP);
  lv_label_set_align(data, LV_LABEL_ALIGN_CENTER);
  lv_label_set_style(data, style);

  align();
}

VerBarMonitor::~VerBarMonitor(){
  lv_obj_del(bar);
  lv_obj_del(data);
}

void VerBarMonitor::controllerSet(double ivalue){
  dataStr.str("");
  dataStr << std::setprecision(prec) << ivalue << unit;
  lv_label_set_text(data, dataStr.str().c_str());

  lv_obj_set_height(bar, (ivalue - min) * (yScalar / range));
  lv_obj_align(bar, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);


  if (output) output->controllerSet(ivalue);
}

void VerBarMonitor::setPrecision(uint8_t iprec){
  prec = iprec;
}

void VerBarMonitor::align(){
  lv_obj_align(bar, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_obj_align(data, bar, LV_ALIGN_OUT_TOP_MID, 0, 0);
}

}
