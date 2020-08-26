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
      Serial.println("--- c: color");
    }


    ///////////// LÜFTER
    if (ch == 'f') // Tastaturanschlag "1"
    {
      Serial.println("--- Modus Fan PWM ---"); Serial.println();
      charmodus = "fan";
    }
    if ((charmodus == "fan") and (ch == '4'))
    {
      Serial.println("fan 100%");
      PwmValuePartCoolingFanMarlin = 255;
    }
    if ((charmodus == "fan") and (ch == '3'))
    {
      Serial.println("fan 75%");
      PwmValuePartCoolingFanMarlin = 200;
    }
    if ((charmodus == "fan") and (ch == '2'))
    {
      Serial.println("fan 50%");
      PwmValuePartCoolingFanMarlin = 124;
    }
    if ((charmodus == "fan") and ((ch == '1') or (ch == '0')))
    {
      Serial.println("fan 0%");
      PwmValuePartCoolingFanMarlin = 0;
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
