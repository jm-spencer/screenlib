ScreenLib
=========
ScreenLib is a PROS library that handles screen drawing functions,
primarily printing each game's field. It provides a powerful way to
draw any possible field without requiring experience with [lvgl](https://littlevgl.com/)

![alt text](./Example.png "Example")

Installing
==========
* Go over to [releases](https://github.com/SpencerJ21/screenlib/releases) and download the latest version
* Open a terminal wherever you downloaded it(try shift + right click in file explorer)
* run `prosv5 c fetch screenlib@VERSION.zip`, replacing VERSION with the version
* run `prosv5 c apply screenlib` in your project directory to install

Usage
=====
Object drawing is mostly done through a `Field` object, by giving a position enum class and a bitfield of which cubes to print.  
Most objects on the screen are referred to by `left`, `right`, `near`, and `far` (near refers to the bottom of the screen while far refers to the top)

An example of this is:  
`field.drawCubeGroup(screen::cubeSector::right4, 0b00001010);`

Let's take a look at how the field is represented
![alt text](./Field.png "Labeled Field")
Each of the cube group names are in `screen::cubeSector`,  
each of the tower names are in `screen::towerPos`, and  
each of the scoring zone names are in `screen::zonePos`

The numbers on the cube show the bit that represents them in their bitfield:  
a 0 means it's looking at bit 0: `0b0000000X`  
a 1 means it's looking at bit 1: `0b000000X0`  
and so on.

This is done so the presence of every cube in a group can be given by a number  
say you want the cubes labeled 3, 1, and 0, the bitfield would be `0b00001011`  

For the stacks near the middle, the cubes in the stack but not on top, are still represented by the bits that follow the top cube's bit (the 3 cubes under a cube on bit 3 are represented by bits 2, 1, and 0)

Alternatively, macros can be used for more verbose code; here is the equivalent of the previous example:  
`field.drawCubeGroup(screen::cubeSector::right4, CUBE_HIGHEST + CUBE_2LOWEST);`

`CUBE_HIGHEST` represents the highest cube in the stack, followed by `CUBE_2HIGHEST` (the 2nd highest), followed by `CUBE_2LOWEST` (the 2nd lowest), and finally `CUBE_LOWEST`  
As the 4 cube stacks on the left and right are in the same order but slightly different positions, the corresponding cubes are represented the same (purple to purple, orange to orange, green to green)

`CUBE_FAR` and `CUBE_NEAR` are for the cube sectors farLeft and farRight

`CUBE_TOP_NEAR`, `CUBE_FAR_LEFT`, `CUBE_NEAR_LEFT`, `CUBE_FAR_RIGHT`, and `CUBE_NEAR_RIGHT` are used for the five cube stack on the near side

and finally, all macros starting with `TOWER_CUBE_` refer to the cubes around a tower
