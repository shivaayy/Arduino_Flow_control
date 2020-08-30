int flow_pin=2;
int valve_pin=3;
int ml_500=4;
int ml_1000=5;
int pump=6;

double flow_rate;
double volume=0.0;
volatile int count=0;

double set_volume=0.0;

void setup() {
  // put your setup code here, to run once:
  pinMode(flow_pin,INPUT);
  pinMode(valve_pin,OUTPUT);
  pinMode(ml_500,INPUT);
  pinMode(ml_1000,INPUT);
  pinMode(pump,OUTPUT);
  pinMode(3,OUTPUT);
  digitalWrite(3,HIGH);
  digitalWrite(ml_500,LOW);
  digitalWrite(ml_1000,LOW);
  degitalWrite(pump,HIGH);

  attachInterrupt(0,Flow,RISING);
  // digitalWrite(valve_pin,HIGH);
  
  Serial.begin(9600);
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int open_500 = digitalRead(ml_500);
  if(open_500){
    degitalWrite(pump,LOW);
    set_volume=500.0;
    volume=0.0;
    Serial.println("------------------------------ measuring  500 ml -----------------------");

  }

  int open_1000 = digitalRead(ml_1000);
  if(open_1000){
    degitalWrite(pump,LOW);
    set_volume=1000.0;
    volume=0.0;
    Serial.println("------------------------------ measuring  1000 ml -----------------------");

  }

  int delay_time=200;
  count=0;
  interrupts();
  // delay(200);
  noInterrupts();
  

// calibrated in 200 ms with 11-12 round per 200 ms 

  flow_rate=(2.28434783*count)/delay_time;  // ml/ms
  volume=volume+(flow_rate*delay_time);

  
  Serial.println("Count per as per delay time"+String(count)+" per "+String(delay_time)+"  ms");
  Serial.println("flow rate "+String(flow_rate*1000)+"   ml/second");
  Serial.println("total volume =="+String(volume)+"\n");

  if(volume>=set_volume){
    volume=0.0;
    digitalWrite(pump,HIGH);

    Serial.println("------------- motor filled----"+String(set_volume)+" ml fluid filled  -------------");
//    Serial.println(String(volume)+);
    }

}

void Flow(){
  count++;
}
