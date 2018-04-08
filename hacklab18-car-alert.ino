#include <ESP8266WiFi.h> 
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define WLAN_SSID "INVENTELECTRONICS"
#define WLAN_PASS "gob3master"


#define AIO_SERVER      "m13.cloudmqtt.com"
#define AIO_SERVERPORT  11094
#define AIO_USERNAME    "qtkxzuns"
#define AIO_KEY         "7OWJ4m8vPI5u"


WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

void MQTT_connect();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(10);

  Serial.println("\n\n==========\nHACKLAB '18\n===========\n");

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
  MQTT_connect();

  if(! mqtt.publish("/alert", "test motherfuuuuuu")){
    Serial.println("Error sending");
  }else{
    Serial.println("OK!");
  }
  
  delay(5000);
}



void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
