  #include <ESP8266WiFi.h>
  #include <PubSubClient.h>

  const char* ssid = "Iphone de Robson";//network name
  const char* password = "invadenao2";//wi fi password 
  const char* mqtt_server = "broker.mqtt-dashboard.com";

  WiFiClient espClient;
  PubSubClient client(espClient);

  String inString = "";
      
  void setup_wifi() {

    delay(10);
    
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  void callback(char* topic, byte* payload, unsigned int length) {
    inString="";
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      inString+=(char)payload[i];
    }

    if(inString == "1"){
      digitalWrite(13, HIGH);              
    }else{
      digitalWrite(13, LOW);
    }
  }

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

  void setup() {
    pinMode(13, OUTPUT);
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
  }

  void loop() {

    if (!client.connected()) {
      reconnect();
    }
    client.loop();

    delay(1000);
  }
