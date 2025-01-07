#include <unistd.h>

int main(){
    char c;
    /*while loop reads 1 byte from standard input and stores it in variable c. read() returns a 1 when 
    it reads 1 byte (defined by 1 inside read(), 0 when it reaches the end of input*/
    while(read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}
