/*
 * Sprite.h
 *
 *  Created on: Feb 14, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_SPRITE_H_
#define INCLUDE_SPRITE_H_

#include <Eigen/Dense>
#include <stdint.h>
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
   Coordinate     lowerLimit;
   Coordinate     upperLimit;

public:
   Sprite();
   Sprite(Shape* shape);
   ~Sprite();

   // Shape list operations
   void AddShape(Shape* shape);
   void SelectShape(uint32_t index);
   uint32_t NumShapes();
   void ClearShapes();

   // Shape operations
   void Backup();
   void Restore();
   void Move();
   void Move(CoordType _diffX, CoordType _diffY);
   void Scale(CoordType _scale);
   void Scale(CoordType _xScale, CoordType _yScale, CoordType _zScale);

   // Motion & Collision detection operations
   void SetVelocity(CoordType xVel, CoordType yVel, CoordType zVel);
   void SetLimits(CoordinateRef lower, CoordinateRef upper);

   /***
    * Extreme Coordinates - Fill a coordinate with the vertex values of the specified coordinate
    * @param coord - output values of the extreme coordinate
    */
   void Left(CoordinateRef coord);
   void Right(CoordinateRef coord);
   void Top(CoordinateRef coord);
   void Bottom(CoordinateRef coord);

   /***
    * Collision detection:
    *   return: > 0 - Distance between the points - The two points have not collided
    *           = 0 - Edges are touching - There is no gap between the two
    *           < 0 - Overlap distance - The two points are overlapping
    */
   int16_t CheckTop(CoordType top);
   int16_t CheckBottom(CoordType bottom);
   int16_t CheckLeft(CoordType top);
   int16_t CheckRight(CoordType bottom);
   int16_t CheckLeft(Sprite& other);
   int16_t CheckRight(Sprite& other);

   // Display operations
   virtual int32_t NumPoints();
   virtual int32_t MapVertices(VertexListRef list);

private:
   void CheckLimit(CoordinateRef diff);

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};



#endif /* INCLUDE_SPRITE_H_ */
