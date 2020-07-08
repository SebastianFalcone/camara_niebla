
#include "DHT.h"
#include "Adafruit_Sensor.h"


#define LED_PIN LED_BUILTIN
volatile byte state = LOW;

/////////////////////////////////////////////////////////////////////
//DEFINICIONES PERTINENTES AL SENSOR DIGITAL DE TEMPERATURA+HUMEDAD//
/////////////////////////////////////////////////////////////////////
#define DHT_PIN 33
#define DHT_TYPE DHT11

DHT dht(DHT_PIN, DHT_TYPE);

float temp_digital, hum_digital; 

////////////////////////////////////////////////////
//DEFINICIONES DEL SENSOR ANALOGICO DE TEMPERATURA//
////////////////////////////////////////////////////
#define TERMISTOR_PIN A0

int Vo;
float logR2, R2, temp_analogica;

const int R1 = 10000;
const float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; 




////////////////////
//INICIA LA FIESTA//
//////////////////// 
void setup() 
{
	Serial.begin(115200);
  	dht.begin();	

	pinMode(LED_PIN, OUTPUT);
   	
   	TIMSK2 = (TIMSK2 & B11111110) | 0x01;
   	TCCR2B = (TCCR2B & B11111000) | 0x07;

}//SETUP
 
 
void loop() 
{
	///////////////////
	//LECTURA DIGITAL//
 	///////////////////
 	hum_digital = dht.readHumidity();
	temp_digital = dht.readTemperature();

	/////////////////////
	//LECTURA ANALOGICA//
	/////////////////////
	Vo = analogRead(TERMISTOR_PIN);
	
	//CALCULO LA R DEL TERMISTOR
  	R2 = R1 * (1023.0 / (float)Vo - 1.0); 
  	
  	// temperature EN Cº
  	temp_analogica = (1.0 / (c1 + c2*logR2 + c3*pow(log(R2), 3))) - 273.15; 

	//USO EL PIN DE LA PLACA PARA VERIFICAR SI SE ENVIO DATA. 
	//SU ESTADO CAMBIA CADA VEZ QUE ENTRO AL INTERRUPT
	digitalWrite(LED_PIN, state);

}//LOOP

ISR(TIMER2_OVF_vect)
{
	int cont;
	cont++;
    
	if(cont == 200)
	{
		Serial.print("	");
		Serial.print(temp_analogica);
		Serial.print("	");
		Serial.print(hum_digital);
		Serial.print("	");
		Serial.println(temp_digital);

		state = !state;
		cont = 0;
	}

}//TIMER 2

ISR(TIMER1_OVF_vect)
{
	int cont;
	cont++;
    
	if(cont == 200)
	{
		Serial.print("	");
		Serial.print(temp_analogica);
		Serial.print("	");
		Serial.print(hum_digital);
		Serial.print("	");
		Serial.println(temp_digital);

		state = !state;
		cont = 0;
	}

}//TIMER 2