#include "main.h"
#include "screen/api.hpp"

void initialize() {
	// this is very important, this MUST be run before anything else
  screen::resources::initialize();
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

	while (true) {
		pros::delay(1000);
	}
}
