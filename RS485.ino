const int led = 13;
const int buzzer = 6;
#define TxRx 3
bool mode = LOW; // HIGH = Tx; LOW = Rx

const char START = 44; // 1; // SOH (Start of Header)    ,
const char OK = 43;    // 6;    // ACK (Acknowledge)     +
const char END = 35;    // EOT (End of Transmission)     #

void beep(int times = 1) {
  tone(buzzer, 1000, 300);
}

/*ISR (USART_TX_vect)
{
  digitalWrite(TxRx, LOW);
}*/

void setup()
{
  //UCSR0B |= (1 << TXCIE0);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TxRx, OUTPUT);
  pinMode(buzzer, OUTPUT);
  beep();
  receive();
  Serial.begin(9600);
}

void loop()
{
  delay(random(200, 500));
  receive();
  if (Serial.available() > 0)
  {
    char c = Serial.read();
    if (c == START)
    {
      Send(OK);
      //receive();
      String msg = Serial.readStringUntil(END);
      Serial.print(msg); //debug;
      // Test
      if (msg == "LED")
      {
        //beep();
        digitalWrite(LED_BUILTIN, HIGH);
        delay(1000);
        digitalWrite(LED_BUILTIN, LOW);
      }
    }
  }
  else
  {
    return;
    char temp;
    do
    {
      Send(START);
      receive();
      temp = Serial.read();
      if (temp == START)
      {
        return;
      }
      delay(150);
    } while (temp != OK);
    Send("LED");
    Send(END);
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

void Send(String message){
  transmit();
  Serial.print(message);
  Serial.flush();
}

void Send(char message){
  transmit();
  Serial.write(message);
  Serial.flush();
}
