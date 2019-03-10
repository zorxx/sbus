# SBUS Parser

Parser for the Futaba SBUS protocol messages (https://www.futabarc.com/sbus/index.html).

## Serial Port Configuration
The following serial port (UART) configuration parameters are
standard for SBUS devices:
```c
#define SBUS_BAUD_RATE           100000
#define SBUS_DATA_BITS           8
#define SBUS_STOP_BITS           2
#define SBUS_PARITY              /*EVEN*/
```

## Usage
1. Create a message handler callback
```c
void sbus_message_handler(const sbus_message_t message)
{
   /* Do something with the parsed message */
}
```

2. Initialize the parser
```c
sbus_parse_init(sbus_message_handler);
```

3. Feed the parser with received serial characters
```c
uint8_t rx_char = device_serial_rx();
sbus_parse_char(rx_char);
```
Note that `device_serial_rx()` is an operating system/device-specific
function to retreive a character from the UART connected to the SBUS
device.
