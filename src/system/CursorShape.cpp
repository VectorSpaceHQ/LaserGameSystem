/*
 * CursorShape.cpp
 *
 *  Created on: Feb 18, 2019
 *      Author: athiessen
 */


#include <Eigen/Dense>
#include "CursorShape.h"
#include "Shape.h"


CursorShape::CursorShape():
   Shape(0),
   currentDir(Center)
{
   SetDirection(currentDir);
}


CursorShape::~CursorShape()
{
   vertices.resize(0, CoordMax);
}


void CursorShape::SetDirection(Direction newDir)
{
   DrawShape(newDir);
   currentDir = newDir;
}


void CursorShape::DrawShape(Direction shape, bool doScale)
{
   switch(shape)
   {
      default:
      case Center:
         vertices.resize(9, CoordMax);
         vertices <<
                  -1,  1, 0, 0,
                   1,  1, 0, 1,
                   1, -1, 0, 1,
                  -1, -1, 0, 1,
                  -1,  1, 0, 1,
                  -1,  0, 0, 0,
                   1,  0, 0, 1,
                   0,  1, 0, 0,
                   0, -1, 0, 1;
         break;

      case Up:
         vertices.resize(5, CoordMax);
         vertices <<
                   0.0, -1.0, 0, 0,
                   0.0,  1.0, 0, 1,
                  -0.5,  0.5, 0, 0,
                   0.0,  1.0, 0, 1,
                   0.5,  0.5, 0, 1;
         break;

      case UpRight:
         vertices.resize(5, CoordMax);
         vertices <<
                  -0.7, -0.7, 0, 0,
                   0.7,  0.7, 0, 1,
                   0.0,  0.7, 0, 0,
                   0.7,  0.7, 0, 1,
                   0.7,  0.0, 0, 1;
         break;

      case Right:
         vertices.resize(5, CoordMax);
         vertices <<
                  -1.0,  0.0, 0, 0,
                   1.0,  0.0, 0, 1,
                   0.5,  0.5, 0, 0,
                   1.0,  0.0, 0, 1,
                   0.5, -0.5, 0, 1;
         break;

      case DownRight:
         DrawShape(UpRight, false);
         Scale(1, -1, 1);
         break;

      case Down:
         DrawShape(Up, false);
         Scale(1, -1, 1);
         break;

      case DownLeft:
         DrawShape(UpRight, false);
         Scale(-1, -1, 1);
         break;

      case Left:
         DrawShape(Right, false);
         Scale(-1, 1, 1);
         break;

      case UpLeft:
         DrawShape(UpRight, false);
         Scale(-1, 1, 1);
         break;
   }

   if(doScale)
   {
      Scale(scale);
      MoveToPosition();
   }
}
