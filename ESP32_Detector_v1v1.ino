#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <DHT.h>             



// Configurações Wi-Fi
const char* ssid = "Claudio";
const char* password = "clf120394";
const char* userMQTT = "UserMQTT";
const char* passwordMQTT = "12345678";

// Configurações MQTT
const char* mqtt_server = "d8badc4d4c1749ea9b0f242d1e1a0c91.s1.eu.hivemq.cloud"; // IP do broker com TLS
const int mqtt_port = 8883;

static const char* ca_cert PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIFazCCA1OgAwIBAgIRAIIQz7DSQONZRGPgu2OCiwAwDQYJKoZIhvcNAQELBQAw
TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh
cmNoIEdyb3VwMRUwEwYDVQQDEwxJU1JHIFJvb3QgWDEwHhcNMTUwNjA0MTEwNDM4
WhcNMzUwNjA0MTEwNDM4WjBPMQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJu
ZXQgU2VjdXJpdHkgUmVzZWFyY2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBY
MTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBAK3oJHP0FDfzm54rVygc
h77ct984kIxuPOZXoHj3dcKi/vVqbvYATyjb3miGbESTtrFj/RQSa78f0uoxmyF+
0TM8ukj13Xnfs7j/EvEhmkvBioZxaUpmZmyPfjxwv60pIgbz5MDmgK7iS4+3mX6U
A5/TR5d8mUgjU+g4rk8Kb4Mu0UlXjIB0ttov0DiNewNwIRt18jA8+o+u3dpjq+sW
T8KOEUt+zwvo/7V3LvSye0rgTBIlDHCNAymg4VMk7BPZ7hm/ELNKjD+Jo2FR3qyH
B5T0Y3HsLuJvW5iB4YlcNHlsdu87kGJ55tukmi8mxdAQ4Q7e2RCOFvu396j3x+UC
B5iPNgiV5+I3lg02dZ77DnKxHZu8A/lJBdiB3QW0KtZB6awBdpUKD9jf1b0SHzUv
KBds0pjBqAlkd25HN7rOrFleaJ1/ctaJxQZBKT5ZPt0m9STJEadao0xAH0ahmbWn
OlFuhjuefXKnEgV4We0+UXgVCwOPjdAvBbI+e0ocS3MFEvzG6uBQE3xDk3SzynTn
jh8BCNAw1FtxNrQHusEwMFxIt4I7mKZ9YIqioymCzLq9gwQbooMDQaHWBfEbwrbw
qHyGO0aoSCqI3Haadr8faqU9GY/rOPNk3sgrDQoo//fb4hVC1CLQJ13hef4Y53CI
rU7m2Ys6xt0nUW7/vGT1M0NPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNV
HRMBAf8EBTADAQH/MB0GA1UdDgQWBBR5tFnme7bl5AFzgAiIyBpY9umbbjANBgkq
hkiG9w0BAQsFAAOCAgEAVR9YqbyyqFDQDLHYGmkgJykIrGF1XIpu+ILlaS/V9lZL
ubhzEFnTIZd+50xx+7LSYK05qAvqFyFWhfFQDlnrzuBZ6brJFe+GnY+EgPbk6ZGQ
3BebYhtF8GaV0nxvwuo77x/Py9auJ/GpsMiu/X1+mvoiBOv/2X/qkSsisRcOj/KK
NFtY2PwByVS5uCbMiogziUwthDyC3+6WVwW6LLv3xLfHTjuCvjHIInNzktHCgKQ5
ORAzI4JMPJ+GslWYHb4phowim57iaztXOoJwTdwJx4nLCgdNbOhdjsnvzqvHu7Ur
TkXWStAmzOVyyghqpZXjFaH3pO3JLF+l+/+sKAIuvtd7u+Nxe5AW0wdeRlN8NwdC
jNPElpzVmbUq4JUagEiuTDkHzsxHpFKVK7q4+63SM1N95R1NbdWhscdCb+ZAJzVc
oyi3B43njTOQ5yOf+1CceWxG1bQVs5ZufpsMljq4Ui0/1lvh+wjChP4kqKOJ2qxq
4RgqsahDYVvTH9w7jXbyLeiNdd8XM2w9U/t7y0Ff/9yi0GE44Za4rF2LN9d11TPA
mRGunUHBcnWEvgJBQl9nJEiU0Zsnvgc/ubhPgXRR4Xq37Z0j4r7g1SgEEzwxA57d
emyPxgcYxn/eR44/KJ4EBs+lVDR3veyJm+kXQ99b21/+jh5Xos1AnX5iItreGCc=
-----END CERTIFICATE-----
)EOF";
// Tópicos MQTT
const char* topicTemperatura = "GRUPO1/ESP32_1/temperatura";
const char* topicUmidade = "GRUPO1/ESP32_1/umidade";
const char* topicFlameChame = "GRUPO1/ESP32_1/flame_chame";
const char* topicGas = "GRUPO1/ESP32_1/sensor_gas";
const char* topicBuzzer = "GRUPO1/ESP32_1/buzzer";
const char* topicMensajem = "GRUPO1/ESP32_1/mensajem";
const char* topicBuzzerManual = "GRUPO1/ESP32_1/buzzer_manual";

#define DHTPIN 14 
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);


const int GAS_PIN = 19;
const int FLAME_PIN = 21;
const int DESLIGAR_PIN = 0;


const int BUZZER_PIN = 23;

// Cliente MQTT com TLS
WiFiClientSecure espClient;
PubSubClient client(espClient);


bool isConnected = false;
unsigned long lastStatusUpdate = 0;

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  Serial.print("Conectando-se à rede Wi-Fi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nConectado à rede Wi-Fi");
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  Serial.print("Mensagem recebida no tópico ");
  Serial.print(topic);
  Serial.print(": ");
  Serial.println(message);
  
  if (String(topic) == topicBuzzerManual) {
    if (message == "ON") {
      digitalWrite(BUZZER_PIN, HIGH);
      client.publish(topicBuzzer, "ON");
      client.publish(topicMensajem, "BUZZER ATIVADO REMOTAMENTE");
    } else if (message == "OFF") {
      digitalWrite(BUZZER_PIN, LOW);
      client.publish(topicBuzzer, "OFF");
      client.publish(topicMensajem, "BUZZER DESATIVADO REMOTAMENTE");
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Tentando conexão MQTT...");
    if (client.connect("ESP32Client",userMQTT,passwordMQTT)) {
      Serial.println("Conectado ao MQTT");
      client.subscribe(topicBuzzerManual);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin(); 
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GAS_PIN, INPUT_PULLUP);
  pinMode(FLAME_PIN, INPUT_PULLUP);
  pinMode(DESLIGAR_PIN, INPUT_PULLUP);
  
  setup_wifi();
  // Configurar certificado da CA
  espClient.setCACert(ca_cert);
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  
  if (isnan(h) || isnan(t)) {
    client.publish(topicMensajem, "ERRO AO LER O SENSOR DHT22");
    Serial.println("Erro ao ler o sensor DHT22");
  }else{
  
    client.publish(topicTemperatura, String(t).c_str());
    client.publish(topicUmidade, String(h).c_str());
    Serial.println("Temperatura: " + String(t) + "°C Umedade: " + String(h) + "%");
  }
  if(!digitalRead(BUZZER_PIN)&&t>60.0){
    digitalWrite(BUZZER_PIN,HIGH);
    client.publish(topicBuzzer, "ON");
    client.publish(topicMensajem, "BUZZER ATIVADO POR TEMPERATURA ELEVADA");
  }

  //
  static bool isGasAlarm = false;
  static bool isFlameAlarm = false;

  if(!digitalRead(GAS_PIN)){
    client.publish(topicGas, "ON");
    if(!isGasAlarm){
      isGasAlarm = true;
      digitalWrite(BUZZER_PIN,LOW);
      client.publish(topicBuzzer, "ON");
      client.publish(topicMensajem, "BUZZER ATIVADO POR DETECÇÃO DE GÁS");
    }
  }else{
    client.publish(topicGas, "OFF");
    if(isGasAlarm){
      isGasAlarm = false;
    }
  }

  if(!digitalRead(FLAME_PIN)){
    client.publish(topicFlameChame, "ON");
    if(!isGasAlarm){
      isGasAlarm = true;
      digitalWrite(BUZZER_PIN,HIGH);
      client.publish(topicBuzzer, "ON");
      client.publish(topicMensajem, "BUZZER ATIVADO POR DETECÇÃO DE CHAMA");
    }
  }else{
    client.publish(topicFlameChame, "OFF");
    if(isGasAlarm){
      isFlameAlarm = false;
    }
  }

  if(!digitalRead(DESLIGAR_PIN)){
    digitalWrite(BUZZER_PIN,LOW);
    client.publish(topicBuzzer, "OFF");
    client.publish(topicMensajem, "BUZZER DESATIVADO MANUALMENTE");
  }


  delay(2000);
  // Atualizar status periodicamente
}
