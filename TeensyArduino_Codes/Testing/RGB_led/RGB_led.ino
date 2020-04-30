

const byte PIN_R = 21;
const byte PIN_G = 22;
const byte PIN_B = 23;


void setup()
{
  pinMode (PIN_R, OUTPUT);
  pinMode (PIN_G, OUTPUT);
  pinMode (PIN_B, OUTPUT);
  delay(10);
  RGB_aus();
  delay(10);
  RGB_color(255, 0, 0);
  delay(1000);
  RGB_color(0, 255, 0);
  delay(1000);
  RGB_color(0, 0, 255);
  delay(1000);
  RGB_aus();

}

void RGB_aus()
{
  analogWrite(PIN_R, 0);
  analogWrite(PIN_G, 0);
  analogWrite(PIN_B, 0);
}

void RGB_color(int R, int G, int B)
{
  analogWrite(PIN_R, R);
  analogWrite(PIN_G, G);
  analogWrite(PIN_B, B);
}

void loop()
{
  RGB_color(255,255,255);
}
