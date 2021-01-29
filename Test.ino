//#define MD_INIT_DELAY 3000

float u_battery
int t_engine
void setup() {
  // put your setup code here, to run once:

}

void loop()
{
  if (can_msg->ID == MS_ECC_ID && AUX_mode)                          //ECC processing
  {
    if (can_msg->Data[0] == 0x07)         //Battery voltage
    {
      v_bat = (can_msg->Data[2] / 10.0);
      Serial3.print("Voltage: ");
      Serial3.println(u_battery, 1);
    }
    if (can_msg->Data[0] == 0x10)        //Engine temp
    {
      t_eng = (((can_msg->Data[3] * 256) + can_msg->Data[4]) / 10);
      Serial3.print("Engine temp: ");
      Serial3.println(t_engine);
    }
  }

  while (Serial1.available() > 0)  //read serial port
  {
    Serial1.read();
  }
}



bool isModuleInitialized;
char serialBuffer[32];
uint8_t serialBufferIdx = 0;

void processCommand()
{
  if (!isModuleInitialized && (strcmp(serialBuffer, "QM+01") == 0 || strcmp(serialBuffer, "QM+02") == 0 || strcmp(serialBuffer, "QM+03") == 0))
  {
    isModuleInitialized = true;
    // init code here
    Serial3.print("Init by the command: ");
    Serial3.println(serialBuffer);
  }
  /*
    else if (strcmp(serialBuffer, "CMD") == 0)
    {
    // another command here
    }
  */
}

void setup()
{
  Serial3.begin(115200);
  Serial3.println("Starting...");
}

void loop()
{
  while (Serial1.available() > 0)
  {
    char c = Serial1.read();
    if (c == '\n')
    {
      serialBuffer[serialBufferIdx] = '\0';
      serialBufferIdx = 0;
      processCommand();
    }
    else if (c == '\0')
    {
      // ignore
    }
    else
    {
      serialBuffer[serialBufferIdx] = c;
      serialBufferIdx++;
      if (serialBufferIdx >= sizeof(serialBuffer))
        serialBufferIdx = 0;
    }
  }
}


unsigned long lastTime = 0;

unsigned long ms = millis();
if (initCommandIdx < 2 && ms - lastTime > MD_INIT_DELAY)
{
  lastTime = ms;
  if (initCommandIdx < 1 )
  {
    Serial3.println("if AUX_mode");
    if (!AUX_mode)
    {
      Serial1.println(MD_PAUSE);
      Serial3.println("MD_PAUSE");
    }
  }
  else if (initCommandIdx < 2)
  {
    Serial1.println(MD_RANDOM_TRACK);
    Serial3.println("MD_RANDOM_TRACK");
  }
  initCommandIdx++;
}
