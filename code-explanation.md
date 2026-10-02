# Obstacle Avoidance Robot – Code Explanation

The `obstacle avoidance` program controls an autonomous robot using an ESP32, an HC-SR04 ultrasonic sensor, and an L298N motor driver. The main purpose of the program is to make the robot move forward when the path is clear and automatically change direction when an obstacle is detected within a certain distance.

The program starts by defining the GPIO pins used to control the two motors through the L298N motor driver. The left motor uses GPIO 25 as the enable pin (`ENA`), GPIO 26 as `IN1`, and GPIO 27 as `IN2`. The right motor uses GPIO 13 as the enable pin (`ENB`), GPIO 14 as `IN3`, and GPIO 12 as `IN4`. The enable pins are used for controlling motor speed using PWM, while the input pins control the direction of rotation.

The HC-SR04 ultrasonic sensor is connected using GPIO 33 as the trigger pin (`TRIG_PIN`) and GPIO 32 as the echo pin (`ECHO_PIN`). The trigger pin is used to send an ultrasonic pulse, while the echo pin receives the reflected signal from an obstacle.

The program also defines the motor speed and obstacle detection distance. `MOTOR_SPEED` is set to `170`, which determines the normal speed of the motors using the ESP32's PWM system. `TURN_SPEED` is set to `180`, which is used while the robot is turning. `OBSTACLE_DISTANCE` is set to `35` centimeters. This means that when an obstacle is detected within approximately 35 cm of the robot, the robot performs its obstacle-avoidance movement.

The program uses the ESP32 LEDC PWM system to control the motor speed. The enable pins of the L298N are attached to a PWM frequency of 1000 Hz with an 8-bit resolution. With 8-bit PWM, the duty-cycle value can range from 0 to 255. Therefore, a speed value such as 170 determines how much power is supplied to the motors.

The program contains separate functions for controlling the motors. The `leftMotorForward()` function sets the left motor direction pins so that the motor rotates in its forward direction and then applies the defined motor speed using PWM. Similarly, `rightMotorForward()` makes the right motor rotate forward.

The program also contains functions for reversing the motors. `leftMotorBackward()` changes the direction pins of the left motor so that it rotates in the opposite direction, while `rightMotorBackward()` does the same for the right motor.

A `stopMotors()` function is provided to stop the robot completely. It sets all motor direction pins to LOW and sets the PWM output of both enable pins to zero. This prevents the motors from continuing to rotate.

The program then combines these individual motor controls into complete robot movements. The `moveForward()` function makes both motors rotate forward at the normal motor speed. The `moveBackward()` function makes both motors rotate backward. A turning function is used to rotate the robot by driving the motors in opposite directions. In this project, the robot performs a right turn when an obstacle is detected.

The ultrasonic sensor is controlled using a distance-measuring function. First, the trigger pin is set LOW for a short period to ensure that the sensor starts from a known state. The trigger pin is then set HIGH for approximately 10 microseconds. This causes the HC-SR04 to transmit an ultrasonic pulse.

After the ultrasonic pulse is transmitted, the program uses `pulseIn()` on the echo pin to measure how long it takes for the reflected ultrasonic signal to return. The measured time represents the round-trip travel time of the ultrasonic wave.

The program converts this travel time into distance using the speed of sound. The calculation is based on the approximate relationship:

`Distance = Duration × 0.034 / 2`

The value `0.034` represents the approximate speed of sound in centimeters per microsecond. The result is divided by 2 because the ultrasonic wave travels from the sensor to the obstacle and then back to the sensor.

The program then compares the measured distance with the defined `OBSTACLE_DISTANCE` value of 35 cm.

If the measured distance is greater than 35 cm, the robot considers the path clear and calls the forward movement function. Both motors rotate forward and the robot continues moving.

If the measured distance is less than or equal to 35 cm, the robot considers an obstacle to be present. The program first stops the motors for approximately 300 milliseconds. This gives the robot time to stop before changing direction.

After stopping, the robot performs a right turn for approximately 500 milliseconds. During this movement, the motors rotate in opposite directions so that the robot changes its orientation. After the turn, the robot stops briefly for approximately 200 milliseconds before continuing with the next distance measurement.

The `loop()` function continuously repeats this process. The ultrasonic sensor measures the distance, the program checks whether an obstacle is present, and the robot either moves forward or performs the obstacle-avoidance movement.

The overall working sequence of the program is:

**Ultrasonic Sensor → Measure Distance → Compare With 35 cm → Path Clear → Move Forward**

or, when an obstacle is detected:

**Ultrasonic Sensor → Obstacle Within 35 cm → Stop → Turn Right → Stop Briefly → Measure Again**

The robot therefore does not require a human controller during normal operation. It continuously uses the HC-SR04 ultrasonic sensor to detect objects in front of it and automatically changes its movement when an obstacle is detected.

The motor driver acts as the interface between the ESP32 and the DC motors. The ESP32 generates the direction and PWM signals, while the L298N receives those signals and supplies the required motor control outputs.

The ESP32 is the main control unit of the robot. It reads the ultrasonic sensor, calculates the distance, decides what action should be taken, and sends the appropriate control signals to the L298N.

Overall, the project demonstrates basic autonomous navigation using an ESP32, ultrasonic distance sensing, PWM-based motor control, and an L298N motor driver. The robot continuously senses its environment and reacts to obstacles without requiring manual control.