

typedef struct Livre{
	int id;
	char * nom;
	char * description;
	char * autheur;
	Cat* cat;
	struct Livre* suivant;
}Livre;

typedef struct Livres {
	Livre* premier;
	int nbr;
	int max;
	int* livres_sorties;
}Livres;


Livres* LIVRES;


Livre* cree_livre(int,int,char*,char*,char*);
void ajouter_livre();
int  ajouter_livre_fichier(Livre*);
void ajouter_livre_a_list(Livre*);
void afficher_livre(Livre*);
void afficher_livres();
void afficher_livres_cat(int);
int  compter_livres_cat(int);
int  lire_livres();
int  suppr_livre(Livre*);
int  suppr_livre_fichier(int);
int  suppr_livre_de_list(int);
void vider_livres();
Livre* trouver_livre_par_id(int);
Livre* trouver_livre_par_titre(char*);
int  chercher_par_titre_desc(char*);
int  chercher_par_autheur(char*);


Livre* cree_livre(int i,int c, char* n, char* d, char* a){
	Livre* l = (Livre*) malloc(sizeof(Livre));
	l->id = i;
	Cat* cat = trouver_cat_par_id(c);
	if(!cat){
		printf("categorie non trouvee\n");
		return NULL;
	}
	l->cat = cat;
	l->nom = (char*) malloc(strlen(n)*sizeof(char)+1);
	l->description = (char*) malloc(strlen(d)*sizeof(char)+1);
	l->autheur = (char*) malloc(strlen(a)*sizeof(char)+1);
	strcpy(l->nom,n);
	strcpy(l->description,d);
	strcpy(l->autheur,a);
	l->suivant = NULL;
	return l;
}

void ajouter_livre_a_list(Livre* c){
	if (LIVRES->premier == NULL ){
		LIVRES->premier = c;
		return;
	}
	Livre* tmp = LIVRES->premier;
	while(tmp->suivant) tmp = tmp->suivant;
	tmp->suivant = c;
	LIVRES->nbr++;
}

void afficher_livre(Livre* c){
	if(c == NULL ) {
		printf("rien a  afficher\n");
		return;
	}
	color(COULEUR_VERT);
	printf("livre id : %d\n",c->id);
	color(COULEUR_JAUNE);
	printf("titre    : %s\n",c->nom);
	printf("Autheur  : %s\n",c->autheur);
	if(c->cat){
		color(COULEUR_BLEU);
		printf("Categorie: %s\n",c->cat->nom);
	}
	color(COULEUR_BLANC);
	printf("Desc     : %s\n",c->description);

}

void afficher_livres(){
	Livre* tmp = LIVRES->premier;
	while(tmp){
		afficher_livre(tmp);
		tmp = tmp->suivant;
	}
}

void afficher_livres_cat(int id){
	Livre* tmp = LIVRES->premier;
	while(tmp){
		if(tmp->cat->id == id )afficher_livre(tmp);
		tmp = tmp->suivant;
	}
}

int compter_livres_cat(int id){
	int n = 0;
	Livre* tmp = LIVRES->premier;
	while(tmp){
		if(tmp->cat->id == id ) n++;
		tmp = tmp->suivant;
	}
	return n;
}

int lire_livres(){
	LIVRES = (Livres*) malloc(sizeof(Livres));
	FILE* livre = fopen("livres.txt","r");
	char* buffer = (char*) malloc(sizeof(char)*1024);
	if(livre == NULL ){
		printf("Erreur ouverture fichier des livres\n");
		return -1;
	}
	int max_livres = 1000;
	LIVRES->premier = NULL;
	LIVRES->nbr = 0;
	LIVRES->max = max_livres;
	LIVRES->livres_sorties = (int*) malloc(sizeof(int)*max_livres);
	for(int i = 0 ; i <max_livres ; i++ ) LIVRES->livres_sorties[i] = 0;
	int id,cat;
	char* str, *nom, *description, *autheur, *cat_s;
	while(fgets(buffer,1024,livre)!=NULL){
		str = strtok(buffer, "|");
		if(!str)continue;
		id = atoi(str);
		cat_s = strtok(NULL, "|");
		if(!cat_s)continue;
		cat = atoi(cat_s);
		nom = strtok(NULL, "|");
		if(!nom)continue;
		autheur = strtok(NULL,"|");
		if(!autheur)continue;
		description = strtok(NULL,"|");
		if(!description)continue;
		Livre* l = cree_livre(id,cat,nom,description,autheur);
		if(!l) {
			printf("\nerreur creation du live\n");
			continue;
		}
		ajouter_livre_a_list(l);
	}
	fclose(livre);
	free(buffer);
	return 0;
}

int suppr_livre(Livre* c){
	if(c){
		printf("livre %d supprime de la memoire\n",c->id);
		free(c->nom);
		free(c->description);
		free(c->autheur);
		free(c);
		c = NULL;
		return 0;
	}
	return -1;
}

int suppr_livre_de_list(int id){
    Livre *tmp = LIVRES->premier;
    if (tmp == NULL) {
        printf("La liste des livres est vide!\n");
        return -1;
    }
    if (tmp->id == id) {
        LIVRES->premier = tmp->suivant;
        suppr_livre(tmp);
		LIVRES->nbr--;
		return 0;
    }
    while (tmp->suivant != NULL) {
        if (tmp->suivant->id == id) {
            Livre *a_supprimer = tmp->suivant;
            tmp->suivant = tmp->suivant->suivant;
            suppr_livre(a_supprimer);
	    	LIVRES->nbr--;
	    	return 0;
        }
        tmp = tmp->suivant;
    }
    if(id) printf("Le livre avec l'ID %d n'existe pas dans la liste!\n", id);
    return -1;
}


void ajouter_livre(){
	int max_id = 0;
	Livre* tmp = LIVRES->premier;
	while (tmp){
	   if( tmp->id > max_id ) max_id = tmp->id;
	   tmp = tmp->suivant;
	}
	max_id++;
	char nom[50];
	char autheur[50];
	char desc[1024];
	int c;

	printf("Donner l'id de la Categorie du livre: ");
	scanf("%d",&c);

	Cat* cat = trouver_cat_par_id(c);
	if(cat == NULL ) {
		printf("categorie non trouvee\n");
		return;
	}
	printf("Categorie: %s\n",cat->nom);
	printf("Donner le titre du livre: ");
	clear_stdin();
	fgets(nom, 50, stdin);
	nom[strcspn(nom, "\n")] = '\0';

	printf("Donner le Nom de l'autheur: ");
	clear_stdin();
	fgets(autheur, 50, stdin);
	autheur[strcspn(autheur, "\n")] = '\0';

	printf("Donner la description du livre: ");
	clear_stdin();
	fgets(desc, 1024, stdin);
	desc[strcspn(desc, "\n")] = '\0';

	Livre* l = cree_livre(max_id,cat->id,nom,desc,autheur);
	ajouter_livre_a_list(l);
	ajouter_livre_fichier(l);
}

int ajouter_livre_fichier(Livre* c){
	FILE* livref = fopen("livres.txt","a");
	char* buffer = (char*) malloc(sizeof(char)*1024);
	if(livref == NULL ){
		printf("Erreur ouverture fichier des livres\n");
		return -1;
	}
	fprintf(livref,"\n%d|%d|%s|%s|%s",c->id,c->cat->id,c->nom,c->autheur,c->description);
	fclose(livref);
	return 0;
}

int suppr_livre_fichier(int c_id){
    FILE* livref = fopen("livres.txt","r");
    if(livref == NULL ){
        printf("Erreur ouverture fichier des livres\n");
        return -1;
    }

    FILE* tempf = fopen("temp.txt", "w");
    if(tempf == NULL ){
        printf("Erreur ouverture fichier temporaire\n");
        return -1;
    }

    char str[1024];
    char *id_str;
    int id;

    char *str_copy = NULL;
    while(fgets(str, sizeof(str), livref) != NULL) {
        if (str_copy) {
            str_copy = realloc(str_copy, strlen(str) + 1);
        } else {
            str_copy = malloc(strlen(str) + 1);
        }
        strcpy(str_copy, str);
        id_str = strtok(str_copy, "|");
        id = atoi(id_str);
        if (c_id != id) {
            fputs(str, tempf);
        }
    }

    free(str_copy);
    fclose(livref);
    fclose(tempf);

    if (remove("livres.txt") != 0) {
        printf("Erreur suppression fichier livres.txt\n");
        return -1;
    }
    if (rename("temp.txt", "livres.txt") != 0) {
        printf("Erreur renommage fichier temp.txt\n");
        return -1;
    }

    return 0;
}



Livre* trouver_livre_par_id(int id){
	Livre* tmp = LIVRES->premier;
	while (tmp){
		if (tmp->id == id) break;
		tmp = tmp->suivant;
	}
	return tmp;
}


Livre* trouver_livre_par_titre(char* nom){
	Livre* tmp = LIVRES->premier;
	while (tmp){
		if (strcmp(tmp->nom,nom)==0) break;
		tmp = tmp->suivant;
	}
	return tmp;
}


int chercher_par_titre_desc(char* nom){
	Livre* tmp = LIVRES->premier;
	int c = 0;
	while (tmp){
		if(strstr(tmp->nom, nom) || strstr(tmp->description, nom)){
			afficher_livre(tmp);
			c++;
		}
		tmp = tmp->suivant;
	}
	return c;
}

int chercher_par_autheur(char* nom){
	Livre* tmp = LIVRES->premier;
	int c = 0;
	while (tmp){
		if(strstr(tmp->autheur, nom)){
			afficher_livre(tmp);
			c++;
		}
		tmp = tmp->suivant;
	}
	return c;
}

void vider_livres(){
	Livre* tmp = LIVRES->premier;
	Livre* tmp1;
	while(tmp){
		tmp1 = tmp;
		suppr_livre(tmp1);
		tmp = tmp->suivant;
	}
	free(LIVRES->livres_sorties);
	free(LIVRES);
}


