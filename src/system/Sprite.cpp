/*
 * Sprite.cpp
 *
 *  Created on: Feb 14, 2019
 *      Author: athiessen
 */

#include "CanvasObject.h"
#include "Shape.h"
#include "Sprite.h"


Sprite::Sprite(Shape* shape):
   shapeList(),
   currentShape(),
   position(0),
   velocity(1),
   acceleration(0)
{
   AddShape(shape);
   currentShape = shapeList[0];
}


Sprite::~Sprite()
{
}


void Sprite::AddShape(Shape* shape)
{
   shapeList.push_back(shape);
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


void Sprite::Move(CoordType diffX, CoordType diffY)
{
   ShapeList_t::iterator  it;

   for(it = shapeList.begin(); it != shapeList.end(); ++it )
   {
      (*it)->Move(diffX, diffY);
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
   velocity(CoordX) = xVel;
   velocity(CoordY) = yVel;
   velocity(CoordZ) = zVel;
}


bool Sprite::CheckTop(CoordType top)
{
   CoordType   minY = currentShape->vertices.col(CoordY).minCoeff();

   return (minY <= top);
}


bool Sprite::CheckBottom(CoordType bottom)
{
   CoordType   maxY = currentShape->vertices.col(CoordY).maxCoeff();

   return (maxY >= bottom);
}


bool Sprite::CheckLeft(CoordType left)
{
   CoordType   minX = currentShape->vertices.col(CoordX).minCoeff();

   return (minX <= left);
}


bool Sprite::CheckRight(CoordType right)
{
   CoordType   maxX = currentShape->vertices.col(CoordX).maxCoeff();

   return (maxX >= right);
}


int32_t Sprite::NumPoints()
{
   return currentShape->NumPoints();
}


int32_t Sprite::MapVertices(VertexListRef list)
{
   return currentShape->MapVertices(list);
}
