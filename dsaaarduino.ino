#include <Servo.h>

// Title:   Auto Pan-Tilt Servo/Cam Control
// Subject: This Sketch receives X,Y coordinates from srial then 
//          moves the camera to center of those coordinates. 
// Remixed: TechBitar / Hazim Bitar
// Date:    Dec 2011
// Credit:  I based this sketch on zagGrad's (SparkFun) code.  

#define  servomaxx   180   // max degree servo horizontal (x) can turn
#define  servomaxy   180   // max degree servo vertical (y) can turn
#define  screenmaxx   320   // max screen horizontal (x)resolution
#define  screenmaxy   240    // max screen vertical (y) resolution
#define  servocenterx   90  // center po#define  of x servo
#define  servocentery   90  // center po#define  of y servo
#define  servopinx   9   // digital pin for servo x
#define  servopiny   10  // digital servo for pin y
#define  baudrate 9600  // com port speed. Must match your C++ setting
#define distancex 1  // x servo rotation steps
#define distancey 1  // y servo rotation steps

int valx = 0;       // store x data from serial port
int valy = 0;       // store y data from serial port
int posx = 0;
int posy = 0;
int incx = 0;  // significant increments of horizontal (x) camera movement
int incy = 0;  // significant increments of vertical (y) camera movement

Servo servox;
Servo servoy;

short MSB = 0;  // to build  2 byte integer from serial in byte
short LSB = 0;  // to build  2 byte integer from serial in byte
int   MSBLSB = 0;  //to build  2 byte integer from serial in byte

void setup() {

  Serial.begin(baudrate);        // connect to the serial port
  Serial.println("Starting Cam-servo Face tracker");

  pinMode(servopinx,OUTPUT);    // declare the LED's pin as output
  pinMode(servopiny,OUTPUT);    // declare the LED's pin as output

  servoy.attach(servopiny); 
  servox.attach(servopinx); 

  // center servos

  servox.write(servocenterx); 
  delay(200);
  servoy.write(servocentery); 
  delay(200);
}

void loop () {
  while(Serial.available() <=0); // wait for incoming serial data
  if (Serial.available() >= 4)  // wait for 4 bytes. 
  {
    // get X axis 2-byte integer from serial
    //MSB = Serial.read();
    //delay(5);
    //LSB = Serial.read();
    //MSBLSB=word(MSB, LSB);
    MSBLSB = Serial.read();
    valx = MSBLSB; 
    delay(10);
    Serial.println(valx);
    // get Y axis 2-byte integer from serial
    //MSB = Serial.read();
    //delay(5);
    //LSB = Serial.read();
    //MSBLSB=word(MSB, LSB);
    MSBLSB = Serial.read();
    valy = MSBLSB; 
    delay(10);
    Serial.println(valy);

    // read last servos positions
    posx = servox.read(); 
    posy = servoy.read();

   //Find out if the X component of the face is to the left of the middle of the screen.
    if(valx < (screenmaxy/2 - incx)){
      if( posx >= 0/*incx*/ ) 
      posx -= distancex; //Update the pan position variable to move the servo to the left.
      else
      posx =5;
    }
    //Find out if the X component of the face is to the right of the middle of the screen.
    if(valx > screenmaxy/2 + incx){
      if(posx <= 180/*servomaxx-incx*/) posx +=distancex; //Update the pan position variable to move the servo to the right.
      else
      posx = 175;
    }

    //Find out if the Y component of the face is below the middle of the screen.
    if(valy < (screenmaxx/2 - incy)){
      if(posy >= 0)
      posy -= distancey; //If it is below the middle of the screen, update the tilt position variable to lower the tilt servo.
      else
      posy = 5;
    }
    //Find out if the Y component of the face is above the middle of the screen.
     else if(valy > (screenmaxx/2 + incy)){
      if(posy <= 180)
      posy += distancey; //Update the tilt position variable to raise the tilt servo.
      else
      posy = 175;
    }

    // Servos will rotate accordingly 
    servox.write(posx);
    servoy.write(posy);

  }   
}














