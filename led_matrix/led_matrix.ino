//We always have to include the library
#include <LedControl.h>
 
/*
Now we need a LedControl to work with.
***** These pin numbers will probably not work with your hardware *****
pin 12 is connected to the DataIn      
pin 11 is connected to the CLK 
pin 10 is connected to LOAD(CS) 
We have only a single MAX72XX.
*/
LedControl lc = LedControl(12, 11, 10, 1);
 
/* we always wait a bit between updates of the display */
unsigned long delaytime = 1000;

/* font library */
byte font[38][8]={
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},// 0: 0
{0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10},// 1: 1
{0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E},// 2: 2
{0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0},// 3: 3
{0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8},// 4: 4
{0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0},// 5: 5
{0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0},// 6: 6
{0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8},// 7: 7
{0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E},// 8: 8
{0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E},// 9: 9
{0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},// 10: A
{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},// 11: B
{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},// 12: C
{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},// 13: D
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},// 14: E
{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},// 15: F
{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},// 16: G
{0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44},// 17: H
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},// 18: I
{0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},// 19: J
{0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},// 20: K
{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},// 21: L
{0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81},// 22: M
{0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},// 23: N
{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},// 24: O
{0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20},// 25: P
{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},// 26: Q
{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},// 27: R
{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},// 28: S
{0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},// 29: T
{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},// 30: U
{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},// 31: V
{0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},// 32: W
{0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},// 33: X
{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},// 34: Y
{0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F},// 35: Z
{0x8,0x7F,0x49,0x49,0x7F,0x8,0x8,0x8},// 36: 中
{0xFE,0xBA,0x92,0xBA,0x92,0x9A,0xBA,0xFE},// 37: 国
};

int val;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);
  
  Serial.begin(9600);
}
 
/*
This method will display the characters for the
word "Arduino" one after the other on the matrix. 
(you need at least 5x7 leds to see the whole chars)
*/
void writeArduinoOnMatrix() {
  /* here is the data for the characters */
  byte a[5] = { B01111110, B10001000, B10001000, B10001000, B01111110 };
  byte r[5] = { B00010000, B00100000, B00100000, B00010000, B00111110 };
  byte d[5] = { B11111110, B00010010, B00100010, B00100010, B00011100 };
  byte u[5] = { B00111110, B00000100, B00000010, B00000010, B00111100 };
  byte i[5] = { B00000000, B00000010, B10111110, B00100010, B00000000 };
  byte n[5] = { B00011110, B00100000, B00100000, B00010000, B00111110 };
  byte o[5] = { B00011100, B00100010, B00100010, B00100010, B00011100 };
  byte img_1[8] = { B11111111, B10000001, B10000001, B10000001, B10000001, B10000001, B10000001, B11111111 };
  byte img_2[8] = { B00000000, B01111110, B01000010, B01000010, B01000010, B01000010, B01111110, B00000000 };
  byte img_3[8] = { B00000000, B00000000, B00111100, B00100100, B00100100, B00111100, B00000000, B00000000 };
  byte img_4[8] = { B00000000, B00000000, B00000000, B00011000, B00011000, B00000000, B00000000, B00000000 };
 
  /* now display them one by one with a small delay */
  lc.setRow(0, 0, a[0]);
  lc.setRow(0, 1, a[1]);
  lc.setRow(0, 2, a[2]);
  lc.setRow(0, 3, a[3]);
  lc.setRow(0, 4, a[4]);
  delay(delaytime);
  
  lc.setRow(0,0,r[0]);
  lc.setRow(0,1,r[1]);
  lc.setRow(0,2,r[2]);
  lc.setRow(0,3,r[3]);
  lc.setRow(0,4,r[4]);
  delay(delaytime);
  
  lc.setRow(0,0,d[0]);
  lc.setRow(0,1,d[1]);
  lc.setRow(0,2,d[2]);
  lc.setRow(0,3,d[3]);
  lc.setRow(0,4,d[4]);
  delay(delaytime);
  
  lc.setRow(0,0,u[0]);
  lc.setRow(0,1,u[1]);
  lc.setRow(0,2,u[2]);
  lc.setRow(0,3,u[3]);
  lc.setRow(0,4,u[4]);
  delay(delaytime);
  
  lc.setRow(0,0,i[0]);
  lc.setRow(0,1,i[1]);
  lc.setRow(0,2,i[2]);
  lc.setRow(0,3,i[3]);
  lc.setRow(0,4,i[4]);
  delay(delaytime);
  
  lc.setRow(0,0,n[0]);
  lc.setRow(0,1,n[1]);
  lc.setRow(0,2,n[2]);
  lc.setRow(0,3,n[3]);
  lc.setRow(0,4,n[4]);
  delay(delaytime);
  
  lc.setRow(0,0,o[0]);
  lc.setRow(0,1,o[1]);
  lc.setRow(0,2,o[2]);
  lc.setRow(0,3,o[3]);
  lc.setRow(0,4,o[4]);
  delay(delaytime);
  
  lc.setRow(0, 0, img_1[0]);
  lc.setRow(0, 1, img_1[1]);
  lc.setRow(0, 2, img_1[2]);
  lc.setRow(0, 3, img_1[3]);
  lc.setRow(0, 4, img_1[4]);
  lc.setRow(0, 5, img_1[5]);
  lc.setRow(0, 6, img_1[6]);
  lc.setRow(0, 7, img_1[7]);
  delay(delaytime);
  
  lc.setRow(0, 0, img_2[0]);
  lc.setRow(0, 1, img_2[1]);
  lc.setRow(0, 2, img_2[2]);
  lc.setRow(0, 3, img_2[3]);
  lc.setRow(0, 4, img_2[4]);
  lc.setRow(0, 5, img_2[5]);
  lc.setRow(0, 6, img_2[6]);
  lc.setRow(0, 7, img_2[7]);
  delay(delaytime);
  
  lc.setRow(0, 0, img_3[0]);
  lc.setRow(0, 1, img_3[1]);
  lc.setRow(0, 2, img_3[2]);
  lc.setRow(0, 3, img_3[3]);
  lc.setRow(0, 4, img_3[4]);
  lc.setRow(0, 5, img_3[5]);
  lc.setRow(0, 6, img_3[6]);
  lc.setRow(0, 7, img_3[7]);
  delay(delaytime);
  
  lc.setRow(0, 0, img_4[0]);
  lc.setRow(0, 1, img_4[1]);
  lc.setRow(0, 2, img_4[2]);
  lc.setRow(0, 3, img_4[3]);
  lc.setRow(0, 4, img_4[4]);
  lc.setRow(0, 5, img_4[5]);
  lc.setRow(0, 6, img_4[6]);
  lc.setRow(0, 7, img_4[7]);
  delay(delaytime);
  
  
  lc.setRow(0,0,0);
  lc.setRow(0,1,0);
  lc.setRow(0,2,0);
  lc.setRow(0,3,0);
  lc.setRow(0,4,0);
  lc.setRow(0, 5, 0);
  lc.setRow(0, 6, 0);
  lc.setRow(0, 7, 0);
  delay(delaytime);
}
 
/*
  This function lights up a some Leds in a row.
The pattern will be repeated on every row.
The pattern will blink along with the row-number.
row number 4 (index==3) will blink 4 times etc.
*/
void rows() {
  for(int row=0;row<8;row++) {
    delay(delaytime);
    lc.setRow(0,row,B10100000);
    delay(delaytime);
    lc.setRow(0,row,(byte)0);
    for(int i=0;i<row;i++) {
      delay(delaytime);
      lc.setRow(0,row,B10100000);
      delay(delaytime);
      lc.setRow(0,row,(byte)0);
    }
  }
}
 
/*
  This function lights up a some Leds in a column.
The pattern will be repeated on every column.
The pattern will blink along with the column-number.
column number 4 (index==3) will blink 4 times etc.
*/
void columns() {
  for(int col=0;col<8;col++) {
    delay(delaytime);
    lc.setColumn(0,col,B10100000);
    delay(delaytime);
    lc.setColumn(0,col,(byte)0);
    for(int i=0;i<col;i++) {
      delay(delaytime);
      lc.setColumn(0,col,B10100000);
      delay(delaytime);
      lc.setColumn(0,col,(byte)0);
    }
  }
}
 
/* 
This function will light up every Led on the matrix.
The led will blink along with the row-number.
row number 4 (index==3) will blink 4 times etc.
*/
void single() {
  for(int row=0;row<8;row++) {
    for(int col=0;col<8;col++) {
      delay(delaytime);
      lc.setLed(0,row,col,true);
      delay(delaytime);
      for(int i=0;i<col;i++) {
        lc.setLed(0,row,col,false);
        delay(delaytime);
        lc.setLed(0,row,col,true);
        delay(delaytime);
      }
    }
  }
}

void show_font(){
  for(int i = 0; i < 38; i++){
    for(int j = 0; j < 8; j++){
      lc.setRow(0, j, font[i][j]);
    }
    delay(delaytime);
  }
}
 
void loop() {
//  show_font();
//  writeArduinoOnMatrix();
//  rows();
//  columns();
//  single();

  val = Serial.read();
  if(val != -1){
    Serial.println(val);
  }
  
  if(val == '0'){
    for(int j = 0; j < 8; j++){
      lc.setRow(0, j, font[0][j]);
    }
  }

  if(val == '1'){
    for(int j = 0; j < 8; j++){
      lc.setRow(0, j, font[1][j]);
    }
  }

  if(val == '2'){
    for(int j = 0; j < 8; j++){
      lc.setRow(0, j, font[2][j]);
    }
  }

  if(val == 'q'){
    for(int j = 0; j < 8; j++){
      lc.setRow(0, j, font[26][j]);
    }
  }
  
  if(val == 'w'){
    for(int j = 0; j < 8; j++){
      lc.setRow(0, j, font[32][j]);
    }
  }
  
  if(val == 'e'){
    for(int j = 0; j < 8; j++){
      lc.setRow(0, j, font[14][j]);
    }
  }
  
  if(val == 'a'){
    for(int j = 0; j < 8; j++){
      lc.setRow(0, j, font[10][j]);
    }
  }
  
  if(val == 's'){
    for(int j = 0; j < 8; j++){
      lc.setRow(0, j, font[28][j]);
    }
  }
  
  if(val == 'd'){
    for(int j = 0; j < 8; j++){
      lc.setRow(0, j, font[13][j]);
    }
  }
  

}

