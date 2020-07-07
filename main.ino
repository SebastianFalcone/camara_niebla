#define LED_PIN LED_BUILTIN

#include "DHT.h"
#include "Adafruit_Sensor.h"

#define DHT_PIN 33
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

float temp, hum; 

#define TERMISTOR_PIN A0

volatile byte state = LOW;



int Vo;
float R1 = 10000; // value of R1 on board
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; 

int cont = 0;
 
void setup() 
{
	Serial.begin(9600);
  	dht.begin();	
	pinMode(LED_PIN, OUTPUT);
   	TIMSK2 = (TIMSK2 & B11111110) | 0x01;
   	TCCR2B = (TCCR2B & B11111000) | 0x07;
}
 
 
void loop() 
{


 	hum = dht.readHumidity();
	temp = dht.readTemperature();

	digitalWrite(LED_PIN, state);
	Vo = analogRead(TERMISTOR_PIN);
  	R2 = R1 * (1023.0 / (float)Vo - 1.0); //calculate resistance on thermistor
  	logR2 = log(R2);
  	T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
  	T = T - 273.15; //convert Kelvin to Celcius	

}

ISR(TIMER2_OVF_vect)
{

	cont++;
    
	if(cont == 200)
	{
		Serial.print("	");
		Serial.print(T);
		Serial.print("	");
		Serial.print(hum);
		Serial.print("	");
		Serial.println(temp);

		state = !state;
		cont = 0;
	}
}
