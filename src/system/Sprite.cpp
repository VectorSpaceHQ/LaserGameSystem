/*
 * Sprite.cpp
 *
 *  Created on: Feb 14, 2019
 *      Author: athiessen
 */

#include <Eigen/Dense>
#include <vector>
#include "CanvasObject.h"
#include "Shape.h"
#include "Sprite.h"


Sprite::Sprite():
   shapeList(),
   currentShape(),
   position(0, 0, 0, 0),
   velocity(0, 0, 0),
   acceleration(0, 0, 0),
   lowerLimit(0, 0, 0, 0),
   upperLimit(0, 0, 0, 0)
{
}


Sprite::Sprite(Shape* shape):
   shapeList(),
   currentShape(),
   position(0, 0, 0, 0),
   velocity(0, 0, 0),
   acceleration(0, 0, 0),
   lowerLimit(0, 0, 0, 0),
   upperLimit(0, 0, 0, 0)
{
   AddShape(shape);
}


Sprite::~Sprite()
{
}


void Sprite::AddShape(Shape* shape)
{
   shapeList.push_back(shape);

   // Initialize the current shape if this is the first shape added to the list
   if(shapeList.size() == 1)
   {
      currentShape = shapeList[0];
   }
}


void Sprite::SelectShape(uint32_t index)
{
   if(index < shapeList.size())
   {
      currentShape = shapeList[index];
   }
}


uint32_t Sprite::NumShapes()
{
   return shapeList.size();
}


void Sprite::ClearShapes()
{
   // Another module is responsible for the allocation of memory for the shapes
   // thus, we just need to clear our list of pointers.
   shapeList.clear();
}


void Sprite::Backup()
{
   ShapeList_t::iterator  it;

   for(it = shapeList.begin(); it != shapeList.end(); ++it )
   {
      (*it)->Backup();
   }
}


void Sprite::Restore()
{
   ShapeList_t::iterator  it;

   for(it = shapeList.begin(); it != shapeList.end(); ++it )
   {
      (*it)->Restore();
   }
}


void Sprite::Move()
{
   Move(velocity(CoordX), velocity(CoordY));
}


void Sprite::Move(CoordType _diffX, CoordType _diffY)
{
   Coordinate              diff;
   ShapeList_t::iterator   it;

   diff << _diffX, _diffY, 0, 0;

   CheckLimit(diff);
   position += diff;

   for(it = shapeList.begin(); it != shapeList.end(); ++it )
   {
      (*it)->Move(diff(CoordX), diff(CoordY), diff(CoordZ));
   }
}


void Sprite::Scale(CoordType _scale)
{
   ShapeList_t::iterator  it;

   for(it = shapeList.begin(); it != shapeList.end(); ++it )
   {
      (*it)->Scale(_scale);
   }
}


void Sprite::Scale(CoordType _xScale, CoordType _yScale, CoordType _zScale)
{
   ShapeList_t::iterator  it;

   for(it = shapeList.begin(); it != shapeList.end(); ++it )
   {
      (*it)->Scale(_xScale, _yScale, _zScale);
   }
}


void Sprite::SetVelocity(CoordType xVel, CoordType yVel, CoordType zVel)
{
   velocity << xVel, yVel, zVel;
}


void Sprite::SetLimits(CoordinateRef lower, CoordinateRef upper)
{
   lowerLimit = lower;
   upperLimit = upper;

   // Use the "color" bit to indicate the limit has been set
   lowerLimit(CoordColor) = 1;
   upperLimit(CoordColor) = 1;
}


void Sprite::Left(CoordinateRef coord)
{
   Coordinate::Index rowIndex;

   currentShape->vertices.col(CoordX).minCoeff(&rowIndex);
   coord = currentShape->vertices.row(rowIndex);
}


void Sprite::Right(CoordinateRef coord)
{
   Coordinate::Index rowIndex;

   currentShape->vertices.col(CoordX).maxCoeff(&rowIndex);
   coord = currentShape->vertices.row(rowIndex);
}


void Sprite::Top(CoordinateRef coord)
{
   Coordinate::Index rowIndex;

   currentShape->vertices.col(CoordY).maxCoeff(&rowIndex);
   coord = currentShape->vertices.row(rowIndex);
}


void Sprite::Bottom(CoordinateRef coord)
{
   Coordinate::Index rowIndex;

   currentShape->vertices.col(CoordY).minCoeff(&rowIndex);
   coord = currentShape->vertices.row(rowIndex);
}


int16_t Sprite::CheckTop(CoordType top)
{
   CoordType   maxY = currentShape->vertices.col(CoordY).maxCoeff();

   return (top - maxY);
}


int16_t Sprite::CheckBottom(CoordType bottom)
{
   CoordType   minY = currentShape->vertices.col(CoordY).minCoeff();

   return (minY - bottom);
}


int16_t Sprite::CheckLeft(CoordType left)
{
   CoordType   minX = currentShape->vertices.col(CoordX).minCoeff();

   return (minX - left);
}


int16_t Sprite::CheckRight(CoordType right)
{
   CoordType   maxX = currentShape->vertices.col(CoordX).maxCoeff();

   return (right - maxX);
}


int16_t Sprite::CheckLeft(Sprite& other)
{
   Coordinate myTop;
   Coordinate myBottom;
   Coordinate myLeft;
   Coordinate otherRight;
   int16_t    overlap = 1;

   Top(myTop);             // Get my top-most coordinate
   Bottom(myBottom);       // Get my bottom-most coordinate
   Left(myLeft);           // Get my left-most coordinate
   other.Right(otherRight);  // Get the right-most coordinate of the other sprite

   // Is the other left-most coordinate within our top/bottom?
   if( (otherRight(CoordY) <= myTop(CoordY)) && (otherRight(CoordY) >= myBottom(CoordY)) )
   {
      overlap = (myLeft(CoordX) - otherRight(CoordX));
   }

   return overlap;
}


int16_t Sprite::CheckRight(Sprite& other)
{
   Coordinate myTop;
   Coordinate myBottom;
   Coordinate myRight;
   Coordinate otherLeft;
   int16_t    overlap = 1;

   Top(myTop);             // Get my top-most coordinate
   Bottom(myBottom);       // Get my bottom-most coordinate
   Right(myRight);         // Get my right-most coordinate
   other.Left(otherLeft);  // Get the left-most coordinate of the other sprite

   // Is the other left-most coordinate within our top/bottom?
   if( (otherLeft(CoordY) <= myTop(CoordY)) && (otherLeft(CoordY) >= myBottom(CoordY)) )
   {
      overlap = (otherLeft(CoordX) - myRight(CoordX));
   }

   return overlap;
}


int32_t Sprite::NumPoints()
{
   return currentShape->NumPoints();
}


int32_t Sprite::MapVertices(VertexListRef list)
{
   return currentShape->MapVertices(list);
}


void Sprite::CheckLimit(CoordinateRef diff)
{
   // If the CoordColor is set, then the limit is valid
   if(lowerLimit(CoordColor) > 0)
   {
      if((position(CoordX) + diff(CoordX)) < lowerLimit(CoordX))
      {
         diff(CoordX) = lowerLimit(CoordX) - position(CoordX);
      }

      if((position(CoordY) + diff(CoordY)) < lowerLimit(CoordY))
      {
         diff(CoordY) = lowerLimit(CoordY) - position(CoordY);
      }

      if((position(CoordZ) + diff(CoordZ)) < lowerLimit(CoordZ))
      {
         diff(CoordZ) = lowerLimit(CoordZ) - position(CoordZ);
      }
   }

   if(upperLimit(CoordColor) > 0)
   {
      if((position(CoordX) + diff(CoordX)) > upperLimit(CoordX))
      {
         diff(CoordX) = upperLimit(CoordX) - position(CoordX);
      }

      if((position(CoordY) + diff(CoordY)) > upperLimit(CoordY))
      {
         diff(CoordY) = upperLimit(CoordY) - position(CoordY);
      }

      if((position(CoordZ) + diff(CoordZ)) > upperLimit(CoordZ))
      {
         diff(CoordZ) = upperLimit(CoordZ) - position(CoordZ);
      }
   }
}
