//serveur.cpp : Jean-Sébastien

#include "serveur.h"
#include "wrapperopengl.h"


Serveur::Serveur(){


}

void 
Serveur::AcceptConnectionTCP(struct global *globalData)
{
 char mes[255];
 int num;
 float x,z;
 struct sockaddr_in socketaddr;
 socklen_t lgr = sizeof(struct sockaddr_in);
 int socketService;
 socketService = accept_rs( globalData->socketTCP, (struct sockaddr *) &socketaddr, &lgr);
     if(socketService != -1){
       if( storeAccept(socketService, globalData) == -1){perror("storeAccept\n");}
     
   }else{perror("accept");exit(EXIT_FAILURE);}
   printf("numero de socket : %d\n", globalData->tabAccepts[0].socket);
   printf("Connexion acceptée\n");
  //while((num =readString(socketService, mes, 255))<1);
  //num=readString(socketService, mes, sizeof(int)+2*sizeof(float)+3*sizeof(char));
 //printf("%d & %d\n",num,sizeof(int)+2*sizeof(float)+3*sizeof(char));
 /* sscanf(mes,"%d:%f:%f\0", &num, &x, &z);
  printf("toto\n");
  mes[0]=(char)num;
  mes[1]='\0';
  //w1->creerfaune(AVATAR, mes, x, z);
  sprintf(mes,"%d:%d:%d:%f:%f\0",CREE,AVATAR,num,x,z);
  SendAllTCP(mes,globalData);*/


}

void 
Serveur::ReceiveAllTCP(fd_set *rdFds, struct global *globalData)
{
   int i;
   char chaine[SIZE];
   //printf("nb sessions %d", globalData->nbAccepts);
   for(i=0;i<globalData->nbAccepts;i++) {
     if(FD_ISSET(globalData->tabAccepts[i].socket,rdFds)) {

	//print(stderr,"Reception message\n");
	int tmp = readString(globalData->tabAccepts[i].socket,chaine, SIZE);
        while(tmp < 1) {
		if(tmp==-1) {removeAccept(i,globalData);delete w1->_faune[AVATAR][i]; break;}
		tmp = readString(globalData->tabAccepts[i].socket,chaine, SIZE);
	};
	if (tmp!=-1) {
		fprintf(stderr, "Message recu par le serveur : %s\n", chaine);
		int action, type, numero;
		float x, z;
		sscanf(chaine,"%d:%d:%d:%f:%f\0",&action, &type, &numero, &x, &z);
		switch(action){
		case DEPLACE : w1->deplacer(type,numero, x, z);
			SendAllTCP(chaine, globalData);
			break;
		}
	}
     }
  }
}



void Serveur::SendAllTCP(char *phrase, struct global *globalData)
{
  int i = 0;

  for( i = 0 ; i < globalData->nbAccepts ; i++ ){
       //fprintf(stdout,"chaine envoyee %s sur socket %d \n", phrase, globalData->tabAccepts[i].socket);
     if(writeString(globalData->tabAccepts[i].socket, phrase) != (ssize_t)strlen(phrase)+1){
       removeAccept(i,globalData);
     }//else{print(stdout,"chaine envoyÃ©e sur socket %d \n",globalData->tabAccepts[i].socket);}
  }
}

void
Serveur::connexion(World * world){

 globalData.portTCP = PORT_SERVEUR;
 w1=world;

 InitServeurTCP(&globalData);
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
Serveur::run(void){


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
 nbSecondTimeOut=10;
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

   FD_SET(globalData.socketTCP,&rdFds);
   if (globalData.socketTCP>fdMax) fdMax = globalData.socketTCP;

   for(i=0;i<globalData.nbAccepts;i++)
     {
     FD_SET(globalData.tabAccepts[i].socket,&rdFds);
     if (globalData.tabAccepts[i].socket>fdMax) fdMax = globalData.tabAccepts[i].socket;
     }

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
   	    if( (timerSend++) == SEND){/*printf("%d\n",timerSend);*/timerSend=0;/*envoyer notre 	position*/
		char message[255];
	    sprintf(message,"%d:%d:%d:%f:%f\0",DEPLACE,AVATAR,w1->getwhoiam(),
			w1->_cameraW->getPosX(),w1->_cameraW->getPosZ());
	    SendAllTCP(message, &globalData);
static int g_timeAtLastFrame=0;
		int currentTime = glutGet(GLUT_ELAPSED_TIME);
		int frameInterval = currentTime - g_timeAtLastFrame;
		char mes1[255];//= (char*)malloc((sizeof(int)+2*sizeof(float))*(_nbproie) + 2*sizeof(int)+sizeof(char));
		char mes2[255];//= (char*)malloc((sizeof(int)+2*sizeof(float))*(_nbpredateur) + 2*sizeof(int)+sizeof(char));
	
		g_timeAtLastFrame = currentTime;
	
			float y1,y2, x,z,speed = (float)frameInterval /SPEED;
			srand(time(NULL)); 
			//sprintf(mes1,"%d%d",PROIE,_nbproie);
			for(int i=0; i< w1->_nbproie;i++){
				y1=(((float)rand()/(float)RAND_MAX)-0.5)*speed;
				y2=(((float)rand()/(float)RAND_MAX)-0.5)*speed;
				x=w1->_faune[PROIE][i]->getx();
				z=w1->_faune[PROIE][i]->getz();
				if(((x+y1)>-(w1->taille()/2))&&((x+y1)<(w1->taille()/2))) x+=y1;//+speed;
				if(((z+y2)>-(w1->taille()/2))&&((z+y2)<(w1->taille()/2))) z+=y2;//+speed;
				sprintf(mes1,"%d:%d:%d:%f:%f",DEPLACE,PROIE,i,x,z);
				//sscanf(chaine,"%d:%d:%d:%f:%f\0",&action, &type, &numero, &x, &z);
				w1->_faune[PROIE][i]->deplacer( x, z,w1->hauteur(x,z));
				SendAllTCP(mes1, &globalData);
			}
			//sprintf(mes1,"%s\0",mes1);
			//printf("%s\n",mes1);
			
			w1->manger();
			//sprintf(mes2,"%d%d",PREDATEUR,_nbpredateur);
			for(int i=0; i< w1->_nbpredateur;i++){
				y1=(((float)rand()/(float)RAND_MAX)-0.5)*speed;
				y2=(((float)rand()/(float)RAND_MAX)-0.5)*speed;
				x=w1->_faune[PREDATEUR][i]->getx();
				z=w1->_faune[PREDATEUR][i]->getz();
				if(((x+y1)>-(w1->taille()/2))&&((x+y1)<(w1->taille()/2))) x+=y1;//+speed;
				if(((z+y2)>-(w1->taille()/2))&&((z+y2)<(w1->taille()/2))) z+=y2;//+speed;
				sprintf(mes2,"%d:%d:%d:%f:%f",DEPLACE,PREDATEUR,i,x,z);
				//sprintf(mes2,"%s%d%f%f",mes2,_nbpredateur,x,z);
				w1->_faune[PREDATEUR][i]->deplacer( x, z,w1->hauteur(x,z));
				SendAllTCP(mes2, &globalData);
			}
			w1->manger();
			
			//sprintf(mes2,"%s\0",mes2);
			//printf("%s\n\n\n",mes2);
		}
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

      if(FD_ISSET(globalData.socketTCP,&rdFds)){
	AcceptConnectionTCP( &globalData);
      }
	ReceiveAllTCP(&rdFds, &globalData);
	//parconr du f
     //if(FD_ISSET(globalData.socketUDP,&rdFds)){
     //	ReceptionBroadcast(&globalData);
     //}
    }


	//if( (timerSend) == SEND){
		
	//}
}







