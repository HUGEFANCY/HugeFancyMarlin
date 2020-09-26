
// Helper functions for Relays
// TODO: make this all into one function 

// Relays Pinout 
const byte RelayHeaterZone_1_EN = 36;
const byte RelayHeaterZone_2_EN = 37;
const byte RelayCoolerZone_1_EN = 38;
const byte RelayCoolerZone_2_EN = 39;

const byte RelayWatercooling_EN = 21;
const byte RelayLicht_EN = 22;

void Relays_setup()
{
  pinMode (RelayHeaterZone_1_EN, OUTPUT);
  Relay_SetStatus(RelayHeaterZone_1_EN, false);
  pinMode (RelayHeaterZone_2_EN, OUTPUT);
  Relay_SetStatus(RelayHeaterZone_2_EN, false);
  pinMode (RelayCoolerZone_1_EN, OUTPUT);
  Relay_SetStatus(RelayCoolerZone_1_EN, false);
  pinMode (RelayCoolerZone_2_EN, OUTPUT);
  RelayCoolerZone_2_SetStatus(false);
  Relay_SetStatus(RelayCoolerZone_2_EN, false);

  pinMode (RelayWatercooling_EN, OUTPUT);
  Relay_SetStatus(RelayWatercooling_EN, true);
  pinMode (RelayLicht_EN, OUTPUT);
  Relay_SetStatus(RelayLicht_EN, true);
  Relay_SetStatus(RelayWatercooling_EN, false);
}

void Relay_SetStatus(int ZoneRelay, bool status)
{
  if (statusSetzen == true)
  {
    digitalWrite(ZoneRelay, HIGH);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(ZoneRelay, LOW);
    delay(10);
  }
}

void Relays_clickCluck()
{
  
  Relay_SetStatus(RelayCoolerZone_1_EN, false);
  delay(3000);
  Relay_SetStatus(RelayCoolerZone_2_EN, false);
  delay(3000);
  Relay_Setstatus(RelayCoolerZone_1_EN, true);
  delay(300);
  Relay_SetStatus(RelayCoolerZone_2_EN, true);
  delay(300);
  

}

void Relays_clickCluck2()
{
  
  Relay_Setstatus(RelayCoolerZone_1_EN, true);
  delay(300);
  Relay_Setstatus(RelayCoolerZone_2_EN, true);
  delay(300);

  Relay_Setstatus(RelayHeaterZone_1_EN, true);
  delay(500);
  Relay_Setstatus(RelayHeaterZone_2_EN, true);
  delay(500);
  

  Relay_Setstatus(RelayHeaterZone_1_EN, false);
  delay(10);
  Relay_Setstatus(RelayHeaterZone_2_EN, false);
  delay(100);
  Relay_Setstatus(RelayCoolerZone_1_EN, false);
  delay(100);
  Relay_Setstatus(RelayCoolerZone_2_EN, false);
  delay(10);

  // Wasserkühlung
  Relay_Setstatus(RelayWatercooling_EN, false);
  delay(100);
  Relay_Setstatus(RelayWatercooling_EN, true);
  delay(100);

  // Licht
  Relay_Setstatus(RelayLicht_EN, false);
  delay(200);
  Relay_Setstatus(RelayLicht, true);
  //delay(500);

}
