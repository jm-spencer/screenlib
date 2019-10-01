#ifndef VER_BAR_MONITOR_HPP_
#define VER_BAR_MONITOR_HPP_
#include "screen/dataMonitors/multi/multiMonitor.hpp"
#include <sstream>

namespace screen {

class VerBarEntry : public MonitorEntry {
public:
  VerBarEntry(lv_obj_t *ibar, lv_obj_t *idata);

  ~VerBarEntry();

  VerBarEntry *withPrecision(uint8_t iprec);

  VerBarEntry *withUnit(std::string iunit);

  VerBarEntry *withBounds(double imin, double imax);

  VerBarEntry *withBarWidth(uint16_t iwidth);

  VerBarEntry *withBarPadding(double ipadding);

  VerBarEntry *withStyle(lv_style_t *style);

  VerBarEntry *withOutput(std::shared_ptr<okapi::ControllerOutput<double>> ioutput);

  virtual void controllerSet(double ivalue) override;

  void align();

protected:
  std::string unit{""};
  std::stringstream dataStr;
  uint8_t prec{3};

  double min{0}, range{100}, padding{0};

  lv_obj_t *bar{nullptr};
  lv_obj_t *data{nullptr};
};



class VerBarMonitor : public MultiMonitor<VerBarEntry> {
public:
  VerBarMonitor(lv_obj_t *parent, lv_style_t *bgStyle = &lv_style_transp);

  ~VerBarMonitor();

  virtual VerBarEntry *makeEntry() override;

  virtual void align() override;
};

}

#endif
