#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ajoutcara(scsv *adr, int colonne, int position, char cara)
{
	switch (colonne)
	{
	case 0:
		(*adr).prenom[position] = cara;
		break;
	case 1:
		(*adr).nom[position] = cara;
		break;
	case 2:
		(*adr).ville[position] = cara;
		break;
	case 3:
		(*adr).cp[position] = cara;
		break;
	case 4:
		(*adr).tel[position] = cara;
		break;
	case 5:
		(*adr).mail[position] = cara;
		break;
	case 6:
		(*adr).metier[position] = cara;
		break;
	}
}

void printligne(scsv *adr)
{
	printf("%*.*s | ", -tailles, tailles, (*adr).prenom);
	printf("%*.*s | ", -tailles, tailles, (*adr).nom);
	printf("%*.*s | ", -taillexs, taillexs, (*adr).ville);
	printf("%*.*s | ", taillexxs - 1, taillexxs - 1, (*adr).cp);
	printf("%*.*s | ", -(taillexs - 1), taillexs - 1, (*adr).tel);
	printf("%*.*s | ", -taillem, taillem, (*adr).mail);
	printf("%*.*s\n", -tailles, tailles, (*adr).metier);
}

void clrscr()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

int seleccategorie()
{
	int selection;
	printf("----------------------\n");
	printf("0 pour le prenom\n");
	printf("1 pour le nom\n");
	printf("2 pour la ville\n");
	printf("3 pour le code postal\n");
	printf("4 pour le telephone\n");
	printf("5 pour l'email\n");
	printf("6 pour le metier\n");
	printf("7 pour quitter ce menu\n");
	printf("----------------------\n");
	do
		scanf("%d", &selection);
	while (selection < 0 || selection > 7);
	return selection;
}

char *adrfromnumcat(scsv *adr, int numcat)
{
	switch (numcat)
	{
	case 0:
		return (*adr).prenom;
	case 1:
		return (*adr).nom;
	case 2:
		return (*adr).ville;
	case 3:
		return (*adr).cp;
	case 4:
		return (*adr).tel;
	case 5:
		return (*adr).mail;
	case 6:
		return (*adr).metier;
	default:
		return (*adr).prenom;
		break;
	}
}

char *catefromnum(int numcat)
{
	switch (numcat)
	{
	case 0:
		return ("prenom");
		break;
	case 1:
		return ("nom");
		break;
	case 2:
		return ("ville");
		break;
	case 3:
		return ("code postal");
		break;
	case 4:
		return ("numero de telephone");
		break;
	case 5:
		return ("adresse mail");
		break;
	case 6:
		return ("metier");
		break;
	default:
		return ("erreur lors de la recuperation");
	}
}

int modifval(scsv *personne)
{
	printf("Quelle est l'information a modifier\n");
	int categorie = seleccategorie();
	if (categorie <= 6 && categorie >= 0)
	{
		// On enleve les possibles retours a la ligne qu'il y a dans stdin pour pouvoir traiter des cases vides
		fflush(stdin);
		printf("Modification de la categorie [%s] : \n", catefromnum(categorie));
		printf("Information actuelle : %s \n", adrfromnumcat(personne, categorie));
		printf("Entrer la nouvelle valeur :\n");
		fgets(adrfromnumcat(personne, categorie), 50, stdin);
		// strlen - 1 parce que c'est comme en algo, si la taille d'un tableau vaut 8, on a des cases qui vont de 0 a 7
		adrfromnumcat(personne, categorie)[strlen(adrfromnumcat(personne, categorie)) - 1] = '\0';
		printf("Client modifie avec succes :\n");
		printligne(personne);
	}
	return (categorie);
}

void tri_insertion_indirect(scsv tabstruct[], int indices[], int nbligne, int cat)
{
	int i,j;
	int petit;
	i = 1;
	while (i<=nbligne)
	{
		petit = indices[i];
		j = i - 1;
		while (j>=0 && strcasecmp(adrfromnumcat(&tabstruct[petit], cat), adrfromnumcat(&tabstruct[indices[j]], cat)) < 0)
		{
			indices[j+1] = indices[j];
			j--;
		}
		indices[j+1] = petit;
		i++;
	}
}
