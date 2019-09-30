#ifndef VER_BAR_MONITOR_HPP_
#define VER_BAR_MONITOR_HPP_
#include "screen/dataMonitors/baseMonitor.hpp"
#include "screen/resources.hpp"
#include <sstream>

namespace screen {

class VerBarMonitor : public BaseMonitor {
public:
  VerBarMonitor(lv_obj_t *parent, std::string iunit = "", double imin = 0, double imax = 100,
                lv_style_t *style = &lv_style_plain_color,
                uint16_t ibarWidth = 480,
                std::shared_ptr<okapi::ControllerOutput<double>> ioutput = nullptr);

  ~VerBarMonitor();

  virtual void controllerSet(double ivalue) override;

  void setPrecision(uint8_t iprec);
protected:
   virtual void align() override;

   std::string unit;
   std::stringstream dataStr;
   uint8_t prec;

   uint16_t barWidth;

   double min, range;

   lv_obj_t *bar;
   lv_obj_t *data;
};

}

#endif
