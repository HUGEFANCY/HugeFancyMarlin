// https://www.mymakerstuff.de/2018/05/18/arduino-tutorial-der-temperatursensor/

int sensorPin = A8;
int bitwertNTC = 0;
long widerstand1 = 10000;                 //Ohm
long bWert = 3950;                          // B- Wert vom NTC
double widerstandNTC = 10000;
double kelvintemp = 273.15;                // 0°Celsius in Kelvin
double Tn = kelvintemp + 25;               //Nenntemperatur in Kelvin
double TKelvin = 0;                        //Die errechnete Isttemperatur
double T = 0;                              //Die errechnete Isttemperatur
int analog_resolution = 10; // sets resolution of analog writing as exponent of 2 (2^12=1024)
const int MAX_ANALOG_VALUE = pow(2, analog_resolution);

void setup() 
{
  analogReadResolution(analog_resolution);

  pinMode(A8, INPUT);
  Serial.begin(9600);
}

void loop()

{

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
