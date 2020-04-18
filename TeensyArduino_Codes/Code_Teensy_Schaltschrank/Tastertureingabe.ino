boolean SerialTastatur_CheckKeys()
{
  if (Serial.available())
  {
    char ch = Serial.read();

    if (ch == '1') // Tastaturanschlag "1"
    {
      Serial.println("--- Tastaturanschlag 1 ---"); Serial.println();
      return true;
    }
  }
  return false;
}
