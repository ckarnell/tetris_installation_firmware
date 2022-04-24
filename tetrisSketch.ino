#include "engine.h"
#include "draw.h"

// Random seed
#define seed A9

/* // Buttons */
int upValue = 0;
int rightValue = 0;
int downValue = 0;
int leftValue = 0;
int counterClockwiseValue = 0;
int flipValue = 0;
int counterClockwiseButtonValue = 0;
int clockwiseButtonValue = 0;
int xValue = 0;
int circleValue = 0;
int triangleValue = 0;
int squareValue = 0;
int l1Value = 0;
int l2Value = 0;
int r1Value = 0;
int r2Value = 0;
int clockwiseValue = 0;
int holdValue = 0;
int startValue = 0;
int selectValue = 0;

TetrisEngine tetrisEngine = TetrisEngine();

const int colorMap[10] = {0, 1, VIOLET, GREEN, RED, CYAN, ORANGE, BLUE, YELLOW, WHITE};

bool gameOver = false;
bool gameOverDrawn = false;

void setup() {
  leds.begin();
  Serial.begin(9875);
  randomSeed(analogRead(seed));
}

bool firstIteration = true;
unsigned long gameOverAt;
long timeBeforeSleep = 60000;

int ghostInds[4][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};


struct Controls controls;
int newGamePushed = false;
int newGameReleased = false;

int ghostSettingsPushed = false;
int ghostSettingsReleased = false;

long long highScore = 0;
/* bool shouldDrawGhost = true; */
bool shouldDrawPiece = true;

void drawGhost() {
  // Undraw the last ghost
  /* if (!shouldDrawGhost) { */
  /*   return; */
  /* } */

  if (tetrisEngine.rowsRemovedThisIteration != 0) {
    for (int i = 0; i < 4; i++) {
      newDrawPixel(ghostInds[i][0], ghostInds[i][1], BLACK);
      ghostInds[i][0] = -1;
      ghostInds[i][1] = -1;
    }
    return;
  }

  int ghostColor = DEFAULT_GHOST_COLOR;
  switch (tetrisEngine.currentPiece -> symbol) {
    case 'J':
      ghostColor = GHOST_BLUE;
      break;
    case 'O':
      ghostColor = GHOST_YELLOW;
      break;
    case 'Z':
      ghostColor = GHOST_RED;
      break;
    case 'S':
      ghostColor = GHOST_GREEN;
      break;
    case 'I':
      ghostColor = GHOST_CYAN;
      break;
    case 'T':
      ghostColor = GHOST_VIOLET;
      break;
    case 'L':
      ghostColor = GHOST_ORANGE;
      break;
  }

  int newGhostInds[4][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};

  // Draw the ghost
  int currentGhostInd = 0;
  int currentGhostY = tetrisEngine.getYModifierAfterHardDrop() + tetrisEngine.currentY;
  for (int y = 0; y < tetrisEngine.currentPiece -> dimension; y++) {
    for (int x = 0; x < tetrisEngine.currentPiece -> dimension; x++) {
      int minoRepresentation = tetrisEngine.currentPiece -> orientations[tetrisEngine.orientation][y][x];
      if (minoRepresentation == 1) {
        if (tetrisEngine.matrixRepresentation[(currentGhostY + y)*tetrisEngine.fieldWidth + (x + tetrisEngine.currentX)] == 0) {
          newDrawPixel(x + tetrisEngine.currentX, currentGhostY + y, ghostColor);
          newGhostInds[currentGhostInd][0] = x + tetrisEngine.currentX;
          newGhostInds[currentGhostInd][1] = currentGhostY + y;
        } else {
          newGhostInds[currentGhostInd][0] = -1;
          newGhostInds[currentGhostInd][1] = -1;
        }
        currentGhostInd++;
      }
    }
  }

  for (int i = 0; i < 4; i++) {
    bool shouldDelete = true;
    for (int j = 0; j < 4; j++) {
      if (ghostInds[i][0] == newGhostInds[j][0] && ghostInds[i][1] == newGhostInds[j][1]) {
        shouldDelete = false;
      }
    }

    if (ghostInds[i][0] != -1 && shouldDelete) {
       if (tetrisEngine.matrixRepresentation[ghostInds[i][1]*tetrisEngine.fieldWidth + ghostInds[i][0]] == 0) {
         newDrawPixel(ghostInds[i][0], ghostInds[i][1], BLACK);
       }
       ghostInds[i][0] = -1;
       ghostInds[i][1] = -1;
    }
  }


  // Copy over
  for (int i = 0; i < 4; i++) {
    ghostInds[i][0] = newGhostInds[i][0];
    ghostInds[i][1] = newGhostInds[i][1];
  }
}



void printNextPiece(int position) {
  int pixelOffset = 300;
  int cellOffsetMultiplier = 8*2;
  
}

// Print next pieces
void printNextPieces() {
  // TODO: Reimplement this
  drawGhost();
  clearNextPieces();
  for (int i = 0; i < 6; i++) {
    Tetromino* nextPiece = tetrisEngine.bag.getFuturePiece(i + 1);

    for (int y = 0; y < nextPiece -> dimension; y++) {
      for (int x = 0; x < nextPiece -> dimension; x++) {
        if (nextPiece -> orientations[0][y][x] == 1) {
//          int adjustedX = x + MATRIX_HEIGHT - 5 - 5*i;
//          newDrawPixel(adjustedX, 1-y, colorMap[nextPiece -> symbolNum]);
            if (y==0) {
              leds.setPixel(300+(i*16)+(x*2), colorMap[nextPiece -> symbolNum]);
              leds.setPixel(300+(i*16)+(x*2)+1, colorMap[nextPiece -> symbolNum]);
            } else {
              leds.setPixel(300+(i*16)+8+(8-(x*2)-2), colorMap[nextPiece -> symbolNum]);
              leds.setPixel(300+(i*16)+8+(8-(x*2)-2)+1, colorMap[nextPiece -> symbolNum]);
            }
        }
      }
    }
  }
}

void printWholeBoard() {
  for(int y = BUFFER_ZONE_HEIGHT; y < tetrisEngine.fieldHeight; y++) {
    for(int x = 0; x < tetrisEngine.fieldWidth; x++) {
      int currentNum = tetrisEngine.matrixRepresentation[y*tetrisEngine.fieldWidth + x];


      int currentColorInd = currentNum;
      if (currentNum == CURRENT_PIECE_CHAR) {
        if (shouldDrawPiece || tetrisEngine.gameController.dropPressed || tetrisEngine.firstPiece) {
          currentColorInd = tetrisEngine.currentPiece -> symbolNum;
        } else {
          // Draw black if we don't want to draw the current piece
          currentColorInd = 0;
        }
      }
      /* int currentColorInd = currentNum == CURRENT_PIECE_CHAR ? tetrisEngine.currentPiece -> symbolNum : currentNum; */
      int currentColor = colorMap[currentColorInd];
      
      if (currentColor != 1) { // Don't draw borders
        newDrawPixel(x, y, currentColor);
      }// else {
  //        }
    }
  }
//  leds.show(); //TODO: Needed??
}

void loop() {
  // TODO: Reimplement controls
  /* int upValue = digitalRead(upButton); */
  /* int leftValue = digitalRead(leftButton); */
  /* int rightValue = digitalRead(rightButton); */
  /* int downValue = digitalRead(downButton); */
  /* int holdValue = digitalRead(holdButton); */
  /* int flipValue = digitalRead(flipButton); */
  /* int startValue = digitalRead(startButton); */
  /* int selectValue = digitalRead(selectButton); */

  // Documented here for order
  /* 'options': '0', */
  /* 'd-up': '1', */
  /* 'd-right': '2', */
  /* 'd-down': '3', */
  /* 'd-left': '4', */
  /* 'x': '5', */
  /* 'square': '6', */
  /* 'circle': '7', */
  /* 'triangle': '8', */
  /* 'L1': '9', */
  /* 'L2': '10', */
  /* 'L3': '11', */
  /* 'R1': '12', */
  /* 'R2': '13', */
  /* 'R3': '14', */
  /* 'ps_button': '15', */
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    startValue = data[0] - '0';
    upValue = data[1] - '0';
    rightValue = data[2] - '0';
    downValue = data[3] - '0';
    leftValue = data[4] - '0';
    xValue = data[5] - '0';
    squareValue = data[6] - '0';
    circleValue = data[7] - '0';
    triangleValue = data[8] - '0';
    l1Value = data[9] - '0';
    l2Value = data[10] - '0';
    r1Value = data[11] - '0';
    r2Value = data[12] - '0';
    selectValue = data[15] - '0';

    // Derived values
    clockwiseButtonValue = circleValue || triangleValue;
    counterClockwiseButtonValue = xValue || squareValue; // 1 when pushed, 0 otherwise
    holdValue = r1Value || l1Value;
    flipValue = r2Value || l2Value;
  }

  /* int clockwiseButtonValue = digitalRead(clockwiseButton); // 1 when pushed, 0 otherwise */
  /* int counterClockwiseButtonValue = digitalRead(counterClockwiseButton); // 1 when pushed, 0 otherwise */

  if (gameOver && !ghostSettingsPushed && flipValue == 1) {
    ghostSettingsPushed = true;
  }

  if (gameOver && ghostSettingsPushed && flipValue == 0) {
    ghostSettingsPushed = false;
    ghostSettingsReleased = true;
  }

  if (gameOver && !newGamePushed && counterClockwiseButtonValue == 1) {
    newGamePushed = true;
  }

  if (gameOver && newGamePushed && counterClockwiseButtonValue == 0) {
    newGameReleased = true;
    newGamePushed = false;
  }

  controls = {
    rightValue, // Right
    leftValue, // Left
    upValue, // Up
    downValue, // Down
    clockwiseButtonValue == 1, // Clockwise
    counterClockwiseButtonValue == 1, // Counter clockwise
    flipValue, // Rotate 180
    holdValue, // Hold
    selectValue, // Select
    startValue, // Start
  };

  if (gameOver && !gameOverDrawn) {
    highScore = tetrisEngine.score > highScore ? tetrisEngine.score : highScore;
    gameOverDrawn = true;
    Serial.print(String(tetrisEngine.score));

//    int wordHeightOffset = 6; // Height of font + 1 space + 1 to set next draw location
    int currentY = 18;
    int lineOffset = 1;
    /* int highestY = currentY + lineOffset*4 + wordHeightOffset*5; */

//    newFillRect(0, currentY, MATRIX_HEIGHT, highestY - currentY, BLACK);
    /* newDrawLine(0, currentY - 1, MATRIX_HEIGHT - 1, currentY - 1, DIM_WHITE); */
    /* newDrawLine(0, highestY-1, MATRIX_HEIGHT - 1, highestY-1, DIM_WHITE); */

    currentY += lineOffset;

    /* /1* drawNumber(&highScore, currentY); *1/ */
    /* currentY += wordHeightOffset; */

    /* /1* drawHigh(currentY); *1/ */
    /* currentY += wordHeightOffset + lineOffset; */

    /* /1* drawNumber(&tetrisEngine.score, currentY); *1/ */
    /* currentY += wordHeightOffset; */

    /* /1* drawScore(currentY); *1/ */
    /* currentY += wordHeightOffset + lineOffset; */


    /* drawGameOver(currentY); */

    /* if (!shouldDrawGhost) { */
    /*   newDrawPixel(MATRIX_HEIGHT-1, MATRIX_WIDTH-1, matrix.Color333(7, 0, 3)); */
    /* } */
    /* currentY += wordHeightOffset; */

    /* newDrawLine(0, currentY, MATRIX_HEIGHT - 1, currentY, matrix.Color333(2, 2, 2)); */
  }

  if (gameOver) {
    firstIteration = true;
    if (newGameReleased) {
      newGameReleased = false;
      gameOver = false;
    } // else if (ghostSettingsReleased) {
      /* ghostSettingsReleased = false; */
      /* shouldDrawGhost = !shouldDrawGhost; */
      /* shouldDrawPiece = !shouldDrawPiece; */

      /* if (!shouldDrawGhost) { */
      /*   newDrawPixel(MATRIX_HEIGHT-1, MATRIX_WIDTH-1, matrix.Color333(7, 0, 3)); */
      /* } else { */
      /*   newDrawPixel(MATRIX_HEIGHT-1, MATRIX_WIDTH-1, matrix.Color333(2, 2, 2)); */
      /* } */
    /* } */
    if (millis() - gameOverAt > timeBeforeSleep) {
      // Go into a "sleep mode" after some time
      clearMatrix();
      leds.show();
    }
  }

  if (!gameOver) {
     gameOverDrawn = false;
     if 
     (firstIteration) {
        clearMatrix();
        leds.show();
        tetrisEngine.prepareNewGame(shouldDrawPiece);

        /* // Draw border */
        /* newDrawLine(0, 4, 0, MATRIX_WIDTH-1, DIM_WHITE); */
        /* matrix.drawLine(3, 0, 3, MATRIX_HEIGHT - 1, DIM_WHITE); */
        /* matrix.drawLine(3, MATRIX_HEIGHT-1, MATRIX_WIDTH-1, MATRIX_HEIGHT - 1, DIM_WHITE); */

        /* clearBottom(); */
        /* clearNextPieces(); */
        /* clearHeldPiece(); */

        // Draw line separating new pieces from help piece display
        /* newDrawLine(5, 0, 5, 2, DIM_WHITE); */
        /* matrix.drawLine(0, 8, 6, 8, matrix.Color333(2, 2, 2)); */
     }
    gameOver = tetrisEngine.loop(controls);
    if (gameOver) {
      gameOverAt = millis();
    }

    if (tetrisEngine.generationThisIteration || (tetrisEngine.pieceHeldThisIteration && !tetrisEngine.pieceHeldThisGame)) {
      printNextPieces();
    }

    if (tetrisEngine.pieceHeldThisIteration) {
      clearHeldPiece();
      Tetromino* heldPiece = tetrisEngine.heldPiece;
      /* int xOffset = heldPiece -> symbolNum == 5 ? 1 : 2; */
      for (int y = 0; y < heldPiece -> dimension; y++) {
        for (int x = 0; x < heldPiece -> dimension; x++) {
          if (heldPiece -> orientations[0][y][x] == 1) {
//            newDrawPixel(x+1, 1-y, colorMap[heldPiece -> symbolNum]);
            /* drawSquareNew(x, y + tetrisEngine.fieldHeight - 1, colorMap[heldPiece -> symbolNum], 2, xOffset); */
            int HELD_START = 440;
            if (y==0) {
//              leds.setPixel(HELD_START+(x*2), colorMap[heldPiece -> symbolNum]);
//              leds.setPixel(HELD_START+(x*2)+1, colorMap[heldPiece -> symbolNum]);
              leds.setPixel(HELD_START+6-(x*2), colorMap[heldPiece -> symbolNum]);
              leds.setPixel(HELD_START+6-(x*2)+1, colorMap[heldPiece -> symbolNum]);
            } else {
//              leds.setPixel(HELD_START+8+(8-(x*2)-2), colorMap[heldPiece -> symbolNum]);
//              leds.setPixel(HELD_START+8+(8-(x*2)-2)+1, colorMap[heldPiece -> symbolNum]);
              leds.setPixel(HELD_START+8+6-(8-(x*2)-2), colorMap[heldPiece -> symbolNum]);
              leds.setPixel(HELD_START+8+6-(8-(x*2)-2)+1, colorMap[heldPiece -> symbolNum]);
            }
          }
        }
      }

      

      /* if (!tetrisEngine.pieceHeldThisGame) { */
      /*   // We had to generate a new piece since this is the first hold of the game, */
      /*   // so we need to redraw held pieces. */
      /*   printNextPieces(); */
      /* } */
    }

    // Print board
    if (tetrisEngine.drawAllThisIteration) {
      printWholeBoard();
      drawGhost();
    } else if (tetrisEngine.drawThisIteration) {

      // Draw the new piece area
      for (int i = 0; i < INDICES_TO_DRAW_LENGTH && tetrisEngine.indicesToDraw[i] != -1; i++) {
         int indexToDraw = tetrisEngine.indicesToDraw[i];
         int x = indexToDraw % tetrisEngine.fieldWidth;
         int y = (indexToDraw - x) / tetrisEngine.fieldWidth;
          
         int currentNum = tetrisEngine.matrixRepresentation[indexToDraw];
         int currentColorInd = currentNum;
         if (currentNum == CURRENT_PIECE_CHAR) {
           if (shouldDrawPiece || tetrisEngine.gameController.dropPressed || tetrisEngine.firstPiece) {
             currentColorInd = tetrisEngine.currentPiece -> symbolNum;
           } else {
             // Draw black if we don't want to draw the current piece
             currentColorInd = 0;
           }
         }

         /* int currentColorInd = currentNum == CURRENT_PIECE_CHAR ? tetrisEngine.currentPiece -> symbolNum : currentNum; */
//         int currentColor = colorMap[currentColorInd];
//         int currentColorInd = currentNum == CURRENT_PIECE_CHAR ? tetrisEngine.currentPiece -> symbolNum : currentNum;
         int currentColor = colorMap[currentColorInd];
           newDrawPixel(x, y, currentColor);
      }

      drawGhost();
    }
    showPixels();

    firstIteration = false;
  }
}
