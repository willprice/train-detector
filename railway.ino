#include "railway.h"
#include <Serial.h>
#include <SD.h>
#include <TMRpcm.h>
#include <SPI.h>

STATE global_state = NO_TRAIN;
TMRpcm player;


void setup() {
  Serial.begin(9600);
  player.speakerPin = 9;
  player.quality(1);
  pinMode(TRAIN_TRIGGER_PIN, INPUT);
  pinMode(ALARM_DISABLE_PIN, INPUT);
  if (!SD.begin(SD_ChipSelectPin))
    Serial.println("SD fail");
  else
    Serial.println("SD initialised");
}

void loop() {
  EVENT event = getEvent();
  transitionFunction(event);
#ifdef DEBUG
  print_state(global_state);
  print_event(event);
  delay(100);
#endif
  delay(10);
}

EVENT getEvent() {
  if (digitalRead(TRAIN_TRIGGER_PIN))
    return TRAIN_ARRIVED;
  if (digitalRead(ALARM_DISABLE_PIN))
    return ACKNOWLEDGE;
  else
    return NO_EVENT;
}

void transitionFunction(EVENT event) {
  switch(global_state) {
    case NO_TRAIN:
      handle_event_no_train(event);
      break;
    case TRAIN:
      handle_event_train(event);
      break;
    default:
      break;
  }

}

void handle_event_no_train(EVENT event) {
  switch(event) {
    case NO_EVENT:
      break;
    case TRAIN_ARRIVED:
      global_state = TRAIN;
      enableAlarm();
      break;
  }
}

void handle_event_train(EVENT event) {
  switch(event) {
    case NO_EVENT:
      break;
    case ACKNOWLEDGE:
      disableAlarm();
      delay(1000 * DELAY);
      global_state = NO_TRAIN;
      break;
  }
}
void enableAlarm() {
#ifdef DEBUG
  Serial.println("Enabling alarm");
#endif
  player.play("alarm.wav");
  player.loop(1);

}

void disableAlarm() {
#ifdef DEBUG
  Serial.println("Disabling alarm");
#endif
  player.loop(0);
  player.disable();

}

void print_state(STATE state) {
  switch(state) {
    case NO_TRAIN:
      Serial.println("No train");
      break;
    case TRAIN:
      Serial.println("Train");
      break;
  }
}

void print_event(EVENT event) {
  switch(event) {
    case NO_EVENT:
      Serial.println("No event");
      break;
    case TRAIN_ARRIVED:
      Serial.println("Train has arrived");
      break;
    case ACKNOWLEDGE:
      Serial.println("Acknowledged");
      break;
  }
}
