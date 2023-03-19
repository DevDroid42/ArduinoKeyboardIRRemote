#include <IRremote.h>
#include <Keyboard.h>
#define IR_RECEIVE_PIN 8
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  Keyboard.begin();
}
void loop() {
  if (IrReceiver.decode()) {
    int command = IrReceiver.decodedIRData.command;
    Serial.println(command);
    switch(command){
      case 18:
        Keyboard.press(KEY_UP_ARROW);        
      break;
      case 24:
        Keyboard.press(KEY_DOWN_ARROW);
      break;
      case 20:
        Keyboard.press(KEY_LEFT_ARROW);
      break;
      case 22:
        Keyboard.press(KEY_RIGHT_ARROW);
      break;
      case 21:
        Keyboard.press(KEY_RETURN);
      break;
      case 17:
        Keyboard.press(KEY_ESC);
      break;
      default:
      break;
    }
    delay(60);
    Keyboard.releaseAll();    
    IrReceiver.resume();
  }
}
