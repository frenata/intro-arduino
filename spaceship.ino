struct Light {
  int n;  // pin position
  int on; // turn it on?
  unsigned long lastOn; // time it was last turned on
  long until;  // random interval until it should be turned on
};

// global list of lights
const int N_LIGHTS = 6;
Light pins[N_LIGHTS];

int shouldBlink = LOW;

long genInterval() {
  return random(50,1000);
}

Light makeLight(int n) {
  return Light{n, LOW, 0, genInterval()};
}

void setup() {
  //randomSeed(analogRead(0));
  pins[0] = makeLight(7);
  pins[1] = makeLight(8);
  pins[2] = makeLight(9);
  pins[3] = makeLight(10);
  pins[4] = makeLight(11);
  pins[5] = makeLight(12);

  // pins
  pinMode(2, INPUT);  // push-button
  pinMode(3, OUTPUT); // ready indicator

  for (int i=0; i<N_LIGHTS; i++)
    pinMode(pins[i].n, OUTPUT);
}

void flipLight(int i) {
  unsigned long now = millis();

  if (now > pins[i].lastOn + pins[i].until) { // toggle
    pins[i].lastOn = now;
    pins[i].until = genInterval();
    pins[i].on ^= 1;
  }
  digitalWrite(pins[i].n, pins[i].on);
}

void loop() {
  if(digitalRead(2)) {
    delay(250);
    shouldBlink ^= 1;
  }

  if(shouldBlink == LOW) { // reset
    digitalWrite(3, HIGH);
    for(int i=0; i<N_LIGHTS; i++)
      digitalWrite(pins[i].n, LOW);
  } else {
    digitalWrite(3, LOW);
    for(int i=0; i<N_LIGHTS; i++)
      flipLight(i);
  }
}
