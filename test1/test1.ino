int temp1 = 0;
int temp2 = 0;

//----------------------------------------------------------
void setup()
{
  pinMode(RED_LED, OUTPUT);
  Serial.begin(9600);
}

//----------------------------------------------------------
void loop()
{
  temp1++;

  Serial.print(temp1);
  Serial.print(',');
  Serial.print(temp2);
  
  digitalWrite(RED_LED, HIGH);
  delay(1000);
  digitalWrite(RED_LED, LOW);
  
  delay(5000);  // 5 sec
}
