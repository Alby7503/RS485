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
    String msg = Serial.readString();
    Serial.println(msg);
    if(msg == "test") 
    {
      tone(6, 1000, 300);
    }
  }
}  
