#include <stdio.h>
#include "mqtt.h"
#include "can.h"


int main(int argc, char *argv[]) {
  int status = initializeCBAndMQTT();
  if(status == -1)
    return -1;

  startCANListnerLoop("vcan0");

  return 0;
}
