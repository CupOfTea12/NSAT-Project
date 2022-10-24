// NSat0.2
//this code is made by Rebeca Martinakova and Murphy Stejskal, two members of Orion cat space radar SR who are working on this high altitude balloon named NSat 0.2. the start of NSat will be 
//at 27.10.2018 at 5:30 in Partizanske

//=== LIBRARIES ===//

#include "DHT.h"
#include <SD.h>
#include <SPI.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <SFE_BMP180.h>

//=== DEFINES ===//
#define SD_INIT_MAX_RETRY 100
#define DHTPIN 2 
#define DHTTYPE DHT21   // DHT 21 (AM2301)
#define TX 5
#define RX 6
#define ALTITUDE 195 //the altitude is set for the Partizanske and the countries around

//=== INITIALIZATIONS ===//
TinyGPS gps;
SoftwareSerial swSerial(RX, TX);
//=== GLOBAL VARIABLES ===//

SFE_BMP180 pressure;

DHT dht(DHTPIN, DHTTYPE);

const int chipSelect = 10; //for SD card

int dataWriteCounter = 0; //counter

//=== SETUP LOOP ===//

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
  // this part is for initialization of the SD card
  int i = 0;
  do {
    Serial.print("Initializing SD card... try No ");
    Serial.println(i);
    i++;
  } while (!SD.begin(chipSelect) && i < SD_INIT_MAX_RETRY);
  // don't do anything more:
  Serial.print("SD Card init retry " + i);

  if (i < SD_INIT_MAX_RETRY) {
    Serial.println(" Working, sd card ready, txt.file is done ");
  } else {
    Serial.println("Unable to read the SD card! Try to restart or change SD card ");
  }
  delay(3000); //M: comment
}

if (pressure.begin());
  Serial.println("BMP180 init success");
  else //else, stop code forever
  {
    Serial.println("BMP180 init failed");
    while (1)
  }



//=== MAIN LOOP ===//
void loop() {
  //using float as data type cause of not full numbers
  float humidity = dht.readHumidity();
  humidity = humidity - 5;

  float temperature = dht.readTemperature();
  temperature = temperature - 5;

  float dew = dewPoint(temperature, humidity);

  //for problem with sd card, then write to serial>>>>>>
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Unable to read data from DHT 21 sensor!");
  } else {
      //code for serial println
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println((char)223); //degree sign

    File dataFile = SD.open("datalog.txt", FILE_WRITE);

    // if the file is available, write to it:
    if (dataFile) {
      writeToDataFile(dataFile, dataWriteCounter, humidity, temperature, dew);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("Problem with txt file! Cant open and log files!");
    }

  }
  delay(5000);
  dataWriteCounter++;
}

char status; {
  double P, T, p0; //creating variabiles for pressure and relative pressure

status= pressure.startTemperature();
if (status ! = 0){
  Serial.print("Temp");
  Serial.print(T, 1);
  Serial.println(" deg C");

  Serial.print("You provided altitude: ");
  Serial.print(ALTITUDE = 0);
  Serial.println("  meters");

  status = pressure.startPressure(3);
  if (status !=0){
    delay (status);

    status = pressure.getPressure(P, T);
    if (status ! = 0){
      Serial.print("preassure measurement: ");
      Serial.print(P);
      Serial.println(" hPa (Pressure measured using temperature)");

       p0= pressure.sealevel(P, ALTITUDE);
       Serial.print("Relative (sea level) pressure: ");
       Serial.print(p0);
       Serial.print("hPa");
    }
  }
}

delay(3000);

   float zSirka, zDlzka; {
    unsigned long stariDat;
    int rok;
    byte mesiac, den, hodina, minuta, sekunda, setinaSekundy;
    char datumCas[32];
    bool novaData = false;
    unsigned long = znaky
    unsigned short = slova, chyby;
    for (unsigned long start = millis(); millis() - start < 1000;){
      while (swSerial.available()) {
        char c = swSerial.read();
        if (gps.encode(c)){
          novaData = true;
        }
      }
    }
   }
//gps data serial print part of code
   if (novaData) {
    gps.f_get_position(&zSirka, &zDlzka, &zstariDat);
    Serial.println(" ::Dostupne GPS udaje:: ");
    Serial.print("Zemepisna sirka: ");
    Serial.println(zSirka == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0: zSirka, 6);
    Serial.print("Zemepisna dlzka: ");
    Serial.println(zDlzka == TinyGPS::GPS_INVALID_F_ANGEL ? 0.0: zDlzka, 6);
    Serial.print("Pocet satelitu: ");
    Serial.println(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITE ? 0. : gps.satellites());
    Serial.print("Presnost: ");
    Serial.println(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    Serial.print("Stari dat: ");
    Serial.println(stariDat == TinyGPS::GPS_INVALID_AGE ? 0 : stariDat);
    Serial.print("Nadmorska vyska m.n.m: ");
    Serial.println(gps.f_altitude() == TinyGPS::GPS_INVALID_F_ALTITUDE ? 0 : gps.f_altitude());
    Serial.print("Rychlost v km/h: ");
    Serial.println(gps.f_speed_kmph() == TinyGPS::GPS_INVALID_F_SPEED ? 0 : gps.f_speed_kmph());
    gps.crack_datetime(&rok, &mesiac, &den, &hodina, &minuta, &sekunda, &setinaSekundy, &stariDat);
    if (stariDat == TinyGPS::GPS_INVALID_AGE){
      Serial.print("Nelze nacist datum a cas: ");
      Serial.println();
    }else{
      Serial.print("date and time: ");
      sprintf(datumCas, "%02d/%02d/%02d %02d %02d:%02d:%02d", mesic, den, rok, hodina, minuta, sekunda);
      Serial.println(datumCas);
      Serial.println();  
    }
    
   }

   gps.stats(&znaky, &slova, &chyby);
    Serial.print("Detected numbers: ");
    Serial.print(Znaky);
    Serial.print(", words: ");
    Serial.print(slova);
    Serial.print(", error with reception of datas: ");
    Serial.print(chyby);
    Serial.println();
    if(znaky==0){
      Serial.print();
      Serial.println("Error with recieving data!");
      Serial.println();
    }
   
   
  
}

/*-----( Declare User-written Functions )-----*/
void writeToDataFile(File dataFile, int counter, float humidity, float temperature, float dew) {
  dataFile.print(counter);
  dataFile.print(", ");
  dataFile.print("Humidity: ");
  dataFile.print(humidity);
  dataFile.print(", Temperature: ");
  dataFile.print(temperature);
  dataFile.print(", Dew point: ");
  dataFile.println(dew);
  dataFile.println("\n");
  String datastring ("Zemepisna sirka: ");
  data
  dataFile.close();
}


//Celsius to Fahrenheit conversion
float celsiusToFahrenheit(float celsius)
{
  return 1.8 * celsius + 32;
}

//Celsius to Kelvin conversion
float celsiusToKelvin(float celsius)
{
  return celsius + 273.15;
}

// dewPoint function NOAA
double dewPoint(double celsius, double humidity)
{
  double a0 = 373.15 / (273.15 + celsius);
  double sum = -7.90298 * (a0 - 1);
  sum += 5.02808 * log10(a0);
  sum += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / a0))) - 1) ;
  sum += 8.1328e-3 * (pow(10, (-3.49149 * (a0 - 1))) - 1) ;
  sum += log10(1013.246);
  double vp = pow(10, sum - 3) * humidity;
  double t = log(vp / 0.61078);   // temp var
  return (241.88 * t) / (17.558 - t);
}

//Candidate for removal
//@Deprecated
double dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity / 100);
  double Td = (b * temp) / (a - temp);
  return Td;
}
