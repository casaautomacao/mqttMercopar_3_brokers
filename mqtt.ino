
void callback1(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");


  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  String teste = topic;


  if (teste == end3)
  {
    setaZeraContagem = 1;


  }


}







void callback2(char* topic, byte* payload, unsigned int length) {
 
  /*
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");


  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
*/


  String teste = topic;

  if (teste == topicoVelocidade)
  {
    int numero = 0;

    for (int i = 0; i < length; i++)
    {
      numero =  numero + ((char)payload[i] - 48) * pow(10, length - 1 - i);

    }

    valoresMqtt[16] = numero;
    delay(100);
  }

}





void callback3(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");


  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  String teste = topic;


  if (teste == end3)
  {
    setaZeraContagem = 1;
  }


}







void reconnect1() {
  // Serial.println("passo 51");
  // Loop until we're reconnected
  if (!client1.connected()) {
    Serial.print("Attempting MQTT Veloxi connection 1...");
    // Create a random client ID
    String clientId = "ESP32_by_CRESCER";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client1.connect(clientId.c_str(), "", "")) {
      Serial.println("connected");


      for (int j = 0; j < quantDados ; j++)
      {
        client1.publish(topico[j].c_str(), "0");
      }

      client1.publish(end4.c_str(), "0");


      client1.subscribe(end3.c_str());



    } else {
      Serial.print("failed, rc=");
      Serial.print(client1.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      //  delay(5000);
    }

  }
}



void reconnect2() {
  // Loop until we're reconnected
  if (!client2.connected()) {
    Serial.print("Attempting MQTT Senai connection 2...");
    // Create a random client ID
    String clientId = "ESP32_by_CRESCER";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client2.connect(clientId.c_str(), "", "")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      for (int j = 0; j < quantDados - 1 ; j++)
      {
        client2.publish(topicoS[j].c_str(), "0");
      }


      client2.publish(end4.c_str(), "0");

      // ... and resubscribe
      client2.subscribe(topicoVelocidade.c_str());


    } else {
      Serial.print("failed, rc=");
      Serial.print(client2.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }

  }
}




void reconnect3() {



  // Loop until we're reconnected
  if (!client3.connected()) {
    //   Serial.print("Attempting MQTT Node-red connection 3...");
    // Create a random client ID
    String clientId = "ESP32_by_CRESCER";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client3.connect(clientId.c_str(), "", "")) {
      //    Serial.println("connected");
      // Once connected, publish an announcement...


      for (int j = 0; j < quantDados ; j++)
      {
        client3.publish(topico[j].c_str(), "0");
      }

      client3.publish(end4.c_str(), "0");

      // ... and resubscribe
      client3.subscribe(end3.c_str());


    } else {
      Serial.print("failed, rc=");
      Serial.print(client3.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      //  delay(5000);
    }
  }

}
