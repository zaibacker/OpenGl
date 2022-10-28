/*  streamSer.c  -  sockets  -  ENIB  -  LI2  -  01/05/2002 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define   PORT_SERVEUR  4700

#include "creerSocket.h"
#include "restartOp.h"
#include "streamOp.h"


/**********************************************************************/
/*                            LE SERVICE                              */
/**********************************************************************/

#include <ctype.h>

#define SIZE 256
 
void service(int sock_service)
{
  int ok;
 
  char chaine1[SIZE];
  char chaine2[SIZE];
 
  ok = readString(sock_service,chaine1,SIZE);
  if (ok==-1 || ok==0) { perror("readString:1"); exit(EXIT_FAILURE); }

  printf("chaine1 recue du client:%s\n",chaine1);
 
  ok = readString(sock_service,chaine2,SIZE);
  if (ok==-1 || ok==0) { perror("readString:2"); exit(EXIT_FAILURE); }

  printf("chaine2 recue du client:%s\n",chaine2);
 
  /***************************************/
  /*        Envoi de la reponse          */
  /***************************************/
 
  ok = writeString(sock_service,chaine2);
  if (ok==-1 || ok==0) { perror("writeString"); exit(EXIT_FAILURE); }

  printf("1er envoi de:%s\n",chaine2);

  ok = writeString(sock_service,chaine1);
  if (ok==-1 || ok==0) { perror("writeString"); exit(EXIT_FAILURE); }

  printf("2eme envoi de:%s\n",chaine1);
}

/**********************************************************************/
/*                          Pour les zombies                          */
/**********************************************************************/

void eliminer_zombie(int signum)
{
 pid_t pid;
 printf("Terminaison d'un processus de service"
        " detectee avec le signal %d\n",signum);
 do {
     pid = waitpid(-1,NULL,WNOHANG);
 } while (pid!=-1 && pid!=0);
}

void initSignalAction(int signum, void(*fct)(int))
{
  struct sigaction action;

  action.sa_handler = fct;
  sigfillset( &(action.sa_mask) );
  action.sa_flags = 0;

  if (sigaction(signum,&action, NULL) != 0)
     fprintf(stderr,"Signal %d non capture\n",signum);
}
/**********************************************************************/

int main (void) {

  int                sock_ecoute, sock_service;

  unsigned short     port;

  struct sockaddr_in adr ;
  socklen_t          lgradr ;

  pid_t  pid;
                                             /* SIGCHLD : fin d'un */
  initSignalAction(SIGCHLD,eliminer_zombie); /*   processus fils   */


  port = PORT_SERVEUR;
  sock_ecoute = creerSocket(&port, SOCK_STREAM);

  if (listen(sock_ecoute,5)==-1) { perror("listen"); exit(EXIT_FAILURE); }

  while (1) {

    printf("Attente de demande de connexion...\n");
    
    lgradr=sizeof(struct sockaddr_in);
    sock_service = accept(sock_ecoute, (struct sockaddr*)&adr, &lgradr);

    if (sock_service==-1) {
                           if (errno!=EINTR) perror("accept");
                           continue;
    }

    pid = fork_rs();

    switch (pid) {

      case -1 : perror("fork");          /* En cas d'erreur   */
                close_rs(sock_ecoute);   /* de fork, on ferme */ 
                close_rs(sock_service);  /* les sockets et on */
                exit(EXIT_FAILURE);      /* arrete le serveur */
                break;

      case  0 : close_rs(sock_ecoute);   /* Le fils traite la */
                service(sock_service);   /* demande. Une fois */
                close_rs(sock_service);  /* le service rendu, */
                exit(EXIT_SUCCESS);      /* on arrete le fils */
                break;

      default : close_rs(sock_service);  /* Le pere ne traite */
                break;                   /* pas la demande et */
                                         /* va vers le while..*/
    }
  }

  return EXIT_SUCCESS;
}
