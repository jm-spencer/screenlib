#include "screen/field.hpp"

void testScreen() {
	//make sure initializeStyles() happens or nothing will work!

	lv_obj_t *scr = lv_obj_create(NULL, NULL);
	//lv_obj_set_style(scr, &screen::blankStyle);
	lv_scr_load(scr);

	screen::Field field(scr);

	field.drawScoringZone(screen::zonePos::farRed, {screen::color::purple, screen::color::orange}, {1, 3}); //two stacks use an array of colors
	field.drawScoringZone(screen::zonePos::nearRed, screen::color::green, 4); 															//one stack does not

	field.drawCubeGroup(screen::cubeSector::left1, 0b00000011); // leave only the bottom two cubes
	field.drawCubeGroup(screen::cubeSector::left3, 0b00001100); // take the two cubes not in the stack
	field.drawCubeGroup(screen::cubeSector::right4, 0b00001010);// take the rightmost and 3rd rightmost cube
	field.drawCubeGroup(screen::cubeSector::near, CUBE_NEAR_LEFT + CUBE_NEAR_RIGHT + CUBE_FAR_RIGHT);	// take the top purple cube
	field.drawCubeGroup(screen::cubeSector::left4, CUBE_HIGHEST + CUBE_2LOWEST);

	field.drawTower(screen::towerPos::left, screen::color::none, 0); 						 //take all the cubes
	field.drawTower(screen::towerPos::center, screen::color::orange, 0b0001110); //put a cube in the tower and take the leftmost cube
	field.drawTower(screen::towerPos::far, screen::color::none, TOWER_CUBE_FAR + TOWER_CUBE_LEFT);

	field.drawRobot(false, 160); //draw robot centered on the field

	field.finishDrawing();

	while(true){
		pros::delay(1000);
	}
}

void opcontrol(){
	testScreen();
}
