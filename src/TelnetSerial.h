/*
 * Copyright (c) 2020 Zartec <admin@zartec.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/*
 TelnetSerial.h - Library for sending serial messages via telnet.
 Created by Zartec on 16.07.20.
*/
#ifndef TelnetSerial_H
#define TelnetSerial_H

#include <Arduino.h>
#include <WiFiServer.h>
#include <WiFiClient.h>

#ifndef DEFAULT_TELNET_PORT
#define DEFAULT_TELNET_PORT 23
#endif
#ifndef MAX_TELNET_CLIENTS
#define MAX_TELNET_CLIENTS 3
#endif

class TelnetSerial : public Print {
public:
    TelnetSerial();

    TelnetSerial(const TelnetSerial&) = delete;

    TelnetSerial& operator=(const TelnetSerial&) = delete;

public:
    /**
     * Starts the telnet server.
     * If no port given it uses the default telnet port 23.
     *
     * @param port The port to listen on
     */
    void begin(uint16_t port = DEFAULT_TELNET_PORT);

    /**
     * Updates the internal logic.
     */
    void loop();

    /**
     * Waits for the first telnet connection before continuing.
     * ArduinoOTA is handled while waiting.
     */
    void waitForClient();

    /**
     * Writes a single char to all serial clients.
     *
     * Required for Print interface.
     *
     * @param c The char to write
     * @return The number chars sent
     */
    size_t write(uint8_t c) override;

    /**
     * Writes a buffer with a given size to all serial clients.
     *
     * Required for Print interface.
     *
     * @param buffer The buffer to write
     * @param size The size of the buffer
     * @return The number chars sent
     */
    size_t write(const uint8_t* buffer, size_t size) override;

    /**
     * Implement Print interface functionality.
     */
    using Print::write;

private:
    uint8_t _sessionCount;
    WiFiServer _server;
    WiFiClient _clients[MAX_TELNET_CLIENTS];
};

extern TelnetSerial TSerial;

#endif //TelnetSerial_H
