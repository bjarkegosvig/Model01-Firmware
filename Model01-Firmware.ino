// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

/**
   These #include directives pull in the Kaleidoscope firmware core,
   as well as the Kaleidoscope plugins we use in the Model 01's firmware

   https://bitbucket.org/jamesnvc/keyboardiolayout
*/

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for TapDance
#include "Kaleidoscope-TapDance.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for an "LED off mode"
#include "LED-Off.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

#include <Kaleidoscope-OneShot.h>
#include <Kaleidoscope-Escape-OneShot.h>
#include <Kaleidoscope-LED-ActiveModColor.h>
#include <Kaleidoscope-Colormap.h>
#include <Kaleidoscope-Focus.h>
#include <Kaleidoscope-LEDEffect-BootGreeting.h>
#include <Kaleidoscope-SpaceCadet.h>
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
#define Key_LT    LSHIFT(Key_Comma)
#define Key_GT    LSHIFT(Key_Period)


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
       MACRO_ANY,
       M_SQ,
       M_SC,
       M_SG
     };

/** Tapdance enum
*/
enum {CT_LCK,
      CT_BLD,
      CT_CLN,
      CT_MNS,
      CT_ST
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

enum { QWERTY, COLEMAK, GAME, FUNCTION, NUMPAD}; // layers
/* This comment temporarily turns off astyle's indent enforcement
     so we can make the keymaps actually resemble the physical key layout better
*/
// *INDENT-OFF*

KEYMAPS(
/*   
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |Sft+Tab/prg |   1  |   2  |   3  |   4  |   5  | Rofi |       |TDBLD |   6  |   7  |   8  |   9  |   0  |    NumLck  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    Tab     |   Q  |   W  |   E  |   R  |   T  |      |       |      |   Y  |   U  |   I  |   O  |   P  |    +=      |
 * |------------+------+------+------+------+------| :/;  |       | -/_  |------+------+------+------+------+------------|
 * |    Shft    |   A  |   S  |   D  |   F  |   G  |------|       |------|   H  |   J  |   K  |   L  |   ;  |    '"      |
 * |------------+------+------+------+------+------|      |       |  Alt |------+------+------+------+------+------------|
 * |    Ctrl    |   Z  |   X  |   C  |   V  |   B  |  Esc |       |      |   N  |   M  |   ,  |   .  |  /   |    _-      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           | Ctrl  |Space | Ent  | Shft |       | Del  | Shft |BckSP | Alt  |
 *                           `----------------------------'       `---------------------------'
 *
 *                                    ,-----------.                        ,-----------.
 *                                    | Layer FUN |                        | Layer FUN |
 *                                    `-----------'                        `-----------'
 */
  [QWERTY] = KEYMAP_STACKED
  (TD(CT_ST),            Key_1,   Key_2,  Key_3,    Key_4,     Key_5,     LALT(Key_P),
   Key_Tab,              Key_Q,   Key_W,  Key_E,    Key_R,     Key_T,     TD(CT_CLN),
   OSM(LeftControl),     Key_A,   Key_S,  Key_D,    Key_F,     Key_G,
   OSM(LeftShift),       Key_Z,   Key_X,  Key_C,    Key_V,     Key_B,     Key_Escape,
   OSM(LeftControl), Key_Spacebar, Key_Enter, OSM(LeftShift),
   ShiftToLayer(FUNCTION),

   TD(CT_BLD),       Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         LockLayer(NUMPAD),
   TD(CT_MNS),       Key_Y,     Key_U,     Key_I,     Key_O,      Key_P,         Key_Equals,
                     Key_H,     Key_J,     Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   OSM(LeftAlt),     Key_N,     Key_M,     Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   Key_Delete, OSM(LeftShift), Key_Backspace, OSM(LeftAlt),
   ShiftToLayer(FUNCTION)),

 /*   Colemake DH Matrix https://colemakmods.github.io/mod-dh/keyboards.html
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |Sft+Tab/prg |   1  |   2  |   3  |   4  |   5  | Rofi |       |TDBLD |   6  |   7  |   8  |   9  |   0  |    NumLck  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    Tab     |   Q  |   W  |   F  |   P  |   B  |      |       |      |   J  |   L  |   U  |   Y  |   ;  |    +=      |
 * |------------+------+------+------+------+------| :/;  |       | -/_  |------+------+------+------+------+------------|
 * |    Shft    |   A  |   R  |   S  |   T  |   G  |------|       |------|   M  |   N  |   E  |   L  |   O  |    '"      |
 * |------------+------+------+------+------+------|      |       |  Alt |------+------+------+------+------+------------|
 * |    Ctrl    |   Z  |   X  |   C  |   D  |   V  |  Esc |       |      |   K  |   H  |   ,  |   .  |  /   |    _-      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           | Ctrl  |Space | Ent  | Shft |       | Del  | Shft |BckSP | Alt  |
 *                           `----------------------------'       `---------------------------'
 *
 *                                    ,-----------.                        ,-----------.
 *                                    | Layer FUN |                        | Layer FUN |
 *                                    `-----------'                        `-----------'
 */
  [COLEMAK] = KEYMAP_STACKED
  (TD(CT_ST),            Key_1,   Key_2,  Key_3,    Key_4,     Key_5,     LALT(Key_P),
   Key_Tab,              Key_Q,   Key_W,  Key_F,    Key_P,     Key_B,     TD(CT_CLN),
   OSM(LeftControl),     Key_A,   Key_R,  Key_S,    Key_T,     Key_G,
   OSM(LeftShift),       Key_Z,   Key_X,  Key_C,    Key_D,     Key_V,     Key_Escape,
   OSM(LeftControl), Key_Spacebar, Key_Enter, OSM(LeftShift),
   ShiftToLayer(FUNCTION),

   TD(CT_BLD),       Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         LockLayer(NUMPAD),
   TD(CT_MNS),       Key_J,     Key_L,     Key_U,     Key_U,      Key_Semicolon, Key_Equals,
                     Key_M,     Key_N,     Key_E,     Key_L,      Key_O,         Key_Quote,
   OSM(LeftAlt),     Key_K,     Key_H,     Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   Key_Delete, OSM(LeftShift), Key_Backspace, OSM(LeftAlt),
   ShiftToLayer(FUNCTION)),

/* Gaming  
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |Sft+Tab/prg |   1  |   2  |   3  |   4  |   5  | Rofi |       |TDBLD |   6  |   7  |   8  |   9  |   0  |    NumLck  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    Tab     |   Q  |   W  |   E  |   R  |   T  |      |       |      |   Y  |   U  |   I  |   O  |   P  |    +=      |
 * |------------+------+------+------+------+------| :/;  |       | -/_  |------+------+------+------+------+------------|
 * |    Shft    |   A  |   S  |   D  |   F  |   G  |------|       |------|   H  |   J  |   K  |   L  |   ;  |    '"      |
 * |------------+------+------+------+------+------|      |       |  Alt |------+------+------+------+------+------------|
 * |    Ctrl    |   Z  |   X  |   C  |   V  |   B  |  Esc |       |      |   N  |   M  |   ,  |   .  |  /   |    _-      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           | Ctrl  |Space | Ent  | Shft |       | Del  | Shft |BckSP | Alt  |
 *                           `----------------------------'       `---------------------------'
 *
 *                                    ,-----------.                        ,-----------.
 *                                    | Layer FUN |                        | Layer FUN |
 *                                    `-----------'                        `-----------'
 */
  [GAME] = KEYMAP_STACKED
  (TD(CT_ST),            Key_1,   Key_2,  Key_3,    Key_4,     Key_5,     LALT(Key_P),
   Key_Tab,              Key_Q,   Key_W,  Key_E,    Key_R,     Key_T,     TD(CT_CLN),
   OSM(LeftControl),     Key_A,   Key_S,  Key_D,    Key_F,     Key_G,
   OSM(LeftShift),       Key_Z,   Key_X,  Key_C,    Key_V,     Key_B,     Key_Escape,
   OSM(LeftControl), Key_Spacebar, Key_Enter, OSM(LeftShift),
   ShiftToLayer(FUNCTION),

   TD(CT_BLD),       Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         LockLayer(NUMPAD),
   TD(CT_MNS),       Key_Y,     Key_U,     Key_I,     Key_O,      Key_P,         Key_Equals,
                     Key_H,     Key_J,     Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   OSM(LeftAlt),     Key_N,     Key_M,     Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   Key_Delete, OSM(LeftShift), Key_Backspace, OSM(LeftAlt),
   ShiftToLayer(FUNCTION)),


/* 
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |  F1  |  F2  |  F3  |  F4  |  F5  |      |       |      |  F6  |  F7  |  F8  |  F9  |  F10 |    F11     |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |            |   |  |   %  |   {  |   }  |   &  |      |       |      |      | Home |  Up  | End  |Insert|    F12     |
 * |------------+------+------+------+------+------|  <   |       |  >   |------+------+------+------+------+------------|
 * |            |   #  |   $  |   (  |   )  |   *  |------|       |------|      | Left | Down |Right |      | (un)lck    |
 * |------------+------+------+------+------+------| PgDn |       | PgDn |------+------+------+------+------+------------|
 * |            |   @  |   ^  |   [  |   ]  |   ~  |      |       |      |Mute  | VolDn|VolUp |      |   \  |     |      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |  Ctrl |      |      |      |       | GUI  |      | Del  |      |
 *                           `----------------------------'       `---------------------------'
*/

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,        Key_F2,        Key_F3,               Key_F4,                Key_F5,              ___,
   ___,      Key_Pipe,      Key_PRCNT,     Key_LeftCurlyBracket, Key_RightCurlyBracket, Key_AND,             Key_LT,
   ___,      Key_HASH,      Key_DOLLR,     Key_LeftParen,        Key_RightParen,        Key_STAR, 
   ___,      Key_AT,        Key_CARET,     Key_LeftBracket,      Key_RightBracket,      Key_TILDE,           Key_PageUp,
   OSM(LeftControl), ___, ___, ___,
   ___,

M(MACRO_VERSION_INFO),            Key_F6,         Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Key_GT,         XXX,            Key_Home,                 Key_UpArrow,              Key_End,         Key_Insert,       Key_F12,
                   XXX,            Key_LeftArrow,            Key_DownArrow,            Key_RightArrow,  ___,              TD(CT_LCK),
   Key_PageDown,   Consumer_Mute,  Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   Key_LeftGui, ___, Key_Delete, ___,
   ___),

/*  
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |      |      |      |      |      |      |       |      |      |   7  |   8  |   9  |   -  |            |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |            |      |      |      |      |      |      |       |      |      |   4  |   5  |   6  |   +  |            |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |Qwerty|Colmak| Game |      |      |------|       |------|      |   1  |   2  |   3  |   =  |      '     |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |      |      |      |      |      |      |       |      |      |   0  |   .  |   *  |   /  |  Enter     |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |       |      |      |      |       |      |      |      |      |
 *                           `----------------------------'       `---------------------------'
 */
  [NUMPAD] =  KEYMAP_STACKED
  (___, ___,     ___,     ___,     ___, ___, ___,
   ___, ___,     ___,     ___,     ___, ___, ___,
   ___, M(M_SQ), M(M_SC), M(M_SG), ___, ___,
   ___, ___,     ___,     ___,     ___, ___, ___,
   ___, ___, ___, ___,
   ___,

M(MACRO_VERSION_INFO),  ___, Key_7, Key_8,      Key_9,         Key_Minus,          UnlockLayer(NUMPAD),
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

static void macroSwitchQwerty(uint8_t keyState) {
  if (keyToggledOn(keyState))
  {
    UnlockLayer(NUMPAD);
    Layer.defaultLayer(QWERTY);
  }
}

static void macroSwitchColemak(uint8_t keyState) {
  if (keyToggledOn(keyState))
  {
    UnlockLayer(NUMPAD);
    Layer.defaultLayer(COLEMAK);
  }
}

static void macroSwitchGame(uint8_t keyState) {
  if (keyToggledOn(keyState))
  {
    UnlockLayer(NUMPAD);
Layer.defaultLayer(GAME);
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
    case M_SQ:
      macroSwitchQwerty(keyState);
      break;
    case M_SC:
      macroSwitchColemak(keyState);
      break;
    case M_SG:
      macroSwitchGame(keyState);
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
    case CT_ST:
  return tapDanceActionKeys(tap_count, tap_dance_action, LSHIFT(Key_Tab), ___ );
  }
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::HostPowerManagement::Suspend:
    LEDControl.paused = true;
    LEDControl.set_all_leds_to({0, 0, 0});
    LEDControl.syncLeds();
    break;
  case kaleidoscope::HostPowerManagement::Resume:
    LEDControl.paused = false;
    LEDControl.refreshAll();
    break;
  case kaleidoscope::HostPowerManagement::Sleep:
    break;
  }
}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

KALEIDOSCOPE_INIT_PLUGINS(LEDControl,
                          LEDOff,
                          Macros,
                          TapDance,
                          OneShot,
                          ActiveModColorEffect,
                          EscapeOneShot,
                          LayerColor,
                        // The HostPowerManagement plugin allows us to turn LEDs off when then host
                        // goes to sleep, and resume them when it wakes up.
                          HostPowerManagement
                        
                          );



/** The 'setup' function is one of the two standard Arduino sketch functions.
    It's called when your keyboard first powers up. This is where you set up
    Kaleidoscope and any plugins.
*/

void setup() {  
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup(); 

  // http://www.color-hex.com/color-palette/5361
  ActiveModColorEffect.highlight_color = CRGB(0xba, 0xff, 0xc9);
  ActiveModColorEffect.sticky_color = CRGB(0xff, 0xdf, 0xba);
  TapDance.time_out=170;
 LEDOff.activate();
}

/** loop is the second of the standard Arduino sketch functions.
    As you might expect, it runs in a loop, never exiting.

    For Kaleidoscope-based keyboard firmware, you usually just want to
    call Kaleidoscope.loop(); and not do anything custom here.
*/

void loop() {
  Kaleidoscope.loop();

}
