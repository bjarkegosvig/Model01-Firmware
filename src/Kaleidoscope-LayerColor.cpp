#include "Kaleidoscope-LayerColor.h"
#include "LEDUtils.h"
#include "Kaleidoscope.h"
#include "layers.h"
#include <Kaleidoscope-OneShot.h>

// http://www.color-hex.com/color-palette/5361
// yellow    #b58900  3/3 yellow   136 #af8700 60  10  65 181 137   0  45 100  71
// orange    #cb4b16  9/3 brred    166 #d75f00 50  50  55 203  75  22  18  89  80
// red       #dc322f  1/1 red      160 #d70000 50  65  45 220  50  47   1  79  86
// magenta   #d33682  5/5 magenta  125 #af005f 50  65 -05 211  54 130 331  74  83
// violet    #6c71c4 13/5 brmagenta 61 #5f5faf 50  15 -45 108 113 196 237  45  77
// blue      #268bd2  4/4 blue      33 #0087ff 55 -10 -45  38 139 210 205  82  82
// cyan      #2aa198  6/6 cyan      37 #00afaf 60 -35 -05  42 161 152 175  74  63
// green     #859900  2/2 green     64 #5f8700 60 -20  65 133 153   0  68 100  60

cRGB layer0_color = CRGB(0x0, 0x0, 0x0);
cRGB layer01_color = CRGB(0x255, 0x0, 0x0);
cRGB layer02_color = CRGB(0x0, 0x255, 0x0);
//cRGB layer1_color = CRGB(0x92, 0xb9, 0x38);
cRGB layer1_color = CRGB(106, 90, 205);
cRGB layer2_color = CRGB(127, 255, 212);
namespace kaleidoscope {
kaleidoscope::EventHandlerResult LayerColor_::onSetup(void) {

  return kaleidoscope::EventHandlerResult::OK;
}

kaleidoscope::EventHandlerResult LayerColor_::afterEachCycle() {

      if (Layer.isOn(4)) {
        setLayerColor(4,layer2_color);
        //  https://github.com/keyboardio/Kaleidoscope-MagicCombo
        ::LEDControl.setCrgbAt(1, 1, CRGB(190, 255, 60));
        ::LEDControl.setCrgbAt(1, 2, CRGB(128, 150, 255));
        ::LEDControl.setCrgbAt(1, 3, CRGB(230, 128, 255));
      }
      else if (Layer.isOn(3)) {
        setLayerColor(3,layer1_color); 
      }
      else if (Layer.isOn(2)) {
         setLayerColor(2,layer0_color);
         ::LEDControl.setCrgbAt(0, 0, CRGB(230, 128, 255));
      }
      else if (Layer.isOn(1)) {
         setLayerColor(1,layer0_color);
         ::LEDControl.setCrgbAt(0, 0, CRGB(128, 150, 255));
      }
      else if (Layer.isOn(0)) {
         setLayerColor(0,layer0_color);
         ::LEDControl.setCrgbAt(0, 0, CRGB(190, 255, 60));
      }

      return kaleidoscope::EventHandlerResult::OK;
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
