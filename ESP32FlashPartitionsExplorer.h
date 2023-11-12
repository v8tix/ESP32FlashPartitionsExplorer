#ifndef ESP32FlashPartitionsExplorer_h
#define ESP32FlashPartitionsExplorer_h

#include <Arduino.h>
#include <esp_partition.h>
#include <ArduinoJson.h>

// Function to print information about each partition as JSON
String getPartitionsDetails();

#endif