


typedef struct Cat{
	int id;
	char * nom;
	char * description;
	struct Cat* suivante;
}Cat;

typedef struct Categories {
	Cat* premiere;
	int nbr;
}Categories;


Categories* CATEGORIES;


Cat* cree_cat(int,char*,char*);
void ajouter_cat();
int  ajouter_cat_fichier(Cat*);
void ajouter_cat_a_list(Cat*);
void afficher_cat(Cat*);
void afficher_categories();
int  lire_categoires();
int  suppr_cat(Cat*);
int  suppr_cat_fichier(int);
Cat* trouver_cat_par_id(int);
Cat* trouver_cat_par_nom(char*);
int suppr_categorie_de_list(int);
void vider_categories();


Cat* cree_cat(int i, char* n, char* d){
	Cat* c = (Cat*) malloc(sizeof(Cat));
	c->id = i;
	c->nom = (char*) malloc(strlen(n)*sizeof(char)+1);
	c->description = (char*) malloc(strlen(d)*sizeof(char)+1);
	strcpy(c->nom,n);
	strcpy(c->description,d);
	c->suivante = NULL;
	return c;
}

void ajouter_cat_a_list(Cat* c){
	if (CATEGORIES->premiere == NULL ){
		// insertion dans une list vide
		CATEGORIES->premiere = c;
		return;
	}
	Cat* tmp = CATEGORIES->premiere;
	while(tmp->suivante) tmp = tmp->suivante;
	tmp->suivante = c;
	CATEGORIES->nbr++;
}

void afficher_cat(Cat* c){
	if(c==NULL){
		printf("categorie vide");
		return;
	}
	color(COULEUR_VERT);
	printf("Categorie: %d\n",c->id);
	color(COULEUR_JAUNE);
	printf("Nom : %s\n",c->nom);
	color(COULEUR_BLANC);
	printf("Desc: %s\n",c->description);
}

void afficher_categories(){
	Cat* tmp = CATEGORIES->premiere;
	while(tmp){
		afficher_cat(tmp);
		tmp = tmp->suivante;
	}
}

int lire_categoires(){
	CATEGORIES = (Categories*) malloc(sizeof(Categories));
	FILE* cat = fopen("categories.txt","r");
	char* ligne = (char*) malloc(sizeof(char)*1024);
	if(cat == NULL ){
		printf("Erreur ouverture fichier des categories\n");
		return -1;
	}
	CATEGORIES->premiere = NULL;
	CATEGORIES->nbr = 0;
	int id;
	char* str, *nom, *description;
	while(fgets(ligne,1024,cat)!=NULL){
		str = strtok(ligne, "|");
		if(!str) continue;
		id = atoi(str);
		nom = strtok(NULL, "|");
		if(!nom) continue;
		description = strtok(NULL,"|");
		if(!description)continue;
		ajouter_cat_a_list(cree_cat(id,nom,description));
	}
	fclose(cat);
	free(ligne);
	return 0;
}

int suppr_cat(Cat* c){
	if(c){
		printf("categorie %d supprimee de memoire\n",c->id);
		free(c->nom);
		free(c->description);
		free(c);
		c = NULL;
		return 0;
	}
	return -1;
}

int suppr_categorie_de_list(int id){
    Cat *tmp = CATEGORIES->premiere;
    if (tmp == NULL) {
        printf("La liste des categories est vide!\n");
        return -1;
    }
    if (tmp->id == id) {
        CATEGORIES->premiere = tmp->suivante;
        suppr_cat(tmp);
		CATEGORIES->nbr--;
        return 0;
    }
    while (tmp->suivante != NULL) {
        if (tmp->suivante->id == id) {
            Cat *a_supprimer = tmp->suivante;
            tmp->suivante = tmp->suivante->suivante;
            suppr_cat(a_supprimer);
	    	CATEGORIES->nbr--;
            return 0;
        }
        tmp = tmp->suivante;
    }
    if(id)printf("La categorie avec l'ID %d n'existe pas dans la liste!\n", id);
    return -1;
}


Cat* trouver_cat_par_id(int id){
	Cat* tmp = CATEGORIES->premiere;
	while (tmp){
		if (tmp->id == id) break;
		tmp = tmp->suivante;
	}
	return tmp;
}


Cat* trouver_cat_par_nom(char* nom){
	Cat* tmp = CATEGORIES->premiere;
	while (tmp){
		if (strcmp(tmp->nom,nom)==0) break;
		tmp = tmp->suivante;
	}
	return tmp;
}

void ajouter_cat(){
	int max_id = 0;
	Cat* tmp = CATEGORIES->premiere;
	while (tmp){
	   if( tmp->id > max_id ) max_id = tmp->id;
	   tmp = tmp->suivante;
	}
	max_id++;
	char nom[50];
	char desc[1024];
	printf("Donner le nom de la categorie: ");
	fflush(stdin);
	fgets(nom,sizeof(nom),stdin);
	nom[strcspn(nom, "\n")] = '\0';
	printf("Donner la description de la categorie: ");
	fflush(stdin);
	fgets(desc,sizeof(desc),stdin);
	desc[strcspn(desc, "\n")] = '\0';
	Cat* c = cree_cat(max_id,nom,desc);
	ajouter_cat_a_list(c);
	ajouter_cat_fichier(c);
}

int ajouter_cat_fichier(Cat* c){
	FILE* catf = fopen("categories.txt","a");
	char* buffer = (char*) malloc(sizeof(char)*1024);
	if(catf == NULL ){
		printf("Erreur ouverture fichier des categories\n");
		return -1;
	}
	fprintf(catf,"\n%d|%s|%s",c->id,c->nom,c->description);
	fclose(catf);
	return 0;
}

int suppr_cat_fichier(int c_id){
    FILE* catf = fopen("categories.txt","r");
    if(catf == NULL ){
        printf("Erreur ouverture fichier des categories\n");
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

    if (remove("categories.txt") != 0) {
        printf("Erreur suppression fichier categories.txt\n");
        return -1;
    }
    if (rename("temp.txt", "categories.txt") != 0) {
        printf("Erreur renommage fichier temp.txt\n");
        return -1;
    }

    return 0;
}


void vider_categories(){
	Cat* tmp = CATEGORIES->premiere;
	Cat* tmp1;
	while(tmp){
		tmp1 = tmp;
		tmp = tmp->suivante;
		suppr_categorie_de_list(tmp1->id);
	}
	free(CATEGORIES);
}


