# Overview

CAN Bus Adapter allows an automotive's CAN (Controller Area Netowkr) Bus to publish MQTT messages.

# Prerequisites



# Install

1. Clone the ClearBlade C SDK [Here](https://github.com/ClearBlade/ClearBlade-C-SDK)

2. Enter your ClearBlade System details in /adapters/contants.h

3. Install `libssl`,`paho-mqtt`,`curl`, and `jansson` libraries TODO Details
4. Build libraries

```
cd /path/to/aforementioned/libraries/
make clean
make
sudo make install
```

5. Build adapter

```
cd /path/to/canbus-adapter/adapters/
make clean
make
```

6. Start adapter

```
./start_adapter
```

# Test

## can-utils

1. Send an example payload to CAN Bus

```
sudo ifconfig vcan0 up
cansend vcan0 123#1122334455667788
```