// Schrittmotoren für den Farbmischer ansteuern

#include <TeensyStep.h>
// Git: https://github.com/luni64/TeensyStep DOCUMENTATION

// PINOUT

// Motor Links
const int ML_EN = 12; // Enable Pin
Stepper ML(14, 15); // Step, Dir
StepControl StepController_L; // Controller, Stepping Mode

// Motor Rechts
const int MR_EN = 16; // Enable Pin
Stepper MR(17, 18); // Step, Dir
StepControl StepController_R; // Controller, Stepping Mode

const int microstepping = 16;
const int Anzahl_Schaufeln = 8;


void Farbmischer_setup()
{
  pinMode (ML_EN, OUTPUT);
  pinMode (MR_EN, OUTPUT);

  const int Farbmischer_MaxSpeed = 8000;
  const int Farbmischer_Acceleration = 1000;

  ML.setMaxSpeed(Farbmischer_MaxSpeed);         // stp/s
  ML.setAcceleration(Farbmischer_Acceleration); // stp/s^2
  MR.setMaxSpeed(Farbmischer_MaxSpeed);         // stp/s
  MR.setAcceleration(Farbmischer_Acceleration); // stp/s^2
}

/*
  byte decodiereFarbmischerUmdrehungen(byte FarbmischerUmdrehungen, char Motor)
  {
  if (Motor == 'L')
  {
    byte Farbschuebe_L = (FarbmischerUmdrehungen & 0b11110000) >> 4; // get the first 4 bits of the byte and shift them right 4 places
    return Farbschaufeln_L;
  }
    if (Motor == 'R')
  {
    byte Farbschaufeln_R = FarbmischerUmdrehungen & 0b00001111; // get the last 4 bits of the byte
    return Farbschaufeln;
  }
  }
*/


void Farbmischer_GibFarbe(byte GibSchaufeln_L, byte GibSchaufeln_R)
{
  if (GibSchaufeln_L != 0)
  {
    float Drehwinkel_L = 2 * PI / Anzahl_Schaufeln * GibSchaufeln_L;
    ML.setTargetRel(Drehwinkel_L * 200 * microstepping); // 1600 = 1 REV with TMC2209
    StepController_L.move(ML);
  }
  if (GibSchaufeln_R != 0)
  {
    float Drehwinkel_R = 2 * PI / Anzahl_Schaufeln * GibSchaufeln_R;
    MR.setTargetRel(Drehwinkel_R * 200 * microstepping); // 1600 = 1 REV with TMC2209
    StepController_R.move(MR);
  }
}
