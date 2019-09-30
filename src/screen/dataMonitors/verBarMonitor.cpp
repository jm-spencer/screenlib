#include "screen/dataMonitors/verBarMonitor.hpp"
#include <iomanip>
#include <algorithm>


namespace screen {

VerBarEntry::VerBarEntry(lv_obj_t *ibar, lv_obj_t *idata):
    bar(ibar), data(idata){
  lv_label_set_align(data, LV_LABEL_ALIGN_CENTER);
}

VerBarEntry::~VerBarEntry(){
  lv_obj_del(bar);
  lv_obj_del(data);
}

VerBarEntry *VerBarEntry::withPrecision(uint8_t iprec){
  prec = iprec;
  return this;
}

VerBarEntry *VerBarEntry::withUnit(std::string iunit){
  unit = iunit;
  return this;
}

VerBarEntry *VerBarEntry::withBounds(double imin, double imax){
  min = imin;
  range = imax - imin;
  return this;
}

VerBarEntry *VerBarEntry::withBarWidth(uint16_t iwidth){
  lv_obj_set_width(bar, iwidth);
  return this;
}

VerBarEntry *VerBarEntry::withBarPadding(double ipadding){
  padding = ipadding;
  return this;
}

VerBarEntry *VerBarEntry::withStyle(lv_style_t *style){
  lv_obj_set_style(bar, style);
  lv_label_set_style(data, style);
  return this;
}

VerBarEntry *VerBarEntry::withOutput(std::shared_ptr<okapi::ControllerOutput<double>> ioutput){
  output = ioutput;
  return this;
}

void VerBarEntry::setYScalar(double iyScalar){

}

void VerBarEntry::controllerSet(double ivalue){
  dataStr.str("");
  dataStr << std::setprecision(prec) << ivalue << unit;
  lv_label_set_text(data, dataStr.str().c_str());

  lv_obj_set_height(bar, (std::clamp(ivalue, min, min + range) - (min + (range * padding))) *
                         (lv_obj_get_height(lv_obj_get_parent(bar)) / (range * (1 + 2 * padding))));

  align();

  if (output) output->controllerSet(ivalue);
}

void VerBarEntry::align(){
  lv_obj_align(bar, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  lv_obj_align(data, bar, LV_ALIGN_IN_TOP_MID, 0, lv_obj_get_height(data) / -2);
}



VerBarMonitor::VerBarMonitor(lv_obj_t *parent, lv_style_t *bgStyle):
    BaseObject(parent, bgStyle){}

VerBarMonitor::~VerBarMonitor(){
  for (auto ent : entries){
    delete ent;
  }
}

VerBarEntry *VerBarMonitor::makeEntry(){
  auto out = new VerBarEntry(
    lv_obj_create(obj, NULL), lv_label_create(obj, NULL)
  );
  out->setYScalar(yScalar);

  entries.push_back(out);
  return out;
}

void VerBarMonitor::align(){
  for (auto ent : entries){
    ent->setYScalar(yScalar);
  }
}

}
