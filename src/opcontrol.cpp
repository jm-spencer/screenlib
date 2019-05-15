#include "screen/field.hpp"

void testScreen() {
	//make sure initializeStyles() happens or nothing will work!

	lv_obj_t *scr = lv_obj_create(NULL, NULL);
	//lv_obj_set_style(scr, &screen::blankStyle);
	lv_scr_load(scr);

	screen::Field field(scr);

	field.drawScoringZone(screen::ZonePos::FarRed, {screen::Color::Purple, screen::Color::Orange}, {1, 3}); //two stacks use an array of colors
	field.drawScoringZone(screen::ZonePos::NearRed, screen::Color::Green, 4); 															//one stack does not

	field.drawCubeGroup(screen::CubeSector::Left1, 0b00000011); // leave only the bottom two cubes
	field.drawCubeGroup(screen::CubeSector::Left3, 0b00001100); // take the two cubes not in the stack
	field.drawCubeGroup(screen::CubeSector::Right4, 0b00001010);// take the rightmost and 3rd rightmost cube
	field.drawCubeGroup(screen::CubeSector::Near, CUBE_NEAR_LEFT + CUBE_NEAR_RIGHT + CUBE_FAR_RIGHT);	// take the top purple cube
	field.drawCubeGroup(screen::CubeSector::Left4, CUBE_HIGHEST + CUBE_2LOWEST);

	field.drawTower(screen::TowerPos::Left, screen::Color::None, 0); 						 //take all the cubes
	field.drawTower(screen::TowerPos::Center, screen::Color::Orange, 0b0001110); //put a cube in the tower and take the leftmost cube
	field.drawTower(screen::TowerPos::Far, screen::Color::None, TOWER_CUBE_FAR + TOWER_CUBE_LEFT);

	field.drawRobot(false, 160); //draw robot centered on the field

	field.finishDrawing();

	while(true){
		pros::delay(1000);
	}
}

void opcontrol(){
	testScreen();
}
