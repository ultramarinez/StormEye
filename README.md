# StormEye

**StormEye** focuses on disrupting Bluetooth connections using an ESP32 and nRF24 modules, generating significant noise.

# Hardware

### Required:
- **ESP32 Dev Module** (such as ESP32-WROOM-32U or any dev board with the needed pins)
- **nRF24L01+PA+LNA modules** (2x)
- **10µF Capacitor** (2x) (any voltage above 5V)
- **Prototype PCB**

### Additional (for battery modification):
- **3.7V Li-Ion Battery**
- **TP4056 Charging Module** (Micro-USB/Type-C)
- **Mini Slide Switch**
- **DC-DC Boost Step-Up Converter (5V)**

## Flashing

1. Visit the [Web Flasher](https://n0tav1ru5.github.io/StormEye/flash.html)
2. Connect your ESP32 via a data USB cable
3. Connect to your ESP32 and install


# ESP32-nRF24L01+ Pinout & Battery Modification

### HSPI Connections

| 1st nRF24L01 Module Pin | HSPI Pin (ESP32) | 10µF Capacitor |
| ----------------------- | ---------------- | -------------- |
| VCC                     | 3.3V             | (+) capacitor  |
| GND                     | GND              | (−) capacitor  |
| CE                      | GPIO 16          |                |
| CSN                     | GPIO 15          |                |
| SCK                     | GPIO 14          |                |
| MOSI                    | GPIO 13          |                |
| MISO                    | GPIO 12          |                |
| IRQ                     |                  |                |

### VSPI Connections

| 2nd nRF24L01 Module Pin | VSPI Pin (ESP32) | 10µF Capacitor |
| ----------------------- | ---------------- | -------------- |
| VCC                     | 3.3V             | (+) capacitor  |
| GND                     | GND              | (−) capacitor  |
| CE                      | GPIO 22          |                |
| CSN                     | GPIO 21          |                |
| SCK                     | GPIO 18          |                |
| MOSI                    | GPIO 23          |                |
| MISO                    | GPIO 19          |                |
| IRQ                     |                  |                |

---

### Notes:
- Ensure that the **10µF capacitors** are connected between the VCC and GND pins of each nRF24L01 module to stabilize the power supply.
- The **IRQ** pins are left unconnected in this configuration. If needed, you can connect them to an appropriate GPIO pin for interrupt handling.

### Battery Modification Connections

| 3.7V Li-Ion Battery | TP4056 Charging Module | Mini Slide Switch | Boost Module | ESP32 |
| ------------------- | ---------------------- | ----------------- | ------------ | ----- |
| Bat+                | B+                     |                   |              |       |
| Bat-                | B-                     |                   |              |       |
|                     | OUT+                   | Switch In         |              |       |
|                     | OUT-                   |                   | IN-          |       |
|                     |                        | Switch Out        | IN+          |       |
|                     |                        |                   | OUT+         | 5V    |
|                     |                        |                   | OUT-         | GND   |

## DISCLAIMER

The use of this tool is strictly at your own risk. It is designed for educational and experimental purposes only. Engaging in activities that disrupt or interfere with wireless communications, including jamming, is illegal in many jurisdictions and may result in severe penalties.

By using this tool, you acknowledge that you understand the legal implications and potential consequences of your actions. The developers and contributors to this project are not responsible for any misuse or unlawful activities that may arise from its use.

**Proceed with caution and responsibility!**
