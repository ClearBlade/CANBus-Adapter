#include <stdio.h>
#include "mqtt.h"


int main(int argc, char *argv[]) {
  int status = initializeCBAndMQTT();
  if(status == -1)
    return -1;

  return 0;
}
