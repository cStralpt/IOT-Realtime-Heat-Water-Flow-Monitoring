#include <OneWire.h> // library yang dibutuhkan
#include <DallasTemperature.h> // library yang dibutuhkan

#define ONE_WIRE_BUS 3 // pin digital 2 sebagai pin data

OneWire oneWire(ONE_WIRE_BUS); // desklarasi pembuatan instance untuk komunikasi
DallasTemperature sensorDS18B20(&oneWire);
volatile int flow_frequency; // Measures flow sensor pulses
unsigned int l_hour; // Calculated litres/hour
unsigned char flowsensor = 2; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
void flow () // Interrupt function
{
   flow_frequency++;
}
void setup() {
  Serial.begin(9600); // komunikasi serial
  sensorDS18B20.begin(); // perintah untuk memulai librarypinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   attachInterrupt(0, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
}

void loop() {
//  Serial.print("Meminta Data Suhu ---------- ");
  sensorDS18B20.requestTemperatures(); // permintaan pembacaan suhu

//  Serial.print("Suhu: ");
  Serial.println(sensorDS18B20.getTempCByIndex(0)); // mengambil dan menampilkan data sensor menggunakan satuan celcius
  currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      l_hour = (flow_frequency * 60 / 7.5); // (Pulse frequency x 60 min) / 7.5Q = flowrate in L/hour
      flow_frequency = 0; // Reset Counter
      Serial.print(l_hour, DEC); // Print litres/hour
//      Serial.println(" L/hour");
   }
  delay(500); // delay 500ms
}
