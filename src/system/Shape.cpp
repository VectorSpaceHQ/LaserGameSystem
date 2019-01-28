/*
 * Shape.cpp
 *
 *  Created on: Aug 24, 2018
 *      Author: athiessen
 */


#include <Eigen/Dense>
//#include <iostream>

#include "Shape.h"


Shape::Shape():
   vertices(),
   scale(1),
   position(),
   velocity(),
   acceleration()
{
}


Shape::Shape(uint16_t numVertices):
   vertices(numVertices, 4),
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
   vertices.block(0, 0, vertices.rows(), 1) += diffX;
   vertices.block(0, 1, vertices.rows(), 1) += diffY;
}


void Shape::Move(CoordType diffX, CoordType diffY, CoordType diffZ)
{
   vertices.block(0, 0, vertices.rows(), 1) += diffX;
   vertices.block(0, 1, vertices.rows(), 1) += diffY;
   vertices.block(0, 2, vertices.rows(), 1) += diffZ;
}


void Shape::Scale(CoordType _scale)
{
   // Set our new scale
   scale = _scale;
   vertices.block(0, 0, vertices.rows(), 3) *= scale;
}


void Shape::LogMatrix()
{
   //std::cout << "Scale: " << scale << std::endl << vertices << std::endl << std::endl;
}
