int led_red = 14,
    led_gre = 12,
    led_blu = 13;

int set = 2, set_old = 2;

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "h'(x)";
const char* password = "T5e5L0e9C7o7M0u2N7i4C4a0C6o4E0s";

WiFiServer server(80);
String header;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  pinMode(2, OUTPUT);
  int resetar = millis();
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(2, LOW);
    delay(200);
    Serial.print(".");
    digitalWrite(2, HIGH);

    resetar = millis();
    if (resetar > 500000)
      ESP.restart();
  }

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();

  pinMode(led_red, OUTPUT);
  pinMode(led_gre, OUTPUT);
  pinMode(led_blu, OUTPUT);


  ArduinoOTA.setHostname("ESP_quarto09");
  ArduinoOTA.onStart([]() {
    Serial.println("Inicio...");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("nFim!");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progresso: %u%%r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Erro [%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Autenticacao Falhou");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Falha no Inicio");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Falha na Conexao");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Falha na Recepcao");
    else if (error == OTA_END_ERROR) Serial.println("Falha no Fim");
  });
  ArduinoOTA.begin();
}

void loop()
{
  ArduinoOTA.handle();

  wifi();

  if (set == 1)
    combination();
  else if (set == 2)
    fade(100);
  else if (set == 3)
    vermelhao();
  else if (set == 4)
    verdao();
  else if (set == 5)
    azulao();
  else if (set == 6)
    verde_agua();
  else if (set == 7)
    lilas();
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
      set = 1;
    else if (header.indexOf("GET /button2") >= 0)
      set = 2;
    else if (header.indexOf("GET /button3") >= 0)
      set = 3;
    else if (header.indexOf("GET /button4") >= 0)
      set = 4;
    else if (header.indexOf("GET /button5") >= 0)
      set = 5;
    else if (header.indexOf("GET /button6") >= 0)
      set = 6;
    else if (header.indexOf("GET /button7") >= 0)
      set = 7;

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

  _html += "<head>";
  _html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  _html += "<link rel=\"icon\" href=\"data:,\">";

  _html += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  _html += ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;";
  _html += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  _html += ".button2 {background-color: #77878A;}</style>";
  _html += "</head>";

  // Web Page Heading
  	_html += "<h1>Web Server select function and color :D</h1>";

	_html += "<p>Same function:</p>";
	_html += "<div class=\"btn-group\" style=\"width:100%\">";
 	_html += "<button style=\"width:50%\" >Pisca pisca> </button>";
  	_html += "<button style=\"width:50%\" >Fade       > </button>";
	_html += "</div>";

	_html += "<p>Basic color:</p>";
	_html += "<div class=\"btn-group\" style=\"width:100%\">";
 	_html += "<button style=\"width:33.3%\" href=\"/button3\">Vermelho</button>";
 	_html += "<button style=\"width:33.3%\" href=\"/button4\">Verde</button>";
 	_html += "<button style=\"width:33.3%\" href=\"/button5\">Azul</button>";
	_html += "</div>";

	_html += "<p>Four buttons in a group:</p>";
	_html += "<div class=\"btn-group\" style=\"width:100%\">";
 	_html += "<button style=\"width:25%\">Apple</button>";
 	_html += "<button style=\"width:25%\">Samsung</button>";
  _html += "<button style=\"width:25%\">Sony</button>";
  _html += "<button style=\"width:25%\">HTC</button>";
	_html += "</div>";

 	_html += "</body></html>";

  return _html;
}

void fade (int del)
{
  Serial.println("primeiro for");
  for (int i = 0; (i < 255) && (!breck_for()); i++)
  {
    analogWrite(led_red, i);
    analogWrite(led_blu, 255 - i);
    Serial.println(i);

    wifi();
    delay(del);
  }

  Serial.println("segundo for");
  for (int i = 0; (i < 255) && (!breck_for()); i++)
  {
    analogWrite(led_red, 255 - i);
    analogWrite(led_gre, i);
    Serial.println(i);

    wifi();
    delay(del );
  }

  Serial.println("terceiro for");
  for (int i = 0; (i < 255) && (!breck_for()); i++)
  {
    analogWrite(led_gre, 255 - i);
    analogWrite(led_blu, i);
    Serial.println(i);

    wifi();
    delay(del );
  }
}

bool breck_for ()
{
  Serial.print("set: ");
  Serial.print(set);
  Serial.print("  set_old: ");
  Serial.println(set_old);

  if (set != set_old)
  {
    set_old = set;
    return true;
  }
  else
    return false;
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

void vermelhao ()
{
  digitalWrite(led_red, HIGH);
  digitalWrite(led_gre, LOW);
  digitalWrite(led_blu, LOW);
}

void verdao ()
{
  digitalWrite(led_red, LOW);
  digitalWrite(led_gre, HIGH);
  digitalWrite(led_blu, LOW);
}

void azulao ()
{
  digitalWrite(led_red, LOW);
  digitalWrite(led_gre, LOW);
  digitalWrite(led_blu, HIGH);
}

void verde_agua ()
{
  digitalWrite(led_red, LOW);
  digitalWrite(led_gre, HIGH);
  digitalWrite(led_blu, HIGH);
}

void lilas ()
{
  analogWrite(led_red, 180);
  analogWrite(led_gre, 50);
  analogWrite(led_blu, 180);
}

void shotdowm_led()
{
  digitalWrite(led_red, LOW);
  digitalWrite(led_gre, LOW);
  digitalWrite(led_blu, LOW);
}
