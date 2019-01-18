/*
 * display.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef SRC_INCLUDE_DISPLAY_H_
#define SRC_INCLUDE_DISPLAY_H_


class Display
{

public:
   virtual void Clear() = 0;
   virtual void DrawLine(/* need parameters here */) = 0;
   virtual void DrawCircle(/* need parameters here */) = 0;
   virtual void DrawRectangle(/* need parameters here */) = 0;

   // Future...
   //void DrawBezier(/* need parameters here */) = 0;
};


#endif /* SRC_INCLUDE_DISPLAY_H_ */
