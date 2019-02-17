/*
 * Shape.h
 *
 *  Created on: Aug 24, 2018
 *      Author: athiessen
 */

#ifndef __shape_h__
#define __shape_h__

#include <Eigen/Dense>
#include <stdint.h>
#include "CanvasObject.h"


class Shape: public CanvasObject
{
public:
   VertexList_t   vertices;

protected:
//   VertexList_t   backupVertices;
   Coordinate     position;         // Where it currently is in normal world space
   uint16_t       scale;

public:
   Shape();
   Shape(uint16_t numVertices);
   Shape(const Shape& other);
   ~Shape();

   // Methods to operate on the vertices
   void Backup();
   void Restore();
   void Move(CoordType diffX, CoordType diffY);
   void Move(CoordType diffX, CoordType diffY, CoordType diffZ);
   void Scale(CoordType _scale);
   void Scale(CoordType _xScale, CoordType _yScale, CoordType _zScale);

   virtual int32_t NumPoints();
   virtual int32_t MapVertices(VertexListRef list);

   void LogMatrix();

public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW

};


#endif   // __shape_h__
