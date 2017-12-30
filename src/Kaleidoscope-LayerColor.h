#pragma once

#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-Macros.h"
#include "LEDUtils.h"
namespace kaleidoscope {
	class LayerColor_ : public KaleidoscopePlugin {
	 public:
	  LayerColor_(void) {}

	  void begin(void) final;


	 private:
	  static void loopHook(const bool postClear);
	  static void setLayerColor(uint8_t currrentLayer, cRGB layerColor);
	};
}
extern kaleidoscope::LayerColor_ LayerColor;
