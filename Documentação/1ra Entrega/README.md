# Proposta Inicial do Projeto

## Universidade **IADE**

## Projeto

**Sistema Inteligente de Monitorização e Segurança para Sala de Servidores**

## Elementos do Grupo

*Alejandro Agrela 20231626,
Bionda Mateus 20231666,
César Pinto 20231615*

## Unidades Curriculares Envolvidas

* Sistemas Distribuídos
* Computação Física e IoT
* Engenharia de Software
* Inteligência Artificial

## Palavras‑chave

IoT, ESP32, Segurança, Sensores, Automação, Monitorização, IA, REST API

## Repositório GitHub

[https://github.com/Engalion/PBL-Semestre-5-Grupo-3]

---

# 1. Descrição do Projeto

A crescente dependência de infraestruturas críticas de TI exige que salas de servidores mantenham condições ambientais e de segurança rigorosas. O presente projeto propõe o desenvolvimento de um **sistema inteligente**, baseado em IoT, capaz de monitorizar variáveis essenciais (como temperatura, humidade e acessos à sala), garantindo segurança e prevenção de incidentes.

O sistema recolhe dados através de sensores instalados, envia‑os para um servidor via **REST API**, armazena numa **base de dados**, e utiliza **Inteligência Artificial** para prever o consumo energético associado ao ambiente de servidores, integrando também dados externos.

---

# 2. Público‑Alvo

* Pequenas e médias empresas com salas de servidores.
* Instituições que necessitam monitorizar ambientes críticos.
* Equipas de IT responsáveis por infraestruturas técnicas.

---

# 3. Guiões de Teste (versão preliminar)


---

# 4. Enquadramento nas Unidades Curriculares

## **4.1 Sistemas Distribuídos**

* Planeamento do projeto.
* Definição da arquitetura distribuída.
* Comunicação ESP32 → REST → BD.

## **4.2 Computação Física e IoT**

* Programação do ESP32.
* Integração de sensores e atuadores.
* Envio de dados para servidor.

## **4.3 Engenharia de Software**

* Especificação inicial dos requisitos.
* Guiões de teste.
* Modelação de sistema.

## **4.4 Inteligência Artificial**

* Recolha e tratamento de dados.
* Integração com fonte externa.
* Modelo preditivo de consumo energético.

---

# 5. Requisitos Técnicos e Tecnologias

## **Hardware (preliminar)**

* Esp32 Dev Kit
* Breadboard 
* Oled
* Motion Sensor
* Humidity and Temperature module
* Buzzer
* Led RGB
* 3 Resistências 220A
* 8 Cabos Dupont F-M
* 8 Cabos Dupont M-M
* Computador
* Futura Possivel adição Botão onde inclui botão físico, resistência 10k e dois fios de lição a 3v e ground.

## **Software**

* Arduino Ide
* Python ide
* Base de Dados

---

# 6. Arquitetura da Solução (Provisória)

```
[Sensores] → ESP32 → API REST → Base de Dados → Dashboard / IA
```

* O ESP32 recolhe dados de sensores.
* Comunica via HTTP com o servidor remoto.
* API valida e guarda dados.
* IA utiliza base de dados para previsão.

---

# 7. Esboço Físico do Artefacto

* Caixa com ESP32.
* Entrada USB para alimentação.
* DHT22 posicionado externamente.
* RFID frontal para identificação.
* LED/buzzer para alertas.

*(Esquemas detalhados serão adicionados no Milestone 2.)*

---

# 8. Lista Preliminar de Material

* ESP32 – 1
* DHT22 – 1
* PIR – 1
* RFID RC522 – 1
* Reed Switch – 1
* LED + resistor – 1
* Buzzer – 1
* Jumpers – vários
* Breadboard – 1

---

# 9. Planeamento e Calendarização Inicial

## **Tarefas Principais**

* T1 — Definição do problema
* T2 — Seleção de sensores
* T3 — Desenvolvimento do protótipo
* T4 — API REST
* T5 — Base de dados
* T6 — IA – recolha e tratamento de dados
* T7 — IA – treino do modelo
* T8 — Testes
* T9 — Documentação e apresentação

<img width="954" height="572" alt="image" src="https://github.com/user-attachments/assets/c4d4e160-37d7-413a-ab15-e92961f732c7" />


## 10. Requisitos Funcionais (RF)

> **Prioridade Alta = Essencial**  
> **Prioridade Média = “Good to have”**

| ID   | Categoria     | Prioridade | Descrição |
|------|---------------|------------|-----------|
| RF01 | Monitorizar   | Alta | O sistema deverá detetar a presença de pessoas na sala através do sensor de movimento (PIR). |
| RF02 | Monitorizar   | Alta | O sistema deverá medir a temperatura e a humidade ambiente em intervalos regulares ou definidos pelo gestor da segurança. |
| RF03 | Interface OLED | Média | O sistema mostrará no ecrã OLED os valores atuais de temperatura, humidade e o estado da sala. |
| RF04 | Alarme | Alta | O sistema ativará o buzzer quando for detetada uma condição de alarme (intrusão ou limites excedidos). |
| RF05 | Sinalização | Alta | O sistema indicará o estado da sala através do LED RGB (verde = normal, vermelho = alarme, azul = standby/configuração). |
| RF06 | Comunicação | Alta | O sistema deve enviar periodicamente para o computador/base de dados as leituras e eventos. |
| RF07 | Armazenamento | Alta | A aplicação deve guardar na base de dados as leituras e eventos recebidos do ESP32. |
| RF08 | Consulta | Média | A aplicação deve permitir consultar o histórico de leituras e eventos por data/hora. |
| RF09 | Gestão | Média | O utilizador deverá conseguir desativar temporariamente o alarme através de botão físico ou comando na aplicação. |

## 11. Requisitos Não Funcionais (RNF)

| ID   | Categoria | Prioridade | Descrição |
|------|-----------|------------|-----------|
| RNF01 | Desempenho | Alta | O sistema deve atualizar leitura de temperatura/humidade a cada 2–5s e reagir a detecção de movimento em <1s. |
| RNF02 | Fiabilidade | Alta | O sistema deve funcionar continuamente entre 8 a 24 horas sem reiniciar. |
| RNF03 | Usabilidade | Média | As mensagens no OLED devem ser claras e legíveis, com abreviações simples. |
| RNF04 | Segurança | Alta | A comunicação deve ser realizada em rede protegida e sem credenciais expostas em texto simples. |
| RNF05 | Integridade dos Dados | Alta | A aplicação Python deve garantir que todas as mensagens válidas são registadas sem perda. |
| RNF06 | Manutenção | Média | O código deve ser modular para facilitar alterações futuras, especialmente no Arduino. |
| RNF07 | Portabilidade | Média | A aplicação deve poder ser executada em qualquer computador com Python e acesso à BD. |
| RNF08 | Escalabilidade | Baixa/Média | A arquitetura deve permitir adicionar novos sensores/atuadores sem grandes alterações. |

# 12. Lista de Componentes IoT - Sensores, Atuadores, Controladores e Interface

## 1. Microcontrolador

### ESP32 Dev Kit
- **Tipo:** Microcontrolador com Wi-Fi e Bluetooth integrados  
- **Descrição:**  
  O ESP32 é o dispositivo central do sistema. Executa o código que lê sensores, processa a lógica de decisão, controla atuadores e gere a comunicação com o computador.  
- **Função no projeto:**  
  - Recolher dados (PIR, DHT)  
  - Controlar atuadores (LED RGB, buzzer, OLED)  
  - Enviar dados via Wi-Fi/cabo para a aplicação/base de dados  
  - Garantir a lógica de alarme e da monitorização  

---

## 2. Sensores

### 2.1 Sensor PIR (Passive Infrared Sensor)
- **Tipo:** Sensor de movimento e presença  
- **Descrição:**  
  Deteta variações de radiação infravermelha emitida pelo corpo humano. Só deteta movimento, não identifica pessoas.  
- **Função no projeto:**  
  - Detetar presença na sala  
  - Acionar o alarme  
  - Atualizar o estado da sala  

### 2.2 Sensor DHT11 (Temperatura e Humidade)
- **Tipo:** Sensor ambiental digital  
- **Descrição:**  
  Sensor capaz de medir temperatura (0–50°C) e humidade (20–80%). Usa protocolo digital próprio e comunica diretamente com o ESP32.  
- **Função no projeto:**  
  - Medir temperatura ambiente  
  - Medir humidade relativa  
  - Permitir registar e monitorizar condições da sala  
  - Acionar alarme caso os valores passem limites (quando definido)  

---

## 3. Atuadores

### 3.1 Buzzer (Alarme)
- **Tipo:** Atuador sonoro  
- **Descrição:**  
  Componente que produz som quando recebe sinal elétrico. Pode emitir som simples ou alertas automáticos.  
- **Função no projeto:**  
  - Produzir alarme sonoro em caso de intrusão  
  - Avisar o utilizador quando ocorre um evento relevante  
  - Reforçar os estados críticos do sistema  

### 3.2 LED RGB
- **Tipo:** Atuador luminoso  
- **Descrição:**  
  LED com três canais (Vermelho, Verde, Azul) que permite criar várias cores combinadas.  
- **Função no projeto:**  
  - Indicar estados do sistema:  
    - Verde: normal  
    - Vermelho: alarme  
    - Azul: standby ou configuração (possível mudança para algo mais relevante)  
  - Dar feedback visual ao utilizador  

### 3.3 Ecrã OLED 0.96" (I2C)
- **Tipo:** Dispositivo de interface / output  
- **Descrição:**  
  Ecrã monocromático de baixa potência, controlado via I2C, ideal para mostrar texto ou pequenos gráficos.  
- **Função no projeto:**  
  - Mostrar temperatura e humidade  
  - Mostrar estado da sala (presença / ausência)  
  - Mostrar notificações  

---

## 4. Interface e Conectividade

### 4.1 Módulo Wi-Fi (nativo no ESP32)
- **Tipo:** Comunicação wireless  
- **Descrição:**  
  Comunicação Wi-Fi integrada no ESP32, compatível com protocolos TCP, UDP, HTTP, MQTT.  
- **Função no projeto:**  
  - Enviar dados para o computador / servidor  
  - Permitir conectividade com a base de dados  
  - Suportar dashboards ou monitorização remota  

---

## 5. Componentes de Suporte (auxiliares)

### 5.1 Breadboard
- **Tipo:** Placa de prototipagem  
- **Descrição:**  
  Superfície que permite montar circuitos sem soldar.  
- **Função no projeto:**  
  - Ligar sensores e atuadores de forma modular  
  - Facilitar testes e alterações rápidas  

### 5.2 Cabos Dupont (M/M, M/F, F/F)
- **Tipo:** Cabos de ligação  
- **Descrição:**  
  Cabos usados para conectar o ESP32 aos sensores, atuadores e breadboard.  
- **Função no projeto:**  
  - Interligar todos os componentes eletrónicos  
  - Assegurar ligações estáveis e seguras  

### 5.3 Resistores
- **Tipo:** Componentes eletrónicos passivos  
- **Descrição:**  
  Limitam corrente elétrica, essenciais para proteger LEDs ou garantir leitura estável do buzzer.  
- **Função no projeto:**  
  - Evitar danos no LED RGB  
  - Ajustar níveis de tensão quando necessário  

---

# Lista de Software

| Software | Descrição |
|----------|-----------|
| Arduino IDE | Ambiente de desenvolvimento usado para programar o ESP32. Desenvolver, compilar e enviar código para o ESP32. |
| Bibliotecas Arduino (Adafruit_SSD1306, DHT, Wire, etc.) | Conjunto de bibliotecas para sensores e ecrã OLED. Permitem usar facilmente o OLED, DHT11 e I2C. |
| Python | Usado para scripts de comunicação, BD e dashboard. Receber dados do ESP32, processar, guardar e mostrar ao utilizador. |
| Biblioteca Python: sqlite3 / MySQL / outro | Base de dados que permite guardar dados persistentes. Armazenar leituras (temperatura/humidade/movimento) e eventos (alarme). |
| Driver USB do ESP32 | Driver de comunicação serial com o microcontrolador. Permite programar o ESP32 via cabo USB. |
| Sistema Operativo (Windows / Linux) | Sistema onde correm Python e Arduino IDE. Execução da aplicação e suporte à programação. |
