# Proposta Inicial do Projeto

## Universidade **IADE**

## Projeto

**SecureRoom – Proteção de Bastidores de Servidores**

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

O sistema recolhe dados através de sensores instalados, envia‑os para um servidor via REST API, armazena numa base de dados, integrando também dados externos.

---

# 2. Público‑Alvo

* Pequenas e médias empresas com salas de servidores.
* Instituições que necessitam monitorizar ambientes críticos.
* Equipas de IT responsáveis por infraestruturas técnicas.

---

# 3. Guiões de Teste 

## 1. Testes de Sensores e Monitorização (RF01, RF02, RNF01)

---

### 🧪 **Teste 1 — Deteção de Movimento (PIR)**
**Objetivo:** Validar que o sensor PIR deteta presença corretamente.  
**RF associado:** RF01  
**Pré-condições:** ESP32 ligado; PIR funcional.

**Passos:**
1. Ligar o sistema e aguardar inicialização.
2. Garantir ausência de movimento por 10 segundos.
3. Caminhar na zona de deteção.
4. Observar LED, OLED e logs.

**Resultados esperados:**
- Estado muda para **"Presença Detetada"** em <1s.  
- LED passa a vermelho (alarme).  
- Evento registado e enviado para o servidor.

---

### 🧪 **Teste 2 — Leitura de Temperatura e Humidade (DHT)**
**Objetivo:** Verificar leituras de temperatura e humidade.  
**RF associado:** RF02

**Passos:**
1. Ligar o sistema.
2. Verificar valores no OLED ou consola.
3. Aumentar temperatura aproximando a mão.
4. Observar atualização dos valores.

**Resultados esperados:**
- Leituras atualizadas a cada 2–5s.  
- Valores coerentes com ambiente real.  
- Dados enviados à API.

---

## 2. Testes da Interface OLED (RF03, RNF03)

---

### 🧪 **Teste 3 — Atualização do Display OLED**
**Objetivo:** Validar informação apresentada no OLED.  
**RF associado:** RF03

**Passos:**
1. Ligar sistema.
2. Confirmar que OLED mostra temperatura, humidade e estado.
3. Criar movimento e verificar atualização do estado.

**Resultados esperados:**
- Texto legível.  
- Atualização automática sem falhas.

---

## 3. Testes dos Atuadores (RF04, RF05)

---

### 🧪 **Teste 4 — Ativação do Buzzer**
**Objetivo:** Verificar funcionamento do alarme sonoro.  
**RF associado:** RF04

**Passos:**
1. Simular intrusão com movimento no PIR.
2. Observar ativação do buzzer.

**Resultados esperados:**
- Buzzer ativa instantaneamente (<1s).  
- Evento enviado ao servidor.

---

### 🧪 **Teste 5 — LED RGB (Sinalização de Estados)**
**Objetivo:** Validar mudança de cores conforme estado.  
**RF associado:** RF05

**Resultados esperados:**
- Verde → Sistema normal.  
- Vermelho → Alarme/intrusão.  
- Azul → Standby/configuração.

---

## 4. Testes de Comunicação ESP32 → API → BD (RF06, RF07, RNF04, RNF05)

---

### 🧪 **Teste 6 — Envio de Dados para a API**
**Objetivo:** Confirmar transmissão de dados.  
**RF associado:** RF06

**Passos:**
1. Ligar o ESP32 com Wi-Fi ativo.
2. Observar consola/logs da API.
3. Confirmar receção de JSONs com leituras.

**Resultados esperados:**
- API recebe dados com código 200 OK.  
- Sem perda de mensagens.

---

### 🧪 **Teste 7 — Registo de Dados na Base de Dados**
**Objetivo:** Garantir armazenamento persistente.  
**RF associado:** RF07

**Passos:**
1. Forçar 5 leituras do ESP32.
2. Abrir BD.
3. Verificar se as entradas foram criadas.

**Resultados esperados:**
- Todas as leituras registadas.  
- Campos completos com timestamp.

---

## 5. Testes de Consulta e Gestão (RF08, RF09)

---

### 🧪 **Teste 8 — Consulta de Histórico**
**Objetivo:** Validar consulta de registos guardados.  
**RF associado:** RF08

**Passos:**
1. Abrir a aplicação/dashboard.
2. Selecionar intervalo de datas.
3. Ver dados listados.

**Resultados esperados:**
- Mostra leituras corretas.  
- Sem erros de ligação.

---

### 🧪 **Teste 9 — Autorização por RFID e Desativação do Alarme**
**Objetivo:** Verificar que o alarme pode ser desativado através de cartão RFID.  
**RF associado:** RF09  

**Passos:**
1. Ativar alarme através de deteção de movimento (PIR).
2. Aproximar um cartão RFID autorizado do leitor RC522.
3. Confirmar mudança do estado da sala.

**Resultados esperados:**
- LED vermelho desativa imediatamente.  
- Buzzer silencia no mesmo instante.  
- O novo movimento NÃO reativa o alarme enquanto a sessão estiver autorizada.  
- Evento de autenticação (data/hora, ID do cartão) registado na BD.

---

## 6. Testes Não Funcionais (RNF01–RNF08)

---

### 🧪 **Teste 10 — Desempenho e Latência**
**Objetivo:** Medir tempo de resposta do sistema.  
**RNF associado:** RNF01

**Resultados esperados:**
- Deteção PIR → reação <1s.  
- Leituras DHT → intervalo 2–5s.

---

### 🧪 **Teste 11 — Estabilidade (8–24h)**
**Objetivo:** Validar fiabilidade prolongada.  
**RNF associado:** RNF02

**Resultados esperados:**
- Sistema opera 8–24h sem reiniciar.  
- Sem falhas de ligação.

---

### 🧪 **Teste 12 — Segurança da Comunicação**
**Objetivo:** Garantir proteção dos dados.  
**RNF associado:** RNF04

**Resultados esperados:**
- Nenhuma password exposta no código.  
- Wi-Fi configurado em rede protegida.

---

### 🧪 **Teste 13 — Portabilidade**
**Objetivo:** Confirmar execução em diferentes ambientes.  
**RNF associado:** RNF07

**Resultados esperados:**
- Script Python executa em Windows e Linux.  
- BD acessível com dependências instaladas.

---

## ✅ **Resumo**
Este conjunto de guiões cobre:
- Todos os **RF01–RF09**  
- Todos os **RNF relevantes**  
- Sensores, atuadores, comunicação, BD, API e lógica de alarme  

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
* Leitor RFID RC522
* Cartão/Tag RFID compatível

## **Software**

* Arduino Ide
* Python ide
* Base de Dados
* Código php

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
* Leitor RFID RC522 montado no exterior da caixa para permitir autenticação.  
* Cartão RFID associado aos utilizadores autorizados.

<img width="1217" height="1164" alt="image" src="https://github.com/user-attachments/assets/38eeb3f0-e339-474e-86e9-50b9aa33c25e" />


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
* RFID RC522 – 1  
* Cartão/Tag RFID – 1 

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

| ID   | Categoria      | Prioridade | Descrição |
|------|----------------|------------|-----------|
| RF01 | Monitorizar    | Alta | O sistema deverá detetar a presença de pessoas na sala através do sensor de movimento (PIR). |
| RF02 | Monitorizar    | Alta | O sistema deverá medir a temperatura e a humidade ambiente em intervalos regulares ou definidos pelo gestor da segurança (equipa de TI, equipa de cybersecurity). |
| RF03 | Interface OLED | Média | O sistema mostrará no ecrã OLED os valores atuais de temperatura, humidade e o estado da sala (com presença ou sem presença). |
| RF04 | Alarme         | Alta | O sistema ativará o buzzer quando for detetada uma condição de alarme (por exemplo, intrusão ou limite de temperatura ou humidade ultrapassados) e será desativado se as condições voltarem ao normal ou pelo gestor/administrador responsável. |
| RF05 | Sinalização    | Alta | O sistema indicará o estado da sala através do LED RGB (ex.: verde = normal, vermelho = alarme, azul = standby/configuração). |
| RF06 | Comunicação    | Alta | O sistema deve enviar periodicamente para o computador/base de dados as leituras de temperatura, humidade, estado de presença e eventos de alarme, para posterior análise e tratamento com inteligência artificial. |
| RF07 | Armazenamento  | Alta | A aplicação vai guardar na base de dados as leituras e eventos recebidos do ESP32. |
| RF08 | Consulta       | Média | A aplicação deve permitir consultar o histórico de leituras e eventos (por data/hora) através da base de dados. |
| RF09 | Gestão         | Alta | O sistema deverá permitir que um utilizador autorizado desative o alarme por um período configurável mediante autenticação por cartão RFID. O sistema deve registar o evento (data/hora e utilizador) na base de dados. |

## 11. Requisitos Não Funcionais (RNF)

| ID    | Categoria            | Prioridade | Descrição |
|-------|----------------------|------------|-----------|
| RNF01 | Desempenho           | Alta | O sistema deve atualizar a leitura da temperatura e humidade pelo menos a cada 2–5 segundos e reagir a movimento em menos de 1 segundo. |
| RNF02 | Fiabilidade          | Alta | O sistema deve conseguir funcionar continuamente durante 24 horas sem necessidade de reiniciar. |
| RNF03 | Usabilidade          | Média | As mensagens no ecrã OLED devem ser claras e legíveis, usando abreviações simples (ex.: “T: 24°C, H: 60%”). |
| RNF04 | Segurança            | Alta | A comunicação entre o ESP32 e o computador deve ser feita numa rede protegida e o código final não deve expor credenciais em texto simples. |
| RNF05 | Integridade dos Dados| Alta | A aplicação em Python deve garantir que todas as mensagens válidas recebidas do ESP32 são registadas na base de dados sem perda de informação. |
| RNF06 | Manutenção           | Média | O código deve ser organizado em módulos/funções para facilitar alterações futuras (ex.: troca de sensor, ajuste de limites de alarme). |
| RNF07 | Portabilidade        | Média | A aplicação em Python deve ser executável em Windows e Linux com Python 3.x. O código Arduino deve ser compatível com placas ESP32 standard. |
| RNF08 | Escalabilidade       | Baixa/Média | A arquitetura deve permitir a adição futura de novos sensores ou atuadores sem grandes alterações. |

## **Notas sobre prioridade**

- **Prioridade Alta = Essencial**  
  (Obrigatório para o funcionamento central do projeto)

- **Prioridade Média = “Good to have”**  
  (Melhora o uso, mas não compromete o essencial)
  
## 12. Lista de Componentes IoT - Sensores, Atuadores, Controladores e Interface

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

## 2.3 Leitor RFID RC522
- **Tipo:** Sensor de identificação por radiofrequência  
- **Descrição:**  
  O módulo RFID RC522 permite ler e escrever cartões/tag RFID utilizando comunicação SPI. É amplamente usado para controlo de acessos devido ao baixo custo e simplicidade.  
- **Função no projeto:**  
  - Controlar o acesso à sala de servidores via cartão RFID  
  - Registar entradas autorizadas e tentativas falhadas  
  - Complementar o sensor PIR com autenticação  
  - Aumentar a segurança física do sistema  

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
| PHP | Usado para a ligação entre sensores, controlo de acessos e base de dados. Permite criar APIs, páginas web e gerir a comunicação entre o sistema e o utilizador. |

---

## 13. DIAGRAMA DE ARQUITETURA (ASCII)

                          ┌──────────────────────────────┐
                          │       Utilizador             │
                          │ (Cartão RFID / Observação)   │
                          └─────────────┬────────────────┘
                                        │
                                        ▼
                          ┌──────────────────────────────┐
                          │         Sensor RFID          │
                          │          RC522               │
                          └─────────────┬────────────────┘
                                        │ UID
                                        ▼
                    ┌──────────────────────────────┐
                    │         ESP32 / Arduino      │
                    │──────────────────────────────│
                    │ - Lê RFID (RC522)            │
                    │ - Lê sensor DHT11 (Temp/HR)  │
                    │ - Lê LDR (Luminosidade)      │
                    │ - Mostra info no OLED        │
                    │ - Controla buzzer/LEDs       │
                    │ - Envia dados via Wi-Fi      │
                    └──────────────┬───────────────┘
                                   │ HTTP POST
                                   ▼
                ┌────────────────────────────────────────────┐
                │                  Servidor PHP              │
                │ (acessos.php / sensores.php / db.php)      │
                └───────────────────┬────────────────────────┘
                                    │ Escreve / Lê
                                    ▼
                        ┌──────────────────────────────┐
                        │         Base de Dados        │
                        │    (MySQL/MariaDB)           │
                        │ - Logs de acessos RFID       │
                        │ - Registos dos sensores      │
                        └──────────────────────────────┘


---

## 14. DESCRIÇÃO DA SOLUÇÃO

O projeto consiste num sistema de controlo de acessos e monitorização ambiental, utilizando um microcontrolador ESP32/Arduino ligado a sensores e a um servidor web.

O sistema desempenha três funções principais:

### 1. Controlo de Acessos com RFID (RC522)

- O utilizador aproxima um cartão RFID.
- O ESP32 lê o UID do cartão.
- O microcontrolador envia o UID para o servidor via HTTP.
- O servidor (acessos.php) guarda o registo e devolve permitido / negado.
- O ESP32 mostra o estado no display OLED e ativa LEDs e buzzer.

### 2. Monitorização Ambiental

- O ESP32 lê periodicamente:
  - Temperatura (DHT11)
  - Humidade (DHT11)
  - Luminosidade (LDR)
- Estes dados são enviados para o servidor (sensores.php) e guardados numa base de dados.

### 3. Interface e Feedback Local

O sistema inclui:

- Display OLED para visualização de cartões, temperatura e humidade.
- LEDs verde/vermelho como indicação de acesso.
- Buzzer para avisos sonoros.
- Wi-Fi para comunicação com o servidor.

---

## 15. ARQUITETURA IMPLEMENTADA (DETALHADA)

A arquitetura é dividida em três camadas:

## Camada 1 — Hardware / Sensores

**Sensores:**

- RC522 (RFID) — Leitura de cartões/tag NFC.
- DHT11 — Mede temperatura e humidade.
- LDR — Mede luminosidade ambiente.

**Atuadores:**

- LED verde — acesso autorizado.
- LED vermelho — acesso negado.
- LED azul — (futura possível adição)
- Buzzer — aviso sonoro.

**Interface:**

- Display OLED I2C — mostra dados dos sensores e informações do acesso.

## Camada 2 — Microcontrolador (ESP32 / NodeMCU)

**Funções do ESP32:**

**Leitura de Sensores**

- UID do RC522 (via SPI).
- Temperatura e Humidade do DHT11.
- Luminosidade (LDR → analógico).

**Processamento**

- Identificação do cartão.
- Geração de alertas (LEDs/buzzer).
- Escrita no display OLED.

**Comunicação**

- Conexão Wi-Fi.
- Envio de dados por HTTP POST para:
  - acessos.php
  - sensores.php

**Bibliotecas Utilizadas**

- MFRC522 → RFID
- DHT → Temperatura e humidade
- Adafruit_SSD1306 → OLED
- HTTPClient → Comunicação HTTP
- WiFi.h → Wi-Fi

## Camada 3 — Servidor Web + Base de Dados

**Scripts PHP**

- db.php → ligação à base de dados
- acessos.php → processa e regista UID
- sensores.php → recebe dados ambientais

**Base de Dados MySQL**

**Tabelas típicas:**

- acessos
  - UID
  - data/hora
  - estado (permitido / negado)
- sensores
  - temperatura
  - humidade
  - luminosidade
  - timestamp
- utilizadores 
  - nome
  - UID autorizado
---

## 16. Funcionamento Geral

- O utilizador aproxima o cartão RFID do leitor.
- O ESP32 lê a UID e comunica com o servidor.
- O servidor regista e devolve o estado.
- O ESP32 mostra no OLED e acende LEDs.
- O ESP32 mede periodicamente os sensores ambientais.
- Os valores são enviados ao servidor e guardados em MySQL.

---

## 17. Diagrama de Circuitos. 

<img width="1600" height="935" alt="image" src="https://github.com/user-attachments/assets/e0c42b02-4318-44e5-a952-486470f8e8e4" />

---

## 18. Fotos do Artefacto.


---

## 19. Plano de Testes.

**Tipos de Testes Aplicados**

| Categoria        | Tipo de Teste     | Aplicabilidade | Justificação |
|------------------|------------------|---------------|--------------|
| Funcional        | Unitário         | Sim           | Validar individualmente os requisitos RF01, RF02, RF03, RF04 e RF05 |
| Funcional        | Integração       | Sim           | Validar RF06 e RF07 (ESP32 → aplicação → BD) |
| Funcional        | Aceitação        | Sim           | Verificar se todos os RF cumprem os objetivos do SecureRoom |
| Funcional        | Sistema (E2E)    | Sim           | Validar o fluxo completo RF01–RF08 |
| Funcional        | Regressão        | Sim           | Garantir que alterações não afetam RF existentes |
| Não Funcional    | Performance      | Sim           | Avaliar RNF01 |
| Não Funcional    | Usabilidade      | Sim           | Avaliar RNF03 |
| Não Funcional    | Robustez         | Sim           | Avaliar RNF02 |
| Não Funcional    | Carga            | Não           | Sistema apenas para um dispositivo |
| Não Funcional    | Stress           | Não           | Evitar danos no hardware |
| Não Funcional    | Segurança        | Não           | Sistema em rede local controlada |

**Casos de Testes**

| ID Caso | Requisito | Caso de Teste | Pré-condição | Passos | Resultado Esperado |
|--------|-----------|---------------|--------------|--------|-------------------|
| CT01 | RF01 | Deteção de presença | ESP32 ligado | Simular movimento | Evento de presença detetado |
| CT02 | RF02 | Medição T/H | Sensores ativos | Aguardar ciclo de leitura | Valores de T/H obtidos |
| CT03 | RF03 | Visualização OLED | Sistema em execução | Observar OLED | Valores e estado visíveis |
| CT04 | RF04 | Alarme sonoro | Limite ultrapassado | Forçar condição de alarme | Buzzer ativado |
| CT05 | RF05 | LED RGB | Sistema ativo | Simular estados | Cor corresponde ao estado |
| CT06 | RF06 | Envio de dados | Wi-Fi ativo | ESP32 envia dados | Dados recebidos pela aplicação |
| CT07 | RF07 | Armazenamento | BD ativa | Consultar BD | Registos guardados |
| CT08 | RF08 | Consulta de histórico | Dados existentes | Filtrar por data | Histórico apresentado |
| CT09 | RNF02 | Robustez | Sistema ativo | Desligar servidor | Sistema recupera |
| CT10 | RNF06 | Manutenção humidade | Código base | Alterar limite | Alteração simples |
| CT11 | RNF06 | Manutenção temperatura | Código base | Alterar limite | Alteração simples |
| CT12 | RF02 | Temperatura no limite | Sistema ativo | Forçar valor limite | Não dispara alarme |
| CT13 | RF02 | Temperatura acima limite | Sistema ativo | Forçar valor acima | Alarme ativado |
| CT14 | RF02 | Humidade no limite | Sistema ativo | Forçar valor limite | Não dispara alarme |
| CT15 | RF02 | Humidade acima limite | Sistema ativo | Forçar valor acima | Alarme ativado |
| CT16 | RF01 | Falha sensor presença | Sistema ativo | Desligar sensor | Nenhum falso alarme |
| CT17 | RF06 | Perda de Wi-Fi | Wi-Fi ativo | Cortar ligação | Dados enviados após retorno |
| CT18 | RNF01 | Tempo de envio | Sistema ativo | Medir tempo | < X segundos |
| CT20 | RNF08 | Acesso sem login | Web | Abrir index.php | Redireciona para login |
| CT21 | RNF08 | Login válido | Web | User/pass corretos | Entra no dashboard |
| CT22 | RNF08 | Login inválido | Web | Credenciais erradas | Mensagem de erro |
| CT23 | RNF08 | Campos vazios | Web | Submeter vazio | Mensagem de erro |
| CT24 | RNF08 | Logout | Web | Logout + back | Sem acesso |
| CT25 | RNF04 | UI admin | Web | Login user | Sem opções admin |
| CT26 | RNF04 | Filtros | Web | Admin vs user | Opções diferentes |
| CT27 | RF08 | Filtro temperatura | Web | Filtrar | Só temperatura |
| CT28 | RF08 | Filtro humidade | Web | Filtrar | Só humidade |
| CT29 | RF08 | Filtro movimento | Web | Filtrar | Só movimento |

## MÉTRICAS DE EXECUÇÃO E EFICÁCIA

Estas métricas avaliam a saúde geral do ciclo de testes e a cobertura das funcionalidades planeadas.

---

### Taxa de Sucesso dos Casos de Teste (TSCT)

A Taxa de Sucesso dos Casos de Teste (TSCT) mede a percentagem de testes executados que passaram sem falhas críticas.

**Resultado obtido:**
- Testes executados: 10  
- Testes com sucesso: 10  

**Aplicação:**

Para o SecureRoom, a meta definida foi **TSCT = 100%** nos testes funcionais e de integração, garantindo que todas as funcionalidades críticas operam conforme o esperado.

---

### Eficiência de Remoção de Defeitos (ERD)

A Eficiência de Remoção de Defeitos (ERD) avalia a capacidade da equipa em identificar e corrigir falhas antes da fase final de demonstração.

**Resultado:**
- Todos os defeitos identificados durante os testes foram corrigidos antes da validação final.

**Meta:**
- Garantir que nenhum defeito de severidade crítica permanece no sistema, nomeadamente falhas de deteção ou perda de dados.

---

## 20. Estrutura do Projeto

<img width="870" height="1536" alt="image" src="https://github.com/user-attachments/assets/6e584577-0b1f-4cc1-b2c6-68d9834b2127" />

## 📁 Raiz (C:\)
Arquivos gerais do projeto, principalmente o banco de dados.

- acessos.sql → script SQL da tabela de acessos  
- users.sql → script SQL da tabela de usuários  
- sensores.sql → script SQL da tabela de sensores  
- PBL_BD.sql → banco de dados completo do projeto  

---

## 📁 htdocs
Pasta do servidor web (Apache/XAMPP). Tudo aqui faz parte do dashboard.

### Arquivos principais
- index.php → página inicial  
- login.php → tela de login  
- logout.php → encerra a sessão  
- auth.php → controle de autenticação  
- db.php → conexão com o banco de dados  

### Funcionalidades
- acessos.php → visualização dos acessos  
- sensores.php → dados dos sensores  
- graficos.php → gráficos do sistema  
- forecast.php → página de previsões  
- export_csv.php → exportação de dados em CSV  

### Administração
- admin_users.php → gerenciamento de usuários  
- admin_cards.php → gerenciamento de cartões  

### Estilo
- style.css → aparência do site  

---

## 📁 htdocs/ai
Módulos de Inteligência Artificial em Python.

- train_arima_temp.py → treino do modelo ARIMA  
- model_temp_arima.pkl → modelo treinado  
- forecast_temp.py → previsão usando o modelo  

---

## 📁 htdocs/api
API para comunicação entre site, IA e dispositivos.

- data.php → fornece dados via API  
- forecast_temp.php → endpoint de previsão de temperatura  

---

## 📁 PBL_ABC_vs1
Código do Arduino.

- PBL_ABC_vs1.ino → código principal do microcontrolador  

---

## 📁 PBL_ABC_vs1/data
Bibliotecas usadas no Arduino (display e gráficos).

- Adafruit-GFX-Library  
- Adafruit_SSD1306  
- u8g2  

---

## 21. Enquadramento

No contexto do projeto desenvolvido no âmbito do Problem Based Learning (PBL) do quinto
semestre, foi implementado um módulo de previsão de temperatura com o objetivo de enriquecer
o sistema com uma componente preditiva baseada em dados históricos.
A inclusão de um mecanismo de previsão permite não só analisar o comportamento passado da
variável temperatura, mas também antecipar a sua evolução futura, acrescentando valor analítico
ao sistema e aproximando-o de um cenário real de monitorização inteligente.

---

### 22. Resumo. 

A implementação do modelo ARIMA permitiu dotar o projeto de uma componente preditiva
sólida e tecnicamente fundamentada.
O módulo desenvolvido demonstra a aplicação prática de conceitos de análise de séries
temporais, integrando-se de forma coerente no sistema global do PBL e contribuindo para a
maturidade técnica do projeto.
