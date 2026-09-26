#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

// Pin Definitions
#define TRIG1 PD2
#define ECHO1 PD3
#define TRIG2 PD4
#define ECHO2 PD5
#define FEEDBACK PB0

// Constants
#define THRESHOLD_DISTANCE 20  // Distance in cm
#define SWIPE_TIME 500         // Max time for swipe (ms)

// Variables
volatile unsigned long timerCount = 0;
unsigned long lastGestureTime = 0;
int gestureState = 0;  // 0: No gesture, 1: Play/Pause, 2: Next, 3: Previous

// Initialize Timer1 for microsecond timing
void timer1_init() {
    TCCR1B |= (1 << CS11); // Timer1 prescaler: 8
    TCNT1 = 0;             // Reset counter
}

// Read the time in microseconds
unsigned long getMicros() {
    return (TCNT1 * 0.5); // Convert to microseconds
}

// Reset the Timer1 counter
void resetTimer() {
    TCNT1 = 0;
}

// Measure distance using ultrasonic sensor
int measureDistance(uint8_t trigPin, uint8_t echoPin) {
    unsigned long duration;
    int distance;

    // Trigger a 10 microsecond pulse
    PORTD &= ~(1 << trigPin);
    _delay_us(2);
    PORTD |= (1 << trigPin);
    _delay_us(10);
    PORTD &= ~(1 << trigPin);

    // Wait for echo
    while (!(PIND & (1 << echoPin)));  // Wait for HIGH
    resetTimer();

    while (PIND & (1 << echoPin));    // Wait for LOW
    duration = getMicros();

    // Calculate distance in cm
    distance = duration * 0.034 / 2;
    return distance;
}

// Gesture detection logic
void detectGesture(int dist1, int dist2) {
    static unsigned long gestureStartTime = 0;
    static int swipeDirection = 0; // 1: Right-to-Left, 2: Left-to-Right

    if (dist1 < THRESHOLD_DISTANCE && dist2 > THRESHOLD_DISTANCE) {
        // Hand near Sensor 1 only
        if (timerCount - gestureStartTime > SWIPE_TIME) {
            gestureState = 1; // Play/Pause
            gestureStartTime = timerCount;
        }
    } else if (dist1 < THRESHOLD_DISTANCE && dist2 < THRESHOLD_DISTANCE) {
        // Swipe gesture detected
        if (swipeDirection == 0) {
            gestureStartTime = timerCount;
        }
        if (timerCount - gestureStartTime < SWIPE_TIME) {
            if (dist1 < dist2) {
                swipeDirection = 1; // Right-to-Left
            } else {
                swipeDirection = 2; // Left-to-Right
            }
        } else {
            if (swipeDirection == 1) {
                gestureState = 2; // Next
            } else if (swipeDirection == 2) {
                gestureState = 3; // Previous
            }
            swipeDirection = 0;
        }
    }
}

// Execute gesture actions
void executeGestureAction() {
    switch (gestureState) {
        case 1:
            // Play/Pause
            PORTB ^= (1 << FEEDBACK); // Toggle feedback LED
            break;
        case 2:
            // Next Track
            PORTB |= (1 << FEEDBACK);
            _delay_ms(200);
            PORTB &= ~(1 << FEEDBACK);
            break;
        case 3:
            // Previous Track
            PORTB |= (1 << FEEDBACK);
            _delay_ms(200);
            PORTB &= ~(1 << FEEDBACK);
            break;
        default:
            break;
    }
    gestureState = 0;
}

void setup() {
    // Configure pins
    DDRD |= (1 << TRIG1) | (1 << TRIG2);  // TRIG pins as output
    DDRD &= ~((1 << ECHO1) | (1 << ECHO2)); // ECHO pins as input
    DDRB |= (1 << FEEDBACK); // Feedback pin as output

    // Initialize timer
    timer1_init();
}

void loop() {
    int dist1 = measureDistance(TRIG1, ECHO1);
    int dist2 = measureDistance(TRIG2, ECHO2);

    detectGesture(dist1, dist2);
    executeGestureAction();

    _delay_ms(100);
}

int main() {
    setup();
    while (1) {
        loop();
    }
}
