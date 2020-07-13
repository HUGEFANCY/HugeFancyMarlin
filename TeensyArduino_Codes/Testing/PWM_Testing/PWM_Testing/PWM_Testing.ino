//Initializing LED Pin
int led_pin = LED_BUILTIN;

void setup() {
  //Declaring LED pin as output
  pinMode(led_pin, OUTPUT);
}

void loop() {
  //Fading the LED
  for(int i=0; i<255; i++){
    analogWrite(led_pin, i);
    delay(50);
  }

  delay(1000);
  for(int i=255; i>0; i--){
    analogWrite(led_pin, i);
    delay(50);
  }
   delay(5000);
}
