#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int markVertical(char *board[], int i, int j);
int markHorizontal(char *board[], int i, int j);
int markDiagonal(char *board[], int i, int j);
void print(char *board[]);
void printQ(char *board[]);
void printW(char *board[]);
void plus2(char *board[]); // one argument -- +2 
void warrior(char *filename, int hasPlus2); // one argument -- -w
int markKnight(char *board[], int i, int j);
int possibleWarrior(char *board[], int i, int j);
void plus2W(char *board[]);


int main(int argc, char **argv) {
  /* error check */
  if (argc < 2) {
    printf("insufficient number of arguments\n");
    return 0;
  }

  FILE *fp;
  /* opening the file */
  if (argc == 2) {
    fp = fopen(argv[1], "r");
  } else if (argc == 3) {
    if (strcmp(argv[1], "-w") == 0) {
      warrior(argv[2], 0);
      return 0;
    } else {
      fp = fopen(argv[2], "r");
    }
  } else {
    warrior(argv[3], 1);
    return 0;
  }

  int i, j, valid;
  char temp;
  char *board[8];
  
  /* allocating memory */
  for (i = 0; i < 8; i++) {
    board[i] = malloc(8 * sizeof(char));
  }

  /* loading into array */
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      board[i][j] = 'O';
    }
  }


  /* reading file & updating array */
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      fscanf(fp, "%c", &temp);
      if (temp == 'Q') {
        board[i][j] = 'Q';
      }      
    }
    fscanf(fp, "%*c");
  }

  /* closing file */
  fclose(fp);
  valid = 0;

/* marking all unavailible spots and checking for validity */
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if (board[i][j] == 'Q') {
        valid += markVertical(board, i, j);
        valid += markHorizontal(board, i, j);
        valid += markDiagonal(board, i, j);
      }
      if (valid > 0) {
        printf("Invalid\n");
        return 0;
      }
    }
  }

  printQ(board);

  /* 1 argument */
  if (argc == 3) {
    if (strcmp(argv[1], "+2") == 0) {
      plus2(board);
    }
  }


  /* FREE MEMORY */
  for (i = 0; i < 8; i++) {
    free(board[i]);
  }


  return 0;
}

int markVertical(char *board[], int i, int j) {
  int k;
  for (k = 0; k < 8; k++) {
    if (k != i) {
      if (board[k][j] == 'Q') {
        return 1;
      } else {
        board[k][j] = 'X';
      }
    }
  }

  return 0;
}

int markHorizontal(char *board[], int i, int j) {
  int k;
  for (k = 0; k < 8; k++) {
    if (k != j) {
      if (board[i][k] == 'Q') {
        return 1;
      } else {
        board[i][k] = 'X';
      }
    }
  }
  return 0;

}

int markDiagonal(char *board[], int i, int j) {
  int temp_i = i -1;
  int temp_j = j -1;

  /* mark NW */
  while ((temp_i > -1) && (temp_j > -1)) {
    if (board[temp_i][temp_j] == 'Q') {
      return 1;
    }
    board[temp_i][temp_j] = 'X';
    temp_i--;
    temp_j--;
  }

  /* mark NE */
  temp_i = i -1;
  temp_j = j + 1;
  while ((temp_i > -1) && (temp_j < 8)) {
    if (board[temp_i][temp_j] == 'Q') {
      return 1;
    }
    board[temp_i][temp_j] = 'X';
    temp_i--;
    temp_j++;
  }

  /* mark SE */
  temp_i = i + 1;
  temp_j = j + 1;
  while ((temp_i < 8) && (temp_j < 8)) {
    if (board[temp_i][temp_j] == 'Q') {
      return 1;
    }
    board[temp_i][temp_j] = 'X';
    temp_i++;
    temp_j++;
  }

  /* mark SW */
  temp_i = i + 1;
  temp_j = j - 1;
  while ((temp_i < 8) && (temp_j > -1)) {
    if (board[temp_i][temp_j] == 'Q') {
      return 1;
    }
    board[temp_i][temp_j] = 'X';
    temp_i++;
    temp_j--;
  }
  return 0;

}


/* prints the board */
void print(char *board[]) {
  int i, j;

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }


}

void printQ(char *board[]) {
  int i, j;

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if (board[i][j] == 'O') {
        printf("%c", 'q');
      } else if (board[i][j] == 'X') {
        printf("%c", '.');
      } else {
        printf("%c", board[i][j]);
      }
    }
    printf("\n");
  }

}

void plus2(char *board[]) {
  int count = 0;
  int i, j;

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if (board[i][j] == 'O') {
        count++;
        board[i][j] = 'Q';
        markVertical(board, i, j);
        markHorizontal(board, i, j);
        markDiagonal(board, i, j);
      }
    }
  }
  /* printing result */
  if (count == 0) { printf("Zero\n"); }
  if (count == 1) { printf("One\n"); }
  if (count >= 2) { printf("Two or more\n"); }

}


void warrior(char *filename, int hasPlus2) {
  FILE *fp;
  fp = fopen(filename, "r");

  int i, j;
  int valid = 0;
  char temp;
  char *board[8];

  /* allocating memory */
  for (i = 0; i < 8; i++) {
    board[i] = malloc(8 * sizeof(char));
  }

  /* loading into array */
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      board[i][j] = 'O';
    }
  }


  /* reading file & updating array */
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      fscanf(fp, "%c", &temp);
      if (temp == 'Q') { board[i][j] = 'Q'; }
      if (temp == 'W') { board[i][j] = 'W'; }
    }
    fscanf(fp, "%*c");
  }

  /* closing file */
  fclose(fp);

  /* marking all unavailible spots and checking for validity */
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if (board[i][j] == 'Q' || board[i][j] == 'W') {
        valid += markVertical(board, i, j);
        valid += markHorizontal(board, i, j);
        valid += markDiagonal(board, i, j);
        if (board[i][j] == 'W') {
          valid += markKnight(board, i, j);
        }
        if (valid > 0) {
          printf("Invalid\n");
          return;
        }
      }
    }
  }
  printW(board);
  
  /* if +2 tag added */
  if (hasPlus2 == 1) { 
    plus2W(board);
  }



  /* FREE MEMORY */
  for (i = 0; i < 8; i++) {
    free(board[i]);
  }

}


int markKnight(char *board[], int i, int j) {
  int temp_i, temp_j;
  int counter = 1;

  while (counter < 9) {
    switch (counter) {
      case 1 :
        temp_i = i - 2;
        temp_j = j - 1;
        break;
      case 2 :
        temp_i = i - 2;
        temp_j = j + 1;
        break;
      case 3 :
        temp_i = i - 1;
        temp_j = j + 2;
        break;
      case 4 :
        temp_i = i + 1;
        temp_j = j + 2;
        break;
      case 5 :
        temp_i = i + 2;
        temp_j = j + 1;
        break;
      case 6 :
        temp_i = i + 2;
        temp_j = j - 1;
        break;
      case 7 :
        temp_i = i + 1;
        temp_j = j - 2;
        break;
      case 8 :
        temp_i = i - 1;
        temp_j = j - 2;
        break;
    }
    /* checks to make sure i, j in bounds before marking it on the board */
    if((temp_i < 8) && (temp_i > -1) && (temp_j < 8) && (temp_j > -1)) {
      if (board[temp_i][temp_j] == 'O' || board[temp_i][temp_j] == 'X') { 
        board[temp_i][temp_j] = 'X'; 
      } else { 
        return 1; 
      }
    }
    counter++;
  }

  return 0;
}

int possibleWarrior(char *board[], int i, int j) {
  int temp_i, temp_j;
  int counter = 1;

  while (counter < 9) {
    switch (counter) {
      case 1 :
        temp_i = i - 2;
        temp_j = j - 1;
        break;
      case 2 :
        temp_i = i - 2;
        temp_j = j + 1;
        break;
      case 3 :
        temp_i = i - 1;
        temp_j = j + 2;
        break;
      case 4 :
        temp_i = i + 1;
        temp_j = j + 2;
        break;
      case 5 :
        temp_i = i + 2;
        temp_j = j + 1;
        break;
      case 6 :
        temp_i = i + 2;
        temp_j = j - 1;
        break;
      case 7 :
        temp_i = i + 1;
        temp_j = j - 2;
        break;
      case 8 :
        temp_i = i - 1;
        temp_j = j - 2;
        break;
    }
    /* checks to make sure i, j in bounds before checking it on the board */
    if((temp_i < 8) && (temp_i > -1) && (temp_j < 8) && (temp_j > -1)) {
      if (board[temp_i][temp_j] == 'Q' || board[temp_i][temp_j] == 'W') {
        return 0;
      }
    }
    counter++;
  }

  return 1;

}


void printW(char *board[]) {
  int i, j, temp;

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if (board[i][j] == 'X') {
        printf("%c", '.');
      } else if (board[i][j] == 'O') {
        temp = possibleWarrior(board, i, j);
        if (temp == 1) { printf("%c", 'w'); }
        else { printf("%c", 'q'); }
      } else if (board[i][j] == 'Q') {
        printf("%c", 'Q');
      } else {
        printf("%c", board[i][j]);
      }
    }
    printf("\n");
  }

}

void plus2W(char *board[]) {
  int count = 0;
  int i, j, temp;

  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      if (board[i][j] == 'O') {
        temp = possibleWarrior(board, i, j);
        if (temp == 1) {
          board[i][j] = 'W';
          markVertical(board, i, j);
        } else {
          board[i][j] = 'Q';
        }
        count++;
        markVertical(board, i, j);
        markHorizontal(board, i, j);
        markDiagonal(board, i, j);
      }
    }
  }

  /* printing result */
  if (count == 0) { printf("Zero\n"); }
  if (count == 1) { printf("One\n"); }
  if (count >= 2) { printf("Two or more\n"); }

}





