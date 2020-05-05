
// Relays

const byte RelayExit_1_EN  = 15;
const byte RelayExit_2_EN = 16;
const byte RelayKompressor_EN = 17;

void Relays_setup()
{
  pinMode (RelayExit_1_EN, OUTPUT);
  RelayExit_1(false);

  pinMode (RelayExit_2_EN, OUTPUT);
  RelayExit_2(false);

  pinMode (RelayKompressor_EN, OUTPUT);
  RelayKompressor(false);
}

void RelayExit_1(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(RelayExit_1_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(RelayExit_1_EN, HIGH);
    delay(10);
  }
}

void RelayExit_2(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(RelayExit_2_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(RelayExit_2_EN, HIGH);
    delay(10);
  }
}

void RelayKompressor(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(RelayKompressor_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(RelayKompressor_EN, HIGH);
    delay(10);
  }
}
