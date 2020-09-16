/*  ISM 2 - INTERPRETADOR DE SENSORES MÓVEIS
 *   
 *  Manager:    Rafael Albino
 *  Programmer: Rafael Albino
 *  Start:      19/01/2019 às 22:09
 *  End:        19/08/2019 às 16:29
 *  Update_1.1?:     29/01/2020 às ??:?? até ??/??/???? às ??:?? 
 */

//-------------------------------------------LIBRARIES-------------------------------------------

#include <U8glib.h>
U8GLIB_ST7920_128X64_1X u8g(51, 49, 47 ,53); //Enable (PORT 51), RW(PORT 49), RS(PORT 47), RESET(PORT 53) --- Create the way to the LCD and Arduino UNO. "(Should be below the library U8glib.h)"

#include <DHT.h>                // The Library of DHT 11.
#include <DHT_U.h>              // The Library of DHT 11.
#include <Adafruit_Sensor.h>    // It's Necessary to the DHT 11 works.
DHT dht(A0,DHT11);              // Create a Object and setting the analogic port that it will receive the datas and which sensor it will be selectioned.

#include <ClosedCube_HDC1080.h>       // The library of Sensor Humidity and Temperature HDC1080.
ClosedCube_HDC1080 Sensor_hdc1080;    // Create a Object of HDC1080 Sensor.

#include <Adafruit_BMP085.h>          // The library of Pressure Sensor BMP180
Adafruit_BMP085 bmp;                  // Create a Object of BMP_180 Sensor.

#define pinButton_PreviousPage 22     // Set the pinButton_PreviousPage to Pin 22  -- button RED --
#define pinButton_NextPage 24         // Set the pinButton_NextPage to Pin 24      -- button GREEN --
#define pinButton_HomePage 26         // Set the pinButton_NextPage to Pin 26      -- button WHITE --
#define pinButton_Select 28           // Set the pinButton_NextPage to Pin 28      -- button YELLOW --

//-------------------------------------------LIBRARIES-------------------------------------------


//--------------------------------------PROTOTAPY_FUNCTIONS--------------------------------------

void functionLight();

void suelen_memory();
void runTime();
void functionDisplay_RunTime();
void mainPage();
void hdc1080Page();
void dht11Page();
void bmp180Page();
void uvm30aSensorPage();

void stopWatch();
void functionDisplay_stopwatch();

void DHT_11();
void HDC_1080();
void BMP_180();
void uv_sensor_UVM30A();

//--------------------------------------PROTOTAPY_FUNCTIONS--------------------------------------


//----------------------------------------GLOBAL_VARIABLE----------------------------------------
    
    byte lengthCASE = 6;          // Control the number of Case existing in the program.

    bool logoSU = true;
    bool logoSU_2 = true;
    
    int numSelectSwitch = 1;      // Variable that store the value that will be use on SWITCH.
    int valueButtonPreviousPage;  // Variable that store the value from button RED.
    int valuepinButtonNextPage;   // Variable that store the value from button GREEN.
    int valuepinButtonHomePage;   // Variable that store the value from button WHITE.
    int valuepinButtonSelect;     // Variable that store the value from button YELLOW.
    
    float temperatureDHT_11;      // Create one variable to receive the temperature from sensor from any function.
    float humidityDHT_11;         // Create one variable to receive the humidity from sensor from any function.
    float maxTempDHT_11=0;        // It store the Maximum temperature from DHT 11.
    float minTempDHT_11=1000;     // It store the Minimum temperature from DHT 11.
    float maxHumiDHT_11=0;        // It store the Maximum Humidity from DHT 11.
    float minHumiDHT_11=101;      // It store the Minimum Humidity from DHT 11.
    
    float tempHDC1080;            // Create one variable to receive the temperature from sensor from any function.
    float humiHDC1080;            // Create one variable to receive the humidity from sensor from any function.
    float maxTempHDC1080=0;       // It store the Maximum temperature from HDC1080;
    float minTempHDC1080=1000;    // It store the Minimum temperature from HDC1080;
    float maxHumiHDC1080=0;       // It store the Maximum Humidity from HDC1080;
    float minHumiHDC1080=101;     // It store the Minimum Humidity from HDC1080;

    float pressureP;                  // Create a variable to receive the value of pressure from BMP180.
    float maxPressureP=-100000;       // It store the Maximum pressure from BMP180;
    float minPressureP=1000000;       // It store the Minimum pressure from BMP180;
    float altitudeA;                  // Create a variable to receive the value of altitude from BMP180.
    float maxAltitudeA=-9000;         // It store the Maximum altitude from BMP180;
    float minAltitudeA=100000;        // It store the Minimum altitude from BMP180;
    float correction_altitude = 103250; // It Store the value of Correction Altitude.

    unsigned int Time = millis(), current, dsecond = 0, second = 0, second2 = 0, minute = 0, hour = 0; // Variable of control of UpTime.
    unsigned int control = 0;         // Variable of control of Stopwatch.
    bool confirmToExecute = false;    // It control the reset function to not reset when the Stopwatch is in executation. (AVOID BUG).

    unsigned int RTcount=0;           // Variable of RTcount of RunTime.
    unsigned int RTTime = millis(), RTcurrent, RTsecond=0, RTminute=0, RThour=0, RTday=0; //Variable of control of UpTime.

    byte lightSelect = 0;             // Set the maximum light of Screen.
    
    int cont = 0;                     // Control the thermometerAnimation_DHT11.

        
    const uint8_t arrowToUP[] U8G_PROGMEM = {   0x18,         // 00011000  X(Position_Column), Y(Position_Line), Start(StartOfLooping), End(EndOfLooping), Variable.
                                                0x3c,         // 00111100  FUNCTION( X,  Y, Start, End,  Variable);
                                                0x66,         // 01100110  u8g.drawBitmapP(10, 10,     1,   9, arrowToUP);
                                                0xff,         // 11111111 
                                                0x18,         // 00011000 
                                                0x18,         // 00011000
                                                0x18,         // 00011000 
                                                0x18,         // 00011000
                                                0x18};        // 00011000

    const uint8_t arrowToDOWN[] U8G_PROGMEM = { 0x18,         // 00011000  X(Position_Column), Y(Position_Line), Start(StartOfLooping), End(EndOfLooping), Variable.
                                                0x18,         // 00011000  FUNCTION( X,  Y, Start, End,  Variable);
                                                0x18,         // 00011000  u8g.drawBitmapP(10, 10,     1,   9, arrowToDOWN);
                                                0x18,         // 00011000
                                                0x18,         // 00011000 
                                                0xff,         // 11111111 
                                                0x66,         // 01100110
                                                0x3c,         // 00111100 
                                                0x18};        // 00011000

    const uint8_t thermometer[] U8G_PROGMEM = { 0x10,         // 00010000  X(Position_Column), Y(Position_Line), Start(StartOfLooping), End(EndOfLooping), Variable.
                                                0x28,         // 00101000  FUNCTION( X,  Y, Start, End,  Variable);
                                                0x28,         // 00101000  u8g.drawBitmapP(10, 10,     1,   9, thermometer);
                                                0x28,         // 00101000 
                                                0x38,         // 00111000 
                                                0x7c,         // 01111100
                                                0xfe,         // 11111110 
                                                0x7c,         // 01111100
                                                0x38};        // 00111000


    const uint8_t drop[] U8G_PROGMEM = {        0x10,         // 00010000  X(Position_Column), Y(Position_Line), Start(StartOfLooping), End(EndOfLooping), Variable.
                                                0x10,         // 00010000  FUNCTION( X,  Y, Start, End,  Variable);
                                                0x38,         // 00101000  u8g.drawBitmapP(10, 10,     1,   9, thermometer);
                                                0x38,         // 00101000 
                                                0x7c,         // 01000100 
                                                0x7c,         // 01000100
                                                0x7c,         // 01000100
                                                0x7c,         // 01000100
                                                0x38};        // 00111000

    const uint8_t star[] U8G_PROGMEM = {        0x18,         
                                                0x3C,         
                                                0xFF,         
                                                0x7E,         
                                                0x3C,
                                                0x66,
                                                0xC3};

    const uint8_t cros[] U8G_PROGMEM = {        0x18,         
                                                0x18,         
                                                0xFF,         
                                                0xFF,         
                                                0x18,         
                                                0x18,         
                                                0x18,         
                                                0x18};         
                                                

    const uint8_t suelen[] U8G_PROGMEM = { 0xff, 0x16, 0x00, 0x40, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x8e, 0x00, 0x0e, 0x00, 0x00, 0x00, 0xc0,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x04, 0x40, 0xb0,
   0x01, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x03, 0x02, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x80,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x01, 0x12,
   0x00, 0x02, 0x10, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xc2, 0x03, 0x00, 0x00, 0x00, 0x3b, 0x00, 0xfe, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x1f, 0x00, 0x00, 0x40, 0x7f, 0x00,
   0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x14, 0x7e, 0x00,
   0x00, 0xe0, 0x7f, 0x02, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x31, 0x7c, 0x41, 0x00, 0xd0, 0xff, 0x14, 0xfc, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x30, 0x38, 0x80, 0x01, 0xe0, 0xff, 0x0a,
   0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x08, 0x30, 0x22,
   0x00, 0xf8, 0xff, 0x0a, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x85, 0xd0, 0x08, 0x00, 0xfc, 0xff, 0x0f, 0xf8, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xe9, 0x25, 0x02, 0x00, 0xfc, 0xff, 0x1f,
   0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xa3, 0x00,
   0x00, 0xfc, 0xff, 0x1f, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xf0, 0x29, 0x0a, 0x00, 0xf0, 0x0b, 0x18, 0xf8, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0x2c, 0x00, 0x00, 0xe0, 0x01, 0x10,
   0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x15, 0x41, 0x00,
   0x00, 0xe0, 0x01, 0x01, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x1c, 0x0b, 0x00, 0x00, 0xf1, 0x01, 0x0d, 0xf0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x06, 0x07, 0x04, 0x00, 0xf3, 0x41, 0x1c,
   0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x81, 0x05, 0x01,
   0x00, 0xf8, 0xe0, 0x19, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0xe1, 0x00, 0x00, 0x00, 0xf8, 0xe0, 0x10, 0xf0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x94, 0x80, 0x00, 0x00, 0xf8, 0x02, 0x00,
   0x10, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x00, 0xfc, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x08, 0x90, 0x00, 0x00, 0xff, 0x43, 0x80, 0x10, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x15, 0x00, 0x80, 0xff, 0x0f, 0x04,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x80, 0xff, 0xbf, 0x9f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x01, 0x00, 0xc0, 0xff, 0xff, 0x1f, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x00, 0x00, 0xe0, 0xfc, 0xfe, 0x3f,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x30, 0x00, 0x00,
   0xc0, 0x00, 0xff, 0x1f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x4e, 0x00, 0x00, 0xd0, 0x00, 0xfe, 0x1f, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x24, 0x00, 0x00, 0xb0, 0x84, 0xff, 0x0f,
   0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x35, 0x00, 0x00,
   0x70, 0x4d, 0xf9, 0x07, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x00, 0x00, 0xf0, 0x17, 0xfc, 0x07, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0x03,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x30, 0xc0, 0xff, 0x01, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x00, 0x00, 0x38, 0x01, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x38, 0x0f, 0xfe, 0x00,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x18, 0xc5, 0xff, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x00, 0x00, 0x78, 0x80, 0xff, 0x00, 0x3f, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xd0, 0x81, 0x7f, 0x00,
   0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0xe0, 0xff, 0x3f, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x1f, 0x80, 0x01, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x07, 0x00,
   0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0xc0, 0xff, 0x01, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x00, 0x00, 0x00, 0xfd, 0x00, 0x00, 0x20, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
   0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x00, 0xfe, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0x30, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00,
   0x06, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0xfc, 0x00, 0x02, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x03, 0x01, 0x03, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xff, 0xc1, 0x03, 0x02,
   0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00,
   0xff, 0x61, 0x00, 0xc6, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x08, 0x00, 0x80, 0xff, 0x07, 0x00, 0xc0, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xc0, 0xff, 0x3f, 0xe0, 0xef,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xa0,
   0xff, 0xff, 0xff, 0x7f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff,
   0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xe0,
   0xff, 0xff, 0xff, 0xff, 0x03, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
   0xff, 0x00, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0x07, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0xff };

//----------------------------------------GLOBAL_VARIABLE----------------------------------------


void setup(){
//----------------------------------------GRAPHIC_DISPLAY----------------------------------------  
  pinMode(31, OUTPUT);      // It turn ON maximum light of Screen.
  digitalWrite(31, HIGH);   // It turn ON maximum light of Screen.
  pinMode(33, INPUT);       // It turn OFF maximum light of Screen.
  pinMode(35, INPUT);       // It turn OFF maximum light of Screen.
  
  u8g.setColorIndex(1);     // Turn on pixel.

  u8g.firstPage(); // Hold on the display freeze.
  do{              // Starting the Loop While. 
    
    u8g.setFont(u8g_font_osb18);       // Set the font "osb18".
    u8g.drawStr(31, 25, "<A>");        // Print A as BOLD. 
    u8g.drawStr(31, 24, "<A>");        // Print A.
    
    u8g.setFont(u8g_font_unifont);     // Set the font "unifont".
    u8g.drawStr(28, 45, "<Ansdles>");  // Print <Ansdles>.
    u8g.drawStr(28, 46, "<       >");  // Print < > with BOLD.
    u8g.drawStr(29, 46, "<Ansdles>");  // Create Effect 3D.

    u8g.setFont(u8g_font_unifont);     // Set the font "unifont"
    
                                   u8g.drawStr(11, 51, "I");
         u8g.drawStr(10, 52, "I"); u8g.drawStr(11, 52, "I"); u8g.drawStr(12, 52, "I");         // Create the Special Caracter 'I'.
                                   u8g.drawStr(11, 53, "I");

    u8g.setFont(u8g_font_unifont);     // Set the font "unifont".
    
                                    u8g.drawStr(61, 59, "S");
          u8g.drawStr(60, 60, "S"); u8g.drawStr(61, 60, "S"); u8g.drawStr(62, 60, "S");        // Create the Special Caracter 'S'.
                                    u8g.drawStr(61, 61, "S");
                              
    u8g.setFont(u8g_font_unifont);     // Set the font "unifont".
    
                                    u8g.drawStr(110, 51, "M");
    u8g.drawLine(110, 52, 110, 41); u8g.drawStr(110, 52, "M"); u8g.drawLine(117, 52, 117, 41); // Create the Special Caracter 'M'.
                                    u8g.drawStr(110, 53, "M");
  
  }while(u8g.nextPage());     // Test the Loop While.
  delay(2500);                // Wait for 1 seconds to show the LOGO. 
    
  dht.begin();                // Start the Object Sensor DHT 11.

  Sensor_hdc1080.begin(0x40); // Start the Object HDC1080 Sensor on address 0x40.

  bmp.begin(0x77);            // Start the Object Pressure Sensor BMP180

  pinMode(pinButton_PreviousPage, INPUT_PULLUP); // Start the Button and active the function PULL UP.
  pinMode(pinButton_NextPage, INPUT_PULLUP);     // Start the Button and active the function PULL UP.
  pinMode(pinButton_HomePage, INPUT_PULLUP);     // Start the Button and active the function PULL UP.
  pinMode(pinButton_Select, INPUT_PULLUP);       // Start the Button and active the function PULL UP.
  

//----------------------------------------GRAPHIC_DISPLAY----------------------------------------  

}

void loop() {
  
  u8g.firstPage();  // Hold on the display freeze.
  do{               // Starting the Loop While. 

      valueButtonPreviousPage = digitalRead(pinButton_PreviousPage); // The variable valueButtonPreviousPage receive the value from port pinButton_PreviousPage.
      valuepinButtonNextPage  = digitalRead(pinButton_NextPage);     // The variable valuepinButtonNextPage receive the value from port valuepinButtonNextPage.
      valuepinButtonHomePage  = digitalRead(pinButton_HomePage);     // The variable valuepinButtonHomePage receive the value from port pinButton_HomePage.
      valuepinButtonSelect    = digitalRead(pinButton_Select);       // The variable valuepinButtonSelect receive the value from port pinButton_Select.

      
      //Function_of_RunTime===============================================================================================================
      RTcurrent = millis();                  // This variable Receive the current value in this time.
      RTsecond = (RTcurrent-RTTime) / 1000;  // dsecond receive the current time(current) - last time (Time) making up sense to stopwatch.
                 
      if(RTsecond > 59){                     // It test if (second) is higher than a 59 seconds.
         RTTime = millis();
         RTminute++;
      }
      if(RTminute > 59){                     // It test if (minute) is higher than a 59 minutes.
         RTTime = millis();
         RTminute = 0;
         RThour++;
      }
      if(RThour > 23){                       // It test if (hour) is higher than a 23 hours.
      RTTime = millis();
      RThour = 0;
      RTday++;
     }
     //Function_of_RunTime===============================================================================================================

                    
     switch(numSelectSwitch){  // Number of control of Screens.
        
        case -1:
            suelen_memory();   // Call the function Suelen Memorial.
        break;
        
        case 0:
            runTime();         // Call the function RunTime.
        break;
        case 1:
            mainPage();        // It call the main screen.
            //suelen_memory();
        break;
        case 2:
            hdc1080Page();     // It call the next screen (hdc1080Page).
        break;
        case 3:
            dht11Page();       // It call the next screen (dht11Page).
        break;
        case 4:
            bmp180Page();      // It call the next screen (bmp180Page).
        break;
        case 5:
            uvm30aSensorPage();// It call the next screen (uvm30aSensorPage).
        break;
        case 6:
            stopWatch();       // It call the next screen (Stopwatch).
        break;
       
     }
     
    if(valuepinButtonNextPage == 0){         // Test if the Button is receiving the value 0 that mean Button is being pressing.
       if(numSelectSwitch < lengthCASE){     // AVOID the bug DISAPPEARANCE Of Screen and hold it working as a LOOP.
          numSelectSwitch++;                 // The variable numSelectSwitch is being incremented and going to the next page.
          delay(250);                        // This delay is being use to wait a 1/4 of second to give the correct time for users avoiding to pass very quick the page.
       }else if(confirmToExecute == true){   // Condition to reset the Stopwatch if the one is stop and not in executation.
             dsecond = 0; second = 0; minute = 0; hour = 0; control = 0; second2 = 0; // Reset the Stopwatch.
             break;                          // Go out of decision IF and nothing is executed.
       }
    }
    

    if(valueButtonPreviousPage == 0){        // Test if the Button is receiving the value 0 that mean Button is being pressing.
       if(numSelectSwitch > -1){             // AVOID the bug DISAPPEARANCE Of Screen and hold it working as a LOOP.
          numSelectSwitch--;                 // The variable numSelectSwitch is being decremented and going to the previously page.
          delay(250);                        // This delay is being use to wait a 1/4 of second to give the correct time for users avoiding to pass very quick the page.
       }else{
          break;                             // Go out of decision IF and nothing is executed.
       }
    }

    
    if(numSelectSwitch > lengthCASE || numSelectSwitch < -1){ // AVOID the bug DISAPPEARANCE Of Screen and hold it working as a LOOP.
       numSelectSwitch = 0;                                   // The variable numSelectSwitch Back to MAIN sreen.
    }


    if(valuepinButtonHomePage == 0){         // Test if the Button is receiving the value 0 that mean Button is being pressing.
       if(numSelectSwitch == 1){             // If you're in HOME and press the Home Button, you'll go to Stopwatch.
          numSelectSwitch = lengthCASE;      // Go to Stopwatch page.
          delay(250);
       }else{
          numSelectSwitch = 1;               // The variable numSelectSwitch is being reseted and going to the Home page.
          delay(250);
       }
    }

    functionLight();          // It call the Function that control the LIGHT of the Screen.
           
  }while(u8g.nextPage());     // Test the Loop While.

}

//----------------------------------------------------------FUNCTIONS----------------------------------------------------------

//-------------------------------------------------------FUNCTION_DHT_11-------------------------------------------------------
void DHT_11(){
     humidityDHT_11    = dht.readHumidity();           // The variable humidityDHT_11 receive the value from dht.readHumidity();
     temperatureDHT_11 = dht.readTemperature();        // The variable temperatureDHT_11 receive the value from dht.readTemperature();
    
    if (isnan(temperatureDHT_11) || isnan(humidityDHT_11)){ // Check if the sensor is working.
        u8g.setFont(u8g_font_04b_03);                       // Set the font u8g_font_04b_03.
        u8g.drawStr(4, 41, "Failed Sensor!");               // Printing the message.
    }else{
        u8g.setFont(u8g_font_04b_03);                       // Set the font u8g_font_04b_03.
        u8g.drawStr(4, 40, "Inter  Sensor");                // Printing the message.
        if(temperatureDHT_11 > 9 && temperatureDHT_11 < 100 ){  // Organize the characters.
            u8g.drawBitmapP(4, 42, 1, 9, thermometer);          // FUNCTION thermometer( X,  Y, Start, End, Variable);
            u8g.setFont(u8g_font_6x10);                         // Set the font u8g_font_6x10
            u8g.setFont(u8g_font_04b_03);                       // Set the font u8g_font_04b_03
            u8g.setPrintPos(13, 50);                            // Set the pixel to print.
            u8g.drawStr(23, 46, ".");                           // Printing the character º.
            u8g.drawStr(25, 50, "C");                           // Printing the letter C.
            u8g.print(temperatureDHT_11,0);                     // Print the Internal Temperature and specify the precision. from DHT 11. (variable, number of precision);
        }else if(temperatureDHT_11 > -1 && temperatureDHT_11 < 10){  // If the temperature be less than 10 and higher than -1, the character º and letter C will be relocated.
            u8g.drawBitmapP(4, 42, 1, 9, thermometer);          // FUNCTION thermometer( X,  Y, Start, End, Variable);
            u8g.setFont(u8g_font_6x10);                         // Set the font u8g_font_04b_03.
            u8g.setFont(u8g_font_04b_03);                       // Set the font u8g_font_04b_03
            u8g.setPrintPos(13, 42);                            // Set the pixel to print.
            u8g.drawStr(19, 38, ".");                           // Printing the character º.
            u8g.drawStr(21, 42, "C");                           // Printing the letter C.
            u8g.print(temperatureDHT_11,0);                     // Print the Internal Temperature and specify the precision from DHT 11. (variable, number of precision);
        }else if(temperatureDHT_11 < 0){        //If the temperature be less than 0, the character º and letter C will be relocated again.
            u8g.drawBitmapP(4, 42, 1, 9, thermometer);          // FUNCTION thermometer( X,  Y, Start, End, Variable);u8g.setFont(u8g_font_6x10);                         // Set the font u8g_font_6x10
            u8g.setFont(u8g_font_04b_03);                       // Set the font u8g_font_04b_03
            u8g.setPrintPos(13, 42);                            // Set the pixel to print.
            u8g.drawStr(27, 38, ".");                           // Printing the character º.
            u8g.drawStr(29, 42, "C");                           // Printing the letter C.
            u8g.print(temperatureDHT_11,0);                     // Print the Internal Temperature and specify the precision from DHT 11. (variable, number of precision);
        }
           
        if(humidityDHT_11 > 9 && humidityDHT_11 < 100){  // Organize the characters.
            u8g.drawBitmapP(37, 42, 1, 9, drop);                // FUNCTION drop( X,  Y, Start, End, Variable);
            u8g.setFont(u8g_font_6x10);                         // Set the font u8g_font_6x10
            u8g.setFont(u8g_font_04b_03);                       // Set the font u8g_font_04b_03
            u8g.drawStr(57, 50, "%");                           // Printing the character %.
            u8g.setPrintPos(46, 50);                            // Set the pixel to print.
            u8g.print(humidityDHT_11,0);                        // Print the Internal humidity and specify the precision from DHT 11. (variable, number of precision);
        }else{                                    // If the humidity be less than 10, the character % will be relocated.
          
            u8g.setFont(u8g_font_6x10);                         // Set the font u8g_font_6x10
            u8g.drawStr(37, 42, "H");                           // Printing the letter H.
            u8g.setFont(u8g_font_04b_03);                       // Set the font u8g_font_04b_03
            u8g.drawStr(51, 42, "%");                           // Printing the character %.
            u8g.setPrintPos(40, 42);                            // Set the pixel to print.
            u8g.print(humidityDHT_11,0);                        // Print the Internal humidity and specify the precision from DHT 11. (variable, number of precision);
        }
    }
}

//-------------------------------------------------------FUNCTION_DHT_11-------------------------------------------------------



//------------------------------------------------------FUNCTION_HDC_1080------------------------------------------------------

void HDC_1080(){
     tempHDC1080 = Sensor_hdc1080.readTemperature(); // Receive the temperature from sensor.
     humiHDC1080 = Sensor_hdc1080.readHumidity();    // Receive the humidity from sensor.  
    
    if(tempHDC1080 > maxTempHDC1080){   // Test if the current temperature is higher than the Maximum.
        maxTempHDC1080 = tempHDC1080;   
    }
    if(tempHDC1080 < minTempHDC1080){   // Test if the current temperature is lower than the Minimum.
        minTempHDC1080 = tempHDC1080;
    }
    if(humiHDC1080 > maxHumiHDC1080){  // Test if the current Humidity is higher than the Maximum.
        maxHumiHDC1080 = humiHDC1080;    
    }
    if(humiHDC1080 < minHumiHDC1080){  // Test if the current Humidity is lower than the Minimum.
        minHumiHDC1080 = humiHDC1080;
    }
    
    u8g.setFont(u8g_font_04b_03);                        // Set the font u8g_font_04b_03.
    u8g.drawStr(4, 8, "Exter  Sensor");                  // Printing the message.

    if(tempHDC1080 > 9 && tempHDC1080 < 100){               // Organize the characters.
        u8g.drawBitmapP(4, 10, 1, 9, thermometer);          // FUNCTION thermometer( X,  Y, Start, End, Variable);
        u8g.setFont(u8g_font_6x10);                         // Set the font u8g_font_6x10
        u8g.setPrintPos(13, 18);                            // Set the pixel to print.
        u8g.print(tempHDC1080,1);                           // Print the External Temperature and specify the precision from HDC1080. (variable, number of precision);
        u8g.drawStr(37, 13, ".");                           // Printing the character º.
        u8g.drawStr(42, 18, "C");                           // Printing the letter C.
    }else if(tempHDC1080 > -1 && tempHDC1080 < 10){ // If the temperature be less than 10 and higher than -1, the character º and letter C will be relocated.
        u8g.drawBitmapP(4, 10, 1, 9, thermometer);          // FUNCTION thermometer( X,  Y, Start, End, Variable);
        u8g.setFont(u8g_font_6x10);                         // Set the font u8g_font_6x10
        u8g.setPrintPos(13, 18);                            // Set the pixel to print.
        u8g.print(tempHDC1080,1);                           // Print the External Temperature and specify the precision from HDC1080. (variable, number of precision);
        u8g.drawStr(32, 13, ".");                           // Printing the character º.
        u8g.drawStr(37, 18, "C");                           // Printing the letter C.
    }else if(tempHDC1080 < 0){                      // If the temperature be less than 0, the character º and letter C will be relocated again.
        u8g.drawBitmapP(4, 10, 1, 9, thermometer);          // FUNCTION thermometer( X,  Y, Start, End, Variable);
        u8g.setFont(u8g_font_6x10);                         // Set the font u8g_font_6x10
        u8g.setPrintPos(13, 18);                            // Set the pixel to print.
        u8g.print(tempHDC1080,1);                           // Print the External Temperature and specify the precision from HDC1080. (variable, number of precision);
        u8g.drawStr(42, 13, ".");                           // Printing the character º.
        u8g.drawStr(47, 18, "C");                           // Printing the letter C.
    }
    
    if(humiHDC1080 > 9 && humiHDC1080 < 100){               // Organize the characters.
       u8g.drawBitmapP(4, 20, 1, 9, drop);                  // FUNCTION drop( X,  Y, Start, End, Variable);
       u8g.setFont(u8g_font_6x10);                          // Set the font u8g_font_6x10
       
       u8g.setPrintPos(13, 28);                             // Set the pixel to print.
       u8g.print(humiHDC1080,1);                            // Print the External Humidity and specify the precision from HDC1080. (variable, number of precision);
       u8g.setFont(u8g_font_04b_03);                        // Set the font u8g_font_04b_03.
       u8g.drawStr(42, 28, "%");                            // Printing the character %.
    }else{                                                  // If the humidity be less than 10, the character % will be relocated.
       u8g.drawBitmapP(4, 20, 1, 9, drop);                  // FUNCTION drop( X,  Y, Start, End, Variable);
       u8g.setFont(u8g_font_6x10);                          // Set the font u8g_font_6x10
       u8g.setPrintPos(13, 28);                             // Set the pixel to print.
       u8g.print(humiHDC1080,1);                            // Print the External Humidity and specify the precision from HDC1080. (variable, number of precision);
       u8g.setFont(u8g_font_04b_03);                        // Set the font u8g_font_04b_03.
       u8g.drawStr(37, 28, "%");                            // Printing the character %.

    }
    
}

//------------------------------------------------------FUNCTION_HDC_1080------------------------------------------------------

//------------------------------------------------------FUNCTION__BMP_180------------------------------------------------------
void BMP_180(){
       pressureP = bmp.readSealevelPressure();           // Receive the value of pressure from BMP180.
       altitudeA = bmp.readAltitude(correction_altitude);             // Receive the value of altitude from BMP180.

       if(pressureP > maxPressureP){                     // Test if the current temperature is higher than the Maximum.
          maxPressureP = pressureP;   
       }
       if(pressureP < minPressureP){                     // Test if the current temperature is lower than the Minimum.
          minPressureP = pressureP;
       }
       if(altitudeA > maxAltitudeA){                     // Test if the current Humidity is higher than the Maximum.
          maxAltitudeA = altitudeA;    
       }
       if(altitudeA < minAltitudeA){                     // Test if the current Humidity is lower than the Minimum.
          minAltitudeA = altitudeA;
       }
       
       u8g.setFont(u8g_font_04b_03);                     // Set the font u8g_font_04b_03.
       u8g.drawStr(68, 8, "Press Sensor");               // Printing the message.
       
       u8g.setFont(u8g_font_6x10);                       // Set the font u8g_font_6x10
       u8g.drawStr(68, 18, "P");                         // Printing the letter P.
       u8g.setPrintPos(75, 18);                          // Set the pixel to print.
       u8g.print(pressureP/1000,1);                      // Print the pressure in Kpa.                           
       u8g.drawStr(108, 18, "Kpa");                      // Printing the letters Kpa.

       u8g.setFont(u8g_font_6x10);                       // Set the font u8g_font_6x10
       u8g.drawStr(68, 28, "A");                         // Printing the letter A.
       u8g.setPrintPos(75, 28);                          // Set the pixel to print.
       u8g.print(altitudeA,0);                           // Print the altitude.
       u8g.setFont(u8g_font_04b_03);                     // Set the font u8g_font_04b_03.
       u8g.drawStr(102, 28, "Meter");                    // Print the word Meter.           
}

//------------------------------------------------------FUNCTION__BMP_180------------------------------------------------------


//-----------------------------------------------------FUNCTION__UV_UVM30A-----------------------------------------------------
void uv_sensor_UVM30A(){
       int sensor_value;   // The variable that receive the value from sensor.
       int voltage;        // The variable that stores real value from sensor.
       sensor_value = analogRead(A2);                    // The port used from sensor.
       voltage = (sensor_value * (5.0 / 1023.0)) * 1000; // A calculation did to find the real value from sensor.
       
       u8g.setFont(u8g_font_04b_03);                     // Set the font u8g_font_04b_03.
       u8g.drawStr(68, 40, "UVRad Sensor");              // Printing the message.

       if (voltage >= 0 && voltage <= 227){              // Execute the specific sentence within the values collected from sensor.
           u8g.drawStr(76, 50, "No UVRad");              // Printing the message.
           u8g.drawStr(68, 60, "RiskIndex:");            // Printing the message.
           u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
           u8g.drawStr(115, 60, "0");                    // Printing a number.
           
       }else if (voltage > 227 && voltage <= 318){       // The same thing again below ↓↓↓.
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(72, 50, "Safe UVRad");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(115, 60, "1");
           
       }else if (voltage > 318 && voltage <= 408){       // ↨↨↨
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(74, 50, "Low UVRad");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(115, 60, "2");
           
       }else if (voltage > 408 && voltage <= 503){       // ↨↨↨
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(68, 50, "Medium UVRad");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(115, 60, "3");
           
       }else if (voltage > 503 && voltage <= 606){       // ↨↨↨
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(68, 50, "Medium UVRad");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(115, 60, "4");
            
       }else if (voltage > 606 && voltage <= 696){       // ↨↨↨
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(68, 50, "Medium UVRad");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(115, 60, "5");
           
       }else if (voltage > 696 && voltage <= 795){       // ↨↨↨
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(73, 50, "High UVRad");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(115, 60, "6");
           
       }else if (voltage > 795 && voltage <= 881){       // ↨↨↨
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(73, 50, "High UVRad");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(115, 60, "7");
           
       }else if (voltage > 881 && voltage <= 976){       // ↨↨↨
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(67, 50, "Harmful");
           u8g.drawStr(100, 50, "UVRad");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(115, 60, "8");
           
       }else if (voltage > 976 && voltage <= 1079){      // ↨↨↨
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(67, 50, "Harmful");
           u8g.drawStr(100, 50, "UVRad");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(115, 60, "9");
           
       }else if (voltage > 1079 && voltage <= 1170){     // ↨↨↨
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(67, 50, "Harmful");
           u8g.drawStr(100, 50, "UVRad");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(112, 60, "10"); 
           
       }else if (voltage > 1170){                        // ↨↨↨
           u8g.setFont(u8g_font_04b_03);                 
           u8g.drawStr(68, 50, "Deadly UVRad!");
           u8g.drawStr(68, 60, "RiskIndex:");
           u8g.setFont(u8g_font_6x10);
           u8g.drawStr(112, 60, "11");  
       }
  
}

//-----------------------------------------------------FUNCTION__UV_UVM30A-----------------------------------------------------


//-------------------------------------------------------FUNCTION__PAGES-------------------------------------------------------

          //========================MAIN_PAGE========================
            void mainPage(){
                    //Function( X, Y,  W,  H);
                 u8g.drawFrame( 0, 0,128, 64);  // Create rectangle
                 u8g.drawFrame( 1, 1, 63, 30);  // Create the External Temperature and Humidity frame..................( Position Left Upper )
                 u8g.drawFrame(65, 1, 62, 30);  // Create the Pressure and Altitude frame..............................( Position Right Upper )
                 u8g.drawFrame( 1,33, 63, 30);  // Create the Internal Temperature and Humidity frame..................( Position Left Bottom )
                 u8g.drawFrame(65,33, 62, 30);  // Create the UV Solar Rays frame......................................( Position Right Bottom )
                 
                 HDC_1080();         // Call the function HDC_1080();
                 BMP_180();          // Call the function BMP_180();
                 DHT_11();           // Call the function DHT_11();
                 uv_sensor_UVM30A(); // Call the function uv_sensor_UVM30A();
                 logoSU = true;   // This command is to activate completely the function suelen_memory().
                 logoSU_2 = true; // This command is to activate completely the function suelen_memory().
            }
          //========================MAIN_PAGE========================


          //========================HDC_1080_PAGE========================
            void hdc1080Page(){
                 
                 tempHDC1080 = Sensor_hdc1080.readTemperature(); // Receive the temperature from sensor.
                 humiHDC1080 = Sensor_hdc1080.readHumidity();    // Receive the humidity from sensor.  
    
                 if(tempHDC1080 > maxTempHDC1080){   // Test if the current temperature is higher than the Maximum.
                    maxTempHDC1080 = tempHDC1080;   
                 }
                 if(tempHDC1080 < minTempHDC1080){   // Test if the current temperature is lower than the Minimum.
                    minTempHDC1080 = tempHDC1080;
                 }
                 if(humiHDC1080 > maxHumiHDC1080){  // Test if the current Humidity is higher than the Maximum.
                    maxHumiHDC1080 = humiHDC1080;    
                 }
                 if(humiHDC1080 < minHumiHDC1080){  // Test if the current Humidity is lower than the Minimum.
                    minHumiHDC1080 = humiHDC1080;
                 }

                                                     
                 u8g.setFont(u8g_font_6x10);               // Set the font u8g_font_6x10.
                 u8g.drawBox(18,1,93,18);                  // Create a Rectangle Full.
                 u8g.setColorIndex(0);                     // Turn OFF the Pixels.
                 u8g.drawStr(20, 9, "External Sensor");    // Printing the message.
                 u8g.drawStr(23, 18, "H D C  1 0 8 0");    // Printing the message.
                 u8g.setColorIndex(1);                     // Turn ON the Pixels.

                 
                 u8g.drawLine(7, 9, 17, 9);                // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 10, 17, 10);              // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 11, 7, 19);               // Line from the Left Upper Side.       ||
                 u8g.drawLine(8, 11, 8, 19);               // Line from the Left Upper Side.       ||
                 
                 u8g.drawLine(111, 9, 120, 9);             // Line from the Right Upper Side.    ------
                 u8g.drawLine(111, 10, 120, 10);           // Line from the Right Upper Side.    ------
                 u8g.drawLine(119, 11, 119, 21);           // Line from the Right Upper Side.      ||
                 u8g.drawLine(120, 11, 120, 21);           // Line from the Right Upper Side.      ||

                                  
                 u8g.drawFrame( 1, 20, 53, 21);                 // Create rectangle Empty.
                 u8g.drawBitmapP(3, 21, 1, 9, arrowToUP);       // FUNCTION arrowToUP( X,  Y, Start, End, Variable);
                 u8g.drawBitmapP(13, 21, 1, 9, thermometer);    // FUNCTION thermometer( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the u8g_font_6x10.
                 u8g.setPrintPos(22, 29);                       // Set the pixel to print.
                 u8g.print(maxTempHDC1080,1);                   // Print the External Temperature and specify the precision from HDC1080. (variable, number of precision);

                 u8g.drawBitmapP(3, 31, 1, 9, arrowToDOWN);     // FUNCTION arrowToDOWN( X,  Y, Start, End, Variable);
                 u8g.drawBitmapP(13, 31, 1, 9, thermometer);    // FUNCTION thermometer( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the u8g_font_6x10.
                 u8g.setPrintPos(22, 39);                       // Set the pixel to print.
                 u8g.print(minTempHDC1080,1);                   // Print the External Temperature and specify the precision from HDC1080. (variable, number of precision);

                 u8g.drawLine(54, 29, 61, 29);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(61, 30, 61, 37);                  // Line from the Center Upper Side.      ||


                 u8g.drawFrame( 1, 42, 53, 21);                 // Create rectangle Empty.
                 u8g.drawBitmapP(3, 43, 1, 9, arrowToUP);       // FUNCTION arrowToUP( X,  Y, Start, End, Variable);
                 u8g.drawBitmapP(13, 43, 1, 9, drop);           // FUNCTION drop( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(22, 51);                       // Set the pixel to print.
                 u8g.print(maxHumiHDC1080,1);                   // Print the External Humidity and specify the precision from HDC1080. (variable, number of precision);

                 u8g.drawBitmapP(3, 53, 1, 9, arrowToDOWN);     // FUNCTION arrowToUP( X,  Y, Start, End, Variable);
                 u8g.drawBitmapP(13, 53, 1, 9, drop);           // FUNCTION drop( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(22, 61);                       // Set the pixel to print.
                 u8g.print(minHumiHDC1080,1);                   // Print the External Humidity and specify the precision from HDC1080. (variable, number of precision);

                 u8g.drawLine(54, 53, 61, 53);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(61, 45, 61, 52);                  // Line from the Center Upper Side.      ||
 
 
                 u8g.drawBox(56,38,12,7);                       // Create a Rectangle Full.
                 u8g.setColorIndex(0);                          // Turn OFF the Pixels.
                 u8g.setFont(u8g_font_04b_03);                  // Set the font u8g_font_04b_03
                 u8g.drawStr(56, 44, "<A>");                    // Print the LOGO of <ANSDLES>
                 u8g.setColorIndex(1);                          // Turn ON the Pixels.
                 u8g.drawStr(75, 44, "------------");           // Print the Line ------------

                 u8g.drawLine(68, 40, 70, 40);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(68, 41, 70, 41);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(68, 42, 70, 42);                  // Line from the Center Upper Side.    ------
                 u8g.drawFrame( 72, 23, 54, 36);                // Create rectangle Empty.
                 u8g.drawFrame( 71, 22, 56, 38);                // Create rectangle Empty.
                 u8g.drawBitmapP(74, 27, 1, 9, thermometer);    // FUNCTION thermometer( X,  Y, Start, End, Variable);                 
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(84, 34);                       // Set the pixel to print.
                 u8g.print(tempHDC1080,1);                      // Print the External Temperature and specify the precision from HDC1080. (variable, number of precision);
                 u8g.drawStr(114, 31, ".");                     // Printing the character º.
                 u8g.drawStr(119, 36, "C");                     // Printing the letter C.

                 u8g.drawBitmapP(74, 45, 1, 9, drop);           // FUNCTION drop( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(84, 54);                       // Set the pixel to print.
                 u8g.print(humiHDC1080,1);                      // Print the External Humidity and specify the precision from HDC1080. (variable, number of precision);
                 u8g.drawStr(119, 54, "%");                     // Printing the letter %.
            }
          //========================HDC_1080_PAGE========================


          //========================DHT__11__PAGE========================
            void dht11Page(){

                 humidityDHT_11    = dht.readHumidity();           // The variable humidityDHT_11 receive the value from dht.readHumidity();
                 temperatureDHT_11 = dht.readTemperature();        // The variable temperatureDHT_11 receive the value from dht.readTemperature();

                 if(temperatureDHT_11 > maxTempDHT_11){   // Test if the current temperature is higher than the Maximum.
                    maxTempDHT_11 = temperatureDHT_11;   
                 }
                 if(temperatureDHT_11 < minTempDHT_11){   // Test if the current temperature is lower than the Minimum.
                    minTempDHT_11 = temperatureDHT_11;
                 }
                 if(humidityDHT_11 > maxHumiDHT_11){      // Test if the current Humidity is higher than the Maximum.
                    maxHumiDHT_11 = humidityDHT_11;    
                 }
                 if(humidityDHT_11 < minHumiDHT_11){      // Test if the current Humidity is lower than the Minimum.
                    minHumiDHT_11 = humidityDHT_11;
                 }


                 u8g.setFont(u8g_font_6x10);               // Set the font u8g_font_6x10.
                 u8g.drawBox(18,1,93,18);                  // Create a Rectangle Full.
                 u8g.setColorIndex(0);                     // Turn OFF the Pixels.
                 u8g.drawStr(20, 9, "Internal Sensor");    // Printing the message.
                 u8g.drawStr(38, 18,  "D H T  11");        // Printing the message.
                 u8g.setColorIndex(1);                     // Turn ON the Pixels.


                 u8g.drawLine(7, 9, 17, 9);                // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 10, 17, 10);              // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 11, 7, 19);               // Line from the Left Upper Side.       ||
                 u8g.drawLine(8, 11, 8, 19);               // Line from the Left Upper Side.       ||
                 
                 u8g.drawLine(111, 9, 120, 9);             // Line from the Right Upper Side.    ------
                 u8g.drawLine(111, 10, 120, 10);           // Line from the Right Upper Side.    ------
                 u8g.drawLine(119, 11, 119, 21);           // Line from the Right Upper Side.      ||
                 u8g.drawLine(120, 11, 120, 21);           // Line from the Right Upper Side.      ||


                 u8g.drawFrame( 1, 20, 53, 21);                 // Create rectangle Empty.
                 u8g.drawBitmapP(4, 21, 1, 9, arrowToUP);       // FUNCTION arrowToUP( X,  Y, Start, End, Variable);
                 u8g.drawBitmapP(16, 21, 1, 9, thermometer);    // FUNCTION thermometer( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the u8g_font_6x10.
                 u8g.setPrintPos(25, 29);                       // Set the pixel to print.
                 u8g.print(maxTempDHT_11,0);                    // Print the Internal Temperature and specify the precision from DHT_11. (variable, number of precision);
                 u8g.drawStr(38, 24, ".");                      // Printing the character º.
                 u8g.drawStr(43, 29, "C");                      // Printing the letter C.

                 u8g.drawBitmapP(4, 31, 1, 9, arrowToDOWN);     // FUNCTION arrowToDOWN( X,  Y, Start, End, Variable);
                 u8g.drawBitmapP(16, 31, 1, 9, thermometer);    // FUNCTION thermometer( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the u8g_font_6x10.
                 u8g.setPrintPos(25, 39);                       // Set the pixel to print.
                 u8g.print(minTempDHT_11,0);                    // Print the Internal Temperature and specify the precision from DHT_11. (variable, number of precision);
                 u8g.drawStr(38, 34, ".");                      // Printing the character º.
                 u8g.drawStr(43, 39, "C");                      // Printing the letter C.



                 u8g.drawLine(54, 29, 61, 29);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(61, 30, 61, 37);                  // Line from the Center Upper Side.      ||


                 u8g.drawFrame( 1, 42, 53, 21);                 // Create rectangle Empty.
                 u8g.drawBitmapP(4, 43, 1, 9, arrowToUP);       // FUNCTION arrowToUP( X,  Y, Start, End, Variable);
                 u8g.drawBitmapP(16, 43, 1, 9, drop);           // FUNCTION drop( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(25, 51);                       // Set the pixel to print.
                 u8g.print(maxHumiDHT_11,0);                    // Print the Internal Humidity and specify the precision from DHT_11. (variable, number of precision);
                 u8g.drawStr(43, 51, "%");                      // Printing the letter %.

                 u8g.drawBitmapP(4, 53, 1, 9, arrowToDOWN);     // FUNCTION arrowToUP( X,  Y, Start, End, Variable);
                 u8g.drawBitmapP(16, 53, 1, 9, drop);           // FUNCTION drop( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(25, 61);                       // Set the pixel to print.
                 u8g.print(minHumiDHT_11,0);                    // Print the Internal Humidity and specify the precision from DHT_11. (variable, number of precision);
                 u8g.drawStr(43, 61, "%");                      // Printing the letter %.
 
                 u8g.drawLine(54, 53, 61, 53);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(61, 45, 61, 52);                  // Line from the Center Upper Side.      ||


                 u8g.drawBox(56,38,12,7);                       // Create a Rectangle Full.
                 u8g.setColorIndex(0);                          // Turn OFF the Pixels.
                 u8g.setFont(u8g_font_04b_03);                  // Set the font u8g_font_04b_03
                 u8g.drawStr(56, 44, "<A>");                    // Print the LOGO of <ANSDLES>
                 u8g.setColorIndex(1);                          // Turn ON the Pixels.
                 u8g.drawStr(75, 44, "------------");           // Print the Line ------------


                 u8g.drawLine(68, 40, 70, 40);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(68, 41, 70, 41);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(68, 42, 70, 42);                  // Line from the Center Upper Side.    ------
                 u8g.drawFrame( 72, 23, 54, 36);                // Create rectangle Empty.
                 u8g.drawFrame( 71, 22, 56, 38);                // Create rectangle Empty.
                 u8g.drawBitmapP(82, 27, 1, 9, thermometer);    // FUNCTION thermometer( X,  Y, Start, End, Variable);                 
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(92, 36);                       // Set the pixel to print.
                 u8g.print(temperatureDHT_11,0);                // Print the Internal Temperature and specify the precision from DHT_11. (variable, number of precision);
                 u8g.drawStr(106, 31, ".");                     // Printing the character º.
                 u8g.drawStr(111, 36, "C");                     // Printing the letter C.

                 u8g.drawBitmapP(82, 45, 1, 9, drop);           // FUNCTION drop( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(92, 54);                       // Set the pixel to print.
                 u8g.print(humidityDHT_11,0);                   // Print the Internal Humidity and specify the precision from DHT_11. (variable, number of precision);
                 u8g.drawStr(109, 54, "%");                     // Printing the letter %.
            }
          //========================DHT__11__PAGE========================

          //========================BMP_180__PAGE========================
            void bmp180Page(){
                 pressureP = bmp.readSealevelPressure();   // Receive the value of pressure from BMP180.
                 altitudeA = bmp.readAltitude(correction_altitude);     // Receive the value of altitude from BMP180.

                 
                 if(pressureP > maxPressureP){             // Test if the current temperature is higher than the Maximum.
                    maxPressureP = pressureP;   
                 }
                 if(pressureP < minPressureP){             // Test if the current temperature is lower than the Minimum.
                    minPressureP = pressureP;
                 }
                 if(altitudeA > maxAltitudeA){             // Test if the current Humidity is higher than the Maximum.
                    maxAltitudeA = altitudeA;    
                 }
                 if(altitudeA < minAltitudeA){             // Test if the current Humidity is lower than the Minimum.
                    minAltitudeA = altitudeA;
                 }

                 
                 u8g.setFont(u8g_font_6x10);               // Set the font u8g_font_6x10.
                 u8g.drawBox(18,1,93,18);                  // Create a Rectangle Full.
                 u8g.setColorIndex(0);                     // Turn OFF the Pixels.
                 u8g.drawStr(20, 9, "Internal Sensor");    // Printing the message.
                 u8g.drawStr(35, 18,  "B M P  180");       // Printing the message.
                 u8g.setColorIndex(1);                     // Turn ON the Pixels.


                 u8g.drawLine(7, 9, 17, 9);                // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 10, 17, 10);              // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 11, 7, 19);               // Line from the Left Upper Side.       ||
                 u8g.drawLine(8, 11, 8, 19);               // Line from the Left Upper Side.       ||
                 
                 u8g.drawLine(111, 9, 120, 9);             // Line from the Right Upper Side.    ------
                 u8g.drawLine(111, 10, 120, 10);           // Line from the Right Upper Side.    ------
                 u8g.drawLine(119, 11, 119, 21);           // Line from the Right Upper Side.      ||
                 u8g.drawLine(120, 11, 120, 21);           // Line from the Right Upper Side.      ||


                 u8g.drawFrame( 1, 20, 53, 21);                 // Create rectangle Empty.
                 u8g.drawBitmapP(4, 21, 1, 9, arrowToUP);       // FUNCTION arrowToUP( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the u8g_font_6x10.
                 u8g.setPrintPos(15, 29);                       // Set the pixel to print.
                 u8g.print(maxPressureP,0);


                 u8g.drawBitmapP(4, 31, 1, 9, arrowToDOWN);     // FUNCTION arrowToDOWN( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the u8g_font_6x10.
                 u8g.setPrintPos(15, 39);                       // Set the pixel to print.
                 u8g.print(minPressureP,0);


                 u8g.drawLine(54, 29, 61, 29);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(61, 30, 61, 37);                  // Line from the Center Upper Side.      ||


                 u8g.drawFrame( 1, 42, 53, 21);                 // Create rectangle Empty.
                 u8g.drawBitmapP(10, 43, 1, 9, arrowToUP);       // FUNCTION arrowToUP( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(22, 51);                       // Set the pixel to print.
                 u8g.print(maxAltitudeA,0);

                 u8g.drawBitmapP(10, 53, 1, 9, arrowToDOWN);     // FUNCTION arrowToUP( X,  Y, Start, End, Variable);
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(22, 61);                       // Set the pixel to print.
                 u8g.print(minAltitudeA,0);


                 u8g.drawLine(54, 53, 61, 53);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(61, 45, 61, 52);                  // Line from the Center Upper Side.      ||


                 u8g.drawBox(56,38,12,7);                       // Create a Rectangle Full.
                 u8g.setColorIndex(0);                          // Turn OFF the Pixels.
                 u8g.setFont(u8g_font_04b_03);                  // Set the font u8g_font_04b_03
                 u8g.drawStr(56, 44, "<A>");                    // Print the LOGO of <ANSDLES>
                 u8g.setColorIndex(1);                          // Turn ON the Pixels.
                 u8g.drawStr(75, 44, "------------");           // Print the Line ------------


                 u8g.drawLine(68, 40, 70, 40);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(68, 41, 70, 41);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(68, 42, 70, 42);                  // Line from the Center Upper Side.    ------
                 u8g.drawFrame( 72, 23, 54, 36);                // Create rectangle Empty.
                 u8g.drawFrame( 71, 22, 56, 38);                // Create rectangle Empty.
                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(75, 36);                       // Set the pixel to print.
                 u8g.print(pressureP/1000,1);
                 u8g.drawStr(106, 36, "Kpa");  

                 u8g.setFont(u8g_font_6x10);                    // Set the font u8g_font_6x10.
                 u8g.setPrintPos(80, 54);                       // Set the pixel to print.
                 u8g.print(altitudeA,1);
                 u8g.drawStr(118, 54, "M");
          }
          //========================BMP_180__PAGE========================
          
          //========================stopWatchPAGE========================
            void stopWatch(){
                 byte ButtonSelect = digitalRead(pinButton_Select); // The variable ButtonSelect receive the value from Button.
                 
                 if(hour == 24){                           // Test if the hour are 24. If it is, the Stopwatch will be stopped.
                   control = 2;
                 }
                 if(ButtonSelect == 0){                    // Test if the ButtonSelect is equal to 0.
                    control++;                             // Increment the variable of control.
                    delay(250);                            // It wait 1/4 of second.
                 }
                 if(control >= 3){                         // Return to count of Stopwatch.
                    control = 1;                           // Set value 1 to variable of control.
                 }


                 if(control == 0){                         // Test if the control is equal the 0 and print a message.
                    functionDisplay_stopwatch();           // Print the Graphic module.
                    u8g.drawStr(47, 32, "Start?");
                    u8g.setFont(u8g_font_unifont);         // Set the font u8g_font_unifont
                    u8g.drawStr(28, 51, "00");             // Print a caracter. ↓
                    u8g.drawStr(43, 51, ":");
                    u8g.drawStr(50, 51, "00");
                    u8g.drawStr(65, 51, ":");
                    u8g.drawStr(72, 51, "00");
                    u8g.drawStr(87, 51, ":");
                    u8g.drawStr(94, 51, "0");              // Print a caracter. ↑
                    confirmToExecute = false;               // It control the reset function to not reset when the Stopwatch is in executation. (AVOID BUG).
                    Time = millis();                        // This variable Receive the current value in this time.
                 }
                      
                 
                 if(control == 1){                       //===EXECUTE the Stopwatch.===
                  
                  u8g.firstPage();                       // Hold on the display freeze.
                   do{                                   // Starting the Loop While to STOPWATCH.
                    functionDisplay_stopwatch();         // Print the Graphic module.
                    u8g.setFont(u8g_font_6x10);          // Set the font u8g_font_6x10.
                    u8g.drawStr(38, 32, "Executing");
                    u8g.setFont(u8g_font_unifont);       // Set the font u8g_font_unifont.
                    current = millis();                  // This variable Receive the current value in this time.
                    dsecond = (current-Time) / 100;      // dsecond receive the current time(current) - last time (Time) making up sense to stopwatch.
                    u8g.setPrintPos(28, 51);
                    u8g.print(hour);                     // Print the hour.
                    u8g.drawStr(43, 51, ":");
                    u8g.setPrintPos(50, 51);
                    u8g.print(minute);                   // Print the minute.
                    u8g.drawStr(65, 51, ":");
                    u8g.setPrintPos(74, 51);
                    u8g.print(second);                   // Print the second.
                    u8g.drawStr(87, 51, ":");
                    u8g.setPrintPos(94, 51);
                    u8g.print(dsecond);                  // Print the dsecond.
                    

                    if(dsecond > 9){                     // It test if (dsecond) is higher than a 9 seconds.
                       Time = millis();
                       second++;
                       second2++;
                    }
                    if(second > 59){                     // It test if (second) is higher than a 59 seconds.
                       Time = millis();
                       second = 0;
                       minute++;
                    }
                    if(minute > 59){                     // It test if (minute) is higher than a 59 minutes.
                       Time = millis();
                       minute = 0;
                       hour++;
                    }
                    confirmToExecute = false;            // It control the reset function to not reset when the Stopwatch is in executation. (AVOID BUG).
                    
                    }while(u8g.nextPage());              // Test the Loop While.
                 }
                    
                    
                    if(control == 2){                       //===PAUSE the Stopwatch.===
                       functionDisplay_stopwatch();         // Print the Graphic module.
                       u8g.setFont(u8g_font_6x10);          // Set the font u8g_font_6x10.
                       u8g.drawStr(47, 32, "PAUSED");
                       u8g.setFont(u8g_font_unifont);       // Set the font u8g_font_unifont.
                       u8g.setPrintPos(28, 51);
                       u8g.print(hour);                     // Print the hour.
                       u8g.drawStr(43, 51, ":");
                       u8g.setPrintPos(50, 51);
                       u8g.print(minute);                   // Print the minu.
                       u8g.drawStr(65, 51, ":");
                       u8g.setPrintPos(74, 51);
                       u8g.print(second);                   // Print the second.
                       u8g.drawStr(87, 51, ":");
                       u8g.setPrintPos(94, 51);
                       u8g.print(dsecond);                  // Print the dsecond.
                       Time = millis();
                       
                       u8g.setFont(u8g_font_04b_03);        // Set the font u8g_font_04b_03
                       u8g.drawStr(45, 61, "Sec: ");        // Print ONLY the second.
                       u8g.setPrintPos(62, 61);
                       u8g.print(second2);                  // Print ONLY the second.
                       confirmToExecute = true;             // It control the reset function to reset ONLY when the Stopwatch is in PAUSE. (AVOID BUG).
                    }
            }
            void functionDisplay_stopwatch(){                 
                 u8g.setFont(u8g_font_6x10);               // Set the font u8g_font_6x10.
                 u8g.drawBox(18,1,93,18);                  // Create a Rectangle Full.
                 u8g.setColorIndex(0);                     // Turn OFF the Pixels.
                 u8g.drawStr(20, 9,  "F U N C T I O N");   // Printing a word.
                 u8g.drawStr(37, 18, "STOPWATCH");         // Printing a word.
                 u8g.setColorIndex(1);                     // Turn ON the Pixels.
                 
                 u8g.drawLine(7, 9, 17, 9);                // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 10, 17, 10);              // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 11, 7, 27);               // Column from the Left Upper Side.     ||
                 u8g.drawLine(8, 11, 8, 27);               // Column from the Left Upper Side.     ||
                 u8g.drawLine(7, 28, 33, 28);              // Line from the Left middle Side.    ------
                 u8g.drawLine(7, 29, 33, 29);              // Line from the Left middle Side.    ------
                 
                 u8g.drawLine(111, 9, 120, 9);             // Line from the Right Upper Side.    ------
                 u8g.drawLine(111, 10, 120, 10);           // Line from the Right Upper Side.    ------
                 u8g.drawLine(119, 11, 119, 29);           // Column from the Right Upper Side.    ||
                 u8g.drawLine(120, 11, 120, 29);           // Column from the Right Upper Side.    ||
                 u8g.drawLine(95, 28, 118, 28);            // Line from the Right middle Side.   ------
                 u8g.drawLine(95, 29, 118, 29);            // Line from the Right middle Side.   ------
                 u8g.drawFrame(35, 21, 59, 15);            // Create rectangle's words.
                 u8g.drawFrame(34, 20, 61, 17);            // Create rectangle's words.
                 u8g.drawLine(62, 37, 66, 37);             // Line from the middle bottom Side.  ------
                 u8g.drawFrame(26, 38, 78, 16);            // Create rectangle's Time.
                 u8g.drawLine(31, 54, 31, 57);             // Column from the Left Upper Side.     ||
                 u8g.drawLine(31, 58, 41, 58);             // Line from the Left bottom Side.    ------
                 u8g.drawLine(98, 54, 98, 57);             // Column from the Right Upper Side.    ||
                 u8g.drawLine(88, 58, 98, 58);             // Line from the Right bottom Side.   ------
                 }
          //========================stopWatchPAGE========================

          //========================RunTime__PAGE========================
            void runTime(){
              logoSU = true;       // This command is to activate completely the function suelen_memory().
              logoSU_2 = true;     // This command is to activate completely the function suelen_memory().
             u8g.firstPage();                       // Hold on the display freeze.
              do{                                   // Starting the Loop While to STOPWATCH.
                 functionDisplay_RunTime();         // Print the Graphic module.
                 u8g.setFont(u8g_font_6x10);        // Set the font u8g_font_6x10.
                 if(millis() < 10000){
                    u8g.setPrintPos(96, 37);
                    u8g.print(millis()/1000);       // 1000 ms / 1000 = 1 Second.
                    
                 }else if(millis() > 9999 && millis() < 100000){
                          u8g.setPrintPos(93, 37);
                          u8g.print(millis()/1000);   // 1000 ms / 1000 = 1 Second.
                          
                 }else if(millis() > 99999 && millis() < 1000000){
                          u8g.setPrintPos(90, 37);
                          u8g.print(millis()/1000);   // 1000 ms / 1000 = 1 Second.
                          
                 }else if(millis() > 999999 && millis() < 10000000){
                          u8g.setPrintPos(87, 37);
                          u8g.print(millis()/1000);   // 1000 ms / 1000 = 1 Second.
                          
                 }else if(millis() > 9999999 && millis() < 100000000){
                          u8g.setPrintPos(84, 37);
                          u8g.print(millis()/1000);   // 1000 ms / 1000 = 1 Second.
                          
                 }else if(millis() > 99999999 && millis() < 1000000000){
                          u8g.setPrintPos(81, 37);
                          u8g.print(millis()/1000);   // 1000 ms / 1000 = 1 Second.
                          
                 }
                 u8g.drawStr(78, 50,  "Seconds");

                 u8g.setPrintPos(11, 30);
                 u8g.print(RTsecond);            // Print second.
                 u8g.drawStr(26, 30,  "s");
                 u8g.setPrintPos(11, 40);
                 u8g.print(RTminute);            // Print minute.
                 u8g.drawStr(26, 40,  "min");
                 u8g.setPrintPos(11, 50);
                 u8g.print(RThour);              // Print Hour.
                 u8g.drawStr(26, 50,  "h");
                 u8g.setPrintPos(11, 60);
                 u8g.print(RTday);               // Print Day.
                 u8g.drawStr(26, 60,  "days");
               }while(u8g.nextPage());              // Test the Loop While.                                
            }
            
            void functionDisplay_RunTime(){
                 u8g.setFont(u8g_font_6x10);               // Set the font u8g_font_6x10.
                 u8g.drawBox(18,1,93,18);                  // Create a Rectangle Full.
                 u8g.setColorIndex(0);                     // Turn OFF the Pixels.
                 u8g.drawStr(20, 9,  "F U N C T I O N");   // Printing a word.
                 u8g.drawStr(26, 18, "R U N T I M E");     // Printing a word.
                 u8g.setColorIndex(1);                     // Turn ON the Pixels.

                 u8g.drawLine(7, 9, 17, 9);                // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 10, 17, 10);              // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 11, 7, 61);               // Line from the Left Upper Side.       ||
                 u8g.drawLine(8, 11, 8, 61);               // Line from the Left Upper Side.       ||
                 
                 u8g.drawLine(111, 9, 120, 9);             // Line from the Right Upper Side.    ------
                 u8g.drawLine(111, 10, 120, 10);           // Line from the Right Upper Side.    ------
                 u8g.drawLine(119, 11, 119, 21);           // Line from the Right Upper Side.      ||
                 u8g.drawLine(120, 11, 120, 21);           // Line from the Right Upper Side.      ||

                 u8g.drawLine(7, 21, 51, 21);                // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 31, 51, 31);                // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 41, 55, 41);                // Line from the Left Middle Side.    ------
                 u8g.drawLine(7, 51, 51, 51);                // Line from the Left Lower Side.     ------
                 u8g.drawLine(7, 61, 51, 61);                // Line from the Left Lower Side.     ------
                 u8g.drawLine(52, 21, 52, 61);                // Line from the Left Upper Side.       ||

                 u8g.drawBox(56,38,12,7);                       // Create a Rectangle Full.
                 u8g.setColorIndex(0);                          // Turn OFF the Pixels.
                 u8g.setFont(u8g_font_04b_03);                  // Set the font u8g_font_04b_03
                 u8g.drawStr(56, 44, "<A>");                    // Print the LOGO of <ANSDLES>
                 u8g.setColorIndex(1);                          // Turn ON the Pixels.
                 u8g.drawStr(75, 43, "------------");           // Print the Line ------------

                 u8g.drawLine(68, 40, 70, 40);                  // Line from the Center Upper Side.    ------
                 u8g.drawLine(68, 41, 70, 41);                  // Line from the Center Middle Side.    ------
                 u8g.drawLine(68, 42, 70, 42);                  // Line from the Center Lower Side.    ------
                 
                 u8g.drawFrame( 72, 23, 54, 36);                // Create rectangle Empty.
                 u8g.drawFrame( 71, 22, 56, 38);                // Create rectangle Empty.
            }
            
          //========================RunTime__PAGE========================
          
          //========================UVM30____PAGE========================
            void uvm30aSensorPage(){

                 int sensor_value;   // The variable that receive the value from sensor.
                 int voltage;        // The variable that stores real value from sensor.
                 sensor_value = analogRead(A2);                    // The port used from sensor.
                 voltage = (sensor_value * (5.0 / 1023.0)) * 1000; // A calculation did to find the real value from sensor.

                 u8g.setFont(u8g_font_6x10);               // Set the font u8g_font_6x10.
                 u8g.drawBox(18,1,93,18);                  // Create a Rectangle Full.
                 u8g.setColorIndex(0);                     // Turn OFF the Pixels.
                 u8g.drawStr(20, 9, "External Sensor");    // Printing the message.
                 u8g.drawStr(36, 18, "U V M  3 0");        // Printing the message.
                 u8g.setColorIndex(1);                     // Turn ON the Pixels.


                if (voltage >= 0 && voltage <= 227){              // Execute the specific sentence within the values collected from sensor.
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                    u8g.drawStr(40, 50, "No UVRad");              // Printing the message. 
                      
                    u8g.drawStr(27, 32, "RiskIndex:");            // Printing the message.
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(91, 34, "0");                     // Printing a number.
                    
           
                }else if (voltage > 227 && voltage <= 318){       // The same thing again below ↓↓↓.
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.                 
                    u8g.drawStr(35, 50, "Safe UVRad");
                    u8g.drawStr(27, 32, "RiskIndex:");;
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(91, 34, "1");
           
                }else if (voltage > 318 && voltage <= 408){       // ↨↨↨
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                                    
                    u8g.drawStr(37, 50, "Low UVRad");
                    u8g.drawStr(27, 32, "RiskIndex:");
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(91, 34, "2");
           
                }else if (voltage > 408 && voltage <= 503){       // ↨↨↨
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                                 
                    u8g.drawStr(29, 50, "Medium UVRad"); 
                    u8g.drawStr(27, 32, "RiskIndex:");
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(91, 34, "3");
           
                }else if (voltage > 503 && voltage <= 606){       // ↨↨↨
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                                    
                    u8g.drawStr(29, 50, "Medium UVRad"); 
                    u8g.drawStr(27, 32, "RiskIndex:");
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(91, 34, "4");
            
                }else if (voltage > 606 && voltage <= 696){       // ↨↨↨
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                                     
                    u8g.drawStr(29, 50, "Medium UVRad"); 
                    u8g.drawStr(27, 32, "RiskIndex:");
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(91, 34, "5");
           
                }else if (voltage > 696 && voltage <= 795){       // ↨↨↨
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                                     
                    u8g.drawStr(29, 50, "High UVRad");
                    u8g.drawStr(27, 32, "RiskIndex:");
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(91, 34, "6");
           
                }else if (voltage > 795 && voltage <= 881){       // ↨↨↨
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                                  
                    u8g.drawStr(29, 50, "High UVRad");
                    u8g.drawStr(27, 32, "RiskIndex:");
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(91, 34, "7");
           
                }else if (voltage > 881 && voltage <= 976){       // ↨↨↨
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                                 
                    u8g.drawStr(26, 50, "Harmful UVRad");
                    
                    u8g.drawStr(27, 32, "RiskIndex:");
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(91, 34, "8");
           
                }else if (voltage > 976 && voltage <= 1079){      // ↨↨↨
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                                    
                    u8g.drawStr(26, 50, "Harmful UVRad");
                    
                    u8g.drawStr(27, 32, "RiskIndex:");
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(91, 34, "9");
           
                }else if (voltage > 1079 && voltage <= 1170){     // ↨↨↨
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                                     
                    u8g.drawStr(26, 50, "Harmful UVRad");
                    
                    u8g.drawStr(27, 32, "RiskIndex:");
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(87, 34, "10"); 
           
                }else if (voltage > 1170){                        // ↨↨↨
                    u8g.setFont(u8g_font_6x10);                   // Set the font u8g_font_6x10.
                                     
                    u8g.drawStr(27, 50, "Deadly UVRad!");
                    u8g.drawStr(27, 32, "RiskIndex:");
                    u8g.setFont(u8g_font_unifont);                // Set the font u8g_font_unifont.
                    u8g.drawStr(87, 34, "11");  
                }

                 
                 u8g.drawLine(7, 9, 17, 9);                // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 10, 17, 10);              // Line from the Left Upper Side.     ------
                 u8g.drawLine(7, 11, 7, 27);               // Column from the Left Upper Side.     ||
                 u8g.drawLine(8, 11, 8, 27);               // Column from the Left Upper Side.     ||
                 u8g.drawLine(7, 28, 21, 28);              // Line from the Left middle Side.    ------
                 u8g.drawLine(7, 29, 21, 29);              // Line from the Left middle Side.    ------
                 u8g.drawLine(111, 9, 120, 9);             // Line from the Right Upper Side.    ------
                 u8g.drawLine(111, 10, 120, 10);           // Line from the Right Upper Side.    ------
                 u8g.drawLine(119, 11, 119, 29);           // Column from the Right Upper Side.    ||
                 u8g.drawLine(120, 11, 120, 29);           // Column from the Right Upper Side.    ||
                 u8g.drawLine(107, 28, 118, 28);           // Line from the Right middle Side.   ------
                 u8g.drawLine(107, 29, 118, 29);           // Line from the Right middle Side.   ------
                 u8g.drawFrame(23, 21, 83, 15);            // Create rectangle's words.
                 u8g.drawFrame(22, 20, 85, 17);            // Create rectangle's words.
                 u8g.drawLine(62, 37, 66, 37);             // Line from the middle bottom Side.  ------
                 u8g.drawFrame(20, 38, 89, 16);            // Create rectangle's Time.
                 u8g.drawLine(31, 54, 31, 57);             // Column from the Left Upper Side.     ||
                 u8g.drawLine(31, 58, 65, 58);             // Line from the Left bottom Side.    ------
                 u8g.drawLine(98, 54, 98, 57);             // Column from the Right Upper Side.    ||
                 u8g.drawLine(66, 58, 98, 58);             // Line from the Right bottom Side.   ------
          }
          //========================UVM30____PAGE========================

          //=======================FUNCTION_LIGHT========================
          void functionLight(){

               if(numSelectSwitch == 1 && valuepinButtonSelect == 0 && lightSelect == 0){      // Set the maximum light of Screen.
                  valuepinButtonSelect = 1;
                  lightSelect = 1;
                   pinMode(31, OUTPUT);      // It turn ON the light of Screen.
                   digitalWrite(31, HIGH);   // It turn ON the light of Screen.
                   pinMode(33, INPUT);       // It turn OFF the light of Screen.
                   pinMode(35, INPUT);       // It turn OFF the light of Screen.
                   delay(150);
               }
               if(numSelectSwitch == 1 && valuepinButtonSelect == 0 && lightSelect == 1){       // Set the Middle light of Screen.
                  valuepinButtonSelect = 1;
                  lightSelect = 2;
                  pinMode(31, INPUT);       // It turn OFF the light of Screen.
                  pinMode(33, OUTPUT);      // It turn ON the light of Screen.
                  digitalWrite(33, HIGH);   // It turn ON the light of Screen.
                  pinMode(35, INPUT);       // It turn OFF the light of Screen.
                  delay(150);
               }
               if(numSelectSwitch == 1 && valuepinButtonSelect == 0 && lightSelect == 2){       // Set the Lower light of Screen.
                  valuepinButtonSelect = 1;
                   lightSelect = 0;
                   pinMode(31, INPUT);       // It turn OFF the light of Screen.
                   pinMode(33, INPUT);       // It turn OFF the light of Screen.
                   pinMode(35, OUTPUT);      // It turn ON the light of Screen.
                   digitalWrite(35, HIGH);   // It turn ON the light of Screen.
                   delay(150);
              }
          }
          //=======================FUNCTION_LIGHT========================

          void suelen_memory(){
                                       
                  if(logoSU == true){                              // Show first a message.
                    u8g.firstPage();
                      do{
                        u8g.setFont(u8g_font_6x10);                // Set the font "u8g_font_6x10".
                        u8g.drawStr(58,11, "Em");    // Print a message.
                        u8g.drawStr(21, 23, "Memoria de uma");    // Print a message.
                        u8g.setFont(u8g_font_unifont);             // Set the font "unifont".
                        u8g.drawStr(32, 47, "Princesa");           // Print a message.
                        u8g.drawStr(33, 47, "Princesa");           // Print a message.
                      }while(u8g.nextPage());
                    delay(3000);  
                    logoSU = false;                                // This option avoid show the message again.
                  }
 
                  if(logoSU_2 == true){
                     u8g.firstPage();
                      do{
                        //Function( X, Y,  W,  H);
                        u8g.drawFrame( 0, 0,128, 64);  // Create rectangle
                        u8g.drawFrame( 2, 2,124, 60);  // Create rectangle
                        u8g.setFont(u8g_font_unifont);             // Set the font "unifont".
                        u8g.drawStr(16, 18, "OI Suelen :)");         // Print Suelen in 3D.
                        u8g.drawStr(17, 19, "OI Suelen :)");         // Print Suelen in 3D.
                        u8g.setFont(u8g_font_6x10);                  // Set the font "u8g_font_6x10".
                        u8g.drawStr(35, 34, "17/07/2019");           // Print data of memorial when was created.
                        u8g.drawStr(10, 48, "Voce vai melhorar!");
                        u8g.drawStr(10, 58, "pode acreditar ;)!");
                      }while(u8g.nextPage());
                    delay(7000);  
                    logoSU_2 = false;                                // This option avoid show the message again.
                  
                   }
                    
                  u8g.drawXBMP(0, 0, 128, 64, suelen);
                  
                  u8g.setColorIndex(0);                     // Turn OFF the Pixels.
                  u8g.setFont(u8g_font_unifont);            
                  u8g.drawStr(73, 13, "Suelen");
                  
                  u8g.drawBitmapP(97, 21, 1, 7, star);
                  u8g.setFont(u8g_font_04b_03);
                  u8g.drawStr(77, 35, "28/12/2002");
                  
                  u8g.drawBitmapP(97, 45, 1, 8, cros);
                  u8g.drawStr(77, 60, "27/12/2019");
                  u8g.setColorIndex(1);                     // Turn ON the Pixels.
                  
                  
          }

//-------------------------------------------------------FUNCTION__PAGES-------------------------------------------------------

//----------------------------------------------------------FUNCTIONS----------------------------------------------------------



/*---------COMMANDS_AND_FUNCTIONS---------
 * ----FONTS OF DISPLAY----
 * Small....> "u8g.setFont(u8g_font_04b_03);  "
 * Medium...> "u8g.setFont(u8g_font_6x10);    "
 * Big......> "u8g.setFont(u8g_font_unifont); "
 * Very Big.> "u8g.setFont(u8g_font_osb18);   "   18, 21, 26, 29, 35
 * Another fonts > u8g.setFont(u8g_font_robot_de_niro);  u8g.setFont(u8g_font_helvB08);  u8g.setFont(u8g_font_8x13);  u8g.setFont(u8g_font_ncenB10);
 */
