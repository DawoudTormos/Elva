# Elva 🚪🔋

## IoT Access Control Project with Energy Metering

### Overview

Elva is an **IoT-based access control system** for elevators, utilizing **wireless key fobs** for user authentication and tracking **energy usage per user**. The system also provides an admin panel for efficient management.

Elva is built on the powerful combination of:

-   **ESP32**
-   **ATmega328P** (with Arduino Bootloader)

The system interfaces with the following components:

-   **RTC Module**
-   **SD Card**
-   **Current Transformers**
-   **Differential analogue measurement circuit for AC**
-   **Solid State Relays (SSR)**
-   Additional circuits like a **voltage divider** (from 5V to 3.3V) and more.

----------

## ✨ Key Features

-   **🚪 Access Control:**
    
    -   Secure authentication using wireless key fobs.
-   **🔋 Energy Monitoring:**
    
    -   Tracks energy consumption per user for accountability.
-   **📋 Admin Panel:**
    
    -   Manage users, monitor energy consumption, and control the system settings.
-   **📦 Modular Components:**
    
    -   Easily adaptable for hardware setups using PCBs or breadboards.

----------

## 🛠️ Tech Stack

-   **Hardware:**
    -   ESP32 for communication and control.
    -   ATmega328P for additional processing.
-   **Components:**
    -   RTC Module for timekeeping.
    -   SD Card for data logging.
    -   Current Transformers and AC measurement circuits for energy tracking.

----------

## 🚀 How to Set Up

### Requirements:

-   ESP32 and ATmega328P microcontrollers.
-   RTC Module, SD Card, Current Transformers, SSR, and supporting circuits.
-   Circuit board (PCB) or breadboard setup for assembly.

### Notes:

-   The provided code covers the **ESP32 only**.
-   Additional components and setup steps are required for full functionality.
-   Integration with the **elevator electrical system** is necessary for measurement and control.

### Steps:

1.  Assemble the hardware components:
    -   Follow the provided circuit designs (to be added in future updates).
2.  Program the ESP32:
    
    ```bash
    Upload the ESP32 code using your preferred Arduino IDE, PlatformIO or ESP32 toolchain.
    ```
3.  Program the ATmega328P :
    
	-	Upload the code from my repo [PowerMeterSerial3](https://github.com/DawoudTormos/PowerMeterSerial3) using your preferred Arduino IDE, PlatformIO or ESP32 toolchain.

4.  Write web files and db file to SD card:
    
	-	Contact me for these files and to help u with configuring everything

5.  Connect the system to the elevator:
    -   Ensure proper wiring with the electrical system.
6.  Test the setup:
    -   Verify communication between the ESP32, key fobs, and energy measurement components.

----------

## Future Updates 🛠️

This project is still evolving. Upcoming updates will include:

-   Circuit diagrams for assembly.
-   Complete setup instructions.
-   Links to repositories for all system components.

----------

## 📝 License

This project is open-source and available under the [MIT License]().

----------

## 💡 About

Elva is an ambitious IoT project that combines access control with energy metering. It reflects my dedication to merging hardware and software to create practical solutions.

Feel free to reach out for contributions, suggestions, or collaboration opportunities!

----------

## 🌟 Contributing

Pull requests are welcome! For major changes, please open an issue first to discuss what you would like to change.

### Steps to Contribute:

1.  Fork the repository.
2.  Create your feature branch:
    
    ```bash
    git checkout -b feature/new-feature
    
    ```
    
3.  Commit your changes:
    
    ```bash
    git commit -m 'Add some feature'
    
    ```
    
4.  Push to the branch:
    
    ```bash
    git push origin feature/new-feature
    
    ```
    
5.  Open a pull request.

----------

Thank you for checking out Elva! 🚀
