#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define POCET_ZNAKU 95

int main(int argc, char *argv[])
{
	FILE * font;
	if (argc==2)
	{
		if((font = fopen("varsity.flf (2)","r"))==NULL)
		{
			printf("Spatny nazev souboru\n");
			return 1;
		}
	}
	char nazev[50]="fonts/";
	if(argc==3)
	{
		strcat(nazev,argv[2]);
		strcat(nazev,".flf (2)");
		//strcpy(argv[1],argv[2]);
		if((font = fopen(nazev,"r"))==NULL)
		{
			printf("Spatny nazev souboru\n");
			printf("%s\n", nazev);
			return 1;
		}
	}

	if(argc==1||argc>3)
	{
		printf("Bylo zadano %d argumentu, coz je spatne.",argc);
		return 1;
	}

	char hlavicka[300];
	fgets (hlavicka , 299 , font);

    typedef struct 
    {
    	int height;
    	int maxLength;
    	int komenty;
    	char mezera;
    }HLAVICKA;

    HLAVICKA mojeHlavicka;
    mojeHlavicka.mezera=hlavicka[5];

	char *pch;
	pch = strtok (hlavicka," ");
	for(short i = 0;pch != NULL; i++)
	{
		switch(i)
		{
			case 1:
				mojeHlavicka.height=atoi(pch);
				break;
			case 3:
				mojeHlavicka.maxLength=atoi(pch);
				break;
			case 5:
				mojeHlavicka.komenty=atoi(pch);
				break;
		}
		pch = strtok (NULL, " ");
	}

	char znaky[POCET_ZNAKU][/*pozice ve sloupci*/mojeHlavicka.height][/*pozice na radku*/mojeHlavicka.maxLength];
	for (int i = 0; i < POCET_ZNAKU; i++)
	{
		for (int j = 0; j < mojeHlavicka.height; j++)
		{
			for (int k = 0; k < mojeHlavicka.maxLength; k++)
			{
				znaky[i][j][k]=' ';
			}
		}
	}
	for (int i = 0; i < mojeHlavicka.komenty; i++)
	{
		fgets (hlavicka , 299 , font);
	}

	for (int i = 0; i < POCET_ZNAKU; i++)
	{
		for (int j = 0; j < mojeHlavicka.height; j++)
		{
			fgets (znaky[i][j] , 299 , font);
			for (int k = 0; k < mojeHlavicka.maxLength&&znaky[i][j][k]!='\0'; k++)
			{
				if (znaky[i][j][k]=='\n')
				{
					znaky[i][j][k]='\0';
				}
				if ((j!=0)&&((znaky[i][j][k]=='@'||(znaky[i][j][k]=='#' && strcmp(nazev,"fonts/katakana.flf (2)")))&&znaky[i][j-1][k]=='\0'))
				{
					znaky[i][j][k]='\0';
				}
				if (znaky[i][j][k]==mojeHlavicka.mezera||(znaky[i][j][k]=='#' && strcmp(nazev,"fonts/katakana.flf (2)"))||znaky[i][j][k]=='@')
				{
					znaky[i][j][k]=' ';
				}
			}
		}
	}

	if (fclose(font)==EOF)
	{
		printf("Soubor nebyl uzavren");
	}
/*	for (int i = 0; i < POCET_ZNAKU; i++)
	{
		for (int j = 0; j < mojeHlavicka.height; j++)
		{
			printf("%s\n", znaky[i][j]);
		}
		if(i%7==0)
		printf("\n");
	}*/
	/*int i = 0;
	for (int k = 0; i<POCET_ZNAKU; k++)
	{
		
	for (int j = 0; j < mojeHlavicka.height; j++)
	{
		for (i= 0 + (k*7+1); i < POCET_ZNAKU&&(i%7!=0||i==0); i++)
		{
			printf("%s", znaky[i][j]);
			printf("%d",i );
		}
		if(i%7==0||i==POCET_ZNAKU)
		{
			printf("%s\n", znaky[i][j]);
			i++;
		}
	}
	}*/
	printf("\n\n\n\n\n\n");
	/*for(int abcde = 0; abcde<7 ; abcde++)
	{
		printf("%s",znaky[52][abcde]);
		printf("%s",znaky[79][abcde]);
		printf("%s",znaky[65][abcde]);
		printf("%s",znaky[83][abcde]);
		printf("%s",znaky[84][abcde]);
		printf("%s",znaky[69][abcde]);
		printf("%s",znaky[82][abcde]);
		printf("\n");
	}
	printf("\n");
	for(int abcde = 0; abcde<7 ; abcde++)
	{
		printf("%s",znaky[45][abcde]);
		printf("%s",znaky[65][abcde]);
		printf("%s",znaky[76][abcde]);
		printf("%s",znaky[67][abcde]);
		printf("%s",znaky[69][abcde]);
		printf("%s",znaky[75][abcde]);
		printf("\n");
	}*/
	int pismeno=0;
	int pismenoCelkem=0;
	while(argv[1][pismeno]!='\0')
	{
		for (int radek = 0; radek < mojeHlavicka.height; radek++)
		{
			pismeno=pismenoCelkem;
			for(int i = 0;i<65&&argv[1][pismeno]!='\0';i+=strlen(znaky[argv[1][pismeno]-32][radek]))
			{
				printf("%s",znaky[argv[1][pismeno]-32][radek]);
				pismeno++;
			}
			printf("\n");
		}
		pismenoCelkem=pismeno;
	}
	return 0;
}


