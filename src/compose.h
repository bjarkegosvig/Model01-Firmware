#pragma once
/*
* Old way of handling danish letters using the compose2 function
* The compose2 function was used in the macroAction functions as 
* shown below:
*
*    const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
*      switch (macro_id) {
*         case L_AE:
*          compose2(Key_A, true, Key_E, true, event);
*          break;
*        case L_OE:
*          compose2(Key_O, true, Key_Slash, false, event);
*          break;
*        case L_AA:
*          compose2(Key_O, false, Key_A, true, event);
*          break;
*       };
*/
#include "Kaleidoscope.h"

using namespace kaleidoscope 

// compose2, press, release and tap functions are taken from https://github.com/lldata/Model01-Firmware/blob/master/Model01-Firmware.ino
// uses right alt as compose key
void compose2(Key key1, bool shift1, Key key2, bool shift2, KeyEvent &event) {
  if (!keyToggledOn(event.state)) {
    return;
  }
    bool shifted = Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftShift)
  || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightShift);
  
  if(shifted) release(Key_LeftShift);
  
  tap(Key_RightAlt);
  if (shifted && shift1) press(Key_LeftShift);
  tap(key1);
  if (shifted && shift1) release(Key_LeftShift);
  if (shifted && shift2) press(Key_LeftShift);
  tap(key2);
  if (shifted && shift2) release(Key_LeftShift);
}

static void press(Key key) {
  Kaleidoscope.hid().keyboard().pressKey(key);
  Kaleidoscope.hid().keyboard().sendReport();
}

static void release(Key key) {
  Kaleidoscope.hid().keyboard().releaseKey(key);
  Kaleidoscope.hid().keyboard().sendReport();
}

static void tap(Key key) {
  press(key);
  release(key);
}
