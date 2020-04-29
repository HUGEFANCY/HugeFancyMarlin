// Sicherheitsfeatures

unsigned long gameover_LastUpdatePreviousMillis = 0;
unsigned long RS485_updateVariables_LastUpdatePreviousMillis = 0;

void watchdog_gameover()
{
  const int gameover_updateInterval = 2000;
  if (currentMillis - gameover_LastUpdatePreviousMillis >= gameover_updateInterval)
  {
    gameover_LastUpdatePreviousMillis = currentMillis; // save the last time of the event

    // Gameover – Länger als 10 Sekunden nichts vom Teensy Schaltschrank gehört. Schalte alles ab.
    const int gameover = 10000;
    if (currentMillis - RS485_updateVariables_LastUpdatePreviousMillis >= gameover)
    {
      Serial.println("Gameover – RS485_updateVariables_LastUpdatePreviousMillis");
      /// ### ToDo -> Marlin stoppen, Notaus, Nothalt
      // ### ToDo Marlin Nothalt aktivieren (ohne Teensy Schaltschrank)
    }
  }
}
