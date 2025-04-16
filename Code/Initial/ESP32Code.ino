#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

void setup() 
{
  Serial.begin(115200); // For debugging
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  SerialBT.begin("ESP32_BT_HyMot"); // Initialize Bluetooth with the name "ESP32_BT"

  Serial.println("Setup Complete!");
  SerialBT.println("Setup Complete!");
}

void loop() 
{
  if (Serial2.available())
  {
    String message = Serial2.readStringUntil('\n');
    message.trim(); // Remove leading and trailing whitespace
    message.replace("\r", ""); // Remove carriage return characters
    String filteredMessage = filterNonPrintable(message);

    SerialBT.println(filteredMessage); // Send filtered message to Bluetooth
    Serial.println(filteredMessage); // Print filtered message to Serial Monitor
    // Serial.println("Sent to Bluetooth: " + message); // Debugging
  }
}

String filterNonPrintable(String input) {
  String output = "";
  for (int i = 0; i < input.length(); i++) {
    char c = input.charAt(i);
    if (isPrintable(c)) {
      output += c;
    }
  }
  return output;
}

bool isPrintable(char c) {
  return c >= 32 && c <= 126; // ASCII printable characters range
}