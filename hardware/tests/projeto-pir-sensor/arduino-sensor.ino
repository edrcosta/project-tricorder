#include <ESP8266WiFi.h> //Import biblioteca de wi fi 
#include <PubSubClient.h>//import biblioteca de cliente do MQTT 

//Criar variáveis para armazenar configurações 
const char* ssid = "AndroidAP9E78aa";//Nome do rede wi fi 
const char* password = "foxc2940aa";//senha da rede wi fi 
const char* mqtt_server = "broker.mqtt-dashboard.com";//endereço do servidor MQTT 

//Cria variável para o cliente de wifi 
WiFiClient espClient;
//Cria uma variavel para o cliente MQTT 
PubSubClient client(espClient);

//Cira variavel para armaezenar mensagens mqtt 
  String msgFromMQTT = "";

//Função de connexão do wi fi 
  void setup_wifi() {

    delay(10);//espear 10 miliseconds 
    
    //escreve no serial monitor que está connectando no wi fi X
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    //tenta conexão 
    WiFi.begin(ssid, password);

  //enquanto o wi fi não estiver connectado 
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);//Espera 
      Serial.print(".");//imprime "."
    }
    
    //inicializa gerador de números aleatórios para ser usado mais tarde
    randomSeed(micros());
    
    //Escreve no serial monitor que conseguiu conectar na rede wi fi e o ip do NODE MCU NA REDE 
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

//Funcao chamada quando recebe mensagem MQTT 
  void callback(char* topic, byte* payload, unsigned int length) {
    msgFromMQTT="";//zera variável de saida de mensagens 
    
    //escreve na serial monitor que chegou uma mensagem 
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");

    ///salva na variável de armazenamento de mensagens 
    //a mensagem que chegou pelo mqtt 
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      msgFromMQTT+=(char)payload[i];
    }
  }

  //funcao que tenta conectar no wi fi caso a conexão seja perdida  
  void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
      Serial.print("Attempting MQTT connection...");
      // Create a random client ID
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
      // Attempt to connect
      if (client.connect(clientId.c_str())) {
        Serial.println("connected");
        // Once connected, publish an announcement...
        client.publish("lock/connected", "ESP Conectado");
        // ... and resubscribe
        client.subscribe("lock/open");
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }

  //Primeira função executada pelo NODE MCU 
  //é executada APENAS UMA VEZ 
  void setup() {
    //Seta pino do sensor como entrada 
    pinMode(13, INPUT);
    //inicializa serial monitor 
    Serial.begin(115200);
    //tenta conectar no wi fi 
    setup_wifi();
    //Connecta no mqtt 
    client.setServer(mqtt_server, 1883);
    
    //Seta função de callback 
    //Essa função será chamada quando receber uma mensagem do mqtt 
    client.setCallback(callback);
  }

  void loop() {

    if (!client.connected()) {
      reconnect();
    }
    client.loop();
    
    if(digitalRead(13) == HIGH){
      client.publish("pirsensor/pirsensor", "1");
    }else{
      client.publish("pirsensor/pirsensor", "0");
    }

    delay(1000);
  }