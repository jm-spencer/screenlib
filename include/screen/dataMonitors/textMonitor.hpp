#ifndef TEXT_MONITOR_HPP_
#define TEXT_MONITOR_HPP_
#include "screen/dataMonitors/baseMonitor.hpp"
#include "screen/resources.hpp"
#include <sstream>

namespace screen {

class TextMonitor : public BaseMonitor {
public:
  TextMonitor(lv_obj_t *parent, const char *icaption = "", std::string iunit = "",
              lv_style_t *captionStyle = &lv_style_plain,
              lv_style_t *dataStyle = &lv_style_plain,
              std::shared_ptr<okapi::ControllerOutput<double>> ioutput = nullptr);

  ~TextMonitor();

  virtual void controllerSet(double ivalue) override;

  void setPrecision(uint8_t iprec);

protected:
   virtual void align() override;

   std::string unit;
   std::stringstream dataStr;
   uint8_t prec;

   lv_obj_t *cap;
   lv_obj_t *data;
};

}  // namespace screen

#endif
