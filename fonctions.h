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
:référent Elliot Curvat
:entree scsv*adr:char, colonne : int, position : int, cara : char
:pre-cond 
:sortie aucune
:post-cond le caractère cara a été ajouté à la position position dans la catégorie colonne de la structure qui a pour adresse scsv*adr
*/
void ajoutcara(scsv *adr, int colonne, int position, char cara);

/**
:référent Elliot Curvat et Kieran Limbourg
:entree scsv*adr:char
:pre-cond 
:sortie aucune
:post-cond la ligne qui a pour adresse scsv*adr a été affichée dans le terminal
*/
void printligne(scsv *adr);

/**
:référent Elliot Curvat
:entree aucune
:pre-cond aucune
:sortie aucune
:post-cond le contenu du terminal a été effacé
*/
void clrscr();

/**
:référent Elliot Curvat
:entree aucune
:pre-cond aucune
:sortie selection:int
:post-cond les choix ont été affichés et l'utilisateur a entré un choix
*/
int seleccategorie();

/**
:référent Elliot Curvat
:entree scsv*adr:char, numcat:int
:pre-cond 0<=numcat<=6
:sortie un pointeur de type char
:post-cond l'adresse retournée correspond à celle de la catégorie entrée
*/
char *adrfromnumcat(scsv *adr, int numcat);

/**
:référent Elliot Curvat
:entree numcat:int
:pre-cond 0<=numcat<=6
:sortie char
:post-cond la catégorie qui est retournée correspond bien au numéro associé
*/
char *catefromnum(int numcat);

/**
:référent Elliot Curvat
:entree scsv*personne:char
:sortie int
:post-cond la valeur a la catégorie souhaitée a été remplacée par l'entrée de l'utilisateur
*/
int modifval(scsv *personne);

/**
:référent Elliot Curvat
:entree tabstruct:tableau de scsv, indices: tableau d'int, nbligne: int, cat: int
:post-cond tabstruct n'a pas été modifié, indices contient les indices des éléments de tabstruct triés par ordre croissant suivant la catégorie cat
*/
void tri_insertion_indirect(scsv tabstruct[], int indices[], int nbligne, int cat);