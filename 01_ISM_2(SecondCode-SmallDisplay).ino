/*  ISM 2 - INTERPRETADOR DE SENSORES MÓVEIS
 *   
 *  Manager:    Rafael Albino
 *  Programmer: Rafael Albino
 *  Start:      24/08/2019 às 14:44
 *  End:        28/08/2019 às 12:51
 *   
 */

//-------------------------------------------LIBRARIES-------------------------------------------

#include <Adafruit_GFX.h>              // Include core graphics library for the display.
#include <Adafruit_SSD1306.h>          // Include Adafruit_SSD1306 library to drive the display.
Adafruit_SSD1306 display(128, 64);     // Create a object of display.
#include <Fonts/FreeMono9pt7b.h>       // Add a custom font
#include <Fonts/FreeMono12pt7b.h>       // Add a custom font
#include <Fonts/FreeSerif18pt7b.h>     // Add a custom font
#include <Fonts/FreeMonoBold9pt7b.h>   // Add a custom font
#include <Fonts/FreeSerif9pt7b.h>      // Add a custom font

#include <DS3231.h>                    // The library necessery to use the module DS3231.
DS3231  rtc(SDA, SCL);                 // Set where the date is coming.
Time  t;                               // Create a objetc t from class Time.

#define pinButton_SetDate 15            // Set the pinButton_Set to Pin A1      -- button BLACK  --
#define pinButton_SelectOption 14       // Set the pinButton_Select to Pin A0   -- button YELLOW --

//-------------------------------------------LIBRARIES-------------------------------------------

//--------------------------------------PROTOTAPY_FUNCTIONS--------------------------------------

void functionLight(); // It calls the function that change the brightnees of screen.
void logo();          // It calls the function the print the LOGO at the beginning.
void monthAlign();    // It is a function to Align the month on the Screen.
void dateAlign();     // It is a function to Align the complete date on the Screen.
void hourAlign();     // It is a function to Align the hour on the Screen.

void changeDATE();

//--------------------------------------PROTOTAPY_FUNCTIONS--------------------------------------

//----------------------------------------GLOBAL_VARIABLE----------------------------------------

byte valuepinButtonSet;    // Variable of control of the Button Set.
byte valuepinButtonSelect; // Variable of control of the Button Select.
byte lightDisplay = 0;     // Variable of control of the brightnees.

//----------------------------------------GLOBAL_VARIABLE----------------------------------------
void setup() {

display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Initialize display with the I2C address of 0x3C.
display.clearDisplay();                     // Clear the display.
display.setTextColor(WHITE);                // Set color to WHITE.
display.setTextWrap(false);                 // If you use in TRUE, the text will be restored below (wrap) ex: {#programm
                                            //                                                                 ing}.
display.setRotation(0);                     // Set orientation of screen. 0 is setted to normal, 1 is setted to 90º, 2 is setted to 180º and 3 is setted to 270º.
display.dim(0);                             // Set brightness (0 is maximun and 1 is a little dim).
display.display();                          // Print everything we set previously (It works like activating the display).

logo();                                     // It calls the function LOGO.
delay(3300);                                // Wait a time to show the LOGO.

rtc.begin();                                // Starting the object.
   //rtc.setDOW(SUNDAY);        // Set Day-of-Week to SUNDAY
   //rtc.setTime(00, 00, 00);   // Set the time to 12:00:00 (24hr format)
   //rtc.setDate(1, 1, 2000);   // Set the date to DD/MM/YYYY

pinMode(pinButton_SetDate, INPUT_PULLUP);       // Start the Button and active the function PULL UP.
pinMode(pinButton_SelectOption, INPUT_PULLUP);  // Start the Button and active the function PULL UP.

}

void loop() {
  t = rtc.getTime();        // t is receveing data.
  valuepinButtonSet    = digitalRead(pinButton_SetDate);      // The variable valuepinButtonSet receive the value from port pinButton_SetDate.
  valuepinButtonSelect = digitalRead(pinButton_SelectOption); // The variable valuepinButtonSelect receive the value from port pinButton_SelectOption.
  display.clearDisplay();   // Clear the display or refresh it.

  if(valuepinButtonSelect == 0){  // It calls the function functionLight() of the brightnees of screen.
    functionLight();              // It calls the function functionLight() of the brightnees of screen.
  }
  
  monthAlign();                  // It calls the function that will print the month at the TOP of the Screen.
  dateAlign();                   // It calls the function that will print the complete date in the middle of the Screen.
  hourAlign();                   // It calls the function that will print the hour at the bottom of the Screen.

  if(valuepinButtonSet == 0){    // It calls the function changeDATE() to change the DATE.
    changeDATE();                // It calls the function changeDATE() to change the DATE.
  }
  
  display.drawLine(0, 35, 128, 35, WHITE);  // Print a Line.
  display.display(); // Print everything we set previously (It works like activating the display "VERY NECESSERY").
}

//------------------------------MONTH_ALIGN------------------------------
void monthAlign(){                         // It call the function that will print the month at the TOP of the Screen.
  display.setFont(&FreeMonoBold9pt7b);     // Set the font to all possibilities.
  if(t.mon == 1){
    display.setCursor(26, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
    
  }else if(t.mon == 2){
    display.setCursor(21, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
    
  }else if(t.mon == 3){
    display.setCursor(36, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
    
  }else if(t.mon == 4){
    display.setCursor(36, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
    
  }else if(t.mon == 5){
    display.setCursor(45, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
    
  }else if(t.mon == 6){
    display.setCursor(41, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
    
  }else if(t.mon == 7){
    display.setCursor(41, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
    
  }else if(t.mon == 8){
    display.setCursor(32, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
    
  }else if(t.mon == 9){
    display.setCursor(15, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2)); 
    
  }else if(t.mon == 10){
    display.setCursor(26, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
     
  }else if(t.mon == 11){
    display.setCursor(21, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
    
  }else if(t.mon == 12){
    display.setCursor(21, 10);             // Set where it will be printed (x,y).
    display.println(rtc.getMonthStr(2));
  }
}
//------------------------------MONTH_ALIGN------------------------------

//------------------------------DATE__ALIGN------------------------------
void dateAlign(){                      // It call the function that will print the complete date in the middle of the Screen.  
  
  display.setFont(&FreeMono9pt7b);     // Set the font to all Function.
  display.setCursor(10, 31);           // Set where it will be printed (x,y).
  display.print(rtc.getDateStr(2));    // It prints the complete date.
  
}
//------------------------------DATE__ALIGN------------------------------

//------------------------------HOUR__ALIGN------------------------------
void hourAlign(){                      // It calls the function that will print the hour at the bottom of the Screen.

  display.setFont(&FreeSerif18pt7b);   // Set the font to all Function.
  display.setCursor(1, 62);            // Set where it will be printed (x,y).
  display.print(rtc.getTimeStr(2));    // It prints the hour.
  
}
//------------------------------HOUR__ALIGN------------------------------

//----------------------------FUNCTION__LIGHT----------------------------
void functionLight(){       // It calls the function that change the brightnees of screen.

    if(lightDisplay == 0){  // It tests if the variable of control is 0.
      display.dim(1);       // It sets the brightnees LOW.
      delay(200);           // Wait 1/5 of second to AVOID BUG of change LOW or HIGH quickly.
      lightDisplay ++;      // It Prepares the control to set the next action successfully.
    }else{
        display.dim(0);     // It sets the brightnees HIGH.
        delay(200);         // Wait 1/5 of second to AVOID BUG of change LOW or HIGH quickly.
        lightDisplay --;    // It Prepares the control to set the next action successfully.
    }
    
}
//----------------------------FUNCTION__LIGHT----------------------------

//------------------------------CHANGE_DATE------------------------------
void changeDATE(){
  delay(250);                   // Wait a 1/4 seconds to AVOID BUG (change the year in incorrect time.)
  unsigned int yearCH = t.year; // ↓ Create a variable to receive the current time to don't to change if the operator press the button accidentally.
  byte monthCH        = t.mon;  // ↨
  byte dayCH          = t.date; // ↨
  byte hourCH         = t.hour; // ↨
  byte minuteCH       = t.min;  // ↨
  byte secondCH       = t.sec;  // ↑ Create a variable to receive the current time to don't to change if the operator press the button accidentally.
  
  
  while(valuepinButtonSelect == 1){   // YEAR SETTING ===========================================================
    
    valuepinButtonSet    = digitalRead(pinButton_SetDate);       // Check if the button is being pressing.
    valuepinButtonSelect = digitalRead(pinButton_SelectOption);  // Check if the button is being pressing.
    display.clearDisplay();                   // Clear the display.
    display.setFont(&FreeSerif9pt7b);         // Set the font "FreeSerif9pt7b".
    display.setCursor(20, 13);                // Set where it will be printed (x,y).
    display.println("Date setting");          // Print a message.
    display.drawLine(0, 21, 128, 21, WHITE);  // Print a Line.

    if(valuepinButtonSet == 0){               // If the button is pressed, the following command is executed.
      rtc.setDate(dayCH, monthCH , ++yearCH); // change the YEAR.
    }
    if(yearCH > 2099){         // If the year pass 2099, the control reset the year to 2000.
      yearCH = 2000;           // Reset the year to 2000.
    }
    delay(150);                // Wait 0,150 seconds to avoid quickly changes of number of year.
    
    display.setCursor(1, 40);             // Set where it will be printed (x,y).
    display.println("Set YEAR");          // Print a message.
    display.setCursor(85, 60);            // Set where it will be printed (x,y).
    display.println(yearCH);              // Print the current year.
    
    display.display();            // Print everything we set previously (It works like activating the display "VERY NECESSERY").
    
  } 
  
  valuepinButtonSelect = 1;       // Change the value of variable button to 1 to AVOID BUG. (Quickly change of options could be happens.)
  delay(250);                     // Wait a 1/4 seconds to AVOID BUG ↑↑↑.

  
  while(valuepinButtonSelect == 1){   // MONTH SETTING ===========================================================
    valuepinButtonSet    = digitalRead(pinButton_SetDate);       // Check if the button is being pressing.
    valuepinButtonSelect = digitalRead(pinButton_SelectOption);  // Check if the button is being pressing.
    display.clearDisplay();                   // Clear the display.
    display.setFont(&FreeSerif9pt7b);         // Set the font "FreeSerif9pt7b".
    display.setCursor(20, 13);                // Set where it will be printed (x,y).
    display.println("Date setting");          // Print a message.
    display.drawLine(0, 21, 128, 21, WHITE);  // Print a Line.

    if(valuepinButtonSet == 0){               // If the button is pressed, the following command is executed.
      rtc.setDate(dayCH, ++monthCH , yearCH); // change the MONTH.
    }
    if(monthCH > 12){          // If the month pass 12, the control reset the month to 1.
      monthCH = 1;             // Reset the month to 12.
    }
    delay(150);                // Wait 0,150 seconds to avoid quickly changes of number of month.
    
    display.setCursor(1, 40);       // Set where it will be printed (x,y).
    display.println("Set MONTH");   // Print a message.
    display.setCursor(105, 60);     // Set where it will be printed (x,y).
    display.println(monthCH);       // Print the current month.
    
    display.display();              // Print everything we set previously (It works like activating the display "VERY NECESSERY").
    
  } 
  
  valuepinButtonSelect = 1;       // Change the value of variable button to 1 to AVOID BUG. (Quickly change of options could be happens.)
  delay(250);                     // Wait a 1/4 seconds to AVOID BUG ↑↑↑.

  
  while(valuepinButtonSelect == 1){    // DAY SETTING ===========================================================
    valuepinButtonSet    = digitalRead(pinButton_SetDate);        // Check if the button is being pressing.
    valuepinButtonSelect = digitalRead(pinButton_SelectOption);   // Check if the button is being pressing.
    display.clearDisplay();                   // Clear the display.
    display.setFont(&FreeSerif9pt7b);         // Set the font "FreeSerif9pt7b".
    display.setCursor(20, 13);                // Set where it will be printed (x,y).
    display.println("Date setting");          // Print a message.
    display.drawLine(0, 21, 128, 21, WHITE);  // Print a Line.

    if(valuepinButtonSet == 0){               // If the button is pressed, the following command is executed.
      rtc.setDate(++dayCH, monthCH , yearCH); // change the DAY.
    }
    if(dayCH > 31){               // If the day pass 31, the control reset the day to 1.
      dayCH = 1;                  // Reset the day to 1.
    }
    delay(150);                   // Wait 0,150 seconds to avoid quickly changes of number of days.
    
    display.setCursor(1, 40);     // Set where it will be printed (x,y).
    display.println("Set DAY");   // Print a message.
    display.setCursor(105, 60);   // Set where it will be printed (x,y).
    display.println(dayCH);       // Print the current day.
    
    display.display();            // Print everything we set previously (It works like activating the display "VERY NECESSERY").
    
} 

  valuepinButtonSelect = 1;       // Change the value of variable button to 1 to AVOID BUG. (Quickly change of options could be happens.)
  delay(250);                     // Wait a 1/4 seconds to AVOID BUG ↑↑↑.


  while(valuepinButtonSelect == 1){    // HOUR SETTING ===========================================================
    valuepinButtonSet    = digitalRead(pinButton_SetDate);       // Check if the button is being pressing.
    valuepinButtonSelect = digitalRead(pinButton_SelectOption);  // Check if the button is being pressing.
    display.clearDisplay();                   // Clear the display.
    display.setFont(&FreeSerif9pt7b);         // Set the font "FreeSerif9pt7b".
    display.setCursor(20, 13);                // Set where it will be printed (x,y).
    display.println("Date setting");          // Print a message.
    display.drawLine(0, 21, 128, 21, WHITE);  // Print a Line.

    if(valuepinButtonSet == 0){                   // If the button is pressed, the following command is executed.
      rtc.setTime(++hourCH, minuteCH, secondCH);  // change the HOUR.
    }
    if(hourCH > 23){               // If the hour pass 23, the control reset the hour to 1.
      hourCH = 0;                  // Reset the hour to 0.
    }
    delay(150);                    // Wait 0,150 seconds to avoid quickly changes of number of hour.
    
    display.setCursor(1, 40);      // Set where it will be printed (x,y).
    display.println("Set HOUR");   // Print a message.
    display.setCursor(105, 60);    // Set where it will be printed (x,y).
    display.println(hourCH);       // Print the current hour.
    
    display.display();             // Print everything we set previously (It works like activating the display "VERY NECESSERY").
    
  } 
  
  valuepinButtonSelect = 1;       // Change the value of variable button to 1 to AVOID BUG. (Quickly change of options could be happens.)
  delay(250);                     // Wait a 1/4 seconds to AVOID BUG ↑↑↑.


  while(valuepinButtonSelect == 1){    // MINUTE SETTING ===========================================================
    valuepinButtonSet    = digitalRead(pinButton_SetDate);        // Check if the button is being pressing.
    valuepinButtonSelect = digitalRead(pinButton_SelectOption);   // Check if the button is being pressing.
    display.clearDisplay();                   // Clear the display.
    display.setFont(&FreeSerif9pt7b);         // Set the font "FreeSerif9pt7b".
    display.setCursor(20, 13);                // Set where it will be printed (x,y).
    display.println("Date setting");          // Print a message.
    display.drawLine(0, 21, 128, 21, WHITE);  // Print a Line.

    if(valuepinButtonSet == 0){                   // If the button is pressed, the following command is executed.
      rtc.setTime(hourCH, ++minuteCH, secondCH);  // Change the minute.
    }
    if(minuteCH > 59){              // If the minute pass 59, the control reset the minute to 0.
      minuteCH = 0;                 // Reset the minute to 0.
    }
    delay(150);                     // Wait 0,150 seconds to avoid quickly changes of number of minutes.
    
    display.setCursor(1, 40);       // Set where it will be printed (x,y).
    display.println("Set MINUTE");  // Print a message.
    display.setCursor(105, 60);     // Set where it will be printed (x,y).
    display.println(minuteCH);      // Print the current minute.
    
    display.display();              // Print everything we set previously (It works like activating the display "VERY NECESSERY").
    
  } 
  
  valuepinButtonSelect = 1;       // Change the value of variable button to 1 to AVOID BUG. (Quickly change of options could be happens.)
  delay(250);                     // Wait a 1/4 seconds to AVOID BUG ↑↑↑.


  while(valuepinButtonSelect == 1){    // SECOND SETTING ===========================================================
    valuepinButtonSet    = digitalRead(pinButton_SetDate);        // Check if the button is being pressing.
    valuepinButtonSelect = digitalRead(pinButton_SelectOption);   // Check if the button is being pressing.
    display.clearDisplay();                   // Clear the display.
    display.setFont(&FreeSerif9pt7b);         // Set the font "FreeSerif9pt7b".
    display.setCursor(20, 13);                // Set where it will be printed (x,y).
    display.println("Date setting");          // Print a message.
    display.drawLine(0, 21, 128, 21, WHITE);  // Print a Line.

    if(valuepinButtonSet == 0){                   // If the button is pressed, the following command is executed.
      rtc.setTime(hourCH, minuteCH, ++secondCH);  // Change the second.
    }
    if(secondCH > 59){               // If the second pass 59, the control reset the second to 0.
      secondCH = 0;                  // Reset the second to 0.
    }
    delay(150);                      // Wait 0,150 seconds to avoid quickly changes of number of seconds.
    
    display.setCursor(1, 40);        // Set where it will be printed (x,y).
    display.println("Set SECOND");   // Print a message.
    display.setCursor(105, 60);      // Set where it will be printed (x,y).
    display.println(secondCH);       // Print the current second.
    
    display.display();               // Print everything we set previously (It works like activating the display "VERY NECESSERY").
   
  } 
  rtc.setTime(hourCH, minuteCH, secondCH);
  
  valuepinButtonSelect = 1;       // Change the value of variable button to 1 to AVOID BUG. (Quickly change of options could be happens.)
  delay(250);                     // Wait a 1/4 seconds to AVOID BUG ↑↑↑.
  
} 
//------------------------------CHANGE_DATE------------------------------

//----------------------------FUNCTION__LOGO-----------------------------
void logo(){

    //display.setCursor(20, 13);                // Set where it will be printed (x,y).
    //display.println("Date setting");          // Print a message.
    display.clearDisplay();   // Clear the display or refresh it.
    
    display.setFont(&FreeMono12pt7b);  // Set the font "FreeSerif9pt7b".
    display.setCursor(42, 17);
    display.println("<A>");            // Print A.
    display.setCursor(42, 16);         // Print A as BOLD.
    display.println("<A>");            // Print A.

    
    display.setFont(&FreeMono9pt7b);  // Set the font "FreeSerif9pt7b".
    display.setCursor(13, 35);
    display.println("<Ansdles>");      // Print <Ansdles>.
    display.setCursor(13, 35);
    display.println("<       >");      // Print < > with BOLD.
    display.setCursor(14, 36);
    display.println("<Ansdles>");      // Create Effect 3D.
    
    
    display.setFont(&FreeMono12pt7b);  // Set the font "FreeSerif9pt7b".
                                                
                                                // Create the Special Caracter 'I'.   
                                                display.setCursor(5, 51);display.println("I");
display.setCursor(4, 52);display.println("I");  display.setCursor(5, 52);display.println("I");  display.setCursor(6, 52);display.println("I");
                                                display.setCursor(5, 53);display.println("I");


                                                // Create the Special Caracter 'S'.
                                                display.setCursor(56, 59);display.println("S");
display.setCursor(56, 60);display.println("S"); display.setCursor(56, 60);display.println("S");  display.setCursor(57, 60);display.println("S");
                                                display.setCursor(56, 61);display.println("S");

    
                                                  // Create the Special Caracter 'M'.
                                                  display.setCursor(110, 51);display.println("M");
display.setCursor(109, 52);display.println("M");  display.setCursor(110, 52);display.println("M");  display.setCursor(111, 52);display.println("M");
                                                  display.setCursor(110, 53);display.println("M");

   
    display.display(); // Print everything we set previously (It works like activating the display "VERY NECESSERY").
}
//----------------------------FUNCTION__LOGO-----------------------------
