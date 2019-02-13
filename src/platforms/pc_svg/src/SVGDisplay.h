
#include <hal.h>
#include <DisplayIfc.h>
#include <Eigen/Dense>
#include <list>
#include "Shape.h"


struct Frame
{
   uint32_t       startTime;
   VertexList_t   points;

   Frame(uint32_t time, Eigen::Ref<const VertexList_t> vertices):
      startTime(time),
      points(vertices.rows(), static_cast<int>(CoordMax))
   {
      points = vertices;
   }
};

typedef std::list<Frame*>  FrameList_t;

class SVGDisplay: public DisplayIfc
{
private:
   HAL::Hal&         hal;
   uint32_t          numFrames;
   FrameList_t       frames;

public:
   SVGDisplay(HAL::Hal& _hal);
   ~SVGDisplay();
   void Render(Eigen::Ref<const VertexList_t> vertices);
   void PrintFrames(char const * fileName);
};
