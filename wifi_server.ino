void initWiFi_connection() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid1, password1);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}




void initWiFi_hotspot() {
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
}
