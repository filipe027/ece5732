void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  

}
char a;
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial1.available()){
    a = Serial1.read();
    Serial.println(a);
  }
}
