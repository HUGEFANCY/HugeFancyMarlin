
// Define the digital inputs
#define jB1 1  // Joystick button 1
#define jB2 0  // Joystick button 2
#define t1 7   // Toggle switch 1
#define t2 4   // Toggle switch 1
#define b1 8   // Button 1
#define b2 9   // Button 2
#define b3 2   // Button 3
#define b4 3   // Button 4

struct DataPackage_Joystick // Max size of this struct is 32 bytes - NRF24L01 buffer limit
{
  byte header;
  byte j1PotX;
  byte j1PotY;
  byte j1Button;
  byte j2PotX;
  byte j2PotY;
  byte j2Button;
  byte pot1;
  byte pot2;
  byte tSwitch1;
  byte tSwitch2;
  byte button1;
  byte button2;
  byte button3;
  byte button4;
};

DataPackage_Joystick Joystick; // Create a variable with the above structure
DataPackage_Joystick LastimeData; // Create a variable with the above structure

void setup_JoystickInputs()
{

  // Activate the Arduino internal pull-up resistors
  pinMode(jB1, INPUT_PULLUP);
  pinMode(jB2, INPUT_PULLUP);
  pinMode(t1, INPUT_PULLUP);
  pinMode(t2, INPUT_PULLUP);
  pinMode(b1, INPUT_PULLUP);
  pinMode(b2, INPUT_PULLUP);
  pinMode(b3, INPUT_PULLUP);
  pinMode(b4, INPUT_PULLUP);

  // Set initial default values
  Joystick.header = 0;
  Joystick.j1PotX = 127; // Values from 0 to 255. When Joystick is in resting position, the value is in the middle, or 127. We actually map the pot value from 0 to 1023 to 0 to 255 because that's one BYTE value
  Joystick.j1PotY = 127;
  Joystick.j2PotX = 127;
  Joystick.j2PotY = 127;
  Joystick.j1Button = 1;
  Joystick.j2Button = 1;
  Joystick.pot1 = 1;
  Joystick.pot2 = 1;
  Joystick.tSwitch1 = 1;
  Joystick.tSwitch2 = 1;
  Joystick.button1 = 0;
  Joystick.button2 = 0;
  Joystick.button3 = 0;
  Joystick.button4 = 0;

  // Set initial last time default values
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
  LastimeData.button1 = 0;
  LastimeData.button2 = 0;
  LastimeData.button3 = 0;
  LastimeData.button4 = 0;
}

void loop_Inputs()
{
  // Read all analog inputs and map them to one Byte value
  Joystick.j1PotX = map(analogRead(A1), 0, 1023, 0, 255); // Convert the analog read value from 0 to 1023 into a BYTE value from 0 to 255
  Joystick.j1PotY = map(analogRead(A0), 0, 1023, 0, 255);
  Joystick.j2PotX = map(analogRead(A2), 0, 1023, 0, 255);
  Joystick.j2PotY = map(analogRead(A3), 0, 1023, 0, 255);
  Joystick.pot1 = map(analogRead(A7), 0, 1023, 0, 255);
  Joystick.pot2 = map(analogRead(A6), 0, 1023, 0, 255);
  // Read all digital inputs
  Joystick.j1Button = digitalRead(jB1);
  Joystick.j2Button = digitalRead(jB2);
  Joystick.tSwitch1 = digitalRead(t1);
  Joystick.tSwitch2 = digitalRead(t2);
  Joystick.button1 = digitalRead(b1);
  Joystick.button2 = digitalRead(b2);
  Joystick.button3 = digitalRead(b3);
  Joystick.button4 = digitalRead(b4);
}
