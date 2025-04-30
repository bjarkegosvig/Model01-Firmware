#pragma once


/** This 'enum' is a list of all the macros used by the Model 100's firmware
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

enum { MACRO_VERSION_INFO,  // Build version info
       MACRO_ANY,           // Any key macro
       M_SQ,                // Make the qwerty keymap the default one 
       M_SC,                // Make the colemak keymap the default one
       M_SG,                // Make the gaming keymap the default one
       L_AE,                // Type danish letter æ
       L_OE,                // Type danish letter ø
       L_AA,                // Type danish letter å
       M_RCTRL_F,           // Press Right CTRL + F
       M_PW,                // Password macro
       M_LPW                // Linux password macro
     };

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */
static void versionInfoMacro(uint8_t key_state) {
  if (keyToggledOn(key_state)) {
        Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
        Macros.type(PSTR(BUILD_INFORMATION));
  }
}

static void macroSwitchQwerty(KeyEvent &event) {
  if (keyToggledOn(event.state))
  {
    Layer.move(QWERTY);
    Layer.activate(QWERTY);
    OneShot.enableStickabilityForModifiers();
  }
}

static void macroSwitchColemak(KeyEvent &event) {
  if (keyToggledOn(event.state))
  {
    Layer.move(COLEMAK);
    Layer.activate(COLEMAK);
    OneShot.enableStickabilityForModifiers();
  }
}

static void macroSwitchGame(KeyEvent &event) {
  if (keyToggledOn(event.state))
  {
    Layer.move(GAME);
    Layer.activate(GAME);
    OneShot.disableStickabilityForModifiers();
  }
}

static void macroRCTRLF(KeyEvent &event) {
  if (keyToggledOn(event.state))
  {
    MACRO(I(25), D(RightControl), T(F), U(RightControl) );
  }
}

static void pwMacro(KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    Macros.type(PSTR("lalal"));
    Macros.tap(Key_Enter);
  }
}

static void pwLinuxMacro(KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    Macros.type(PSTR("lalal"));
    Macros.tap(Key_Enter);
  }
}

/**
 * Handle how to type the danish letter in connection with the compose system
 * on the operation system. On Windows this requires the program wincompose
 * The compose key is set to Right Alt.
 */
static void handleDanish(uint8_t macro_id, KeyEvent &event) {
    if (!keyToggledOn(event.state))
        return;

  bool should_capitalize = Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_LeftShift) || Kaleidoscope.hid().keyboard().wasModifierKeyActive(Key_RightShift);
    static constexpr Key compose = Key_RightAlt;
    static const macro_t *symbols[] = {
        // æ is <compose ae>
        MACRO(Tr(compose), T(A), T(E)),
        // Æ is <compose aE>
        MACRO(Tr(compose), T(A), T(LeftShift), T(E)),

        // ø is <compose o/>
        MACRO(Tr(compose), T(O), T(Slash)), 
        // Ø is <compose  O/> handled with ShiftBlocker on the / part
        MACRO(Tr(compose), T(LeftShift), T(O)),
      
        // å is <ComposeKey aa>
        MACRO(Tr(compose), T(O), T(A)),
        // Å is <ComposeKey aA>
        MACRO(Tr(compose), T(O), T(LeftShift), T(A)),
        
    };

    if (should_capitalize) {
        OneShot.cancel();
        Macros.play(symbols[(macro_id - L_AE) * 2 + 1]);
        if (macro_id == L_OE) {
            // Handle typing / and not ?O/O/ in 'Ø' even though shift is held
            ShiftBlocker.enable();
            Macros.play(MACRO(T(Slash)));
            ShiftBlocker.disable();
        }
    } else {
        Macros.play(symbols[(macro_id - L_AE) * 2]);
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
const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  switch (macro_id) {
    case MACRO_VERSION_INFO:
        versionInfoMacro(event.state);
        break;
    case M_SQ:
        macroSwitchQwerty(event);
        break;
    case M_SC:
        macroSwitchColemak(event);
        break;
    case M_SG:
        macroSwitchGame(event);
        break;
    case L_AE:
    case L_OE:
    case L_AA:
        handleDanish(macro_id, event);
        break;
    case M_RCTRL_F:
        if (keyToggledOn(event.state)) 
        {
            return MACRO(I(25),
                   D(RightControl), T(F), U(RightControl) );
        }
        break;
    case M_PW:
        pwMacro(event);
        break;
    case M_LPW:
        pwLinuxMacro(event);
        break;
  }

  return MACRO_NONE;
}
