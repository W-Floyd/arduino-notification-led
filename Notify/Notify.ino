int light = 1;

char serInString[100];
int  serInIndx  = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int ledArray[6] = {3, 5, 6, 9 , 10, 11};

// the setup routine runs once when you press reset:
void setup() {

  Serial.begin(9600);

  for ( int i = 0; i < 6; i++ ) {
    pinMode(ledArray[i], OUTPUT);
  }

}

void loop () {



}

void serialEvent() {

  // light,fade_time,pulses,brightness
  // 0,500,3,255


  delay (50);

  String inputString = readSerialString();

  Serial.println("Received serial command, containing: " + inputString);

  int commaIndex = inputString.indexOf(',');
  int secondCommaIndex = inputString.indexOf(',', commaIndex + 1);
  int thirdCommaIndex = inputString.indexOf(',', secondCommaIndex + 1);

  // Pin number to light up
  String lightNum = inputString.substring(0, commaIndex);

  int light = 5;

  light = lightNum.toInt();

  Serial.println("Light number " + String(light));

  // Milliseconds per pulse
  String fadeLevel = inputString.substring(commaIndex + 1, secondCommaIndex);

  int fade = 100;

  fade = fadeLevel.toInt();

  Serial.println("Fading for " + String(fade) + " milliseconds");

  // Number of pulses to perform
  String pulseNum = inputString.substring(secondCommaIndex + 1); // To the end of the string

  int num = 2;

  num = pulseNum.toInt();

  Serial.println(String(num) + " pulse(s)");

  // Brightness of light
  String brightNum = inputString.substring(thirdCommaIndex + 1); // To the end of the string

  int bright = 255;

  bright = brightNum.toInt();

  Serial.println("Brightness level " + String(bright));

  pulse(light, fade, num, bright);

}

void pulse (int light, int fade, int num, int bright) {

  for (int i = 1; i <= num; i++) {

    blip(light, fade, bright);

  }

}

void blip (int light, int fade, int bright) {

  float waitTimeMicro = ( ( float(fade) / float(bright) ) / 2) * 1000;

  for (int i = 0; i <= bright; i++) {
    analogWrite(ledArray[light], i);
    customDelay(waitTimeMicro);
  }

  for (int i = bright; i >= 0; i--) {
    analogWrite(ledArray[light], i);
    customDelay(waitTimeMicro);
  }

}

void customDelay (float micro) {
  if ( micro < 10000 ) {
    delayMicroseconds(micro);
  } else {
    delay(float(micro) / float(1000));
  }
}

String readSerialString () {
  char ch;
  String input;
  while (Serial.available()) {
    ch = Serial.read();
    if ( ch == '-' ) {
      Serial.println("Breaking reading");
      break;
    }

    input += ch;

    while (! Serial.available()) {
      delay (10);
    }

  }
  return input;
}
// 0,500,3,255-1,500,3,255

