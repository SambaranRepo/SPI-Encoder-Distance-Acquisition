#include <Metro.h>
#include <MLX90316.h>

byte pinSS = 5;
byte pinSCK = 3; 
byte pinMOSI = 4;

float angle;
unsigned long t;
int dir;
int counter;
float distance;
float prev_angle;
unsigned long t1;
unsigned long t2;
int prev_counter;
long change;
long v;

Metro mlxMetro = Metro(5);
MLX90316 mlx_1 = MLX90316();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mlx_1.attach(pinSS,pinSCK, pinMOSI);
  Serial.println("SPI encoder reading");
  prev_counter = 0;
  distance = 0;
  v = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mlxMetro.check() == 1)
  {
    prev_angle = mlx_1.readAngle()/10;
    t1 = millis()/1000; 
    delay(500);
    angle = mlx_1.readAngle()/10;
    t2 = millis()/1000;
    t = t2 - t1; 
//    Serial.println("Prev angle :");
//    Serial.println(prev_angle);
//    Serial.println("\n Current angle :");
//    Serial.println(angle); 
    }
    if (270 <= prev_angle && prev_angle <=360 && 0< angle && angle<=90)
    {
      Serial.println("Inside first if");
      counter = prev_counter+1; 
    }
    else if (0<prev_angle && prev_angle<=90 && 270<=angle && angle<=360)
    {
      Serial.println("Inside second if");
      counter = prev_counter-1;
    }
    change = (360*counter + angle)- (360*prev_counter + prev_angle);
    v = change / t;
    
//    Serial.println("Previous counter : ");
//    Serial.println(prev_counter);
//    Serial.println("Current Counter : ");
//    Serial.println(counter);
    distance = distance + (2*3.14*0.1 / 360) * change;
//    Serial.println(prev_angle);
//    Serial.println(angle);
    Serial.println("\n Distance : "); 
    Serial.println(distance);
    Serial.println("Speed of encoder : ");
    Serial.println(v);
    prev_counter = counter;
    
  }
