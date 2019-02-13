
#include <hal.h>


class MockOnOffSwitch: public HAL::OnOffSwitch
{
private:
   void showLed();
   bool ledOn;

public:
   MockOnOffSwitch():
      ledOn(false)
   {
   }

   void Init()
   {
      ledOn = false;
   }

   void On()
   {
      ledOn = true;
      showLed();
   }

   void Off()
   {
      ledOn = false;
      showLed();
   }

   void Toggle()
   {
      ledOn = !ledOn;
      showLed();
   }
};


class MockHal: public HAL::Hal
{
private:
   uint32_t          time;
   MockOnOffSwitch   onOffSwitch;

public:
   MockHal();
   ~MockHal() {};

   bool Init();

   void Delay(int ms);

   int GetNumRotaryEncoders() { return 0; }
   int GetNumPushButtons() { return 0; }
   int GetNumPushServos() { return 0; }
   int GetNumPushOnOffSwitches() { return 0; }

   HAL::OnOffSwitch* GetOnOffSwitch(HAL::HalId id);
};
