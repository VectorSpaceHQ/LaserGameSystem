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


// Positions in the coordinate
enum CoordPositions
{
   CoordX      = 0,
   CoordY      = 1,
   CoordZ      = 2,
   CoordColor  = 3,

   // Do not add below this line
   CoordMax
};

typedef int16_t CoordType;
typedef Eigen::Array<CoordType, 1, CoordMax>                               Coordinate;    // 3D Coordinate + color
typedef Eigen::Array<CoordType, 1, 3>                                      Magnitude;     // 3D Magnitude
typedef Eigen::Array<CoordType, Eigen::Dynamic, CoordMax, Eigen::RowMajor> VertexList_t;  //


class Shape
{
public:
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
   int32_t NumPoints();
   int32_t MapVertices(Eigen::Ref<VertexList_t> list);

   void LogMatrix();
};


#endif   // __shape_h__
