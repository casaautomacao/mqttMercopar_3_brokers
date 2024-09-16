



void printDebugF()
{

  if (printDebug.Saida(1))

  {


 Serial.print("Peça Pernalizada: ");

 Serial.print(contaPecaPersonal);

  Serial.print("  - Peça Coringa: ");
   Serial.print(contaPecaCoringa);

 Serial.print("  - IP: ");
   Serial.print(ETH.localIP());

Serial.print("  - seg rod: ");
   Serial.print(millis()/1000);

      
 Serial.println();
  
  printDebug.Saida(0);
  }
  

}
