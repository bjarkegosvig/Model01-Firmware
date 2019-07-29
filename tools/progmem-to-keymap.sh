#! /bin/sh
FOCUS="$(dirname $0)/focus"

roLayers="$(${FOCUS} keymap.roLayers)"

if [ -z "${roLayers}" ]; then
    echo "No PROGMEM layers found, bailing out." >&2
    exit 1
fi

${FOCUS} "keymap.map $(${FOCUS} keymap.map | sed -e "s#^\(\([0-9]* *\)\{384\}\).*#\1\1#")"
