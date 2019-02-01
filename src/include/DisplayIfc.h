/*
 * DisplayIfc.h
 *
 *  Created on: Jan 22, 2019
 *      Author: athiessen
 */

#ifndef INCLUDE_DISPLAYIFC_H_
#define INCLUDE_DISPLAYIFC_H_

#include <Eigen/Dense>
#include "Shape.h"


class DisplayIfc
{
public:
   //virtual void Render(Coordinate* _vertices, int32_t _numVertices) = 0;
   virtual void Render(Eigen::Ref<const VertexList_t> vertices) = 0;

protected:
   virtual ~DisplayIfc() {}
   DisplayIfc() {}
};



#endif /* INCLUDE_DISPLAYIFC_H_ */
