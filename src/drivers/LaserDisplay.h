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
#include "Shape.h"


class LaserDisplay: public DisplayIfc
{
private:
   HAL::Hal&   hal;

public:
   LaserDisplay(HAL::Hal& _hal);
   ~LaserDisplay() {};

public:
   void Update();
   void Render(Eigen::Ref<const VertexList_t> vertices);

};


#endif /* SRC_DRIVERS_LASERDISPLAY_H_ */
