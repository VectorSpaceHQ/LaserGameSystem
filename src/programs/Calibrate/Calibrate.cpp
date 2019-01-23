/*
 * Calibrate.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#include <Eigen/Dense>

#include "Calibrate.h"
#include "Program.h"


// MaxSize is 4096  -- resolution of the laser
//   divided by 2 for positive and negative axes (grow from 0 in the center)
//   subtract one to ensure we don't go one past the edge
const int Calibrate::MaxSize = 2047;
const int Calibrate::StepSize = 12;


Calibrate::Calibrate(Display& _display
         //GamePad& _gamePad1,
         //GamePad& _gamePad2
         ):
   Program(_display/*, _gamePad1, _gamePad2*/),
   square(5, 3),
   scaledSquare(5, 3),
   squareColors(5),
   scale(1)
{
   // Set all vertices to 100%, except the first one
   squareColors << 0, 1, 1, 1, 1;
   square <<
      -1, -1, 0,   // Initial position: Start at top left (but don't draw -- see colors)
       1, -1, 0,   // Draw to top right
       1,  1, 0,   // Draw to bottom right
      -1,  1, 0,   // Draw to bottom left
      -1, -1, 0;   // Draw to top left to complete the square
      // Drawing should return to the second row since the first row is the starting point.
}


// This method is called every time the program is actually scheduled (every 33 iterations)
// Currently is draws an expanding/shrinking square.
// When the square reaches the limits of the display, it starts to shrink.
void Calibrate::Update()
{
   // Start by growing
   static int shrinkGrow = 1;

   // Add (12 *  1) to scale if growing,
   //  or (12 * -1) to scale if shrinking.
   scale += StepSize * shrinkGrow;

   if(scale >= MaxSize)    // If scale is bigger than our max size, then
   {
      scale = MaxSize;     // Set to max size
      shrinkGrow *= -1;    // Start shrinking
   }
   else if(scale <= 1)     // If scale is smaller than 1
   {
      scale = 1;           // Set to 1
      shrinkGrow *= -1;    // Start growing
   }

   // Multiply the matrix of vertices of our square by the scale factor
   scaledSquare = square * scale;

   // TODO: Call the display to draw our scaled square
}
