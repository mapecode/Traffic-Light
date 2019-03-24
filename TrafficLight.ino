  #define GREEN_TRAFFIC       0       /*State 0*/
  #define YELLOW_TRAFFIC      1       /*State 1*/
  #define RED_TRAFFIC         2       /*State 2*/
  #define GREEN_PEOPLE        3       /*State 3*/
  #define RED_PEOPLE          4       /*State 4*/

  #define BUTTON_PIN          2
  #define RED_PEOPLE_PIN      3
  #define GREEN_PEOPLE_PIN    4
  #define GREEN_TRAFFIC_PIN   5
  #define YELLOW_TRAFFIC_PIN  6
  #define RED_TRAFFIC_PIN     7
  
  #define DELAY               1000    /*MiliSeconds Delay*/
  
  int state=GREEN_TRAFFIC & RED_PEOPLE;
  int start=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(GREEN_TRAFFIC_PIN,OUTPUT);
  pinMode(YELLOW_TRAFFIC_PIN,OUTPUT);
  pinMode(RED_TRAFFIC_PIN,OUTPUT);
  pinMode(GREEN_PEOPLE_PIN,OUTPUT);
  pinMode(RED_PEOPLE_PIN,OUTPUT);
  pinMode(BUTTON_PIN,INPUT);
  
  digitalWrite(GREEN_TRAFFIC_PIN,HIGH);
  digitalWrite(RED_PEOPLE_PIN,HIGH);
}

void intermitent(int pin){
  int i;
  for(i=0;i<3*2;i++){
    digitalWrite(pin,HIGH);
    delay(0.25*DELAY);
    digitalWrite(pin,LOW);
    delay(0.25*DELAY);
  }
  digitalWrite(pin,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(BUTTON_PIN)==HIGH){
    start=1;
    while(start==1){
      switch(state){
         case GREEN_TRAFFIC & RED_PEOPLE:
           delay(3*DELAY);
           digitalWrite(GREEN_TRAFFIC_PIN,LOW);
           state=YELLOW_TRAFFIC;
           break;
         case YELLOW_TRAFFIC:
           digitalWrite(YELLOW_TRAFFIC_PIN,HIGH);
           delay(3*DELAY);
           digitalWrite(YELLOW_TRAFFIC_PIN,LOW);
           digitalWrite(RED_PEOPLE_PIN,LOW);
           state = RED_TRAFFIC & GREEN_PEOPLE;
           break;
         case RED_TRAFFIC & GREEN_PEOPLE:
           digitalWrite(RED_TRAFFIC_PIN,HIGH);
           digitalWrite(GREEN_PEOPLE_PIN,HIGH);
           delay(15*DELAY);
           intermitent(GREEN_PEOPLE_PIN);
           digitalWrite(RED_TRAFFIC_PIN,LOW);
           digitalWrite(GREEN_PEOPLE_PIN,LOW);
           state=GREEN_TRAFFIC & RED_PEOPLE;
           digitalWrite(BUTTON_PIN,LOW);
           digitalWrite(GREEN_TRAFFIC_PIN,HIGH);
           digitalWrite(RED_PEOPLE_PIN,HIGH);
           start=0;
           break;
      }
    }
  }
}
