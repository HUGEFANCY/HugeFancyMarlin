

Data_Package LastimeData; // Create a variable with the above structure
Metro Metro_SerialDataOutput = Metro(50);

void setupSerialDataOutput()
{
  // Set initial default values
  LastimeData.j1PotX = 127; // Values from 0 to 255. When Joystick is in resting position, the value is in the middle, or 127. We actually map the pot value from 0 to 1023 to 0 to 255 because that's one BYTE value
  LastimeData.j1PotY = 127;
  LastimeData.j2PotX = 127;
  LastimeData.j2PotY = 127;
  LastimeData.j1Button = 1;
  LastimeData.j2Button = 1;

  LastimeData.pot1 = 1;
  LastimeData.pot2 = 1;
  LastimeData.tSwitch1 = 1;
  LastimeData.tSwitch2 = 1;
  LastimeData.button1 = 1;
  LastimeData.button2 = 1;
  LastimeData.button3 = 1;
  LastimeData.button4 = 1;
}


void loopSerialDataOutput()
{
  if (Metro_SerialDataOutput.check() == true)
  {
    // Potentiometer
    if (LastimeData.pot1 != data.pot1)
    {
      Serial.print("Poti L = "); Serial.println(data.pot1);
      LastimeData.pot1 = data.pot1;
    }
    if (LastimeData.pot2 != data.pot2)
    {
      Serial.print("Poti R = "); Serial.println(data.pot2);
      LastimeData.pot2 = data.pot2;
    }

    // ToggleSwitch
    if (LastimeData.tSwitch1 != data.tSwitch1)
    {
      Serial.print("Toogle L = "); Serial.println(data.tSwitch1);
      LastimeData.tSwitch1 = data.tSwitch1;
    }
    if (LastimeData.tSwitch2 != data.tSwitch2)
    {
      Serial.print("Toogle R = "); Serial.println(data.tSwitch2);
      LastimeData.tSwitch2 = data.tSwitch2;
    }


    // Buttonx
    if (LastimeData.button1 != data.button1)
    {
      Serial.print("Button 1 = "); Serial.println(data.button1);
      LastimeData.button1 = data.button1;
    }
    if (LastimeData.button2 != data.button2)
    {
      Serial.print("Button 2 = "); Serial.println(data.button2);
      LastimeData.button2 = data.button2;
    }
    if (LastimeData.button3 != data.button3)
    {
      Serial.print("Button 3 = "); Serial.println(data.button3);
      LastimeData.button3 = data.button3;
    }
    if (LastimeData.button4 != data.button4)
    {
      Serial.print("Button 4 = "); Serial.println(data.button4);
      LastimeData.button4 = data.button4;
    }


  }
}
