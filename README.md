# OS Monitoring and Automatic Restarter

## Why?

I have a server environment but it frequently shows kernel panic :(

This problem is resolved with a workaround now, but I have worries about it.

And to make matters worse, I'll travel starting tomorrow.


## Deployed sample
<img width=320px src=https://user-images.githubusercontent.com/11992915/266371685-48697872-b7b3-44ec-b7ce-0a0098a00b59.jpg>


## Architecture

1. Server (PC) sends `A` (`0x41`) to `/dev/ttyACM0` every 1s.
1. Watcher (Arduino UNO) check the serial port,
   and if can not receive a message for more than 5 sec,
   it triggers RESET PIN on the motherboard.
   (excepts wait for boot state.)


## How to use it

### PC daemon installation

1. Install `./target/availability_report` to `/usr/sbin/`.
1. Install `./target/availability_report.service` to `/etc/systemd/system/`.
1. Run `systemctl daemon-reload` and `systemctl enable --now availability_report`

**NOTE:** If your device path is not `/dev/ttyACM0`, please edit the `availability_report`.

### Arduino installation

1. Write `watcher/watcher.ino` to Arduino.


### System installation

1. Connect RESET PIN (+) on the motherboard to GPIO 2 on the Arduino.
1. Connect Arduino to the PC. (Ground potential must be matched.)

