#ifndef VER_BAR_MONITOR_HPP_
#define VER_BAR_MONITOR_HPP_
#include "okapi/api/control/controllerOutput.hpp"
#include "screen/util/baseObject.hpp"
#include "screen/resources.hpp"
#include <sstream>
#include <memory>
#include <vector>

namespace screen {

class VerBarEntry : okapi::ControllerOutput<double> {
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

  void setYScalar(double iyScalar);

  virtual void controllerSet(double ivalue) override;

protected:
  void align();

  std::string unit{""};
  std::stringstream dataStr;
  uint8_t prec{3};

  double min{0}, range{100}, padding{0};

  lv_obj_t *bar{nullptr};
  lv_obj_t *data{nullptr};

  std::shared_ptr<okapi::ControllerOutput<double>> output{nullptr};
};



class VerBarMonitor : public BaseObject {
public:
  VerBarMonitor(lv_obj_t *parent, lv_style_t *bgStyle = &lv_style_transp);

  ~VerBarMonitor();

  VerBarEntry *makeEntry();

protected:
   virtual void align() override;

   std::vector<VerBarEntry *> entries;

};

}

#endif
