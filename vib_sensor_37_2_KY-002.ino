int shockPin = 10; // Use Pin 10 as our Input
int shockVal = HIGH; // This is where we record our shock measurement
boolean bAlarm = false;

unsigned long beginShockTime; // Record the time that we measured a shock
unsigned long endShockTime, shockDuration;
int shockAlarmTime = 500; // Number of milli seconds to keep the shock alarm high
int beginS, endS, durationS;


void setup ()
{
  Serial.begin(9600);  
  pinMode (shockPin, INPUT) ; // input from the KY-002
}
void loop ()
{
  shockVal = digitalRead (shockPin) ; // read the value from our sensor
  
  if (shockVal == LOW) // If we're in an alarm state
  {
    beginShockTime = millis(); // record the time of the shock
    // The following is so you don't scroll on the output screen
    if (!bAlarm){
      Serial.print("Shock detected after: ");
      beginS = beginShockTime/1000;
      Serial.print(beginS);
      Serial.println(" seconds the program started");
      bAlarm = true;
    }
  }
  else
  {
    if( (millis()-beginShockTime) > shockAlarmTime  &&  bAlarm){
      //if complete time - time when shock was detected is bigger than
      //500 mille seconds (shockAlarmtime) AND bAlarm = True
      
      Serial.print("    Shock stopped after ");
      endShockTime = millis();
      endS = endShockTime/1000;
      Serial.print(endS);
      Serial.println(" seconds");

      
      durationS = endS - beginS;
      Serial.print("    The shock duration was "); 
      Serial.print(durationS);
      Serial.println(" seconds\n");
      
      bAlarm = false;
    }
  }
}

