/*
 * LaserDisplay.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef SRC_DRIVERS_LASERDISPLAY_H_
#define SRC_DRIVERS_LASERDISPLAY_H_

#include <stdint.h>
#include "DisplayIfc.h"
#include "Hal.h"
#include "CanvasObject.h"


struct LaserPoint
{
   uint16_t x;    // X Coordinate
   uint16_t y;    // Y Coordinate
   uint16_t c;    // Color
};


class LaserDisplay: public DisplayIfc
{
private:
   HAL::Hal&   hal;
   LaserPoint* activeVerts;
   LaserPoint* backgroundVerts;
   bool newVerts;
   int vertIndex;
   uint16_t    numActivePts;
   uint16_t    numBackgroundPts;

public:
   LaserDisplay(HAL::Hal& _hal);
   ~LaserDisplay() {};

public:
   void Update();
   void Render(VertexListRef vertices);

};


#endif /* SRC_DRIVERS_LASERDISPLAY_H_ */
