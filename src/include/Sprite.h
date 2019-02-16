/*
 * Sprite.h
 *
 *  Created on: Feb 14, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_

#include <vector>
#include "CanvasObject.h"
#include "Shape.h"


class Sprite: public CanvasObject
{
private:
   typedef std::vector<Shape*>   ShapeList_t;      // A list of shapes allows us to animate the sprite

   ShapeList_t    shapeList;
   Shape*         currentShape;

public:
   Coordinate     position;         // Where it currently is in normal world space
   Magnitude      velocity;         // The direction/scale of the X/Y vector
   Magnitude      acceleration;     // The current acceleration (future?)

public:
   Sprite(Shape* shape);     // Sprites must have at least one shape
   ~Sprite();

   // Shape list operations
   void AddShape(Shape* shape);
   void SelectShape(uint32_t index);
   uint32_t NumShapes();

   // Shape operations
   void Backup();
   void Restore();
   void Move();
   void Move(CoordType diffX, CoordType diffY);
   void Scale(CoordType _scale);
   void Scale(CoordType _xScale, CoordType _yScale, CoordType _zScale);

   // Motion & Collision detection operations
   void SetVelocity(CoordType xVel, CoordType yVel, CoordType zVel);
   bool CheckTop(CoordType top);
   bool CheckBottom(CoordType bottom);
   bool CheckLeft(CoordType top);
   bool CheckRight(CoordType bottom);

   // Display operations
   int32_t NumPoints();
   int32_t MapVertices(VertexListRef list);
};



#endif /* INCLUDE_SPRITE_H_ */
