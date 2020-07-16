# TelnetSerial

This library provides a serial interface via telnet server.

**Simple usage on defaul port 23**
```Arduino
void setup() {
    /*
     * Setup you WiFi connection here.
     */
     
    TSerial.begin();
}

void loop() {
    /*
     * Update internal logic.
     */
    TSerial.loop();
}
```

**Simple usage on specific port**
```Arduino
void setup() {
    /*
     * Setup you WiFi connection here.
     */
     
    TSerial.begin(456);
}

void loop() {
    /*
     * Update internal logic.
     */
    TSerial.loop();
}
```

**Wait for first successfull connection**
```Arduino
void setup() {
    /*
     * Setup you WiFi connection here.
     */
    TSerial.begin(456);
    
    /*
     * This call waits for the first client.
     * ArduinoOTA is handled while waiting.
     */
    TSerial.waitForClient();
}

void loop() {
    /*
     * Update internal logic.
     */
    TSerial.loop();
}
```
