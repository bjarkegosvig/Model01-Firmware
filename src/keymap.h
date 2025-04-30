# pragma once

/** The Model 100's key layouts are defined as 'keymaps'. By default, there are three
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
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   keeping NUM and FN consistent and accessible on all layers
  *
  * The PROG key is special, since it is how you indicate to the board that you
  * want to flash the firmware. However, it can be remapped to a regular key.
  * When the keyboard boots, it first looks to see whether the PROG key is held
  * down; if it is, it simply awaits further flashing instructions. If it is
  * not, it continues loading the rest of the firmware and the keyboard
  * functions normally, with whatever binding you have set to PROG. More detail
  * here: https://community.keyboard.io/t/how-the-prog-key-gets-you-into-the-bootloader/506/8
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
 * Custom key code defines
 */
#define Key_EXCLM LSHIFT(Key_1)
#define Key_AT    LSHIFT(Key_2)
#define Key_HASH  LSHIFT(Key_3)
#define Key_DOLLR LSHIFT(Key_4)
#define Key_PRCNT LSHIFT(Key_5)
#define Key_CARET LSHIFT(Key_6)
#define Key_AND   LSHIFT(Key_7)
#define Key_STAR  LSHIFT(Key_8)
#define Key_PLUS  LSHIFT(Key_Equals)
#define Key_LCB   LSHIFT(Key_LeftBracket)
#define Key_RCB   LSHIFT(Key_RightBracket)
#define Key_TILDE LSHIFT(Key_Backtick)
#define Key_LT    LSHIFT(Key_Comma)
#define Key_GT    LSHIFT(Key_Period)
#define Key_MCHAT LGUI(LSHIFT(Key_A))

#define Key_MWL   LGUI(LCTRL(Key_LeftArrow))
#define Key_MWR   LGUI(LCTRL(Key_RightArrow))
#define Key_MXL   LGUI(LSHIFT(Key_LeftArrow))
#define Key_MXR   LGUI(LSHIFT(Key_RightArrow))
#define Key_MAX   LGUI(Key_LeftArrow)
#define Key_MIN   LGUI(Key_RightArrow)
#define Key_GMX   LGUI(Key_M)

#define Key_MMON  LCTRL(LSHIFT(Key_Enter))
#define Key_MDT   LSHIFT(LCTRL(Key_L))
#define Key_DTL   LSHIFT(LCTRL(Key_LeftBracket))
#define Key_DTR   LSHIFT(LCTRL(Key_RightBracket))
#define Key_Launch LGUI(LALT(Key_Space))
// clang-format off

KEYMAPS(
/*
 * ,------------------------------------------------------.       ,------------------------------------------------------.
*  |  Esc/prg   |   1  |   2  |   3  |   4  |   5  | Rofi |       |  GUI |   6  |   7  |   8  |   9  |   0  | OS LaySel  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    Tab     |   Q  |   W  |   E  |   R  |   T  | Tab  |       |      |   Y  |   U  |   I  |   O  |   P  |    +=      |
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
 *                                    | Layer Fun |                        | Layer NUM |
 *                                    `-----------'                        `-----------'
 */
  [QWERTY] = KEYMAP_STACKED
  (Key_Escape,            Key_1,   Key_2,  Key_3,    Key_4,     Key_5,     Key_Launch,
   Key_Tab,               Key_Q,   Key_W,  Key_E,    Key_R,     Key_T,     Key_Tab,
   OSM(LeftControl),      Key_A,   Key_S,  Key_D,    Key_F,     Key_G,
   OSM(LeftShift),        Key_Z,   Key_X,  Key_C,    Key_V,     Key_B,     TD(CT_CLN),
   OSM(LeftControl), Key_Spacebar, Key_Enter, Key_Escape,
   ShiftToLayer(FUNCTION),

   TD(CT_WEZ),        Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         LockLayer(NUMPAD),
   Key_Escape,        Key_Y,     Key_U,     Key_I,     Key_O,      Key_P,         Key_Equals,
                      Key_H,     Key_J,     Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   Key_Minus,         Key_N,     Key_M,     Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   OSM(LeftGui), OSM(LeftShift), Key_Backspace, OSM(LeftAlt),
   ShiftToLayer(ARROW)),

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
   ShiftToLayer(FUNCTION),

   TD(CT_CP),        Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         OSL(LAYSEL),
   TD(CT_MNS),       Key_J,     Key_L,     Key_U,     Key_Y,      Key_Semicolon, Key_Equals,
                     Key_M,     Key_N,     Key_E,     Key_I,      Key_O,         Key_Quote,
   Key_Delete,       Key_K,     Key_H,     Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   OSM(LeftAlt), OSM(LeftShift), Key_Backspace, OSM(RightControl),
   ShiftToLayer(ARROW)),

/* Gaming
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |  Esc/prg   |   1  |   2  |   3  |   4  |   5  |  N   |       |  GUI |   6  |   7  |   8  |   9  |   0  | OS LaySel  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    Tab     |   Q  |   W  |   E  |   R  |   T  |      |       |      |   Y  |   U  |   I  |   O  |   P  |    +=      |
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
   Key_Tab,              Key_Q,   Key_W,  Key_E,    Key_R,     Key_T,     Key_M,
   Key_LeftControl,      Key_A,   Key_S,  Key_D,    Key_F,     Key_G,
   Key_LeftShift,        Key_Z,   Key_X,  Key_C,    Key_V,     Key_B,     Key_Enter,
   Key_LeftControl, Key_Spacebar, Key_LeftShift,    Key_LeftAlt,
   ShiftToLayer(GAMEFCN),

   ___,            Key_6,                     Key_7,                    Key_8,                      Key_9,                  Key_0,            OSL(LAYSEL),
   Key_GT,         ___,                       Key_Home,                 Key_UpArrow,                Key_End,                Key_Insert,       Key_PLUS,
                   ___,                       Key_LeftArrow,            Key_DownArrow,              Key_RightArrow,         ___,              ___,
   Key_PageDown,   ___,                       ___,                      ___,                        ___, Key_Backslash,    Key_Pipe,
   ___, ___, ___, ___,
   ShiftToLayer(GAMEFCN)),

   /*Key_LeftGui,      Key_6,     Key_7,     Key_8,     Key_9,      Key_0,         OSL(LAYSEL),
   TD(CT_MNS),       Key_Y,     Key_U,     Key_I,     Key_O,      Key_P,         Key_Equals,
                     Key_H,     Key_J,     Key_K,     Key_L,      Key_Semicolon, Key_Quote,
   OSM(LeftAlt),     Key_N,     Key_M,     Key_Comma, Key_Period, Key_Slash,     Key_Minus,
   Key_Delete, OSM(LeftShift), Key_Backspace, OSM(LeftAlt),
   ShiftToLayer(GAMEFCN)),*/

/* Gaming function
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |      ~     |   F1 |  F2  |  F3  |   F4 |  F5  |      |       |      |  F6  |   F7 |   F8 |   F9 |  F10 | OS LaySel  |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |  CapsLck   |  KP7 |  KP8 |  KP9 |   R  |      |      |       |      |      |      |      |      |      |            |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |    PgUp    |  KP4 |  KP5 |  KP6 |  KP0 |      |------|       |------|      |      |      |      |      |            |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |    PgDn    |  KP1 |  KP2 |  KP3 |      |      |      |       |      |      |      |      |      |      |            |
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
  (Key_KeypadNumLock,   Key_F1,          Key_F2,          Key_F3,         Key_F4,       XXX,    XXX,
   Key_CapsLock,        Key_Keypad7,     Key_Keypad8,     Key_Keypad9,    Key_R,        XXX,    XXX,
   Key_PageUp,          Key_Keypad4,     Key_Keypad5,     Key_Keypad6,    Key_Keypad0,  XXX,
   Key_PageDown,        Key_Keypad1,     Key_Keypad2,     Key_Keypad3,    XXX,          XXX,    XXX,
   Key_LeftControl, Key_Spacebar, Key_LeftShift,    Key_LeftAlt,
   ShiftToLayer(FUNCTION),

   XXX,     Key_F6,         Key_F7,  Key_F8,  Key_F9,   Key_F10,       OSL(LAYSEL),
   XXX,     XXX,            XXX,     XXX,     XXX,      XXX,           XXX,
            XXX,            XXX,     XXX,     XXX,      XXX,           XXX,
   XXX,     XXX,            XXX,     XXX,     XXX,      XXX,           XXX,
   Key_Delete, OSM(LeftShift), Key_Backspace, OSM(LeftAlt),
   ShiftToLayer(ARROW)),



/*
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |  F1  |  F2  |  F3  |  F4  |  F5  |      |       |      |  F6  |  F7  |  F8  |  F9  |  F10 |    F11     |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |    +       |   |  |   {  |   %  |   }  |   &  |      |       |      | Mute | Home |  Up  | End  |Insert|    +       |
 * |------------+------+------+------+------+------|  <   |       |  >   |------+------+------+------+------+------------|
 * |            |   #  |   (  |   $  |   )  |   *  |------|       |------| Play | Left | Down |Right |      | (un)lck    |
 * |------------+------+------+------+------+------| PgDn |       | PgDn |------+------+------+------+------+------------|
 * |            |   @  |   [  |   ^  |   ]  |   ~  |      |       |      | VolDn|VolUp |NextTk|PrevTk|   \  |     |      |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |  Ctrl |      |      |      |       |      |      | Del  |      |
 *                           `----------------------------'       `---------------------------'
*/

  [FUNCTION] =  KEYMAP_STACKED
  (Key_Backtick,      Key_F1,        Key_F2,                 Key_F3,               Key_F4,                Key_F5,              ___,
   Key_PLUS, Key_Pipe,      Key_LeftCurlyBracket,   Key_PRCNT,            Key_RightCurlyBracket, Key_AND,             Key_LT,
   ___,      Key_HASH,      Key_LeftParen,          Key_DOLLR,            Key_RightParen,        Key_STAR,
   ___,      Key_AT,        Key_LeftBracket,        Key_CARET,            Key_RightBracket,      Key_TILDE,           Key_PageUp,
   OSM(LeftControl), ___, ___, ___,
   ___,

   ___,            Key_F6,                    Key_F7,                   Key_F8,                     Key_F9,                 Key_F10,          Key_F11,
   Key_GT,         Consumer_Mute,             Key_Home,                 Key_UpArrow,                Key_End,                Key_Insert,       Key_PLUS,
                   Consumer_PlaySlashPause,   Key_LeftArrow,            Key_DownArrow,              Key_RightArrow,         ___,              TD(CT_LCK),
   Key_PageDown,   Consumer_VolumeDecrement,  Consumer_VolumeIncrement, Consumer_ScanPreviousTrack, Consumer_ScanNextTrack, Key_Backslash,    Key_Pipe,
   ___, ___, Key_Delete, ___,
   ShiftToLayer(LAYSEL)),

/*
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |      |      |      |      |      |      |       |      |      |      |      |      |      |            |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |            |MV2Mon|VD LFT|VD RGT|MakeVD|      |      |       |      |      |      |      |      |      |            |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |MaxL  |MaxDn |MaxUp |MaxR  |      |------|       |------|      |      |      |      |      |            |
 * |------------+------+------+------+------+------|Mute  |       |      |------+------+------+------+------+------------|
 * |            |      |      |  MSD |MSU   |      |Teams |       |  `   |      |      |      |      |      |            |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |       |      |      |      |       |      |      |      |      |
 *                           `----------------------------'       `---------------------------'
 */
  [ARROW] =  KEYMAP_STACKED
  (___, ___,         ___,        ___,                  ___,                      ___,                  ___,
   ___, Key_MMON,    Key_DTL,    Key_DTR,              Key_MDT,                  ___,                  LGUI(Key_O),
   ___, Key_MXL,     Key_MXR,    Key_MAX,              Key_MIN,                  Key_GMX,
   ___, ___,         ___,        Key_MWL,              Key_MWR,                  ___,                  Key_MCHAT,
   ___, ___, ___, ___,
   ShiftToLayer(LAYSEL),

   M(M_RCTRL_F),     ___,                       ___,            ___,            ___,            ___,                M(M_PW),
   ___,              ___,                       Key_Home,       Key_UpArrow,    Key_End,        ___,                M(M_LPW),
                    LCTRL(Key_RightBracket),    Key_LeftArrow,  Key_DownArrow,  Key_RightArrow, ___,                ___,
   Key_Backtick,    ___,                        ___,            ___,            ___,            ___,                ___,
   ___, ___, Key_Delete, ___,
   ___),


/*
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |      |      |      |      |      |      |       |      |      |      |      |      |      |            |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |            |Numpad|Qwerty|Colmak|      |      |      |       |      |      |      |      |      |      |            |
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
   ___, M(M_SQ), M(M_SC), M(M_SG),  ___,      ___, ___,
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

 /*
 * ,------------------------------------------------------.       ,------------------------------------------------------.
 * |            |      |      |      |      |      |      |       |      |      |      |      |      |  -   |            |
 * |------------+------+------+------+------+-------------|       |------+------+------+------+------+------+------------|
 * |            |      |      |      |      |      |      |       |      |   .  |   7  |   8  |   9  |   +  |      *     |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |      |      |      |      |      |------|       |------|   0  |   4  |   5  |   6  |   =  |      '     |
 * |------------+------+------+------+------+------|      |       |      |------+------+------+------+------+------------|
 * |            |      |      |      |      |      |      |       |      |   ,  |   1  |   2  |   3  |   /  |Unlck layer |
 * `------------+------+------+------+------+-------------'       `-------------+------+------+------+------+------------'
 *                           ,----------------------------.       ,---------------------------.
 *                           |       |      |      |      |       |      |      |      |      |
 *                           `----------------------------'       `---------------------------'
 */
  [NUMPAD] =  KEYMAP_STACKED
  (___, ___,     ___,     ___,      ___,      ___, ___,
   ___, ___,     ___,     ___,      ___,      ___, ___,
   ___, ___,     ___,     ___,      ___,      ___,
   ___, ___,     ___,     ___,      ___,      ___, ___,
   ___, ___, ___, ___,
   ___,



   OSL(LAYSEL),            ___,         XXX,    XXX,        XXX,           Key_Minus,           UnlockLayer(NUMPAD),
   ___,                    Key_Period,  Key_7,  Key_8,      Key_9,         LSHIFT(Key_Equals),  LSHIFT(Key_9),
                           Key_0,       Key_4,  Key_5,      Key_6,         Key_Equals,          Key_Quote,
   ___,                    Key_Comma,   Key_1,  Key_2,      Key_3,         Key_Slash,           UnlockLayer(NUMPAD),
   ___, ___, ___, ___,
   ___)

) // KEYMAPS(

/* Re-enable astyle's indent enforcement */
// clang-format on

