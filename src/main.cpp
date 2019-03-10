#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define MQTT_VERSION MQTT_VERSION_3_1_1

#include "configuration.h"

WiFiClient espClient;
PubSubClient client(espClient);

/*---- STATES ------*/
bool m_led_status = false;
bool m_motion_status = false;

char m_msg_buffer[MSG_BUFFER_SIZE]; 
long lastMsg = 0;

/*========= PUBLISH STATES =================================================*/

// function called to publish the motion state
void publishMotionState() {
  if (m_motion_status) {
    client.publish(MQTT_MOTION_STATE_TOPIC, PAYLOAD_ON, true);
  } else {
    client.publish(MQTT_MOTION_STATE_TOPIC, PAYLOAD_OFF, true);
  }
}

/*---- READ SENSORS ------*/

bool readMotion() {
    int motion = digitalRead(pirPin);
    if (motion == HIGH) {
        digitalWrite(ledPin, HIGH);
        return true;
    } else {
        digitalWrite(ledPin, LOW);
        return false;
    }
}

/*========= WIFI/MQTT CONNECTION ===============================================*/

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.mode(WIFI_STA);
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("connected");

      // Once connected, publish an announcement...
      // publish the initial values
      publishMotionState();

    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/*===== MAIN ===========================================================*/

void setup() {
    Serial.begin(9600);

    pinMode(ledPin, OUTPUT);
    pinMode(pirPin, INPUT);

    digitalWrite(ledPin, LOW);

    Serial.print("INFO: Connecting to ");
    WiFi.mode(WIFI_STA);
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("INFO: WiFi connected");
    Serial.print("INFO: IP address: ");
    Serial.println(WiFi.localIP());

    // init the MQTT connection
    client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    long now = millis();

    if ( (now - lastMsg > 1000) || (now < lastMsg) ) {
        lastMsg = now;

        int cMotion = readMotion();
        if (cMotion != m_motion_status) {
            m_motion_status = cMotion;
            publishMotionState();
        }
    }
}