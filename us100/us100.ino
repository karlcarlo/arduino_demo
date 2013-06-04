//TRIG 接Digital 5口，触发测距；ECHO接Digital 4口，接收距离信号。

//程序代码：

int inputPin=4;  // 定义超声波信号接收接口   ECHO接4口
int outputPin=5; // 定义超声波信号发出接口  TRIG 接5口

void setup(){
  Serial.begin(9600);
  pinMode(inputPin, INPUT);
  pinMode(outputPin, OUTPUT);
}

void loop(){
  digitalWrite(outputPin, LOW); // 使发出发出超声波信号接口低电平2μs
  delayMicroseconds(2);
  digitalWrite(outputPin, HIGH); // 使发出发出超声波信号接口高电平10μs，这里是至少10μs
  delayMicroseconds(10);
  digitalWrite(outputPin, LOW);    // 保持发出超声波信号接口低电平
  int distance = pulseIn(inputPin, HIGH);  // 读出脉冲时间
  distance= distance/58;   // 将脉冲时间转化为距离（单位：厘米）[模块将距离值转化为340m/s 时的时间值的2倍，通过Echo 端输出一高电平，可根据此高电平的持续时间来计算距离值。即距离值为：(高电平时间*340m/s)/2。]
  Serial.println(distance);   //输出距离值                
  delay(50);  
}
