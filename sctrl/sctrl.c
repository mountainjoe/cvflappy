#include <stdio.h>
#include <unistd.h>

#include <curses.h>

#if RASPI
#include <wiringPi.h>
#endif /* RASPI */

#define SOLENOID_GPIO (4)
#define SOLENOID_TAP_USEC ( 500 * 1000 )

int main( int argc, char **argv) {
  int input = 0; 

#if RASPI
  wiringPiSetupGpio(); 
  pinMode( SOLENOID_GPIO, OUTPUT );
  digitalWrite( SOLENOID_GPIO, 0 ); 
#endif /* RASPI */

  initscr();
  cbreak();

  printw("starting... hit any character to tap solenoid\nhit return to exit\n" ); 

  do {
    input = getch();
    printw("read char: %c\n", (char)input); 
    refresh();
#if RASPI
    digitalWrite( SOLENOID_GPIO, 1 );
#endif 
    usleep(SOLENOID_TAP_USEC); 
#if RASPI
    digitalWrite( SOLENOID_GPIO, 0 ); 
#endif 

  } while ( (input != EOF) && (input != '\n') );

  printw("exiting\n"); 
  endwin(); 
}
