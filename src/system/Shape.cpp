/*
 * Shape.cpp
 *
 *  Created on: Aug 24, 2018
 *      Author: athiessen
 */


#include <Eigen/Dense>

#include "Shape.h"


Shape::Shape():
   vertices(0, static_cast<int>(CoordMax)),
   backupVertices(0, static_cast<int>(CoordMax)),
   position(),
   scale(1)
{
}


Shape::Shape(uint16_t numVertices):
   vertices(numVertices, static_cast<int>(CoordMax)),
   backupVertices(0, static_cast<int>(CoordMax)),     // Only reserve memory for backup when *actually* requested to backup
   position(),
   scale(1)
{
}


Shape::Shape(const Shape& other):
   vertices(other.vertices.rows(), static_cast<int>(CoordMax)),
   backupVertices(other.backupVertices.rows(), static_cast<int>(CoordMax)),
   position(other.position),
   scale(other.scale)
{
   if(this != &other)
   {
      vertices = other.vertices;
      backupVertices = other.backupVertices;
   }
}


Shape::~Shape()
{
   vertices.resize(0, CoordMax);
   ClearBackup();
}


void Shape::Backup()
{
   backupVertices.resize(vertices.rows(), CoordMax);
   backupVertices = vertices;
}


void Shape::Restore()
{
   vertices.resize(backupVertices.rows(), CoordMax);
   vertices = backupVertices;
}


void Shape::ClearBackup()
{
   backupVertices.resize(0, CoordMax);
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


void Shape::MoveToPosition()
{
   vertices.block(0, CoordX, vertices.rows(), 1) += position(CoordX);
   vertices.block(0, CoordY, vertices.rows(), 1) += position(CoordY);
   vertices.block(0, CoordZ, vertices.rows(), 1) += position(CoordZ);
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
