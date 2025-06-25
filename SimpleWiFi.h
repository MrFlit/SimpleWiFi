
#ifndef SIMPLE_WIFI_H
#define SIMPLE_WIFI_H

#include <WiFi.h>
#include <Preferences.h>

class SimpleWiFi {
  public:
    SimpleWiFi() {}

    void begin(const char* ssid, const char* password) {
      _ssid = ssid;
      _password = password;
      saveCredentials();
      connect();
    }

    void beginFromStorage() {
      loadCredentials();
      if (_ssid != "" && _password != "") {
        connect();
      } else {
        Serial.println("⚠️ No saved credentials.");
      }
    }

    void connect() {
      WiFi.begin(_ssid.c_str(), _password.c_str());
      Serial.print("Connecting to WiFi");
      unsigned long startAttemptTime = millis();

      while (WiFi.status() != WL_CONNECTED) {
        if (millis() - startAttemptTime > _timeout) {
          Serial.println("\n❌ Connection Timeout.");
          return;
        }
        Serial.print(".");
        delay(500);
      }

      Serial.println("\n✅ Connected!");
      Serial.print("IP Address: ");
      Serial.println(WiFi.localIP());
    }

    void ensureConnected() {
      if (WiFi.status() != WL_CONNECTED) {
        Serial.println("🔄 Disconnected. Reconnecting...");
        connect();
      }
    }

    bool isConnected() {
      return WiFi.status() == WL_CONNECTED;
    }

    String getIP() {
      return WiFi.localIP().toString();
    }

    String getSSID() {
      return WiFi.SSID();
    }

    int getRSSI() {
      return WiFi.RSSI();
    }

    void setTimeout(unsigned long ms) {
      _timeout = ms;
    }

  private:
    String _ssid;
    String _password;
    unsigned long _timeout = 10000; // default 10 seconds

    void saveCredentials() {
      Preferences prefs;
      prefs.begin("wifi", false);
      prefs.putString("ssid", _ssid);
      prefs.putString("pass", _password);
      prefs.end();
    }

    void loadCredentials() {
      Preferences prefs;
      prefs.begin("wifi", true);
      _ssid = prefs.getString("ssid", "");
      _password = prefs.getString("pass", "");
      prefs.end();
    }
};

#endif
