#pragma once
/*
* Plugin that blocks a held shift key, can be used in Macros
* Taken from:
*  https://kaleidoscope.readthedocs.io/en/latest/UPGRADING.html#releasing-keys-with-macros-release-or-u-ur-uc
*/
#include "Kaleidoscope.h"

namespace kaleidoscope {
    namespace plugin {
        // When activated, this plugin will suppress any `shift` key (including modifier
        // combos with `shift` a flag) before it's added to the HID report.
        class ShiftBlocker : public Plugin {

         public:
          EventHandlerResult onAddToReport(Key key) {
            if (active_ && key.isKeyboardShift())
              return EventHandlerResult::ABORT;
            return EventHandlerResult::OK;
          }

          void enable() {
            active_ = true;
          }
          void disable() {
            active_ = false;
          }

         private:
          bool active_{false};

        };

    } // namespace plugin
} // namespace kaleidoscope

kaleidoscope::plugin::ShiftBlocker ShiftBlocker;
