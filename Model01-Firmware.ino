// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

/**
   These #include directives pull in the Kaleidoscope firmware core,
   as well as the Kaleidoscope plugins we use in the Model 01's firmware
*/

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for TapDance
#include "Kaleidoscope-TapDance.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for an "LED off mode"
#include "LED-Off.h"

#include <Kaleidoscope-OneShot.h>
#include <Kaleidoscope-Escape-OneShot.h>
#include <kaleidoscope/hid.h>
#include <Kaleidoscope-LED-ActiveModColor.h>
#include <Kaleidoscope-Colormap.h>
#include <Kaleidoscope-Focus.h>
#include "src/Kaleidoscope-LayerColor.h"


#define Key_AT    LSHIFT(Key_2)
#define Key_STAR  LSHIFT(Key_8)
#define Key_DOLLR LSHIFT(Key_4)
#define Key_CARET LSHIFT(Key_6)
#define Key_PRCNT LSHIFT(Key_5)
#define Key_EXCLM LSHIFT(Key_1)
#define Key_HASH  LSHIFT(Key_3)
#define Key_AND   LSHIFT(Key_7)
#define Key_LCB   LSHIFT(Key_LeftBracket)
#define Key_RCB   LSHIFT(Key_RightBracket)
#define Key_TILDE LSHIFT(Key_Backtick)


/** This 'enum' is a list of all the macros used by the Model 01's firmware
    The names aren't particularly important. What is important is that each
    is unique.

    These are the names of your macros. They'll be used in two places.
    The first is in your keymap definitions. There, you'll use the syntax
    `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`

    The second usage is in the 'switch' statement in the `macroAction` function.
    That switch statement actually runs the code associated with a macro when
    a macro key is pressed.
*/

enum { MACRO_VERSION_INFO,
       MACRO_NUMLCK,
       MACRO_ANY
     };

/** Tapdance enum
*/
enum {CT_LCK,
      CT_BLD,
      CT_CLN,
      CT_MNS
     };


/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
    keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
    keymap.

    Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
    of first the left hand's layout, followed by the right hand's layout.

    Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
    defined as part of the USB HID Keyboard specification. You can find the names
    (if not yet the explanations) for all the standard `Key_` defintions offered by
    Kaleidoscope in these files:
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
       https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h

    Additional things that should be documented here include
      using ___ to let keypresses fall through to the previously active layer
      using XXX to mark a keyswitch as 'blocked' on this layer
      using ShiftToLayer() and LockLayer() keys to change the active keymap.
      the special nature of the PROG key
      keeping NUM and FN consistent and accessible on all layers


    The "keymaps" data structure is a list of the keymaps compiled into the firmware.
    The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
    macros switch to key layers based on this list.



    A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
    Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
*/

/**
    Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
    The third one is layer 2.
    This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
    the numbers 0, 1 and 2.
*/

enum { QWERTY, FUNCTION, NUMPAD}; // layers
/* This comment temporarily turns off astyle's indent enforcement
     so we can make the keymaps actually resemble the physical key layout better
*/
// *INDENT-OFF*

KEYMAPS(
/*   

 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * | Prog       |   {  |   @  |   *  |   $  |   ^  | Rofi |       |TDBLD |   %  |   !  |   #  |   &  |   }  |    NumLck  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    Tab     |   Q  |   W  |   E  |   R  |   T  |      |       |  Ent |   Y  |   U  |   I  |   O  |   P  |    +=      |
 * |------------+------+------+------+------+------|  Tab |       |      |------+------+------+------+------+------------|
 * | Shft       |   A  |   S  |   D  |   F  |   G  |------|       |------|   H  |   J  |   K  |   L  |   ;  |    '"      |
 * |------------+------+------+------+------+------|      |       |  _-  |------+------+------+------+------+------------|
 * | Ctrl       |   Z  |   X  |   C  |   V  |   B  |  :/; |       |      |   N  |   M  |   ,  |   .  |  /   |    _-      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           | Ctrl  |Space | Alt  | Esc  |       | Shft |Space |BckSP | Alt  |
 *                           `----------------------------'       `---------------------------'
 *
 *                                    ,-----------.                        ,-----------.
 *                                    | Layer FUN |                        | Layer FUN |
 *                                    `-----------'                        `-----------'
 */
  [QWERTY] = KEYMAP_STACKED
  (___,                  Key_1,   Key_2,  Key_3,    Key_4,     Key_5, LALT(Key_P),
   Key_Tab,              Key_Q,   Key_W,  Key_E,    Key_R,     Key_T,     Key_Tab,
   OSM(LeftControl),     Key_A,   Key_S,  Key_D,    Key_F,     Key_G,
   OSM(LeftShift),       Key_Z,   Key_X,  Key_C,    Key_V,     Key_B,     TD(CT_CLN),
   OSM(LeftControl), Key_Spacebar, OSM(LeftAlt), Key_Escape,
   ShiftToLayer(FUNCTION),

   TD(CT_BLD),       Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         M(MACRO_NUMLCK),
   Key_Enter,        Key_Y,     Key_U,     Key_I,     Key_O,      Key_P,         Key_Equals,
                     Key_H,     Key_J,     Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   TD(CT_MNS),       Key_N,     Key_M,     Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   OSM(LeftShift), Key_Spacebar, Key_Backspace, Key_LeftGui,
   ShiftToLayer(FUNCTION)),


/*  
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |  F1  |  F2  |  F3  |  F4  |  F5  |      |       |PTrck |  F6  |  F7  |  F8  |  F9  |  F10 |    F11     |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    tab     |   |  |   %  |   {  |   }  |   &  |      |       |      | NTrck| Home |  Up  | End  |Insert|    F12     |
 * |------------+------+------+------+------+------| PgUp |       |  P/P |------+------+------+------+------+------------|
 * |     Home   |   #  |   $  |   (  |   )  |   *  |------|       |------|      | Left | Down |Right |      | (un)lck    |
 * |------------+------+------+------+------+------| PgDn |       |      |------+------+------+------+------+------------|
 * |     End    |   @  |   ^  |   [  |   ]  |   ~  |      |       |      |Mute  | VolDn|VolUp |      |   \  |     |      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |  Ctrl |  Del |      |      |       | Shft |      | Del  |      |
 *                           `----------------------------'       `---------------------------'
 */

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,        Key_F2,        Key_F3,               Key_F4,                Key_F5,              XXX,
   ___,      Key_Pipe,      Key_PRCNT,     Key_LeftCurlyBracket, Key_RightCurlyBracket, Key_AND,             Key_PageUp,
   Key_Home, Key_HASH,      Key_DOLLR,     Key_LeftParen,        Key_RightParen,        Key_STAR, 
   Key_End,  Key_AT,        Key_CARET,     Key_LeftBracket,      Key_RightBracket,      Key_TILDE,           Key_PageDown,
   OSM(LeftControl), Key_Delete, ___, ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_Home,                 Key_UpArrow,              Key_End,         Key_Insert,       Key_F12,
                               XXX,                    Key_LeftArrow,            Key_DownArrow,            Key_RightArrow,  ___,              TD(CT_LCK),
   System_MainMenu,            Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   OSM(LeftShift), ___, Key_Delete, ___,
   ___),

/*  
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |      |      |      |      |      |      |       |      |      |   7  |   8  |   9  |   -  |            |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |            |      |      |      |      |      |      |       |      |      |   4  |   5  |   6  |   +  |            |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |      |      |      |      |      |------|       |------|      |   1  |   2  |   3  |   =  |      '     |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |      |      |      |      |      |      |       |      |      |   0  |   .  |   *  |   /  |  Enter     |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |       |      |      |      |       |      |      |      |      |
 *                           `----------------------------'       `---------------------------'
 */
  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_7, Key_8,      Key_9,         Key_Minus,          ___,
   ___,                    ___, Key_4, Key_5,      Key_6,         LSHIFT(Key_Equals), ___,
                           ___, Key_1, Key_2,      Key_3,         Key_Equals,         Key_Quote,
   ___,                    ___, Key_0, Key_Period, LSHIFT(Key_9), Key_Slash,          Key_Enter,
   ___, ___, ___, ___,
   ___),

) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
    When a key bound to the macro is pressed, this macro
    prints out the firmware build information as virtual keystrokes
*/

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

static void toggleNumPad(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    if (Layer.isOn(NUMPAD)) {
      Layer.off(NUMPAD);
    } else {
      Layer.on(NUMPAD);
    }
  }
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
    case MACRO_NUMLCK:
      toggleNumPad(keyState);
      break;
  }
  return MACRO_NONE;
}


/**  Tapdance imp
*/
void tapDanceAction(uint8_t tap_dance_index, byte row, byte col, uint8_t tap_count, kaleidoscope::TapDance::ActionType tap_dance_action) {
  switch (tap_dance_index) {
    case CT_LCK:
      return tapDanceActionKeys(tap_count, tap_dance_action, LGUI(Key_L), LCTRL(LALT(Key_Delete)));
    case CT_BLD:
      return tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_F11), LCTRL(Key_F5), LSHIFT(Key_F5));
    case CT_CLN:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                LSHIFT(Key_Semicolon),
                                Key_Semicolon);
    case CT_MNS:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                Key_Minus,
                                LSHIFT(Key_Minus));
  }
}


/** The 'setup' function is one of the two standard Arduino sketch functions.
    It's called when your keyboard first powers up. This is where you set up
    Kaleidoscope and any plugins.
*/

void setup() {


  // Next, tell Kaleidoscope which plugins you want to use.
  // The order can be important. For example, LED effects are
  // added in the order they're listed here.
  Kaleidoscope.use(
    // LEDControl provides support for other LED modes
    &LEDControl,

    // We start with the LED effect that turns off all the LEDs.
    &LEDOff,

    // The macros plugin adds support for macros
    &Macros,

    // Tapdance
    &TapDance,

    // Oneshot modifiers
    &OneShot,
    &EscapeOneShot,

    // LED effects
    &LayerColor,
    &ActiveModColorEffect
  );

  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  // http://www.color-hex.com/color-palette/5361
  ActiveModColorEffect.highlight_color = CRGB(0x26, 0x8b, 0xd2);
  ActiveModColorEffect.sticky_color = CRGB(0xd3, 0x36, 0x82);
}

/** loop is the second of the standard Arduino sketch functions.
    As you might expect, it runs in a loop, never exiting.

    For Kaleidoscope-based keyboard firmware, you usually just want to
    call Kaleidoscope.loop(); and not do anything custom here.
*/

void loop() {
  Kaleidoscope.loop();

}
