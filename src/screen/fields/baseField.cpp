#include "screen/fields/baseField.hpp"

namespace screen {

BaseField::BaseField(lv_obj_t *parent, const double ilength) : scalar(ilength / 240.0)
{
  obj = lv_obj_create(parent, NULL);
  lv_obj_set_style(obj, &resources::fieldStyle);
  lv_obj_set_size(obj, ilength, ilength);
  lv_obj_set_pos(obj, 120, 0);
}

BaseField::~BaseField()
{
  lv_obj_del(obj);
}

void BaseField::clean()
{
  lv_obj_clean(obj);
}

void BaseField::setX(int x)
{
  lv_obj_set_x(obj, x);
}

void BaseField::setY(int y)
{
  lv_obj_set_y(obj, y);
}

void BaseField::setPos(int x, int y)
{
  lv_obj_set_pos(obj, x, y);
}

void BaseField::hide(bool hide)
{
  lv_obj_set_hidden(obj, hide);
}

void BaseField::setSideLength(uint32_t ilength)
{
  scalar = ilength / 240.0;
  lv_obj_set_size(obj, ilength, ilength);
  clean();
}

lv_obj_t *BaseField::getChildObj(lv_obj_t *clone)
{
  return lv_obj_create(obj, clone);
}

lv_obj_t *BaseField::getChildLineObj(lv_obj_t *clone)
{
  return lv_line_create(obj, clone);
}

}  // namespace screen
