// Schrittmotoren für den Farbmischer ansteuern

#include <TeensyStep.h>
// Git: https://github.com/luni64/TeensyStep DOCUMENTATION

// PINOUTMotorSpeed

// Motor Rechts = F1
const int M_R_EN = 33; // Enable Pin
Stepper M_R(34, 35); // Step, Dir

// Motor Links = F2
const int M_L_EN = 29; // Enable Pin //15
Stepper M_L(27, 28); // Step, Dir // 16,17

StepControl StepController; // Controller, Stepping Mode


/*
  // Motor Zusatz
  const int M_Zusatz_EN = 26; // Enable Pin
  const int M_Zusatz_Endstop = 25; // Endstop Pin
  Stepper M_Zusatz(30, 31); // Step, Dir
*/

/*
  // NANOTEC
  const int microstepping_nanotec = 64; // Stepper Nanotec 16-fach
  const int Nanotec_MaxSpeed = 800; // Stepper Nanotec z.B. 800
  const int Nanotec_Acceleration = 500; // Stepper Nanotec z.B. 500
  // Enable Funktion bei Nanotec invertiert.
*/


const int motorsteps = 200; // 200 Schrittmotor, 16 Servo
const int gear_ratio = 1; // >0 entspricht Untersetzung

const int M_LR_microstepping = 8; // TMC 2209 16 = Standard ohne Jumper
const int M_LR_MaxSpeed = 400;
const int M_LR_Acceleration = 500;
int MotorSpeed = 200; // Umdrehungen, speed steps/s,
int MotorAcceleration = 150; // acceleration mm/s^2


const int Anzahl_Schaufeln = 3;


Metro StepperTurnOffIntervall = Metro(1000);


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
  StepController.moveAsync(M_L);

  M_L.setMaxSpeed(M_LR_MaxSpeed);         // stp/s
  M_L.setAcceleration(M_LR_Acceleration); // stp/s^2
  //Schrittmotor_L_aktiv(false);
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
  StepController.moveAsync(M_R);

  M_R.setMaxSpeed(M_LR_MaxSpeed); // stp/s
  M_R.setAcceleration(M_LR_Acceleration); // stp/s^2
  //Schrittmotor_R_aktiv(false);
}


void Farbmischer_GibFarbe(int GibSchaufeln_L, int GibSchaufeln_R)
{
  Schrittmotor_L_aktiv(true);
  M_L.setMaxSpeed(M_LR_MaxSpeed); // stp/s
  M_L.setAcceleration(M_LR_Acceleration); // stp/s^2

  Schrittmotor_R_aktiv(true);
  M_R.setMaxSpeed(M_LR_MaxSpeed); // stp/s
  M_R.setAcceleration(M_LR_Acceleration); // stp/s^2

  M_L.setTargetRel(GibSchaufeln_L * motorsteps * gear_ratio * M_LR_microstepping / Anzahl_Schaufeln);
  M_R.setTargetRel(GibSchaufeln_R * motorsteps * gear_ratio * M_LR_microstepping / Anzahl_Schaufeln);


  StepController.moveAsync(M_L, M_R);
}

void Stepper_loop()
{
  if (StepperTurnOffIntervall.check() == 1)
  {
    if (StepController.isRunning() == false)
    {
      Schrittmotor_L_aktiv(false);
      Schrittmotor_R_aktiv(false);
    }
  }
}
