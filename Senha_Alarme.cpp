/*Este projeto visa, sem o auxílio de bibliotecas, receber os 
* digitos indicados no Teclado 4x4 pelo usuário, e mostrando no 
* monitor serial se a senha esta correta (realizar uma ação, 
* desligar um 'alarme' com um buzzer), ou errada(Repetir a solicitação de senha e
* manter ligado o alarme)
*/

//Senha Correta
int Senha[8]= {3, 8, //A
               3, 9, //3
               5, 11, //7
               6, 8,}, //D
  Vez =0, SenhaUs[8], a =0, Corre =0, Fr =850;

void setup(){
	
  //Definindo pinos de envio de sinal
  for(int x=3; x<=6; x++){
  	pinMode(x, OUTPUT);
  }
  
  //Definindo pinos de recebimento de sinal
  for(int y=8; y<=11; y++){
  	pinMode(y, INPUT);
  }
  
  //Pino dos LEDs
  pinMode(12, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Iniciando o sistema...");
  Serial.println();
 
}

void loop(){
  
  /*Iniciando as variaveis tirando valores residuais e solicitando a senha */
  Serial.println("Senha:");
  tone(12, Fr);
  Vez =0;
  a=0;
  Corre =0;
  for(int e=0; e<8; e++){
  	SenhaUs[e]=0;
  }
  for(int p =3; p<=6; p++){//Desligando qualquer sinal que ainda esteja sendo enviado de outras vezes que o código foi executado
    digitalWrite(p, LOW);
  }
  
  /*Executar envio e recebimento de sinal nos pinos do teclado enquanto 'Vez' for menor do que 4*/
  do{
  	
  for(int l =3; l<=6; l++){//Seleção do pino para o envio do sinal no teclado
    
    digitalWrite(l, HIGH);//Enviando o sinal para o teclado
    
    for(int z =11; z>=8; z--){//Seleção do pino para o recebimento do sinal do teclado
    
      /*Se o pino 'z' receber energia, isso significa que um digito foi teclado e as ações a seguir serão realizadas*/
      if(digitalRead(z)== HIGH){
      	SenhaUs[a] = l;//Posição 'a' recebe o pino de envio do sinal...
      	
        SenhaUs[a+1] = z;//...E sua sucessora recebe o pino de recebimento do sinal
        
        Vez++;//Mais uma valor teclado
        
        a += 2;//'a' recebe +2 para os proximos valores digitados não ocuparem os anteriores
		 
        Serial.print("*");
        
		delay(550);//Pequeno delay impedindo uma resposta acelerado do compilador que tenderia a completar a senha com a primeira tecla selecionada
      }
           
     }
  	digitalWrite(l, LOW);  
  }
  }while(Vez <4);//Se 'Vez' chegar a 4 isso significa que foram digitados todos os 4 digitos da senha
  
  /*Analise da senha digitada com a senha cadastrada no sistema*/
  for(int q=0; q<8; q++){
    if(Senha[q] == SenhaUs[q]){
    	Corre++;
    }
  }
  if(Corre == 8){//Se a correção foi exata com 8, ou seja senha correta
  	
	Serial.println("\nSenha CORRETA");//Informe ao Usuario
    
	noTone(12);//LEDs Ligados
    
	delay(5000);//5s antes de reiniciar o sistema
    
    Serial.println("\nReiniciando Sistema...");
  	delay(300);
    
  }else{//Se não
  	Serial.println("\nSenha INCORRETA");//O usuário é informado e nenhuma outra ação é executada
  }
}


