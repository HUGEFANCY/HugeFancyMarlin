


byte pwmPinKuehlung = 30;
Metro KuehlungUpdateIntervall = Metro(1000);

void KuehlungPWM_setup()
{
  pinMode(pwmPinKuehlung, OUTPUT); // Setzt den Pin als output.
}


void KuehlungPWM_loop()
{
  if (KuehlungUpdateIntervall.check() == 1)  // check if the metro has passed its interval
  {
    analogWrite(pwmPinKuehlung, PwmValuePartCoolingFanMarlin);
  }
}
