// Sicherheitsfeatures

unsigned long gameover_LastUpdatePreviousMillis = 0;
unsigned long RS485_AnswerUpdateVariables_LastUpdatePreviousMillis = 0;

void watchdog_gameover()
{
  const int gameover_updateInterval = 2000;
  if (currentMillis - gameover_LastUpdatePreviousMillis >= gameover_updateInterval)
  {
    gameover_LastUpdatePreviousMillis = currentMillis; // save the last time of the event

    // ### ToDo aufrufen im Intervall von 1 Sekunde oder immer wenn I2C neues verkündet
    // ### ToDo bzw. wenn lange nichts mehr von Marlin kommt ABBRUCH!!!!

    // Gameover – Länger als 10 Sekunden nichts vom Teensy Extruder gehört. Schalte alles ab.
    const int gameover = 10000;
    if (currentMillis - RS485_AnswerUpdateVariables_LastUpdatePreviousMillis >= gameover)
    {
      Serial.println("Gameover – RS485_AnswerUpdateVariables_LastUpdatePreviousMillis");
      /// ### ToDo -> Marlin stoppen, Notaus, Nothalt
    }
  }
}
