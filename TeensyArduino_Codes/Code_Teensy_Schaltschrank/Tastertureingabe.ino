boolean SerialTastatur_CheckKeys()
{
  if (Serial.available())
  {
    char ch = Serial.read();

    if (ch == '1') // Tastaturanschlag "1"
    {
      Serial.println("--- Tastaturanschlag 1 ---"); Serial.println();
      RS485_Schaltschrank_Send_clickColor(1, 0);
      return true;
    }
        if (ch == '2') // Tastaturanschlag "1"
    {
      Serial.println("--- Tastaturanschlag 2 ---"); Serial.println();
      RS485_Schaltschrank_Send_clickColor(0, 1);
      return true;
    }



    if (ch == 'f') // Tastaturanschlag "2"
    {
      Serial.println("--- Farbe ---"); Serial.println();
      RS485_Schaltschrank_Send_clickColor(1, 3);
      return true;
    }



  }


  return false;
}
