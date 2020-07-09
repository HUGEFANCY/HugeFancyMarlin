
byte pwmPinKuehlung = 30;
byte fakeGroundPin = 31;
Metro KuehlungUpdateIntervall = Metro(1000);

void KuehlungPWM_setup()
{
  pinMode(pwmPinKuehlung, OUTPUT); // Setzt den Pin als output.
  pinMode(fakeGroundPin, OUTPUT);
  digitalWrite(fakeGroundPin, LOW);
}

void KuehlungPWM_loop()
{
  if (KuehlungUpdateIntervall.check() == 1)  // check if the metro has passed its interval
  {
    int PWMvalue = map(PwmValuePartCoolingFanMarlin, 0, 255, 255, 0); // PWM Wert umdrehen
    analogWrite(pwmPinKuehlung, PWMvalue);
  }
}
