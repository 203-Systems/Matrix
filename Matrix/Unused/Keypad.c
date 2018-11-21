//74HC164
#define SI PB12
#define CLKI PB13

//74HC165
#define SO PA8
#define LOAD PB15
#define CLKO PB14

byte input;

bool cache[8][8];


void setup() {

  pinMode(SI, OUTPUT);
  pinMode(CLKI, OUTPUT);

  pinMode(LOAD, OUTPUT);
  pinMode(CLKO, OUTPUT);
  pinMode(SO, INPUT);

}

bool Scan() {

  for (int x = 0; x < 8; x++) //for 0 - 7 do
  {
    shiftOut(SI, CLKI, MSBFIRST, 1 << x); // bit shift a logic high (1) value by i
    digitalWrite(LOAD, LOW);
    digitalWrite(LOAD, HIGH);

    digitalWrite(CLKO, LOW);
    digitalWrite(LOAD, LOW);
    digitalWrite(LOAD, HIGH);

    for (int y = 0; y < 8; y++)
    {
      digitalWrite(CLKO, LOW);
      if (digitalRead(SO) != cache[x][y]) {
        if (digitalRead(SO)) {
          Serial.print(x * 10 + y);
          Serial.println( "\tOn");
        } else {

        }
        cache[x][y] = digitalRead(SO);
      }
      digitalWrite(CLKO, HIGH);
    }
    //delay(200);
  }
}
