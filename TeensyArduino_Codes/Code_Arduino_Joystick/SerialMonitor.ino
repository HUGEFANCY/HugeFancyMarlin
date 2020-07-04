



Metro Metro_SerialDataOutput = Metro(100);





void loop_SerialDataOutput()
{
  if (Metro_SerialDataOutput.check() == true)
  {
    ///////////////////////
    // Potentiometer
    ///////////////////////
    if (LastimeData.pot1 != Joystick.pot1)
    {
      Serial.print("Poti 1 = "); Serial.println(Joystick.pot1);
      LastimeData.pot1 = Joystick.pot1;
    }

    if (LastimeData.pot2 != Joystick.pot2)
    {
      Serial.print("Poti 2 = "); Serial.println(Joystick.pot2);
      //Oled(dataOutgoing.pot2, 5);
      LastimeData.pot2 = Joystick.pot2;
    }

    ///////////////////////
    // ToggleSwitch
    ///////////////////////
    if (LastimeData.tSwitch1 != Joystick.tSwitch1)
    {
      Serial.print("Toogle L = "); Serial.println(Joystick.tSwitch1);
      LastimeData.tSwitch1 = Joystick.tSwitch1;
    }
    if (LastimeData.tSwitch2 != Joystick.tSwitch2)
    {
      Serial.print("Toogle R = "); Serial.println(Joystick.tSwitch2);
      LastimeData.tSwitch2 = Joystick.tSwitch2;
    }

    ///////////////////////
    // Buttons
    ///////////////////////
    if (LastimeData.button1 != Joystick.button1)
    {
      Serial.print("Button 1 = "); Serial.println(Joystick.button1);
      LastimeData.button1 = Joystick.button1;
    }
    if (LastimeData.button2 != Joystick.button2)
    {
      Serial.print("Button 2 = "); Serial.println(Joystick.button2);
      LastimeData.button2 = Joystick.button2;
    }
    if (LastimeData.button3 != Joystick.button3)
    {
      Serial.print("Button 3 = "); Serial.println(Joystick.button3);
      LastimeData.button3 = Joystick.button3;
    }
    if (LastimeData.button4 != Joystick.button4)
    {
      Serial.print("Button 4 = "); Serial.println(Joystick.button4);
      LastimeData.button4 = Joystick.button4;
    }
    
  }
}
