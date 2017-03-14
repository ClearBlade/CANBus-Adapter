#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <pthread.h>
#include "mqtt.h"


void *readCANData(void *canData) {
  char *mqttMessage;
  struct can_frame *frame = (struct can_frame *) canData;
  printf("Received data from CAN bus: %s\n", frame->data);

  int size = asprintf(&mqttMessage, "ID: %d, Data: %s", frame->can_id, frame->data);
  if(size == -1) {
    printf("Malloc failed while construction MQTT message.\nCannot publish to MQTT\n");
    pthread_exit(NULL);
  }

  publishCANMessage(mqttMessage);

  //free(mqttMessage);
  pthread_exit(NULL);
}


int startCANListnerLoop(const char *interfaceName) {
  pthread_t tid;
  int s;
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

	const char *ifname = interfaceName;

	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket: ");
		return -1;
	}

	strncpy(ifr.ifr_name, ifname, strlen(ifname));
	ioctl(s, SIOCGIFINDEX, &ifr);

	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind: ");
		return -1;
	}

  while(1) {
    nbytes = read(s, &frame, sizeof(struct can_frame));
    if(nbytes) {
      pthread_create(&tid, NULL, readCANData, (void *)&frame);
    }
  }

  return 0;
}
