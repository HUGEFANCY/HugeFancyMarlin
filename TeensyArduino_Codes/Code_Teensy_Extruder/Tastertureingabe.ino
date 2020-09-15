boolean SerialTastatur_CheckKeys()
{
  if (Serial.available())
  {
    char ch = Serial.read();

    if (ch == '1') // Tastaturanschlag "1"
    {
      Serial.println("Motor Links");
      Farbmischer_GibFarbe(1,0);
      //Schrittmotor_L(1, MotorSpeed, MotorAcceleration); // Umdrehungen, speed steps/s, acceleration mm/s^2
      return true;
    }

    if (ch == '2') // Tastaturanschlag "2"
    {
      Serial.println("Motor Rechts");
      Farbmischer_GibFarbe(0,1);
      //Schrittmotor_R(1, MotorSpeed, MotorAcceleration); // Umdrehungen, speed steps/s, acceleration mm/s^2
      // Schrittmotor_nanotec(1, 80 * 64, 50 * 64);
      return true;
    }


    if (ch == '+') // Tastaturanschlag "+"
    {
      Serial.println("+");
      Schrittmotor_L_aktiv(true);
      Schrittmotor_R_aktiv(true);
      // Schrittmotor_nanotec_aktiv(true);
      return true;
    }

    if (ch == '-') // Tastaturanschlag "-"
    {
      Serial.println("-");
      Schrittmotor_L_aktiv(false);
      Schrittmotor_R_aktiv(false);
      // Schrittmotor_nanotec_aktiv(false);
      return true;
    }

    if (ch == 'r') // Tastaturanschlag "-"
    {
      Serial.println("1");
      Relays_clickCluck();
    }

    if (ch == 'w') // Tastaturanschlag "-"
    {
      RelayWatercooling_SetStatus(true);

    }

    if (ch == 's') // Tastaturanschlag "-"
    {
      RelayWatercooling_SetStatus(false);

    }

    if (ch == 'f') // Tastaturanschlag "f"
    {
      Farbmischer_GibFarbe(1, 1);
    }
    if (ch == 'g') // Tastaturanschlag "f"
    {
      Farbmischer_GibFarbe(0, 1);
    }
    if (ch == 'h') // Tastaturanschlag "f"
    {
      Farbmischer_GibFarbe(1, 0);
    }



  }


  return false;
}
