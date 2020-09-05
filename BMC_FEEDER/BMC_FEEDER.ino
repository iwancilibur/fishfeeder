#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <PCA9685.h>
#include <EEPROM.h>


const char* ssid = "BMC Makerspace";
const char* password = "123qweasd";
const char* mqtt_server = "iwancilibur.my.id";
      char* clientid="iwanciliburDevice01";
      
int addr = 0;
#define EEPROM_SIZE 64

PCA9685 pwmController(Wire, PCA9685_PhaseBalancer_Weaved); // Library using Wire1 and weaved phase balancing scheme
PCA9685_ServoEvaluator pwmServo;

int channel0=0;
int channel1=1;
int channel2=2;
int channel3=3;
int channel4=4;
int channel5=5;
int channel6=6;
int channel7=7;
int channel8=8;
int channel9=9;
int channel10=10;
int channel11=11;
int channel12=12;
int channel13=13;

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
  Serial.println(terima);
 // myservo.write(terima);
  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
 
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
    Serial.print("AtsuhuPublishting MQTT connection...");
    // AtsuhuPublisht to connect
    if (client.connect(clientid)) {
      Serial.println("connected");
      client.subscribe("waktu");
      client.subscribe("control");
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
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }
    client.loop();
}
