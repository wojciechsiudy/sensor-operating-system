Sensor Operating System
===

It is a response for Robotic Operating System for users who want serialize data from multiple sensors in convinient way without endless recompilation and dealing with libraries or overcomplication. The application...

# Usage

@todo: Manual


# runtime requirements
 - optional flag in kernel config `CONFIG_POSIX_MQUEUE=y` if run on POSIX-compilant UNIX OS or 3'rd party IPC support on Windows since XP
 - for Pyhton-implemented external sensors using API the package `posix-ipc` is required

