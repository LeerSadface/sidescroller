#include <U8g2lib.h>
#include <Wire.h>


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

int i = 0;
int x0 = 2;
int x1 = 2;
int x2 = 20;
int y1, y2, y0;
int xb = 128;
int yb, wb, hb;
int yb2, wb2, hb2;
int xb2 = 128;

int tempo = 2;
int mov = 2;
int score;
bool box1, box2, box3, box4, box5;

int status;

static int successfullDodges = 0;
int hoch, runter;


void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  Serial.begin(9600);

  pinMode(12, INPUT);
  pinMode(11, INPUT);

  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  tri_pos2();
  status = 0;
}

bool tri_pos1() {
  y0 = 0;
  y1 = 20;
  y2 = 10;
  u8g2.drawTriangle(x0, y0, x1, y1, x2, y2);
  u8g2.setFont(u8g2_font_chroma48medium8_8r);
  u8g2.setCursor(x1 + 1, y1 - 6);
  u8g2.print(score);
}
bool tri_pos2() {
  y0 = 22;
  y1 = 42;
  y2 = 31;
  u8g2.drawTriangle(x0, y0, x1, y1, x2, y2);
  u8g2.setFont(u8g2_font_chroma48medium8_8r);
  u8g2.setCursor(x1 + 1, y1 - 6);
  u8g2.print(score);
}

bool tri_pos3() {
  y0 = 44;
  y1 = 64;
  y2 = 54;
  u8g2.drawTriangle(x0, y0, x1, y1, x2, y2);
  u8g2.setFont(u8g2_font_chroma48medium8_8r);
  u8g2.setCursor(x1 + 1, y1 - 6);
  u8g2.print(score);
}


bool box_1() {

  yb = 0;
  wb = 10;
  hb = 42;


  u8g2.drawBox(xb, yb, wb, hb);
  box1 = true;
  box2 = false;
  box3 = false;
  box4 = false;
}

bool box_2() {

  yb = 22;
  wb = 10;
  hb = 42;

  u8g2.drawBox(xb, yb, wb, hb);
  box1 = false;
  box2 = true;
  box3 = false;
  box4 = false;
}

bool box_3() {

  yb = 0;
  wb = 10;
  hb = 42;

  xb2 = xb - wb2;
  yb2 = 22;
  wb2 = 25;
  hb2 = 20;

  u8g2.drawBox(xb, yb, wb, hb);
  u8g2.drawBox(xb2, yb2, wb2, hb2);
  box1 = false;
  box2 = false;
  box3 = true;
  box4 = false;
}

bool box_4() {

  yb = 22;
  wb = 10;
  hb = 42;

  xb2 = xb - wb2;
  yb2 = 22;
  wb2 = 25;
  hb2 = 20;

  u8g2.drawBox(xb, yb, wb, hb);
  u8g2.drawBox(xb2, yb2, wb2, hb2);
  box1 = false;
  box2 = false;
  box3 = false;
  box4 = true;
}

bool box_5() {

  yb = 22;
  wb = 60;
  hb = 20;

  u8g2.drawBox(xb, yb, wb, hb);
}
void increaseSpeed() {
  

  if (successfullDodges >= 3 && tempo < 8) {
    tempo += 2;  // Increase speed by 2 until tempo reaches 8
    successfullDodges = 0;  // Reset the counter
  }
}


void run_game() {

  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);

 increaseSpeed();

  if (hoch == 1 && runter == 1) {
    tri_pos2();
    mov = 2;
  }
  if (hoch == 0 && runter == 0) {
    tri_pos2();
    mov = 2;
  } else if (hoch == 0) {
    tri_pos1();
    mov = 1;
  } else if (runter == 0) {
    tri_pos3();
    mov = 3;
  }

  if (i <= 5) {

    box_1();

  } else if (i <= 10 && i > 5) {

    box_2();

  } else if (i <= 15 && i > 10) {
    box_3();

  } else if (i <= 20 && i > 15) {
    box_4();
  }


  if (xb == -10) {

    score = score + 1;

    successfullDodges++;
    xb = 128;

    
    i = random(0, 20);
  }
  
  xb = xb - tempo;


  if (xb <= 20 && xb >= 8 && yb == 0 && (box1 == true || box3 == true) && (mov == 1 || mov == 2)) {  // Box 1

    status = 3;
    Serial.println("Dead Box 1");
  } else if (xb <= 20 && xb >= 8 && yb == 22 && (box2 == true || box4 == true) && (mov == 2 || mov == 3)) {  // Box 2

    status = 3;
    Serial.println("Dead Box 2");

  } else if (xb2 <= 20 && xb2 >= 8 && yb2 == 22 && box3 == true && (mov == 2)) {  // Box 3

    if (xb2 <= 20 && xb2 >= 8 && yb2 <= 42 && box3 == true && mov == 2) {
      Serial.println("Dead Box 3");
      status = 3;
    }

    Serial.println("Dead Box 3");
    status = 3;

  } else if (xb2 <= 20 && xb2 >= 8 && yb2 == 22 && box4 == true && (mov == 2)) {  // Box 4
    Serial.println("Dead Box 4");
    if (xb2 <= 20 && xb >= 8 && yb2 <= 42 && box4 == true && (mov == 2)) {
      Serial.println("Dead Box 4");
      status = 3;
    }

    status = 3;
  }
}


void startscreen() {

  u8g2.setFont(u8g2_font_chroma48medium8_8r);
  u8g2.setCursor(0, 32);
  u8g2.print("Start Game?");

  score = 0;
  xb = 128;

  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);


  if (hoch != 1 || runter != 1) {

    status = 1;
  }
}

void gameover() {

  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);

  u8g2.setFont(u8g2_font_10x20_tf);
  u8g2.setCursor(10, 32);
  u8g2.print("GAME OVER!\n");

  u8g2.setFont(u8g2_font_10x20_tf);
  u8g2.setCursor(10, 50);
  u8g2.print("Score= ");

  u8g2.setCursor(80, 50);
  u8g2.print(score);

  if (hoch != 1 || runter != 1) {
    delay(2000);
    status = 0;
  }
}


void loop() {
  // put your main code here, to run repeatedly:


  u8g2.firstPage();
  do {

    hoch = digitalRead(12);
    runter = digitalRead(11);

    if (status == 0) {

      startscreen();
    }
    if (status == 1) {


      run_game();
    }


    if (status == 3) {
      gameover();
    }
  }


  while (u8g2.nextPage());
}
