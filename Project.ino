

#define FASTLED_INTERNAL
#include <FastLED.h>
#define NUM_LEDS 30
#define DATA_PIN 11
CRGB leds[NUM_LEDS];


int sampleBufferValue=0;
int  analog=0;
int lastvalue=0;
int noise=0;
int failsafe=0;
uint16_t sampleval=0;
int k=0;
uint16_t bright=0;
int buttonnew;
int buttonold=1;
int pattern=0;

void setup() {
  pinMode(12,INPUT);
  pinMode(11,OUTPUT);
  pinMode(8,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(40);
  Serial.begin(9600);
}

void loop() {
  buttonnew=digitalRead(12);
  if(buttonold==0 && buttonnew==1){
        pattern++;
        if(pattern==2){pattern=0;}
    }
    buttonold=buttonnew;
  /*
  EVERY_N_MILLISECONDS(10){
  analog=analogRead(A3)/10;
  //Serial.println(analog);
  }
  if(analog>50){analog=50;}
  if(analog<20){analog=20;}
  uint8_t value=map(analog,20,50,30,250);
  Serial.println(value);
  EVERY_N_MILLISECONDS(50){
  leds[0]=CRGB(100/value,100/value,value);
  //leds[15]=CHSV(value,255,255);
  for(int i =NUM_LEDS-1;i>0;i--){
   leds[i]=leds[i-1] ;
    }
  }
  FastLED.show();
    */
 
   
   sampleval=analogRead(A1);
   k=map(sampleval,0,1023,1,650);
   bright=map(analogRead(A2),0,1023,0,100);
   FastLED.setBrightness(bright);
   for(int i=0;i<=2000;i++){
    if(digitalRead(8)==LOW){
       sampleBufferValue++;
    }
   }
   // Serial.println(sampleBufferValue);
   
   if(sampleBufferValue>k){
    sampleBufferValue=k;
    }
   if(sampleBufferValue<0){
    sampleBufferValue=0;
    }
    //Serial.println(sampleBufferValue);
    
   uint8_t value=map(sampleBufferValue,0,k,0,255);
   sampleBufferValue=0;
   
   /*noise=abs(lastvalue-value);
   //Serial.println(noise);
    if(noise<10){
      value=lastvalue;
      failsafe=value;
    }  
   
   EVERY_N_MILLISECONDS(35){
    if(failsafe==value){
      value=0;
      }
    }*/

   
   Serial.println(value);
   
    
   EVERY_N_MILLISECONDS(45){
if(pattern==0){
    if(value>=0&&value<40){
    leds[14] = CRGB(0,0,150);
    leds[15] = CRGB(0,0,150);
    }
    if(value>=40&&value<70){    
    //leds[14] =  CRGB(200,0,55);
    //leds[15] =  CRGB(200,0,55);
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    }
    if(value>=70&&value<150){
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    }
    if(value>=150&&value<256){
    leds[14] =  CRGB(140,250,40);
    leds[15] =  CRGB(140,250,40);
    }
}
if(pattern==1){
    if(value>=0&&value<50){
    leds[14] = CRGB(0,0,150);
    leds[15] = CRGB(0,0,150);
    }
    if(value>=50&&value<256){    
    leds[14] = CRGB::White;
    leds[15] = CRGB::White;
    }
}
    //Serial.println(value);
    int j=0;
    for(int i =29;i>15;i--){
       leds[i]=leds[i-1] ;
       leds[j]=leds[j+1];
       j++;
  
    }

    FastLED.show();

    
   }

  //lastvalue=value;
  
  //fadeToBlackBy(leds, NUM_LEDS, 1);

}
