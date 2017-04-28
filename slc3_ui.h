/*
TCSS372 - Computer Architecture
Problem #3
Group Members: 
Shaun Coleman
Joshua Meigs
*/
#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <stdlib.h>
#include <string.h> 
#include "slc3.h"

#define WIN_WIDTH 70
#define MAIN_WIN_HEIGHT 21
#define IO_WIN_HEIGHT 7
#define MAIN_WIN_START_POS 0, 0
#define IO_WIN_START_POS 21, 0

#define TITLE_Y_X 0, 14
#define REG_TITLE_Y_X 1, 14
#define MEM_TITLE_Y_X 1, 42

#define MAX_INPUT_SIZE 80
#define MAX_REG 8
#define MAX_MEM 16
#define REG_LABEL_X 14
#define REG_VAL_X 18
#define MEM_LABEL_X 40
#define REG_MEM_START_Y 2
#define MEM_VAL_X 47

#define PC_LABEL_Y_X 13,13
#define PC_VAL_Y_X 13,17

#define IR_LABEL_Y_X 13,26
#define IR_VAL_Y_X 13,30

#define A_LABEL_Y_X 14,13
#define A_VAL_Y_X 14,17

#define B_LABEL_Y_X 14,26
#define B_VAL_Y_X 14,30

#define MAR_LABEL_Y_X 15,12
#define MAR_VAL_Y_X 15,17

#define MDR_LABEL_Y_X 15,24
#define MDR_VAL_Y_X 15,30

#define CC_LABEL_Y_X 16,14

#define N_LABEL_Y_X 16,18
#define N_VAL_Y_X 16,21
#define Z_LABEL_Y_X 16,23
#define Z_VAL_Y_X 16,26
#define P_LABEL_Y_X 16,28
#define P_VAL_Y_X 16,31

#define MENU_Y_X 18,1
#define INPUT_LABEL_Y_X 1,5
#define OUTPUT_LABEL_Y_X 2,5
#define PROMPT_Y_X 19,1
#define PROMPT_DISPLAY_Y 19
#define PROMPT_DISPLAY_X 3

#define ARROW_X 38
#define INPUT_LIMIT 65
#define DEFAULT_MEM_ADDRESS 0x3000
#define CP_WHITE_BLUE 1
#define TOTAL_WIN_HEIGHT 27

#define HEX_OUT_LABEL "x%.04x:"
#define HEX_OUT_FORMAT "x%.04x"
#define REG_OUT_FORMAT "R%d:"

#define HALF(x) ((x)/2)

typedef struct {
	WINDOW *mainWin;
	WINDOW *ioWin;
	unsigned short memAddress;
	unsigned short maxY, maxX;
} DEBUG_WIN_s;

typedef DEBUG_WIN_s* DEBUG_WIN_p;

// Print Main Window Labels
void printLabels(DEBUG_WIN_p);

// Print IO Window Labels
void printIoLabels(DEBUG_WIN_p);

// Update and reprint Memory labels and values
void updateMemory(DEBUG_WIN_p, unsigned short*, unsigned short);

// Update register values
void updateRegisterValues(DEBUG_WIN_p, CPU_p);

// Reprints only the boarder of the screen
void reprintBoarder(DEBUG_WIN_p);

// Clear and reprint both windows
void reprintScreen(DEBUG_WIN_p, CPU_p, unsigned short *, char);

// Update Screen Pos and Refresh
void updateScreen(DEBUG_WIN_p, CPU_p, unsigned short *, char);

// Initialize Struct and start ncurses
void initializeWindows(DEBUG_WIN_p);

// Free Windows and exit ncurses
void endWindows(DEBUG_WIN_p);

// Clears the prompt section of the screen
void clearPrompt(DEBUG_WIN_p);

// Prompts user with optional message
void promptUser(DEBUG_WIN_p, char*, char*);

// Displays a message in the prompt section using the standout attribute
void displayBoldMessage(DEBUG_WIN_p win, char* message);