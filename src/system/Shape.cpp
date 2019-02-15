/*
 * Shape.cpp
 *
 *  Created on: Aug 24, 2018
 *      Author: athiessen
 */


#include <Eigen/Dense>

#include "Shape.h"


Shape::Shape():
   vertices(),
   backupVertices(),
   scale(1),
   position(),
   velocity(),
   acceleration()
{
}


Shape::Shape(uint16_t numVertices):
   vertices(numVertices, static_cast<int>(CoordMax)),
   backupVertices(numVertices, static_cast<int>(CoordMax)),
   scale(1),
   position(),
   velocity(),
   acceleration()
{
}


Shape::Shape(const Shape& other)
{
   if(this != &other)
   {
      vertices = other.vertices;
      backupVertices = other.backupVertices;
      scale = other.scale;
      position = other.position;
      velocity = other.velocity;
      acceleration = other.acceleration;
   }
}


void Shape::Backup()
{
   backupVertices = vertices;
}


void Shape::Restore()
{
   vertices = backupVertices;
}


void Shape::Move(CoordType diffX, CoordType diffY)
{
   // Update our position
   position(CoordX) += diffX;
   position(CoordY) += diffY;

   // Now update all of our vertices
   vertices.block(0, CoordX, vertices.rows(), 1) += diffX;  // Start at row 0, column X and modify 1 column
   vertices.block(0, CoordY, vertices.rows(), 1) += diffY;  // Start at row 0, column y and modify 1 column
}


void Shape::Move(CoordType diffX, CoordType diffY, CoordType diffZ)
{
   // Update our position
   position(CoordX) += diffX;
   position(CoordY) += diffY;
   position(CoordZ) += diffZ;

   // Now update all of our vertices
   vertices.block(0, CoordX, vertices.rows(), 1) += diffX;  // Start at row 0, column x and modify 1 column
   vertices.block(0, CoordY, vertices.rows(), 1) += diffY;  // Start at row 0, column y and modify 1 column
   vertices.block(0, CoordZ, vertices.rows(), 1) += diffZ;  // Start at row 0, column z and modify 1 column
}


void Shape::Scale(CoordType _scale)
{
   // Set our new scale
   scale = _scale;
   vertices.block(0, CoordX, vertices.rows(), CoordZ + 1) *= scale;
}


void Shape::Scale(CoordType _xScale, CoordType _yScale, CoordType _zScale)
{
   vertices.block(0, CoordX, vertices.rows(), 1) *= _xScale;
   vertices.block(0, CoordY, vertices.rows(), 1) *= _yScale;
   vertices.block(0, CoordZ, vertices.rows(), 1) *= _zScale;
}


int32_t Shape::NumPoints()
{
   return vertices.rows();
}


int32_t Shape::MapVertices(VertexListRef list)
{
   list = vertices;

   return vertices.rows();
}


void Shape::LogMatrix()
{
   //std::cout << "Scale: " << scale << std::endl << vertices << std::endl << std::endl;
}
