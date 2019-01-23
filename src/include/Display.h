/*
 * display.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef SRC_INCLUDE_DISPLAY_H_
#define SRC_INCLUDE_DISPLAY_H_

#include "DisplayImpl.h"
#include "ScheduledInterval.h"


class Display: public ScheduledInterval
{
private:
   DisplayImpl&       displayImpl;

public:
   Display(DisplayImpl& _displayImpl);
   ~Display() {};

   void Update();
   void Render();
   void Clear();

//   void DrawLine(/* need parameters here */);
//   void DrawCircle(/* need parameters here */);
//   void DrawRectangle(/* need parameters here */);

   // Future...
   //void DrawBezier(/* need parameters here */) = 0;
};


#endif /* SRC_INCLUDE_DISPLAY_H_ */
