int flow_pin=2;
int valve_pin=3;
double flow_rate;
double volume=0.0;
volatile int count=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(flow_pin,INPUT);
  pinMode(valve_pin,OUTPUT);
  attachInterrupt(0,Flow,RISING);
digitalWrite(valve_pin,HIGH);
  
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  count=0;
  interrupts();
  delay(100);
  noInterrupts();
  flow_rate=count/77.5;
  volume=volume+(flow_rate*1);
  Serial.println(String(flow_rate)+"round/100 milli");
  Serial.println("total volume =="+String(volume)+"\n");
  if(volume>10){
    volume=0.0;
    digitalWrite(valve_pin,HIGH);
//    Serial.println(String(volume)+);
    }

}

void Flow(){
  count++;
}
