#include "screen/dataMonitors/multi/horBarMonitor.hpp"
#include <iomanip>
#include <algorithm>


namespace screen {

HorBarEntry::HorBarEntry(lv_obj_t *ibar, lv_obj_t *idata):
    bar(ibar), data(idata){
  lv_label_set_align(data, LV_LABEL_ALIGN_CENTER);
}

HorBarEntry::~HorBarEntry(){
  lv_obj_del(bar);
  lv_obj_del(data);
}

HorBarEntry *HorBarEntry::withPrecision(uint8_t iprec){
  prec = iprec;
  return this;
}

HorBarEntry *HorBarEntry::withUnit(std::string iunit){
  unit = iunit;
  return this;
}

HorBarEntry *HorBarEntry::withBounds(double imin, double imax){
  min = imin;
  range = imax - imin;
  return this;
}

HorBarEntry *HorBarEntry::withBarHeight(uint16_t iheight){
  lv_obj_set_height(bar, iheight);
  return this;
}

HorBarEntry *HorBarEntry::withBarPadding(double ipadding){
  padding = ipadding;
  return this;
}

HorBarEntry *HorBarEntry::withStyle(lv_style_t *style){
  lv_obj_set_style(bar, style);
  lv_label_set_style(data, style);
  return this;
}

HorBarEntry *HorBarEntry::withOutput(std::shared_ptr<okapi::ControllerOutput<double>> ioutput){
  output = ioutput;
  return this;
}

void HorBarEntry::controllerSet(double ivalue){
  dataStr.str("");
  dataStr << std::setprecision(prec) << ivalue << unit;
  lv_label_set_text(data, dataStr.str().c_str());

  lv_obj_set_width(bar, (std::clamp(ivalue, min, min + range) - (min + (range * padding))) *
                         (lv_obj_get_width(lv_obj_get_parent(bar)) / (range * (1 + 2 * padding))));

  align();

  if (output) output->controllerSet(ivalue);
}

void HorBarEntry::align(){
  lv_obj_align(bar, NULL, LV_ALIGN_IN_LEFT_MID, 0, 0);
  lv_obj_align(data, bar, LV_ALIGN_IN_RIGHT_MID, lv_obj_get_width(data) / 2, 0);
}



HorBarMonitor::HorBarMonitor(lv_obj_t *parent, lv_style_t *bgStyle):
    MultiMonitor(parent, bgStyle){}

HorBarMonitor::~HorBarMonitor(){
  for (auto ent : entries){
    delete ent;
  }
}

HorBarEntry *HorBarMonitor::makeEntry(){
  auto out = new HorBarEntry(
    lv_obj_create(obj, NULL), lv_label_create(obj, NULL)
  );

  out->align();

  entries.push_back(out);
  return out;
}

void HorBarMonitor::align(){
  for (auto ent : entries){
    ent->align();
  }
}

}
