# Overview

CAN Bus Adapter allows an automotive's CAN (Controller Area Network) Bus to publish MQTT messages.

# Prerequisites


1. Install `libssl`,`curl`, and `jansson`,`gcc`, `autoconf`, and `libtool` libraries by running 

```
sudo apt-get install libssl-dev libcurl4-openssl-dev libjansson-dev gcc autoconf libtool
```

1. Install `paho-mqtt` C library, [repo](https://eclipse.org/paho/clients/c/)

```
git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
make clean
make
sudo make install
```

2. Build the ClearBlade C SDK [Repo](https://github.com/ClearBlade/ClearBlade-C-SDK)

```
git clone https://github.com/ClearBlade/ClearBlade-C-SDK
cd ClearBlade-C-SDK
make clean
make
sudo make install
```

# Install

1. Enter your ClearBlade System details in /adapters/contants.h, example below

```
#ifndef _CONSTANTS_H
#define _CONSTANTS_H


char *SYSTEM_KEY = <SYSTEM_KEY>; // ex. "94aaa4890bc0afe1fbd282b1ac8e01"
char *SYSTEM_SECRET = <SYSTEM_SECRET>; // ex. "9AAEC4890BC68AB6B9BBEDF6B21F"
char *USER_EMAIL = <USER_EMAIL>; // ex. "test@clearblade.com"
char *USER_PASSWORD = <PASSWORD>; // ex. "password"

...
```

#endif

```
2. Build adapter

```
cd /path/to/canbus-adapter/adapters/
make clean
make
```

3. Start adapter

```
./start_adapter
```

# Test

1. Install [can-utils](https://github.com/linux-can/can-utils)

```
git clone https://github.com/linux-can/can-utils
cd can-utils
./autogen.sh
./configure
make
sudo make install
```

2. Install virtual can interface

```
sudo modprobe can
sudo modprobe can_raw
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0
sudo ip link show vcan0
```

3. Send an example payload to CAN Bus

```
sudo ifconfig vcan0 up
cansend vcan0 123#1122334455667788
```

4. All set! You'll see CANBus messages within the CANBus Adapter!

```
ClearBlade init successful: NByVFwfSCjVf4zF8XSMTG_osxg3B0BA_Tw-CkqU89jsqSlS_eosLT3pPbc4w1Z0KvTQCWjeSvLnGgxoqQw==
Successful connection to MQTT broker
Subscribe succeeded
vcan0 at index 0
Received data from CAN bus: "3DUfw�
Send MQTT message: ID: 291, Data: "3DUfw�
```
