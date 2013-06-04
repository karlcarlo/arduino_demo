#include <Servo.h> 
Servo servo_x;
Servo servo_y;
               
int pos_x = 0;
int pos_y = 0;
int x_angle_min = 20;
int x_angle_default = 40;
int x_angle_max = 120;
int y_angle_min = 15;
int y_angle_default = 75;
int y_angle_max = 150;
String in_data = "";

void setup(){
  Serial.begin(9600);
  servo_x.attach(9);  // 该舵机由arduino第九脚控制
  servo_y.attach(10);
  servo_x.write(x_angle_default);
  servo_y.write(y_angle_default);
  
  Serial.println("\n\nPlease input angle");
} 

void loop(){
  while(Serial.available() > 0) {
    int in_char = Serial.read();
    if(isDigit(in_char)){
      in_data += (char)in_char;
    }
    if(in_char == '\n'){
      pos_x = in_data.toInt();
      if(pos_x > x_angle_max){
        pos_x = x_angle_max;
      }
      else if(pos_x < x_angle_min){
        pos_x = x_angle_min;
      }
      pos_y = in_data.toInt();
      if(pos_y > y_angle_max){
        pos_y = y_angle_max;
      }
      else if(pos_y < y_angle_min){
        pos_y = y_angle_min;
      }
      
      Serial.println("x move to");
      Serial.println(pos_x);
      Serial.println("y move to");
      Serial.println(pos_y);
      servo_x.write(pos_x);
      servo_y.write(pos_y);
      delay(15);
      in_data = "";
    }
  }
}

