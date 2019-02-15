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

protected:
   Coordinate     position;         // Where it currently is in normal world space
   Magnitude      velocity;         // The direction/scale of the X/Y vector
   Magnitude      acceleration;     // The current acceleration (future?)

public:
   Sprite(Shape* shape);     // Sprites must have at least one shape
   ~Sprite();

   void AddShape(Shape* shape);
   void SelectShape(uint32_t index);
   uint32_t NumShapes();

   void Backup();
   void Restore();
   void Move(CoordType diffX, CoordType diffY);
   void Scale(CoordType _scale);
   void Scale(CoordType _xScale, CoordType _yScale, CoordType _zScale);

   int32_t NumPoints();
   int32_t MapVertices(VertexListRef list);
};



#endif /* INCLUDE_SPRITE_H_ */
