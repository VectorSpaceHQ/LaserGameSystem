

#include <hal.h>
#include "MockHal.h"


void MockOnOffSwitch::showLed()
{
}


MockHal::MockHal():
   time(0),
   onOffSwitch()
{
}


bool MockHal::Init()
{
   return true;
}


void MockHal::Delay(int ms)
{
   time += ms;
}


uint32_t MockHal::GetTime()
{
   return time;
}


HAL::OnOffSwitch* MockHal::GetOnOffSwitch(HAL::HalId id)
{
   return &onOffSwitch;
}
