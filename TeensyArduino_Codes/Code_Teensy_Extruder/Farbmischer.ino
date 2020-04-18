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

void Farbmischer_GibFarbe(int Schuebe_L, int Schuebe_R)
{
  const int Anzahl_Schaufeln = 8;

  if (Schuebe_L != 0)
  {
    float Drehwinkel_L = 2 * PI / Anzahl_Schaufeln * Schuebe_L;
    ML.setTargetRel(Drehwinkel_L * 200 * microstepping); // 1600 = 1 REV with TMC2209
    StepController_L.move(ML);
  }
  if (Schuebe_R != 0)
  {
    float Drehwinkel_R = 2 * PI / Anzahl_Schaufeln * Schuebe_R;
    MR.setTargetRel(Drehwinkel_R * 200 * microstepping); // 1600 = 1 REV with TMC2209
    StepController_R.move(MR);
  }
}
