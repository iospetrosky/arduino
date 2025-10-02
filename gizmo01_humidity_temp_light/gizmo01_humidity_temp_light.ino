#define LED D4 // built in led on board
#define RED_LED D2
#define WHITE_LED D1

#define DHTPIN D7     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22 // DHT 22 (AM2302)

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <DHT.h>
#include <DHT_U.h>

// WiFi parameters to be configured
const char *ssid = "lorenzo_work24"; // Write here your router's username
const char *password = "f3d3r1c0";   // Write here your router's passward

DHT dht(DHTPIN, DHTTYPE);

void setup(void)
{
    pinMode(LED, OUTPUT);       // LED pin as output.
    pinMode(RED_LED, OUTPUT);   // LED pin as output.
    pinMode(WHITE_LED, OUTPUT); // LED pin as output.
    pinMode(D0, WAKEUP_PULLUP); // doesn't change anything

    Serial.begin(115200); // or 9600
    // while(!Serial) {}
    Serial.println("xx"); // this starts a new line in the console after all the rubbish during the connection
    Serial.println("Connecting to WiFi");
    // Connect to WiFi
    digitalWrite(RED_LED, LOW);
    digitalWrite(WHITE_LED, LOW);
    digitalWrite(LED, HIGH); // this actually switches OFF

    WiFi.begin(ssid, password);

    // while wifi not connected yet, print '.'
    int k = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        delay(100);
        k++;
        if (k > 100)
        {
            Serial.println("WiFi not connecting - forced restart");
            ESP.restart();
        }
    }

    // Print the IP address
    Serial.println(WiFi.localIP());
    blink_times(RED_LED, 10, 30);

    dht.begin();
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

void go_to_sleep(float minutes)
{
    blink_times(LED, 5, 30);
    Serial.print("Now going to sleep for ");
    long msecs = minutes * 60 * 1000 * 1000;
    Serial.print(msecs);
    Serial.println(" microseconds");
    ESP.deepSleep(msecs, WAKE_RFCAL); // or WAKE_RF_DEFAULT, WAKE_RF_DISABLED, doesn't work either
                                      // delay(2000);
}

void loop()
{
    Serial.println("Main loop");
    delay(2000); // Wait a few seconds between measurements
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (isnan(humidity) || isnan(temperature))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
    go_to_sleep(0.25);
}

/*

// now try to make an http call
  digitalWrite(WHITE_LED, LOW);
  delay(500);
  WiFiClient client;
  HTTPClient http;

  String serverPath = "http://192.168.1.30/microtools/greenhouse.php?act=ADDMEASURE&senstype=Humidity&measure=38&sensloc=WHITE";
  http.begin(client, serverPath.c_str());
  int httpResponseCode = http.GET();
  http.end();
  digitalWrite(WHITE_LED, HIGH);
*/
