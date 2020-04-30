boolean SerialTastatur_CheckKeys()
{
  if (Serial.available())
  {
    char ch = Serial.read();

    if (ch == '1') // Tastaturanschlag "1"
    {
      Serial.println("1");
       relay_clickCluck();
       
      
      return true;
    }

    if (ch == '2') // Tastaturanschlag "2"
    {
     
      return true;
    }


    if (ch == '+') // Tastaturanschlag "+"
    {
      return true;
    }

    if (ch == '-') // Tastaturanschlag "-"
    {
      return true;
    }
  }






  return false;
}
