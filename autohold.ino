#include <Wire.h>
#define UPPER 90 // 40 grade
#define CENTER 150 //0 grade
#define LOWER 210 //-40 grade
#define accel_module (0x53)

#define filter_count 10

//1.5PWM / grad

byte values[6] ;
char output[20];

float servo;

bool first=1;
int xoff, yoff, zoff;

int count;
double sum;

void setup()
{
  
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  analogWrite(3, CENTER);
  delay(100);

  Wire.begin();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(0);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(16);
  Wire.endTransmission();
  Wire.beginTransmission(accel_module);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();
}

void loop()
{ 
  int xyzregister = 0x32;
  int x, y, z;

  Wire.beginTransmission(accel_module);
  Wire.write(xyzregister);
  Wire.endTransmission();

  Wire.beginTransmission(accel_module);
  Wire.requestFrom(accel_module, 6);

  int i = 0;
  while (Wire.available()) {
    values[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();
  if (first)
  {
    xoff = (((int)values[1]) << 8) | values[0];
    yoff = (((int)values[3]) << 8) | values[2];
    zoff = (((int)values[5]) << 8) | values[4];
    first=0;
  }

  if (count==filter_count)
  {
    count=0;
    servo = map((sum/filter_count), 90, -90, LOWER, UPPER);
    sum=0;
  }
  else
  {
    x = (((((int)values[1]) << 8) | values[0])-xoff)/2.7777;
    y = (((((int)values[3]) << 8) | values[2])-yoff)/2.7777;
    z = (((((int)values[5]) << 8) | values[4])-zoff)/2.7777;
    sum=sum+y*1.5;
    count++;
  }
    //servo = map(y*1.5, 90, -90, LOWER, UPPER);
    analogWrite(3, servo);
  
  sprintf(output, "%d %d %d", x, y, z);
  Serial.print(output);
  Serial.write(10);
}

