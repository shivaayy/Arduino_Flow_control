int flow_pin=2;
int pump=6;

double flow_rate;
double volume=0.0;
volatile int count=0;

double set_volume=1.0;
unsigned long old_time=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(flow_pin,INPUT);

  pinMode(pump,OUTPUT);

  digitalWrite(pump,HIGH);

  attachInterrupt(0,Flow,FALLING);
  
  
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  int open_500 = analogRead(A0);
//  delay(500);
//  Serial.println("value of 500 ml button == "+String(open_500));
//Serial.println("a   "+String(open_500));

  if(open_500>1000){
    delay(500);
    count=0;
    attachInterrupt(0,Flow,FALLING);
    
    
    digitalWrite(pump,LOW);
    old_time=millis();
    Serial.println("--------------------- motor onnnnnnnnnnnnnnnn--------------");
    set_volume=500.0;
    volume=0.0;
    Serial.println("------------------------------ measuring  500 ml -----------------------");
    

  }

  int open_1000 = analogRead(A2);
//  delay(500);
//  Serial.println("value of 1000 ml button == "+String(open_1000));
//Serial.println("b   "+String(open_1000));
  if(open_1000>1000){
    delay(500);
    count=0;
    attachInterrupt(0,Flow,FALLING);
    digitalWrite(pump,LOW);
    old_time=millis();
        Serial.println("--------------------- motor onnnnnnnnnnnnnnnn--------------");

    set_volume=1000.0;
    volume=0.0;
    Serial.println("------------------------------ measuring  1000 ml -----------------------");

  }


int temp=millis()-old_time;
    Serial.println("temp "+String(temp));


  if(temp>50){
    detachInterrupt(0);
    flow_rate=(count*2.2)/temp;  // ml/ms     (count*1000.0*1000)/(temp*7.5*60000)
    count=0;
    old_time=millis();
    
    attachInterrupt(0,Flow,FALLING);

    Serial.println("flow rate ------------========= "+String(flow_rate)+"  ml / ms");
    volume=volume+(flow_rate*temp);
    
    Serial.println("volume =================================================== "+String(volume));
    if(volume>=set_volume){
      digitalWrite(pump,HIGH);
          Serial.println("--------------------- motor offfffffffffffffffffffffffffffffffffff--------------");

      
      }
    
  }

//   int delay_time=100;
//   count=0;
//   interrupts();
//   delay(delay_time);
//   noInterrupts();
  

// // calibrated in 200 ms with 11-12 round per 200 ms 
// Serial.println("Count per as per delay time  "+String(count)+" per "+String(delay_time)+"  ms");
// if(digitalRead(pump)==0){
//    flow_rate=(2.28434783*count)/delay_time;  // ml/ms
//   volume=volume+(flow_rate*delay_time);

 
//   }
//  Serial.println("flow rate "+String(flow_rate*1000)+"   ml/second");
//   Serial.println("total volume =="+String(volume)+"\n");

//   if(volume>=set_volume){
//     volume=0.0;
//     digitalWrite(pump,HIGH);

//     Serial.println("------------- motor filled----"+String(set_volume)+" ml fluid filled  -------------");
// //    Serial.println(String(volume)+);
//     }

}

void Flow(){
  count++;
}
