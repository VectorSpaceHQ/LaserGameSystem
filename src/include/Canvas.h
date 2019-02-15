/*
 * Canvas.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <list>

#include "CanvasObject.h"
#include "DisplayIfc.h"
#include "CanvasObject.h"


class Canvas
{
public:
   uint32_t             width;
   uint32_t             height;
   int32_t              top;
   int32_t              right;
   int32_t              bottom;
   int32_t              left;

private:
   DisplayIfc&          displayIfc;
   CanvasObjectList_t   objects;
   VertexList_t         allVertices;

public:
   Canvas(uint32_t _width, uint32_t _height, DisplayIfc& _displayImpl);
   ~Canvas() {};

   void Clear();
   void AddObject(CanvasObject* newObject);
   void Render();

private:
   /***
    * Iterate over all the shapes and sum up the number of vertices
    */
   int32_t  TotalVertices();

   void CollectVertices();
};


#endif /* __CANVAS_H__ */
