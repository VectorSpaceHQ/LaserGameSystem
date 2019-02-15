/*
 * LaserDisplay.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef SRC_DRIVERS_LASERDISPLAY_H_
#define SRC_DRIVERS_LASERDISPLAY_H_

#include "DisplayIfc.h"

#include "Hal.h"
#include "CanvasObject.h"


class LaserDisplay: public DisplayIfc
{
private:
   HAL::Hal&   hal;
   VertexList_t activeVerts;
   VertexList_t backgroundVerts;
   bool newVerts;
   int vertIndex;

public:
   LaserDisplay(HAL::Hal& _hal);
   ~LaserDisplay() {};

public:
   void Update();
   void Render(VertexListRef vertices);

};


#endif /* SRC_DRIVERS_LASERDISPLAY_H_ */
