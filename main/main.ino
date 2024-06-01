// Bibliotecas usadas
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Dados do WiFi
#define WIFI_SSID ""  // Colocar nome do WIFI
#define WIFI_PASSWORD "" // Colocar senha do WIFI

// Telegram BOT Token (Botfather)
#define BOT_TOKEN "7205986318:AAGGDEBrQ1K240fywguYpDziALlWNxoekeM"  // ID do bot criado

// Use (IDBot) para saber qual o seu ID
#define CHAT_ID "1045989702"    // ID da conversa que vai receber a mensagem

// Criando instância do BOT
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

// Alocando sensor da porta e adicionando uma flag para não enviar diversas mensagens enquanto a porta estiver aberta.
#define Sensor 4  // Inserir o pino
bool flag = 1;


// Void do Setup
void setup() {

  pinMode(Sensor, INPUT);

  Serial.begin(115200);
  Serial.println();


  //Conexão da rede:
  Serial.print("Connectando Wifi ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org");  // Pegando UTC data via NTP
  time_t now = time(nullptr);

  while (now < 24 * 3600) {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  bot.sendMessage(CHAT_ID, "Bot iniciou", "");  // Envia mensagem dizendo que iniciou o BOT
}

// Fim do void do Setup

//  Início do loop do sensor

void loop() {

  int Porta = digitalRead(Sensor);


  if (Porta == 0) {
    if (flag) {
      Serial.println("Porta Aberta");
      bot.sendMessage(CHAT_ID, "Porta do Rack XXX foi aberta", "");
      flag = 0;
    }

  } else {
      Serial.println("Porta fechada");
      bot.sendMessage(CHAT_ID, "Porta do Rack XXX foi fechada", "");
    flag = 1;
  }

}

// Fim do loop do sensor 

// Fim do programa