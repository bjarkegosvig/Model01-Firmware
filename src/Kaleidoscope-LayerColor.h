#pragma once

#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-Macros.h"
#include "LEDUtils.h"
namespace kaleidoscope {
	class LayerColor_ : public kaleidoscope::Plugin {
	 public:
	  LayerColor_(void) {}

  	    kaleidoscope::EventHandlerResult onSetup(void);
		kaleidoscope::EventHandlerResult afterEachCycle();


	 private:
	  static void setLayerColor(uint8_t currrentLayer, cRGB layerColor);
	};
}
extern kaleidoscope::LayerColor_ LayerColor;
