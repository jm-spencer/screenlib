#include "screen/dataMonitors/multi/gaugeMonitor.hpp"

namespace screen {

GaugeEntry::GaugeEntry(lv_obj_t *igauge, uint8_t iid, lv_color_t *icolorArr):
  gauge(igauge), id(iid), colorArr(icolorArr){}

void GaugeEntry::controllerSet(double ivalue){
  lv_gauge_set_value(gauge, id, ivalue);

  if (output) output->controllerSet(ivalue);
}

GaugeMonitor::GaugeMonitor(lv_obj_t *parent, lv_style_t *bgStyle, uint8_t maxEntries):
    MultiMonitor(parent, bgStyle){
  gauge = lv_gauge_create(obj, NULL);
  colorArr = new lv_color_t[maxEntries];

  align();
}

GaugeMonitor::~GaugeMonitor(){
  for (auto ent : entries){
    delete ent;
  }

  lv_obj_del(gauge);
  delete colorArr;
}

GaugeEntry *GaugeMonitor::makeEntry(){
  static uint8_t id = 0;

  colorArr[id] = LV_COLOR_BLACK;
  GaugeEntry *out = new GaugeEntry(gauge, id, colorArr);
  entries.push_back(out);

  id++;
  return out;
}

void GaugeMonitor::align(){
  lv_obj_align(gauge, NULL, LV_ALIGN_CENTER, 0, 0);
}

}
