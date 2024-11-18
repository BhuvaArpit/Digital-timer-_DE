#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3
#define RESTART_BUTTON_PIN 4    // Pin for the restart button
#define PAUSE_BUTTON_PIN 5      // Pin for the pause button
#define INCREMENT_BUTTON_PIN 6  // Pin for the increment button
#define DECREMENT_BUTTON_PIN 7  // Pin for the decrement button
#define BUZZER_PIN 8            // Pin for the buzzer

TM1637Display display(CLK, DIO);

void setup() {
  // Initialize the display
  display.setBrightness(0x0f); // Set brightness to maximum
  display.clear(); // Clear the display
  
  pinMode(RESTART_BUTTON_PIN, INPUT_PULLUP);   // Set the restart button pin as input with internal pull-up resistor
  pinMode(PAUSE_BUTTON_PIN, INPUT_PULLUP);     // Set the pause button pin as input with internal pull-up resistor
  pinMode(INCREMENT_BUTTON_PIN, INPUT_PULLUP); // Set the increment button pin as input with internal pull-up resistor
  pinMode(DECREMENT_BUTTON_PIN, INPUT_PULLUP); // Set the decrement button pin as input with internal pull-up resistor
  pinMode(BUZZER_PIN, OUTPUT);                 // Set the buzzer pin as output
}
void loop() {
  int countdown = 10; // Initial countdown value
  
  while (countdown >= 0) {
    // Display the remaining time on the 4-digit 7-segment display
    display.showNumberDec(countdown, true);
    
    // Delay for 1 second
    delay(1000);
    
    // Check if the restart button is pressed
    if (digitalRead(RESTART_BUTTON_PIN) == LOW) {
      // If the restart button is pressed, restart the countdown
      countdown = 10;
    }
    
    // Check if the pause button is pressed
    if (digitalRead(PAUSE_BUTTON_PIN) == LOW) {
      // If the pause button is pressed, pause the countdown
      while (digitalRead(PAUSE_BUTTON_PIN) == LOW) {
        // Wait for the button to be released
        delay(10);
      }
    } else {
      // If the pause button is not pressed, decrement the countdown
      countdown--;
    }

    // Check if the increment button is pressed
    if (digitalRead(INCREMENT_BUTTON_PIN) == LOW) {
      // If the increment button is pressed, increase the countdown by 10 seconds
      countdown += 10;
      
      // Wait for the button to be released
      while (digitalRead(INCREMENT_BUTTON_PIN) == LOW) {
        delay(10);
      }
    }
    
    // Check if the decrement button is pressed
    if (digitalRead(DECREMENT_BUTTON_PIN) == LOW) {
      // If the decrement button is pressed, decrease the countdown by 10 seconds
      countdown -= 10;
      
      // Wait for the button to be released
      while (digitalRead(DECREMENT_BUTTON_PIN) == LOW) {
        delay(10);
      }
    }
    
    // Ensure countdown doesn't go below 0
    if (countdown < 0) {
      countdown = 0;
      display.showNumberDec(countdown, true);
      break;
    }
  }
  
  // Timer is over, ring the buzzer
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000); // Buzzer duration
  digitalWrite(BUZZER_PIN, LOW);
  
  // Wait until restart button is pressed to continue
  while (digitalRead(RESTART_BUTTON_PIN) == HIGH) {
    delay(10);
  }
}