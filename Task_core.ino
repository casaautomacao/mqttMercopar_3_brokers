
void core0code( void * pvParameters ) {


  for (;;)
  {

    vTaskDelay(2);

    if (tempWdt.Saida(1))
    {
      Serial.println("WDT");
      tempWdt.Saida(0);
    }

    contaPeca();

  }

}



void core1code( void * pvParameters ) {


  for (;;)
  {

    vTaskDelay(10);

    ArduinoOTA.handle();
    printDebugF();
    reconexao();
    writeMqtt();
    zeraContagem();
  }

}
