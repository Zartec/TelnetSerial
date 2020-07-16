/**
 * This example shows how to create a serial telnet server on a custom port
 */

#include <TelnetSerial.h>

void setup() {
    /*
     * Setup you WiFi connection here.
     */
    
    TSerial.setup(456);
}

void loop() {
    /*
     * This call waits for the first client.
     * ArduinoOTA is handled while waiting.
     */
    TSerial.loop();
}
