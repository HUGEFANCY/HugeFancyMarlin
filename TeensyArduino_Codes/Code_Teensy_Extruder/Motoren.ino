// Schrittmotoren für den Farbmischer ansteuern

#include <TeensyStep.h>
// Git: https://github.com/luni64/TeensyStep DOCUMENTATION

// PINOUT

// Motor Rechts = F1
const int M_R_EN = 33; // const int MR_EN = 18; // Enable Pin
Stepper M_R(34, 35); // Stepper MR(19, 20); // Step, Dir
StepControl StepController_R; // Controller, Stepping Mode

/*
  // NANOTEC (läuft an Rechts = F1)
  const int M_nanotec_EN = 30; // Enable Pin
  Stepper M_nanotec(31, 32); // Step, Dir
  StepControl StepController_nanotec; // Controller, Stepping Mode

  const int microstepping_nanotec = 64; // Stepper Nanotec 16-fach
  const int Nanotec_MaxSpeed = 800; // Stepper Nanotec z.B. 800
  const int Nanotec_Acceleration = 500; // Stepper Nanotec z.B. 500
*/


// Motor Links = F2
const int M_L_EN = 29; // Enable Pin //15
Stepper M_L(27, 28); // Step, Dir // 16,17
StepControl StepController_L; // Controller, Stepping Mode


const int motorsteps = 16; // 200 Schrittmotor, 16 Servo
const int gear_ratio = 40; // >0 entspricht Untersetzung

const int M_LR_microstepping = 16; // TMC 2209 16 = Standard ohne Jumper
const int M_LR_MaxSpeed = 8000;
const int M_LR_Acceleration = 1000;

const int Anzahl_Schaufeln = 8;


void Motoren_setup()
{
  pinMode (M_L_EN, OUTPUT);
  pinMode (M_R_EN, OUTPUT);
  // NANOTEC
  //pinMode (M_nanotec_EN, OUTPUT);
  delay(10);

  Schrittmotor_L_aktiv(false);
  Schrittmotor_R_aktiv(false);
  // NANOTEC
  // Schrittmotor_nanotec_aktiv(false);

  // Speed [stp/s] // Acceleration [stp/s^2]
  M_L.setMaxSpeed(M_LR_MaxSpeed);
  M_L.setAcceleration(M_LR_Acceleration);
  M_R.setMaxSpeed(M_LR_MaxSpeed);
  M_R.setAcceleration(M_LR_Acceleration);
  // NANOTEC
  // M_nanotec.setMaxSpeed(Nanotec_MaxSpeed);
  // M_nanotec.setAcceleration(Nanotec_Acceleration);
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

  M_L.setTargetRel(Umdrehungen * gear_ratio * motorsteps * M_LR_microstepping); // 1600 = 1 REV with TMC2209
  StepController_L.move(M_L);

  M_L.setMaxSpeed(M_LR_MaxSpeed);         // stp/s
  M_L.setAcceleration(M_LR_Acceleration); // stp/s^2
  Schrittmotor_L_aktiv(false);
}

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

  M_R.setTargetRel(Umdrehungen * motorsteps * gear_ratio * M_LR_microstepping); // 1600 = 1 REV with TMC2209
  StepController_R.move(M_R);

  M_R.setMaxSpeed(M_LR_MaxSpeed); // stp/s
  M_R.setAcceleration(M_LR_Acceleration); // stp/s^2
  Schrittmotor_R_aktiv(false);
}


/* NANOTEC
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
    delay(100);
  }
  }

  void Schrittmotor_nanotec(int Umdrehungen, int Speed, int Acceleration)
  {
  Schrittmotor_nanotec_aktiv(true);
  M_nanotec.setMaxSpeed(Speed); // stp/s
  M_nanotec.setAcceleration(Acceleration); // stp/s^2

  M_nanotec.setTargetRel(Umdrehungen * gear_ratio * motorsteps * microstepping_nanotec);
  StepController_nanotec.move(M_nanotec);

  Schrittmotor_nanotec_aktiv(false);
  }
*/


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
