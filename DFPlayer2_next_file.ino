#define BUTTON_PIN A2
#define LED_PIN LED_BUILTIN

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Bounce2.h>
Bounce2::Button button = Bounce2::Button();
int ledState = LOW;
int number = 1;

SoftwareSerial mySoftwareSerial(10, 11);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);


void setup() {
  button.attach( BUTTON_PIN ,  INPUT_PULLUP );
  button.interval(5); 
  button.setPressedState(LOW); 
   pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,ledState);

  mySoftwareSerial.begin(9600);
  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true)
      ;
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500);  //Set serial communictaion time out 500ms

  //----Set volume----
  myDFPlayer.volume(20);    //Set volume value (0~30).
  myDFPlayer.volumeUp();    //Volume Up
  myDFPlayer.volumeDown();  //Volume Down

  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //  myDFPlayer.EQ(DFPLAYER_EQ_POP);
  //  myDFPlayer.EQ(DFPLAYER_EQ_ROCK);
  //  myDFPlayer.EQ(DFPLAYER_EQ_JAZZ);
  //  myDFPlayer.EQ(DFPLAYER_EQ_CLASSIC);
  //  myDFPlayer.EQ(DFPLAYER_EQ_BASS);

  //----Set device we use SD as default----
  //  myDFPlayer.outputDevice(DFPLAYER_DEVICE_U_DISK);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  //  myDFPlayer.outputDevice(DFPLAYER_DEVICE_AUX);
  //  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SLEEP);
  //  myDFPlayer.outputDevice(DFPLAYER_DEVICE_FLASH);

  //----Mp3 control----
  //  myDFPlayer.sleep();     //sleep
   myDFPlayer.reset();     //Reset the module
  //myDFPlayer.enableDAC();  //Enable On-chip DAC
  //  myDFPlayer.disableDAC();  //Disable On-chip DAC
 //  myDFPlayer.outputSetting(true, 30); //output setting, enable the output and set the gain to 15

//myDFPlayer.enableLoopAll();
  /*//----Mp3 play----
  myDFPlayer.next();  //Play next mp3
  delay(1000);
  myDFPlayer.previous();  //Play previous mp3
  delay(1000);
  myDFPlayer.play(1);  //Play the first mp3
  delay(1000);
  myDFPlayer.loop(1);  //Loop the first mp3
  delay(1000);
  myDFPlayer.pause();  //pause the mp3
  delay(1000);
  myDFPlayer.start();  //start the mp3 from the pause
  delay(1000);
  myDFPlayer.playFolder(15, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)
  delay(1000);
  myDFPlayer.enableLoopAll();  //loop all mp3 files.
  delay(1000);
  myDFPlayer.disableLoopAll();  //stop loop all mp3 files.
  delay(1000);
  myDFPlayer.playMp3Folder(4);  //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
  delay(1000);
  myDFPlayer.advertise(3);  //advertise specific mp3 in SD:/ADVERT/0003.mp3; File Name(0~65535)
  delay(1000);
  myDFPlayer.stopAdvertise();  //stop advertise
  delay(1000);
  myDFPlayer.playLargeFolder(2, 999);  //play specific mp3 in SD:/02/004.mp3; Folder Name(1~10); File Name(1~1000)
  delay(1000);
  myDFPlayer.loopFolder(5);  //loop all mp3 files in folder SD:/05.
  delay(1000);
  myDFPlayer.randomAll();  //Random play all the mp3.
  delay(1000);
  myDFPlayer.enableLoop();  //enable loop.
  delay(1000);
  myDFPlayer.disableLoop();  //disable loop.
  delay(1000);
  
*/
/*
  //----Read imformation----
  Serial.println(myDFPlayer.readState());                //read mp3 state
  Serial.println(myDFPlayer.readVolume());               //read current volume
  Serial.println(myDFPlayer.readEQ());                   //read EQ setting
  Serial.println(myDFPlayer.readFileCounts());           //read all file counts in SD card
  Serial.println(myDFPlayer.readCurrentFileNumber());    //read current play file number
  Serial.println(myDFPlayer.readFileCountsInFolder(1));  //read fill counts in folder SD:/03

*/

}

void loop() {
   button.update();

 if ( button.fell() == true ) {
    
    // TOGGLE THE LED STATE : 
   // ledState = !ledState; // SET ledState TO THE OPPOSITE OF ledState
    //digitalWrite(LED_PIN,ledState); // WRITE THE NEW ledState
    digitalWrite(LED_PIN,HIGH);
    //myDFPlayer.randomAll();
    myDFPlayer.playFolder(1, number);

  
  }
  if ( button.rose() == true ) {
    digitalWrite(LED_PIN,LOW);
    myDFPlayer.pause();
    if (number < 14)
      {
        ++number;
      }
      else 
      {
        number = 1;
      }
  }
}
