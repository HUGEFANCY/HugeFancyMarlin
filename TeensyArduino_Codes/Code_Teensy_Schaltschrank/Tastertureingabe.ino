String charmodus = "leer";

void SerialTastatur_CheckKeys()
{
  if (Serial.available())
  {
    char ch = Serial.read();

    if (ch == 'i') // Tastaturanschlag "1"
    {
      Serial.println("--- Information ---");
      Serial.println("--- f: fan");
    }


    ///////////// LÜFTER
    if (ch == 'f') // Tastaturanschlag "1"
    {
      Serial.println("--- Modus Fan PWM ---"); Serial.println();
      charmodus = "fan";
    }
    if ((charmodus == "fan") and (ch == '1'))
    {
      Serial.println("fan 100%");
      PwmValuePartCoolingFanMarlin = 0;
    }
    if ((charmodus == "fan") and (ch == '2'))
    {
      Serial.println("fan 50%");
      PwmValuePartCoolingFanMarlin = 122;
    }
    if ((charmodus == "fan") and (ch == '3'))
    {
      Serial.println("fan 50%");
      PwmValuePartCoolingFanMarlin = 255;
    }


    if (ch == 'c') // Tastaturanschlag "1"
    {
      Serial.println("--- Modus Click Color ---"); Serial.println();
      charmodus = "click_color";
    }
    if ((charmodus == "click_color") and (ch == '1'))
    {
      Serial.println("1 x Color L");
      RS485_Schaltschrank_Send_clickColor(1, 0);
    }
    if ((charmodus == "click_color") and (ch == '2'))
    {
      Serial.println("1 x Color R");
      RS485_Schaltschrank_Send_clickColor(0, 1);
    }
  }
}
