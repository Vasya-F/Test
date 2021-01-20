
float v_bat
int t_eng
void setup() {
  // put your setup code here, to run once:

}

void loop()
{
  if (can_msg->ID == MS_ECC_ID && AUX_mode)                          //ECC processing
  {
    if (can_msg->Data[0] == 0x07)         //Battery voltage
    {
      v_bat = (can_msg->Data[2] / 10);
      Serial3.println("Voltage: " + v_bat, 1);
    }

    if (can_msg->Data[0] == 0x10)        //Engine temp
    {
      t_eng = (((can_msg->Data[3] * 256) + can_msg->Data[4]) / 10);
      Serial3.println("Engine temp: " + t_eng);
    }
  }
}

case MS_BTN_DOWN:
      {
        handleRepetitiveButton(can_msg->Data, MD_PREV_TRACK, MD_FAST_REWIND);
        handleButton(can_msg->Data, nullptr, BT_REFUSE);
        break;
  
