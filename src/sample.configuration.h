// Wifi: SSID and password
const char* WIFI_SSID = "your-ssid";
const char* WIFI_PASSWORD = "your-wifi-password";

// MQTT: ID, server IP, port, username and password
const PROGMEM char* MQTT_CLIENT_ID = "motion_sensor_01";
const PROGMEM char* MQTT_SERVER_IP = "192.168.#.#";
const PROGMEM uint16_t MQTT_SERVER_PORT = 1883;
const PROGMEM char* MQTT_USER = "homeassistant";
const PROGMEM char* MQTT_PASSWORD = "####";

// MQTT: topics
const char* MQTT_MOTION_STATE_TOPIC = "motion/sensor/motion01/status";

// buffer used to send/receive data with MQTT
const uint8_t MSG_BUFFER_SIZE = 20;

// payloads by default (on/off)
const char* PAYLOAD_ON = "ON";
const char* PAYLOAD_OFF = "OFF";

/*---PINS ------*/
int ledPin = 0;
int pirPin = 2;