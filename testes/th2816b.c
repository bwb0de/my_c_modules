#define PORT 0
#include "dos.h"
#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "conio.h"

void port_init( int port,unsigned char code );
int check_stat( int port ); /* read serial port state(16bit) */
void send_port( int port,char c ); /* send a character to serial port */
char read_port( int port ); /* recive a character form serial port */
void string_wr( char *ps ); /* write a string to serial port */
void string_rd( char *ps ); /* read a string from serial port */
char input[256]; /* quary recieve bufer */

main() {
    port_init( PORT,0xe3 ); /* initilize serial port:baud = 9600,no verify,1 bit stop,8 bit data */
    string_wr( "trig:sour bus;*trg" );
    string_rd( input );
    printf( "\n%s",input );
    string_wr( "freq 10khz" );
    string_wr( "func:imp:type rx;:func:smon on" );
    string_wr( "voltage:level 500mv" );
}

/* write string to serial port */
void string_wr( char *ps ) { 
    char c;
    int m,n;

    while( check_stat(PORT) & 256 ) read_port( PORT );/* read data until null */
        for( ;*ps; )
            { c = 0;
            for( m = 100;m;m-- )
                { send_port( PORT,*ps );
                for( n = 1000;n;n-- )
                    { delay( 2 ); /* wait about 2ms, use dos.h libray funtion */
                        if( kbhit() && ( getch() == 27 ) ) /* if escape key keypress */
                            { printf( "\nE20:Write Canceled!" );
                                exit(1);
                            }
                        if( check_stat(PORT) & 256 )
                            { c = read_port( PORT );
                                break;
                            }
                    }
                if( n ) break;
                }
            if( c == *ps ) ps++;
            else
                { printf( "\nE10:Write Echo Error!" );
                    exit(1);
                }
            }

    send_port( PORT,'\n' );/* send command end symbol */
    delay( 2 );
    while( !(check_stat(PORT) & 256) );
    read_port( PORT );
}



/* read string from serial port */
void string_rd( char *ps ) {
    unsigned char c,i;
    for( i = 0;i < 255;i++ ) /* max read 256 characters */
        { while( ! (check_stat(PORT) & 256) ) /* wait serial recieve ready */
            if( kbhit() && (getch() == 27) ) /* if escape key keypress */
                { printf( "\nE21:Read Canceled!" );
                    exit(1);
                }
            c = read_port( PORT );
            if( c == '\n' ) break;
            *ps = c;
            ps++;
        }
    *ps = 0;
}


/* send a character to serial port */
void send_port( int port,char c ) {
    union REGS r;
    r.x.dx = port; /* serial port */
    r.h.ah = 1; /* int14 function1:send character */
    r.h.al = c; /* character to be sent */
    int86( 0x14,&r,&r );
    if( r.h.ah & 128 ) /* check ah.7,if set by int86( 0x14,&r,&r ),mean trans error */
        { printf( "\nE00:Serial port send error!" );
            exit(1);
        }
}


/* read a character from serial port */
char read_port( int port ){
    union REGS r;
    r.x.dx = port; /* serial port */
    r.h.ah = 2; /* int14 function2:read character */
    int86( 0x14,&r,&r );
    if( r.h.ah & 128 ) /* if ah.7 be set,mean trans error */
        { printf( "\nE01:Serial port read error!" );
            exit(1);
        }
    return r.h.al;
}


/* check the status of serial port */
int check_stat( int port ){
    union REGS r;
    r.x.dx = port; /* serial port */
    r.h.ah = 3; /* int14 function3:read status */
    int86( 0x14,&r,&r );
    return r.x.ax; /* ax.7 show serial operation, ax.8 show serial recive ready*/
}


/* initialize the serial port */
void port_init( int port,unsigned char code ){
    union REGS r;
    r.x.dx = port; /* serial port */
    r.h.ah = 0; /* int14 function0:initial serial port */
    r.h.al = code; /* initialization code */
    int86( 0x14,&r,&r );
}