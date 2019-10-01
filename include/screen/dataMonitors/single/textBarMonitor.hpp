#ifndef TEXT_BAR_MONITOR_HPP_
#define TEXT_BAR_MONITOR_HPP_
#include "screen/dataMonitors/single/singleMonitor.hpp"
#include "screen/resources.hpp"
#include <sstream>

namespace screen {

class TextBarMonitor : public SingleMonitor {
public:
  TextBarMonitor(lv_obj_t *parent, const char *icaption = "", std::string iunit = "",
                 double min = 0, double max = 100, uint16_t ianimTime = 0, double ibarSize = 25,
                 lv_style_t *captionStyle = &lv_style_plain, lv_style_t *dataStyle = &lv_style_plain,
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
  lv_obj_t *bar;

  uint16_t animTime;
  double barSize;
};

}

#endif
