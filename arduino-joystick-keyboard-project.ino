// made by Megalaxatif in 02/2024 
// this project use the CREATIVE COMMONS ATTRIBUTION 4.0 INTERNATIONAL LICENSE
// you can change the key pressed at line 10 under the comment "key values"
// plug the joystick wires in the correct pins defined at line 8 under the comment "plug info"
// Enjoy your new plug and play joystick :)

#include <Keyboard.h>
// plug info
#define x_axis_pin A0
#define y_axis_pin A1
// key values
const char left_char = 's';
const char right_char = 'f';
const char up_char = 'e';
const char down_char = 'd';
// values which create a dead zone around the center of the joystick, so x_axis must be > 128 + 49 or < 128 - 49 and y_axis must be > 127 + 50 or < 127 - 50 to press a key in order to avoid high sensivity movements 
const int target_x_value = 49;
const int target_y_value = 50;

int x_axis = 0;
int y_axis = 0;

void setup() {
  Keyboard.begin();
}

void loop() {
  // read the real axis values and convert them to a number between 0 and 255 using the map() function
  x_axis = analogRead(x_axis_pin);
  x_axis = map(x_axis, 0, 1023, 0, 255);

  y_axis = analogRead(y_axis_pin);
  y_axis = map(y_axis, 0, 1023, 0, 255);

  // if the keyboard is in the dead zone we release all the keys because the joystick doesn't move or it doesn't move enought
  if (x_axis > 128 - target_x_value && x_axis < 128 + target_x_value && // dead zone x_axis
      y_axis > 128 - target_y_value && y_axis < 128 + target_y_value ){  // dead zone y_axis
    Keyboard.releaseAll();
  }
  // else we check which axis moved and we convert the data in its associated key
  else{
    if (x_axis < 128 - target_x_value){
      // left
      Keyboard.press(left_char);
      Keyboard.release(right_char);
    }
    else if (x_axis > 128 + target_x_value){
      // right
      Keyboard.press(right_char);
      Keyboard.release(left_char);
    }
    else {
      Keyboard.release(left_char);
      Keyboard.release(right_char);
    }
    if (y_axis < 127 - target_y_value){
      // up
      Keyboard.press(up_char);
      Keyboard.release(down_char);
    }
    else if (y_axis > 127 + target_y_value){
      // down
      Keyboard.press(down_char);
      Keyboard.release(up_char);
    }
    else {
      Keyboard.release(up_char);
      Keyboard.release(down_char);
    }
  }
  //log
  //Serial.print("x: ");
  //Serial.println(x_axis);
  //Serial.print("y: ");
  //Serial.println(y_axis);
  // wait to avoid too frequent transmition issues
  delay(10);
}