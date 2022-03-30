const int led = 13;
const int buzzer = 6;
#define TxRx 3
bool mode = LOW; // HIGH = Tx; LOW = Rx

const char START = 44; // 1; // SOH (Start of Header)
const char OK = 43;    // 6;    // ACK (Acknowledge)
const char END = 35;    // EOT (End of Transmission)

void beep(int times = 1) {
  tone(buzzer, 1000, 300);
}

ISR (USART_TX_vect)
{
  digitalWrite(TxRx, LOW);
}

void setup()
{
  UCSR0B |= (1 << TXCIE0);
  pinMode(led, OUTPUT);
  pinMode(TxRx, OUTPUT);
  pinMode(buzzer, OUTPUT);
  beep();
  receive();
  Serial.begin(9600);
}

void loop()
{
  delay(random(200, 500));
  //receive();
  if (Serial.available() > 0)
  {
    char c = Serial.read();
    if (c == START)
    {
      transmit();
      Serial.write(OK);
      //receive();
      String msg = Serial.readStringUntil(END);
      // Test
      if (msg == "LED")
      {
        //beep();
        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(led, LOW);
      }
    }
  }
  else
  {
    char temp;
    do
    {
      transmit();
      Serial.write(START);
      //receive();
      temp = Serial.read();
      if (temp == START)
      {
        return;
      }
      delay(150);
    } while (temp != OK);
    Serial.print("LED");
    Serial.write(END);
  }
}

void receive()
{
  mode = LOW;
  digitalWrite(TxRx, LOW);
  delay(200);
}

void transmit()
{
  mode = HIGH;
  digitalWrite(TxRx, HIGH);
  delay(200);
}
