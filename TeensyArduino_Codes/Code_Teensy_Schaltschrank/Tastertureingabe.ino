boolean SerialTastatur_CheckKeys()
{
  if (Serial.available())
  {
    char ch = Serial.read();

    if (ch == '1') // Tastaturanschlag "1"
    {
      Serial.println("--- Tastaturanschlag 1 ---"); Serial.println();
      RelayKompressor(true);
      return true;
    }




    if (ch == '2') // Tastaturanschlag "2"
    {
      Serial.println("--- Tastaturanschlag 2 ---"); Serial.println();
      RelayKompressor(false);
      return true;
    }
  }


  return false;
}
