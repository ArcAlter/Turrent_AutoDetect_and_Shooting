// Define pin connections
const int dirPin = 18;
const int stepPin = 19;

// Variables that can be changed via Serial
int stepDelay = 1000;    // Speed (lower = faster)
bool running = false;    // Start/Stop state
int direction = HIGH;    // Current direction

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  
  Serial.begin(115200);
  
  // Print a helpful UI menu
  printMenu();
}

void loop() {
  // 1. Check for incoming Serial commands
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    handleCommand(cmd);
  }

  // 2. If motor is "started", take one step
  if (running) {
    digitalWrite(dirPin, direction);
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }
}

void handleCommand(char cmd) {
  switch (cmd) {
    case '1': // Start
      running = true;
      Serial.println(">>> Motor: STARTED");
      break;
    case '0': // Stop
      running = false;
      Serial.println(">>> Motor: STOPPED");
      break;
    case 'd': // Flip Direction
      direction = !direction;
      Serial.print(">>> Direction changed to: ");
      Serial.println(direction == HIGH ? "CW" : "CCW");
      break;
    case '+': // Increase Speed (decrease delay)
      stepDelay = max(50, stepDelay - 100); 
      Serial.print(">>> Speed UP. Delay: ");
      Serial.println(stepDelay);
      break;
    case '-': // Decrease Speed (increase delay)
      stepDelay += 100;
      Serial.print(">>> Speed DOWN. Delay: ");
      Serial.println(stepDelay);
      break;
    case 'h': // Help menu
      printMenu();
      break;
  }
}

void printMenu() {
  Serial.println("\n--- Stepper Test Menu ---");
  Serial.println("[1] Start  [0] Stop");
  Serial.println("[d] Change Direction");
  Serial.println("[+] Faster [-] Slower");
  Serial.println("[h] Show this menu again");
  Serial.println("--------------------------");
}