#include <Servo.h> 
Servo myservo;  //创建一个舵机控制对象
                          // 使用Servo类最多可以控制8个舵机
int pos = 0;    // 该变量用与存储舵机角度位置
/*~~~~~~~~~~~~~~~~~~~~~~~~~~华丽的分割线~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void setup() 
{ 
  myservo.attach(8);  // 该舵机由arduino第九脚控制
  myservo.write(0);
} 
/*~~~~~~~~~~~~~~~~~~~~~~~~~~华丽的分割线 ~~~~~~~~~~~~~~~~~~~~~~~~~~ */ 
void loop() 
{ 
  for(pos = 0; pos < 180; pos += 1)  // 从0度到180度运动 
  {                                                     // 每次步进一度
    myservo.write(pos);        // 指定舵机转向的角度
    delay(100);                       // 等待15ms让舵机到达指定位置
  } 
  for(pos = 180; pos>=1; pos-=1)   //从180度到0度运动  
  {                                
    myservo.write(pos);         // 指定舵机转向的角度 
    delay(100);                        // 等待15ms让舵机到达指定位置 
  } 
}

