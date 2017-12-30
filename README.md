# Keyboardio Model 01 Firmware 
My keymaps. Current there are two branches bgk which contains my daily layout and the gaming branch containing a layout for gaming

The daily layout uses my own plugin which colors the active keys on the non default keymap





### Linux

```sh
mkdir -p $HOME/Arduino
cd $HOME/Arduino 
```

## Download hardware platform, including library source code 

```sh
mkdir -p hardware/keyboardio

## then clone the hardware definitions to make them available to the arduino environment
git clone --recursive https://github.com/keyboardio/Arduino-Boards.git hardware/keyboardio/avr
````


# Build and flash the firmware

Before you begin, make sure your Model 01 is connected to your computer.

### Option 1: From the command line

```sh
cd Model01-Firmware
make flash
```

When the builder tells you to hit Enter to continue, hold down "Prog" in the top left corner of your keyboard and hit Enter.

### Option 2: From the Arduino IDE


Open the sketch you wish to flash (for example, `Model01-Firmware.ino`).

Click the Upload button or press `Ctrl-U`.

Hold down the "Prog" key in the top left corner of your keyboard, until the compile finishes and the upload begins.



# Updating the firmware and libraries

From time to time, you may want to pull the latest version of this firmware from GitHub. To do that, navigate to the Model01-Firmware directory in your shell and pull the latest code.

```sh
cd Model01-Firmware
git pull
```

After that, you'll want to update the Kaleidoscope libraries.


### Linux

```sh
cd $HOME/Arduino/hardware/keyboardio/avr
make update-submodules
```


