#define UNICODE
// constant definitions
enum COLOR{BLACK=30, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE};			//enum is a keyword to make collection of constant
#define bg(c) (c+10) //macro definition
// function declarations
void clearScreen(void);
void setColors(short fg, short bg);
void resetColors(void);
void barChart(int [] );


