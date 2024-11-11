# Protótipo GS EcoBalance

## Projeto IoT: Redução do Consumo Energético em Empresas
### 1. Introdução

  Este projeto tem como objetivo monitorar a produção e o consumo de energia em sistemas de painéis solares, ajudando empresas a otimizar o consumo energético. Com o uso de um dispositivo ESP32, os dados de produção e consumo de energia são coletados em tempo real e enviados ao Thinger.io, onde podem ser analisados para identificar oportunidades de melhoria.
---
### 2. Objetivos
- Monitorar a produção de energia solar e o consumo elétrico.
- Fornecer dados de consumo e produção em tempo real para visualização e análise.
- Automatizar alertas visuais (LEDs) para indicar a relação entre produção e consumo.
---  
### 3. Componentes Utilizados
- ESP32: Microcontrolador para coleta e envio dos dados.
  <div align="left">
  <img src="https://github.com/user-attachments/assets/6688c23a-34d2-4bec-acd3-3ebb2b2176ee" alt="Diagrama do Sistema" width="100"/>
  </div>
  

- LDR: Sensor de intensidade luminosa que simula a produção de energia solar.
  <div align="left">
  <img src="https://github.com/user-attachments/assets/9cc879cf-8cf4-42c2-be86-655aadf10030" alt="Diagrama do Sistema" width="100"/>
  </div>
  

- Potenciômetro: Simula o consumo energético da empresa.
   <div align="left">
  <img src="https://github.com/user-attachments/assets/d8d931ff-53e9-4149-ba77-20ce06ba0337" alt="Diagrama do Sistema" width="100"/>
  </div>


- LED: Indica visualmente a suficiência ou insuficiência energética.
  <div align="left">
  <img src="https://github.com/user-attachments/assets/0be50a9e-d058-4383-8579-bcba5b18583f" alt="Diagrama do Sistema" width="100"/>
  <img src="https://github.com/user-attachments/assets/99522e59-c8b4-4859-964b-135b9cfad6d1" alt="Diagrama do Sistema" width="100"/>
  </div>
  <div align="center">
  <img src="https://github.com/user-attachments/assets/99522e59-c8b4-4859-964b-135b9cfad6d1" alt="Diagrama do Sistema" width="100"/>
  
  </div>


---

### 4. Diagrama do Sistema
- Diagrama do circuito com ESP32, LDR, potenciômetro e LED, mostrando as conexões entre os pinos.
  <div align="center">

  <img src="https://github.com/user-attachments/assets/99522e59-c8b4-4859-964b-135b9cfad6d1" alt="Diagrama do Sistema" width="600"/>
  </div>
  

### 5. Configurações
Bibliotecas Utilizadas
```
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
```
Conexão Wi-Fi
```
SSID: Wokwi-GUEST
```
## Thinger.io
URL: https://backend.thinger.io/v3/users/${user}/devices/${device_id}/callback/data

Credenciais: Autenticação via Token (necessário substituir no código com o token fornecido).
---
### 6. Funcionamento do Código
- Setup
- Inicia a comunicação serial.
- Conecta ao Wi-Fi.
- Configura os pinos de entrada e saída (LDR, Potenciômetro e LED).
```
// Credenciais do Wi-Fi
const char* ssid = "Wokwi-GUEST"; 
// URL do endpoint do Thinger.io (ajuste com seu dispositivo e chave)
const char* thinger_device_id = "${device_id}";
const char* thinger_device_key = "${device_key}";
const String url = "https://backend.thinger.io/v3/users/${user}/devices/${device_id}/callback/data";

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
```

- Loop Principal
- Lê os valores do LDR (produção de energia) e do potenciômetro (consumo de energia).
- Exibe os valores no monitor serial.
- Compara os valores:
- LED Apagado: Quando a produção é maior que o consumo.
- LED Aceso: Quando o consumo é maior que a produção.
```
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
```
- Envia os dados coletados para o Thinger.io.
```
// Enviando dados ao servidor Thinger.IO
void sendDataToThinger() {
  WiFiClientSecure client;
  client.setInsecure();  // Desabilita a verificação SSL temporariamente para testes
  int ldrValue = analogRead(LDR_PIN);  // Leitura do valor do LDR
  int potValue = analogRead(POT_PIN); //Leitura do valor

  HTTPClient https;
  https.begin(client,url); 
  https.addHeader("Content-Type", "application/json");
  https.addHeader("Authorization", "Bearer ${Bearer}");
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
```
---

### 7. Resultados Esperados
- Esse sistema permite que empresas visualizem seu perfil energético em tempo real, possibilitando ajustes no consumo e aprimorando a eficiência energética com base nos dados coletados.
---

### 8. Próximos Passos
- Implementar um dashboard no Thinger.io para visualização gráfica dos dados coletados.
<div align="center">
  <img src="https://github.com/user-attachments/assets/5d24be83-123d-494f-8836-17c6183e9021" alt="Diagrama do Sistema" width="600"/>
</div>

---


### 9. Conclusão
Esse projeto IoT oferece uma solução acessível para pequenas empresas que desejam monitorar e otimizar seu consumo energético de maneira eficiente e em tempo real.
