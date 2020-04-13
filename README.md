# i2c-motor-control-over-uart
Controls multiple Rhino servo motors https://www.active-robots.com/dc-servo-motor-10rpm-uart-12c-ppm-drive.html

## Setup

Set each motor to have a unique address (Incrementing 0-127) using its build-in UART command. Then connect all motors to the Arduino's i2c bus.

Set the number of motors at the top of the INO file.

## Usage

Control this program over your Arduino's UART Serial connection.

Read a value with `[Motor number 0-127],[Command]` e.g. `0,R` which would return e.g. `3642`

Write a value with `[Motor number 0-127],[Command],[value]` e.g. `0,S,-200`

### Commands

| Command | Description                           |
|---------|---------------------------------------|
| S       | Read/Write Motor Speed and Direction  |
| M       | Read/Write Motor Max Speed            |
| D       | Read/Write Speed Damping              |
| P       | Read/Write Encoder Position           |
| G       | Read/Write Go to Position Command     |
| R       | Write Relative Go to Position Command |
| A       | Read/Write Speed-Feedback Gain term   |
| B       | Read/Write P-Gain term                |
| C       | Read/Write I-Gain term                |
