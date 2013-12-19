#BOARD_TAG    = atmega168
# MONITOR_PORT = /dev/tty.usbserial*

BOARD_TAG    = attiny85
MCU = attiny85
F_CPU = 8000000
ALTERNATE_CORE = tiny8
#ARDUINO_CORE_PATH = /Applications/Arduino.app/Contents/Resources/Java/hardware/attiny/cores/attiny
ALTERNATE_CORE_PATH = /Applications/Arduino.app/Contents/Resources/Java/hardware/attiny
#ALTERNATE_CORE_PATH = /Applications/Arduino.app/Contents/Resources/Java/hardware/tiny/avr/cores
ARDUINO_VAR_PATH = /Applications/Arduino.app/Contents/Resources/Java/hardware/attiny/variants/tiny8

ARDUINO_LIBS = IRremote_attiny85


include /Users/timmo/Coding/github/Arduino-Makefile/arduino-mk/Arduino.mk
