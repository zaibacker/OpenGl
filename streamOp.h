/*  streamOp.h  -  sockets  -  ENIB  -  LI2  -  01/05/2002 */

#ifndef    STREAMOP_H
#define    STREAMOP_H

#include <sys/types.h>

/*******************************************************************/
/*     Quelques operations de lecture/ecriture sur socket          */
/*                     en mode connecte                            */
/*******************************************************************/

                    /* connectToServer  retourne -1 si Pb */
                    /* connectToServer2 retourne -1 si Pb */

extern int connectToServer(char serverHost[],unsigned short serverPort);
extern int connectToServer2(struct in_addr adrHost, unsigned short serverPort);

extern ssize_t writeFully(int sockfd, const void *buf, size_t count);
extern ssize_t readFully(int sockfd, void* buf, size_t count);

extern ssize_t writeLong(int sockfd, const long *l);
extern ssize_t readLong(int sockfd, long *l);

extern ssize_t writeShort(int sockfd, const short *s);
extern ssize_t readShort(int sockfd, short *s);

extern ssize_t writeString(int sockfd, char str[]);
extern ssize_t readString(int sockfd, char str[], size_t len);

#endif  /* STREAMOP_H */
