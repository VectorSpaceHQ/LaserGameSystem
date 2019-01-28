/*
 * Calibrate.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#include "Calibrate.h"
#include "Program.h"
#include "Shape.h"


// MaxSize is 4096  -- resolution of the laser
//   divided by 2 for positive and negative axes (grow from 0 in the center)
//   subtract one to ensure we don't go one past the edge
const int Calibrate::MaxSize = 2047;
const int Calibrate::StepSize = 12;


Calibrate::Calibrate(Canvas& _display
         //GamePad& _gamePad1,
         //GamePad& _gamePad2
         ):
   Program(_display/*, _gamePad1, _gamePad2*/),
   square(5),
   scale(1),
   shrinkGrow(1)
{
   square.vertices <<
   //  X   Y  Z  C   // C is for "Color"!
      -1, -1, 0, 0,  // Initial position: Start at top left (but don't draw -- see colors)
       1, -1, 0, 1,  // Draw to top right
       1,  1, 0, 1,  // Draw to bottom right
      -1,  1, 0, 1,  // Draw to bottom left
      -1, -1, 0, 1;  // Draw to top left to complete the square
}


// This method is called every time the program is actually scheduled (every 33 iterations)
// Currently is draws an expanding/shrinking square.
// When the square reaches the limits of the display, it starts to shrink.
void Calibrate::Update()
{
   square.Scale(scale);
   square.Restore();

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

   // TODO: Call the display to draw our scaled square
}
