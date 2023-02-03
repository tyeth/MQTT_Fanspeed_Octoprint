#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
//  INSTALL BOTH LIBRARIES ABOVE! i.e. PubSubClient and ArduinoJSON


// // Replace with your network credentials
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASS ""
#define PIN_NUMBER 15


const char* mqttServer = "YOUR_MQTT_SERVER";
const int mqttPort = 1883; // Default MQTT port
const char* mqttUsername = "YOUR_USERNAME";
const char* mqttPassword = "YOUR_PASSWORD";
// const char* MQTT_TOPIC = "octoPrint/event/DisplayLayerProgress_fanspeedChanged";
const char* MQTT_TOPIC = "octoPrint/event/DisplayLayerProgress_timerTrigger";

void callback(char* topic, byte* payload, unsigned int length);

WiFiClient espClient;
PubSubClient client(espClient);
int oldDuty = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  // Convert the incoming payload to a string
    Serial.println("mqtt msg callback:");

  char message[length + 1];
  for (int i = 0; i < length; i++) {
    message[i] = (char)payload[i];
  }
  message[length] = '\0';
  // Serial.println(message);
  
  // Parse JSON data
  DynamicJsonDocument doc(2048);
  deserializeJson(doc, message);//(char *)subscription->lastread);
  JsonObject obj = doc.as<JsonObject>();

  // Check if fanspeed is present
  if (obj.containsKey("fanspeed")) {
    Serial.println("mqtt msg has fanspeed:");
    String fanspeed = obj["fanspeed"];
    Serial.println(fanspeed);

    int duty = 0;
    if (fanspeed != "off" && fanspeed != "-") {
      if (fanspeed.endsWith("%")) {
      // Extract percentage value
        fanspeed.remove(fanspeed.length() - 1);
        duty = map(fanspeed.toInt(), 0, 100, 0, 255);
      }
      // Set PWM duty cycle
    }
    if(duty != oldDuty){
      analogWrite(PIN_NUMBER, duty);
      Serial.println("fanspeed PWM duty cycle for analogWrite:");
      Serial.println(duty);
      oldDuty = duty;
      //confirm update via mqtt? remote octoprint fan plugin? Why?
    } else {
      Serial.println("fanspeed unchanged.");
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqttUsername, mqttPassword)) {
      Serial.println("MQTT connected!");
      client.subscribe(MQTT_TOPIC);
    } else {
      Serial.println(".");
      delay(1000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setBufferSize(16*1024);
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  Serial.println("fanspeed PWM duty cycle for analogWrite:");
  Serial.println(oldDuty);
  pinMode(PIN_NUMBER, OUTPUT);
  analogWrite(PIN_NUMBER, oldDuty);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(500);
}

