#include <ESP8266WiFi.h> 
#include <FirebaseESP8266.h>

#include <SoftwareSerial.h>
SoftwareSerial uno(D6,D7); //TX,RX

#define ssid "IOT"  //WiFi SSID
#define password "78612345"  //WiFi Password

#define FIREBASE_HOST "iotproject-d1c35-default-rtdb.firebaseio.com" //Your Firebase Project URL goes here without "http:" , "\" and "/"
#define FIREBASE_AUTH "aijflOB08qtjEqNJhP9sFFIcR7tRly8YbuaRxFof" //Your Firebase Auth Token

FirebaseData firebaseData;

#define wifiLed D4 //GPIO 2

String data="";

int cont=0;

void setup(){
Serial.begin(9600);//Starting serial comunication
uno.begin(9600);
delay(100);
pinMode(wifiLed, OUTPUT); // configure the wifiLed(digital pi D4) as an OUTPUT(Voltage).
digitalWrite(wifiLed, HIGH); // digitalWrite provide either LOW or HIGH value to the digital PIN. if set HIGH, it will provide 5V to the PIN, and 0V for LOW. //red
WiFi.begin (ssid, password);

while(WiFi.status() != WL_CONNECTED){
  delay(500);
  Serial.print(".");
}
digitalWrite(wifiLed, LOW);

Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
Serial.println("Welcome");
delay(1000); 

}

void loop(){
  
while(uno.available()>0) {
    char inChar = (char)uno.read();
    if(inChar == '\n' or inChar == '\r'){ 
        
    }
    else
    {
      data += inChar;
      }
    
 if (inChar == '\n' or inChar == '\r') {

  String dataInS = data.substring(1, data.length()); // Extract only the number. E.g. from "A120" to "120"   
     if(data.charAt(0) == 'A'){
if(Firebase.setString(firebaseData, "/Power1", dataInS)){
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
}else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
   }     
     }
else if(data.charAt(0) == 'B'){
if(Firebase.setString(firebaseData, "/Power2", dataInS)){
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
}else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
   }
}
else if(data.charAt(0) == 'C'){
if(Firebase.setString(firebaseData, "/Power3", dataInS)){
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
}else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
   }
}
else if(data.charAt(0) == 'D'){
if(Firebase.setString(firebaseData, "/Temp", dataInS)){
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
}else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
   }
}
else if(data.charAt(0) == 'E'){  
if(Firebase.setString(firebaseData, "/Light", dataInS)){
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
}else{
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
   }
}

uno.flush();
data="";
  }//END OF ONE LINE
 }//END OF SERIAL AVAILABLE


delay(10);
}
