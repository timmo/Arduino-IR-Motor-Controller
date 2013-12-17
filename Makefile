#BOARD_TAG    = atmega168
# MONITOR_PORT = /dev/tty.usbserial*

BOARD_TAG    = attiny85
MCU = attiny85
F_CPU = 8000000
#ALTERNATE_CORE = tiny8
ALTERNATE_CORE_PATH = /Applications/Arduino.app/Contents/Resources/Java/hardware/attiny
ARDUINO_VAR_PATH = /Applications/Arduino.app/Contents/Resources/Java/hardware/attiny/variants/tiny8

ARDUINO_LIBS = IRremote


include /Users/timmo/Coding/github/Arduino-Makefile/arduino-mk/Arduino.mk
