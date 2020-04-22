// Schrittmotoren für den Farbmischer ansteuern

#include <TeensyStep.h>
// Git: https://github.com/luni64/TeensyStep DOCUMENTATION

// PINOUT

// Motor Links = F2
const int M_L_EN = 15; // Enable Pin //15
Stepper M_L(16, 17); // Step, Dir // 16,17
StepControl StepController_L; // Controller, Stepping Mode

/*
  // Motor Rechts = F1
  const int M_R_EN = 18; // const int MR_EN = 18; // Enable Pin
  Stepper M_R(19, 20); // Stepper MR(19, 20); // Step, Dir
  StepControl StepController_R; // Controller, Stepping Mode
*/

const int M_LR_microstepping = 16; // TMC 2209 16 = Standard ohne Jumper
const int M_LR_MaxSpeed = 8000;
const int M_LR_Acceleration = 1000;

// Motor Nanotec (läuft an Rechts = F1)
const int M_nanotec_EN = 18; // Enable Pin
Stepper M_nanotec(19, 20); // Step, Dir
StepControl StepController_nanotec; // Controller, Stepping Mode

const int microstepping_nanotec = 2; // TMC 2209 16 = Standard ohne Jumper
const int Nanotec_MaxSpeed = 8000;
const int Nanotec_Acceleration = 1000;

const int Anzahl_Schaufeln = 8;


void Motoren_setup()
{
  pinMode (M_L_EN, OUTPUT);
  //pinMode (M_R_EN, OUTPUT);
  pinMode (M_nanotec_EN, OUTPUT);
  delay(10);

  Schrittmotor_L_aktiv(false);
  //Schrittmotor_R_aktiv(false);
  Schrittmotor_nanotec_aktiv(false);

  // Speed [stp/s] // Acceleration [stp/s^2]
  M_L.setMaxSpeed(M_LR_MaxSpeed);
  M_L.setAcceleration(M_LR_Acceleration);
  //M_R.setMaxSpeed(M_LR_MaxSpeed);
  //M_R.setAcceleration(M_LR_Acceleration);
  M_nanotec.setMaxSpeed(Nanotec_MaxSpeed);
  M_nanotec.setAcceleration(Nanotec_Acceleration);
}

void Schrittmotor_L_aktiv(bool statusSetzen)
{
  if (statusSetzen == true)
  {
    digitalWrite(M_L_EN, LOW);
    delay(10);
  }
  else if (statusSetzen == false)
  {
    digitalWrite(M_L_EN, HIGH);
  }
}

void Schrittmotor_L(int Umdrehungen, int Speed, int Acceleration)
{
  Schrittmotor_L_aktiv(true);
  M_L.setMaxSpeed(Speed); // stp/s
  M_L.setAcceleration(Acceleration); // stp/s^2

  M_L.setTargetRel(Umdrehungen * 200 * M_LR_microstepping); // 1600 = 1 REV with TMC2209
  StepController_L.move(M_L);

  M_L.setMaxSpeed(M_LR_MaxSpeed);         // stp/s
  M_L.setAcceleration(M_LR_Acceleration); // stp/s^2
  Schrittmotor_L_aktiv(false);
}

/*

  void Schrittmotor_R_aktiv(bool value)
  {
  if (value == true)
  {
    digitalWrite(M_R_EN, LOW);
    delay(10);
  }
  else if (value == false)
  {
    digitalWrite(M_R_EN, HIGH);
  }
  }

  void Schrittmotor_R(int Umdrehungen, int Speed, int Acceleration)
  {
  Schrittmotor_R_aktiv(true);
  M_R.setMaxSpeed(Speed); // stp/s
  M_R.setAcceleration(Acceleration); // stp/s^2

  M_R.setTargetRel(Umdrehungen * 200 * M_LR_microstepping); // 1600 = 1 REV with TMC2209
  StepController_R.move(M_R);

  M_R.setMaxSpeed(M_LR_MaxSpeed); // stp/s
  M_R.setAcceleration(M_LR_Acceleration); // stp/s^2
  Schrittmotor_R_aktiv(false);
  }

*/



void Schrittmotor_nanotec_aktiv(bool value)
{
  if (value == true)
  {
    digitalWrite(M_nanotec_EN, HIGH); // INVENTIERT WEGEN NANOTEC!!!!!
    delay(500);
  }
  else if (value == false)
  {
    digitalWrite(M_nanotec_EN, LOW); // INVENTIERT WEGEN NANOTEC!!!!!
    delay(10);
  }
}

void Schrittmotor_nanotec(int Umdrehungen, int Speed, int Acceleration)
{
  Schrittmotor_nanotec_aktiv(true);
  M_nanotec.setMaxSpeed(Speed); // stp/s
  M_nanotec.setAcceleration(Acceleration); // stp/s^2

  M_nanotec.setTargetRel(Umdrehungen * 200 * microstepping_nanotec);
  StepController_nanotec.move(M_nanotec);

  Schrittmotor_nanotec_aktiv(false);
}



void Farbmischer_GibFarbe(int GibSchaufeln_L, int GibSchaufeln_R)
{
  if (GibSchaufeln_L != 0)
  {
    float Drehwinkel_L = 2 * PI / Anzahl_Schaufeln * GibSchaufeln_L;
    M_L.setTargetRel(Drehwinkel_L * 200 * M_LR_microstepping); // 1600 = 1 REV with TMC2209
    StepController_L.move(M_L);
  }
  if (GibSchaufeln_R != 0)
  {
    //float Drehwinkel_R = 2 * PI / Anzahl_Schaufeln * GibSchaufeln_R;
    //MR.setTargetRel(Drehwinkel_R * 200 * microstepping); // 1600 = 1 REV with TMC2209
    //StepController_R.move(MR);
  }
}
