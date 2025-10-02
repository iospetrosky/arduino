// all the necessary includes must be already in place
String get_datetime_from_web() {
    // const char* host = "httpbin.org";
    const char* host = "timeapi.io";
    // String url = "/get";
    String url = "/api/Time/current/zone?timeZone=Europe/London";
    unsigned long startTime = millis();
    const unsigned long timeout = 10000; // 10 seconds

    WiFiClientSecure client;

    client.setInsecure();
    Serial.println("Starting connection attempts to time server...");
    while (!client.connect(host, 443) && millis() - startTime < timeout) {
        delay(100); // small delay to avoid busy looping
        Serial.println("Retry");
    }
    if (!client.connected()) {
        Serial.println("Connection to time server timed out");
        return "0000-00-00 00:00:00";
    }

    // if (!client.connect(host, 443)) {  // 443 is the https port
    //     Serial.println("Connect to Time server failed");
    //     return "0000-00-00 00:00:00";
    // }

    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host +
                 "\r\n" + "Connection: close\r\n\r\n");
#ifdef DEBUG
    Serial.println("request sent");
#endif
    while (client.connected()) {
        String line = client.readStringUntil('\n');
#ifdef DEBUG
        Serial.println(line);
#endif
        if (line == "\r") {
#ifdef DEBUG
            Serial.println("headers received");
#endif
            break;
        }
    }

    String chunk = "";
    int limit = 1;
    String response = "";

    /* it could be a little more clever, but I read until I find a chunk
       starting with a { I keep that chunk and terminate the transfer */
    do {
        if (client.connected()) {
            client.setTimeout(2000);
            chunk = client.readStringUntil('\n');
#ifdef DEBUG
            Serial.println(chunk);
#endif
            if (chunk.startsWith("{")) {
                response = chunk;
                break;
            }
        }
    } while (chunk.length() > 0 && ++limit < 100);
#ifdef DEBUG
    Serial.println("==========");
    Serial.println(response);
    Serial.println("==========");
#endif
    int dtpos = response.indexOf("dateTime") + 11;
    String dtext = response.substring(dtpos, dtpos + 19);
    dtext.replace("T", " ");
#ifdef DEBUG
    Serial.println(dtext);
#endif
    return dtext;
}