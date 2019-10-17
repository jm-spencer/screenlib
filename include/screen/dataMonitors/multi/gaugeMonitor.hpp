#ifndef GAUGE_MONITOR_HPP_
#define GAUGE_MONITOR_HPP_
#include "screen/dataMonitors/multi/multiMonitor.hpp"

namespace screen {

class GaugeEntry : public MonitorEntry {
public:

  GaugeEntry(lv_obj_t *igauge, uint8_t iid, lv_color_t *icolorArr);

  GaugeEntry *with

  virtual void controllerSet(double ivalue) override;

protected:
  lv_obj_t *gauge;
  uint8_t id;
  lv_color_t *colorArr;
};

class GaugeMonitor : public MultiMonitor<GaugeEntry> {
public:
  GaugeMonitor(lv_obj_t *parent, lv_style_t *bgStyle = &lv_style_transp, uint8_t maxEntries = 8);

  ~GaugeMonitor();

  virtual GaugeEntry *makeEntry() override;

  virtual void align() override;

protected:

  lv_obj_t *gauge;
  lv_color_t *colorArr;
};

}

#endif
