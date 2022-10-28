/*  creerSocket.c  -  sockets  -  ENIB  -  LI2  -  01/05/2002 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "creerSocket.h"

int creerSocket(unsigned short *port, int type) {

  int    la_socket, autorisation , ok;

  struct sockaddr_in adresse;
  socklen_t          lgr;

  la_socket=socket(PF_INET, type, 0);
  if (la_socket==-1) { perror("socket"); exit(EXIT_FAILURE); }

   /* Pour pouvoir relancer immediatement un serveur TCP  */
   /* ou lancer, sur une meme machine,                    */
   /*    plusieurs recepteurs UDP sur                     */
   /*    le meme port de diffusion (broadcast, multicast) */
  autorisation=1;
  ok = setsockopt(la_socket, SOL_SOCKET, SO_REUSEADDR,
                  &autorisation, sizeof(int));
  if (ok==-1) { perror("setsockopt"); exit(EXIT_FAILURE); }

  lgr = sizeof(struct sockaddr_in);
  memset(&adresse, 0, lgr) ;
  adresse.sin_family      = AF_INET ;
  adresse.sin_port        = htons(*port);
  adresse.sin_addr.s_addr = htonl(INADDR_ANY);
  ok = bind (la_socket, (struct  sockaddr*)&adresse, lgr);
  if (ok==-1) { perror("bind"); exit(EXIT_FAILURE); }

  ok = getsockname (la_socket, (struct sockaddr*)&adresse, &lgr);
  if (ok==-1) { perror("getsockname"); exit(EXIT_FAILURE); }

  *port = ntohs (adresse.sin_port);
  return (la_socket) ;
}
