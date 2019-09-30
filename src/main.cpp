#include "main.h"
#include "screen/api.hpp"
#include "screen/dataMonitors/verBarMonitor.hpp"
#include "screen/dataMonitors/horBarMonitor.hpp"

lv_style_t tightBarStyle;

void initialize() {
  pros::delay(50);

	// this is very important, this MUST be run before anything else
  screen::resources::initialize();

  lv_style_copy(&tightBarStyle, &lv_style_plain);
  tightBarStyle.body.main_color = LV_COLOR_RED;
  tightBarStyle.body.grad_color = LV_COLOR_RED;
  tightBarStyle.body.padding.hor = 3;
  tightBarStyle.body.padding.ver = 3;
  tightBarStyle.body.radius = 0;
  tightBarStyle.body.border.width = 0;
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	// make sure   screen::resources::initialize() happens or nothing will work!
	// in this example it is called in initialize()

	// initialize and load a screen object
	lv_obj_t *scr = lv_obj_create(NULL, NULL);
	lv_scr_load(scr);

	screen::ttField field(scr);

	// two stacks use an array of colors
	// draw a purple stack with height 1 and an orange stack with height 3 in the far red zone
	field.draw(screen::scoringZone::farRed, {screen::color::purple, screen::color::orange}, {1, 3});

	// one stack does not need to use an array
	// draw a green stack with height 4 in the near red zone
	field.draw(screen::scoringZone::nearRed, screen::color::green, 4);

	// draw the 1st(furthest) left stack with only the bottom two cubes
	field.draw(screen::cubeGroup::left1, 0b00011);

	// draw the 3rd(2nd closest) left stack, but not the cubes to the left of it
	field.draw(screen::cubeGroup::left3, 0b01100);

	// draw the first and 3rd cube in the row
	// right4 is the closest row of cubes on the right
	// it looks the same in binary and on the field
	field.draw(screen::cubeGroup::right4, 0b01010);

	// alternatively, macros can be used

	// draw the 3 cubes the macros describe
	// (this is the 5 cube stack on the audience side)
	field.draw(screen::cubeGroup::near, CUBE_NEAR_LEFT + CUBE_NEAR_RIGHT + CUBE_FAR_RIGHT);

	// draw the highest(rightmost), and the 2nd lowest(leftmost) cube of the 4th(closest) left cube
	// group
	field.draw(screen::cubeGroup::left4, CUBE_HIGHEST + CUBE_2LOWEST);

	// draw the left tower with no cubes in or around
	field.draw(screen::tower::left, screen::color::none, 0);

	// draw an orange cube in the center tower, and draw all cubes around it except the left one
	field.draw(screen::tower::center, screen::color::orange, 0b1110);

	// draw the far tower with no cube, and draw the cube past it and to the left of it
	field.draw(screen::tower::far, screen::color::none, TOWER_CUBE_FAR + TOWER_CUBE_LEFT);

	// draw a "robot" on the red (denoted by true) side of the field with a center y-value of 160
	// (straddling the line between the 4th and 5th tiles from the top)
	field.drawRobot(true, 160);

	// draw all objects not explicity defined here with their default settings
	field.finishDrawing();

  screen::TextBarMonitor mon(scr, "I is", "cm", 0, 100, 10, 25, &lv_style_plain, &tightBarStyle);
  screen::TextMonitor mon2(scr, "J is", "cm", &lv_style_plain_color, &tightBarStyle);
  //screen::VerBarMonitor mon3(scr, "", 0, 100, 240, 0.1);
  //screen::HorBarMonitor mon4(scr, "=i but horizontal", 0, 100, 240, 0.1);
  mon.setPos(240, 0);
  mon.setSize(60, 60);
  mon2.setPos(240, 60);
  mon2.setSize(60, 40);
  //mon3.setPos(300, 0);
  //mon3.setSize(60, 180);
  //mon4.setPos(240, 180);
  //mon4.setSize(240, 60);
  double i = 1;

  while (true) {
    if (i < 100) i++;
    else i = 0;

    mon.controllerSet(i);
    mon2.controllerSet(i);
    //mon3.controllerSet(i);
    //mon4.controllerSet(i);

    std::cout << "step\n";
    pros::delay(500);
}
}


/* plan moving forward:
   split baseMonitor into baseMonitor and monitorEntry
      baseMonitor will not inherit while monitorEntry will inherit ControllerOutput
    extend this split into all the other monitors
      include ways to construct via a constructor and a member in the baseMonitor class
    use this new template to make GraphMonitor
*/
