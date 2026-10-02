# ESP32 Obstacle Avoiding Robot 🤖

An autonomous 2WD obstacle-avoiding robot built using an ESP32, L298N motor driver, and HC-SR04 ultrasonic sensor.

The robot continuously measures the distance between itself and nearby objects. When an obstacle is detected within a predefined distance, the robot stops and turns right to avoid it.

---

## 📌 Project Overview

This project demonstrates the basic principles of:

- Embedded systems
- Robotics
- Ultrasonic distance sensing
- Motor control
- PWM speed control
- Autonomous obstacle avoidance
- ESP32 programming

The robot is designed as a simple autonomous mobile robot that can detect obstacles in its path and change its direction without manual control.

---

## 🛠️ Components Used

| Component | Quantity |
|-----------|----------|
| ESP32 Development Board | 1 |
| L298N Motor Driver | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| DC Geared Motors | 2 |
| Robot Chassis | 1 |
| Wheels | 2 |
| Battery | 1 |
| Jumper Wires | As required |

---

## 🔌 Pin Connections

### L298N Motor Driver → ESP32

| L298N Pin | ESP32 GPIO |
|-----------|------------|
| ENA | GPIO 25 |
| IN1 | GPIO 26 |
| IN2 | GPIO 27 |
| ENB | GPIO 13 |
| IN3 | GPIO 14 |
| IN4 | GPIO 12 |
| GND | GND |

### HC-SR04 → ESP32

| HC-SR04 Pin | ESP32 |
|-------------|-------|
| TRIG | GPIO 33 |
| ECHO | GPIO 32 |
| VCC | 5V/VIN |
| GND | GND |

> ⚠️ **Important:** The HC-SR04 ECHO signal can be 5V, while ESP32 GPIO pins operate at 3.3V logic. A voltage divider or suitable level shifter should be used between ECHO and GPIO 32 for safe operation.

---

## ⚙️ How It Works

1. The HC-SR04 ultrasonic sensor sends an ultrasonic pulse.
2. The sensor receives the reflected echo from nearby objects.
3. The ESP32 calculates the distance using the echo time.
4. If the distance is greater than the obstacle threshold, the robot moves forward.
5. If an obstacle is detected within **35 cm**, the robot:
   - Stops
   - Waits briefly
   - Turns right
   - Stops again
   - Continues moving forward

### Obstacle Detection Logic

```text
Start
  ↓
Measure Distance
  ↓
Is obstacle within 35 cm?
  ↓
 ┌───────────────┐
 │               │
No              Yes
 │               │
 ↓               ↓
Move Forward    Stop
                 ↓
              Turn Right
                 ↓
                Stop
                 ↓
           Measure Again