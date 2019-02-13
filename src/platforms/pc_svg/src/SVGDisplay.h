
#include <hal.h>
#include <DisplayIfc.h>


class SVGDisplay: public DisplayIfc
{
private:
   HAL::Hal&   hal;

public:
   SVGDisplay(HAL::Hal& _hal);
   void Render(Eigen::Ref<const VertexList_t> vertices);

};
