/*
 * NumeralShape.h
 *
 *  Created on: Feb 19, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_NUMERALSHAPE_H_
#define INCLUDE_NUMERALSHAPE_H_

#include <stdint.h>
#include "Shape.h"

class NumeralShape: public Shape
{
public:
   uint8_t   value;

   NumeralShape();
   ~NumeralShape();

   void SetValue(uint8_t newValue);

};


#endif /* INCLUDE_NUMERALSHAPE_H_ */
