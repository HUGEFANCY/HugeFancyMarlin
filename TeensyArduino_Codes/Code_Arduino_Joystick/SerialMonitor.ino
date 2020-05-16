

DataPackageOutcoming LastimeData; // Create a variable with the above structure

Metro Metro_SerialDataOutput = Metro(100);


void setup_SerialDataOutput()
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


void loop_SerialDataOutput()
{
  if (Metro_SerialDataOutput.check() == true)
  {
    // Potentiometer
    if ((LastimeData.pot1 != dataOutgoing.pot1) and (dataOutgoing.button1 == 0))
    {
      Serial.print("Poti 1 = "); Serial.println(dataOutgoing.pot1);
      Oled(dataOutgoing.pot1, 3);
      LastimeData.pot1 = dataOutgoing.pot1;

      if (dataOutgoing.button2 == 0)
      {
        TargetTemperatureZone_1 = dataOutgoing.pot1;
      }
    }

    if (LastimeData.pot2 != dataOutgoing.pot2)
    {
      Serial.print("Poti 2 = "); Serial.println(dataOutgoing.pot2);
      Oled(dataOutgoing.pot2, 5);
      LastimeData.pot2 = dataOutgoing.pot2;
    }

    // ToggleSwitch
    if (LastimeData.tSwitch1 != dataOutgoing.tSwitch1)
    {
      Serial.print("Toogle L = "); Serial.println(dataOutgoing.tSwitch1);
      LastimeData.tSwitch1 = dataOutgoing.tSwitch1;
    }
    if (LastimeData.tSwitch2 != dataOutgoing.tSwitch2)
    {
      Serial.print("Toogle R = "); Serial.println(dataOutgoing.tSwitch2);
      LastimeData.tSwitch2 = dataOutgoing.tSwitch2;
    }


    // Buttons
    if (LastimeData.button1 != dataOutgoing.button1)
    {
      Serial.print("Button 1 = "); Serial.println(dataOutgoing.button1);
      LastimeData.button1 = dataOutgoing.button1;
    }
    /*
      if (LastimeData.button2 != dataOutgoing.button2)
      {
      Serial.print("Button 2 = "); Serial.println(dataOutgoing.button2);
      LastimeData.button2 = dataOutgoing.button2;
      }
    */
    if (LastimeData.button3 != dataOutgoing.button3)
    {
      Serial.print("Button 3 = "); Serial.println(dataOutgoing.button3);
      LastimeData.button3 = dataOutgoing.button3;
    }
    if (LastimeData.button4 != dataOutgoing.button4)
    {
      Serial.print("Button 4 = "); Serial.println(dataOutgoing.button4);
      LastimeData.button4 = dataOutgoing.button4;
    }


  }
}
