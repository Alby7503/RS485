void setup() 
{
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  Serial.begin(9600);
} 
 
void loop() 
{ 
  
  if (Serial.available()) {
    char a = Serial.read();
    Serial.print(a);
    if(a == 'a') 
    {
      tone(6, 1000, 300);
    }
  }
}  
