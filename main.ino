unsigned long vrgMilis = 0;
const long interval = 5000; // Interval voor inactiefCon()
bool verzenden = true; // Verzenden van idle berichten bedienen
int rel = 4;
char ingang;

void setup() {
  pinMode(rel, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  if (verzenden) {
    inactiefCon();
  }

  if (Serial.available() > 0) {
    char ingang = Serial.read();
    hoofdPrograma(ingang);
  }
}

void inactiefCon() {
  unsigned long hdgMilis = millis();

  if (hdgMilis - vrgMilis >= interval) {
    vrgMilis = hdgMilis;
    Serial.println("AAN HET WACHTEN VOOR ACTIVITEIT, DRUK OP H VOOR HULPMENU OF ERGENS OM DEZE BERICHTEN TE DOVEN");
  }
}

void hoofdPrograma(char ingang) {
  if (ingang == 'h' || ingang == 'H') {
    verzenden = false;
    Serial.println(ingang);
    Serial.println("\033[91;49m========== HELPMENU ==========");
    Serial.println("");
    Serial.println("\033[91;49m==== ALGEMENE BEDIENINGEN ====");
    Serial.println("\033[32;49m[1] Lamp AAN");
    Serial.println("\033[31;49m[0 / 2] Lamp UIT");
    Serial.println("");
    Serial.println("\033[91;49m==== OPDRACHTREGELINTERFACE BEDIENINGEN ====");
    Serial.println("\033[0m[C] Opdrachtregelinterface wissen");
    Serial.println("[H] Toon deze hulpmenu");
    Serial.println("[I] Informatie");
    rdy();
  } else if (ingang == 'c' || ingang == 'C') {
    Serial.print("[\033[2J\033[H");
    verzenden = false;
    rdy();
  } else if (ingang == '1') {
    Serial.println(ingang);
    digitalWrite(rel, HIGH);
    Serial.println("\033[32;49m[1] Lamp AAN");
    verzenden = false;
    knipperLED();
    rdy();
  } else if (ingang == '0' || ingang == '2') {
    Serial.println(ingang);
    digitalWrite(rel, LOW);
    Serial.println("\033[31;49m[0 / 2] Lamp UIT");
    verzenden = false;
    knipperLED();
    rdy();
  } else if (ingang == 'i' || ingang == 'I') {
    Serial.println(ingang);
    Serial.println("\033[39;49mLights Out");
    Serial.println("CLI versie 2");
    Serial.println("\033[39;49mGemaakt door \033[34;49;1m17\033[36;49;1mnct \033[0m@ 2024");
    verzenden = false;
    rdy();
  } else if ((ingang == 'x' || 'X') && verzenden == true) {
    /* de OR operator dient niet zo gebruikt te worden, doe je het toch? Hij zal dan niet alleen op x of X reageren maar op alles. */
    verzenden = false;
    killmsg();

  }

}

void knipperLED() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(50);
  digitalWrite(LED_BUILTIN, LOW);
}

void killmsg() {
  Serial.println("BERICHTEN GEDOOFD.");
  Serial.print("\033[39;49m>");
}

void rdy() {
  Serial.print("\033[39;49m>");
}
