#define TxRx 3

bool turn = false;
int cont = 1;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  Serial.setTimeout(5000);
  delay(random(10, 500));
  if (Serial.available() > 0) {
    Serial.read();
  } else {
    Send(0);
    turn = true;
  }
}

void loop() {
  if (!turn) {
    cont = WaitReceive();
    for (int i = 0; i < cont; i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(250);
      digitalWrite(LED_BUILTIN, LOW);
      delay(250);
    }
  } else {
    Send(cont++);
    delay(500);
  }
  turn = !turn;
}

void Send(int number) {
  digitalWrite(TxRx, HIGH);
  Serial.print(number);
  Serial.flush();
  digitalWrite(TxRx, LOW);
}

int WaitReceive() {
  while (Serial.available() < 0) delay(50);
  return Serial.parseInt();
}
