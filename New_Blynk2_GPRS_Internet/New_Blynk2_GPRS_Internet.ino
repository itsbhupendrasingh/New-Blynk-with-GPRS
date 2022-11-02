
#define BLYNK_TEMPLATE_ID "Template ID"
#define BLYNK_DEVICE_NAME "Device Name"
#define BLYNK_AUTH_TOKEN "Blynk Auth Token"

#define BLYNK_PRINT Serial
#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include <BlynkSimpleSIM800.h>
#include <SoftwareSerial.h>
SoftwareSerial SerialAT(9,10); // RX, TX
TinyGsm modem(SerialAT);

char auth[] = BLYNK_AUTH_TOKEN;
char apn[]  = "Bsnlnet";
char user[] = "";
char pass[] = "";
int device1=6, device2=7;

BLYNK_WRITE(V0) // to control 1st device
{
  if(param.asInt()==1)
  {
    digitalWrite(device1, HIGH);
  }
  if(param.asInt()==0)
  {
    digitalWrite(device1, LOW);
  }
}

BLYNK_WRITE(V1) // to control 2nd device
{
  if(param.asInt()==1)
  {
    digitalWrite(device2, HIGH);
  }
  if(param.asInt()==0)
  {
    digitalWrite(device2, LOW);
  }
}

void setup()
{
  Serial.begin(9600);
  delay(10);
  SerialAT.begin(9600);
  pinMode(device1, OUTPUT);
  pinMode(device2, OUTPUT);
  Serial.println("Serial Begin... Waiting for GSM Modem Activation");
  delay(3000);
  Serial.println("Initializing modem...");
  modem.restart();

  Blynk.begin(auth, modem, apn, user, pass, "blynk.cloud", 80);
  Serial.println("Sucessfully connected");
}

void loop()
{
  Blynk.run();
}
