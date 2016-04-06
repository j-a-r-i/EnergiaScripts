//#include <lcd.h>
#include <OneWire.h>

//lcd     disp(P1_6, P1_7);
OneWire ds(P1_4);

byte cntLoop = 0;
byte cntMeas = 0;
byte cntSensors = 0;
byte addr1[8];
byte addr2[8];
byte data[10];

//byte wday = 0;
//byte hour = 0;
//byte min  = 0;
//byte sec  = 0;

//---------------------------------------------------------------
void setup()
{
  // put your setup code here, to run once:
  P1DIR |= (BIT0 + BIT6);
  P1OUT |= BIT0;

  Serial.begin(9600);
  //disp.begin(16, 2);
  //Serial.println("Running");
  
  if (ds.search(addr1)) {
    Serial.print(addr1[0], HEX);
    Serial.print(addr1[1], HEX);
    Serial.print(addr1[2], HEX);
    Serial.print(addr1[3], HEX);
    Serial.println(addr1[4], HEX);
    cntSensors = 1;
  }
  else {
    Serial.println("E01");
  }
  
  if (ds.search(addr2)) {
    Serial.print(addr2[0], HEX);
    Serial.print(addr2[1], HEX);
    Serial.print(addr2[2], HEX);
    Serial.print(addr2[3], HEX);
    Serial.println(addr2[4], HEX);
    cntSensors = 2;
  }
  else {
    Serial.println("E02");
  }
}

//---------------------------------------------------------------
void loop()
{
  byte i;
  //unsigned int time = (unsigned int)(millis()/1000);
  
  switch (cntLoop) {
    case 0:
      ds.reset();
      ds.select(addr1);
      ds.write(0x44, 0);  // start conversion
      break;
      
    case 1:
  //delay(800);        // up to 750ms
      ds.depower();
      ds.reset();
      ds.select(addr1);
      ds.write(0xBE, 0);  // Read scratchpad

      for (i=0; i<9; i++) {
        data[i] = ds.read();
      }
      break;
      
    case 2:
      //disp.setCursor(0,1);   // to second line
      //disp.print(time);
      //disp.print(counter);
      //disp.setCursor(7,1);
      //disp.print( (data[1]<<8) | data[0]);
      break;
      
    case 3:
      cntMeas++;
      Serial.print('m');
      Serial.print(cntMeas, HEX);
      Serial.print(' ');
      Serial.print( (data[1]<<8) | data[0], HEX );
      Serial.print(' ');
      Serial.print(0x00, HEX);
      Serial.print(' ');
      Serial.println(0x00, HEX);
      break;
      
    case 4:
      //P1OUT ^= BIT0;
      P1OUT ^= BIT6;
      break;
  }
  
  if( Serial.available() > 0 ) {
    //Serial.println("r");
    P1OUT ^= BIT0;
    //byte cmd = (byte)Serial.read();
    //byte arg = (byte)Serial.read();
    
    /*switch(cmd) {
      case 1:
        Serial.println("c1");
        if (arg)
          P1OUT |= BIT0;
        else
          P1OUT &= ~BIT0;
        break;

      case 2:
        Serial.println("c2");
        if (arg)
          P1OUT |= BIT6;
        else
          P1OUT &= ~BIT6;
        break;
        
      default:
        Serial.println("c??");
        break;
    }*/
  }
  
  cntLoop++;
  if (cntLoop == 20)
    cntLoop=0;
    
  sleepSeconds(1);
}

