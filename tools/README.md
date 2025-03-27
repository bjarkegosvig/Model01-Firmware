# README.md

## Colormap ##

To apply a colormap to the keyboard run
```
colormap/apply_colormap <palette>
```
Palette can be

* bgk
* ega
* pastel

To change the colormap edit the file `colormap/colormap.txt`  
The mapping between `colormap.txt` and the keyboard can be seen in `colormap/colormap-layout.pdf`

### To get focus help menu ###
```
./focus help 
```

### To check the current EEPROM contents ###

```
./focus eeprom.contents
```
### To reset the EEPROM ###

1. `./clear-eeprom`
2. Re-flash from the Arduino IDE

**After changing the EEPROM, power-cycle the keyboard.**

## Udev ##
To setup udev rules for keyboardio keyboards run:
```
udev/setup_udev.sh
```
