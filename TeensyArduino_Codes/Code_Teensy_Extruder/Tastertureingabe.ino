boolean SerialTastatur_CheckKeys()
{
  if (Serial.available())
  {
    char ch = Serial.read();

    if (ch == '1') // Tastaturanschlag "1"
    {
      Serial.println("Motor Links");
      Schrittmotor_L(1, 8000, 1000); // Umdrehungen, speed steps/s, acceleration mm/s^2
      return true;
    }

    if (ch == '2') // Tastaturanschlag "2"
    {
      Serial.println("Motor Rechts");
      Schrittmotor_R(1, 8000, 1000); // Umdrehungen, speed steps/s, acceleration mm/s^2
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

    if (ch == '4') // Tastaturanschlag "-"
    {
      Serial.println("1");
      relay_clickCluck();

    }
  }


  return false;
}
