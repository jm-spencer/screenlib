#ifndef HOR_BAR_MONITOR_HPP_
#define HOR_BAR_MONITOR_HPP_
#include "screen/dataMonitors/multi/multiMonitor.hpp"
#include <sstream>

namespace screen {

class HorBarEntry : public MonitorEntry {
public:
  HorBarEntry(lv_obj_t *ibar, lv_obj_t *idata);

  ~HorBarEntry();

  HorBarEntry *withPrecision(uint8_t iprec);

  HorBarEntry *withUnit(std::string iunit);

  HorBarEntry *withBounds(double imin, double imax);

  HorBarEntry *withBarHeight(uint16_t iheight);

  HorBarEntry *withBarPadding(double ipadding);

  HorBarEntry *withStyle(lv_style_t *style);

  HorBarEntry *withOutput(std::shared_ptr<okapi::ControllerOutput<double>> ioutput);

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



class HorBarMonitor : public MultiMonitor<HorBarEntry> {
public:
  HorBarMonitor(lv_obj_t *parent, lv_style_t *bgStyle = &lv_style_transp);

  ~HorBarMonitor();

  virtual HorBarEntry *makeEntry() override;

  virtual void align() override;

};

}

#endif
