/*
 * display.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef SRC_INCLUDE_DISPLAY_H_
#define SRC_INCLUDE_DISPLAY_H_

#include "hal.h"

class Display
{
private:
   HAL::OnOffSwitch* mainLight;

public:
   Display();
   ~Display() {};

   void Init(HAL::OnOffSwitch* _mainLight) {mainLight = _mainLight; }
   void Clear();

//   void DrawLine(/* need parameters here */);
//   void DrawCircle(/* need parameters here */);
//   void DrawRectangle(/* need parameters here */);

   // Future...
   //void DrawBezier(/* need parameters here */) = 0;
};


#endif /* SRC_INCLUDE_DISPLAY_H_ */
