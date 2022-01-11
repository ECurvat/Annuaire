#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "fonctions.h"

int main()
{
	char tab[200]; // Buffer lors de l'ouverture du fichier
	int nbcol = 0; // La colonne a laquelle on se trouve lors de l'ouverture du fichier
	int nbligne = 0; // Le nombre de clients dans l'annuaire
	// si il y a 4999 lignes dans le csv, nbligne sera a 4998 (nbligne commence a 0)
	int i, j, k; // Pour les boucles ou du stockage de nombre de clients
	int categorie; // Categorie selectionnee par client (nom, prenom...)
	int retour1, retour2, retour3; // Resultats des fonctions strlen ou strcasecmp
	int indices[6000]; // Pour le tri par insertion indirect
	int idclient; // Choix du client (pour modifier, supprimer...) lors d'une recherche
	int choix1, choix2, choix3, choix4; // Choix pour les menus	
	char validation; // Pour valider un choix (par y ou n)
	char ainserer[50]; // Valeur a inserer lors de la modification d'un client
	char nomfichier[50]; // Nom du fichier pour la sauvegarde	
	char chemin[100]; // Pour le nom du fichier à ouvrir	
	
	// Pour les recherches
	char recherche[50], recherche1[50], recherche2[50], recherche3[50];
	char premlet;

	// Pour chronométrer les temps d'exécution
	clock_t start, end;
	int elapsed;

// Debut du programme
	printf("Entrer le nom du fichier (avec extension) a lire : ");
	fflush(stdin);
	fgets(chemin, 100, stdin);
	chemin[strlen(chemin) - 1] = '\0';

	// On cree un tableau qui contient une structure par case --> eviter de faire une structure par personne pour 5000 personnes
	scsv tabstruct[6000];
	start = clock();
	FILE *fic = fopen(chemin, "r");
	// Si le fichier est vide, on arrete le programme tout de suite
	if (fic == NULL)
		exit(EXIT_FAILURE);

	// Lecture de chaque ligne une par une
	while (fgets(tab, sizeof(tab), fic) != NULL)
	{
		// On reinitialise nbcol a chaque nouvelle lecture de ligne
		nbcol = 0;
		j = 0;
		// On parcourt chaque ligne
		for (i = 0; tab[i] != '\0'; i++)
		{
			// Dans le parcourt de chaque ligne, on execute le code dessous si on trouve une ,
			// Permet de changer la categorie, de remplir le tableau  de structures
			if (tab[i] == ',' || tab[i] == '\n')
			{
				// On ajoute un \0 avant de passer a la categorie suivante quand on detecte une ,
				// But = reduire les bugs possibles
				// On augmente nbcol pour savoir a quelle categorie on se trouve (nom, prenom...)
				ajoutcara(&(tabstruct[nbligne]), nbcol, j, '\0');
				nbcol++;
				j = 0;
			}
			else
			{
				// On appelle la fonction ajoutcara pour ajouter chaque caractere (tab[i]) un par un dans la bonne structure a la bonne colonne (categorie) et au bon indice de tableau de categorie
				// Il faut envoyer les caracteres un par un, donc on utilise j qui est reinitialise a chaque nouvelle virgule
				ajoutcara(&(tabstruct[nbligne]), nbcol, j, tab[i]);
				j++;
			}
		}
		nbligne++;
	}
	// Pour enlever l'ajout de ligne final qui permet de terminer la boucle --> la derniere valeur de nbligne est une ligne qui n'existe pas
	nbligne--;
	// On ferme le fichier quand on a fini de remplir le tableau de structures contenant toutes les lignes
	fclose(fic);
	end = clock();

	// Calcul et affichage de la durée d'ouverture du fichier
	elapsed = ((double)end - start) / CLOCKS_PER_SEC * 1000;
	printf("L'ouverture a pris %d ms.\n", elapsed);

	// Remplissage du tableau d'indices (tri)
	for (int k = 0; k <= nbligne; k++)
	{
		indices[k] = k;
	}

	// Menu principal
	do
	{
		printf("Menu principal\n");
		printf("\t0 -- Rechercher parmi les clients\n");
		printf("\t1 -- Modifier l'annuaire de clients\n");
		printf("\t2 -- Trier le tableau\n");
		printf("\t3 -- Sauvegarder l'annuaire\n");
		printf("\t4 -- Quitter le programme\n");
		scanf("%d", &choix1);
		clrscr();
		switch (choix1)
		{
		case 0:
			// Rechercher parmi les clients
			do
			{
				printf("Rechercher parmi les clients\n");
				printf("\t\t0 -- Afficher tous les clients\n");
				printf("\t\t1 -- Afficher les clients remplissant un critere\n");
				printf("\t\t2 -- Afficher un client particulier\n");
				printf("\t\t3 -- Afficher les clients pour lesquels il manque une information\n");
				printf("\t\t4 -- Retour au menu precedent\n");
				scanf("%d", &choix2);
				clrscr();
				switch (choix2)
				{
				case 0:
					// Afficher tous les clients
					start = clock();
					for (i = 0; i <= nbligne; i++)
						printligne(&(tabstruct[indices[i]]));
					end = clock();
					elapsed = ((double)end - start) / CLOCKS_PER_SEC * 1000;
					printf("L'affichage a pris %d ms.\n", elapsed);
					break;
				case 1:
					do
					{
						printf("Afficher les clients remplissant un critere\n");
						printf("\t\t\t0 -- Critere sur le prenom\n");
						printf("\t\t\t1 -- Critere sur le nom\n");
						printf("\t\t\t2 -- Critere sur la ville\n");
						printf("\t\t\t3 -- Critere sur le code postal\n");
						printf("\t\t\t4 -- Critere sur le numero de telephone\n");
						printf("\t\t\t5 -- Critere sur l'adresse mail\n");
						printf("\t\t\t6 -- Critere sur le metier\n");
						printf("\t\t\t7 -- Retour au menu precedent\n");
						scanf("%d", &choix3);
						if (choix3 <= 6 && choix3 >= 0)
						{
							printf("\t\t\t\t0 -- Commence par...\n");
							printf("\t\t\t\t1 -- Contient...\n");
							printf("\t\t\t\t2 -- Est exactement...\n");
							scanf("%d", &choix4);
							switch (choix4)
							{
							case 0:
								// Rechercher un client dont une information commence par
								printf("Saisir un caractere\n");
								fflush(stdin);
								scanf("%c", &premlet);
								start = clock();
								for (i = 0; i <= nbligne; i++)
								{
									if (adrfromnumcat(&tabstruct[i], choix3)[0] == premlet)
										printligne(&tabstruct[indices[i]]);
								}
								end = clock();
								elapsed = ((double)end - start) / CLOCKS_PER_SEC * 1000;
								printf("La recherche a pris %d ms.\n", elapsed);
								break;
							case 1:
								// Rechercher un client dont une information contient
								printf("Saisir la recherche sur le critere\n");
								scanf(" %s", recherche);
								start = clock();
								for (k = 0; k <= nbligne; k++)
								{
									char *retour4 = strstr(adrfromnumcat(&tabstruct[k], choix3), recherche);
									if (retour4)
									{
										printf("ID : %d ", k);
										printligne(&tabstruct[indices[k]]);
									}
								}
								end = clock();
								elapsed = ((double)end - start) / CLOCKS_PER_SEC * 1000;
								printf("La recherche a pris %d ms.\n", elapsed);
								break;
							case 2:
								// Rechercher un client dont une information est exactement
								printf("Saisir la recherche sur le critere (sensible a la casse)\n");
								scanf(" %s", recherche);
								start = clock();
								for (k = 0; k <= nbligne; k++)
								{
									retour1 = strcasecmp(adrfromnumcat(&tabstruct[k], choix3), recherche);
									if (retour1 == 0)
									{
										printf("ID : %d ", k);
										printligne(&tabstruct[indices[k]]);
									}
								}
								end = clock();
								elapsed = ((double)end - start) / CLOCKS_PER_SEC * 1000;
								printf("La recherche a pris %d ms.\n", elapsed);
								break;
							default:
								break;
							}
						}
					} while (choix3 <= 6 && choix3 >= 0);
					break;
				case 2:
					// Rechercher un client par plusieurs informations à la fois
					do
					{
						printf("Afficher un client particulier\n");
						printf("\t\t\t0 -- Rechercher avec prenom, nom et adresse mail\n");
						printf("\t\t\t1 -- Rechercher avec prenom, nom et numero de telephone\n");
						printf("\t\t\t2 -- Retour au menu precedent\n");
						scanf("%d", &choix3);
						clrscr();
						switch (choix3)
						{
						case 0:
							// Recherche un client avec prenom, nom et adresse mail
							printf("Saisir le prenom\n");
							scanf(" %s", recherche1);
							printf("Saisir le nom\n");
							scanf(" %s", recherche2);
							printf("Saisir l'adresse mail\n");
							scanf(" %s", recherche3);
							start = clock();
							for (k = 0; k <= nbligne; k++)
							{
								int retour1 = strcasecmp(tabstruct[k].prenom, recherche1);
								int retour2 = strcasecmp(tabstruct[k].nom, recherche2);
								int retour3 = strcasecmp(tabstruct[k].mail, recherche3);
								if (retour1 == 0 && retour2 == 0 && retour3 == 0)
								{
									printf("ID : %d -- ", k);
									printligne(&tabstruct[indices[k]]);
								}
							}
							end = clock();
							elapsed = ((double)end - start) / CLOCKS_PER_SEC * 1000;
							printf("La recherche a pris %d ms.\n", elapsed);
							break;
						case 1:
							// Rechercher un client avec prenom, nom et numero de telephone
							printf("Saisir le prenom\n");
							scanf(" %s", recherche1);
							printf("Saisir le nom\n");
							scanf(" %s", recherche2);
							printf("Saisir le numero de telephone\n");
							scanf(" %s", recherche3);
							start = clock();
							for (k = 0; k <= nbligne; k++)
							{
								int retour1 = strcasecmp(tabstruct[k].prenom, recherche1);
								int retour2 = strcasecmp(tabstruct[k].nom, recherche2);
								int retour3 = strcasecmp(tabstruct[k].tel, recherche3);
								if (retour1 == 0 && retour2 == 0 && retour3 == 0)
								{
									printf("ID : %d -- ", k);
									printligne(&tabstruct[indices[k]]);
								}
							}
							end = clock();
							elapsed = ((double)end - start) / CLOCKS_PER_SEC * 1000;
							printf("La recherche a pris %d ms.\n", elapsed);
							break;
						default:
							break;
						}
					} while (choix3 <= 1 && choix3 >= 0);
					break;
				case 3:
					// Afficher les clients pour lesquels il manque une information
					do
					{
						printf("Afficher les clients pour lesquels il manque une information\n");
						printf("\t\t\t0 -- Afficher tous les clients auxquels il manque une information\n");
						printf("\t\t\t1 -- Afficher les clients auxquels il manque une information specifique\n");
						printf("\t\t\t2 -- Retour au menu precedent\n");
						scanf("%d", &choix3);
						clrscr();
						switch (choix3)
						{
						case 0:
							// Afficher les clients auxquels il manque au moins une information
							start = clock();
							i = 0; // Compteur de personnes a qui il manque au moins une information
							for (k = 0; k <= nbligne; k++)
							{
								for (j = 0; j <= 6; j++)
								{
									retour1 = strlen(adrfromnumcat(&tabstruct[k], j));
									if (retour1 == 0)
									{
										printf("ID : %d -- ", k);
										printligne(&tabstruct[indices[k]]);
										i++;
										break;
									}
								}
							}
							end = clock();
							elapsed = ((double)end - start) / CLOCKS_PER_SEC * 1000;
							printf("La recherche a pris %d ms.\n", elapsed);
							printf("Il manque au moins une information a %d clients sur %d clients presents dans l'annuaire\n", i, nbligne + 1);
							break;
						case 1:
							// Afficher les clients auxquels il manque une information specifique
							printf("Afficher les clients auxquels il manque une information specifique\n");
							printf("\t\t\t0 -- Critere sur le prenom\n");
							printf("\t\t\t1 -- Critere sur le nom\n");
							printf("\t\t\t2 -- Critere sur la ville\n");
							printf("\t\t\t3 -- Critere sur le code postal\n");
							printf("\t\t\t4 -- Critere sur le numero de telephone\n");
							printf("\t\t\t5 -- Critere sur l'adresse mail\n");
							printf("\t\t\t6 -- Critere sur le metier\n");
							printf("\t\t\t7 -- Retour au menu precedent\n");
							scanf("%d", &choix4);
							if (choix4 <= 6 && choix4 >= 0)
							{
								start = clock();
								for (k = 0; k <= nbligne; k++)
								{
									if (strlen(adrfromnumcat(&tabstruct[k], choix4)) == 0)
									{
										printf("ID : %d -- ", k);
										printligne(&tabstruct[indices[k]]);
									}
								}
								end = clock();
								elapsed = ((double)end - start) / CLOCKS_PER_SEC * 1000;
								printf("La recherche a pris %d ms.\n", elapsed);
							}
							break;
						default:
							break;
						}
					} while (choix3 <= 1 && choix3 >= 0);
					break;
				default:
					break;
				}
			} while (choix2 <= 3 && choix2 >= 0);
			break;
		case 1:
			// Modifier l'annuaire des clients (ajout, modification, suppression)
			do
			{
				printf("Modifier l'annuaire des clients\n");
				printf("\t\t0 -- Ajouter un client\n");
				printf("\t\t1 -- Modifier un client\n");
				printf("\t\t2 -- Supprimer un client\n");
				printf("\t\t3 -- Retour au menu precedent\n");
				scanf("%d", &choix2);
				clrscr();
				switch (choix2)
				{
				case 0:
					// Ajouter un client
					nbligne++;
					for (i = 0; i <= 6; i++)
					{
						printf("Information a saisir [%s] : ", catefromnum(i));
						fflush(stdin);
						fgets(adrfromnumcat(&tabstruct[nbligne], i), 50, stdin);
						adrfromnumcat(&tabstruct[nbligne], i)[strlen(adrfromnumcat(&tabstruct[nbligne], i)) - 1] = '\0';
					}
					printligne(&tabstruct[nbligne]);

					indices[nbligne] = nbligne;
					break;
				case 1:
					// Modifier un client (inclus une recherche)
					printf("Recherche du client par :\n");
					categorie = seleccategorie();
					printf("Saisir les occurrences a afficher\n");
					scanf(" %s", recherche);
					k = 0;
					for (k = 0; k <= nbligne; k++)
					{
						retour1 = strcasecmp(adrfromnumcat(&tabstruct[k], categorie), recherche);
						if (retour1 == 0)
						{
							printf("ID : %d ", k);
							printligne(&tabstruct[indices[k]]);
						}
					}
					printf("Selectionner l'id du client que vous voulez modifier\n");
					scanf("%d", &idclient);
					printf("Vous allez modifier ce client :\n");
					printligne(&tabstruct[idclient]);
					do
					{
						categorie = modifval(&tabstruct[idclient]);
					} while (categorie >= 0 && categorie <= 6);
					break;
				case 2:
					// Supprimer un client (inclus une recherche)
					printf("Recherche du client par :\n");
					categorie = seleccategorie();
					printf("Saisir les occurrences a afficher\n");
					scanf(" %s", recherche);
					for (k = 0; k <= nbligne; k++)
					{
						retour1 = strcasecmp(adrfromnumcat(&tabstruct[k], categorie), recherche);
						if (retour1 == 0)
						{
							printf("ID : %d -- ", k);
							printligne(&tabstruct[indices[k]]);
						}
					}
					printf("Selectionner l'id du client que vous voulez supprimer\n");
					scanf("%d", &idclient);
					printf("etes-vous certain de vouloir supprimer ce client (y/n) ? Cette action est irreversible\n");
					scanf(" %c", &validation);
					if (validation == 'y')
					{
						for (i = idclient; i <= nbligne; i++)
							tabstruct[i] = tabstruct[i + 1];
						nbligne--;
						printf("Succes de l'operation\n");
						printf("Il reste %d clients dans l'annuaire.\n", nbligne);
					}
					else
						printf("Annulation de l'operation\n");
					break;
				default:
					break;
				}
			} while (choix2 <= 2 && choix2 >= 0);
			break;
		case 2:
			// Tri du tableau
			printf("Trier le tableau par :\n");
			categorie = seleccategorie();
			start = clock();
			tri_insertion_indirect(tabstruct, indices, nbligne, categorie);
			end = clock();
			elapsed = ((double)end - start) / CLOCKS_PER_SEC * 1000;
			printf("Le tri a pris %d ms.\n", elapsed);
			break;
		case 3:
			// Sauvegarder l'annuaire
			do
			{
				printf("Sauvegarder l'annuaire\n");
				printf("\t\t\t0 -- Je souhaite faire la sauvegarde dans l'annuaire actuel\n");
				printf("\t\t\t1 -- Je souhaite faire la sauvegarde dans un nouvel annuaire\n");
				printf("\t\t\t2 -- Revenir au menu precedent\n");
				scanf("%d", &choix2);
				clrscr();
				switch (choix2)
				{
				case 0:
					// Sauvegarde dans l'annuaire actuel
					printf("etes-vous certain de vouloir ecraser l'annuaire actuel (y/n) ? Cette action est irreversible\n");
					scanf(" %c", &validation);
					if (validation == 'y')
					{
						FILE *fic = fopen(chemin, "w");
						for (i = 0; i <= nbligne; i++)
						{
							for (j = 0; j <= 5; j++) // 0 à 5 pour print la dernière ligne sans la virgule
							{
								fprintf(fic, "%s,", adrfromnumcat(&tabstruct[indices[i]], j));
							}
							fprintf(fic, "%s\n", adrfromnumcat(&tabstruct[indices[i]], j));
						}
						fclose(fic);
						printf("Sauvegarde effectuee avec succes\n");
					}
					else
						printf("Annulation de l'operation\n");
					break;
				case 1:
					// Sauvegarde dans un nouvel annuaire
					printf("Saisir le nom du nouvel annuaire avec l'extension\n");
					printf("Attention, si le fichier existe deja, son contenu sera efface\n");
					fflush(stdin);
					fgets(nomfichier, 50, stdin);
					nomfichier[strlen(nomfichier) - 1] = '\0';
					FILE *save = fopen(nomfichier, "w"); // W pcq on veut creer un nouveau fichier et avoir le curseur au debut
					for (i = 0; i <= nbligne; i++)
					{
						for (j = 0; j <= 5; j++) // 0 à 5 pour print la dernière ligne sans la virgule
						{
							fprintf(fic, "%s,", adrfromnumcat(&tabstruct[indices[i]], j));
						}
						fprintf(fic, "%s\n", adrfromnumcat(&tabstruct[indices[i]], j));
					}
					fclose(save);
					printf("Sauvegarde effectuee avec succes\n");
					break;
				default:
					break;
				}
			} while (choix2 <= 1 && choix2 >= 0);
			break;
		case 4:
			// Quitter le programme
			exit(EXIT_SUCCESS);
			break;
		default:
			break;
		}
	} while (choix1 <= 4 && choix1 >= 0);
	return 0;
}