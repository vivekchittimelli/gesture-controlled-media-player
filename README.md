# Gesture Controlled Media Player

An Arduino-based gesture-controlled media player that uses two ultrasonic sensors to detect hand movements and convert them into media control actions.

## Features

- Gesture-based media control
- Two ultrasonic sensors for hand-distance detection
- Play/Pause gesture detection
- Next-track gesture detection
- Previous-track gesture detection
- Distance-based gesture recognition
- Feedback output for detected actions
- Configurable gesture distance and timing thresholds

## Hardware

The source code uses:

- Microcontroller with AVR register support
- Two ultrasonic distance sensors
- Feedback LED/output

The exact board model is not specified in the source code itself.

## How It Works

The system continuously measures the distance between the user's hand and two ultrasonic sensors.

The program uses the measured distances and timing information to identify different hand gestures.

### Play/Pause

When a hand is detected close to Sensor 1 while Sensor 2 is outside the detection threshold, the system identifies the gesture as Play/Pause.

### Next Track

A right-to-left swipe across the two sensors is interpreted as a Next Track gesture.

### Previous Track

A left-to-right swipe across the sensors is interpreted as a Previous Track gesture.

## Gesture Detection

The default distance threshold in the source code is:

```text
20 cm
The maximum swipe detection time is:

500 ms
Feedback

The program uses a feedback output to indicate detected actions.

Play/Pause toggles the feedback output.
Next Track activates the feedback output briefly.
Previous Track activates the feedback output briefly.
Project Structure
gesture-controlled-media-player/
│
├── gesture_media_player.ino
└── README.md
Running the Project
Open gesture_media_player.ino in the Arduino IDE or a compatible AVR development environment.
Connect the required ultrasonic sensors and feedback output according to the pin definitions in the source code.
Select the appropriate compatible microcontroller/board.
Compile and upload the program.
Place your hand within the sensor detection area.
Perform the supported gestures.
Pin Configuration

The source code defines the following connections:

Function	Pin
Sensor 1 Trigger	PD2
Sensor 1 Echo	PD3
Sensor 2 Trigger	PD4
Sensor 2 Echo	PD5
Feedback Output	PB0
Technologies
C/C++
AVR register programming
Ultrasonic distance sensing
Embedded systems
Arduino development
Author

Chittimelli Vivek

Computer Science Engineering Student
Methodist College of Engineering and Technology, Hyderabad

GitHub: https://github.com/vivekchittimelli

LinkedIn: https://www.linkedin.com/in/vivek-chittimelli
