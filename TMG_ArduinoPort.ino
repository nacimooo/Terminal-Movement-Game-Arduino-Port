#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Setup:
// button 1 on pin 4
// button 2 on pin 7
// LCD connected over I2C

// button pins
int btn1pin = 4;
int btn2pin = 7;

// playing field dimentions
int xDim = 16;
int yDim = 2;

// 0 => not pressed
int btn1State = 0;
int btn2State = 0;

// player location
int xCor;
int yCor;

// fruit location
int xfCor;
int yfCor;

// num randomizer
int num = 0;

// score
int score1 = 0;
int score2 = 0;

// setup LCD screen
LiquidCrystal_I2C lcd(0x27, xDim, yDim);

// randomize the location of the Fuit
void randomize(){  
    // keep things random
    if (num > 3){
      num = 0;
      }
    randomSeed(analogRead(num));
    num++;

    // set new location
    xfCor = random(0, 14);
    yfCor = random(yDim);
  }

void setup() {  
  // start the LCD
  lcd.init();
  lcd.backlight();

  // setup the pins for the buttons
  pinMode(btn1pin, INPUT);
  pinMode(btn2pin, INPUT);

  // Delay just for things to set nicely
  delay(15);

  // starting location of the player
  int xCor = 0;
  int yCor = 0;
  
}

  // just run this once but I wanted it to be in the loop() section
  int first = 0;

void loop() {
    // first randomization
    if (first == 0){
      randomize();
      first = 1;
      }

  // print playing field and clear the player's past location
  lcd.setCursor(0,0);
  lcd.print(",,,,,,,,,,,,,,|");
  lcd.setCursor(0,1);
  lcd.print(",,,,,,,,,,,,,,|");


  // print the Fruit
  lcd.setCursor(xfCor, yfCor);
  lcd.print('@');

  // Print Player
  lcd.setCursor(xCor, yCor);
  lcd.print('#');

  // print score area
  lcd.setCursor(xDim-1,yDim-1);
  lcd.print(score1);
  lcd.setCursor(xDim-1,0);
  lcd.print(score2);

  // set the buttons as digital reads 
  btn1State = digitalRead(btn1pin);
  btn2State = digitalRead(btn2pin);


  // run checks for which button is pressed
  if(btn1State == HIGH){
     // move right
     xCor++;
     // except when the limit of the screen is reached
     if (xCor > xDim - 3){
      xCor = xDim - 3;
      }
    }

  if(btn2State == HIGH){
      // move left
      xCor --;
      // except when the limit of the screen is reached
      if (xCor < 0){
          xCor = 0;
        }
    }

  // up and down movement
  if (btn1State == HIGH && btn2State == HIGH){
    if (yCor == 1){
          yCor = 0;
        }
      else if (yCor == 0){
          yCor = 1;
        }
    }

  // check is the player has reached the fuit
  if (xCor == xfCor && yCor == yfCor){
    // create the new location of the fruit
    randomize();
    // add to the score
    score1++;
      if (score1 > 9){
        score2++;
        score1 = 0;
      }
    }
  // delay to keep things visible
  delay(100);
}
