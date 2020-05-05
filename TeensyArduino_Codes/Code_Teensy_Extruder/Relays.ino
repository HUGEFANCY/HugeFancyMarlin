
// Relays

const byte RelayHeaterZone_1_EN = 36;
const byte RelayHeaterZone_2_EN = 37;
const byte RelayCoolerZone_1_EN = 38;
const byte RelayCoolerZone_2_EN = 39;

const byte RelayWatercooling_EN = 21;
const byte RelayLicht_EN = 22;

void Relays_setup()
{
  pinMode (RelayHeaterZone_1_EN, OUTPUT);
  RelayHeaterZone_1_SetStatus(false);
  pinMode (RelayHeaterZone_2_EN, OUTPUT);
  RelayHeaterZone_2_SetStatus(false);
  pinMode (RelayCoolerZone_1_EN, OUTPUT);
  RelayCoolerZone_1_SetStatus(false);
  pinMode (RelayCoolerZone_2_EN, OUTPUT);
  RelayCoolerZone_2_SetStatus(false);

  pinMode (RelayWatercooling_EN, OUTPUT);
  RelayWatercooling_SetStatus(false);
  pinMode (RelayLicht_EN, OUTPUT);
  RelayLicht_SetStatus(false);
}


void RelayHeaterZone_1_SetStatus(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(RelayHeaterZone_1_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(RelayHeaterZone_1_EN, HIGH);
    delay(10);
  }
}

void RelayHeaterZone_2_SetStatus(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(RelayHeaterZone_2_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(RelayHeaterZone_2_EN, HIGH);
    delay(10);
  }
}

void RelayCoolerZone_1_SetStatus(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(RelayCoolerZone_1_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(RelayCoolerZone_1_EN, HIGH);
    delay(10);
  }
}

void RelayCoolerZone_2_SetStatus(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(RelayCoolerZone_2_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(RelayCoolerZone_2_EN, HIGH);
    delay(10);
  }
}



void RelayWatercooling_SetStatus(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(RelayWatercooling_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(RelayWatercooling_EN, HIGH);
    delay(10);
  }
}

void RelayLicht_SetStatus(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(RelayLicht_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(RelayLicht_EN, HIGH);
    delay(10);
  }
}


void Relays_clickCluck()
{
  RelayHeaterZone_1_SetStatus(true);
  delay(200);
  RelayHeaterZone_2_SetStatus(true);
  delay(200);
  RelayCoolerZone_1_SetStatus(true);
  delay(200);
  RelayCoolerZone_2_SetStatus(true);
  delay(200);

  RelayHeaterZone_1_SetStatus(false);
  delay(200);
  RelayHeaterZone_2_SetStatus(false);
  delay(200);
  RelayCoolerZone_1_SetStatus(false);
  delay(200);
  RelayCoolerZone_2_SetStatus(false);
  delay(200);

  // Wasserkühlung
  RelayWatercooling_SetStatus(true);
  delay(500);
  RelayWatercooling_SetStatus(false);
  delay(500);

  // Licht
  RelayLicht_SetStatus(true);
  delay(200);
  RelayLicht_SetStatus(false);
  //delay(500);

}
