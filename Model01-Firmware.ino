// -*- mode: c++ -*-

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

/**
   These #include directives pull in the Kaleidoscope firmware core,
   as well as the Kaleidoscope plugins we use in the Model 01's firmware
*/

// avr watchdog for timeout reset
#include <avr/wdt.h>

// The Kaleidoscope core
#include "Kaleidoscope.h"
#include "Kaleidoscope-SpaceCadet.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for TapDance
#include "Kaleidoscope-TapDance.h"


// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"


// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

#include "Kaleidoscope-MouseKeys.h"

#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-LED-ActiveModColor.h"
#include "Kaleidoscope-Colormap.h"
#include "Kaleidoscope-HostOS.h"

#include "Kaleidoscope-FocusSerial.h"

#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-Colormap.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-LED-Palette-Theme.h"

#include "kaleidoscope/device/device.h"    

/**
* My implementation of my keymap.
* @NOTE the include order is important, the files which contains
* functionality used in the subsequent must be included first. 
* So the layer.h which holds the layers enum, must be include
* before macros.h and keymap.h which both uses the layers enum.
*/
#include "src/shiftblocker.h"
#include "src/layers.h"
#include "src/macros.h"
#include "src/tapDance.h"
#include "src/keymap.h"


/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::plugin::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

KALEIDOSCOPE_INIT_PLUGINS(
                          Macros,
                          TapDance,
                          EscapeOneShot,
                          OneShot,
                          ActiveModColorEffect,
                          MouseKeys,
                          FocusSettingsCommand,
                          FocusEEPROMCommand,
                          FocusHostOSCommand,
                          LEDControl,
                          // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
                          // editable keymap in EEPROM.
                          EEPROMSettings,
                          LEDPaletteTheme,
                          ColormapEffect,
                          Focus,
                          ShiftBlocker,
                          // The HostPowerManagement plugin allows us to turn LEDs off when then host
                          // goes to sleep, and resume them when it wakes up.
                          HostPowerManagement

                         );



/** The 'setup' function is one of the two standard Arduino sketch functions.
 * It's called when your keyboard first powers up. This is where you set up
 * Kaleidoscope and any plugins.
 */
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

    // Important for LED Custom Palette, how many paletts we should reserve
  ColormapEffect.max_layers(MaxLayerNum);
  //ColormapEffect.activate();  
//  EEPROMKeymap.setup(MaxLayerNum);

  OneShot.setDoubleTapTimeout(5);

  // http://www.color-hex.com/color-palette/5361
  ActiveModColorEffect.setHighlightColor(CRGB(0xff, 0xff, 0xba));
  ActiveModColorEffect.setStickyColor(CRGB(0xba, 0xe1, 0xff));
  ActiveModColorEffect.setOneShotColor(CRGB(0xba, 0xff, 0xc9));
  TapDance.setTimeout(200);
  OneShot.setTimeout(1000);
  Layer.move(QWERTY);
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();

  // Paint key 3 pink on all layers, if capslock is on
  bool capsState = !!(Kaleidoscope.hid().keyboard().getKeyboardLEDs() & LED_CAPS_LOCK);
  
  // KeyAddr(row, column) matrix reference can be found at 
  // https://github.com/keyboardio/Kaleidoscope/tree/master/plugins/Kaleidoscope-Qukeys
  if (capsState) {
    LEDControl.setCrgbAt(KeyAddr(1,0), CRGB(255, 0, 128));
  } else {
    LEDControl.refreshAt(KeyAddr(1,0));
  }

  // Paint key 4 pink on all layers, if numlock is on
  bool numState = !!(Kaleidoscope.hid().keyboard().getKeyboardLEDs() & LED_NUM_LOCK);

  if (numState) {
    LEDControl.setCrgbAt(KeyAddr(0,0), CRGB(255, 0, 128));
  } else {
    LEDControl.refreshAt(KeyAddr(0,0));
  }
}


