 /*

  {"function_name":"SendRadioCode","code":"10"}%
  {"function_name":"SendRadioCode","code":"99"}% 
  {"function_name":"temperature"}%
  {"function_name":"lumiere"}%
*/

#include <ArduinoJson.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

// Serial buffer
String command = "";

// End of command marker
char endMarker = '%';



void executeFunction(String json_data) {
  StaticJsonBuffer<200> jsonBuffer;
 
  JsonObject& SendRadioCode = jsonBuffer.parseObject(json_data);
  if ( SendRadioCode["function_name"] == String("SendRadioCode") )
  {
    allume_prise(SendRadioCode["code"]);
  }

  JsonObject& humidity_and_temp = jsonBuffer.parseObject(json_data);
  if ( humidity_and_temp["function_name"] == String("temperature") )
  {
    temperature();
  }

  JsonObject& lumiere = jsonBuffer.parseObject(json_data);
  if ( lumiere["function_name"] == String("lumiere") )
  {
    verif_lumiere();
  }
}

void temperature() {
  // Mesure la tension sur la broche A0 (sortie capteur) et A1 (rÃ©fÃ©rence du point zÃ©ro)
  int valeur_brute = analogRead(A0);
 
  
  // Transforme la mesure (nombre entier) en température via un produit en croix
  float temperature_celcius = (valeur_brute * (1.1 / 1023.0 * 100.0));
   
  // Envoi la mesure au PC pour affichage
  // Serial.println(temperature_celcius);
  Serial.print("{\"devicetype\":\"19\",\"value\":");
  Serial.print(temperature_celcius);
  Serial.print("}\n");

}

void verif_lumiere(){
  int valeur = analogRead(A2);
  
    Serial.print("{\"devicetype\":\"20\",\"value\":");
    Serial.print(valeur);
    Serial.print("}\n");
  }



/**
   This function is automatically called when data is received on serial port
*/
void serialEvent() {
  //lit toutes les données (vide le buffer de réception)
  char last_readed_char = Serial.read();
  if ( last_readed_char == endMarker ) {
    executeFunction(command);
    command = "";
  } else {
    command += last_readed_char;
  }
}



void setup() {
  Serial.begin(9600);
  analogReference(INTERNAL); 
  mySwitch.enableReceive(0);
  mySwitch.setRepeatTransmit(25);
  mySwitch.enableTransmit(10);
  mySwitch.setProtocol(1);
  mySwitch.setPulseLength(489);
  Serial.println("init ");

 delay(1000);

}


void loop() {


  if (mySwitch.available()) {
    int value = mySwitch.getReceivedValue();

    if (value == 0) {
      Serial.print("Unknown encoding");
    }
    else {
      Serial.print("Received ");
      Serial.print( mySwitch.getReceivedValue() );
      Serial.print(" / ");
      Serial.print( mySwitch.getReceivedBitlength() );
      Serial.print("bit ");
      Serial.print("Protocol: ");
      Serial.println( mySwitch.getReceivedProtocol() );
  
    }
    delay(200);
    mySwitch.resetAvailable();
  }

}



void allume_prise(long code) {
  //  Serial.print(code);


int ledPin1 = 7; 
int ledPin2 = 6;
int ledPin3 = 5;
int ledPin4 = 4;       
int ledPin5 = 8;
  

  if (code == 1)
  {
    mySwitch.send(1381716, 24);
    //  Serial.print("prise 1 est etiente");


    Serial.print("{\"devicetype\":\"14\",\"value\":");
    Serial.print("1");
    Serial.print("}\n");
    digitalWrite(ledPin1, LOW);   // sets the LED off
 
  }
  else if (code == 2)
  {
    mySwitch.send(1381717, 24);
    //  Serial.print("prise 1 est allumee");
    Serial.print("{\"devicetype\":\"14\",\"value\":");
    Serial.print("2");
    Serial.print("}\n");
    digitalWrite(ledPin1, HIGH);   // sets the LED on
 
  }

  else if (code == 3) {
    mySwitch.send(1394004, 24);
    // Serial.print("prise 2 est etiente");
    Serial.print("{\"devicetype\":\"15\",\"value\":");
    Serial.print("3");
    Serial.print("}\n");
     digitalWrite(ledPin2, LOW);   // sets the LED off
  }
  else if (code == 4)
  {
    mySwitch.send(1394005, 24);
    //  Serial.print("prise 2 est allumee");
    Serial.print("{\"devicetype\":\"15\",\"value\":");
    Serial.print("4");
    Serial.print("}\n");
    digitalWrite(ledPin2, HIGH);   // sets the LED on
  }


  else if (code == 5)
  {
    sendCommand(0, 0, 0);
    //  Serial.print("prise 3 est etiente");
    Serial.print("{\"devicetype\":\"16\",\"value\":");
    Serial.print("5");
    Serial.print("}\n");
     digitalWrite(ledPin3, LOW);   // sets the LED off
  }
  else if (code == 6) {
    sendCommand(0, 0, 1);
    //  Serial.print("prise 3 est allumee");
    Serial.print("{\"devicetype\":\"16\",\"value\":");
    Serial.print("6");
    Serial.print("}\n");
    digitalWrite(ledPin3, HIGH);   // sets the LED on
  }


  else if (code == 7)
  {
    sendCommand(1, 0, 0);
    //  Serial.print("prise 4 est etiente");
    Serial.print("{\"devicetype\":\"17\",\"value\":");
    Serial.print("7");
    Serial.print("}\n");
     digitalWrite(ledPin4, LOW);   // sets the LED off
  }

  else  if (code == 8)
  {
    sendCommand(1, 0, 1);
    //  Serial.print("prise 4 est allumee");
    Serial.print("{\"devicetype\":\"17\",\"value\":");
    Serial.print("8");
    Serial.print("}\n");
    digitalWrite(ledPin4, HIGH);   // sets the LED on
  }

  else if (code == 11)
  {
     mySwitch.send(1397076, 24);
    //  Serial.print("prise 5 est etiente");
    Serial.print("{\"devicetype\":\"17\",\"value\":");
    Serial.print("11");
    Serial.print("}\n");
     digitalWrite(ledPin5, LOW);   // sets the LED off
  }

  else  if (code == 12)
  {
     mySwitch.send(1397079, 24);
    //  Serial.print("prise 5 est allumee");
    Serial.print("{\"devicetype\":\"17\",\"value\":");
    Serial.print("12");
    Serial.print("}\n");
    digitalWrite(ledPin5, HIGH);   // sets the LED on
  }
  else if (code == 10)
  {
    sendCommand(0, 0, 0);
    delay(50);
    sendCommand(1, 0, 0);
    delay(50);
    mySwitch.send(1394004, 24);
    delay(50);
    mySwitch.send(1381716, 24);
    // Serial.print("toutes les prises sont etientes");
    Serial.print("{\"devicetype\":\"xx\",\"value\":");
    Serial.print("10");

    Serial.print("}\n");
  }

  else  if (code == 9)
  {
    mySwitch.send(1394005, 24);
    delay(50);
    mySwitch.send(1381717, 24);
    delay(50);
    sendCommand(0, 0, 1);
    delay(50);
    sendCommand(1, 0, 1);
    //Serial.print("toutes les prises sont allumees");
    Serial.print("{\"devicetype\":\"xx\",\"value\":");
    Serial.print("11");
    Serial.print("}\n");
  }
  else  if (code == 99)
  {
    temperature();
  }
  else
  {
    Serial.print("code inconnu");
  }
}


void sendCommand(int selector, int number, int state) {
  // all list are zero based
  // Selector list (A, B, C)
  char *selectorCodes[3] = { "0FF", "F0F", "FF0"};

  // Button number list
  char *buttonCodes[4] = {"0FFFFFFF", "F0FFFFFF", "FF0FFFFF", "FFF0FFFF"};

  // State list
  char *stateCodes[2] = { "0", "1" };

  // Concatenate into Tri-State command
  char sendCommand[12] = "";
  strcat(sendCommand, selectorCodes[selector]);
  strcat(sendCommand, buttonCodes[number]);
  strcat(sendCommand, stateCodes[state]);

  // Send the code
  Serial.println(sendCommand);
  mySwitch.sendTriState(sendCommand);
}


