void setup()
{
  UCSR0B |= (1 << TXCIE0);   // TX Complete Interrupt Enable 0
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  Serial.begin(9600);
}

ISR (USART_TX_vect)
{
  digitalWrite(3, LOW);
}

void loop()
{
  digitalWrite(3, HIGH);
  Serial.write('a');
  delay(2500);
}
