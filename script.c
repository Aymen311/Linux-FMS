#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Liste_Disques(void);
void Afficher_Secteur(const char * disque_physique, int Num_sect) ; 
void Lire_Secteur(unsigned char **p, const char * disque_physique, int Num_sect);

void main(){
    char disque[256];
    char input[256];
    int n;
    strcpy(disque, "/dev/");
    Liste_Disques();    
    printf("\nEntrez le nom du disque physique : ");
    scanf("%s", input);
    printf("\nEntrez le numero de secteur a lire : ");
    scanf("%d" , &n);
    strcat(disque,input);
    Afficher_Secteur(disque, n) ;
}



/*Lire_Secteur (disque_physique, Num_sect): Lire le secteur ayant le numéro Num_sect du
disque physique disque_physique*/
void Lire_Secteur(unsigned char **p, const char * disque_physique, int Num_sect)
{
    int i, n,s;
    unsigned char buffer = (unsigned char)malloc(sizeof(unsigned char)*512);
    long int a=512*Num_sect; 
    FILE *disk=NULL;
    disk = fopen(disque_physique, "rb"); /* Linux */
    if(disk == NULL) printf("\n Erreur le disque physique1 n'est pas ouvert\n" );
    else{ s=fseek(disk, a, SEEK_SET); /*seek par rapport au début du fichier : 0 */
    if(s!=0) printf("\n Erreur de fseek : s= %d",s);
    else{ 
        n=fread(buffer,512, 1, disk);
        if(n<=0) printf("\n Erreur de fread = %d ",n);
        else{
        printf("Secteur %d: Nombre d'elements lus = %d\n",i,n);
        }
    }
    }
    fclose(disk);
    *p = buffer ; 
}


/*Afficher_Secteur (disque_physique, Num_sect): Appelle la fonction lire_secteur
(disque_physique, Num_sect) pour lire le secteur Num_sect et affiche son contenu en
hexadécimal.*/



void Liste_Disques(void){
    void slice_str(const char * str, char * buffer, size_t start, size_t end)
    {
        size_t j = 0;
        for ( size_t i = start; i <= end; ++i ) {
            buffer[j++] = str[i];
        }
        buffer[j] = 0;
    }
   

   FILE* ptr;
    char str[256];
    char *token;
    char buf[256];
    char name[256];
    ptr = fopen("/proc/partitions", "r");
    while (fgets(str, 50, ptr) != NULL) {
        
        token = strtok(str, " ");
       while( token != NULL ) {
        strcpy(name,token);
        token = strtok(NULL, " ");
            }
  slice_str(name,buf,0,1);
  if (strlen(name) == 4 &&(!strcmp("sd",buf) || !strcmp("hd",buf))){
              printf("%s\n",name);
       }


        }
    fclose(ptr);       
}

void Afficher_Secteur(const char * disque_physique, int Num_sect){
    unsigned char *p; 
    Lire_Secteur(&p,disque_physique, Num_sect);
    int j =0 ;
    for(int i=0; i<512; i++){
        if(i%16==0) {printf("\n %04d : ",j ); j+=16;}
        printf("%02x ", *(p+i));
    }
    printf("\n");
}
