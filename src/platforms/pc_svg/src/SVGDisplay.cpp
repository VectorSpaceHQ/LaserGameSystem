
#include <DisplayIfc.h>
#include <Eigen/Dense>
#include <hal.h>
#include "SVGDisplay.h"


SVGDisplay::SVGDisplay(HAL::Hal& _hal):
   hal(_hal)
{
}

void SVGDisplay::Render(Eigen::Ref<const VertexList_t> vertices)
{

}
