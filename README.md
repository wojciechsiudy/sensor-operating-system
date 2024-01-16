Sensor Operating System
===

It is a response for Robotic Operating System for users who want serialize data from multiple sensors in convinient way without endless recompilation and dealing with libraries or overcomplication. The application is configured with JSON containg basic config and sensor specification.

# Supported data sources:
 - serial port
 - MQTT
 - inter-process message queue

Additionally serial port can be both text or binary. If serial is binary the user must compile parser implementing `serialParsedSensor` and providing class abstract factory. See `ExampleParser.cpp` for details.

# Usage

You can specify any input or output directory. Defaults are `sos_config.json` and `output/`. The flag `-c` clears the previous output.
`./sensor-operating-system [-i <path to config>] [-o <path to output>] [-c]`

# runtime requirements
 - optional flag in kernel config `CONFIG_POSIX_MQUEUE=y` if run on POSIX-compilant UNIX OS or 3'rd party IPC support on Windows since XP
 - for Pyhton-implemented external sensors using API the package `posix-ipc` is required

