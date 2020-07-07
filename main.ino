#define ledPin LED_BUILTIN
volatile byte state = LOW;

int cont = 0;
 
void setup() 
{
	Serial.begin(10000);

	pinMode(ledPin, OUTPUT);
   	TIMSK2 = (TIMSK2 & B11111110) | 0x01;
   	TCCR2B = (TCCR2B & B11111000) | 0x07;
}
 
 
void loop() 
{
	digitalWrite(ledPin, state);
}
 
 
ISR(TIMER2_OVF_vect)
{

	cont++;
    
	if(cont == 100)
	{
		state = !state;
		cont = 0;
	}
}