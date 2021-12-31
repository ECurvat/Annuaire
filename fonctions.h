#define taillexxs 6
#define taillexs 15
#define tailles 20
#define taillem 30
#define taillel 40

typedef struct structurecsv
{
	char prenom[taillem], nom[taillem], ville[taillem], cp[taillexxs], tel[taillexs], mail[taillel], metier[tailles];
} scsv;

/**
:auteur Elliot Curvat
:entree scsv*adr:char, colonne : int, position : int, cara : char
:pre-cond 
:sortie aucune
:post-cond le caractère cara a été ajouté à la position position dans la catégorie colonne de la structure qui a pour adresse scsv*adr
*/
void ajoutcara(scsv *adr, int colonne, int position, char cara);

/**
:auteur Elliot Curvat et Kieran Limbourg
:entree scsv*adr:char
:pre-cond 
:sortie aucune
:post-cond la ligne qui a pour adresse scsv*adr a été affichée dans le terminal
*/
void printligne(scsv *adr);

/**
:auteur Elliot Curvat
:entree aucune
:pre-cond aucune
:sortie aucune
:post-cond le contenu du terminal a été effacé
*/
void clrscr();

/**
:auteur Elliot Curvat
:entree aucune
:pre-cond aucune
:sortie selection:int
:post-cond les choix ont été affichés et l'utilisateur a entré un choix
*/
int seleccategorie();

/**
:auteur Elliot Curvat
:entree scsv*adr:char, numcat:int
:pre-cond 0<=numcat<=6
:sortie un pointeur de type char
:post-cond l'adresse retournée correspond à celle de la catégorie entrée
*/
char *adrfromnumcat(scsv *adr, int numcat);

/**
:auteur Elliot Curvat
:entree numcat:int
:pre-cond 0<=numcat<=6
:sortie char
:post-cond la catégorie qui est retournée correspond bien au numéro associé
*/
char *catefromnum(int numcat);

/**
:auteur Elliot Curvat
:entree scsv*personne:char
:pre-cond
:sortie int
:post-cond
*/
int modifval(scsv *personne);

void tri_insertion_indirect(scsv tabstruct[], int indices[], int nbligne, int cat);

void tri_selection(scsv (*adr)[], int nbligne);