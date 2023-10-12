#include <Servo.h>
Servo servo;
const int floor_LED[] = {7,8,9,10,11,12,13};
const int call_LED[] = {4,5,6};
const int button[] = {14,15,16};
const int buzzor = 2;
int frequency[] = {2217,2489,2794};

int currentFloor = 1;
int targetFloor = 1; 
int finalFloor = 1;
bool movingUp = false;
bool movingDown = false;
bool stop = true;

int currentLED = 0;
int callLED_floor = 1;
int currentCheck = 1;
int targetCheck = 1;
int savedCheck = 1;
int timecheck = 0;
int pastTime;



// 입력받은 호출 층 수를 LED로 표시하기 위한 함수
void CallLED_func(int idx,int saved) {
	for (int i=0; i<3; i++) {
      if (idx == i) {
    	digitalWrite(call_LED[i],HIGH);
        }
      else if (saved == i+1) {
    	digitalWrite(call_LED[i],HIGH);      
      }
      else {
      	digitalWrite(call_LED[i],LOW);
      	}
      
	}
}

// 7Segment에 현재 층 정보를 정수로 반올림 해 나타내기 위한 함수
float roundFloat(float number, int decimalPlaces) {
  float multiplier = pow(10, decimalPlaces);
  return round(number * multiplier) / multiplier;
}









void setup() {
  // pinMode 및 각 입력 핀 설정
  Serial.begin(9600);
  servo.attach(3);
  for (int i=0; i<7; i++) {
  pinMode(floor_LED[i], OUTPUT);
  }
  for (int i=0; i<3; i++) {
  pinMode(call_LED[i], OUTPUT);
  }
  for (int i=0; i<3; i++) {
  pinMode(button[i], INPUT);
  }
  pinMode(buzzor, OUTPUT);
  servo.write(0);
}








void loop() {
  // 계속해서 목표 층 수를 받음.
  for (int i=0;i<3;i++) {
    int State = 0;
    State = digitalRead(button[i]);
    if (State==HIGH) {
      stop = true;
      targetFloor = i+1;
      savedCheck = 3*(targetFloor-1)+1;
      break;
      }
  }
  servo.write(currentLED*30);
  Serial.write(currentLED);
  // 현재 층과 위치를 비교해서 위로 갈지, 아래로 갈지 판별함.
  if (targetCheck > currentCheck) {
    movingUp = true;
    movingDown = false;
    callLED_floor = targetFloor;
    stop = false;
  }
  else if (targetCheck < currentCheck) {
    movingUp = false;
    movingDown = true;
    callLED_floor = targetFloor;
    stop = false;
  }
  else {
    stop = true;
    targetCheck = savedCheck;
    finalFloor = targetFloor;
  }

  // LED를 순차적으로 켜고 끄며 엘리베이터 동작을 표시함.
  // 위로 올라갑니다.
  if (movingUp == true & stop == false) {
    currentFloor = int(1+((1+currentLED)/3));
    CallLED_func(callLED_floor-1,finalFloor);
    // digitalWrite(call_LED[targetFloor-1],HIGH);
    digitalWrite(floor_LED[currentLED],HIGH);
    if (timecheck == 0) {
    pastTime = millis();
    timecheck = 1;
    }
    // 150ms간격으로 진행 (비차단 방식, 지연 x)
    if (timecheck == 1) {
    	if (millis() - pastTime > 150) {
    // delay(500);
    digitalWrite(floor_LED[currentLED],LOW);
    currentLED++;
    currentCheck++;
    timecheck=0;
    	}
    }
  }
  
  // 아래로 내려갑니다.
  if (movingDown == true & stop == false) {
    currentFloor = int(1+((1+currentLED)/3));
    CallLED_func(callLED_floor-1, finalFloor);
    digitalWrite(floor_LED[currentLED],HIGH);
    if (timecheck == 0) {
    pastTime = millis();
    timecheck = 1;
    }
    // 150ms간격으로 진행 (비차단 방식, 지연 x) 
    if (timecheck == 1) {
    if (millis() - pastTime > 150) {
    // delay(500);
    digitalWrite(floor_LED[currentLED],LOW);   
    currentLED--;
    currentCheck--;
    timecheck=0;
    }
    }
  }
  
  // 목표 층과 현재 층이 일치한 상태
  if (stop == true) {
    if (timecheck == 0) {
    pastTime = millis();
      for (int i=1;i<=3;i++) {
      if (currentFloor == i) {
    tone(buzzor,frequency[i-1],50);
    timecheck = 1;
        break;
      }
      }
    }
    currentFloor = int(1+((1+currentLED)/3));
    digitalWrite(call_LED[callLED_floor-1],LOW);
    digitalWrite(floor_LED[currentLED],HIGH);
    if (timecheck == 1) {
    if (millis() - pastTime > 50) {
      noTone(buzzor);
    }
    }
    }
}

