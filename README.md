# ESP32FlashPartitionsExplorer Arduino Library

The ESP32FlashPartitionsExplorer library provide a function to retrieve details about ESP32 flash partitions and display the information in JSON format.

## Installation

1. Download the ZIP file of this repository.
2. Extract the ZIP file.
3. Rename the extracted folder to `ESP32FlashPartitionsExplorer`.
4. Move the `ESP32FlashPartitionsExplorer` folder to the `libraries` folder in your Arduino sketchbook.

## Usage

1. Include the library in your Arduino sketch:

    ```cpp
    #include <ESP32FlashPartitionsExplorer.h>
    ```

   2. Use the provided functions to get information about ESP32 flash partitions:

   ```cpp
      void setup() {
         Serial.begin(115200);
         Serial.println(getPartitionsDetails());
      }
   ```

## Functions

### `getPartitionsDetails()`

This function retrieves information about each ESP32 flash partition and returns the details in JSON format.

## Example Output

```json
{"partitions":[{"label":"nvs","type":{"code":1,"description":"Data"},"subtype":{"code":2,"description":"NVS partition"},"mem":{"offset":{"dec":36864,"hex":"0x9000"},"end_at":{"dec":57344,"hex":"0xe000"},"size":{"bytes":20480,"kilobytes":20,"megabytes":0.01953125}}},{"label":"otadata","type":{"code":1,"description":"Data"},"subtype":{"code":0,"description":"OTA selection partition"},"mem":{"offset":{"dec":57344,"hex":"0xe000"},"end_at":{"dec":65536,"hex":"0x10000"},"size":{"bytes":8192,"kilobytes":8,"megabytes":0.0078125}}},{"label":"app0","type":{"code":0,"description":"Application"},"subtype":{"code":16,"description":"OTA partition 0"},"mem":{"offset":{"dec":65536,"hex":"0x10000"},"end_at":{"dec":1376256,"hex":"0x150000"},"size":{"bytes":1310720,"kilobytes":1280,"megabytes":1.25}}},{"label":"app1","type":{"code":0,"description":"Application"},"subtype":{"code":17,"description":"OTA partition 1"},"mem":{"offset":{"dec":1376256,"hex":"0x150000"},"end_at":{"dec":2686976,"hex":"0x290000"},"size":{"bytes":1310720,"kilobytes":1280,"megabytes":1.25}}},{"label":"spiffs","type":{"code":1,"description":"Data"},"subtype":{"code":130,"description":"SPIFFS partition"},"mem":{"offset":{"dec":2686976,"hex":"0x290000"},"end_at":{"dec":4128768,"hex":"0x3f0000"},"size":{"bytes":1441792,"kilobytes":1408,"megabytes":1.375}}},{"label":"coredump","type":{"code":1,"description":"Data"},"subtype":{"code":3,"description":"COREDUMP partition"},"mem":{"offset":{"dec":4128768,"hex":"0x3f0000"},"end_at":{"dec":4194304,"hex":"0x400000"},"size":{"bytes":65536,"kilobytes":64,"megabytes":0.0625}}}]}
