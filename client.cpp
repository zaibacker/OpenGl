#include "client.h"
#include "wrapperopengl.h"


Client::Client(char * host){

	_hostname=host;
	timerSend = 0;
	_port = 0;
	fprintf(stderr, "Nom de la machine serveur : %s %d %d\n", _hostname, _port, &_port);
}


void 
Client::ReceiveTCP(struct global *globalData)
{
   int i;
   char chaine[SIZE];
         fprintf(stderr,"Reception message\n");
         if(readString(sockService,chaine, SIZE)>0){
	 // Afficher les positions des autres clients
		fprintf(stderr, "Message recu par le client : %s\n", chaine);
	 	int action, type, numero;
		float x, z;
		sscanf(chaine,"%d:%d:%d:%f:%f\0",&action, &type, &numero, &x, &z);
		switch(action){
		case DEPLACE : w1->deplacer(type,numero, x, z);
			break;
		case CREE : char nom[1];
			nom[0] =  (char)numero;
			//w1->creerfaune(type, nom, x, z);
			break;
		case DETRUI : w1->detruirefaune(type, numero);
			break;
		}
         }
}


void Client::SendTCP(char *phrase, struct global *globalData)
{

     //fprintf(stdout,"1 chaine envoyée sur socket %d \n",globalData->tabAccepts[i].socket);
     if(writeString(sockService, phrase) != (ssize_t)strlen(phrase)+1){
	perror("WriteString"); exit(1);
     } //else{fprintf(stdout,"chaine %s envoyee\n", phrase);}
}

void
Client::connexion(World * world) {
  //fprintf(stderr, "Nom de la machine serveur : %s %d %d\n", _hostname, _port, &_port);
  w1=world;
  sockService = creerSocket(&_port, SOCK_STREAM);

  /***************************************/ 
  /* Preparation de l'adresse du serveur */
  /***************************************/ 

  hp = gethostbyname (_hostname);

  if (hp == NULL) { perror("gethostbyname"); exit(EXIT_FAILURE); }

  lgradr = sizeof(struct sockaddr_in);
  memset(&adr, 0, lgradr);
  adr.sin_family = AF_INET;
  adr.sin_port = htons (PORT_SERVEUR);

  adr.sin_addr = *((struct in_addr *) (hp -> h_addr_list[0]));


  /****************************************/ 
  /*        Demande  de connexion         */
  /****************************************/ 

  ok = connect_rs(sockService, (struct sockaddr*)&adr, lgradr);
  if (ok == -1) { perror("connect"); exit(EXIT_FAILURE); }
 globalData.portTCP = _port;


 //InitServeurTCP(&globalData);
 //InitBroadcast(&globalData);

 // Apres la phase d'initialisation, on peut
 // Initialiser l'info locale a la session : IP + port
 // =======================================

 globalData.localInfo.portTCP = htons(globalData.portTCP);
 globalData.localInfo.addr    = getHostId();
 strncpy(globalData.localInfo.user,getenv("USER"),SIZE);
 globalData.localInfo.user[SIZE-1]='\0';
 getLocalHostName(globalData.localInfo.machine,SIZE);

 { // Pour info ... 

   char dotAddr[3+1+3+1+3+1+3+1];

   fprintf(stderr,"portTCP local  : %hu\n",ntohs(globalData.localInfo.portTCP));

   getDotAddr(globalData.localInfo.addr,dotAddr,sizeof(dotAddr));
   fprintf(stderr,"Adresse locale : %s\n",dotAddr);

   fprintf(stderr,"Machine locale : %s\n",globalData.localInfo.machine);

   fprintf(stderr,"USER           : %s\n",globalData.localInfo.user);
 }

}

void
Client::run(void){

 int i;

 int    sortieWhile; 

 fd_set rdFds;
 int    fdMax;
 int    resultSelect;
 struct timeval timeout,newTime,oldTime;
 int elapsed, timeoutMilli, remaining;

 // unsigned long tempsDerniereEmission, tempsCourant;
 long     nbSecondTimeOut;

 // struct sigaction actionSIGPIPE;

 // Init portTCP, portUDP


         // ================================================== //
         // LE RESTE DU main EST A COMPLETER ET A MODIFIER ... //
         // ================================================== //

 sortieWhile=0;
 nbSecondTimeOut=1;
 timeout.tv_sec=0;
 timeout.tv_usec=nbSecondTimeOut;
 gettimeofday(&oldTime,0);

  // Construction du tableau des descripteurs en attente
  // ===================================================

   FD_ZERO(&rdFds);
   fdMax = -1;

 //  FD_SET(STDIN_FILENO,&rdFds);
 // if (STDIN_FILENO>fdMax) fdMax = STDIN_FILENO;

  // FD_SET(globalData.socketUDP,&rdFds);
 //  if (globalData.socketUDP>fdMax) fdMax = globalData.socketUDP;

   FD_SET(sockService,&rdFds);
   if (sockService>fdMax) fdMax = sockService;


   // Initialisation du timeout pour le select
   // ========================================

   
  //timeout.tv_sec=2;
  //timeout.tv_usec=0;
 
   do
   {
    resultSelect=select(fdMax+1,
                        &rdFds,(fd_set *)0,(fd_set *)0,
                        &timeout);
   }while((resultSelect==-1)&&(errno==EINTR));

   switch(resultSelect)
   {
    case -1:
            fprintf(stderr,"Pb dans select !\n");
            break;
    case 0: 
            //fprintf(stderr,"Pas de phrase depuis %d secondes ...\n",nbSecondTimeOut);
            timeout.tv_sec=0;
            timeout.tv_usec=nbSecondTimeOut;
            //fprintf("Nouveau timeout : %d\n",(int)timeout.tv_sec);
		
            gettimeofday(&oldTime,0);
            break;
    default:

  gettimeofday(&newTime,0);
  //spend.tv_sec = newTime.tv_sec-oldTime.tv_sec;

  elapsed = (1000* newTime.tv_sec+newTime.tv_usec) - (1000* oldTime.tv_sec+oldTime.tv_usec);
  timeoutMilli = 1000 * timeout.tv_sec + timeout.tv_usec;
  remaining = nbSecondTimeOut*1000 - elapsed;
   if(remaining<0){
     timeout.tv_sec=0;
     timeout.tv_usec=0;
   }
   else{
   timeout.tv_sec = remaining/1000;
   timeout.tv_usec = remaining%1000;
   }
   //fprintf("timeout : %d,%d\n",(int)timeout.tv_sec,(int)timeout.tv_usec);
   oldTime.tv_sec = newTime.tv_sec;
   oldTime.tv_usec = newTime.tv_usec;

     /* if (FD_ISSET(STDIN_FILENO,&rdFds))
      {
       GetLine(phrase,SIZE);
       fprintf(stdout,"==>%s<==\n",phrase);
       SendAllTCP(phrase, &globalData);
       if (strcmp(phrase,"bye")==0) sortieWhile=1;
      }*/

      if(FD_ISSET(sockService,&rdFds)){
	//AcceptConnectionTCP( &globalData);
	ReceiveTCP(&globalData);
      }

     //if(FD_ISSET(globalData.socketUDP,&rdFds)){
     //	ReceptionBroadcast(&globalData);
     //}

   }
	if( (timerSend++) == SEND){/*printf("%d\n",timerSend);*/timerSend=0;/*envoyer notre 	position*/
	    char message[255];
	    sprintf(message,"%d:%d:%d:%f:%f\0",DEPLACE,AVATAR,w1->getwhoiam(),
	    w1->_cameraW->getPosX(),w1->_cameraW->getPosZ());
	    SendTCP(message, &globalData);		
	}


}



