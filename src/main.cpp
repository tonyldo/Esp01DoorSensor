#include <Arduino.h>

int holdPin = 0;   // defines GPIO 0 as the hold pin (will hold CH_PD high untill we power down).
int switchPin = 2; // defines GPIO 2 as the Switch read pin (reads the state of the Switch output).
int control = 1;   // sets the control to 1 (it must have been we woke up).

void setup()
{
  pinMode(holdPin, OUTPUT);    // sets GPIO 0 to output
  digitalWrite(holdPin, HIGH); // sets GPIO 0 to high (this holds CH_PD high when the switch is close).

  pinMode(switchPin, INPUT); // sets GPIO 2 to an input so we can read the switch output state
}

void loop()
{
  if ((control) == 0)
  { // if (pir) == 0, which its not first time through as we set it to "1" above
    // send to mqtt close msg
    delay(1000);                // wait for client to close
    digitalWrite(holdPin, LOW); // set GPIO 0 low this takes CH_PD & powers down the ESP
  }
  else
  { // if (control) == 0 is not true
    // keep send to mqtt open msg
    delay(500);
    if (digitalRead(switchPin) != 1)
    {
      control = 0; // set control to false. On the next interation will be sending de close msg.
    }
  }
}