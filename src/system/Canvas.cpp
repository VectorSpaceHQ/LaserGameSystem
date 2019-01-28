/*
 * Canvas.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */


#include <Canvas.h>


Canvas::Canvas(DisplayIfc& _displayImpl):
   ScheduledInterval(1),
   displayImpl(_displayImpl)
{
}


void Canvas::Update()
{
   static int numRuns = 500;

   // Render a new display every 100 runs
   if(--numRuns <= 0)
   {
      Render();
      numRuns = 500;
   }
}


void Canvas::Render()
{
   // TODO: Perform transformations here

   // After transformations, then render the updates on the implementation
   displayImpl.Render();
}


void Canvas::Clear()
{
}
