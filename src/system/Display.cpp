/*
 * Display.cpp
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */


#include "Display.h"


Display::Display(DisplayImpl& _displayImpl):
   ScheduledInterval(1),
   displayImpl(_displayImpl)
{
}


void Display::Update()
{
   static int numRuns = 25;

   // Update the display implementation every time we are called
   displayImpl.Update();

   // Render a new display every 100 runs
   if(--numRuns <= 0)
   {
      Render();
      numRuns = 25;
   }
}


void Display::Render()
{
   // TODO: Perform transformations here

   // After transformations, then render the updates on the implementation
   displayImpl.Render();
}


void Display::Clear()
{
}
