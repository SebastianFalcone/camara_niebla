int ThermistorPin = A0;
int Vo;
float R1 = 10000; // value of R1 on board
float logR2, R2, T;
float c1 = 0.001129148, c2 = 0.000234125, c3 = 0.0000000876741; //steinhart-hart coeficients for thermistor

void setup() 
{
  pinMode(LED_BUILTIN, OUTPUT);	
  Serial.begin(115200);
}

void loop() 
{
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0); //calculate resistance on thermistor
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // temperature in Kelvin
  T = T - 273.15; //convert Kelvin to Celcius
  //T = T + 17,2;//correccion

	
  //Serial.println("hola");
  Serial.println(T);

  //digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  //digitalWrite(LED_BUILTIN, LOW);
  //delay(500);
}
