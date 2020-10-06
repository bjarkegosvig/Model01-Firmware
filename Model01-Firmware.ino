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

// avr watchdog for timeout reset
#include <avr/wdt.h>

// The Kaleidoscope core
#include <Kaleidoscope.h>

#include "Kaleidoscope-LEDEffect-BootGreeting.h"

#include <Kaleidoscope-SpaceCadet.h>

// Support for macros
#include <Kaleidoscope-Macros.h>

// Support for TapDance
#include <Kaleidoscope-TapDance.h>

// Support for controlling the keyboard's LEDs
#include <Kaleidoscope-LEDControl.h>

// Support for host power management (suspend & wakeup)
#include <Kaleidoscope-HostPowerManagement.h>

#include <Kaleidoscope-MouseKeys.h>

#include <Kaleidoscope-OneShot.h>
#include <Kaleidoscope-Escape-OneShot.h>
#include <Kaleidoscope-LED-ActiveModColor.h>
#include <Kaleidoscope-Colormap.h>
#include <Kaleidoscope-LEDEffect-BootGreeting.h>
//#include "src/Kaleidoscope-LayerColor.h"

#include <Kaleidoscope-FocusSerial.h>
#include <Kaleidoscope-EEPROM-Settings.h>
#include "Kaleidoscope-EEPROM-Keymap.h"
#include <Kaleidoscope-LED-Palette-Theme.h>
#include <Kaleidoscope-Colormap.h>


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
#define Key_AWDW  LALT(LSHIFT(Key_H))
#define Key_AWIW  LALT(LSHIFT(Key_L))
#define Key_AWMM  LCTRL(LGUI(Key_Enter))
#define Key_MCHAT  LCTRL(LSHIFT(Key_M))
#define Key_MMON  LGUI(LSHIFT(Key_LeftArrow))
#define Key_MXL   LGUI(Key_LeftArrow)
#define Key_MXR   LGUI(Key_RightArrow)
#define Key_MAX   LGUI(Key_UpArrow)
#define Key_MIN   LGUI(Key_DownArrow)
#define Key_MDT   LGUI(LCTRL(Key_D))
#define Key_DTL   LGUI(LCTRL(Key_LeftArrow))
#define Key_DTR   LGUI(LCTRL(Key_RightArrow))

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
       M_SG,
       M_ARW,
       M_RS,
       L_AE,
       L_OE,
       L_AA
     };

/** Tapdance enum
*/
enum {CT_LCK,
      CT_BLD,
      CT_CLN,
      CT_MNS,
      CT_ST,
      CT_LPB,
      CT_RPB
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

enum { QWERTY, COLEMAK, GAME, GAMEFCN, ARWGAME, FUNCTION, NUMPAD, LAYSEL, MaxLayerNum}; // layer
/* This comment temporarily turns off astyle's indent enforcement
     so we can make the keymaps actually resemble the physical key layout better
*/
// *INDENT-OFF*

KEYMAPS(
/*
 * ,------------------------------------------------------.       ,------------------------------------------------------.
*  |  Esc/prg   |   1  |   2  |   3  |   4  |   5  | Rofi |       |  GUI |   6  |   7  |   8  |   9  |   0  | OS LaySel  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    Tab     |   Q  |   W  |   E  |   R  |   T  |{/(/[ |       |]/)/} |   Y  |   U  |   I  |   O  |   P  |    +=      |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |    Shft    |   A  |   S  |   D  |   F  |   G  |------|       |------|   H  |   J  |   K  |   L  |   ;  |    '"      |
 * |------------+------+------+------+------+------|      |       |  -_  |------+------+------+------+------+------------|
 * |    Ctrl    |   Z  |   X  |   C  |   V  |   B  | :/;  |       |      |   N  |   M  |   ,  |   .  |  /   |    _-      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           | Ctrl  |Space | Ent  | Esc  |       | GUI  | Shft |BckSP | Alt  |
 *                           `----------------------------'       `---------------------------'
 *
 *                                    ,-----------.                        ,-----------.
 *                                    | Layer Num |                        | Layer FUN |
 *                                    `-----------'                        `-----------'
 */
  [QWERTY] = KEYMAP_STACKED
  (Key_Escape,           Key_1,   Key_2,  Key_3,    Key_4,     Key_5,     LGUI(Key_P),
   Key_Tab,              Key_Q,   Key_W,  Key_E,    Key_R,     Key_T,     TD(CT_LPB),
   OSM(LeftControl),     Key_A,   Key_S,  Key_D,    Key_F,     Key_G,
   OSM(LeftShift),       Key_Z,   Key_X,  Key_C,    Key_V,     Key_B,     TD(CT_CLN),
   OSM(LeftControl), Key_Spacebar, Key_Enter, Key_Escape,
   ShiftToLayer(NUMPAD),

   Key_LeftGui,      Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         OSL(LAYSEL),
   TD(CT_RPB),       Key_Y,     Key_U,     Key_I,     Key_O,      Key_P,         Key_Equals,
                     Key_H,     Key_J,     Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   Key_Minus,        Key_N,     Key_M,     Key_Comma, Key_Period, Key_Slash,    Key_Minus,
   Key_LeftGui, OSM(LeftShift), Key_Backspace, OSM(LeftAlt),
   ShiftToLayer(FUNCTION)),

 /*   Colemake DH Matrix https://colemakmods.github.io/mod-dh/keyboards.html
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |  Esc/prg   |   1  |   2  |   3  |   4  |   5  | Rofi |       |  GUI |   6  |   7  |   8  |   9  |   0  | OS LaySel  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    Tab     |   Q  |   W  |   F  |   P  |   B  |      |       |      |   J  |   L  |   U  |   Y  |   ;  |    +=      |
 * |------------+------+------+------+------+------| :/;  |       | -/_  |------+------+------+------+------+------------|
 * |    Shft    |   A  |   R  |   S  |   T  |   G  |------|       |------|   M  |   N  |   E  |   I  |   O  |    '"      |
 * |------------+------+------+------+------+------|      |       | Del  |------+------+------+------+------+------------|
 * |    Ctrl    |   Z  |   X  |   C  |   D  |   V  |  Esc |       |      |   K  |   H  |   ,  |   .  |  /   |    _-      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           | Ctrl  |Space | Ent  | Shft |       | Alt  | Shft |BckSP | Ctrl  |
 *                           `----------------------------'       `---------------------------'
 *
 *                                    ,-----------.                        ,-----------.
 *                                    | Layer FUN |                        | Layer FUN |
 *                                    `-----------'                        `-----------'
 */
  [COLEMAK] = KEYMAP_STACKED
  (Key_Escape,           Key_1,   Key_2,  Key_3,    Key_4,     Key_5,     LALT(Key_P),
   Key_Tab,              Key_Q,   Key_W,  Key_F,    Key_P,     Key_B,     TD(CT_CLN),
   OSM(LeftControl),     Key_A,   Key_R,  Key_S,    Key_T,     Key_G,
   OSM(LeftShift),       Key_Z,   Key_X,  Key_C,    Key_D,     Key_V,     Key_Escape,
   OSM(LeftControl), Key_Spacebar, Key_Enter, OSM(LeftShift),
   ShiftToLayer(NUMPAD),

   Key_LeftGui,      Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         OSL(LAYSEL),
   TD(CT_MNS),       Key_J,     Key_L,     Key_U,     Key_Y,      Key_Semicolon, Key_Equals,
                     Key_M,     Key_N,     Key_E,     Key_I,      Key_O,         Key_Quote,
   Key_Delete,       Key_K,     Key_H,     Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   OSM(LeftAlt), OSM(LeftShift), Key_Backspace, OSM(RightControl),
   ShiftToLayer(FUNCTION)),

/* Gaming
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |  Esc/prg   |   1  |   2  |   3  |   4  |   5  |  N   |       |  GUI |   6  |   7  |   8  |   9  |   0  | OS LaySel  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    M       |   Q  |   W  |   E  |   R  |   T  |      |       |      |   Y  |   U  |   I  |   O  |   P  |    +=      |
 * |------------+------+------+------+------+------|  M   |       | -/_  |------+------+------+------+------+------------|
 * |    Shft    |   A  |   S  |   D  |   F  |   G  |------|       |------|   H  |   J  |   K  |   L  |   ;  |    '"      |
 * |------------+------+------+------+------+------|      |       |  Alt |------+------+------+------+------+------------|
 * |    Ctrl    |   Z  |   X  |   C  |   V  |   B  |  Ent |       |      |   N  |   M  |   ,  |   .  |  /   |    _-      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           | Ctrl  |Space | Shft | Alt  |       | Del  | Shft |BckSP | Alt  |
 *                           `----------------------------'       `---------------------------'
 *
 *                                    ,-----------.                        ,-----------.
 *                                    | Layer FUN |                        | Layer FUN |
 *                                    `-----------'                        `-----------'
 */
[GAME] = KEYMAP_STACKED
  (Key_Escape,           Key_1,   Key_2,  Key_3,    Key_4,     Key_5,     Key_N,
   Key_M,              Key_Q,   Key_W,  Key_E,    Key_R,     Key_T,     Key_M,
   Key_LeftControl,      Key_A,   Key_S,  Key_D,    Key_F,     Key_G,
   Key_LeftShift,        Key_Z,   Key_X,  Key_C,    Key_V,     Key_B,     Key_Enter,
   Key_LeftControl, Key_Spacebar, Key_LeftShift,    Key_LeftAlt,
   ShiftToLayer(GAMEFCN),

   Key_LeftGui,      Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         OSL(LAYSEL),
   TD(CT_MNS),       Key_Y,     Key_U,     Key_I,     Key_O,      Key_P,         Key_Equals,
                     Key_H,     Key_J,     Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   OSM(LeftAlt),     Key_N,     Key_M,     Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   Key_Delete, OSM(LeftShift), Key_Backspace, OSM(LeftAlt),
   ShiftToLayer(GAMEFCN)),

/* Gaming function
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |      ~     |   F1 |  F2  |  F3  |   F4 |  F5  |      |       |      |  F6  |   F7 |   F8 |   F9 |  F10 | OS LaySel  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |  CapsLck   |      |      |      |      |      |      |       |      |      |   7  |   8  |   9  |      |            |
 * |------------+------+------+------+------+------|  6   |       |      |------+------+------+------+------+------------|
 * |    PgUp    |   1  |   2  |   3  |   4  |   5  |------|       |------|   0  |   4  |   5  |   6  |      |            |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |    PgDn    |      |      |      |      |      |  Ent |       |      |      |   1  |   2  |   3  |      |            |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           | Ctrl  |Space | Shft | Alt  |       | Del  | Shft |BckSP | Alt  |
 *                           `----------------------------'       `---------------------------'
 *
 *                                    ,-----------.                        ,-----------.
 *                                    | Layer FUN |                        | Layer FUN |
 *                                    `-----------'                        `-----------'
 */
[GAMEFCN] = KEYMAP_STACKED
  (Key_TILDE,           Key_F1,          Key_F2,           Key_F3,           Key_F4,    Key_F5,    Key_N,
   Key_CapsLock,        Key_Q,           Key_UpArrow,      Key_E,            Key_R,     Key_T,     Key_6,
   Key_PageUp,          Key_1,           Key_2,            Key_3,            Key_4,     Key_5,
   Key_PageDown,        Key_Z,           Key_X,            Key_C,            Key_V,     Key_B,     Key_Enter,
   Key_LeftControl, Key_Spacebar, Key_LeftShift,    Key_LeftAlt,
   ShiftToLayer(FUNCTION),

   XXX,     Key_F6,         Key_F7,          Key_F8,          Key_F9,           Key_F10,       OSL(LAYSEL),
   XXX,     XXX,            Key_Keypad7,     Key_Keypad8,     Key_Keypad9,      XXX,           XXX,
            Key_Keypad0,    Key_Keypad4,     Key_Keypad5,     Key_Keypad6,      XXX,           XXX,
   XXX,     XXX,            Key_Keypad1,     Key_Keypad2,     Key_Keypad3,      XXX,           XXX,
   Key_Delete, OSM(LeftShift), Key_Backspace, OSM(LeftAlt),
   ShiftToLayer(NUMPAD)),




  /* Gaming
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |  Esc/prg   |   1  |   2  |   3  |   4  |   5  |  N   |       |  GUI |   6  |   7  |   8  |   9  |   0  | OS LaySel  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    Tab     |   Q  |  Up  |   E  |   R  |   T  |      |       |      |   Y  |   U  |   I  |   O  |   P  |    +=      |
 * |------------+------+------+------+------+------|  M   |       | -/_  |------+------+------+------+------+------------|
 * |    Shft    | Left | Down |Right |   F  |   G  |------|       |------|   H  |   J  |   K  |   L  |   ;  |    '"      |
 * |------------+------+------+------+------+------|      |       |  Alt |------+------+------+------+------+------------|
 * |    Ctrl    |   Z  |   X  |   C  |   V  |   B  |  Ent |       |      |   N  |   M  |   ,  |   .  |  /   |    _-      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           | Ctrl  |Space | Shft | Alt  |       | Del  | Shft |BckSP | Alt  |
 *                           `----------------------------'       `---------------------------'
 *
 *                                    ,-----------.                        ,-----------.
 *                                    | Layer FUN |                        | Layer FUN |
 *                                    `-----------'                        `-----------'
 */
[ARWGAME] = KEYMAP_STACKED
  (Key_Escape,           Key_1,           Key_2,            Key_3,            Key_4,     Key_5,     Key_N,
   Key_Tab,              Key_Q,           Key_UpArrow,      Key_E,            Key_R,     Key_T,     Key_M,
   Key_LeftControl,      Key_LeftArrow,   Key_DownArrow,    Key_RightArrow,   Key_F,     Key_G,
   Key_LeftShift,        Key_Z,           Key_X,            Key_C,            Key_V,     Key_B,     Key_Enter,
   Key_LeftControl, Key_Spacebar, Key_LeftShift,    Key_LeftAlt,
   ShiftToLayer(FUNCTION),

   Key_LeftGui,      Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         OSL(LAYSEL),
   TD(CT_MNS),       Key_Y,     Key_U,     Key_I,     Key_O,      Key_P,         Key_Equals,
                     Key_H,     Key_J,     Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   OSM(LeftAlt),     Key_N,     Key_M,     Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   Key_Delete, OSM(LeftShift), Key_Backspace, OSM(LeftAlt),
   ShiftToLayer(NUMPAD)),




/*
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |  F1  |  F2  |  F3  |  F4  |  F5  |      |       |  Rst |  F6  |  F7  |  F8  |  F9  |  F10 |    F11     |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |            |   |  |   %  |   {  |   }  |   &  |      |       |      | Mute | Home |  Up  | End  |Insert|    F12     |
 * |------------+------+------+------+------+------|  <   |       |  >   |------+------+------+------+------+------------|
 * |            |   #  |   $  |   (  |   )  |   *  |------|       |------| Play | Left | Down |Right |      | (un)lck    |
 * |------------+------+------+------+------+------| PgDn |       | PgDn |------+------+------+------+------+------------|
 * |            |   @  |   ^  |   [  |   ]  |   ~  |      |       |      | VolDn|VolUp |NextTk|PrevTk|   \  |     |      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |  Ctrl |      |      |      |       |      |      | Del  |      |
 *                           `----------------------------'       `---------------------------'
*/

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,        Key_F2,        Key_F3,               Key_F4,                Key_F5,              ___,
   ___,      Key_Pipe,      Key_PRCNT,     Key_LeftCurlyBracket, Key_RightCurlyBracket, Key_AND,             Key_LT,
   ___,      Key_HASH,      Key_DOLLR,     Key_LeftParen,        Key_RightParen,        Key_STAR,
   ___,      Key_AT,        Key_CARET,     Key_LeftBracket,      Key_RightBracket,      Key_TILDE,           Key_PageUp,
   OSM(LeftControl), ___, ___, ___,
   ShiftToLayer(LAYSEL),

   M(M_RS),        Key_F6,                    Key_F7,                   Key_F8,                     Key_F9,                 Key_F10,          Key_F11,
   Key_GT,         Consumer_Mute,             Key_Home,                 Key_UpArrow,                Key_End,                Key_Insert,       Key_F12,
                   Consumer_PlaySlashPause,   Key_LeftArrow,            Key_DownArrow,              Key_RightArrow,         ___,              TD(CT_LCK),
   Key_PageDown,   Consumer_VolumeDecrement,  Consumer_VolumeIncrement, Consumer_ScanPreviousTrack, Consumer_ScanNextTrack, Key_Backslash,    Key_Pipe,
   ___, ___, Key_Delete, ___,
   ___),

/*
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |      |      |      |      |      |      |       |      |      |      |      |      |   -  |            |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |            |MV2Mon|VD LFT|VD RGT|MakeVD|      |      |       |      |   .  |   7  |   8  |   9  |   +  |      *     |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |MaxL  |MaxDn |MaxUp |MaxR  |      |------|       |------|   0  |   4  |   5  |   6  |   =  |      '     |
 * |------------+------+------+------+------+------|Mute  |       |      |------+------+------+------+------+------------|
 * |            |      |      |  MSD |MSU   |      |Teams |       |      |   ,  |   1  |   2  |   3  |   /  |  Enter     |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |       |      |      |      |       |      |      |      |      |
 *                           `----------------------------'       `---------------------------'
 */
  [NUMPAD] =  KEYMAP_STACKED
  (___, ___,         ___,        ___,                  ___,                      ___,                  ___,
   ___, Key_MMON,    Key_DTL,    Key_DTR,              Key_MDT,                  ___,                  ___,
   ___, Key_MXL,     Key_MIN,    Key_MAX,              Key_MXR,                  ___,
   ___, ___,         ___,        Key_mouseScrollDn,    Key_mouseScrollUp,        ___,                  Key_MCHAT,
   ___, ___, ___, ___,
   ___,



M(MACRO_VERSION_INFO),     ___,         XXX,   XXX,        XXX,           Key_Minus,          ___,
   ___,                    Key_Period,  Key_7, Key_8,      Key_9,         LSHIFT(Key_Equals), LSHIFT(Key_9),
                           Key_0,       Key_4, Key_5,      Key_6,         Key_Equals,         Key_Quote,
   ___,                    Key_Comma,   Key_1, Key_2,      Key_3,         Key_Slash,          Key_Enter,
   ___, ___, ___, ___,
   ShiftToLayer(LAYSEL)),

/*
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |      |      |      |      |      |      |       |      |      |      |      |      |      |            |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |            |Qwerty|Colmak| Game |G Arw |      |      |       |      |      |      |      |      |      |            |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |      |      |      |      |      |------|       |------|      |   æ  |   ø  |   å  |      |            |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |      |      |      |      |      |      |       |      |      |      |      |      |      |            |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |       |      |      |      |       |      |      |      |      |
 *                           `----------------------------'       `---------------------------'
 */
  [LAYSEL] =  KEYMAP_STACKED
  (___, ___,     ___,     ___,      ___,      ___, ___,
   ___, M(M_SQ), M(M_SC), M(M_SG),  M(M_ARW),  ___, ___,
   ___, ___,     ___,     ___,      ___,      ___,
   ___, ___,     ___,     ___,      ___,      ___, ___,
   ___, ___, ___, ___,
   ___,



   ___,   ___,    ___,      ___,        ___,      ___,    ___,
   ___,   ___,    ___,      ___,        ___,      ___,    ___,
          ___,    M(L_AE),   M(L_OE),   M(L_AA),  ___,    ___,
   ___,   ___,    ___,      ___,        ___,      ___,    ___,
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
    Layer.move(QWERTY);
    Layer.activate(QWERTY);
    OneShot.enableStickabilityForModifiers();
  }
}

static void macroSwitchColemak(uint8_t keyState) {
  if (keyToggledOn(keyState))
  {
    Layer.move(COLEMAK);
    Layer.activate(COLEMAK);
    OneShot.enableStickabilityForModifiers();
  }
}

static void macroSwitchGame(uint8_t keyState) {
  if (keyToggledOn(keyState))
  {
    Layer.move(GAME);
    Layer.activate(GAME);
    OneShot.disableStickabilityForModifiers();
  }
}


static void macroSwitchArwGame(uint8_t keyState) {
  if (keyToggledOn(keyState))
  {
    Layer.move(ARWGAME);
    Layer.activate(ARWGAME);
    OneShot.disableStickabilityForModifiers();
  }
}

static void macroReset(uint8_t keyState) {
  if (keyToggledOn(keyState))
  {
    wdt_enable(WDTO_120MS);
    while (1) {}
  }
}

/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.e

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
    case M_RS:
      macroReset(keyState);
      break;
     case L_AE:
      compose2(Key_A, true, Key_E, true, keyState);
      break;
    case L_OE:
      compose2(Key_Slash, false, Key_O, true, keyState);
      break;
    case L_AA:
      compose2(Key_O, false, Key_A, true, keyState);
      break;
    case M_ARW:
      macroSwitchArwGame(keyState);
      break;
  }


  return MACRO_NONE;
}

// compose2, press, release and tap functions are taken from https://github.com/lldata/Model01-Firmware/blob/master/Model01-Firmware.ino
// uses right alt as compose key
static void compose2(Key key1, bool shift1, Key key2, bool shift2, uint8_t keyState) {
  if (!keyToggledOn(keyState)) {
    return;
  }
    bool shifted = Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftShift)
  || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightShift);

  tap(Key_RightAlt);
  if (shifted && shift1) press(Key_LeftShift);
  tap(key1);
  if (shifted && shift1) release(Key_LeftShift);
  if (shifted && shift2) press(Key_LeftShift);
  tap(key2);
  if (shifted && shift2) release(Key_LeftShift);
  //release(Key_RightAlt);
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

/**  Tapdance imp
*/
void tapDanceAction(uint8_t tap_dance_index, byte row, byte col, uint8_t tap_count, kaleidoscope::plugin::TapDance::ActionType tap_dance_action) {
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
      return tapDanceActionKeys(tap_count, tap_dance_action, Key_Esc, ___ );

     case CT_LPB:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                Key_LeftBracket,
                                Key_LeftParen);
      case CT_RPB:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                Key_RightBracket,
                                Key_RightParen);
  }
}

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
                          LEDControl,
                          Macros,
                          TapDance,
                          EscapeOneShot,
                          OneShot,
                          ActiveModColorEffect,
                          MouseKeys,
                          // Focus allows bi-directional communication with the host, and is the
                          // interface through which the keymap in EEPROM can be edited.
                          Focus,

                          // FocusSettingsCommand adds a few Focus commands, intended to aid in
                          // changing some settings of the keyboard, such as the default layer (via the
                          // `settings.defaultLayer` command)
                          FocusSettingsCommand,

                          // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
                          // both debugging, and in backing up one's EEPROM contents.
                          FocusEEPROMCommand,
                          // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
                          // editable keymap in EEPROM.
                          EEPROMSettings,
                          EEPROMKeymap,
                          LEDPaletteTheme,
                          ColormapEffect,
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

    // Important for LED Custom Palette, how many paletts we should reserve
  ColormapEffect.max_layers(MaxLayerNum);
//  EEPROMKeymap.setup(MaxLayerNum);

  OneShot.double_tap_time_out = 5;

  // http://www.color-hex.com/color-palette/5361
  ActiveModColorEffect.highlight_color = CRGB(0xba, 0xff, 0xc9);
  ActiveModColorEffect.sticky_color = CRGB(0xff, 0xdf, 0xba);
  TapDance.time_out = 200;
  MouseKeys.wheelDelay = 20;
  MouseKeys.wheelSpeed = 2;
  OneShot.time_out = 1000;
  Layer.move(QWERTY);
}

/** loop is the second of the standard Arduino sketch functions.
    As you might expect, it runs in a loop, never exiting.

    For Kaleidoscope-based keyboard firmware, you usually just want to
    call Kaleidoscope.loop(); and not do anything custom here.
*/

void loop() {
  Kaleidoscope.loop();

}
