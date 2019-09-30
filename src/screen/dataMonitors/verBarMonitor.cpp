#include "screen/dataMonitors/verBarMonitor.hpp"
#include <iomanip>
#include <algorithm>
#include <iostream>


namespace screen {

VerBarMonitor::VerBarMonitor(lv_obj_t *parent, std::string iunit, double imin, double imax, uint16_t ibarWidth, double barPadding,
                             lv_style_t *bgStyle, lv_style_t *indicStyle,
                             std::shared_ptr<okapi::ControllerOutput<double>> ioutput):
                             unit(iunit), prec(3), barWidth(ibarWidth), min((1 + barPadding) * imin - (barPadding * imax)), range((1 + 2 *barPadding) * (imax - imin)), BaseMonitor(parent, bgStyle, ioutput){
  bar = lv_obj_create(obj, NULL);
  lv_obj_set_style(bar, indicStyle);
  lv_obj_set_width(bar, barWidth);

  data = lv_label_create(obj, NULL);
  lv_label_set_style(data, indicStyle);
  lv_label_set_align(data, LV_LABEL_ALIGN_CENTER);

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

  lv_obj_set_height(bar, (std::clamp(ivalue, min, min + range) - min) * (100 * yScalar / range));

  align();


  if (output) output->controllerSet(ivalue);
}

void VerBarMonitor::setPrecision(uint8_t iprec){
  prec = iprec;
}

void VerBarMonitor::align(){
  lv_obj_align(bar, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_obj_align(data, bar, LV_ALIGN_IN_TOP_MID, 0, lv_obj_get_height(data) / -2);
}

}
