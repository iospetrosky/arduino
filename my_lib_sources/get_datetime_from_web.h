// all the necessary includes must be already in place

String get_datetime_from_web() {
    String url = "http://192.168.1.30/microtools/datetime.php";
    //String url = "http://mysensors.42web.io/datetime.php";
    WiFiClient client;
    HTTPClient http;
    String response;
    dbg("Init HTTP request");

    http.begin(client, url); // Initialize the request
    int httpCode = http.GET(); // Send the GET request

    if (httpCode > 0) {
        response = http.getString(); // Get the response body
        http.end(); // Close connection
    } else {
        dbg("Error retrieving time from web");
        http.end();
        response =  "0000-00-00 00:00:00";
    }

#ifdef DEBUG
    Serial.println("==========");
    Serial.println(response);
    Serial.println("==========");
#endif
    return response;
}