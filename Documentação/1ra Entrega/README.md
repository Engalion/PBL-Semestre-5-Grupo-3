# Proposta Inicial do Projeto

## Universidade **IADE**

## Projeto

**Sistema Inteligente de Monitorização e Segurança para Sala de Servidores**

## Elementos do Grupo

*Alejandro Agrela 20231626,
Bionda Mateus 20231666,
César Pinto 20231626*

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

### **Guião 1 – Registo de Entrada na Sala**

1. O utilizador aproxima o cartão RFID do leitor.
2. O sistema lê o ID.
3. O ESP32 envia o evento "entrada" para a API REST.
4. A API grava o evento na base de dados.
5. O dashboard mostra o nome do utilizador e timestamp.

### **Guião 2 – Alerta de Temperatura Elevada**

1. O sensor lê uma temperatura acima do limite.
2. O ESP32 envia o valor para a API.
3. A API regista o valor e atualiza o estado.
4. O sistema ativa um alerta visual e sonoro.
5. A aplicação mostra aviso de temperatura crítica.

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

* 1x ESP32
* Sensor de temperatura/humidade DHT22
* Sensor PIR
* Módulo RFID/NFC
* Sensor magnético de porta
* Buzzer / LED de alerta
* Breadboard, jumpers e alimentação

## **Software**

* Arduino IDE / PlatformIO
* Node.js / Python para API REST
* MySQL ou MariaDB
* Biblioteca Pandas e Scikit‑Learn (IA)
* GitHub

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

*(Gráfico de Gantt será inserido quando concluído.)*

---


