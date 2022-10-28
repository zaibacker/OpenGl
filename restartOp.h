/*  restartOp.h  -  ENIB  -  LI2  -  01/05/2002 */

#ifndef    RESTARTOP
#define    RESTARTOP

#include <sys/types.h>
#include <sys/sem.h>
#include <sys/socket.h>

/********************************************************/
/*                        fork                          */
/********************************************************/

extern pid_t fork_rs(void);

/********************************************************/
/*                   wait, waitpid                      */
/********************************************************/

extern pid_t wait_rs(int *status);
extern pid_t waitpid_rs(pid_t pid, int *status, int options);

/********************************************************/
/*                         sleep                        */
/********************************************************/
 
extern unsigned int sleep_rs(unsigned int seconds);

/********************************************************/
/*                   read, write, close                 */
/********************************************************/

extern ssize_t read_rs(int fd, void *buf, size_t len);
extern ssize_t write_rs(int fd, const void *buf, size_t count);
extern int     close_rs(int fd);

/********************************************************/
/*                        dup, dup2                     */
/********************************************************/

extern int dup_rs(int oldfd);
extern int dup2_rs(int oldfd, int newfd);

/********************************************************/
/*                        semop                         */
/********************************************************/
extern int semop_rs(int semid, struct sembuf *sops,unsigned nsops);

/********************************************************/
/*                      msgsnd, msgrcv                  */
/********************************************************/

extern int msgsnd_rs(int msqid, /* const */ void* msgp, int msgsz, int msgflg);
extern int msgrcv_rs(int msqid, void* msgp, int msgsz, long msgtyp,int msgflg);

/********************************************************/
/*                     connect, accept                  */
/********************************************************/

extern int connect_rs(int sockfd, struct sockaddr *serv_addr,socklen_t addrlen);
extern int accept_rs(int sockfd, struct sockaddr *addr,socklen_t *addrlen);

/********************************************************/
/*                     recv, send                       */
/********************************************************/

extern ssize_t recv_rs(int sockfd, void *buf, size_t len, int flags);
extern ssize_t send_rs(int sockfd, const void *buf, size_t count, int flags);

/********************************************************/
/*                   recvfrom, sendto                   */
/********************************************************/
extern ssize_t recvfrom_rs(int sockfd, void *buf, size_t len, int flags,
                           struct sockaddr *from, socklen_t *fromlen);
extern ssize_t sendto_rs(int sockfd, const void *msg, size_t count, int flags,
                         const struct sockaddr *to, socklen_t tolen);

#endif  /* RESTARTOP */
