# Mega2560_WDT
How to use watchdog timer on Arduino Mega2560 with sleep mode.

Target:
Use sleep mode with periodicaly waking up to do some work.
Watchdog timer has a 8 sec max work time.
To sleep for more than 8 seconds create a variable to store how much times we wake up.
