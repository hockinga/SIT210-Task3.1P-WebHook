// Imports
#include "Adafruit_DHT.h"

// Constants
const int TEMP_PIN = D2;      // Pin connected to the temp sensor
const int LED_BUILTIN = D7;   // Pin connected to the builtin LED
const int DELAY_TIME = 35000; // Time between each temp reading (millis)

// Initialise temp sensor
DHT dht(TEMP_PIN, DHT22);


/**
 * Start the temp sensor and initialise the data variable
 */
void setup() {

    // Setup LEDs
    pinMode(D7, OUTPUT);

    // Start the temp sensor
    dht.begin();
}


/**
 * Returns the temp from the sensor as a string
 *
 * @return temp as a string
 */
String read_temp() {

    // Read temp
    float temp = dht.getTempCelcius();

    // Convert to string and return
    if (isnan(temp)) {
        // Failed to read temp
        return String("E");
    } else {
        return String(temp);
    }
}


/**
 * Blinks an LED
 *
 * @param led the led to blink
 */
void blink(int led) {
    digitalWrite(led, HIGH);
    delay(1000);
    digitalWrite(led, LOW);
}


/**
 * Posts temp data to the server
 */
void post_temp(String temp) {

    // Post temp
    Particle.publish("webhooksTemp", "{\"field1\":\"" + temp + "\"}", PRIVATE);

    // Inform via LED
    blink(LED_BUILTIN);
}


/**
 * Repeatedly read temp data and post it to the server.
 */
void loop() {

    // Wait before each reading
    delay(DELAY_TIME);

    // Read temp
    String temp = read_temp();

    // Send temp to server
    post_temp(temp);
}