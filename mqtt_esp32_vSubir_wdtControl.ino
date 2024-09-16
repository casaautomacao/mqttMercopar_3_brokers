String dispositivo = "crescer2"; // 1 será painele veloxi  - 2 será Senai, painel e veloxi

int vetorIn[3]={39,34,35};

long contaPecaPersonal = 0;
long contaPecaCoringa = 0;

String topicoVelocidade = "mercopar/hero/velocidadedacelula";

#include <ESPmDNS.h>
#include <Crescer.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>
#include <ModbusMaster.h>
#include <EEPROM.h>

//#define MAX485_DE      33 // placa branca
#define MAX485_DE      2 // placa preta


#define quantDados 17

String fimTopico[quantDados] = { "fase01V",
                                 "fase02V",
                                 "fase03V",
                                 "fase01I",
                                 "fase02I",
                                 "fase03I",
                                 "faseTotP",
                                 "fase01P",
                                 "fase02P",
                                 "fase03P",//10
                                 "fase01FP",
                                 "fase02FP",
                                 "fase03FP",
                                 "status_celula",
                                 "cont_pc_corin",
                                 "cont_pc_perso",
                                 "velocidade_celula" //17
                               };

float valoresMqtt[quantDados];


String topico[quantDados];
String topicoS[quantDados];

ModbusMaster Eletricas;


#include <ETH.h>

Tempora tempReconec;
Tempora printDebug;
Tempora tempWdt;

// Update these with values suitable for your network.

const char* ssid = "crescer";
const char* password = "cpb32832";
const char* mqtt_server = "";
const char* mqtt_server2 = "";
const char* mqtt_server3 = "192.168.100.114";

WiFiClient espClient1;
WiFiClient espClient2;
WiFiClient espClient3;
PubSubClient client1(espClient1);
PubSubClient client2(espClient2);
PubSubClient client3(espClient3);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE	(50)
char msg[MSG_BUFFER_SIZE];
char msg2[MSG_BUFFER_SIZE];
int value = 0;

IPAddress print_IP(0, 0, 0, 0);

// Tipo de Ethernet PHY
#define ETH_TYPE ETH_PHY_LAN8720
#define ETH_ADDR 0
#define ETH_PHY_ADDR 1

#define ETH_CLK_MODE ETH_CLOCK_GPIO0_IN
static bool eth_connected = false;


String end3;
String end4;
int setaZeraContagem = 0;

TaskHandle_t core0;
TaskHandle_t core1;

 int status34;
  int status34Old;

  int status35;
  int status35Old;


void setup() {

for(int i=0;i<3;i++)
{
  pinMode(vetorIn[i], INPUT);
}



  // pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  // Init in receive mode
  //  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);


  Serial.begin(115200);
  tempReconec.defiSP(10000);
   Serial.println();
    Serial.println();
     Serial.println();
      Serial.println();
      
  Serial.println("oi");
 Serial.println();
  Serial.println();
   Serial.println(); 
   Serial.println();
 EEPROM.begin(1024);
  Serial2.begin(9600, SERIAL_8N1);
  // Modbus slave ID 1
  Eletricas.begin(1, Serial2);

  Eletricas.preTransmission(preTransmission);
  Eletricas.postTransmission(postTransmission);


   status34 = digitalRead(34);
   status34Old = status34;

   status35 = digitalRead(35);
   status35Old = status35;
printDebug.defiSP(2000);




tempWdt.defiSP(1000);

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
    core0code,   /* Task function. */
    "core0",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &core0,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
 //  delay(500);

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
    core1code,   /* Task function. */
    "core1",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &core1,      /* Task handle to keep track of created task */
    1);          /* pin task to core 1 */


// eth_speed_t speed = ETH_SPEED_10M;
  //  esp_eth_ioctl(eth_handle, ETH_CMD_S_SPEED, &speed);

  ETH.begin( 1 , 32, 14, 4 , ETH_PHY_LAN8720);

  otaSetup();
  Serial.println("passo 1");


  MDNS.begin(dispositivo);

contaPecaPersonal = leLong(0);
contaPecaCoringa = leLong(4);

  for (int j = 0; j < quantDados ; j++)
  {
    topico[j] = "br/com/cmcontrol/dispositivo/" + dispositivo + "/set/evento/registrar/" + fimTopico[j];
  }

 for (int j = 0; j < quantDados ; j++)
  {
    topicoS[j] = "mercopar/creser/" + fimTopico[j];
  }


 // end3 = "br/com/cmcontrol/dispositivo/" + dispositivo + "/get/evento/registrar/fase01V";
   end3 = "br/com/cmcontrol/dispositivo/" + dispositivo + "/set/evento/registrar/zera_contagem";
    end4 = "br/com/cmcontrol/dispositivo/" + dispositivo + "/set/evento/registrar/tempo_sem_reset";

  // setup_wifi();
  client1.setServer(mqtt_server, 1883);
  client1.setCallback(callback1);

  Serial.println("passo 2");

  if (dispositivo == "crescer2")  client2.setServer(mqtt_server2, 2883);
  if (dispositivo == "crescer2")  client2.setCallback(callback2);


  Serial.println("passo 3");
  client3.setServer(mqtt_server3, 1883);
  client3.setCallback(callback3);
  Serial.println("passo 4");
  Serial.println("passo 5");




  delay(4000);

}

void loop() {
 

/*


*/



}
