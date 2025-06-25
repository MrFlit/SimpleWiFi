# SimpleWiFi
WiFi Library for ESP32

🔌 Installation:
1) Open Arduino IDE.
2) Sketch> connect the library> Add .Zip library
3) Select simplewifi.zip


## 🧱 Class: Simplewifi

🔧 Variables:
- _ssid and _password - lines with current connection data.
- _timeout - connection expectations (default 10 seconds).

## 🧩 Methods:

| Method                   | Description                                            |
| ----------------------- | --------------------------------------------------- |
| `begin(ssid, password)` | Launches the connection and saves data in memory   |
| `beginFromStorage()`    | Uploads saved data and connects         |
| `connect()`             | Connects to Wi-Fi and displays the status               |
| `ensureConnected()`     | Checks the connection, with a break - retracts |
| `isConnected()`         | Returns `true` if ESP32 is connected             |
| `getIP()`               | Returns ESP32 IP addresses                    |
| `getSSID()`             | Returns the current SSID                             |
| `getRSSI()`             | Returns the signal level (dBm)                  |
| `setTimeout(ms)`        | Installs the connection timeout                   |


## Example 1: Simple connection and preservation
```
#include <SimpleWiFi.h><br/>
SimpleWiFi wifi;
void setup() {
  Serial.begin(115200);
  wifi.begin("MyNetwork", "MyPassword"); // Saves and connects
}
void loop() {
  wifi.ensureConnected(); // Personation during a break
  delay(5000);
}
```
## Example 2: Connection using saved data
```
#include <SimpleWiFi.h>
SimpleWiFi wifi;
void setup() {
  Serial.begin(115200);
  wifi.beginFromStorage(); // uploads the latest saved data
}
void loop() {
  if (!wifi.isConnected()) {
    Serial.println("📡 Loss of communication!");
    wifi.ensureConnected();
  } else {
    Serial.println("✅ IP: " + wifi.getIP());
  }
  delay(5000);
}
```

