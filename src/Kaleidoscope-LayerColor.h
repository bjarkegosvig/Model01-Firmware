#pragma once
#include <Kaleidoscope.h>
#include "Kaleidoscope-LEDControl.h"

namespace kaleidoscope {
	namespace plugin {
		class LayerColor_ : public kaleidoscope::Plugin {
		public:
		LayerColor_(void) {}

			kaleidoscope::EventHandlerResult onSetup(void);
			kaleidoscope::EventHandlerResult afterEachCycle();


		private:
		static void setLayerColor(uint8_t currrentLayer, cRGB layerColor);
		};
	}	
}
extern kaleidoscope::plugin::LayerColor_ LayerColor;
