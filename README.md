# Protótipo GS EcoBalance

## Projeto IoT: Redução do Consumo Energético em Empresas
### 1. Introdução

  Este projeto tem como objetivo monitorar a produção e o consumo de energia em sistemas de painéis solares, ajudando empresas a otimizar o consumo energético. Com o uso de um dispositivo ESP32, os dados de produção e consumo de energia são coletados em tempo real e enviados ao Thinger.io, onde podem ser analisados para identificar oportunidades de melhoria.
--
### 2. Objetivos
- Monitorar a produção de energia solar e o consumo elétrico.
- Fornecer dados de consumo e produção em tempo real para visualização e análise.
- Automatizar alertas visuais (LEDs) para indicar a relação entre produção e consumo.
--  
### 3. Componentes Utilizados
- ESP32: Microcontrolador para coleta e envio dos dados.
- <div align="left">
  <img src="https://github.com/user-attachments/assets/6688c23a-34d2-4bec-acd3-3ebb2b2176ee" alt="Diagrama do Sistema" width="100"/>
  </div>
  

- LDR: Sensor de intensidade luminosa que simula a produção de energia solar.
  ![image](https://github.com/user-attachments/assets/9cc879cf-8cf4-42c2-be86-655aadf10030)

- Potenciômetro: Simula o consumo energético da empresa.
- ![image](https://github.com/user-attachments/assets/d8d931ff-53e9-4149-ba77-20ce06ba0337)

- LED: Indica visualmente a suficiência ou insuficiência energética.
  ![image](https://github.com/user-attachments/assets/0be50a9e-d058-4383-8579-bcba5b18583f)

--

### 4. Diagrama do Sistema
- Diagrama do circuito com ESP32, LDR, potenciômetro e LED, mostrando as conexões entre os pinos.
  ![image](https://github.com/user-attachments/assets/faa97048-2435-4062-86ed-d6e87b9f38b0)


5. Configurações
Bibliotecas Utilizadas
cpp
Copiar código
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
Conexão Wi-Fi
SSID: Wokwi-GUEST
Thinger.io
URL: https://backend.thinger.io/v3/users/larissa/devices/testegs/callback/data
Credenciais: Autenticação via Token (necessário substituir no código com o token fornecido).
6. Funcionamento do Código
Setup
Inicia a comunicação serial.
Conecta ao Wi-Fi.
Configura os pinos de entrada e saída (LDR, Potenciômetro e LED).
Loop Principal
Lê os valores do LDR (produção de energia) e do potenciômetro (consumo de energia).
Exibe os valores no monitor serial.
Compara os valores:
LED Apagado: Quando a produção é maior que o consumo.
LED Aceso: Quando o consumo é maior que a produção.
Envia os dados coletados para o Thinger.io.
7. Código-Fonte
Inclua o código completo do projeto, com comentários explicativos sobre cada seção para facilitar a compreensão.

8. Resultados Esperados
Esse sistema permite que empresas visualizem seu perfil energético em tempo real, possibilitando ajustes no consumo e aprimorando a eficiência energética com base nos dados coletados.

9. Próximos Passos
Implementar um dashboard no Thinger.io para visualização gráfica dos dados coletados.
Expandir o sistema para monitoramento de múltiplas fontes de consumo e produção de energia.
10. Conclusão
Esse projeto IoT oferece uma solução acessível para pequenas empresas que desejam monitorar e otimizar seu consumo energético de maneira eficiente e em tempo real.
