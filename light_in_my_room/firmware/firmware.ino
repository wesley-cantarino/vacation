int led_red = 14,
    led_gre = 12,
    led_blu = 13;

int set = 2, set_old = 2;

#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid = "h'(x)";
const char* password = "T5e5L0e9C7o7M0u2N7i4C4a0C6o4E0s";

WiFiServer server(80);
String header;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  pinMode(2, OUTPUT);
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(2, LOW);
    delay(200);
    Serial.print(".");
    digitalWrite(2, HIGH);
  }

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  pinMode(led_red, OUTPUT);
  pinMode(led_gre, OUTPUT);
  pinMode(led_blu, OUTPUT);
}

void loop()
{
  wifi();

  if (set == 1)
    combination();
  else if (set == 2)
    fade(100);
}








void wifi ()
{
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("New Client.");
    String currentLine = "";

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        header += c;

        if (c == '\n')
        {
          if (currentLine.length() == 0)
          {
            client.println(all_html()); //envia o html para o cliente

            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }
      }
    }

    if (header.indexOf("GET /button1") >= 0)
    {
      set = 1;
    }

    if (header.indexOf("GET /button2") >= 0)
    {
      set = 2;
    }

    header = "";
    client.stop();
  }
}

String all_html ()
{
  String _html = "";
  //_html += "HTTP/1.1 200 OK";
  //_html += "Content-type:text/html";
  //_html += "Connection: close";
  // Display the HTML web page

  _html += "<!DOCTYPE html><html>";
  _html += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  _html += "<link rel=\"icon\" href=\"data:,\">";

  _html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  _html += ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;";
  _html += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  _html += ".button2 {background-color: #77878A;}</style></head>";

  // Web Page Heading
  _html += "<body><h1>ESP8266 Web Server</h1>";

  _html += "<p><a href=\"/button1\"><button class=\"button\">CLICK button 1</button></a></p>";
  _html += "<p><a href=\"/button2\"><button class=\"button\">CLICK button 2</button></a></p>";

  _html += "</body></html>";

  return _html;
}

void fade (int del)
{
  Serial.println("primeiro for");
  for (int i = 0; i < 255; i++)
  {
    analogWrite(led_red, i);
    analogWrite(led_blu, 255 - i);
    Serial.println(i);

    wifi();
    i = breck_for(i);
    delay(del);
  }

  Serial.println("segundo for");
  for (int i = 0; i < 255; i++)
  {
    analogWrite(led_red, 255 - i);
    analogWrite(led_gre, i);
    Serial.println(i);

    wifi();
    i = breck_for(i);
    delay(del );
  }

  Serial.println("terceiro for");
  for (int i = 0; i < 255; i++)
  {
    analogWrite(led_gre, 255 - i);
    analogWrite(led_blu, i);
    Serial.println(i);

    wifi();
    i = breck_for(i);
    delay(del );
  }
}

int breck_for (int i)
{
  Serial.print("set: ");
  Serial.print(set);
  Serial.print("  set_old: ");
  Serial.println(set_old);

  if (set != set_old)
  {
    set_old = set;
    return 254;
  }
  else
    return i;
}

void combination ()
{
  digitalWrite(led_red, HIGH);
  delay(500);
  digitalWrite(led_gre, HIGH);
  delay(500);

  digitalWrite(led_red, LOW);
  delay(500);

  digitalWrite(led_blu, HIGH);
  delay(500);

  digitalWrite(led_gre, LOW);
  delay(500);

  shotdowm_led();
}

void shotdowm_led()
{
  digitalWrite(led_red, LOW);
  digitalWrite(led_gre, LOW);
  digitalWrite(led_blu, LOW);
}
