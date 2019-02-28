/*
 * CanvasObject.h
 *
 *  Created on: Feb 14, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_CANVASOBJECT_H_
#define INCLUDE_CANVASOBJECT_H_

#include <Eigen/Dense>
#include <stdint.h>

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

typedef float CoordType;
typedef Eigen::Array<CoordType, 1, CoordMax>                               Coordinate;    // 3D Coordinate + color
typedef Eigen::Array<CoordType, 1, 3>                                      Magnitude;     // 3D Magnitude
typedef Eigen::Array<CoordType, Eigen::Dynamic, CoordMax, Eigen::RowMajor> VertexList_t;  //
typedef Eigen::Ref<VertexList_t> VertexListRef;
typedef Eigen::Ref<Coordinate> CoordinateRef;


class CanvasObject
{
public:
   virtual int32_t NumPoints() = 0;
   virtual int32_t MapVertices(VertexListRef list) = 0;

protected:
   CanvasObject() {}
   virtual ~CanvasObject() {}
};


#endif /* INCLUDE_CANVASOBJECT_H_ */
