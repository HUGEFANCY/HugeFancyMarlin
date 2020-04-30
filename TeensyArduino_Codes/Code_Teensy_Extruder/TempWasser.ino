
// Temperatursensoren Wasserkühlung
// Pinout Lüfter Radiator: https://alienware-forum.de/index.php/Attachment/1319-6b70473c-Diagram-1-png/?s=91c43ccfd0541d71ad162c7ef674f13691a83f23

// Pinout
int PinWasserIn = A21;
int PinWasserOut = A22;

Metro TempWasserIntervall = Metro(1000);

int Lesewassertemp(int Pin)
{
  const int bWert = 3435; // B- Wert vom NTC
  const long Widerstand = 10000; // Ohm
  double widerstandNTC = 0; // Wird berechnet


  int bitwertNTC = 0;


  const double kelvintemp = 273.15; // 0° Celsius in Kelvin
  double Tn = kelvintemp + 25; // Nenntemperatur in Kelvin
  double TKelvin = 0; // Die errechnete Isttemperatur
  int T = 0; // Die errechnete Isttemperatur

  bitwertNTC = analogRead(PinWasserIn);
  widerstandNTC = Widerstand * (((double)bitwertNTC / 1024) / (1 - ((double)bitwertNTC / 1024))); // berechne den Widerstandswert vom NTC

  TKelvin = 1 / ((1 / Tn) + ((double)1 / bWert) * log((double)widerstandNTC / Widerstand)); // ermittle die Temperatur in Kelvin
  T = round(TKelvin - kelvintemp); // ermittle die Temperatur in °C
  Serial.println(T);
  return (T);

}

void TempWasser_loop()
{
  if (TempWasserIntervall.check() == 1)  // check if the metro has passed its interval
  {
    TempWatercooling_In = Lesewassertemp(PinWasserIn);
    TempWatercooling_Out = Lesewassertemp(PinWasserOut);
  }
}
