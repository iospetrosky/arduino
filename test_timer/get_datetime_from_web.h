// all the necessary includes must be already in place
void dbg(String text) {
    Serial.println(text);
}

String get_datetime_from_web() {
    const char* host = "worldtimeapi.org";
    //String url = "http://worldtimeapi.org/api/timezone/Europe/London";
    String url = "http://192.168.1.30/microtools/datetime.php";
    WiFiClient client;
    HTTPClient http;
    String response;
    dbg("Init HTTP request");

    // http.begin(client, "worldtimeapi.org", 80, "/api/timezone/Europe/London" );
    // int httpcode = http.GET();
    // if (httpcode > 0) {
    //     response = http.getString();
    //     http.end();
    // } else {
    //     dbg("Bad");
    //     return "";
    // }

    http.begin(client, url); // Initialize the request
    int httpCode = http.GET(); // Send the GET request

    if (httpCode > 0) {
        response = http.getString(); // Get the response body
        http.end(); // Close connection
    } else {
        dbg("Bad call");
        http.end();
        return "0000-00-00 00:00:00";
    }

#ifdef DEBUG
    Serial.println("==========");
    Serial.println(response);
    Serial.println("==========");
#endif
    int dtpos = response.indexOf("dateTime") + 11;
    String dtext = response.substring(dtpos, dtpos + 19);
    dtext.replace("T", " ");
    dbg(dtext);
    return dtext;
}