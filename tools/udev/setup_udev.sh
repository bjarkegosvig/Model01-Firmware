#!/bin/bash
sudo cp udev/60-kaleidoscope.rules /etc/udev/rules.d/
sudo udevadm control --reload-rules 
sudo udevadm trigger --attr-match=vendor='Keyboardio'
