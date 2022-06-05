#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
void Liste_Disques(void);
void Afficher_Secteur(const char * disque_physique, int Num_sect) ; 
void Lire_Secteur(unsigned char **p, const char * disque_physique, int Num_sect);

void main(){
    char disque[256];
    char input[256];
    strcpy(disque, "/dev/");
    Liste_Disques();    
    printf("\nEntrez le nom du disque physique : ");
    scanf("%s", input);
    strcat(disque,input);
    Afficher_Secteur(disque, 0) ;
}



/*Lire_Secteur (disque_physique, Num_sect): Lire le secteur ayant le numéro Num_sect du
disque physique disque_physique*/
void Lire_Secteur(unsigned char **p, const char * disque_physique, int Num_sect)
{
    int i, n,s;
    unsigned char *buffer = (unsigned char*)malloc(sizeof(unsigned char)*512);
    long int a=512*Num_sect; /* secteur 10 */
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
void Afficher_Secteur(const char * disque_physique, int Num_sect){
    unsigned char *p; 
    Lire_Secteur(&p,disque_physique, Num_sect);
    for(int i=0; i<512; i++){
        if(i%16==0) printf("\n %2d : ",i/16 +1 );
        printf("%02x ", *(p+i-1));
    }
    printf("\n");
}


void Liste_Disques(void){
    void slice_str(const char * str, char * buffer, size_t start, size_t end)
    {
        size_t j = 0;
        for ( size_t i = start; i <= end; ++i ) {
            buffer[j++] = str[i];
        }
        buffer[j] = 0;
    }
    DIR* dir = opendir("/dev/");
    if (!dir) {
        perror("opendir");
        exit(1);
    }

    struct dirent* entry;

    printf("La liste des disques:\n");
    while ( (entry = readdir(dir)) != NULL) 
    {
        char dir_name[256];
        char buf[256];
        strcpy(dir_name,entry->d_name);
        slice_str(dir_name,buf,0,1);
        if (strlen(dir_name)==3 && (!strcmp("sd",buf) || !strcmp("hd",buf)))
        printf("%s\n", dir_name);
    }

    if (closedir(dir) == -1) {
        perror("closedir");
        exit(1);
    }
}
