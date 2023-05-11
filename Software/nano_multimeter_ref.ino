#include <LiquidCrystal_I2C.h>

#include <Wire.h>

#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3);

//int var;
//float reading;
char test;
String s = "t";


////////////////////////////////////////////////

LiquidCrystal_I2C lcd(0x27, 16, 2);



////////////////////////////////////////////
//resistance sensor



int analogPinA6 = A6;
int V_measured = 0;
int Vin = 5;
float Vout = 0;
int apply_voltage = 8;

float R2 = 0;
float buffer = 0;

int ch2K = 9;
int ch20K = 10;
int ch200K = 11;
int ch1M = 12;
int choose_sensor = A1;

//////////////////////////////////////////////////////



//voltage sensor variables
int value;
float vout;
float vin;
float R1 = 100000.0;
float R2_volt = 4700.0;



/////////////////////////////////////////////////////

//current sensor


int analogPin = A2;
float current = 0;





/////////////////////////////////////////////////////
//capacitance sensor variables
#define chargePin      6
#define dischargePin   7
#define resistorValue  10000.0F
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;
float nanoFarads;

void setup() {
  Serial.begin(9600);
  BTserial.begin(38400);
  Serial.print("BTserial started at "); Serial.println(9600);
  Serial.println(" ");
  pinMode(A0, INPUT);
  pinMode(chargePin, OUTPUT);
  digitalWrite(chargePin, LOW);
  lcd.init();
  lcd.backlight();

}


void loop() {
  int sensor = analogRead(A2);
  Serial.println(sensor);
  delay(200);
  int i = 0;
    if (sensor >= (330) && sensor < (700)) {
      s = cap_sens();
     
//      char x[s.length() + 1];
//       s.toCharArray(x, s.length() + 1);
//      while ( i < s.length()) {
//        if (BTserial.available()) {
//          BTserial.write(x[i]);
//          i++;
//        }
        lcd.setCursor(0, 0);
        lcd.print(s);
        Serial.println(s);
//      }

      
    }
  if (sensor < (330)) {

    s = volt_sens();
  //  s = s + 'z';
   
    
    
//    char x[s.length() + 1];
//     s.toCharArray(x, s.length() + 1);
//    while ( i < s.length()) {
//      if (BTserial.available()) {
//        BTserial.write(x[i]);
//        i++;
//      }


      lcd.setCursor(0, 0);
      lcd.print(s);
      Serial.println(s);
    //}
  }
   if (sensor >= (700)) {
      s = res_sens();
//      char x[s.length() + 1];
//       s.toCharArray(x, s.length() + 1);
//      while ( i < s.length()) {
//        if (BTserial.available()) {
//          BTserial.write(x[i]);
//          i++;
//        }
        lcd.setCursor(0, 0);
        lcd.print(s);
        Serial.println(s);
//      
//        
//        
        
        // Serial.println(test);
      }
      //        if(test == '4'){
      //           s = curr_sens();
      //           if(BTserial.available())
      //            BTserial.print(s);
      //           lcd.setCursor(0,0);
      //           lcd.print(s);
      //        }

      delay(100);


    }

//  }
//}
//Resistance Sensor

String res_sens() {

  pinMode(V_measured, INPUT);
  pinMode(analogPinA6, INPUT);
  pinMode(apply_voltage, OUTPUT);
  pinMode(ch2K, INPUT);
  pinMode(ch20K, INPUT);
  pinMode(ch200K, INPUT);
    pinMode(ch1M, INPUT);
  s = "";
  // int scale = analogRead(choose_scale);
  // if (scale<256)
  //{
  //  digitalWrite(apply_voltage,HIGH);
  //  pinMode(ch2K,OUTPUT);
  //  pinMode(ch20K,INPUT);
  //  pinMode(ch200K,INPUT);
  //  pinMode(ch1M,INPUT);
  //  digitalWrite(ch2K,LOW);
  //
  //  float R1= 2; // Set this values to the value of the used resistor in K ohms
  //  V_measured= analogRead(analogPinA6); //in 8bits
  //
  //      buffer= V_measured * Vin;
  //      Vout= (buffer)/1024.0;  //in volts
  //      buffer= (Vin/Vout) -1;
  //      R2= R1 * buffer*1000; //*1000 because we express it in ohms
  //
  //      if (R2 > 2000)
  //      {
  //        s = ("Increase scale");
  //        return s;
  //      }
  //
  //      if (R2 < 2000)
  //      {
  //        s = String(R2);
  //        return s;
  //      }
  //
  //}
  ////////////////////////////////////////////
  //
  //
  //
  //
  //
  //
  /////////////////////-20k-/////////////////////
  if (1)
  {
    digitalWrite(apply_voltage, HIGH);
    pinMode(ch2K, OUTPUT);
    pinMode(ch20K, INPUT);
    pinMode(ch200K, INPUT);
    pinMode(ch1M, INPUT);
    digitalWrite(ch2K, LOW);

    float R1 = 2; // Set this values to the value of the used resistor in K ohms
    V_measured = analogRead(analogPinA6); //in 8bits

    buffer = V_measured * Vin;
    Vout = (buffer) / 1024.0; //in volts
    buffer = (Vin / Vout) - 1;
    R2 = R1 * buffer;

    //      if (R2 > 22000)
    //      {
    //        s = ("Increase scale");
    //        return s;
    //      }
    //
    //      if (R2 < 22000)
    //      {
    //  s = String(R2)+"Kohmm";

    if (R2 < 2) {

      //  float R1 = 2; // Set this values to the value of the used resistor in K ohms
      //  V_measured= analogRead(analogPinA6); //in 8bits
      //
      //      buffer= V_measured * Vin;
      //      Vout= (buffer)/1024.0;  //in volts
      //      buffer= (Vin/Vout) -1;
      //      R2= R1 * buffer;
      return String(R2) + "Kohms";

    }
    else if (R2 > 2 && R2 < 22) {



      digitalWrite(apply_voltage, HIGH);
      pinMode(ch2K, INPUT);
      pinMode(ch20K, OUTPUT);
      pinMode(ch200K, INPUT);
      pinMode(ch1M, INPUT);
      digitalWrite(ch20K, LOW);

      float R1 = 22; // Set this values to the value of the used resistor in K ohms
      V_measured = analogRead(analogPinA6); //in 8bits

      buffer = V_measured * Vin;
      Vout = (buffer) / 1024.0; //in volts
      buffer = (Vin / Vout) - 1;
      R2 = R1 * buffer; //*1000 because we express it in ohms

      return String(R2) + "Kohms";


    }
    else if (R2 > 22 && R2 < 220) {



      digitalWrite(apply_voltage, HIGH);
      pinMode(ch2K, INPUT);
      pinMode(ch20K, INPUT);
      pinMode(ch200K, OUTPUT);
      pinMode(ch1M, INPUT);
      digitalWrite(ch200K, LOW);

      float R1 = 220; // Set this values to the value of the used resistor in K ohms
      V_measured = analogRead(analogPinA6); //in 8bits

      buffer = V_measured * Vin;
      Vout = (buffer) / 1024.0; //in volts
      buffer = (Vin / Vout) - 1;
      R2 = R1 * buffer; //*1000 because we express it in ohms

      return String(R2) + "Kohms";


    }
    else if (R2 > 220 && R2 < 2000) {



      digitalWrite(apply_voltage, HIGH);
      pinMode(ch2K, INPUT);
      pinMode(ch20K, INPUT);
      pinMode(ch200K, INPUT);
      pinMode(ch1M, OUTPUT);
      digitalWrite(ch1M, LOW);

      float R1 = 1; // Set this values to the value of the used resistor in M ohms
      V_measured = analogRead(analogPinA6); //in 8bits

      buffer = V_measured * Vin;
      Vout = (buffer) / 1024.0; //in volts
      buffer = (Vin / Vout) - 1;
      R2 = R1 * buffer; //*1000 because we express it in ohms

      return String(R2) + "mohms";


    }
    // }
    return " " ;
  }
}
////////////////////////////////////////////





///////////////////-200k-/////////////////////
//if (scale>512 && scale<=768)
//{
//  digitalWrite(apply_voltage,HIGH);
//  pinMode(ch2K,INPUT);
//  pinMode(ch20K,INPUT);
//  pinMode(ch200K,OUTPUT);
//  pinMode(ch1M,INPUT);
//  digitalWrite(ch200K,LOW);
//
//  float R1 = 220; // Set this values to the value of the used resistor in K ohms
//  V_measured= analogRead(analogPinA6); //in 8bits
//
//      buffer= V_measured * Vin;
//      Vout= (buffer)/1024.0;  //in volts
//      buffer= (Vin/Vout) -1;
//      R2= R1 * buffer;
//
//      if (R2 > 220000)
//      {
//        s = ("Increase scale");
//        //delay(1000);
//      }
//
//      if (R2 < 220000)
//      {
//         s = String(R2)+"kohm";
//        return s;
//      }
//
//}
////////////////////////////////////////////





///////////////////-1M-/////////////////////
//if (scale>768)
//{
//  digitalWrite(apply_voltage,HIGH);
//  pinMode(ch2K,INPUT);
//  pinMode(ch20K,INPUT);
//  pinMode(ch200K,INPUT);
//  pinMode(ch1M,OUTPUT);
//  digitalWrite(ch1M,LOW);
//
//  float R1= 1; // Set this values to the value of the used resistor in M ohms
//  V_measured= analogRead(analogPinA6); //in 8bits
//
//      buffer= V_measured * Vin;
//      Vout= (buffer)/1024.0;  //in volts
//      buffer= (Vin/Vout) -1;
//      R2= R1 * buffer;
//
//      if (R2 > 2000000)
//      {
//        s = ("Increase scale");
//        return s;
//      }
//
//      if (R2 < 2000000)
//      {
//         s = String(R2)+"Mohm";
//        return s;
//      }
//

//////////////////////////////////////////////













//Voltage Sensor

String volt_sens() {
  value = analogRead(A0);
  float vout = (value * 5) / 1024.0;
  float vin = vout / (R2_volt / (R1 + R2_volt));
  vin = vin * (5 / 111.2);
  if (vin < 0.09) {
    vin = 0;
  }
  return String(vin) + "V           ";
}


//Capacitive Sensor

String cap_sens() {
  s = "";
  char buff[10];
  digitalWrite(chargePin, HIGH);
  startTime = micros();
  while (analogRead(A3) < 648) {
  }

  elapsedTime = micros() - startTime;
  microFarads = ((float)elapsedTime / resistorValue) ;



  if (microFarads > 1) {




    s = (String(microFarads) + "uF            ");


  }

  else {
    nanoFarads = microFarads * 1000.0;



    s = (String(nanoFarads) + "nF                  ");

  }


  digitalWrite(chargePin, LOW);
  pinMode(dischargePin, OUTPUT);
  digitalWrite(dischargePin, LOW);     //discharging the capacitor
  while (analogRead(A3) > 0) {
  }//This while waits till the capacitor is discharged
  delay(10);
  pinMode(dischargePin, INPUT);
  return s;
}



//Current Sensor

String curr_sens() {
  String s = "";
  float c = analogRead(analogPin);
  current = c / 1023 * 5.0;
  if (current < 0.5)
  {

    s = String(current * 1.1) + "A";

  }
  else {

    s = String(current) + "A";

  }
  return s;
}
