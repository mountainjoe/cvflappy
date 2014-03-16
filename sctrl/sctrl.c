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

  printf("starting... hit any character to tap solenoid\r\n" ); 

  do {
    input = getch();

    printf("read char: %c\n\n", (char)input); 
#if RASPI
    digitalWrite( SOLENOID_GPIO, 1 );
#endif 
    usleep(SOLENOID_TAP_USEC); 
#if RASPI
    digitalWrite( SOLENOID_GPIO, 0 ); 
#endif 

  } while ( (input != EOF) && (input != '\n') );

  printf("exiting\r\n"); 
}
