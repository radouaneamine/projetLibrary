


typedef struct Etudiant{
	int id;
	char * nom;
	int livres[5]; // max livres un etudiant peux prendre
	struct Etudiant* suivant;
}Etudiant;

typedef struct Etudiantegories {
	Etudiant* premier;
	int nbr;
}Etudiantegories;


Etudiantegories* ETUDIANTS;


Etudiant* cree_etudiant(int,char*,int*);
void ajouter_etudiant();
int  ajouter_etudiant_fichier(Etudiant*);
void ajouter_etudiant_a_list(Etudiant*);
void afficher_etudiant(Etudiant*);
void afficher_etudiants();
int  lire_etudiants();
int  suppr_etudiant(Etudiant*);
int  suppr_etudiant_fichier(int);
Etudiant* trouver_etudiant_par_id(int);
Etudiant* trouver_etudiant_par_nom(char*);
int suppr_etudiant_de_list(int);
void vider_etudiants();
void prendre_livre(Etudiant*, int );
void retourner_livre(Etudiant*, int );


Etudiant* cree_etudiant(int i, char* n, int* l){
	Etudiant* c = (Etudiant*) malloc(sizeof(Etudiant));
	c->id = i;
	c->nom = (char*) malloc(strlen(n)*sizeof(char)+1);
	strcpy(c->nom,n);
	c->suivant = NULL;
	if(l) for(int i = 0 ; i<5 ; i++ ) c->livres[i] = l[i];
	else for(int i = 0 ; i<5 ; i++ ) c->livres[i] = 0;
	return c;
}

void ajouter_etudiant_a_list(Etudiant* c){
	if (ETUDIANTS->premier == NULL ){
		// insertion dans une list vide
		ETUDIANTS->premier = c;
		return;
	}
	Etudiant* tmp = ETUDIANTS->premier;
	while(tmp->suivant) tmp = tmp->suivant;
	tmp->suivant = c;
	ETUDIANTS->nbr++;
}

void afficher_etudiant(Etudiant* c){
	if(c==NULL){
		printf("Etudiant vide");
		return;
	}
	color(COULEUR_VERT);
	printf("Etudiant: %d - ",c->id);
	color(COULEUR_JAUNE);
	printf("Nom : %s\n",c->nom);
}

void afficher_etudiants(){
	Etudiant* tmp = ETUDIANTS->premier;
	while(tmp){
		afficher_etudiant(tmp);
		tmp = tmp->suivant;
	}
}

int lire_etudiants(){
	ETUDIANTS = (Etudiantegories*) malloc(sizeof(Etudiantegories));
	FILE* cat = fopen("etudiants.txt","r");
	char* ligne = (char*) malloc(sizeof(char)*1024);
	if(cat == NULL ){
		printf("Erreur ouverture fichier des etudiants\n");
		return -1;
	}
	ETUDIANTS->premier = NULL;
	ETUDIANTS->nbr = 0;
	int id, e_livres[5],lid;
	char* str, *nom, *livres, *l;
	Etudiant*  e;
	while(fgets(ligne,1024,cat)!=NULL){
		str = strtok(ligne, "|");
		if(!str) continue;
		id = atoi(str);
		nom = strtok(NULL, "|");
		if(!nom) continue;
		for (int i=0 ; i<5 ; i++) e_livres[i] = 0;
		livres = strtok(NULL, "|");
		if(!livres) {
			e = cree_etudiant(id,nom,NULL) ;
		}
		else {
		     l = strtok(livres,",");
		     if(l) {
			     lid = atoi(l);
			     e_livres[0] = lid;
		     }
		     for ( int  i=1 ; i<5;i++){
			     l = strtok(NULL,",");
			     if(l) {
				     lid = atoi(l);
				     e_livres[i] = lid;
			     }else {
				     break;
			     }
		     }
		     for(int j = 0 ; j <5 ; j++) {
			if(e_livres[j] != 0 ){
			     for(int i = 0 ; i<1000; i++) {
				 if(LIVRES->livres_sorties[i] == 0 ) {
					 LIVRES->livres_sorties[i] = e_livres[j];
					 break;
				 }
			     }
			}
		     }
		     e = cree_etudiant(id,nom,e_livres) ;
		}
		ajouter_etudiant_a_list(e);
	}
	fclose(cat);
	free(ligne);
	return 0;
}

int suppr_etudiant(Etudiant* c){
	if(c){
		printf("etudiant %d supprime de memoire\n",c->id);
		free(c->nom);
		free(c);
		c = NULL;
		return 0;
	}
	return -1;
}

int suppr_etudiant_de_list(int id){
    Etudiant *tmp = ETUDIANTS->premier;
    if (tmp == NULL) {
        printf("La liste des etudiants est vide!\n");
        return -1;
    }
    if (tmp->id == id) {
        ETUDIANTS->premier = tmp->suivant;
        suppr_etudiant(tmp);
		ETUDIANTS->nbr--;
        return 0;
    }
    while (tmp->suivant != NULL) {
        if (tmp->suivant->id == id) {
            Etudiant *a_supprimer = tmp->suivant;
            tmp->suivant = tmp->suivant->suivant;
            suppr_etudiant(a_supprimer);
	    	ETUDIANTS->nbr--;
            return 0;
        }
        tmp = tmp->suivant;
    }
    if(id)printf("L'etudiant avec l'ID %d n'existe pas dans la liste!\n", id);
    return -1;
}


Etudiant* trouver_etudiant_par_id(int id){
	Etudiant* tmp = ETUDIANTS->premier;
	while (tmp){
		if (tmp->id == id) break;
		tmp = tmp->suivant;
	}
	return tmp;
}


Etudiant* trouver_etudiant_par_nom(char* nom){
	Etudiant* tmp = ETUDIANTS->premier;
	while (tmp){
		if (strcmp(tmp->nom,nom)==0) break;
		tmp = tmp->suivant;
	}
	return tmp;
}

void ajouter_etudiant(){
	int max_id = 0;
	Etudiant* tmp = ETUDIANTS->premier;
	while (tmp){
	   if( tmp->id > max_id ) max_id = tmp->id;
	   tmp = tmp->suivant;
	}
	max_id++;
	char nom[50];
	printf("Donner le nom de l'etudiant: ");
	clear_stdin();
	fgets(nom,sizeof(nom),stdin);
	nom[strcspn(nom, "\n")] = '\0';
	Etudiant* c = cree_etudiant(max_id,nom,NULL);
	ajouter_etudiant_a_list(c);
	ajouter_etudiant_fichier(c);
}

int ajouter_etudiant_fichier(Etudiant* c){
	FILE* catf = fopen("etudiants.txt","a");
	char* buffer = (char*) malloc(sizeof(char)*1024);
	if(catf == NULL ){
		printf("Erreur ouverture fichier des etudiants\n");
		return -1;
	}
	fprintf(catf,"\n%d|%s",c->id,c->nom);
	char l[30];
	strcpy(l,"");
	for(int i = 0 ; i < 5 ; i++) {
		if(c->livres[i]) {
			if(strlen(l)) sprintf(l,"%s,%d",l,c->livres[i]);
			else  sprintf(l,"%d",c->livres[i]);
		}
	}
	if(strlen(l)) fprintf(catf,"|%s",l);
	fclose(catf);
	return 0;
}

int suppr_etudiant_fichier(int c_id){
    FILE* catf = fopen("etudiants.txt","r");
    if(catf == NULL ){
        printf("Erreur ouverture fichier des etudiants\n");
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
    while(fgets(str, sizeof(str), catf) != NULL) {
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
    fclose(catf);
    fclose(tempf);

    if (remove("etudiants.txt") != 0) {
        printf("Erreur suppression fichier etudiants.txt\n");
        return -1;
    }
    if (rename("temp.txt", "etudiants.txt") != 0) {
        printf("Erreur renommage fichier temp.txt\n");
        return -1;
    }

    return 0;
}


void prendre_livre(Etudiant* e , int id ){
	for(int i = 0 ; i < 5 ; i++ ) {
		if( e->livres[i] == 0 ) {
			e->livres[i] = id;
			suppr_etudiant_fichier(e->id);
			ajouter_etudiant_fichier(e);
			printf("livre %d pris par l'etudiant %s\n",id,e->nom);
			return;
		}
	}
	printf("l'etudiant %s ne peut plus prende des livres\n",e->nom);
}

void retourner_livre(Etudiant* e, int id ){
	for(int i = 0 ; i < 5 ; i++ ) {
		if( e->livres[i] == id ) {
			e->livres[i] = 0;
			suppr_etudiant_fichier(e->id);
			ajouter_etudiant_fichier(e);
			printf("livre %d retourné par l'etudiant %s\n",id,e->nom);
			return;
		}
	}
	printf("le livre %d n'est pas prix par l'etudiant %s",id, e->nom);
}

void vider_etudiants(){
	Etudiant* tmp = ETUDIANTS->premier;
	Etudiant* tmp1;
	while(tmp){
		tmp1 = tmp;
		tmp = tmp->suivant;
		suppr_etudiant_de_list(tmp1->id);
	}
	free(ETUDIANTS);
}


