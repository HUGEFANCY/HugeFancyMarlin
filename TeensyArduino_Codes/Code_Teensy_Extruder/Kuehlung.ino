
byte pwmKuehlungPin = 30;

void KuehlungPWM_setup()
{
  pinMode(pwmKuehlungPin, OUTPUT); // Setzt den Pin als output
}

void KuehlungPWM()
{
  int PWMvalue = map(PwmValuePartCoolingFanMarlin, 0, 255, 255, 0); // PWM Wert umdrehen
  analogWrite(pwmKuehlungPin, PWMvalue);
  Serial.print("PWMvalue = "); Serial.println(PwmValuePartCoolingFanMarlin);
}
