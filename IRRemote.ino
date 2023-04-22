#include <IRremote.h>
#include <Keyboard.h>
#define IR_RECEIVE_PIN 8
#define LONG_MAX 4294967295
#define ACTIVE_DURATION 120000

unsigned long lastPressedTime = 0;
bool remoteEnabled = true;

void setup() {
  //Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  Keyboard.begin();
}
void loop() {
  updateRemoteEnableStatus();
  if (IrReceiver.decode()) {
    int command = IrReceiver.decodedIRData.command;
    //Serial.println(command);
    //Serial.println(lastPressedTime);

    if (command == 85) {
      if (remoteEnabled) {
        disableRemote();
      } else {
        enableRemote();
      }
    }
    if (remoteEnabled) {
      pressKeys(command);
    }

    delay(60);
    IrReceiver.resume();
  }
}

void updateRemoteEnableStatus() {
  //account for overflow, reset last pressed time before overflow occurs
  if (millis() > (LONG_MAX - 200)) {
    lastPressedTime = 0;
  }
  //remoteEnabled = millis() - lastPressedTime < ACTIVE_DURATION;
}

void enableRemote() {
  lastPressedTime = millis();
  remoteEnabled = true;
}

void disableRemote() {
  lastPressedTime = 0;
  remoteEnabled = false;
}

void pressKeys(int command) {
  enableRemote();
  switch (command) {
    case 69:
      Keyboard.press(KEY_UP_ARROW);
      break;
    case 70:
      Keyboard.press(KEY_DOWN_ARROW);
      break;
    case 71:
      Keyboard.press(KEY_LEFT_ARROW);
      break;
    case 72:
      Keyboard.press(KEY_RIGHT_ARROW);
      break;
    case 68:
      Keyboard.press(KEY_RETURN);
      break;
    case 73:
      Keyboard.press(KEY_ESC);
      break;
    case 74:
      Keyboard.press(KEY_BACKSPACE);
      break;
    default:
      break;
  }
  Keyboard.releaseAll();
}
