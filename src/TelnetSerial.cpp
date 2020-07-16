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
 TelnetSerial.cpp - Library for sending serial messages via telnet.
 Created by Zartec on 16.07.20.
*/

#include "TelnetSerial.h"

#include <ArduinoOTA.h>

uint8_t i = 0;
bool connected = false;
size_t result = 0;

TelnetSerial::TelnetSerial() : _sessionCount(0), _server(DEFAULT_TELNET_PORT) {
}

void TelnetSerial::begin(uint16 port /*= DEFAULT_TELNET_PORT*/) {
    _server.begin(port);
    _server.setNoDelay(true);
}

void TelnetSerial::loop() {
    for (WiFiClient& client : _clients) {
        if (client && !client.connected()) {
            client.stop();
            _sessionCount--;
        }
    }

    if (_server.hasClient()) {
        connected = false;
        for(i = 0; i < MAX_TELNET_CLIENTS; i++) {
            if (!_clients[i]) {
                _clients[i] = _server.available();
                _clients[i].flush();
                _clients[i].println(F("Welcome"));
                _clients[i].print(F("Running for "));
                _clients[i].print(millis());
                _clients[i].println(F(" ms"));
                _clients[i].println(F("----------------------------------------------------------------"));
                connected = true;
            }
        }

        if (!connected) {
            WiFiClient client = _server.available();
            client.flush();
            client.println(F("To many sessions connected!"));
            client.stop();
        } else {
            _sessionCount++;
        }
    }

    for (WiFiClient& client : _clients) {
        if (client && client.connected() && client.available()) {
            while(client.available()) {
                client.read();
            }
        }
    }
}

void TelnetSerial::waitForClient() {
    while (!_sessionCount) {
        loop();
        ArduinoOTA.handle();
        yield();
    }
}

size_t TelnetSerial::write(uint8_t c) {
    for(i = 0; i < MAX_TELNET_CLIENTS; i++) {
        if (_clients[i] && _clients[i].connected()) {
            result = _clients[i].write(c);
        }
    }
    return result;
}

size_t TelnetSerial::write(const uint8_t* buffer, size_t size) {
    for(i = 0; i < MAX_TELNET_CLIENTS; i++) {
        if (_clients[i] && _clients[i].connected()) {
            result = _clients[i].write(buffer, size);
        }
    }
    return result;
}

#if !defined(NO_GLOBAL_INSTANCES) && !defined(NO_GLOBAL_TSERIAL)
TelnetSerial TSerial;
#endif
