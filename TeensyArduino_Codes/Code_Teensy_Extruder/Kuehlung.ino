
byte pwmKuehlungPin = 30;
byte fakeGroundPin = 31;

void KuehlungPWM_setup()
{
  pinMode(pwmKuehlungPin, OUTPUT); // Setzt den Pin als output

  // GND machen
  pinMode(fakeGroundPin, OUTPUT);
  digitalWrite(fakeGroundPin, LOW);
}

void KuehlungPWM()
{
  int PWMvalue = map(PwmValuePartCoolingFanMarlin, 0, 255, 255, 0); // PWM Wert umdrehen
  analogWrite(pwmKuehlungPin, PWMvalue);
  Serial.print("PWMvalue = "); Serial.println(PWMvalue);
}
