#include <stdio.h>
#include <clearblade.h>
#include <stdbool.h>
#include "constants.h"

int initFlag = false;

int messageArrived(void *context, char *topicName, int topicLen, MQTTAsync_message *message) {
  printf("Message arrived\n");
  printf("Topic: %s\n", topicName);
  printf("Message: %s\n", (char *) message->payload);

  return 1;
}


void onConnect(void* context, MQTTAsync_successData* response) {
  printf("Successful connection to MQTT broker\n");
  extern int finished;
  finished = 1;
}

void cbInitCallback(bool error, char *result) {
  if(error) {
    printf("ClearBlade init error: %s\n", result);
  } else {
    printf("ClearBlade init successful: %s\n", result);
    initFlag = true;
  }
}

int initializeCBAndMQTT() {
  initializeClearBlade(SYSTEM_KEY, SYSTEM_SECRET, PLATFORM_URL, MESSAGING_URL, USER_EMAIL, USER_PASSWORD, &cbInitCallback);
  if(!initFlag)
    return -1;
  connectToMQTT(MQTT_CLIENT_ID, 0, &onConnect, &messageArrived);
  subscribeToTopic("canbus-incoming", 0);

  return 0;
}

void publishCANMessage(char *message) {
  publishMessage(message, "canbus-outgoing", 0, 0);
}
