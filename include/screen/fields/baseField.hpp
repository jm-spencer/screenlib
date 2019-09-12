#ifndef SCREEN_FIELD_BASE_HPP_
#define SCREEN_FIELD_BASE_HPP_
#include "screen/resources.hpp"

namespace screen {

class BaseField {
public:
  BaseField(lv_obj_t *parent, double ilength = 240);
  ~BaseField();


    /**
     * Remove all objects from the field, and reset to default
     */
    virtual void clean();

    /**
     * Set new x position of the field on the screen
     *
     * @param x new x-value of the distance from the leftmost side of the screen
     *    (screen is 480 pixels wide)
     */
    void setX(int x);

    /**
     * Set new y position of the field on the screen
     *
     * @param y new y-value of the distance from the top side of the field
     *    (screen is 240 pixels tall)
     */
    void setY(int y);

    /**
     * Set new position of the field on the screen
     *
     * note: the default(if this is never called) is 120,0 (centered)
     *
     * @param x new x-value of the distance from the leftmost side of the screen
     *    (screen is 480 pixels wide)
     * @param y new y-value of the distance from the top side of the field
     *    (screen is 240 pixels tall)
     */
    void setPos(int x, int y);

    /**
     * Set the new width and height of the field
     *
     * this will clean the screen and remove all existing objects
     *
     * note: you can make the field larger than the screen,
     *    but you would then need a way to move the screen around in order to see it
     */
    void setSideLength(uint ilength);

    lv_obj_t *getChildObj(lv_obj_t *clone = NULL);

    lv_obj_t *getChildLineObj(lv_obj_t *clone = NULL);



protected:
  lv_obj_t *obj;

  double scalar;
};

} //namespace screen

#endif
