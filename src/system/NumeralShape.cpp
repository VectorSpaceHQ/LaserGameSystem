/*
 * NumeralShape.cpp
 *
 *  Created on: Feb 19, 2019
 *      Author: athiessen
 */


#include <stdint.h>
#include "NumeralShape.h"
#include "Shape.h"


NumeralShape::NumeralShape():
   Shape(0),
   value(0)
{
   SetValue(value);
}


NumeralShape::~NumeralShape()
{
   vertices.resize(0, CoordMax);
}


void NumeralShape::SetValue(uint8_t newValue)
{
   value = newValue;

   switch(newValue)
   {
      default:
      case 0:
         vertices.resize(6, CoordMax);
         vertices <<
                   1,  1, 0, 0,
                   1, -1, 0, 1,
                  -1, -1, 0, 1,
                  -1,  1, 0, 1,
                   1,  1, 0, 1,
                  -1, -1, 0, 1;
         break;

      case 1:
         vertices.resize(2, CoordMax);
         vertices <<
                   0,  1, 0, 0,
                   0, -1, 0, 1;
         break;

      case 2:
         vertices.resize(6, CoordMax);
         vertices <<
                  -1,  1, 0, 0,
                   1,  1, 0, 1,
                   1,  0, 0, 1,
                  -1,  0, 0, 1,
                  -1, -1, 0, 1,
                   1, -1, 0, 1;
         break;

      case 3:
         vertices.resize(6, CoordMax);
         vertices <<
                  -1,  1, 0, 0,
                   1,  1, 0, 1,
                   1, -1, 0, 1,
                  -1, -1, 0, 1,
                   1,  0, 0, 0,
                   0,  0, 0, 1;
         break;

      case 4:
         vertices.resize(4, CoordMax);
         vertices <<
                   1, -1, 0, 0,
                   1,  1, 0, 1,
                  -1,  0, 0, 1,
                   1,  0, 0, 1;
         break;

      case 5:
         vertices.resize(6, CoordMax);
         vertices <<
                   1,  1, 0, 0,
                  -1,  1, 0, 1,
                  -1,  0, 0, 1,
                   1,  0, 0, 1,
                   1, -1, 0, 1,
                  -1, -1, 0, 1;
         break;

      case 6:
         vertices.resize(6, CoordMax);
         vertices <<
                   1,  1, 0, 0,
                  -1,  1, 0, 1,
                  -1, -1, 0, 1,
                   1, -1, 0, 1,
                   1,  0, 0, 1,
                  -1,  0, 0, 1;
         break;

      case 7:
         vertices.resize(3, CoordMax);
         vertices <<
                  -1,  1, 0, 0,
                   1,  1, 0, 1,
                  -1, -1, 0, 1;
         break;

      case 8:
         vertices.resize(7, CoordMax);
         vertices <<
                   1,  1, 0, 0,
                   1, -1, 0, 1,
                  -1, -1, 0, 1,
                  -1,  1, 0, 1,
                   1,  1, 0, 1,
                   1,  0, 0, 0,
                  -1,  0, 0, 1;
         break;

      case 9:
         vertices.resize(6, CoordMax);
         vertices <<
                  -1, -1, 0, 0,
                   1, -1, 0, 1,
                   1,  1, 0, 1,
                  -1,  1, 0, 1,
                  -1,  0, 0, 1,
                   1,  0, 0, 1;
         break;

   }

   Scale(scale);
   MoveToPosition();
}


void NumeralShape::operator++()
{
   if(value == 9)
   {
      SetValue(0);
   }
   else
   {
      SetValue(value + 1);
   }
}


void NumeralShape::operator--()
{
   if(value == 0)
   {
      SetValue(9);
   }
   else
   {
      SetValue(value - 1);
   }
}
