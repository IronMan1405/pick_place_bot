# **Pick N Place Bot**

## Team
Raghav P S - Mechanical Desig, Integration & Testing  
Dakshesh Nankani - Electronics, Power, Control & Programming

---

## 1. **Abstract**

This project presents the design and implementation of a manually controlled pick-and-place robot capable of operating within a constrained arena under strict dimensional, power, and time limitations. The robot uses a four-wheel differential-drive chassis along with a custom servo-actuated arm and gripper mechanism to pick and place thermocol blocks into designated zones.  

An ESP32 microcontroller processes RF remote-control inputs to coordinate locomotion and object manipulation in real time. Major emphasis was placed on mechanical stability, reliable power distribution under simultaneous motor and servo loads, and predictable low-latency control response.  

The final system successfully integrated mechanical, electronic, and control subsystems into a robust mobile platform capable of performing the assigned tasks within the specified runtime constraints.

---

## 2. **Problem Statement**

The objective of this project was to design a remote controlled robot and maneuver the bot through the arena while performing the given tasks of picking and placing objects in the designated locations.  

The system was required to comply with the following constraints:

- Strict dimensional limits at the start of the run  
- Maximum operating voltage of **15 V DC**  
- Single-operator manual control using wired or wireless communication  
- No use of ready-made gripping mechanisms  
- Completion of all tasks within **2 minutes 30 seconds**

The key engineering challenge was to develop a compact and reliable robot capable of stable motion, real-time responsiveness, and consistent object manipulation under simultaneous motor and servo loading.

---

## 3. **Objectives**

- To design a compact mobile robot compliant with the competition size and power constraints.  
- To implement a reliable manual control system with predictable and low-latency response.  
- To develop a custom servo-based pick-and-place mechanism capable of handling thermocol blocks.  
- To achieve stable differential drive motion for navigating the arena and obstacles.  
- To design a power distribution system that ensures stable operation under combined motor and servo loads.  
- To integrate all subsystems into a robust platform operable by a single user within the given time limit.

---

## 4. **System Overview**

The robot consists of a four wheeled chassis with DC geared motors and two servo motors for the arm and its gripper, controlled by an ESP32 based system. The user controls the robot using an RF remote transmitter, and the microcontroller processes the control signals to drive the robot and the arm.   
The system can be divided into mechanical, electronic, and control subsystems, with the control logic forming the core of system coordination.  
   
---

## 5. **Mechanical Design**

> Why this chassis design?

- The chassis is a flat, rectangular, four-wheel platform chosen for      simplicity, stability.

- Four-wheel configuration provides better static stability compared to two or three wheels, which is critical when an arm is mounted on top.

- The wide wheelbase increases the support while reducing the risk of tipping during arm motion and lifting.

- A flat plate chassis allows easy mounting of electronics, battery, and actuators while keeping the mass low.

> Why this arm and gripper design/layout?

- The arm is front-mounted, which allows direct access to objects without requiring complex chassis movement.

- The single-link arm with a servo-driven joint reduces mechanical complexity while still enabling lifting and placing blocks.

- The gripper is a parallel jaw type, providing uniform contact and better grip on cube shaped obstacles that was required to be maneuvered around.

> How was stability(COM) ensured during lifting?

- Heavy components such as battery, motors, and control electronics are placed low and centrally on the chassis to keep the center of mass close to the ground.

- The arm is mounted near the front axle, so the lifting moment is countered by the rear wheels.

---

## 6. **Electronics & Hardware**

### 1. **Microcontroller**

An ESP32 Devkit v1 was used as the onboard microcontroller for this robot.

### 2. **Motor Driver**

A pair of L298N motor drivers were used. each L298N controlled the motors on one side, enabling differential drive.

### 3. **Actuators**

Four Johnson Geared DC Motors were used, each for one wheel. These motors were chosen specifically as they could provide high torque and speeds of up to 600rpm rated at 12V.  
Two MG996R servo motors were used for the arm, one at the base of the arm to rotate it up and down and one for the opening and closing the gripper/claw.   
MG996R servo motors were chosen specifically as they can provide high torque (stall torque = 921 N-m @ 4.8V)

### 4. **Power System**

A 3S Li-Po Battery of 1500mAh rating was used to power the entire robot.   
Two LM2596 buck converters were used to supply 5V power to servo motors and the microcontroller. These were connected parallelly to the battery.  
Separate buck converters were used to isolate servo load fluctuations from the microcontroller supply.

---

## 7. **Software & Control Logic**

### 1. **Programming Environment**

Arduino IDE & PlatformIO

### 2. **Control Strategy**

The Robot is controlled using a Radiofrequency Transmitter, with the microcontroller reading PWM signals from the receiver using pulseIn() function. These signals are mapped to motor speed, direction, and servo angles.  
The control signals were continuous signals, allowing smoother motion of the bot.

### 3. **Key Algorithms**

Signal mixing is used to give the differential drive output for the wheels. And it is efficient as multiple channels are used to control the motors.

---

## 8. **Challenges Faced**

- **Power management:** Early designs caused controller resets due to voltage drops during high-current servo motion.  
- **Gripper reliability:** Thermocol blocks were difficult to grip due to low friction and compressibility.  
- **Traction limitations:** Off-the-shelf wheels lacked sufficient grip on inclined or uneven surfaces.  
- **Mechanical tuning:** Arm geometry, servo limits, and weight distribution required repeated refinement.  
- **System integration:** Simultaneous debugging of wiring, mechanics, and control logic was time-intensive.  

---

## 9. **Conclusion**

The robot was successfully designed and integrated to satisfy the core mechanical, electrical, and control constraints of the project. However, performance during final demonstration did not fully meet expectations. Instabilities caused by power delivery under high servo loads, limited wheel traction, and insufficient final-stage mechanical tuning affected operational consistency.  

These outcomes highlighted the importance of extensive full-system testing under realistic operating conditions. While subsystem-level functionality was achieved, reliable real-world performance required deeper iteration and validation.  

Despite the final shortcomings, the project provided valuable hands-on learning in robotics system design, power electronics, actuator integration, and real-time control. The lessons gained form a strong foundation for future iterations with improved robustness, reliability, and task efficiency.
