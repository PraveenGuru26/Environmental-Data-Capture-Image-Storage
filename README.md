# Environmental-Data-Capture

## Description
This project aims to create a secure and scalable solution for recording and storing clinical data, including pressure, humidity, and temperature readings, along with images captured by an ESP32-CAM module. The data is logged into Google Sheets, and the captured images are uploaded to a Google Drive folder. This system leverages Arduino code to interface with sensors and the ESP32-CAM, providing a robust platform for clinical data management.

## Table of Contents
- [Installation](#installation)
- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Usage](#usage)
- [Features](#features)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)

## Hardware Requirements
- *ESP32-CAM Module*: For capturing images.
- *DHT11 Sensor*: For measuring humidity and temperature.
- *HX710B Pressure Sensor*: For measuring pressure.
- *Customized PCB Board and Jumper Wires*: For connecting components.
- *Power Supply*: Suitable for the ESP32-CAM and sensors.

## Software Requirements
- *Arduino IDE*: For writing and uploading the code to the ESP32-CAM module.
- *Google Sheets API*: For logging sensor data.
- *Google Drive API*: For uploading captured images.
- *Libraries*:
  - DHT.h for DHT11 sensor
  - WiFi.h for ESP32 Wi-Fi connectivity
  - ESP_Google_Sheet_Client.h for Google Sheet Data Logging
  - SD_MMC.h for Storing Credentials in SD Card
  - esp_camera.h for activating camera pins

## Installation

### Arduino IDE Setup
1. *Install ESP32 Board*:
   - Open Arduino IDE and go to *File* > *Preferences*.
   - In the "Additional Boards Manager URLs" field, add the following URL:
     
     https://dl.espressif.com/dl/package_esp32_index.json
     
   - Go to *Tools* > *Board* > *Boards Manager* and install the *ESP32* package.

2. *Install Required Libraries*:
   - Install the required libraries from *Sketch* > *Include Library* > *Manage Libraries...* and search for the above-mentioned libraries.

3. *Google Sheets and Drive API Setup*:
   - Enable the Google Sheets API and Google Drive API in the Google Cloud Console.
   - Create credentials and download the credentials.json file.
   - Follow the steps provided by Google to set up OAuth2.0.

### Circuit Setup
1. *ESP32-CAM*: Connect the camera module as per the datasheet instructions.
2. *DHT11 Sensor*: Connect the sensor to the ESP32 following the pinout:
   - VCC to 3.3V
   - GND to GND
   - Data pin to a GPIO pin (e.g., GPIO 2)
3. *HX710B Pressure Sensor*: Connect the sensor as per its datasheet.
   - SCK to a GPIO pin (e.g., GPIO 12)
   - DOUT to a GPIO pin (e.g., GPIO 13)

## Usage

1. *Upload the Code*:
   - Open the Arduino IDE.
   - Load the provided .ino file.
   - Update the Wi-Fi credentials, Google Sheets, and Google Drive settings in the code.
   - Compile and upload the code to the ESP32-CAM.

2. *Run the System*:
   - Power the ESP32-CAM module.
   - The system will start capturing temperature, humidity, and pressure data and log them into the connected Google Sheet.
   - Images captured by the ESP32-CAM will be uploaded to the specified Google Drive folder.

3. *Monitor Data*:
   - View real-time sensor data in Google Sheets.
   - Access captured images from Google Drive.

## Features
- *Real-time Data Logging*: Records temperature, humidity, and pressure data into Google Sheets.
- *Image Capture and Storage*: Captures images using ESP32-CAM and uploads them to Google Drive.
- *Secure and Scalable*: Uses Google’s APIs for secure data storage and management.
- *Simple Integration*: Easy to set up and integrate into existing systems.

## Contributing
Contributions are welcome! If you would like to contribute, please follow the standard [GitHub workflow](https://guides.github.com/introduction/flow/). You can open an issue or submit a pull request with your proposed changes.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contact
For any inquiries, please reach out to me at [email@example.com](mailto:email@example.com).

---

This README provides a clear and structured overview of your project, making it easier for others to understand, install, and contribute to your project.
