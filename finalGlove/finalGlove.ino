int analogPin = 3;
int data = 0;
int analogPin2 = 3;
int data2 = 0;
int analogPin3 = 3;
int data3 = 0;

const int FLEX_PIN = A0;
const int FLEX_PIN2 = A1;
const int FLEX_PIN3 = A2;// Pin connected to voltage divider output

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 47500.0; // Measured resistance of 3.3k resistor
const float R_DIV2 = 47500.0; // Measured resistance of 3.3k resistor
float R_DIV3 = 3700.0; // Measured resistance of 3.3k resistor

// Upload the code, then try to adjust these values to more
// accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg

const float STRAIGHT_RESISTANCE2 = 17300.0; // resistance when straight
const float BEND_RESISTANCE2 = 70000.0; // resistance at 90 deg

float STRAIGHT_RESISTANCE3 = 24180.0; // resistance when straight
float BEND_RESISTANCE3 = 30500; // resistance at 90 deg



void setup() {
  Serial.begin(9600);

    Serial.begin(9600);
  pinMode(FLEX_PIN, INPUT);
  pinMode(FLEX_PIN2, INPUT);
  pinMode(FLEX_PIN3, INPUT);
}



void loop() {
    data = analogRead(analogPin);
    data2 = analogRead(analogPin2);
    data3 = analogRead(analogPin3);
    //Serial.println(data);
    

 // Read the ADC, and calculate voltage and resistance from it
  int flexADC = analogRead(FLEX_PIN);
  int flexADC2 = analogRead(FLEX_PIN2);
  int flexADC3 = analogRead(FLEX_PIN3);
  //
  float flexV = flexADC * VCC / 1023.0;
  float flexV2 = flexADC2 * VCC / 1023.0;
  float flexV3 = flexADC3 * VCC / 1023.0;
  //
  float flexR = R_DIV * (VCC / flexV - 1.0);
  float flexR2 = R_DIV2 * (VCC / flexV2 - 1.0);
  float flexR3 = R_DIV3 * (VCC / flexV3 - 1.0);
  //

  // Use the calculated resistance to estimate the sensor's
  // bend angle:
  float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE,
                   0, 90.0);
  float angle2 = map(flexR2, STRAIGHT_RESISTANCE2, BEND_RESISTANCE2,
                   0, 90.0);
  float angle3 = map(flexR3, STRAIGHT_RESISTANCE3, BEND_RESISTANCE3,
                   0, 90.0);
                   
 Serial.print(String(angle));
 Serial.print(String(angle2));
 Serial.print(String(angle3));
//Serial.println();
//STRAIGHT
if(angle3>75){
  if(angle3<90){
    BEND_RESISTANCE3 = BEND_RESISTANCE3-200;
  } 
  if(angle3>90){
    BEND_RESISTANCE3 = BEND_RESISTANCE3+200;
  }
  //Serial.println(BEND_RESISTANCE3);
}
//BEND
if(angle3<20&&angle3>10){
    STRAIGHT_RESISTANCE3 = STRAIGHT_RESISTANCE3+50;
    //Serial.println(STRAIGHT_RESISTANCE3 + String(" UP "));
}
if(angle3<10&&angle3>0){
    STRAIGHT_RESISTANCE3 = STRAIGHT_RESISTANCE3+25;
    //Serial.println(STRAIGHT_RESISTANCE3 + String(" UP "));
}
if(angle3<0){
 STRAIGHT_RESISTANCE3=STRAIGHT_RESISTANCE3-20;
 //Serial.println(STRAIGHT_RESISTANCE3 + String(" DOWN "));
}
if(angle3<-10){
 STRAIGHT_RESISTANCE3=STRAIGHT_RESISTANCE3-100;
 //Serial.println(STRAIGHT_RESISTANCE3 + String(" MOREDOWN "));
}
Serial.println(STRAIGHT_RESISTANCE3);
  //Serial.println();
  delay(500);
}
