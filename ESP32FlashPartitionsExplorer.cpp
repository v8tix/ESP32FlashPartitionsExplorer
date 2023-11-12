#include <Arduino.h>
#include <esp_partition.h>
#include <ArduinoJson.h>

// Function to get a description for the partition type
String getPartitionTypeDescription(esp_partition_type_t type) {
  switch (type) {
    case ESP_PARTITION_TYPE_APP:
      return "Application";
    case ESP_PARTITION_TYPE_DATA:
      return "Data";
    default:
      return "Unknown";
  }
}

// Function to get a description for the partition subtype
String getPartitionSubtypeDescription(esp_partition_type_t type, esp_partition_subtype_t subtype) {
  if (type == ESP_PARTITION_TYPE_APP) {
    switch (subtype) {
      case ESP_PARTITION_SUBTYPE_APP_FACTORY:
        return "Factory application partition";
      case ESP_PARTITION_SUBTYPE_APP_OTA_MIN ... ESP_PARTITION_SUBTYPE_APP_OTA_MAX:
        return "OTA partition " + String(subtype - ESP_PARTITION_SUBTYPE_APP_OTA_MIN);
      default:
        return "Unknown";
    }
  } else if (type == ESP_PARTITION_TYPE_DATA) {
    switch (subtype) {
      case ESP_PARTITION_SUBTYPE_DATA_OTA:
        return "OTA selection partition";
      case ESP_PARTITION_SUBTYPE_DATA_PHY:
        return "PHY init data partition";
      case ESP_PARTITION_SUBTYPE_DATA_NVS:
        return "NVS partition";
      case ESP_PARTITION_SUBTYPE_DATA_COREDUMP:
        return "COREDUMP partition";
      case ESP_PARTITION_SUBTYPE_DATA_NVS_KEYS:
        return "Partition for NVS keys";
      case ESP_PARTITION_SUBTYPE_DATA_EFUSE_EM:
        return "Partition for emulate eFuse bits";
      case ESP_PARTITION_SUBTYPE_DATA_UNDEFINED:
        return "Undefined (or unspecified) data partition";
      case ESP_PARTITION_SUBTYPE_DATA_ESPHTTPD:
        return "ESPHTTPD partition";
      case ESP_PARTITION_SUBTYPE_DATA_FAT:
        return "FAT partition";
      case ESP_PARTITION_SUBTYPE_DATA_SPIFFS:
        return "SPIFFS partition";
      default:
        return "Unknown";
    }
  } else {
    // Add cases for other partition types and their subtypes as needed
  }

  return "Unknown";
}

// Function to print information about each partition as JSON
String getPartitionsDetails() {
  // Use esp_partition_iterator_t to iterate through all available partitions
  esp_partition_iterator_t it = esp_partition_find(ESP_PARTITION_TYPE_ANY, ESP_PARTITION_SUBTYPE_ANY, NULL);

  // Create a JSON array to hold individual partition objects
  DynamicJsonDocument jsonDoc(4096);  // Adjust the size based on your requirements
  JsonArray partitions = jsonDoc.to<JsonArray>();

  while (it != NULL) {
    const esp_partition_t* partition = esp_partition_get(it);

    // Create a JSON object for each partition
    JsonObject partitionInfo = partitions.createNestedObject();

    // Add partition information to the JSON object
    partitionInfo["label"] = partition->label;

    // Add type information to the JSON object
    JsonObject typeInfo = partitionInfo.createNestedObject("type");
    typeInfo["code"] = partition->type;
    typeInfo["description"] = getPartitionTypeDescription(partition->type);

    // Handle ESP_PARTITION_TYPE_DATA differently
    if (partition->type == ESP_PARTITION_TYPE_DATA) {
      // Add subtype information directly under the "subtype" node
      JsonObject subtypeInfo = partitionInfo.createNestedObject("subtype");

      // Iterate through all possible subtypes and handle each case individually
      switch (partition->subtype) {
        case ESP_PARTITION_SUBTYPE_DATA_OTA:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_DATA_OTA;
          subtypeInfo["description"] = "OTA selection partition";
          break;
        case ESP_PARTITION_SUBTYPE_DATA_PHY:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_DATA_PHY;
          subtypeInfo["description"] = "PHY init data partition";
          break;
        case ESP_PARTITION_SUBTYPE_DATA_NVS:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_DATA_NVS;
          subtypeInfo["description"] = "NVS partition";
          break;
        case ESP_PARTITION_SUBTYPE_DATA_COREDUMP:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_DATA_COREDUMP;
          subtypeInfo["description"] = "COREDUMP partition";
          break;
        case ESP_PARTITION_SUBTYPE_DATA_NVS_KEYS:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_DATA_NVS_KEYS;
          subtypeInfo["description"] = "Partition for NVS keys";
          break;
        case ESP_PARTITION_SUBTYPE_DATA_EFUSE_EM:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_DATA_EFUSE_EM;
          subtypeInfo["description"] = "Partition for emulate eFuse bits";
          break;
        case ESP_PARTITION_SUBTYPE_DATA_UNDEFINED:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_DATA_UNDEFINED;
          subtypeInfo["description"] = "Undefined (or unspecified) data partition";
          break;
        case ESP_PARTITION_SUBTYPE_DATA_ESPHTTPD:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_DATA_ESPHTTPD;
          subtypeInfo["description"] = "ESPHTTPD partition";
          break;
        case ESP_PARTITION_SUBTYPE_DATA_FAT:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_DATA_FAT;
          subtypeInfo["description"] = "FAT partition";
          break;
        case ESP_PARTITION_SUBTYPE_DATA_SPIFFS:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_DATA_SPIFFS;
          subtypeInfo["description"] = "SPIFFS partition";
          break;
        default:
          subtypeInfo["code"] = partition->subtype;
          subtypeInfo["description"] = "Unknown";
      }
    } else if (partition->type == ESP_PARTITION_TYPE_APP) {
      // Add subtype information directly under the "subtype" node
      JsonObject subtypeInfo = partitionInfo.createNestedObject("subtype");

      // Handle ESP_PARTITION_TYPE_APP subtypes
      switch (partition->subtype) {
        case ESP_PARTITION_SUBTYPE_APP_FACTORY:
          subtypeInfo["code"] = ESP_PARTITION_SUBTYPE_APP_FACTORY;
          subtypeInfo["description"] = "Factory application partition";
          break;
        case ESP_PARTITION_SUBTYPE_APP_OTA_MIN ... ESP_PARTITION_SUBTYPE_APP_OTA_MAX:
          subtypeInfo["code"] = partition->subtype;
          subtypeInfo["description"] = "OTA partition " + String(partition->subtype - ESP_PARTITION_SUBTYPE_APP_OTA_MIN);
          break;
        default:
          subtypeInfo["code"] = partition->subtype;
          subtypeInfo["description"] = "Unknown";
      }
    } else {
      // Add subtype information directly under the "subtype" node
      JsonObject subtypeInfo = partitionInfo.createNestedObject("subtype");
      subtypeInfo["code"] = partition->subtype;
      subtypeInfo["description"] = getPartitionSubtypeDescription(partition->type, partition->subtype);
    }

    // Add memory information to the JSON object within the "mem" node
    JsonObject memInfo = partitionInfo.createNestedObject("mem");
    memInfo["offset"]["dec"] = (uintptr_t)partition->address;
    memInfo["offset"]["hex"] = "0x" + String((uintptr_t)partition->address, HEX);

    // Calculate the end_at based on the offset and size
    uintptr_t endAt = (uintptr_t)partition->address + partition->size;
    // Add end_at information to the "mem" node
    memInfo["end_at"]["dec"] = endAt;
    memInfo["end_at"]["hex"] = "0x" + String(endAt, HEX);

    // Add size information to the "mem" node in different units
    JsonObject sizeInfo = memInfo.createNestedObject("size");
    sizeInfo["bytes"] = partition->size;
    sizeInfo["kilobytes"] = partition->size / 1024.0;
    sizeInfo["megabytes"] = partition->size / (1024.0 * 1024.0);

    // Move to the next partition
    it = esp_partition_next(it);
  }

  // Release the iterator
  esp_partition_iterator_release(it);

  // Serialize the JSON array to a string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Return the JSON string
  return "{\"partitions\":" + jsonString + "}";
}