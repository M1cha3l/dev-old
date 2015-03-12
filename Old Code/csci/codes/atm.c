/* 
 *  Client.c
 *  by Tami Meredith
 *  Lab 7
 */

/*
 *  Notes: 
 *  Please ensure that the port number in this file matches the port number
 *  used in the server code. They must be the same!
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#define HOST     "localhost" 
#define BUFSIZE  128 
#define COMDLEN  64

#define DEBUG 0 /* Change to 1 to enable debugging output */

/*
 * Useful global variables
 */
char *app;
char  comd[COMDLEN];

int
getComd()
{
  int a1, a2, amt;
  char c;
  int valid = 0;
  do {
    printf("Command [w: withdraw, d: deposit, t: transfer, b: balance, q: quit, s: shutdown]\n? ");
    scanf("%c", &c);
    switch (c) {
      case 'w':
      case 'W':
        printf("Account Number [1 to 99]\n? ");
        scanf("%i", &a1);
        printf("Amount [in cents]\n? ");
        scanf("%i", &amt);
        sprintf(comd, "wd %d %d", a1, amt);
        valid = 1;
        break;
      case 'd':
      case 'D':
        printf("Account Number [1 to 99]\n? ");
        scanf("%i", &a1);
        printf("Amount [in cents]\n? ");
        scanf("%i", &amt);
        sprintf(comd, "dep %d %d", a1, amt);
        valid = 1;
        break;
      case 't':
      case 'T':
        printf("Source Account Number [1 to 99]\n? ");
        scanf("%i", &a1);
        printf("Destination Account Number [1 to 99]\n? ");
        scanf("%i", &a2);
        printf("Amount [in cents]\n? ");
        scanf("%i", &amt);
        sprintf(comd, "trans %d %d %d", a1, a2, amt);
        valid = 1;
        break;
      case 'b':
      case 'B':
        printf("Account Number [1 to 99]\n? ");
        scanf("%i", &a1);
        sprintf(comd, "bal %d", a1);
        valid = 1;
        break;
      case 's':
      case 'S':
        sprintf(comd, "shutdown");
        valid = 1;
        break;
      case 'q':
      case 'Q':
        return (0);
      default:
        printf("\nError: Invalid command.\n");
        printf("Char %c (%d)\n", c, c);
        break;
    }
    scanf("%c",&c); /* read the stupid newline from the buffer */
  } while (!valid);
#if DEBUG
  printf("Command: %s\n", comd);
#endif
  return (1);
} /* end getComd() */

int
main(int argc, char **argv)
{
  char hostname[100];
  int  port;
  char buf[BUFSIZE];
  int  sd;
  struct sockaddr_in sin;
  struct sockaddr_in pin;
  struct hostent *hp;
  int i;

  /* Process command line arguments */
  app = argv[0];
  if (argc < 2) {
      fprintf (stderr, "usage: %s <port> <hostname>\n", app); 
      exit(1);
  }
  sscanf(argv[1],"%d",&port);
  if (argc == 3) {
    strcpy(hostname,argv[2]);
  } else {
    strcpy(hostname,HOST);
  }

  /* find the desired host machine */
  if ((hp = gethostbyname(hostname)) == 0) {
    perror("gethostbyname");
    exit(1);
  }

  /* fill in the socket structure with host information */
  memset(&pin, 0, sizeof(pin));
  pin.sin_family = AF_INET;
  pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
  pin.sin_port = htons(port);

  while (getComd()) {
 
    /* grab an Internet domain socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
      perror("socket");
      exit(1);
    }

    /* connect to PORT on HOST */
    if (connect(sd,(struct sockaddr *)  &pin, sizeof(pin)) == -1) {
      perror("connect");
      exit(1);
    }

    /* send a message to the server PORT on machine HOST */
    if (send(sd, comd, strlen(comd)+1, 0) == -1) {
      perror("send");
      exit(1);
    }

    if (!strcmp(comd,"shutdown")) {
      /* Quit - no response coming */
      exit(0);
    }

    /* wait for a message to come back from the server */
    strcpy (buf, "No response."); /* clear last message */
    if (recv(sd, buf, BUFSIZE, 0) == -1) {
      perror("recv");
      exit(1);
    }

    /* Display the received return message from the server */
    printf("Server Response: <%s>\n", buf);
    close(sd);
  } /* end command loop */

} /* end main() */
