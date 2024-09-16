void zeraContagem()
{

  if (setaZeraContagem)
  {

Serial.println("zera conta peça");
    contaPecaPersonal = 0;
    contaPecaCoringa = 0;
    salvaLong(0, contaPecaPersonal);
    salvaLong(4, contaPecaCoringa);

    setaZeraContagem = 0;
  }


}




void reconexao()
{
  if (tempReconec.Saida(1))
  {
    Serial.println("Reconectar...");
    if (!client1.connected()) {
      reconnect1();
    }

    if (!client2.connected() and dispositivo == "crescer2") {
      reconnect2();
    }

    if (!client3.connected()) {
      reconnect3();
    }
    tempReconec.Saida(0);
  }


  if (client1.connected()) client1.loop();
  if (client2.connected() and dispositivo == "crescer2") client2.loop();
  if (client3.connected()) client3.loop();

}





void contaPeca() {


  status34 = digitalRead(34);
  status35 = digitalRead(35);

  if (status34 != status34Old )
  {
    if (status34 == 0)
    {
      contaPecaPersonal++;

      salvaLong(0, contaPecaPersonal);


    }
    status34Old = status34;
  }

  if (status35 != status35Old )
  {
    if (status35 == 0)
    {
      contaPecaCoringa++;
      salvaLong(4, contaPecaCoringa);
    }
    status35Old = status35;
  }

}







void writeMqtt() {



  uint8_t result;
  //  uint16_t data[6];

  result = Eletricas.readHoldingRegisters(0x0000, 41);
  if (result == Eletricas.ku8MBSuccess)
  {
    //  Serial.println("Energia* ");

    int j = 0;
    for (int i = 0; i < 41; i++)
    {

      if (i < 23)
      {
        //      Serial.print(i);
        //      Serial.print(": ");
        //      Serial.print(nomeVar(i));
        //      Serial.print(": ");
      }



      if (i < 3)
      {
        float trab = Eletricas.getResponseBuffer(i) / 10.0;
        //     Serial.println(trab, 1);
        valoresMqtt[j] = trab;
        j++;
      }
      else if (i < 6)
      {
        float trab = Eletricas.getResponseBuffer(i) / (10.00 * 2.50);
        //    Serial.println(trab, 2);
        valoresMqtt[j] = trab;
        j++;
      }
      else if (i < 19)
      {
        float trab = Eletricas.getResponseBuffer(i) / (10.000 * 2.500);
        //     Serial.println(trab, 3);
        if (i >= 15 and i < 19)
        {
          valoresMqtt[j] = trab;
          j++;
        }

      }
      else if (i >= 19 and i <= 22)
      {
        float trab = Eletricas.getResponseBuffer(i) / 1000.000;
        //    Serial.println(trab / 1000.000 , 3);
        if (i >= 20)
        {
          valoresMqtt[j] = trab;
          j++;
        }

      }

      //  else Serial.print(Eletricas.getResponseBuffer(i) / 10.0, 1);

      //  Serial.print(", ");
      //  Serial.print("\n");
    }

  }


  long ti = millis();

  for (int j = 0; j < quantDados ; j++)
  {

    if (j < quantDados - 4)
    {
      snprintf (msg, MSG_BUFFER_SIZE, "%lf", valoresMqtt[j]);

      if (client1.connected()) client1.publish(topico[j].c_str(), msg);
      if (client2.connected()) client2.publish(topicoS[j].c_str(), msg);
      if (client3.connected()) client3.publish(topico[j].c_str(), msg);

    }
    else if (j < quantDados - 3 )
    {

      snprintf (msg, MSG_BUFFER_SIZE, "%ld", digitalRead(vetorIn[0]));

      if (client1.connected()) client1.publish(topico[j].c_str(), msg);
      if (client2.connected()) client2.publish(topicoS[j].c_str(), msg);
      if (client3.connected()) client3.publish(topico[j].c_str(), msg);

    }

    else if (j < quantDados - 2 )
    {

      snprintf (msg, MSG_BUFFER_SIZE, "%ld", contaPecaPersonal);

      if (client1.connected()) client1.publish(topico[j].c_str(), msg);
      if (client2.connected()) client2.publish(topicoS[j].c_str(), msg);
      if (client3.connected()) client3.publish(topico[j].c_str(), msg);

    }
    else if (j < quantDados - 1 )
    {

      snprintf (msg, MSG_BUFFER_SIZE, "%ld", contaPecaCoringa);

      if (client1.connected()) client1.publish(topico[j].c_str(), msg);
      if (client2.connected()) client2.publish(topicoS[j].c_str(), msg);
      if (client3.connected()) client3.publish(topico[j].c_str(), msg);

    }

    else if (j < quantDados )

    {
      snprintf (msg, MSG_BUFFER_SIZE, "%ld", int(valoresMqtt[16]));



      if (client1.connected()) client1.publish(topico[j].c_str(), msg);
      if (client2.connected())
      {
        // client2.subscribe(topicoVelocidade.c_str());

      }

      if (client3.connected()) client3.publish(topico[j].c_str(), msg);
    }

  }


  snprintf (msg, MSG_BUFFER_SIZE, "%ld", millis()/1000/60);

  if (client1.connected()) client1.publish(end4.c_str(), msg);
 // if (client2.connected()) client2.publish(end4.c_str(), msg);
  if (client3.connected()) client3.publish(end4.c_str(), msg);



}
