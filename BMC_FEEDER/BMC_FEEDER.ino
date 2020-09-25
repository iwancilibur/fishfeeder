#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <PCA9685.h>
#include <PCF8574.h>
#include <EEPROM.h>

// adjust addresses if needed
PCF8574 Port1(0x20);  //Create an instance of the library
PCF8574 Port2(0x21);  //Create an instance of the library

const char* ssid = "BMC Makerspace";
const char* password = "123qweasd";
const char* mqtt_server = "110.35.82.86";
      char* clientid="iwanciliburDevice01";
#define mqtt_user "loradev_mqtt"
#define mqtt_password "test123"

int addr = 0;
#define EEPROM_SIZE 64

PCA9685 pwmController(Wire, PCA9685_PhaseBalancer_Weaved); // Library using Wire1 and weaved phase balancing scheme
PCA9685_ServoEvaluator pwmServo;

int channel0=0;int channel1=1;int channel2=2;int channel3=3;int channel4=4;int channel5=5;int channel6=6;int channel7=7;
int channel8=8;int channel9=9;int channel10=10;int channel11=11;int channel12=12;int channel13=13;

int relay1=0;int relay2=1;int relay3=2; int relay4=3;int relay5=4;int relay6=5;int relay7=6;int relay8=7;
int relay9=0;int relay10=1; int relay11=2;int relay12=3;int relay13=4;int relay14=5;int relay15=6;int relay16=7;
  
WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  int terima=messageTemp.toInt();
  if (String(topic) == "bmc/autodrainage/relay1")  {if(messageTemp == "on"){Port1.write(relay1, HIGH); Serial.println("Relay1 HIGH");}else{Port1.write(relay1, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay2")  {if(messageTemp == "on"){Port1.write(relay2, HIGH); Serial.println("Relay2 HIGH");}else{Port1.write(relay2, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay3")  {if(messageTemp == "on"){Port1.write(relay3, HIGH); Serial.println("Relay3 HIGH");}else{Port1.write(relay3, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay4")  {if(messageTemp == "on"){Port1.write(relay4, HIGH); Serial.println("Relay4 HIGH");}else{Port1.write(relay4, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay5")  {if(messageTemp == "on"){Port1.write(relay5, HIGH); Serial.println("Relay5 HIGH");}else{Port1.write(relay5, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay6")  {if(messageTemp == "on"){Port1.write(relay6, HIGH); Serial.println("Relay6 HIGH");}else{Port1.write(relay6, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay7")  {if(messageTemp == "on"){Port1.write(relay7, HIGH); Serial.println("Relay7 HIGH");}else{Port1.write(relay7, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay8")  {if(messageTemp == "on"){Port1.write(relay8, HIGH); Serial.println("Relay8 HIGH");}else{Port1.write(relay8, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay9")  {if(messageTemp == "on"){Port2.write(relay9, HIGH); Serial.println("Relay9 HIGH");}else{Port2.write(relay9, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay10") {if(messageTemp == "on"){Port2.write(relay10, HIGH);Serial.println("Relay10 HIGH");}else{Port2.write(relay10, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay11") {if(messageTemp == "on"){Port2.write(relay11, HIGH);Serial.println("Relay11 HIGH");}else{Port2.write(relay11, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay12") {if(messageTemp == "on"){Port2.write(relay12, HIGH);Serial.println("Relay12 HIGH");}else{Port2.write(relay12, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay13") {if(messageTemp == "on"){Port2.write(relay13, HIGH);Serial.println("Relay13 HIGH");}else{Port2.write(relay13, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay14") {if(messageTemp == "on"){Port2.write(relay14, HIGH);Serial.println("Relay14 HIGH");}else{Port2.write(relay14, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay15") {if(messageTemp == "on"){Port2.write(relay15, HIGH);Serial.println("Relay15 HIGH");}else{Port2.write(relay15, LOW);}}
  if (String(topic) == "bmc/autodrainage/relay16") {if(messageTemp == "on"){Port2.write(relay16, HIGH);Serial.println("Relay16 HIGH");}else{Port2.write(relay16, LOW);}}
  
  if (String(topic) == "waktu") {
    //Serial.print("Terima Waktu:");Serial.println(terima);
    EEPROM.write(addr, terima);
    }
    
  if (String(topic) == "control") {
    Serial.print("Changing output to ");
    int waktunya=EEPROM.read(addr);
    
    if(messageTemp == "on"){
      for (int i=0; i<waktunya; i++){
      pwmController.setChannelPWM(channel0, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel1, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel2, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel3, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel4, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel5, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel6, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel7, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel8, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel9, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel10, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel11, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel12, pwmServo.pwmForAngle(0));
      pwmController.setChannelPWM(channel13, pwmServo.pwmForAngle(0));
      delay(1000);
      pwmController.setChannelPWM(channel0, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel1, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel2, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel3, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel4, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel5, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel6, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel7, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel8, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel9, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel10, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel11, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel12, pwmServo.pwmForAngle(180));
      pwmController.setChannelPWM(channel13, pwmServo.pwmForAngle(180));
      delay(1000);
    }
    }  
  }
  
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Menghubungkan ke MQTT...");
    // AtsuhuPublisht to connect
    //if (client.connect(clientid, mqtt_user, mqtt_password)) {
    if (client.connect(clientid)) {
      Serial.println("MQTT Terhubung");
      client.subscribe("waktu");
      client.subscribe("control");
      client.subscribe("bmc/autodrainage/relay1"); client.subscribe("bmc/autodrainage/relay2");
      client.subscribe("bmc/autodrainage/relay3");client.subscribe("bmc/autodrainage/relay4");
      client.subscribe("bmc/autodrainage/relay5");client.subscribe("bmc/autodrainage/relay6");
      client.subscribe("bmc/autodrainage/relay7");client.subscribe("bmc/autodrainage/relay8");
      client.subscribe("bmc/autodrainage/relay9");client.subscribe("bmc/autodrainage/relay10");
      client.subscribe("bmc/autodrainage/relay11");client.subscribe("bmc/autodrainage/relay12");
      client.subscribe("bmc/autodrainage/relay13");client.subscribe("bmc/autodrainage/relay14");
      client.subscribe("bmc/autodrainage/relay15");client.subscribe("bmc/autodrainage/relay16");
      
      // Once connected, publish an announcement...
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup()
{
  // Debug console
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  EEPROM.begin(EEPROM_SIZE);
  Wire.begin();                      // Wire must be started first
  Wire.setClock(4000);             // Supported baud rates are 100kHz, 400kHz, and 1000kHz
  pwmController.resetDevices();       // Software resets all PCA9685 devices on Wire line
  pwmController.init(B000000);        // Address pins A5-A0 set to B000000
  pwmController.setPWMFrequency(50);  // 50Hz provides 20ms standard servo phase length
  EEPROM.write(addr, 5);
  
  Port1.begin();            //Initiliase the PCF8574 (all pins are set to high)
  Port2.begin();            //Initiliase the PCF8574 (all pins are set to high)

  /*/for (int i=0; i<8; i++){
    //Port.pinMode(i, OUTPUT); //Set digital pin 0 to an ouput
    Port1.shiftRight();
    Port2.shiftRight();
  }
  /*/
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
    client.loop();
}
