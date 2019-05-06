#define joysX 0
#define joysY 1

#define LEFT_P 1
#define CENTER_P 2
#define RIGHT_P 3

struct enemy
{
  int pos;
  int dst;
};

// 2-dimensional array of row pin numbers:
const int row[8] = {
  2, 7, 19, 5, 13, 18, 12, 16
};

// 2-dimensional array of column pin numbers:
const int col[8] = {
  6, 11, 10, 3, 17, 4, 8, 9
};

// 2-dimensional array of pixels:
int pixels[8][8];

int count = 1000;
int Cur_x = 4;
int Cur_y = 4;
int Position = 0;
int Anim = 8;
int Anim2 = 7;
int Anim3 = 4;
struct enemy Trucks[4];
bool Death = false;

unsigned long timing = 0; // Переменная для хранения точки отсчета
unsigned long timingTruck = 0; // Переменная для хранения точки отсчета



char str[] = "FABCDEDCBA";
int strLen = sizeof(str);
int ptrChar = 0;


typedef bool charMapType[8][8];

const charMapType charBlank = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const charMapType heart0 = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const charMapType heart1 = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const charMapType heart2 = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0}
};

const charMapType heart3 = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const charMapType heart4 = {
  {0, 1, 1, 0, 0, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1},
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

const charMapType *charMap[6] = {&heart0, &heart1, &heart2, &heart3, &heart4, &charBlank};

void setup() {
  // initialize the I/O pins as outputs
  // iterate over the pins:
  Serial.begin(9600);
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    // initialize the output pins:
    pinMode(col[thisPin], OUTPUT);
    pinMode(row[thisPin], OUTPUT);
    // take the col pins (i.e. the cathodes) high to ensure that
    // the LEDS are off:
    digitalWrite(col[thisPin], HIGH);
  }

   for(int i = 0; i < 4; i++)
   {
     Trucks[i].pos = random(1,7);
     Trucks[i].dst = -2 * i;
   }
  

  //setupScreen();
  setupChar();

}

void loop() {

  // draw the screen:
  if(Death == false)
  {
    refreshScreen();
    joystikUpdate();
  
    if(millis() - timing > 100){ // Вместо 10000 подставьте нужное вам значение паузы 
      timing = millis(); 
      Anim = (Anim + 1) % 8;
      Anim2 = (Anim2 + 1) % 8;
      Anim3 = (Anim3 + 1) % 8;
    }

    checkDeath();

    if(millis() - timingTruck > 500){ // Вместо 10000 подставьте нужное вам значение паузы 
      timingTruck = millis(); 
      enemyMove();
      truckRespawn();
    }
    
    pointCreate();
  }
  else
  {
    refreshScreen();
  
    if(count-- == 0){
      count = 1000;
      setupChar();
    }
  }
}

void checkDeath()
{
   for(int i = 0; i < 4; i++)
   {
     if(Trucks[i].dst == 7 && (Trucks[i].pos == 5 || Trucks[i].pos == 6) && Position == RIGHT_P)
        Death = true;
     if(Trucks[i].dst == 7 && (Trucks[i].pos == 1 || Trucks[i].pos == 2) && Position == LEFT_P)
        Death = true;
     if(Trucks[i].dst == 7 && (Trucks[i].pos == 4 || Trucks[i].pos == 3) && Position == CENTER_P)
        Death = true;
   }
}

void enemyMove()
{
  for(int i = 0; i < 4; i++)
  {
    Trucks[i].dst++;
  }
}

void truckRespawn()
{
  for(int i = 0; i < 4; i++)
  {
    if(Trucks[i].dst > 8)
    {
      Trucks[i].pos = random(1,7);
      Trucks[i].dst = -1;
    }
  }
  
}

void joystikUpdate()
{
  int xValuess = analogRead (joysX);
  int yValuef = analogRead (joysY);

  if(yValuef >= 700)
     Position = RIGHT_P;       // Cur_y = 5;// Cur_y = (Cur_y + 1) % 8;
  else if(yValuef <= 400)
     Position = LEFT_P;       //Cur_y = 3;// Cur_y = (Cur_y - 1) % 8;
  else 
  {
     Position = CENTER_P;        //Cur_x = 4; Cur_y = 4;
  }

  //for (int x = 0; x < 10000; x++);
}


void pointCreate(){
  char c = str[ptrChar];
  int offset = c - 'A';
  
  const charMapType *cMap = charMap[offset];
  //charMapType *cMap = &charDummy;
  
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      bool v = (*cMap)[x][y];

      pixels[x][y] = LOW;
      
      if(Position == CENTER_P){
        pixels[7][3] = HIGH;
        pixels[7][4] = HIGH;
      }else if(Position == LEFT_P){
        pixels[7][2] = HIGH;
        pixels[7][1] = HIGH;
      }else if(Position == RIGHT_P){
        pixels[7][5] = HIGH;
        pixels[7][6] = HIGH;
      }

      if((y == 0 || y == 7) && (x == Anim || x == Anim2 || x == Anim3))
        pixels[x][y] = HIGH;


      for(int i = 0; i < 4; i++)
      {
        if(Trucks[i].dst < 8 && Trucks[i].dst >= 0)
        {
          pixels[Trucks[i].dst][Trucks[i].pos] = HIGH;
        }
      }
        
    }
  }
    
  ptrChar++;
  if(ptrChar>=strLen-1){
    ptrChar = 0;
  }

}

void setupChar(){
  char c = str[ptrChar];
  int offset = c - 'A';
  
  const charMapType *cMap = charMap[offset];
  //charMapType *cMap = &charDummy;
  
  for (int x = 0; x < 8; x++) {
    for (int y = 0; y < 8; y++) {
      bool v = (*cMap)[x][y];
      
      if(v == true){
        pixels[x][y] = LOW;
      }else{
        pixels[x][y] = HIGH;
      }
    }
  }
  
  ptrChar++;
  if(ptrChar>=strLen-1){
    ptrChar = 0;
  }

}

void refreshScreen() {
                                                               // iterate over the rows (anodes):
  for (int thisRow = 0; thisRow < 8; thisRow++) {
                                                               // take the row pin (anode) high:
    digitalWrite(row[thisRow], HIGH);
                                                               // iterate over the cols (cathodes):
    for (int thisCol = 0; thisCol < 8; thisCol++) {
                                                                // get the state of the current pixel;
      int thisPixel = pixels[thisRow][thisCol];
                                                              // when the row is HIGH and the col is LOW,
                                                               // the LED where they meet turns on:
      digitalWrite(col[thisCol], thisPixel);
                                                              // turn the pixel off:
      if (thisPixel == LOW) {
        digitalWrite(col[thisCol], HIGH);
      }
    }
                                                              // take the row pin low to turn off the whole row:
    digitalWrite(row[thisRow], LOW);
  }
}
