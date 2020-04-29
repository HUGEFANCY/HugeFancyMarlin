

const byte PIN_R = 21;
const byte PIN_G = 22;
const byte PIN_B = 23;


void RGB_setup()
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
  digitalWrite(PIN_R, 0);
  digitalWrite(PIN_G, 0);
  digitalWrite(PIN_B, 0);
}

void RGB_color(int R, int G, int B)
{
  digitalWrite(PIN_R, 1);
  digitalWrite(PIN_G, 1);
  digitalWrite(PIN_B, 1);
}
