/*
 * Canvas.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <DisplayIfc.h>
#include "ScheduledInterval.h"


class Canvas: public ScheduledInterval
{
private:
   DisplayIfc&       displayImpl;

public:
   Canvas(DisplayIfc& _displayImpl);
   ~Canvas() {};

   void Update();
   void Render();
   void Clear();

//   void DrawLine(/* need parameters here */);
//   void DrawCircle(/* need parameters here */);
//   void DrawRectangle(/* need parameters here */);

   // Future...
   //void DrawBezier(/* need parameters here */) = 0;
};


#endif /* __CANVAS_H__ */
