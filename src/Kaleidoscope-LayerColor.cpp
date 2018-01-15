#include "Kaleidoscope-LayerColor.h"
#include "LEDUtils.h"
#include "Kaleidoscope.h"
#include "layers.h"
#include <Kaleidoscope-OneShot.h>

// http://www.color-hex.com/color-palette/5361
cRGB layer0_color = CRGB(0x0, 0x0, 0x0);
cRGB layer1_color = CRGB(0xba, 0xff, 0xc9);
cRGB layer2_color = CRGB(0xff, 0xdf, 0xba);
namespace kaleidoscope {
  void LayerColor_::begin(void) {
    Kaleidoscope.useLoopHook(loopHook);
  }

  void LayerColor_::loopHook(bool postClear) {
    if (!postClear)
      return;

      if (Layer.isOn(2)) {
        setLayerColor(2,layer2_color);
      }
      else if (Layer.isOn(1)) {
        setLayerColor(1,layer1_color); 
      }
      else if (Layer.isOn(0)) {
         setLayerColor(0,layer0_color);
      }
  }


  void LayerColor_::setLayerColor(uint8_t currrentLayer, cRGB layerColor) 
  {
    for (uint8_t r = 0; r < ROWS; r++) {
      for (uint8_t c = 0; c < COLS; c++) {
        Key k = Layer.lookupOnActiveLayer(r, c);
        Key layer_key = Layer.getKey(currrentLayer, r, c);

      if (::OneShot.isOneShotKey(k)) {
        // do nothing to allow activeModColorEffect to function
      }

       else if ((k != layer_key)) {
          ::LEDControl.refreshAt(r, c);
        } else {
          ::LEDControl.setCrgbAt(r, c, layerColor);
        }
      }
    } 
  };
}
kaleidoscope::LayerColor_ LayerColor;
