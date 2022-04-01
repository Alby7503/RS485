void setup()
{
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  Serial.begin(9600);
}

void loop()
{
  Serial.print("test");
  Serial.flush();
  delay(2500);
}
