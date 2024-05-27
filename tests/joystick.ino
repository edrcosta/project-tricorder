#define joyX A0
#define joyY A1
 
int xMap, yMap, xValue, yValue;
 
void setup() {
  Serial.begin(9600);
 
}
 
void loop() {
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  xMap = map(xValue, 0,1023, 0, 7);
  yMap = map(yValue,0,1023,7,0);

 Serial.print("x:");
 Serial.print(joyX);
 Serial.print(" y:");
 Serial.println(joyY);
}