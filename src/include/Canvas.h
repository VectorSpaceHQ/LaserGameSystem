/*
 * Canvas.h
 *
 *  Created on: Jan 17, 2019
 *      Author: athiessen
 */

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include <list>
#include <stdint.h>

#include "CanvasObject.h"
#include "DisplayIfc.h"
#include "CanvasObject.h"


class Canvas
{
private:
   typedef std::list<CanvasObject*>  CanvasObjectList_t;

   CanvasObjectList_t   canvasObjects;
   VertexList_t         allVertices;
   DisplayIfc&          displayIfc;

public:
   uint32_t             width;
   uint32_t             height;
   int32_t              top;
   int32_t              right;
   int32_t              bottom;
   int32_t              left;

public:
   Canvas(uint32_t _width, uint32_t _height, DisplayIfc& _displayImpl);
   ~Canvas() {};

   void Clear();
   void AddObject(CanvasObject* newObject);
   void RemoveObject(CanvasObject* newObject);
   void Render();

private:
   /***
    * Iterate over all the shapes and sum up the number of vertices
    */
   int32_t  TotalVertices();

   void CollectVertices();
};


#endif /* __CANVAS_H__ */
