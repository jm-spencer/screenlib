#ifndef TEXT_MONITOR_HPP_
#define TEXT_MONITOR_HPP_
#include "screen/dataMonitors/baseMonitor.hpp"
#include "screen/resources.hpp"

namespace screen {

class TextMonitor : public BaseMonitor {
 public:
  TextMonitor(lv_obj_t *parent, std::string icaption = "", std::string iunit = "",
              uint32_t ilength = 40, lv_style_t *captionStyle = &lv_style_plain,
              lv_style_t *dataStyle = &lv_style_plain,
              std::shared_ptr<okapi::ControllerOutput<double>> ioutput = nullptr);

  ~TextMonitor();

  virtual void controllerSet(double ivalue) override;

 private:
  std::string unit;

  lv_obj_t *cap;
  lv_obj_t *data;
};

}  // namespace screen

#endif
