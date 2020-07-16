/**
 * This example shows how to create a serial telnet server
 */

#include <TelnetSerial.h>

void setup() {
    /*
     * Setup you WiFi connection here.
     */
    
    TSerial.setup();
}

void loop() {
    /*
     * This call waits for the first client.
     * ArduinoOTA is handled while waiting.
     */
    TSerial.loop();
}
