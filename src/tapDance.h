#pragma once

/** Tapdance enum
*/
enum {CT_LCK,   // lock/unlock PC
      CT_BLD,   // IDE build shortcut
      CT_CLN,   // :/;
      CT_MNS,   // -/_
      CT_ST,    // ESC/No key, used for programming the keyboard
      CT_LPB,   // [/(
      CT_RPB,   // ]/)
      CT_CP,    // Windows cmd copy/paste
      CT_WEZ,    // Windows cmd copy/paste
     };

/**  Tapdance imp
*/
void tapDanceAction(uint8_t tap_dance_index, KeyAddr key_addr, uint8_t tap_count,
                    kaleidoscope::plugin::TapDance::ActionType tap_dance_action){
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
      
      case CT_CP:
      return tapDanceActionKeys(tap_count, tap_dance_action,
                                LCTRL(Key_Insert),
                                LSHIFT(Key_Insert));
     case CT_WEZ:
     return tapDanceActionKeys(tap_count, tap_dance_action,
                                LALT(Key_L),
                                LCTRL(LSHIFT(Key_P)));
  }
}

