const int led = 13;
const int TxRx = 7;
bool mode = false; // HIGH = Tx; LOW = Rx

const char START = 1; // SOH (Start of Header)
const char OK = 6;    // ACK (Acknowledge)
const char END = 4;   // EOT (End of Transmission)

void setup()
{
    pinMode(led, OUTPUT);
    pinMode(TxRx, OUTPUT);
    digitalWrite(TxRx, LOW);
    Serial.begin(9600);
}

void loop()
{
    delay(random(1000, 8000));
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        if (c == START)
        {
            transmit();
            Serial.write(OK);
            receive();
            String msg = Serial.readStringUntil(END);
            // Test
            if (msg == "LED")
            {
                digitalWrite(led, HIGH);
                delay(1000);
                digitalWrite(led, LOW);
            }
        }
    }
    else
    {
        do
        {
            transmit();
            Serial.write(START);
            receive();
            delay(150);
        } while (Serial.read() != OK);
        Serial.print("LED");
        Serial.write(END);
    }
    delay(50);
}

void receive(){
    mode = LOW;
    digitalWrite(TxRx, mode);
}

void transmit(){
    mode = HIGH;
    digitalWrite(TxRx, mode);
}