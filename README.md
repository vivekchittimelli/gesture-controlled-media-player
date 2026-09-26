\# Gesture Controlled Media Player



An Arduino-based gesture-controlled media player that uses two ultrasonic sensors to detect hand movements and convert them into media control actions.



\## Features



\- Gesture-based media control

\- Two ultrasonic sensors for hand-distance detection

\- Play/Pause gesture detection

\- Next-track gesture detection

\- Previous-track gesture detection

\- Distance-based gesture recognition

\- Feedback output for detected actions

\- Configurable gesture distance and timing thresholds



\## Hardware



The source code uses:



\- Microcontroller with AVR register support

\- Two ultrasonic distance sensors

\- Feedback LED/output



The exact board model is not specified in the source code itself.



\## How It Works



The system continuously measures the distance between the user's hand and two ultrasonic sensors.



The program uses the measured distances and timing information to identify different hand gestures.



\### Play/Pause



When a hand is detected close to Sensor 1 while Sensor 2 is outside the detection threshold, the system identifies the gesture as Play/Pause.



\### Next Track



A right-to-left swipe across the two sensors is interpreted as a Next Track gesture.



\### Previous Track



A left-to-right swipe across the sensors is interpreted as a Previous Track gesture.



\## Gesture Detection



The default distance threshold in the source code is:



```text

20 cm

