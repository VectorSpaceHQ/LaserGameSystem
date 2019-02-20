/*
 * CursorShape.h
 *
 *  Created on: Feb 18, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_CURSORSHAPE_H_
#define INCLUDE_CURSORSHAPE_H_

#include "Shape.h"

class CursorShape: public Shape
{
public:
   enum Direction
   {
      Center = 0,
      Up,
      UpRight,
      Right,
      DownRight,
      Down,
      DownLeft,
      Left,
      UpLeft
   };

   CursorShape();
   ~CursorShape();

   void SetDirection(Direction newDir);

private:
   Direction   currentDir;

   void DrawShape(Direction shape, bool doScale = true);

};


#endif /* INCLUDE_CURSORSHAPE_H_ */
