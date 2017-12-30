// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif


/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */


// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
//#include "Kaleidoscope-LEDControl.h"


/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_ANY
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { QWERTY, FUNCTION }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

KEYMAPS(
/*   
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * | Prog/+=    |   1  |   2  |   3  |   4  |   5  | Rofi |       |TDBLD |   6  |   7  |   8  |   9  |   0  |    NumLck  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    Tab     |   Q  |   W  |   E  |   R  |   T  |      |       |  Ent |   Y  |   U  |   I  |   O  |   P  |    +=      |
 * |------------+------+------+------+------+------|  Tab |       |      |------+------+------+------+------+------------|
 * | Shft       |   A  |   S  |   D  |   F  |   G  |------|       |------|   H  |   J  |   K  |   L  |   ;  |    '"      |
 * |------------+------+------+------+------+------|      |       | CTRL |------+------+------+------+------+------------|
 * | Ctrl       |   Z  |   X  |   C  |   V  |   B  |  Esc |       |+SPC  |   N  |   M  |   ,  |   .  |  /   |    _-      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |   F   |Space |  G   |  R   |       | Shft | Ent  |BckSP | _-   |
 *                           `----------------------------'       `---------------------------'
 */

  [QWERTY] = KEYMAP_STACKED
  (___,             Key_1, Key_2, Key_3, Key_4, Key_5, ___,
   Key_Tab,         Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
   Key_LeftShift,   Key_A, Key_S, Key_D, Key_F, Key_G,
   Key_LeftControl, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
   Key_F,           Key_Spacebar, Key_G, Key_R,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),  Key_6, Key_7, Key_8,     Key_9,         Key_0,         ___,
   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
                  Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
   Key_RightAlt,  Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),

 /*  
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |  F1  |  F2  |  F3  |  F4  |  F5  |      |       |PTrck |  F6  |  F7  |  F8  |  F9  |  F10 |    F11     |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |            |      |      |      |      |      |      |       |      |      |      |      |      |      |            |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |      |      |      |      |      |------|       |------|      |      |      |      |      |            |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |      |      |      |      |      |      |       |      |      |      |      |      |      |            |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |       |      |      |      |       |      |      |      |      |
 *                           `----------------------------'       `---------------------------'
 */

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,        Key_F2,        Key_F3,               Key_F4,           Key_F5,              XXX,
   ___,      ___,           ___,           ___,                  ___,              ___,                 ___,
   ___,      ___,           ___,           ___,                  ___,              ___, 
   ___,      ___,           ___,           ___,                  ___,              ___,                 ___,
   ___,      ___, ___, ___,
   ___,

   ___,     Key_F6,         Key_F7,        Key_F8,               Key_F9,           Key_F10,          Key_F11,
   ___,     ___,            ___,           ___,                  ___,              ___,              Key_F12,
            ___,            ___,           ___,                  ___,              ___,              ___,
   ___,     ___,            ___,           ___,                  ___,              ___,              ___,
   ___, ___, ___, ___,
___),

) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;

  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;
  }
  return MACRO_NONE;
}


/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(

    // The macros plugin adds support for macros
    &Macros
  );

}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
