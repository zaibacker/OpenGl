/*  restartOp.c  -  ENIB  -  LI2  -  01/05/2002 */

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <errno.h>

#include "restartOp.h"

/********************************************************/
/*                        fork                          */
/********************************************************/
pid_t fork_rs(void)
{
 pid_t result;

 do {
      result=fork();
 } while ((result==-1) && (errno==EAGAIN));

 return result;
}

/********************************************************/
/*                   wait, waitpid                      */
/********************************************************/
pid_t wait_rs(int *status)
{
 pid_t endPid;

 do {
      endPid=wait(status);
 } while ((endPid==-1) && (errno==EINTR));
 
 return endPid;
}

pid_t waitpid_rs(pid_t pid, int *status, int options)
{
 pid_t endPid;

 do {
      endPid=waitpid(pid,status,options);
 } while ((endPid==-1) && (errno==EINTR));
 
 return endPid;
}

/********************************************************/
/*                         sleep                        */
/********************************************************/
 
unsigned int sleep_rs(unsigned int seconds)
{
 int nbSecondsElapsed = 0;
 
 do {
 
     seconds = seconds -  nbSecondsElapsed;
 
     nbSecondsElapsed = sleep(seconds);
 
 } while (nbSecondsElapsed!=0);
 
 return 0;       /*  Zero  if  the requested time has elapsed */
}

/********************************************************/
/*                   read, write, close                 */
/********************************************************/

ssize_t read_rs(int fd, void *buf, size_t len)
{
 ssize_t returnValue = 0;

 do {
      returnValue = read(fd,buf,len);
 } while ((returnValue==-1) && (errno==EINTR));

 return returnValue;
}

ssize_t write_rs(int fd, const void *buf, size_t count)
{
 ssize_t returnValue = 0;

 do {
      returnValue = write(fd,buf,count);
 } while ((returnValue==-1) && (errno==EINTR));

 return returnValue;
}

int     close_rs(int fd)
{
 int returnValue = 0;

 do {
      returnValue = close(fd);
 } while ((returnValue==-1) && (errno==EINTR));

 return returnValue;
}

/********************************************************/
/*                        dup, dup2                     */
/********************************************************/

int dup_rs(int oldfd)
{
 int returnValue = 0;

 do {
      returnValue = dup(oldfd);
 } while ((returnValue==-1) && (errno==EINTR));

 return returnValue;
}

int dup2_rs(int oldfd, int newfd)
{
 int returnValue = 0;

 do {
      returnValue = dup2(oldfd,newfd);
 } while ((returnValue==-1) && (errno==EINTR));

 return returnValue;
}

/********************************************************/
/*                        semop                         */
/********************************************************/
int semop_rs(int semid, struct sembuf *sops,unsigned nsops)
{
 int returnValue = 0;

 do {
      returnValue = semop(semid,sops,nsops);
 } while ((returnValue==-1) && (errno==EINTR));

 return returnValue;
}

/********************************************************/
/*                      msgsnd, msgrcv                  */
/********************************************************/
 
int msgsnd_rs(int msqid, /* const */ void *msgp, int msgsz, int msgflg)
{
 int returnValue = 0;

 do {
      returnValue = msgsnd(msqid,msgp,msgsz,msgflg);
 } while ((returnValue==-1) && (errno==EINTR)); 
 
 return returnValue;
}

int msgrcv_rs(int msqid, void *msgp, int msgsz,long msgtyp,int msgflg)
{
 int returnValue = 0;

 do {
      returnValue = msgrcv(msqid,msgp,msgsz,msgtyp,msgflg);
 } while ((returnValue==-1) && (errno==EINTR)); 
 
 return returnValue;
}

/********************************************************/
/*                     connect, accept                  */
/********************************************************/

int connect_rs(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen)
{
  int returnValue = 0;

  do {
      returnValue = connect(sockfd,serv_addr,addrlen);
  } while ((returnValue==-1) && (errno==EINTR));

  return returnValue;
}

int accept_rs(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
 int returnValue  = 0;
 int addrlenSaved = *addrlen;

 do {
      *addrlen = addrlenSaved;
      returnValue = accept(sockfd,addr,addrlen);
  } while ((returnValue==-1) && (errno==EINTR));

  return returnValue;
}

/********************************************************/
/*      recv, send  (TCP ou UDP avec pseudo-connexions) */
/********************************************************/

ssize_t recv_rs(int sockfd, void *buf, size_t len, int flags)
{
 int returnValue = 0;

 do {
     returnValue = recv(sockfd,buf,len,flags);
 } while ((returnValue==-1) && (errno==EINTR));

 return returnValue;
}

ssize_t send_rs(int sockfd, const void *buf, size_t count, int flags)
{
 int returnValue = 0;

 do {
     returnValue = send(sockfd,buf,count,flags);
 } while ((returnValue==-1) && (errno==EINTR));

 return returnValue;
}

/********************************************************/
/*               recvfrom, sendto  (UDP)                */
/********************************************************/

ssize_t recvfrom_rs(int sockfd, void *buf, size_t len, int flags,
                    struct sockaddr *from, socklen_t *fromlen)
{
 ssize_t returnValue = 0;
 do {
      returnValue = recvfrom(sockfd,buf,len,flags,from,fromlen);
  } while ((returnValue==-1) && (errno==EINTR));

 return returnValue;
}

ssize_t sendto_rs(int sockfd, const void *msg, size_t count, int flags,
                  const struct sockaddr *to, socklen_t tolen)
{
 ssize_t returnValue = 0;
 do {
      returnValue = sendto(sockfd,msg,count,flags,to,tolen);
  } while ((returnValue==-1) && (errno==EINTR));

 return returnValue;
}
