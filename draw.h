#include <OctoWS2811.h>

// LED Matrix
#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   9
#define LAT 10
#define A   A0
#define B   A1
#define C   A2
#define D   A3

const int SQUARE_WIDTH = 3;
const int PIXEL_OFFSET_X = 1;
const int PIXEL_OFFSET_Y = 4;
const int SCORE_DIGITS = 8;

const int ledsPerStrip = 100;
DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);
//RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

/* const int CYAN   = matrix.Color333(0,4,7); // 1183 */
/* const int VIOLET = matrix.Color333(4,0,7); // -28641 */
/* const int RED    = matrix.Color333(7,0,0); // -2048 */
/* const int YELLOW = matrix.Color333(7,4,0); // -896 */
/* const int GREEN  = matrix.Color333(0,7,0); // 2016 */
/* const int ORANGE = matrix.Color333(7,2,0); // -1472 */
/* const int BLUE   = matrix.Color333(0,0,7); */
/* const int WHITE  = matrix.Color333(1, 1, 1); */
/* const int BLACK  = matrix.Color333(0, 0, 0); */
const int DEFAULT_GHOST_COLOR = 0x202020;
const int BLACK = 0x000000;
const int WHITE = 0x888888;
//uint32_t red = 0x800000;
const int RED = 0xF00000;
//uint32_t orange = 0x804000;
const int ORANGE = 0xFF8800;
//uint32_t yellow = 0x808000;
const int YELLOW = 0xFFFF00;
const int GREEN = 0x00FF00;
const int BLUE = 0x0000FF;
const int INDIGO= 0x240040;
const int VIOLET= 0xFF00FF;
//uint32_t violet= 0x750475;
const int CYAN= 0x00FFFF;
/* const int DIM = matrix.Color333(1, 1, 7); */
/* const int DIM = matrix.Color333(1, 1, 7); */
/* const int DIM_WHITE = matrix.Color333(2, 2, 2); */
const int DIM_WHITE = 0x404040;
/* const int DIM = matrix.Color333(1, 1, 7); */
/* const int BRIGHT = matrix.Color333(7, 1, 1); */
/* const int GHOST_BLUE = matrix.Color333(0, 0, 1); */
const int GHOST_BLUE = 0x000020;
/* const int GHOST_YELLOW = matrix.Color333(2, 1, 0); */
const int GHOST_YELLOW = 0x402000;
/* const int GHOST_RED = matrix.Color333(1, 0, 0); */
const int GHOST_RED = 0x200000;
/* const int GHOST_GREEN = matrix.Color333(0, 1, 0); */
const int GHOST_GREEN = 0x002000;
/* const int GOST_CYAN = matrix.Color333(0, 1, 2); */
const int GHOST_CYAN = 0x002040;
/* const int GHOST_VIOLET = matrix.Color333(1, 0, 2); */
const int GHOST_VIOLET = 0x200040;
/* const int GHOST_ORANGE = matrix.Color333(2, 1, 0); // TODO: Fix, currently same as yellow */
const int GHOST_ORANGE = 0x402000; // TODO: Fix, currently same as yellow
const int MATRIX_HEIGHT = 20;
const int MATRIX_WIDTH = 10;

/* int adjustYCoord(int yCoord, int multiplier) { */
/*   // We want y = 20 to appear at 60 on the led board, */
/*   // but we want y = 40 to appear at 0 on the led board, */
/*   // a linear function. */
/*   // f(BUFFER_HEIGHT) = 60 */
/*   // f(24) = 0 */
/*   int result = (MAIN_MATRIX_HEIGHT+BUFFER_ZONE_HEIGHT+BORDER_SIZE)*multiplier; // Start with the max height */
/*   result -= yCoord*multiplier; */
/*   return result - 3; */
/* } */

/* void fillRect(int yCoord, xCoord, multiplier, multiplier, color) { */
/*   matrix.setPixel(); */
/* } */

/* void drawSquareNew(int xCoord, int yCoord, int color, int multiplier, int xOffset = 0) { */
/* //  int adjustedYCoord = adjustYCoord(yCoord, multiplier) - multiplier + PIXEL_OFFSET_Y; // Subtract 3 since the origin is seen as lower left instead of top left */
/*   int adjustedYCoord = adjustYCoord(yCoord, multiplier) - SQUARE_WIDTH + PIXEL_OFFSET_Y; // Subtract 3 since the origin is seen as lower left instead of top left */
/* //  if (adjustedYCoord > MATRIX_HEIGHT) { */
/* //    // Nothing to draw if we're outside of the boord */
/* //    return; */
/* //  } */
/*   int adjustedXCoord = ((xCoord - 1) * multiplier) + PIXEL_OFFSET_X + xOffset; */
/*   matrix.fillRect(adjustedYCoord, adjustedXCoord, multiplier, multiplier, color); */
/* } */

/* void clearBottom() { */
/*   matrix.fillRect(0, 0, 2, MATRIX_HEIGHT, BLACK); */
/* } */

void showPixels() {
  leds.show();
}

void newDrawPixel(int xWithoutMultiplier, int yWithBuffer, int color) {
  int x = xWithoutMultiplier*2;
//  Serial.print('X: ');
  Serial.print(x);
  Serial.print(' ');
  int y = yWithBuffer - 4;
//  Serial.print('Y: ');
  Serial.println(y);
  // First row
  int rowOffset = 400;
  if (y == 0) {
    leds.setPixel(x+rowOffset, color);
    leds.setPixel(x+rowOffset+1, color);
  }

  rowOffset = 420;
  if (y == 1) {
    leds.setPixel(rowOffset+(20-x), color);
    leds.setPixel(rowOffset+(20-x)+1, color);
  }

  rowOffset = 500;
  if (y == 2) {
    leds.setPixel(x+rowOffset, color);
    leds.setPixel(x+rowOffset+1, color);
  }

  rowOffset = 520;
  if (y == 3) {
    leds.setPixel(rowOffset+(20-x), color);
    leds.setPixel(rowOffset+(20-x)+1, color);
  }

  rowOffset = 540;
  if (y == 4) {
    leds.setPixel(x+rowOffset, color);
    leds.setPixel(x+rowOffset+1, color);
  }

  rowOffset = 0;
  if (y == 5) {
    leds.setPixel(rowOffset+(20-x), color);
    leds.setPixel(rowOffset+(20-x)+1, color);
  }

  rowOffset = 20;
  if (y == 6) {
    leds.setPixel(x+rowOffset, color);
    leds.setPixel(x+rowOffset+1, color);
  }

  rowOffset = 40;
  if (y == 7) {
    leds.setPixel(rowOffset+(20-x), color);
    leds.setPixel(rowOffset+(20-x)+1, color);
  }

  rowOffset = 600;
  if (y == 8) {
    leds.setPixel(x+rowOffset, color);
    leds.setPixel(x+rowOffset+1, color);
  }

  rowOffset = 620;
  if (y == 9) {
    leds.setPixel(rowOffset+(20-x), color);
    leds.setPixel(rowOffset+(20-x)+1, color);
  }

  rowOffset = 640;
  if (y == 10) {
    leds.setPixel(x+rowOffset, color);
    leds.setPixel(x+rowOffset+1, color);
  }

  rowOffset = 100;
  if (y == 11) {
    leds.setPixel(rowOffset+(20-x), color);
    leds.setPixel(rowOffset+(20-x)+1, color);
  }

  rowOffset = 120;
  if (y == 12) {
    leds.setPixel(x+rowOffset, color);
    leds.setPixel(x+rowOffset+1, color);
  }

  rowOffset = 140;
  if (y == 13) {
    leds.setPixel(rowOffset+(20-x), color);
    leds.setPixel(rowOffset+(20-x)+1, color);
  }

  rowOffset = 700;
  if (y == 14) {
    leds.setPixel(x+rowOffset, color);
    leds.setPixel(x+rowOffset+1, color);
  }

  rowOffset = 720;
  if (y == 15) {
    leds.setPixel(rowOffset+(20-x), color);
    leds.setPixel(rowOffset+(20-x)+1, color);
  }

  rowOffset = 740;
  if (y == 16) {
    leds.setPixel(x+rowOffset, color);
    leds.setPixel(x+rowOffset+1, color);
  }

  rowOffset = 200;
  if (y == 17) {
    leds.setPixel(rowOffset+(20-x), color);
    leds.setPixel(rowOffset+(20-x)+1, color);
  }

  rowOffset = 220;
  if (y == 18) {
    leds.setPixel(x+rowOffset, color);
    leds.setPixel(x+rowOffset+1, color);
  }

  rowOffset = 240;
  if (y == 19) {
    Serial.println("HERE");
    Serial.println(rowOffset+(20-x));
    leds.setPixel(rowOffset+(20-x), color);
    leds.setPixel(rowOffset+(20-x)+1, color);
//    leds.setPixel(240, color);
//    leds.setPixel(241, color);
//    leds.show();
  }
}


void clearNextPieces() {
  /* matrix.fillRect(0, 9, 6, MATRIX_HEIGHT, matrix.Color333(0, 0, 0)); */
  for (int x = 700; x < 748; x++) {
    leds.setPixel(x, BLACK);
  }
}

void clearHeldPiece() {
  /* newFillRect(0, 0, 5, 3, matrix.Color333(0, 0, 0)); */
  /* matrix.fillRect(0, 0, 6, 8, matrix.Color333(0, 0, 0)); */
  for (int x = 40; x < 48; x++) {
    leds.setPixel(x, BLACK);
  }
}


void clearMatrix() {
  for (int x = 0; x < 10; x++) {
    for (int y = 0; y < 20; y++) {
      newDrawPixel(x, y, BLACK);
    }
  }
  clearNextPieces();
  clearHeldPiece();
}

int scoreRep[SCORE_DIGITS] = {0, 0, 0, 0, 0, 0, 0, 0};

void translateScoreIntoScoreRep(long long score) {
  for (int i = 0; i < SCORE_DIGITS; i++) {
    int currentDigitInd = SCORE_DIGITS - 1 - i;
    int divideBy = pow(10, i);
    score /= divideBy;
    scoreRep[i] = score % 10;
//    long long currentDigitValue = score % divideBy;
  }
}

/* void newFillRect(int startX, int startY, int endX, int endY, int color) { */
/*     matrix.fillRect(startY, startX, endY, endX, color); */
/* } */
/* void newFillRect(int startX, int startY, int width, int height, int color) { */
/*     matrix.fillRect(startY, startX, height, width, color); */
/* } */

/* void newDrawLine(int startX, int startY, int endX, int endY, int color) { */
/*     matrix.drawLine(startY, startX, endY, endX, color); */
/* } */



/* void drawDigit(int digit, int startingX, int startingY, int color) { */
/*   // Font from here: https://fontstruct.com/fontstructions/show/1422505/5x4-pxl */
/*   // Starting X is from the left and starting Y is from the bottom */
/*   switch (digit) { */
/*     case 0: */
/*       //0000 */
/*       //00 0 */
/*       //00 0 */
/*       //00 0 */
/*       //0000 */

/*       matrix.drawLine(startingY, startingX, startingY, startingX+3, color); */
/*       matrix.drawLine(startingY+4, startingX, startingY+4, startingX+3, color); */

/*       matrix.drawLine(startingY+1, startingX, startingY+3, startingX, color); */
/*       matrix.drawLine(startingY+1, startingX+1, startingY+3, startingX+1, color); */
/*       matrix.drawLine(startingY+1, startingX+3, startingY+3, startingX+3, color); */

/*       break; */
/*     case 1: */
/*       // 111 */
/*       //1111 */
/*       // 111 */
/*       // 111 */
/*       // 111 */
/*       // 111 */

/*       newDrawPixel(startingX, startingY+3, color); */
/*       newFillRect(startingX + 1, startingY, 3, 5, color); */

/*       break; */
/*     case 2: */
/*       //2222 */
/*       //  22 */
/*       //2222 */
/*       //22 */
/*       //2222 */

/*       newDrawLine(startingX, startingY, startingX+3, startingY, color); */
/*       newDrawLine(startingX, startingY+1, startingX+1, startingY+1, color); */
/*       newDrawLine(startingX, startingY+2, startingX+3, startingY+2, color); */
/*       newDrawLine(startingX+2, startingY+3, startingX+3, startingY+3, color); */
/*       newDrawLine(startingX, startingY+4, startingX+3, startingY+4, color); */

/*       break; */
/*     case 3: */
/*       //3333 */
/*       //  33 */
/*       // 333 */
/*       //  33 */
/*       //3333 */

/*       newDrawLine(startingX, startingY, startingX+3, startingY, color); */
/*       newDrawLine(startingX, startingY+4, startingX+3, startingY+4, color); */
/*       newFillRect(startingX+2, startingY+1, 2, 3, color); */
/*       newDrawPixel(startingX+1, startingY+2, color); */
/*       break; */
/*     case 4: */
/*       //4 44 */
/*       //4 44 */
/*       //4444 */
/*       //  44 */
/*       //  44 */

/*       newFillRect(startingX+2, startingY, 2, 5, color); */
/*       newDrawLine(startingX, startingY+2, startingX, startingY+4, color); */
/*       newDrawPixel(startingX+1, startingY+2, color); */
/*       break; */
/*     case 5: */
/*       //5555 */
/*       //55 */
/*       //5555 */
/*       //  55 */
/*       //5555 */

/*       newFillRect(startingX, startingY+2, 2, 3, color); */
/*       newFillRect(startingX+2, startingY, 2, 3, color); */
/*       newDrawLine(startingX, startingY, startingX+1, startingY, color); */
/*       newDrawLine(startingX+2, startingY+4, startingX+3, startingY+4, color); */
/*       break; */
/*     case 6: */
/*       //6666 */
/*       //66 */
/*       //6666 */
/*       //66 6 */
/*       //6666 */

/*       newFillRect(startingX, startingY, 2, 5, color); */
/*       newDrawLine(startingX+2, startingY, startingX+3, startingY, color); */
/*       newDrawLine(startingX+2, startingY+2, startingX+3, startingY+2, color); */
/*       newDrawLine(startingX+2, startingY+4, startingX+3, startingY+4, color); */
/*       newDrawPixel(startingX+3, startingY+1, color); */
/*       break; */
/*     case 7: */
/*       //7777 */
/*       //  77 */
/*       //  77 */
/*       //  77 */
/*       //  77 */

/*       newFillRect(startingX+2, startingY, 2, 5, color); */
/*       newDrawLine(startingX, startingY+4, startingX+3, startingY+4, color); */
/*       break; */
/*     case 8: */
/*       //8888 */
/*       //88 8 */
/*       //8888 */
/*       //88 8 */
/*       //8888 */

/*       newFillRect(startingX, startingY, 2, 5, color); */
/*       newDrawLine(startingX+2, startingY, startingX+3, startingY, color); */
/*       newDrawPixel(startingX+3, startingY+1, color); */
/*       newDrawLine(startingX+2, startingY+2, startingX+3, startingY+2, color); */
/*       newDrawPixel(startingX+3, startingY+3, color); */
/*       newDrawLine(startingX+2, startingY+4, startingX+3, startingY+4, color); */
/*       break; */
/*     case 9: */
/*       //9999 */
/*       //9 99 */
/*       //9999 */
/*       //  99 */
/*       //9999 */

/*       newFillRect(startingX+2, startingY, 2, 5, color); */
/*       newDrawLine(startingX, startingY, startingX+1, startingY, color); */
/*       newDrawLine(startingX, startingY+2, startingX+1, startingY+2, color); */
/*       newDrawPixel(startingX, startingY+3, color); */
/*       newDrawLine(startingX, startingY+4, startingX+1, startingY+4, color); */
/*       break; */
/*   } */
/* } */

/* const int LETTER_WIDTH = 4; */

/* void drawLetter(char letter, int startingX, int startingY, int color) { */
/*   switch (letter) { */
/*     case 'A': */
/*       //AAAA */
/*       //A  A */
/*       //AAAA */
/*       //A  A */
/*       //A  A */

/*       newDrawLine(startingX, startingY, startingX, startingY+4, color); */
/*       newDrawLine(startingX+3, startingY, startingX+3, startingY+4, color); */
/*       newDrawLine(startingX+1, startingY+2, startingX+2, startingY+2, color); */
/*       newDrawLine(startingX+1, startingY+4, startingX+2, startingY+4, color); */
/*       break; */
/*     case 'C': */
/*       //CCCC */
/*       //C */
/*       //C */
/*       //C */
/*       //CCCC */

/*       newDrawLine(startingX, startingY, startingX+3, startingY, color); */
/*       newDrawLine(startingX, startingY+1, startingX, startingY+3, color); */
/*       newDrawLine(startingX, startingY+4, startingX+3, startingY+4, color); */
/*       break; */
/*     case 'E': */
/*       //EEEE */
/*       //E */
/*       //EEEE */
/*       //E */
/*       //EEEE */

/*       newDrawLine(startingX, startingY, startingX+3, startingY, color); */
/*       newDrawLine(startingX, startingY+2, startingX+3, startingY+2, color); */
/*       newDrawLine(startingX, startingY+4, startingX+3, startingY+4, color); */
/*       newDrawPixel(startingX, startingY+1, color); */
/*       newDrawPixel(startingX, startingY+3, color); */
/*       break; */
/*     case 'G': */
/*       //GGGG */
/*       //G */
/*       //G GG */
/*       //G  G */
/*       //GGGG */

/*       newDrawLine(startingX, startingY, startingX+3, startingY, color); */
/*       newDrawLine(startingX, startingY+1, startingX, startingY+3, color); */
/*       newDrawLine(startingX+3, startingY+1, startingX+3, startingY+2, color); */
/*       newDrawPixel(startingX+2, startingY+2, color); */
/*       newDrawLine(startingX, startingY+4, startingX+3, startingY+4, color); */
/*       break; */
/*     case 'H': */
/*       //H  H */
/*       //H  H */
/*       //HHHH */
/*       //H  H */
/*       //H  H */

/*       newDrawLine(startingX, startingY, startingX, startingY+4, color); */
/*       newDrawLine(startingX+3, startingY, startingX+3, startingY+4, color); */
/*       newDrawLine(startingX+1, startingY+2, startingX+2, startingY+2, color); */
/*       break; */
/*     case 'I': */
/*       //IIII */
/*       // II */ 
/*       // II */ 
/*       // II */ 
/*       //IIII */

/*       newDrawLine(startingX, startingY, startingX+3, startingY, color); */
/*       newDrawLine(startingX, startingY+4, startingX+3, startingY+4, color); */
/*       newFillRect(startingX+1, startingY+1, 2, 3, color); */
/*       break; */
/*     case 'M': */
/*       //MMMM */
/*       //MMMM */
/*       //M  M */
/*       //M  M */
/*       //M  M */

/*       newFillRect(startingX, startingY+3, 4, 2, color); */
/*       newDrawLine(startingX, startingY, startingX, startingY+2, color); */
/*       newDrawLine(startingX+3, startingY, startingX+3, startingY+2, color); */
/*       break; */
/*     case 'O': */
/*       //OOOO */
/*       //O  O */
/*       //O  O */
/*       //O  O */
/*       //OOOO */

/*       newDrawLine(startingX, startingY, startingX+3, startingY, color); */
/*       newDrawLine(startingX, startingY+4, startingX+3, startingY+4, color); */
/*       newDrawLine(startingX, startingY+1, startingX, startingY+3, color); */
/*       newDrawLine(startingX+3, startingY+1, startingX+3, startingY+3, color); */
/*       break; */
/*     case 'R': */
/*       //RRR */
/*       //R  R */
/*       //RRR */
/*       //R  R */
/*       //R  R */

/*       newDrawLine(startingX, startingY, startingX, startingY+4, color); */
/*       newDrawLine(startingX+1, startingY+2, startingX+2, startingY+2, color); */
/*       newDrawLine(startingX+1, startingY+4, startingX+2, startingY+4, color); */
/*       newDrawLine(startingX+3, startingY, startingX+3, startingY+1, color); */
/*       newDrawPixel(startingX+3, startingY+3, color); */
/*       break; */
/*     case 'S': */
/*       //SSSS */
/*       //S */
/*       //SSSS */
/*       //   S */
/*       //SSSS */

/*       newDrawLine(startingX, startingY, startingX+3, startingY, color); */
/*       newDrawLine(startingX, startingY+2, startingX+3, startingY+2, color); */
/*       newDrawLine(startingX, startingY+4, startingX+3, startingY+4, color); */
/*       newDrawPixel(startingX+3, startingY+1, color); */
/*       newDrawPixel(startingX, startingY+3, color); */
/*       break; */
/*     case 'V': */
/*       //V  V */
/*       //V  V */
/*       //V  V */
/*       //V V */
/*       // V */

/*       newDrawLine(startingX, startingY+1, startingX, startingY+4, color); */
/*       newDrawPixel(startingX+1, startingY, color); */
/*       newDrawPixel(startingX+2, startingY+1, color); */
/*       newDrawLine(startingX+3, startingY+2, startingX+3, startingY+4, color); */
/*       break; */
/*   } */
/* } */

/* void drawGameOver(int y) { */
/*   drawLetter('G', 0,              y, CYAN); */
/*   drawLetter('A', LETTER_WIDTH,   y, VIOLET); */
/*   drawLetter('M', LETTER_WIDTH*2, y, RED); */
/*   drawLetter('E', LETTER_WIDTH*3, y, YELLOW); */
/*   drawLetter('O', LETTER_WIDTH*4, y, GREEN); */
/*   drawLetter('V', LETTER_WIDTH*5, y, ORANGE); */
/*   drawLetter('E', LETTER_WIDTH*6, y, BLUE); */
/*   drawLetter('R', LETTER_WIDTH*7, y, CYAN); */
/* } */

/* void drawScore(int y) { */
/*   drawLetter('S', 0, y, matrix.Color333(5, 5, 5)); */
/*   drawLetter('C', LETTER_WIDTH + 1, y, matrix.Color333(5, 5, 5)); */
/*   drawLetter('O', LETTER_WIDTH*2 + 2, y, matrix.Color333(5, 5, 5)); */
/*   drawLetter('R', LETTER_WIDTH*3 + 3, y, matrix.Color333(5, 5, 5)); */
/*   drawLetter('E', LETTER_WIDTH*4 + 4, y, matrix.Color333(5, 5, 5)); */
/* } */

/* void drawHigh(int y) { */
/*   drawLetter('H', 0, y, matrix.Color333(5, 5, 5)); */
/*   drawLetter('I', LETTER_WIDTH + 1, y, matrix.Color333(5, 5, 5)); */
/*   drawLetter('G', LETTER_WIDTH*2 + 2, y, matrix.Color333(5, 5, 5)); */
/*   drawLetter('H', LETTER_WIDTH*3 + 3, y, matrix.Color333(5, 5, 5)); */
/* } */

/* void drawNumber(long long* originalNum, int y) { */
/*   long long num = *originalNum; */
/*   int startX = MATRIX_HEIGHT - 4; */
/*   int color = BRIGHT; */
/*   int numToDraw; */

/*   while (startX >= 0) { */
/*     numToDraw = num % 10; */
/*     color = color == DIM ? BRIGHT : DIM; */
/*     drawDigit(numToDraw, startX, y, color); */
/*     num /= 10; */
/*     startX -= 4; */
/*   } */
/* } */
