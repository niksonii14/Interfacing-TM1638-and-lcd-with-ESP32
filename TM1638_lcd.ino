#include <TM1638plus.h> // Include TM1638plus library
#include <LiquidCrystal.h> // Include LiquidCrystal library

// Define ESP32 GPIO pins connected to TM1638
#define STB 27    // Strobe Pin
#define CLK 26    // Clock Pin
#define DIO 25    // Data I/O Pin

// Instantiate TM1638plus object
TM1638plus module(STB, CLK, DIO);

// Initialize the LiquidCrystal object with the pins connected to the LCD
LiquidCrystal lcd(5, 23, 18, 13, 22, 15);

uint8_t lastButtons = 0; // Store the last button state for debouncing

void setup() {
  Serial.begin(115200);
  Serial.println("TM1638plus and LCD Test with ESP32");

  // Initialize TM1638 module
  module.displayBegin(); // Initialize display
  module.reset();        // Clear display

  // Initialize LCD
  lcd.begin(20, 4);      // Set up the LCD with 20 columns and 4 rows
  lcd.setCursor(0, 0);
  lcd.print("TM1638 & LCD"); // Display a message on the LCD
  lcd.setCursor(0, 1);
  lcd.print("Demo Start");
}

void loop() {
  // Poll buttons from TM1638 module
  uint8_t buttons = module.readButtons();

  // Check if a new button press occurred
  if (buttons != 0 && buttons != lastButtons) {
    // Find the button number pressed
    int buttonNumber = -1; // Default: no button
    for (int i = 0; i < 8; i++) {
      if (buttons & (1 << i)) {
        buttonNumber = i + 1; // Buttons are 1-indexed
        break;
      }
    }

    // Clear LCD and display button information
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Button Pressed:");
    lcd.setCursor(0, 1);
    lcd.print("Btn #: ");
    lcd.print(buttonNumber);

    // Print to Serial Monitor
    Serial.print("Button Pressed: ");
    Serial.println(buttonNumber);

    // Update last button state
    lastButtons = buttons;
  }

  // If no buttons are pressed, reset lastButtons to avoid repeated detection
  if (buttons == 0) {
    lastButtons = 0;
  }

  // delay(100); // Small delay for debouncing
}
