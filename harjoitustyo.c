#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct puusolmu_t {
  int luku;
  short tila; /* tasapainoilmaisin */
  struct puusolmu_t *vasen, *oikea;
} puusolmu, *puuosoitin;

void lisaa_solmu(puuosoitin *, int, int *);
void oikea_kierto(puuosoitin *, int *);
void print(puuosoitin, int space);
void vasen_kierto(puuosoitin *, int *);
void searchNode(int, puuosoitin);
puuosoitin lisaaAvaimet(int *);
puuosoitin lisaaAvaimetIlmanTulostusta(int *);

int main()
{
    int etp = 0;
    puuosoitin start = NULL;
	int number = 1;

	while (number != 0)
	{
		printf("1) Lisää avaimet tiedostosta\n");
		printf("2) Lisää yksittäinen alkio\n");
        printf("3) Hae alkiota: \n");
        printf("4) Lisää avaimet ilman välitulostuksia: \n");
		printf("0) Lopeta\n");
		scanf("%d", &number);

		switch (number)
		{
		case 1:
            start = lisaaAvaimet(&etp);
            break;
		case 2: {
            int value = 0;
			printf("Lisättävä alkio: \n");
            scanf("%d", &value);
			lisaa_solmu(&start, value, &etp);
            print(start, 10);
            printf("\n");
            printf("-----------------------------------------------\n");
            break;
            }
        case 3: {
        	int value = 0;
			printf("Haettava alkio: \n");
            scanf("%d", &value);
			searchNode(value, start);
			break;
            }
        case 4: 
            start = lisaaAvaimetIlmanTulostusta(&etp);
            break;
		case 0:
			return 1;
		
		default:
			break;
		}

	}
  return 0;
}

puuosoitin lisaaAvaimetIlmanTulostusta(int *etp){
    char fileName[80];

    printf("Tiedoston nimi: ");
    scanf("%s", fileName);
    FILE *fp = fopen(fileName, "r");
        if(fp==NULL){
            printf("Tiedostoa ei löytynyt\n");
            exit(1);
        }
    char rivi[80];
    int luvut[15000];
    int i = 0;
    while(fgets(rivi, 10, fp) != NULL) {
        int alkio = atoi(rivi);
        luvut[i] = alkio;
        i++;
    }

    *etp = 0;
    puuosoitin puu = NULL;
  
    for(i = 0; luvut[i] != 0; i++)
    {
    lisaa_solmu(&puu, luvut[i], etp);
    }
    print(puu, 10);
    printf("\n");
    printf("-----------------------------------------------\n");
  return puu;
}


puuosoitin lisaaAvaimet(int *etp){
    char fileName[80];

    printf("Tiedoston nimi: ");
    scanf("%s", fileName);
    FILE *fp = fopen(fileName, "r");
        if(fp==NULL){
            printf("Tiedostoa ei löytynyt\n");
            exit(1);
        }
    char rivi[80];
    int luvut[15000];
    int i = 0;
    while(fgets(rivi, 10, fp) != NULL) {
        int alkio = atoi(rivi);
        luvut[i] = alkio;
        i++;
    }

    *etp = 0;
    puuosoitin puu = NULL;
  
    for(i = 0; luvut[i] != 0; i++)
    {
    lisaa_solmu(&puu, luvut[i], etp);
    print(puu, 10);
    printf("\n");
    printf("-----------------------------------------------\n");
  }
  return puu;
}

void lisaa_solmu(puuosoitin *emo, int luku, int *etp)
{
  if(!(*emo))
  {
    *etp = 1;
    if(!(*emo = (puuosoitin)malloc(sizeof(puusolmu))))
    {
      perror("malloc");
      exit(1);
    }
    (*emo)->vasen = (*emo)->oikea = NULL;
    (*emo)->tila = 0;
    (*emo)->luku = luku;
  } else if(luku < (*emo)->luku)
  {
    lisaa_solmu(&(*emo)->vasen, luku, etp);
    if(*etp)
    {
      switch((*emo)->tila)
      {
        case -1:
          (*emo)->tila = 0;
          *etp = 0;
          break;
        case 0:
          (*emo)->tila = 1;
          break;
        case 1:
          vasen_kierto(emo, etp);
      }
    }
  } else if(luku > (*emo)->luku)
  {
    lisaa_solmu(&(*emo)->oikea, luku, etp);
    if(*etp)
    {
      switch((*emo)->tila)
      {
        case 1:
          (*emo)->tila = 0;
          *etp = 0;
          break;
        case 0:
          (*emo)->tila = -1;
           break;
        case -1:
          oikea_kierto(emo, etp);
      }
    }
  } else
  {
    *etp = 0;
    printf("Luku %d on jo puussa\n", luku);
  }
}

void searchNode(int data, puuosoitin start){
        puusolmu *copy = start;
        while(copy->luku != data)
        {
            /*Siirrytään puussa oikealle, koska syötetty arvo on suurempi kuin puussa oleva arvo*/
            if(copy->luku < data){
                /*Saavutetaan puun loppu ja voidaan todeta, että alkiota ei löytynyt*/
                if(copy->oikea == NULL){
                    printf("Alkiota ei löytynyt\n");
                    return;
                }
                /*Siirrytään puussa oikealle*/
                copy = copy->oikea;
            } 
            else if (copy->luku > data)
            {
                /*Saavutetaan puun loppu ja voidaan todeta, että alkiota ei löytynyt*/
                if(copy->vasen == NULL){
                printf("Alkiota ei löytynyt\n");
                return;
            }
            /*Siirrytään puussa vasemmalle */    
            copy = copy->vasen;
        }
    } printf("Alkio löytynyt!!!\n");
}

void print(puuosoitin solmu, int space) {    
    if (solmu == NULL) 
        return; 
    space += 10; 
    print(solmu->oikea, space); 
    printf("\n");
    int i; 
    for (i = 10; i < space; i++) 
        printf(" "); 
    printf("%d (%d) \n", solmu->luku, solmu->tila); 
    print(solmu->vasen, space); 
}

void vasen_kierto(puuosoitin *emo, int *etp)
{
  puuosoitin lapsi, lapsenlapsi;

  lapsi = (*emo)->vasen;
  if(lapsi->tila == 1) /* LL-kierto */
  {
    (*emo)->vasen = lapsi->oikea;
    lapsi->oikea = *emo;
    (*emo)->tila = 0;
    (*emo) = lapsi;
  } else /* LR-kierto */
  {
    lapsenlapsi = lapsi->oikea;
    lapsi->oikea = lapsenlapsi->vasen;
    lapsenlapsi->vasen = lapsi;
    (*emo)->vasen = lapsenlapsi->oikea;
    lapsenlapsi->oikea = *emo;
    switch(lapsenlapsi->tila)
    {
      case 1:
        (*emo)->tila = -1;
        lapsi->tila = 0;
        break;
      case 0:
        (*emo)->tila = lapsi->tila = 0;
        break;
      case -1:
        (*emo)->tila = 0;
        lapsi->tila = 1;
    }
    *emo = lapsenlapsi;
  }
  (*emo)->tila = 0;
  *etp = 0;
}

void oikea_kierto(puuosoitin *emo, int *etp)
{
  puuosoitin lapsi, lapsenlapsi;

/*Määritellään, että lapsi on emon oikea alkio*/
  lapsi = (*emo)->oikea;
  /*Selvitetään suunta*/
  if(lapsi->tila == -1) /* RR-kierto */
  {
    (*emo)->oikea = lapsi->vasen;
    lapsi->vasen = *emo;
    (*emo)->tila = 0;
    (*emo) = lapsi;
  } else /* RL-kierto */
  {
    lapsenlapsi = lapsi->vasen;
    lapsi->vasen = lapsenlapsi->oikea;
    lapsenlapsi->oikea = lapsi;
    (*emo)->oikea = lapsenlapsi->vasen;
    lapsenlapsi->vasen = *emo;
    /*Päivitetään alkioiden tilat riippuen lapsenlapsen alla olevista alkioista*/
    switch(lapsenlapsi->tila)
    {
      case 1:
        (*emo)->tila = 0;
        lapsi->tila = -1;
        break;
      case 0:
        (*emo)->tila = lapsi->tila = 0;
        break;
      case -1:
        (*emo)->tila = 1;
        lapsi->tila = 0;
    }
    *emo = lapsenlapsi;
  }
  (*emo)->tila = 0;
  *etp = 0;
}