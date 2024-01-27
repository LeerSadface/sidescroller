
#include <U8g2lib.h>
#include <Wire.h>


U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);


#define SPEAKER_PIN 8


int i = 0;
int x0 = 2;
int x1 = 2;
int x2 = 20;
int y1, y2, y0;
int xb = 128;
int yb, wb, hb;
int yb2, wb2, hb2;
int xb2 = 128;

int potPin = A0;

int level = 1;
int tempo = 2;
int mov = 2;
int score;
bool box1, box2, box3, box4, box5;

int status;

bool melody = false;

bool melWeird = false;

int hoch, runter;


void setup() {
  // put your setup code here, to run once:
  u8g2.begin();
  Serial.begin(9600);

  randomSeed(analogRead(1));

  pinMode(12, INPUT);
  pinMode(11, INPUT);

  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  tri_pos2();
  status = 0;
}

void clear_screen() {
  u8g2.clearBuffer();  // Löscht den Bildschirminhalt
  u8g2.sendBuffer();   // Sendet die gelöschten Daten an das Display
}
void play_tone() {
  tone(8, 300, 200);  // Pin 8, Frequenz 1000 Hz, Dauer 100 ms
  delay(100);
  tone(8, 200, 300);  // Pin 8, Frequenz 1000 Hz, Dauer 100 ms
  delay(100);
  tone(8, 100, 600);  // Pin 8, Frequenz 1000 Hz, Dauer 100 ms
  delay(100);
}

void playWeird() {
  tone(8, 400, 50);
  delay(60);
  tone(8, 300, 50);
  delay(60);
  tone(8, 500, 50);
  delay(60);
  noTone(8);
  melWeird = true;
}

void playIdleMelody() {
  tone(8, 262, 200);   // Note: C4, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 330, 200);   // Note: E4, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 392, 200);   // Note: G4, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 523, 200);   // Note: C5, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 659, 200);   // Note: E5, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 784, 200);   // Note: G5, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 988, 200);   // Note: B5, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 1047, 200);  // Note: C6, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 988, 200);   // Note: B5, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 784, 200);   // Note: G5, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 659, 200);   // Note: E5, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 523, 200);   // Note: C5, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 392, 200);   // Note: G4, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 330, 200);   // Note: E4, Dauer 400 ms
  delay(100);          // Pause 500 ms
  tone(8, 262, 200);   // Note: C4, Dauer 400 ms
  delay(100);
  melody = true;
}

void play_tone_score() {
  tone(8, 500, 50);  // Pin 8, Frequenz 1000 Hz, Dauer 100 ms
  delay(100);
}

bool tri_pos1() {
  y0 = 0;
  y1 = 20;
  y2 = 10;
  u8g2.drawTriangle(x0, y0, x1, y1, x2, y2);
  u8g2.setFont(u8g2_font_chroma48medium8_8r);
  u8g2.setCursor(x1 + 1, y1 - 6);
  u8g2.print(level);
}
bool tri_pos2() {
  y0 = 22;
  y1 = 42;
  y2 = 31;
  u8g2.drawTriangle(x0, y0, x1, y1, x2, y2);
  u8g2.setFont(u8g2_font_chroma48medium8_8r);
  u8g2.setCursor(x1 + 1, y1 - 6);
  u8g2.print(level);
}

bool tri_pos3() {
  y0 = 44;
  y1 = 64;
  y2 = 54;
  u8g2.drawTriangle(x0, y0, x1, y1, x2, y2);
  u8g2.setFont(u8g2_font_chroma48medium8_8r);
  u8g2.setCursor(x1 + 1, y1 - 6);
  u8g2.print(level);
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


void run_game() {

  melody = true;

  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);



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

  if (i <= 2) {

    box_1();

  } else if (i <= 4 && i > 2) {

    box_2();

  } else if (i <= 7 && i > 4) {
    box_3();

  } else if (i < 9 && i > 7) {
    box_4();
  }


  if (xb <= -15) {

    score = score + 1;

    xb = 128;
    play_tone_score();

    i = random(0, 9);
  }

  if (score <= 3) {
    tempo = 3;
    level = 1;
    melWeird = false;
  }
  if (score <= 6 && score >= 3) {
    tempo = 3.6;
    level = 2;
  }
  if (score <= 9 && score >= 6) {
    tempo = 4;
    level = 3;
  }
  if (score <= 12 && score >= 9) {
    tempo = 4.5;
    level = 4;
  }
  if (score <= 15 && score >= 12) {
    tempo = 5;
    level = 5;
  }
  if (score <= 18 && score >= 15) {
    tempo = 6;
    level = 6;
  }
  if (score <= 21 && score >= 18) {
    tempo = 6.5;
    level = 7;
  }
  if (score <= 24 && score >= 21) {
    tempo = 7;
    level = 8;
  }
  if (score <= 27 && score >= 24) {
    tempo = 8;
    level = 9;
  }
  if (score <= 30 && score >= 27) {
    tempo = 8.5;
    level = 10;
  }
  if (score <= 33 && score >= 30) {
    tempo = 9;
    level = 11;
  }
  if (score <= 36 && score >= 33) {
    tempo = 9.5;
    level = 12;
  }

  if (level == 3) {
    if (melWeird == false) {
      playWeird();
    }
    u8g2.setDisplayRotation(U8G2_R2);
    
  }

  if (level == 4) {
    melWeird = false;
  }

  if (level == 6) {

    if (melWeird == false) {
      playWeird();
    }
    u8g2.setDisplayRotation(U8G2_R0);
  }

  if (level == 7) {
    melWeird = false;
  }



  xb = xb - tempo;
  xb2 = xb2 - tempo;

  if (xb <= 20 && xb >= 8 && yb == 0 && (box1 == true || box3 == true) && (mov == 1 || mov == 2)) {  // Box 1
    play_tone();
    status = 3;
    clear_screen();

  } else if (xb <= 20 && xb >= 8 && yb == 22 && (box2 == true || box4 == true) && (mov == 2 || mov == 3)) {  // Box 2
    play_tone();
    status = 3;
    clear_screen();



  } else if (xb2 <= 20 && xb2 >= 8 && yb2 == 22 && box3 == true && (mov == 2)) {  // Box 3

    if (xb2 <= 20 && xb2 >= 8 && yb2 <= 42 && box3 == true && mov == 2) {

      play_tone();
      status = 3;
      clear_screen();
    }


    play_tone();
    status = 3;
    clear_screen();

  } else if (xb2 <= 20 && xb2 >= 8 && yb2 == 22 && box4 == true && (mov == 2)) {  // Box 4

    if (xb2 <= 20 && xb >= 8 && yb2 <= 42 && box4 == true && (mov == 2)) {

      play_tone();
      status = 3;
    }
    play_tone();
    status = 3;
    clear_screen();
  }

  else if (xb2 <= 20 && xb2 >= 8 && yb2 == 22 && box3 && mov == 2) {  // Kollision mit Box 3
    if (xb2 <= 20 && xb2 >= 8 && yb2 <= 42) {                         // Kollision mit dem oberen Bereich von Box 3
      play_tone();
      status = 3;
      clear_screen();
    }
  }
}


void startscreen() {

  u8g2.setFont(u8g2_font_chroma48medium8_8r);
  u8g2.setCursor(0, 32);
  u8g2.print("Start Game?");

  score = 0;
  xb = 128;

  if (melody == false) {
    playIdleMelody();
  }

  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  int potValue = analogRead(potPin);

  int brightness = map(potValue, 0, 1023, 0, 255);

  u8g2.setContrast(brightness);

  if (hoch != 1 || runter != 1) {

    status = 1;
  }
}

void gameover() {

  u8g2.setDisplayRotation(U8G2_R0);

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
