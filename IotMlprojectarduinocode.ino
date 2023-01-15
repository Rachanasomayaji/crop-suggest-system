
#include "DHT.h"

#define DHTPIN 33      
#define DHTTYPE DHT11   

#define PUSH 2


#include <WiFi.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


const char* ssid     = "Rachna";
const char* password = "rachana1234";

const char* host = "192.168.43.162";

DHT dht(DHTPIN, DHTTYPE);
void setup()
{
    Serial.begin(115200);
    delay(10);

    lcd.init();
  lcd.backlight();

     dht.begin();

     pinMode(PUSH,INPUT);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

     lcd.setCursor(0,0);
        lcd.print("Wifi connected");
}

int value = 0;

void loop()
{
    delay(500);
  

    float h = dht.readHumidity();
      float t = dht.readTemperature(true);



    if( isnan(h) || isnan(t) )
    {
        h=t=0;  
    }
    
    value=digitalRead(PUSH);


    Serial.println("value of push = "+String(value));


    if( value==1 )
    {
    

    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 5001;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request

    Serial.println("Temp = "+String(t)+",Humidity = "+String(h));

    String url="http://192.168.43.162:5001/?temp="+String(t)+"&hum="+String(h);
    Serial.print("Requesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial

    String line="";
    while(client.available()) {
        line = client.readStringUntil('\r');

        
        Serial.print(line);
    }

 lcd.clear();
 lcd.setCursor(1,0);
  lcd.print(line);
    Serial.println();
    Serial.println("closing connection");
    
  } // end of push button

}
