#include <Servo.h> //includes the servo library
#include <LiquidCrystal.h>
//initialize the interface pins
LiquidCrystal lcd(2, 3, A1, A2, A3, A4);

#include <MUX74HC4067.h>
MUX74HC4067 mux(8, 9, 10, 11, 12);

float amp1=0, amp2=0, amp3=0, amp4=0;
float V1=0, V2=0, V3=0;
float power1=0, power2=0, power3=0;
float temp=0;
int timer=0, timer0=0;
int tolerance = 50; // allowable tolerance setting - so solar servo motor isn't constantly in motion

int light =0;

int Vo;
float R1 = 10000; // value of R1 on board
float logR2, R2, T; //steinhart-hart coeficients for thermistor
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; 

#define en  5 //Enable IBT2 Pin  // Motor Speed
#define in1 6 //Motor  IBT2 Pin  //Motor Forward
#define in2 7 //Motor  IBT3 Pin  //Motor Backward

void setup() {
Serial.begin(9600);

pinMode(en,  OUTPUT); // declare as output for IBT2 Pin enA 
pinMode(in1, OUTPUT); // declare as output for IBT2 Pin in1 
pinMode(in2, OUTPUT); // declare as output for IBT2 Pin in2 

analogWrite(en, 120); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed 

mux.signalPin(A0, INPUT, ANALOG);
  
lcd.begin(20, 4);
lcd.setCursor(0, 0);
lcd.print("     WELCOME");
lcd.setCursor(0,1); 
lcd.print("    ");

delay(2000);
lcd.clear();
}

void loop() {


if(timer==0){
  delay(10);
  
  Vo = mux.read(6);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); //calculate resistance on thermistor
  logR2 = log(R2);
  temp = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
  
  temp = temp - 273.15; //convert Kelvin to Celcius
 // T = (T * 9.0)/ 5.0 + 32.0; //convert Celcius to Fahrenheit
} // read temperature

amp1 = 0;
for(int i = 0; i < 500; i++) {
amp1 = amp1 + (.0286 * mux.read(3) -14.53) / 500;
}

amp2 = 0;
for(int i = 0; i < 500; i++) {
amp2 = amp2 + (.0286 * mux.read(4) -14.53) / 500;
}

amp3 = 0;
for(int i = 0; i < 500; i++) {
amp3 = amp3 + (.0286 * mux.read(5) -14.53) / 500;
}

amp4 = 0;
for(int i = 0; i < 500; i++) {
amp4 = amp4 + (.0286 * mux.read(9) -14.53) / 500;
}

V1= ((mux.read(0)*(4.5/1023)*15)); delay(10);
V2= ((mux.read(1)*(4.5/1023)*15)); delay(10);
V3= ((mux.read(2)*(4.5/1023)*15)); delay(10);

if(amp1<0)amp1=0;
if(amp2<0)amp2=0;
if(amp3<0)amp3=0;

power1 = V1*amp1;
power2 = V2*amp2;
power3 = V3*amp3;

lcd.setCursor(0,0);  lcd.print("S1:"); lcd.print(V1,1); lcd.print("  ");     
lcd.setCursor(8,0);  lcd.print(amp1);   lcd.print("  "); 
lcd.setCursor(15,0); lcd.print(power1,1); lcd.print(" "); 

lcd.setCursor(0,1);  lcd.print("S2:"); lcd.print(V2,1); lcd.print("  ");     
lcd.setCursor(8,1);  lcd.print(amp2);   lcd.print("  "); 
lcd.setCursor(15,1); lcd.print(power2,1); lcd.print(" "); 

lcd.setCursor(0,2);  lcd.print("S3:"); lcd.print(V3,1); lcd.print("  ");     
lcd.setCursor(8,2);  lcd.print(amp3);   lcd.print("  "); 
lcd.setCursor(15,2); lcd.print(power3,1); lcd.print(" "); 

lcd.setCursor(0,3);     
lcd.print("Temperature: ");
lcd.print(temp,1);   
lcd.write(223);
lcd.print("C ");  

int val1 = mux.read(7); // read the value of ldr 1
delay(10);
int val2 = mux.read(8); // read the value of ldr 2
delay(10);
   
//Serial.print(val1); Serial.print("  \t  "); 
//Serial.println(val2); 

   
 if((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance)) {
digitalWrite(in1, LOW); //Right Motor forword Pin 
digitalWrite(in2, LOW);  //Right Motor backword Pin 
}else {
if(val1 > val2) {        
if(amp4<1.0){digitalWrite(in1, HIGH);} //Right Motor forword Pin 
else {digitalWrite(in1, LOW);}
digitalWrite(in2, LOW);  //Right Motor backword Pin 
 }else{       
digitalWrite(in1, LOW);  //Right Motor forword Pin 
if(amp4<1.0){digitalWrite(in2, HIGH);} //Right Motor backword Pin 
else{digitalWrite(in2, LOW);} 
}
}

light = map(val1,0,1023,100,0);

//Serial.println(light); 

timer0=timer0+1;
if(timer0>20){timer0=0; 
timer=timer+1;
if(timer>4)timer=0;
Wi-Fi();
}

delay(1);
}//main loop ends

void Wi-Fi(){
     if(timer==0){Serial.print("A");Serial.println(power1);}
else if(timer==1){Serial.print("B");Serial.println(power2);}
else if(timer==2){Serial.print("C");Serial.println(power3);} 
else if(timer==3){Serial.print("D");Serial.println(temp);}
else if(timer==4){Serial.print("E");Serial.println(light);}
}
