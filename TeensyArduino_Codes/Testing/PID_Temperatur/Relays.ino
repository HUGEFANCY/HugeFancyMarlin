
// relays


const byte relay_heaterOben_EN = 2;
const byte relay_heaterUnten_EN = 3;
const byte relay_coolerOben_EN = 4;
const byte relay_coolerUnten_EN = 5;

void setup_relays()
{
  pinMode (relay_heaterOben_EN, OUTPUT);
  relay_heaterOben_setStatus(false);
  pinMode (relay_heaterUnten_EN, OUTPUT);
  relay_heaterUnten_setStatus(false);
  pinMode (relay_coolerOben_EN, OUTPUT);
  relay_coolerOben_setStatus(false);
  pinMode (relay_coolerUnten_EN, OUTPUT);
  relay_coolerUnten_setStatus(false);
}


void relay_heaterOben_setStatus(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(relay_heaterOben_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(relay_heaterOben_EN, HIGH);
    delay(10);
  }
}

void relay_heaterUnten_setStatus(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(relay_heaterUnten_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(relay_heaterUnten_EN, HIGH);
    delay(10);
  }
}

void relay_coolerOben_setStatus(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(relay_coolerOben_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(relay_coolerOben_EN, HIGH);
    delay(10);
  }
}

void relay_coolerUnten_setStatus(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(relay_coolerUnten_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(relay_coolerUnten_EN, HIGH);
    delay(10);
  }
}


void relay_clickCluck()
{
  relay_heaterOben_setStatus(true);
  delay(200);
  relay_heaterUnten_setStatus(true);
  delay(200);
  relay_coolerOben_setStatus(true);
  delay(200);
  relay_coolerUnten_setStatus(true);
  delay(200);
  relay_heaterOben_setStatus(false);
  delay(200);
  relay_heaterUnten_setStatus(false);
  delay(200);
  relay_coolerOben_setStatus(false);
  delay(200);
  relay_coolerUnten_setStatus(false);
  delay(200);
  delay(1000);
}
