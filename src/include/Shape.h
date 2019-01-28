/*
 * Shape.h
 *
 *  Created on: Aug 24, 2018
 *      Author: athiessen
 */

#ifndef __shape_h__
#define __shape_h__

#include <stdint.h>
#include <Eigen/Dense>


typedef int16_t CoordType;

typedef Eigen::Matrix<CoordType, 1, 4> Coordinate;    // 3D Coordinate + color
typedef Eigen::Matrix<CoordType, 1, 3> Magnitude;     // 3D Magnitude


class Shape
{
public:
   typedef Eigen::Array<CoordType, Eigen::Dynamic, 4>  VertexList_t;

   VertexList_t   vertices;

protected:
   VertexList_t   backupVertices;
   uint16_t       scale;
   Coordinate     position;         // Where it currently is in normal world space
   Magnitude      velocity;         // The direction/scale of the X/Y vector
   Magnitude      acceleration;     // The current acceleration (future?)

public:
   Shape();
   Shape(uint16_t numVertices);
   Shape(const Shape& other);

   // Methods to operate on the vertices
   void Backup();
   void Restore();
   void Move(CoordType diffX, CoordType diffY);
   void Move(CoordType diffX, CoordType diffY, CoordType diffZ);
   void Scale(CoordType _scale);

   void LogMatrix();
};


#endif   // __shape_h__
