/*
 title: led rgb
 author: Jone
*/

int led_r = 10;
int led_g = 11;
int led_b = 12;

void setup (){
  pinMode(led_r, OUTPUT);
  pinMode(led_g, OUTPUT);
  pinMode(led_b, OUTPUT);
}

void loop(){
  set_led(255, 0, 0);  // 红色
  delay(1000);
  set_led(0, 255, 0);  // 绿色
  delay(1000);
  set_led(0, 0, 255);  // 蓝色
  delay(1000);
  set_led(255, 255, 0);  // 黄色
  delay(1000);  
  set_led(80, 0, 80);  // 紫色
  delay(1000);
  set_led(0, 255, 255);  // 浅绿色
  delay(1000);
}

void set_led(int r, int g, int b){
  analogWrite(led_r, r);
  analogWrite(led_g, g);
  analogWrite(led_b, b);
}


