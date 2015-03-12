/* 
 *  botm.c
 *  Lab 7 Server Side Component
 *  by Michael Hughes
 *  Permission given for students to modify and use this in assignments
 *  by Tami Meredtih
 */

/* 
 *  Program does not run according to specifications at the moment.
 *  The server creates and populates an array of accounts, where the
 *  specific account is found by the index of the array.
 *  Only the bal (balance) option works as it should. The program seems
 *  to hang sometimes when other operations are attempted.
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

#define DEBUG 0 /* Set to 0 to turn off debugging */

#define PORT 	1985
#define BUFSIZE 128
#define loop    while(1)

#define NUMACCTS 101
#define SHMSIZE  (NUMACCTS*sizeof(t_account))


typedef struct {
    int balance;
    int acctNum;
} t_account;

t_account  *accts;
char       *shm;

void dep(t_account *act, int amt)
{
    int tmp = act->balance;
    tmp = tmp + amt;
    act->balance = tmp;
    //return(0);
    exit(EXIT_SUCCESS);
}

void wd(t_account *acct1, int amt)
{
    int tmp = acct1->balance;
    tmp = tmp - amt;
    acct1->balance = tmp;
    //return(0);
    exit(EXIT_SUCCESS);
}

void trans(t_account *act1, t_account *act2, int amt)
{
    int x,y,z;
    x = act1->balance;
    y = act2->balance;
    z = amt;
    x = x - z;
    y = y + z;
    act1->balance = x;
    act2->balance = y;
    //return(0);
    exit(EXIT_SUCCESS);
}

int bal(t_account *act)
{
    return act->balance;
    exit(EXIT_SUCCESS);
}

int childmain(char *msg, int sd_current)
{
    char buf[BUFSIZE];
    /* display the incoming request */
    fprintf(stderr, "process %d handling: <%s>\n", getpid(), msg);
    sprintf(buf,"OK");
   
    /* acknowledge the message */
    if (send(sd_current, buf, strlen(buf)+1, 0) == -1) 
    {
        perror("send");
    }
    close (sd_current);
    return 0;
}

int main(int argc, char **argv)
{
    char     buf[BUFSIZE];  /* used for incoming and outgoing data */
    char    *msg;
    int      sd, sd_current;
    //, cc, fromlen, tolen;
    socklen_t      addrlen;
    struct   sockaddr_in sin;
    struct   sockaddr_in pin;
    int      pid, status;
    key_t    key = 8899;
    int      shmid;
    int      num;
    accts = malloc(SHMSIZE);
  

    /* setup the accounts */
    if ((shmid = shmget(key, SHMSIZE, IPC_CREAT | 0666)) < 0) 
    {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    if ((shm = shmat (shmid, NULL, 0)) == (char *) -1) 
    {
        perror("shmat");
        exit(EXIT_FAILURE);
    }
    accts = (t_account *) shm;
    memset (accts, 0, NUMACCTS * sizeof(t_account));
    for(num = 1; num <= NUMACCTS; num++)
    {
        accts[num].balance = 10;
        accts[num].acctNum = num;
    }

    /* get an internet domain socket */
    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    /* complete the socket structure */
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(PORT);

    /* bind the socket to the port number */
    if (bind(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1) 
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    fprintf(stderr, "%s: status: listening on port %d\n", argv[0], PORT);

    /* show that we are willing to listen */
    if (listen(sd, 5) == -1) 
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

#if DEBUG
    for(num = 1; num <= NUMACCTS; num++)
    {
        printf("testing %d %d\n",accts[num].acctNum,accts[num].balance);
    }
#endif

    loop 
    {

        /* wait for a client to talk to us */
        addrlen = sizeof(pin); 
        if ((sd_current = accept(sd, (struct sockaddr *)  &pin, &addrlen)) == -1) 
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

#if DEBUG
        /* show the ip address and port of the client */
        fprintf(stderr, "Server received connection from %s\n", inet_ntoa(pin.sin_addr));
        fprintf(stderr, "Coming from port %d\n", ntohs(pin.sin_port));
#endif

        /* get a message from the client */
        if (recv(sd_current, buf, sizeof(buf), 0) == -1) 
        {
            perror("recv");
            exit(EXIT_FAILURE);
        }
        msg = strdup(buf);
    
#if DEBUG
        /* show the data received from the client */
        fprintf(stderr, "Server received: <%s>\n", msg);
#endif

        /* Is this a shutdown request? */
        if (strcmp(msg,"shutdown") == 0) 
        {
            fprintf(stderr, "%s: status: shutting down\n", argv[0]);
            break;
        }
        
        char test[BUFSIZE];
        sscanf(msg,"%s",test);
        if (strcmp(test,"bal") == 0) 
        {
           char word[BUFSIZE];
           char comd[BUFSIZE];
           int aNum,num;
           sscanf(msg,"%s %d",word,&aNum);
           pid = fork();
           if(pid < 0)
           {
               perror("fork");
               exit(EXIT_SUCCESS);
           }
           else if(pid == 0)
           {
               num = bal(&accts[aNum]);
               sprintf(comd,"Account: %d\nBalance: %d\n",aNum,num);
               childmain(comd,sd_current);
               exit(EXIT_SUCCESS);
           }
           else
           {
               wait(&status);
           }
        }
        else if(strcmp(test,"wd") == 0) 
        {
            char word[BUFSIZE];
            char comd[BUFSIZE]; 
            int aNum, amt,num;
            sscanf(msg,"%s %d %d",word,&aNum,&amt);
            pid = fork();
            if(pid < 0)
            {
                perror("fork");
                exit(EXIT_SUCCESS);
            }
            else if(pid == 0)
            {

                wd(&accts[aNum],amt);
                num = bal(&accts[aNum]);
                sprintf(comd,"Account: %d\nWithdraw the amount: %d\nBalance: %d\n",
                    aNum,amt,num);
                childmain(comd,sd_current);
                exit(EXIT_SUCCESS);
            }
            else
            {
                wait(&status);
            }
        }
        else if (strcmp(test,"trans") == 0) 
        {
            char word[BUFSIZE];
            char comd[BUFSIZE]; 
            int aNum1, aNum2, amt,bal1,bal2;
            sscanf(msg,"%s %d %d %d",word,&aNum1,&aNum2,&amt);
            pid = fork();
            if(pid < 0)
            {
                perror("fork");
                exit(EXIT_SUCCESS);
            }
            else if(pid == 0)
            {

                trans(&accts[aNum1],&accts[aNum2],amt);
                bal1 = bal(&accts[aNum1]);
                bal2 = bal(&accts[aNum2]);
                sprintf(comd,"Transfer from account: %d\nTransfer to account: %d\nTransfer amount: %d\nAccount %d balance: %d\nAccount %d balance: %d\n",
                    aNum1,aNum2,amt,aNum1,bal1,aNum2,bal2);
                childmain(comd,sd_current);
                exit(EXIT_SUCCESS);
            }
            else 
            {
                wait(&status);
            }
        }
        else if (strcmp(test,"dep") == 0)
        {
            printf("trace1\n");
            char word[BUFSIZE];
            char comd[BUFSIZE];  
            int aNum, amt, num;
            scanf(msg,"%s %d %d",word,&aNum,&amt);
            pid = fork();
            if(pid < 0)
            {
                perror("fork");
                exit(EXIT_SUCCESS);
            }
            else if(pid == 0)
            {

                dep(&accts[aNum],amt);
                printf("trace2\n");
                num = bal(&accts[aNum]);
                sprintf(comd,"Account: %d\nDeposit the amount: %d\nBalance: %d\n",
                    aNum,amt,num);
                childmain(comd,sd_current);
                exit(EXIT_SUCCESS);
            }
            else
            {
                wait(&status);
            }
        }

        /* Handle this transaction */    
        //childmain(msg,sd_current);
        close(sd_current); 

    } /* end loop */

    close(sd);
    return 0;
} /* end main() */
