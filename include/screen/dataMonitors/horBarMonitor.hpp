#ifndef HOR_BAR_MONITOR_HPP_
#define HOR_BAR_MONITOR_HPP_
#include "screen/dataMonitors/baseMonitor.hpp"
#include "screen/resources.hpp"
#include <sstream>

namespace screen {

class HorBarMonitor : public BaseMonitor {
public:
  HorBarMonitor(lv_obj_t *parent, std::string iunit = "", double imin = 0, double imax = 100,
                uint16_t ibarHeight = 240, double barPadding = 0,
                lv_style_t *bgStyle = &lv_style_transp, lv_style_t *indicStyle = &lv_style_pretty_color,
                std::shared_ptr<okapi::ControllerOutput<double>> ioutput = nullptr);

  ~HorBarMonitor();

  virtual void controllerSet(double ivalue) override;

  void setPrecision(uint8_t iprec);
protected:
   virtual void align() override;

   std::string unit;
   std::stringstream dataStr;
   uint8_t prec;

   uint16_t barHeight;

   double min, range;

   lv_obj_t *bar;
   lv_obj_t *data;
};

}

#endif
