Funcionamento
O sensor DHT22 possui três pinos: VCC que é o positivo, GND que representa o negativo e o D de saída de dados. No protótipo, o pino positivo é conectado ao 3v do ESP32, o GND e conectado no GND da placa, e o pino de dados é conectado ao D14. A precisão do modulo sensor e de mais ou menos 0,5 Graus para temperatura e 2% para umidade.
O modulo de sensor Fogo Flame Chame possui três pinos: VCC que é o positivo, GND que representa o negativo e o D de saída de dados. No protótipo, o pino positivo é conectado ao 3v do ESP32, o GND e conectado no GND da placa, e o pino de dados é conectado ao D21. Quando há fogo no ambiente, o sensor é acionado e é disparado a buzina do sensor Buzzer.
O modulo de sensor de gás Mq-2 possui três pinos: VCC que é o positivo, GND que representa o negativo e o D de saída de dados. No protótipo, o pino positivo é conectado ao 3v do ESP32, o GND e conectado no GND da placa, e o pino de dados é conectado ao D19. Quando há fumaça no ambiente, o sensor é acionado e é disparado a buzina do sensor Buzzer.
O modulo sensor Buzzer ativo possui três pinos: VCC que é o positivo, GND que representa o negativo e o D de saída de dados. No protótipo, o pino positivo é conectado ao 3v do ESP32, o GND e conectado no GND da placa, e o pino de dados é conectado ao D23. Quando o sensor Flame Chame detectar fogo o modulo Buzzer é acionado.
Para o funcionamento da placa ESP32, ela foi conectada ao notebook através de um cabo mini USB, sendo que para conectar ao Wi-Fi e ao Broken, foi preciso informar os dados da rede de Wi-Fi como nome da rede (SSID), senha e dados do Broken como userMQTT e passwordMQTT.
Para rodar o programa na placa ESP32 foi utilizado a IDE do Arduino já com as bibliotecas ESP32 devidamente instaladas.
A placa foi plugada numa protoboard através dos pinos 15 ao 30.
A plataforma Node-RED foi utilizada para interligar o dispositivo físico através de nós utilizando um navegador. 
O feeds de temperatura e umidade foram configurados através de um dashboard, gráfico do tipo gague, permitindo o monitoramento em tempo real, foram criados dois label, um para fogo e um para fumaça e um botão de mensagem nas cores verde(desativado) e vermelho(ativado).
A ESP32 é uma placa de desenvolvimento de hardware aberto que é baseada em um processador dual-core de 32 bits e possui 520KB de memória flash. Possui Wi-Fi e Bluetooth integrados, o que elimina a necessidade de comprar módulos separados sendo essa uma grande vantagem em relação ao Arduino.
A placa ESP32 é uma plataforma versátil para o desenvolvimento de projetos eletrônicos, como dispositivos de automação residencial, soluções Iot, monitoramento veicular, rastreamento de frota entre outros.
Um broker MQTT é um servidor central que gerencia a comunicação entre dispositivos loT.
Sensor de fogo Flame Chame e utilizado para verificar a presença de fogo ou fontes de calor.
Ele recebe mensagens de dispositivos que publicam dados e as distribui para dispositivos que estão inscritos nos tópicos correspondentes. O broker atua como intermediário, garantindo que as mensagens cheguem aos dispositivos certos, sem que eles precisem se conectar diretamente uns aos outros.
O sensor MQ-2 é um detector de gás e fumaça que pode indicar a presença de GLP, Propano, Metano, Hidrogênio e outros tipos de gases. Seu nível de detecção vai de 300 a 10.000 ppm, ajustáveis por um potenciômetro na parte de trás do modulo. Um chip comparador LM393 é o responsável por ler as informações do sensor e converter as informações para o microcontrolador.
O DHT22-AM2302 é um sensor de temperatura digital que utiliza um sensor capacitivo e um termistor para medir o ar circundante e emite um sinal digital no pino dos dados.
Buzzer Componente para adicionar efeitos sonoros indicado para projetos eletrônicos como alarme, sistemas de sinalização e jogos. 
Buzzer é um dispositivo para geração de sinais sonoros (beeps), como aqueles encontrados em computadores. Para a emissão do som, o buzzer vibra através de um oscilador. Essa oscilação é determinada por uma frequência, que por sua vez define um som específico
Protoboard Placa que permite que os componentes eletrônicos possam ser interligados em um número quase infinito de maneiras para produzir circuitos eletrônicos em trabalhos de prototipagem.
Configurações do internet e protocolo MQTT: const char* 
  ssid = "Claudio";
const char* password = "xxxxxxx";
const char* userMQTT = "UserMQTT";
const char* passwordMQTT = "12345678";
const char* mqtt_server = "d8badc4d4c1749ea9b0f242d1e1a0c91.s1.eu.hivemq.cloud"; // IP do broker com TLS
const int mqtt_port = 8883;
