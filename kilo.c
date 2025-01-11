#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

//the termios struct in its original state.
struct termios orig_termios;

//Disabling raw mode at exit
void disableRawMode(){
    //setting terminal attributes back to orignial state
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

//Turning off echoing & canonical mode
void enableRawMode(){
    //reading current terminal attributes into struct
    tcgetattr(STDIN_FILENO, &orig_termios);
    //calls disableRawMode when program exits
    atexit(disableRawMode);
    
    struct termios raw = orig_termios;

    /*modifying the struct to remove ECHO(prints everything to terminal)
    ECHO is a bitflag, and ~ is the bitwise NOT. The value of bitflag is flipped
    ICANON disables canonical mode*/
    raw.c_lflag &=  ~(ECHO | ICANON);

    //passing modified struct through tcsetattr() to change terminal attributes
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(){
    enableRawMode();

    char c;
    /*while loop reads 1 byte from standard input and stores it in variable c. read() returns a 1 when 
    it reads 1 byte (defined by 1 inside read(), 0 when it reaches the end of input*/
    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}
