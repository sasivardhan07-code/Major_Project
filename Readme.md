[README.md](https://github.com/user-attachments/files/30650252/README.md)
# 🚗 Real Time Vehicle Status Monitoring Using CAN

**Project Description:**

This project uses the CAN protocol to connect three LPC2129-based nodes—Main, Indicator, and Fuel—for real-time vehicle monitoring. The Main Node detects accidents via accelerometer data to trigger airbag deployment and displays fuel level and status on an LCD. The Indicator Node controls scrolling LED turn signals based on commands from the Main Node. The Fuel Node reads fuel gauge data via ADC and sends it to the Main Node over CAN.


# 🎯 Aim
To Design and implement a real-time vehicle monitoring system using CAN protocol that displays important vehicle parameters such as:

* Fuel percentage
* Indicators status
* Airbag activation

# ⚙️System Architecture
![4](https://github.com/user-attachments/assets/60751582-ad98-49fa-97f6-3f325de11b43)



# 🧠Project Nodes
1️⃣ Main (Dashboard) Nodes
This is the central node responsible for displaying vehicle status.

Functions:

 * Displays fuel percentage on LCD
 * Displays airbag status
 * Sends indicator signals to indicator node
 * Receives fuel information from fuel node
 * Reads accelerometer data for accident detection

 2️⃣ Fuel Node
 Responsible for fuel monitoring.

 Functions:

 * Reads fuel sensor using ADC
 * Converts ADC value into fuel percentage
 * Sends fuel information to main node through CAN


 3️⃣  Indicator Node
 Responsible for vehicle indicators 

 Functions:

 * Receives CAN messages from main node
 * Controls left and right LED indicators

# 📦 Hardware Requirements

| Component | Description |
|-----------|-------------|
| 🧠 **LPC2129 Microcontroller** | Main controller |
| 🚌 **MCP2551** | CAN transceiver |
| 🖥️ **LCD (20×4)** | Display dashboard |
| 📈 **MMA7660** | Accelerometer sensor |
| 💡 **LEDs** | Indicator simulation |
| 🔘 **Push Buttons** | Indicator switches |
| ⛽ **Fuel Gauge / Potentiometer** | Fuel input simulation |
| 🔌 **USB-UART Converter** | Programming interface |

	
	
	

# 💻 Software Requirements
* Embedded C
* Keil µVision IDE
* Flash Magic
* CAN communication libraries
# 🧩Project Modules

🖥️ LCD Module

Displays:

* Fuel percentage
* Indicator status
* Airbag status
* Dashboard information
# 📈ADC Module
Reads fuel sensor value and converts it into fuel percentage
# 🚘CAN Module
Handles communication between nodes.

Operations:

* Transmit data
* Receeive data
* Frame formatting
# 🚨Interrupt Module
Handles external interrupts for:

* Left indicator
* Right indicator
# 📄I2C Module
Used for communication with the MMA7660 accelerometer sensor.
# ⛓️‍💥 Accelerometer Module
Reads X,Y,Z acceleration values and detects accidents.

if acceleration exceeds threshold ->Airbag is triggered.
# 📡 CAN Message Format

| CAN ID | Data | Description |
|:------:|------|-------------|
| **0x01** | Fuel Percentage | ⛽ Sent from Fuel Node |
| **0x02** | Left Indicator | ⬅️ Activates the left turn indicator |
| **0x03** | Right Indicator | ➡️ Activates the right turn indicator |
# 🔄 Project Workflow

1️⃣ Fuel node reads fuel value using ADC.

2️⃣ Fuel percentage is calculated.

3️⃣ Fuel data is transmitted to main node using CAN.

4️⃣ Main node receives fuel data and displays it on LCD.

5️⃣ External interrupt detects indicator button press.

6️⃣ Indicator command is sent to indicator node via CAN.

7️⃣ Indicator node receives command and activates LEDs.

8️⃣ Accelerometer detects sudden movement.

9️⃣ If crash detected -> airbag status is displayed.

# 📸 Output
The LCD dashboard displays:

```text
------ DASHBOARD ------

Fuel            : ███ 49%
Airbag Status   : OFF
Indicator       : ← →
```
# 🔌Overall Hardware Connections

![1](https://github.com/user-attachments/assets/72863127-2033-44eb-8d75-f29d6e7f645b)

# 💚When No Accident Occurs
![2](https://github.com/user-attachments/assets/07c0550f-b41c-48b8-a18d-1776196d4743)

# 💥When Accident Occurs

![3](https://github.com/user-attachments/assets/bf786bd0-c27a-45fe-be87-34b9ae20f3b1)
 
 
 # ✨Features

 ✔ Real-time vehicle monitoring

 ✔ CAN-based distributed architecture

✔ Fuel level monitoring

 ✔ Indicator control system

✔ Airbag accident detection

 ✔ LCD dashboard display

# 📱 Applications
* Automotive monitoring systems
* Vehicle dashboard systems
* Safety Systems in vehicles
* CAN-based embedded systems
# 🔮Future Enhancements
* Add GPS for real-time vehicle tracking
* Integrate GSM module for accident alerts 
* Monitor additional parameters (temperature,tire pressure,battery)
* Develop mobile/web dashboard for remote monitoring
* Implement cloud or SD card data logging
# 🏁 Conclusion
This project demonstrates how CAN protocol enables reliable communication between multiple vehicle subsystems.

The system improves:
* Vehicle safety 
* Real-time Monitoring
* Efficient communication between nodes
# 👨‍💻 Author

**Sasi Vardhan Garlapati**  
Electronics and Communication Engineering (ECE)  
Developer of Real-Time Vehicle Status Monitoring Using CAN


# 📜 License

This project is developed for academic and learning purposes.
you are free to modify and enhance it with proper credt.

⭐ if you find this project useful,consider giving it a star on Github.



