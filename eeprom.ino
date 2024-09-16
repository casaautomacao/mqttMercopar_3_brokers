

void salvaLong(int endereco, long grava) // endereco inicial
{

  Serial.println("   GRAVA EEPROM  ");

  byte hihi = grava /  16777216;
  byte hi = (grava  -  hihi * 16777216 ) / 65536;
  byte lo = (grava  -  hihi * 16777216 - hi * 65536) / 256;
  byte lolo = grava  -  hihi * 16777216 - hi * 65536 - hi * 256;
  EEPROM.write(endereco, hihi);
  EEPROM.write(endereco + 1, hi);
  EEPROM.write(endereco + 2, lo);
  EEPROM.write(endereco + 3, lolo);

   delay(1);
 EEPROM.commit();
 delay(10);
}


long leLong(int endereco) // endereco inicial
{
  byte hihi = EEPROM.read(endereco);
  byte hi = EEPROM.read(endereco + 1);
  byte lo = EEPROM.read(endereco + 2);
  byte lolo = EEPROM.read(endereco + 3);
 // Serial.println("   LEITURA EEPROM  ");
 // Serial.println(hihi * 16777216 + hi * 65536 + lo * 256 + lolo);

  return hihi * 16777216 + hi * 65536 + lo * 256 + lolo;
}
