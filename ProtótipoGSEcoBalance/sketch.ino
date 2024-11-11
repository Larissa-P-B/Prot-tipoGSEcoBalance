

/***************************************************************
  FIAP
  Tecnologia em Análise e Desenvolvimento de Sistemas
  DISRUPTIVE ARCHITECTURES: IOT, IOB e Generative IA
  Global Solution - EcoBalace - um sistema de equilibrio energetico inteligente
  Turma: 2TDSPK
****************************************************************
Elaborado por: 
 Nome: Gabriel Ortiz Oliva Gil   RM:98642 – 2TDSPK 
 Nome: Rafael Noboru Watanabe Nasaha  RM:99948 – 2TDSPK 
 Nome: João Pedro Kraide Máximo - RM:550974 – 2TDSPK 
 Nome: Matheus de Andrade Ferreira - RM:99375 – 2TDSPK 
 Nome: Larissa Pereira Biusse - RM:551062 - 2TDSPK 
****************************************************************/

//bibliotecas 
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

// Credenciais do Wi-Fi
const char* ssid = "Wokwi-GUEST"; 
// URL do endpoint do Thinger.io (ajuste com seu dispositivo e chave)
const char* thinger_device_id = "testegs";
const char* thinger_device_key = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJqdGkiOiJEZXZpY2VDYWxsYmFja190ZXN0ZWdzIiwic3ZyIjoidXMtZWFzdC5hd3MudGhpbmdlci5pbyIsInVzciI6Imxhcmlzc2EifQ.j6nT0pFV-Z63mgxncXUCYayFrL55GEqL7i_QQucmF3k";
const String url = "https://backend.thinger.io/v3/users/larissa/devices/testegs/callback/data";

// Configuração dos pinos:
const int LDR_PIN = 34;       // Pino do LDR para produção de energia (ADC1)
const int POT_PIN = 35;       // Pino do Potenciômetro para consumo de energia (ADC2)
const int LED_PIN = 25;       // Pino do LED (simula relé)  


void setup() {
  // Inicia a comunicação serial
  Serial.begin(115200);
  
  
  connectToWiFi();
  // Exibe o IP após a conexão
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
 // Configuração dos pinos de I/Os digitais:
  
  // Saída ---> LED   
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  

  int ldrValue = analogRead(LDR_PIN);  // Leitura do valor do LDR
  int potValue = analogRead(POT_PIN);  // Leitura do valor do Potenciômetro
  
   Serial.print("Produção de Energia (LDR): ");
   Serial.println(ldrValue);   // Exibe o valor de produção
  
   Serial.print("Consumo de Energia (Potenciômetro): ");
   Serial.println(potValue);   // Exibe o valor de consumo
  
   // Lógica para ligar/desligar o LED com base nos valores lidos

  if (ldrValue > potValue) {
     digitalWrite(LED_PIN, LOW);  // Desliga o LED (suficiência de energia)
   } else {
     digitalWrite(LED_PIN, HIGH);   //  Liga o LED (insuficiência de energia)
   }

   sendDataToThinger();
  
   delay(1000); // Aguarda 1 segundo entre as leituras
}

// Conexão ao WiFi

void connectToWiFi() {
  Serial.print("Conectando ao Wi-Fi");
  WiFi.begin(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConectado ao Wi-Fi");
}

// Enviando dados ao servidor Thinger.IO
void sendDataToThinger() {
  WiFiClientSecure client;
  client.setInsecure();  // Desabilita a verificação SSL temporariamente para testes
  int ldrValue = analogRead(LDR_PIN);  // Leitura do valor do LDR
  int potValue = analogRead(POT_PIN); //Leitura do valor

  HTTPClient https;
  https.begin(client,url); 
  https.addHeader("Content-Type", "application/json");
  https.addHeader("Authorization", "Bearer eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJqdGkiOiJEZXZpY2VDYWxsYmFja190ZXN0ZWdzIiwic3ZyIjoidXMtZWFzdC5hd3MudGhpbmdlci5pbyIsInVzciI6Imxhcmlzc2EifQ.j6nT0pFV-Z63mgxncXUCYayFrL55GEqL7i_QQucmF3k");
  https.addHeader("Accept", "application/json, text/plain, */*");
  
  
  String payload = "{\"Produção de Energia (LDR)\": " + String(ldrValue) + ", \"Consumo de Energia (Potenciômetro)\": " + String(potValue) + "}";
  int httpResponseCode = https.POST(payload);
  
  //Logica para capturar resposta do servidor
  if (httpResponseCode > 0) {
    String response = https.getString();
    Serial.println("Resposta do servidor: " + String(httpResponseCode));
  } else {
    Serial.println("Erro na requisição: " + String(httpResponseCode));
  }

  https.end();
}
