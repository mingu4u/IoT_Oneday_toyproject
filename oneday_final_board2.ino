
const int BUTTON_PIN = 13;

int digits [10][7]{
{1,1,1,1,1,1,0}, // digit 0
{0,1,1,0,0,0,0}, // digit 1
{1,1,0,1,1,0,1}, // digit 2
{1,1,1,1,0,0,1}, // digit 3
{0,1,1,0,0,1,1}, // digit 4
{1,0,1,1,0,1,1}, // digit 5
{1,0,1,1,1,1,1}, // digit 6
{1,1,1,0,0,0,0}, // digit 7
{1,1,1,1,1,1,1}, // digit 8
{1,1,1,1,0,1,1} // digit 9
};


void displayDigit(int d) {
if (digits[d][0]==1) digitalWrite(2, HIGH); else digitalWrite(2, LOW); //A
if (digits[d][1]==1) digitalWrite(3, HIGH); else digitalWrite(3, LOW); //B
if (digits[d][2]==1) digitalWrite(4, HIGH); else digitalWrite(4, LOW); //C
if (digits[d][3]==1) digitalWrite(5, HIGH); else digitalWrite(5, LOW); //D
if (digits[d][4]==1) digitalWrite(6, HIGH); else digitalWrite(6, LOW); //E
if (digits[d][5]==1) digitalWrite(7, HIGH); else digitalWrite(7, LOW); //F
if (digits[d][6]==1) digitalWrite(8, HIGH); else digitalWrite(8, LOW); //G
}

float roundFloat(float number, int decimalPlaces) {
  float multiplier = pow(10, decimalPlaces);
  return round(number * multiplier) / multiplier;
}


void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);// Segment A
  pinMode(3, OUTPUT);// Segment BS
  pinMode(4, OUTPUT);// Segment C
  pinMode(5, OUTPUT);// Segment D
  pinMode(6, OUTPUT);// Segment E
  pinMode(7, OUTPUT);// Segment F
  pinMode(8, OUTPUT);// Segment G
  pinMode(BUTTON_PIN, INPUT); //BUTTON
}

void loop() {	
  if (Serial.available()) {
   int number = Serial.read();
    int rounded = roundFloat(1+(1+number)/3, 0);
    Serial.println(rounded);
    displayDigit(rounded);
	}
}


