
void preTransmission()
{
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_DE, 0);
}


String nomes[41] = { "Va", "Vb", "Vc", "Ia", "Ib","Ic","x", "PatT","PATa", "PATb", "PATc","PreT", "PRa", "PRb","PRc", "PapT", "PAPa", "PAPb", "PAPc", "FPT", "FPa", "FPb", "FPc", "a", "b", "c", "Fa", "Fb", "Fc", "a", "b", "c", "a", "b", "c", "a", "b", "c", "a", "b", "c"};
                     
                      
                 


String nomeVar(int pos)
{
  return nomes[pos];
}
