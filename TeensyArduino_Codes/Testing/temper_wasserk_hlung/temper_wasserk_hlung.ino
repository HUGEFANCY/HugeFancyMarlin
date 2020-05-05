int sensorPin = A8;
int bitwertNTC = 0;
long widerstand1 = 100000;                 //Ohm
int bWert = 3435;                          // B- Wert vom NTC
double widerstandNTC = 0;
double kelvintemp = 273.15;                // 0°Celsius in Kelvin
double Tn = kelvintemp + 25;               //Nenntemperatur in Kelvin
double TKelvin = 0;                        //Die errechnete Isttemperatur
double T = 0;                              //Die errechnete Isttemperatur

void setup() {

  Serial.begin(9600);
}

void loop() {

    Serial.println("Sensormessung:  ");
    bitwertNTC = analogRead(sensorPin);      // lese Analogwert an A0 aus
    widerstandNTC = widerstand1 * (((double)bitwertNTC / 1024) / (1 - ((double)bitwertNTC / 1024)));
    // berechne den Widerstandswert vom NTC
    TKelvin = 1 / ((1 / Tn) + ((double)1 / bWert) * log((double)widerstandNTC / widerstand1));
    // ermittle die Temperatur in Kelvin
    T = TKelvin - kelvintemp;                // ermittle die Temperatur in °C

    Serial.println("Analog: ");              //
    Serial.println(bitwertNTC);              //
    Serial.println("NTC- Widerstand: ");     //Gebe die ermittelten Werte aus
    Serial.println(widerstandNTC);           //
    Serial.println("Temperatur: ");          //Gebe die ermittelten Werte aus
    Serial.println(T);                       //

    delay(1000);                               // Warte eine Sekunde und mache alles nochmal
  
}
