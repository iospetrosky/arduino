#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const int light_pin = A0; // the analog pin
const int green_led = D8;
const int white_led = D7;

#define DEBUG 1 // comment out to disable debug messages

void setup()
{
    Serial.begin(9600);
    pinMode(green_led, OUTPUT);
    pinMode(white_led, OUTPUT);

    digitalWrite(green_led, LOW);
    digitalWrite(white_led, LOW);
    connect_to_wifi(green_led);
}

void loop()
{
    int analog_value = analogRead(light_pin);
  
    Serial.print("Analog Value = ");
    Serial.print(analog_value); // The raw analog reading

    send_to_cloud(analog_value);
    delay(500);
    go_to_sleep(5);
}

void blink_times(int led_num, int times, int interval)
{
    for (int x = 0; x < times; x++)
    {
        digitalWrite(led_num, HIGH); // this swithes on
        delay(interval);
        digitalWrite(led_num, LOW); // this swithes off
        delay(interval);
    }
}

const char *ssid = "lorenzo_work24"; // network ID
const char *password = "f3d3r1c0";
void connect_to_wifi(int sig_led)
{
    Serial.println("Connecting to WiFi");
    WiFi.begin(ssid, password);
    int k = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(sig_led, HIGH);
        delay(100);
        digitalWrite(sig_led, LOW);
        delay(100);
        k++;
        if (k > 30)
        {
            Serial.println("WiFi not connecting - forced restart");
            ESP.restart();
        }
    }

    // Print the IP address
    Serial.println(WiFi.localIP());
    blink_times(sig_led, 10, 30);
}

void go_to_sleep(float minutes)
{
    blink_times(white_led, 5, 30);
    long msecs = minutes * 60 * 1000 * 1000;
#ifdef DEBUG
    Serial.print("Now going to sleep for ");
    Serial.print(msecs);
    Serial.println(" microseconds");
#endif
    ESP.deepSleep(msecs, WAKE_RF_DEFAULT);
    delay(2000);
}

void send_to_cloud(float value)
{
    const char* host = "api.thingspeak.com";
    String url = "/update?api_key=5XUAVVFH6RJT7IMT&field1=" + String(value);
    Serial.println(url.c_str());

    WiFiClientSecure client;

    client.setInsecure();
    if (!client.connect(host,443)) { // 443 is the https port
      Serial.println("Connect to host failure");
      return;
    }

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
  
}