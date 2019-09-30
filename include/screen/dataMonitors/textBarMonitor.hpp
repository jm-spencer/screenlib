#ifndef TEXT_BAR_MONITOR_HPP_
#define TEXT_BAR_MONITOR_HPP_
#include "screen/dataMonitors/baseMonitor.hpp"
#include "screen/resources.hpp"
#include <sstream>

namespace screen {

class TextBarMonitor : public BaseMonitor {
public:
  TextBarMonitor(lv_obj_t *parent, const char *icaption = "", std::string iunit = "",
                 double min = 0, double max = 100, lv_style_t *captionStyle = &lv_style_plain, lv_style_t *dataStyle = &lv_style_plain,
                 uint16_t ianimTime = 0, double ibarSize = 25,
                 std::shared_ptr<okapi::ControllerOutput<double>> ioutput = nullptr);

  ~TextBarMonitor();

  virtual void controllerSet(double ivalue) override;

  void setPrecision(uint8_t iprec);

protected:
  virtual void align() override;

  std::string unit;
  std::stringstream dataStr;
  uint8_t prec;

  lv_obj_t *cap;
  lv_obj_t *data;
  lv_obj_t *bar; //will take 25% of element

  uint16_t animTime;
  double barSize;
};

}

#endif
