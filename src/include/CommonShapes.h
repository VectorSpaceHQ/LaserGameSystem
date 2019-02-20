/*
 * Rectangle.h
 *
 *  Created on: Feb 14, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_COMMONSHAPES_H_
#define INCLUDE_COMMONSHAPES_H_

#include <math.h>
#include "Shape.h"

#define PI  (3.14159265)


class Rectangle: public Shape
{
public:
   Rectangle(int width, int height):
      Shape(5)
   {
      vertices <<
         -(width / 2), -(height / 2), 0, 0,
          (width / 2), -(height / 2), 0, 1,
          (width / 2),  (height / 2), 0, 1,
         -(width / 2),  (height / 2), 0, 1,
         -(width / 2), -(height / 2), 0, 1;
   }

   ~Rectangle() {}
};


class Square: public Shape
{
public:
   Square(int width):
      Shape(5)
   {
      vertices <<
         -(width / 2), -(width / 2), 0, 0,
          (width / 2), -(width / 2), 0, 1,
          (width / 2),  (width / 2), 0, 1,
         -(width / 2),  (width / 2), 0, 1,
         -(width / 2), -(width / 2), 0, 1;
   }

   ~Square() {}
};


class Polygon: public Shape
{
public:
   Polygon(int numVertices, int radius):
      Shape(numVertices + 1)
   {
      float    angle = 0;
      float    angleStride = 2 * PI / numVertices;

      vertices(0, CoordX) = sin(angle) * radius;
      vertices(0, CoordY) = cos(angle) * radius;
      vertices(0, CoordZ) = 0;
      vertices(0, CoordColor) = 0;

      for(int cntr = 1; cntr <= numVertices; cntr++)
      {
         angle += angleStride;

         vertices(cntr, CoordX) = sin(angle) * radius;
         vertices(cntr, CoordY) = cos(angle) * radius;
         vertices(cntr, CoordZ) = 0;
         vertices(cntr, CoordColor) = 1;
      }

      // The starting point is the move point
      vertices(0, CoordColor) = 0;
   }

   ~Polygon() {}
};


class Star: public Shape
{
public:
   Star(int numPoints, int outerRadius, int innerRadius):
      Shape((2 * numPoints) + 1)
   {
      float    angle = 0;
      float    angleStride = PI / numPoints;

      vertices(0, CoordX) = sin(angle) * outerRadius;
      vertices(0, CoordY) = cos(angle) * outerRadius;
      vertices(0, CoordZ) = 0;
      vertices(0, CoordColor) = 0;

      for(int cntr = 1; cntr <= (numPoints * 2); cntr++)
      {
         angle += angleStride;

         if(cntr % 2 == 0)
         {
            vertices(cntr, CoordX) = sin(angle) * outerRadius;
            vertices(cntr, CoordY) = cos(angle) * outerRadius;
         }
         else
         {
            vertices(cntr, CoordX) = sin(angle) * innerRadius;
            vertices(cntr, CoordY) = cos(angle) * innerRadius;
         }

         vertices(cntr, CoordZ) = 0;
         vertices(cntr, CoordColor) = 1;
      }

      // The starting point is the move point
      vertices(0, CoordColor) = 0;
   }

   ~Star() {}
};


#endif /* INCLUDE_COMMONSHAPES_H_ */
