#include "check.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
int ask_check_num()
{
    char num[100];
    int real_num;
    
    loop:
    clear();
    printw("check:");
    getstr(num);
    real_num=atoi(num);
    if (real_num>75)
    {
		printw("le numero %d ne figure pas dans les registres\n",real_num);
		refresh();
		napms(1000);
		goto loop;
	}
    return real_num;
}

int* alloc(int dim)
{
	int* tab=NULL;
	tab=(int*)malloc(dim*sizeof(int));
	if(tab==NULL){
		printf("allocation error");
		exit(1);
	}
	return tab;
}

int open(FILE** A)
 {
    *A=fopen("l1.csv","r+");
    return(*A==NULL)?0:1;        
}

//~ void lgoto(FILE* A,int b)
//~ {
    //~ int c,len=1;
    //~ while(len!=b)


int search_student(data* students, char part_of_name[]) {
    char part_of_name_lower[200];
    int i;

    // Convertir la partie du nom recherchée en minuscules
    to_lower_str(part_of_name_lower, part_of_name);

    // Parcourir la liste des élèves
    bool found = false;
    data results[75];
    int result_count = 0;
    for (i = 0; i < 75; i++) {
        char student_name_lower[200];
        char student_surname_lower[200];
        
        // Convertir le nom et le prénom de l'élève actuel en minuscules
        to_lower_str(student_name_lower, students[i].name);
        to_lower_str(student_surname_lower, students[i].surname);

        // Vérifier si la partie du nom recherchée est une sous-chaîne du nom ou du prénom de l'élève
        if (strstr(student_name_lower, part_of_name_lower) != NULL || strstr(student_surname_lower, part_of_name_lower) != NULL) {
            found = true;
            results[result_count++] = students[i];
        }
    }

    if (found) {
        int highlight = 0;
        int choice = -1;
        int c;

        while (choice == -1) {
            clear();
            for (i = 0; i < result_count; i++) {
                if (i == highlight) {
                    attron(A_REVERSE);
                }
                mvprintw(i, 0, "%s %s %d", results[i].name, results[i].surname, results[i].number);
                if (i == highlight) {
                    attroff(A_REVERSE);
                }
            }
            refresh();

            c = getch();
            switch (c) {
                case KEY_UP:
                    if (highlight > 0)
                        highlight--;
                    break;
                case KEY_DOWN:
                    if (highlight < result_count - 1)
                        highlight++;
                    break;
                case 10: // Enter key
                    choice = highlight;
                    break;
                case 27: // Escape key
                    choice = -2;
                    break;
                default:
                    break;
            }
        }

        if (choice >= 0) {
            clear();
            refresh();
            return results[choice].number;
        }
    } else {
        mvprintw(0, 0, "Aucun élève trouvé pour '%s'.", part_of_name);
        refresh();
        getch();
    }

    return -1; // Retourne -1 si aucun élève n'a été trouvé ou si l'utilisateur a annulé
}

    //~ {   
        //~ c=fgetc(A);
        //~ if(c=='\n')
            //~ len++;    
    //~ }
//~ }
bool lgoto(FILE* A,int b)
{
    int c;
    char s[5]=" ";
    sprintf(s,"%d ",b);
    while((c=fgetc(A))!=EOF)
    {
		if(c=='\n')
		{
			if((c=fgetc(A))==s[0])
			{
				if((c=fgetc(A))==s[1])
				{
					return true;
				}
			}
		}
	}
	rewind(A);
	return false;
}

void to_lower_str(char* dest, const char* src) {
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[i] = tolower(src[i]);
    }
    dest[i] = '\0';
}



bool name(FILE* A,int b)
{
    int c;
    lgoto(A,b);
    while((c=fgetc(A))!=':')
       addch(c);
    while((c=fgetc(A))!=':')
        addch(c);
    printw(" ");
    while((c=fgetc(A))!=':')
        addch(c);
       
	return true;
}

bool option(FILE* A)
{
	char op;
    char result[100]="";
	int b;
	b=ask_check_num();
    name(A,b);
    //printw("\n");
    mvprintw(4,0,"r:annuler\no:oui\nn:non\np:perso\nq:menu\n");
	loop:
	printw(":");
	refresh();
	op=getch();
	switch(op)
	{
            case 'r':
            ///printf("retour");
            break;
            case 'o':
            sprintf(result," OUI");
            ///printf("OUI");
            break;
            case 'n':
				sprintf(result," NON");
			//~ else
				//~ printf("deja fait");	
            break;
            case 'p':
				sprintf(result," PRS");
				///printf("PERSO");
				
			//~ else
				//~ printf("deja fait");	            
            break;
            case 'q':
            //printf("FERMETURE DU PROGRAMME\n");
            return false;
            default:
			printw("\ncommande invalide\n");
            goto loop;
            break;        
     }
     fputs(result,A);
     rewind(A);
     return(true);
}

void remplis(FILE* A)
{
	char result[]="ABSENT";
	for(int i=0 ; i<70 ; i++)
	{
		int c;
		lgoto(A,i);
		while((c=fgetc(A))!=':');
		while((c=fgetc(A))!=':');
		fputs(result,A);
	    rewind(A);
	}
		
}

bool is_in(int a,int* tab ,int dim)
{
	for(int i=0 ; i<dim ; i++)
		if(a==tab[i])
			return true;
	return (false);
}

void abs_thg()
{
	FILE *f = fopen("l1.csv", "r+");
	int c, a ,b=0; 
	while((a=fgetc(f))!=EOF)
	{
		while((c=fgetc(f))!=':' && c!=EOF) a++;
		while((c=fgetc(f))!=':' && c!=EOF) a--;
		while((c=fgetc(f))!=':' && c!=EOF) a++;
		c=fgetc(f);
		if(c==' ') 
		{
			fprintf(f,"ABS");
			b++;
		}
	}
	printf("le nombre d'absent est %d\n", b);
	rewind(f);
}

void date(const char *source, const char *dest) {
    FILE *f = fopen(source, "r");
	// find the length of the source file.
    int c; long length=0;
    while((c=fgetc(f))!=EOF) length++;


    // Allocate memory to store the source file content
    char *content = (char*)malloc(length+1);

    //alaiko any daholy alou le contenu
    //fread(content, 1, length, f);
    rewind(f);
    for (int i=0; i<length; i++)
    {
		fscanf(f,"%c",&content[i]);
	}
	//aleo terminena ihany ny stringy 
	content[length] = '\0';

    fclose(f);

    // Concatenéna maivana anle string vaovao
    char *new_content = (char *)malloc(length + strlen(__DATE__) + 1);
    
    strcpy(new_content, __DATE__);
    strcat(new_content, content);

    free(content);

    // Open the destination file in "a" mode
    FILE *fi_d = fopen(dest, "a");
 
    // alefako any daholy amzay
    //fputs(new_content, fi_d);
    
	for (int i=0; i<length + strlen(__DATE__); i++){
		fprintf(f,"%c",new_content[i]);
		}
    fclose(fi_d);
    free(new_content);
}

//~ thg;
/*------------------------------------------------------------------------------------------------------*/

int studentNumber(FILE* file) //Count number of the students in the file
{
    int count;
    char line[100];
    while(fgets(line,100,file)!=NULL)
        count++;
    rewind(file);
    return(count);
}

data* allocation(int studentsNumbers)  
{
    data* students=NULL;
    students=(data*)malloc(studentsNumbers*sizeof(data));
    return(students);
}



void getData(FILE* file, data students[])
{
    int number,i=0,name,surname,c;
    char num[4]; 
    char** splitted;
    char line[100];

    while(!feof(file))
    {
        while(!feof(file))
        {
            fgets(line,100,file);
            
            if(occurence(line,':') == 3)
            {
                splitted = split(line);
                students[i].number = atoi(splitted[0]);
                students[i].name = splitted[1];
                students[i].surname = splitted[2];            
                i++;
            }
        }
    } 
}   


char** split(char* str)
{
    char** splitted;
    int i,j=0,k=0,size;
    size=occurence(str,':');
    splitted = (char**) malloc((size+1)*sizeof(char*));

    for(int i=0; i<size+1; i++)
        splitted[i] = (char*) malloc(100*sizeof(char));

    for(i=0; i<strlen(str); i++)
    {
        if(str[i] != ':')
           splitted[j][k++] = str[i];

        else
        {
            j++;
            k=0;
        } 
    }      

    return(splitted);    
}

int occurence(char str[], char ch){
    int c=0;

    for(int i=0; i<strlen(str); i++){
        if(str[i] == ch)
            c++;
    }
    return(c);
}


/***************************************/

int menu(WINDOW* win,int count, ...)
{
	keypad(win,true);
	va_list arg;
	va_start(arg,count);
	start_color();
	init_pair (1,COLOR_BLACK,COLOR_YELLOW);
	init_pair (2,COLOR_YELLOW,COLOR_BLACK);
	
	char **argument=(char**)malloc(count*sizeof(char*));;
	int i,c,heighlight=1,y,x;
	getmaxyx(stdscr,y,x);
	for(i=0; i<count ; i++)
	{
		argument[i]=(char*)malloc(200*sizeof(char));
		sprintf(argument[i],"%s" , va_arg(arg, char*));
	}
	wattron(win, COLOR_PAIR(1));
	mvwprintw(win,0,x/2-22,"-------- %s ----------\n\n\n", argument[0]);		//titre
		for (i = 1; i < count; i++) {
        if (i == heighlight)
            wattron(win, COLOR_PAIR(1) | A_BOLD | A_DIM|A_BLINK);  
		else
			wbkgd(stdscr, COLOR_PAIR(2));		//arrrière plan
            wattron(win, COLOR_PAIR(2));
			WINDOW *window = subwin(win, 4, x - 25, i * 4, 10);  
			box(window, 0, 0);
			mvwprintw(win, i * 4 + 1, x / 2 - 10, " %s ", argument[i]);
			wrefresh(window);
			delwin(window);
        wattroff(win, A_BOLD | A_DIM|A_BLINK);
        wrefresh(win);
		}
	
	 while((c=getch())!='\n')
	{
		switch (c)
	{
		case KEY_UP:
			heighlight-=(heighlight==1)? 0:1;
			break;
		
		case KEY_DOWN:
			heighlight+=(heighlight==count-1)? 0:1;
			break;
	}for (i = 1; i < count; i++) {
        if (i == heighlight)
            wattron(win, COLOR_PAIR(1) | A_BOLD | A_DIM|A_BLINK);  
		else
			wbkgd(stdscr, COLOR_PAIR(2));				//arrrière plan
            wattron(win, COLOR_PAIR(2));
			WINDOW *window = subwin(win, 4, x - 25, i * 4, 10);  
			box(window, 0, 0);
			mvwprintw(win, i * 4 + 1, x / 2 - 10, " %s ", argument[i]);
			wrefresh(window);
			delwin(window);
        wattroff(win, A_BOLD | A_DIM|A_BLINK);
        wrefresh(win);
		}
	}
	va_end(arg);
	return heighlight;
}	
void interface()
{
	modify_langue change;
	change = modify_francais(change);	//initialisation 
	menu:
	switch(menu(stdscr,6,change.menu[0],change.menu[1],change.menu[2],change.menu[3],change.menu[4],change.menu[5]))			//ngeza ndrindra
	{
		case CHECK:																						//si check
		clear();
		check:
		switch(menu(stdscr,4,change.checker[0],change.checker[1], change.checker[2],change.checker[3]))									//faire switch
		{
			case by_num:
			clear();
			check();
			refresh();
			clear();
			goto check;
			break;
			case by_name:
			clear();
			endwin();
			name_check();
			refresh();
			clear();
			goto check;
			break;
			case go_back:
			clear();
			refresh();
			goto menu;
			break;
		}
		break;
		case LIST:
		clear();
		printw("disponible a la prochaine mise a jour");
		refresh();
		napms(1000);
		clear();
		goto menu;
		break;
		case PARCOURIR:														//si parcourir
		clear();
		parcourir:
		switch(menu(stdscr,4,change.parcourir[0],change.parcourir[1], change.parcourir[2],change.parcourir[3]))		//choisir entre
		{
			case by_num:
			clear();
			printw("petafana eto le algo an le by numero");
			refresh();
			napms(2000);
			clear();
			goto parcourir;
			break;
			case by_name:
			clear();
			printw("petafana eto le algo an le by name");
			refresh();
			napms(2000);
			clear();
			goto parcourir;
			break;
			case go_back:
			clear();
			refresh();
			goto menu;
			break;
		}
		break;
		case OPTION:																		//si option
		clear();
		option:
		switch (menu(stdscr,4,change.option[0] , change.option[1],change.option[2],change.option[3])){		//choisir entre : 
			case langue:																		// langue
			switch(menu(stdscr,5,change.langueP[0],change.langueP[1] , change.langueP[2], change.langueP[3],change.langueP[4]))
			{
				case francais:
				clear();
				printw("application des changements ...");
				change = modify_francais (change);
				refresh();
				napms(2000);
				clear();
				goto menu;
				break;
				case anglais:
				clear();
				printw("please wait");
				change = modify_anglais (change);
				refresh();
				napms(2000);
				clear();
				goto menu;
				break;
				case malagasy:
				clear();
				printw("miandrasa kely ");
				change = modify_malagasy (change);
				napms(2000);
				clear();
				goto menu;
				break;
				case goback:
				clear();
				refresh();
				goto menu;
				break;
			}
			case theme:
			clear();
			printw("theme milay be");
			refresh();
			napms(2000);
			clear();
			goto option;
			break;
			case back:
			clear();
			refresh();
			goto menu;
			break;
		}
		break;
		case QUITTER:
		clear();
		refresh();
		printw("%s.",change.quitter[0]);
		refresh();
		napms(500);
		printw(".");
		refresh();
		napms(500);
		printw(".");
		refresh();
		napms(500);
		printw(".");
		refresh();
		napms(500);
		break;
	}
	for (int i = 0; i < 6; i++) {
        free(change.menu[i]);
    }
    for (int i = 0; i < 4; i++) {
        free(change.checker[i]);
        free(change.retourner[i]);
        free(change.parcourir[i]);
        free(change.option[i]);
        free(change.langueP[i]);
    }
    free(change.quitter[0]);
    free(change.quitter);
}

///***************************************************///
	
modify_langue modify_malagasy ( modify_langue change){
	change.menu = (char**)malloc(6 * sizeof(char*));
	for (int i=0; i<6; i++){
		change.menu[i] = (char*)malloc(6 * sizeof(char)); 
	}
	if (change.menu == NULL){
		printf("erreur d'allocation ! '");
		exit(1);
	}
	strcpy(change.menu[0], " MENIO LEHIBE ");
    strcpy(change.menu[1], "tsikiro");
    strcpy(change.menu[2], "lisitra");
    strcpy(change.menu[3], "mitady");
    strcpy(change.menu[4], "safidy");
    strcpy(change.menu[5], "hiala");
    
	change.checker = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.checker[i] = (char*)malloc(4 * sizeof(char)); 
	}
	if (change.checker == NULL){
		printf("erreur d'allocation ! '");
		exit(1);
	}
	strcpy(change.checker[0], " tsikiro ");			
    strcpy(change.checker[1], " amin'ny laharana ");			
    strcpy(change.checker[2], " amin'ny anarana");
    strcpy(change.checker[3], "hiverina");

	change.retourner = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.retourner[i] = (char*)malloc(4 * sizeof(char)); 
	}
	if (change.retourner == NULL){
		printf("erreur d'allocation ! '");
		exit(1);
	}
	strcpy(change.retourner[0], " lisitra ");
    strcpy(change.retourner[1], " daty ");
    strcpy(change.retourner[2], "ankizy");
    strcpy(change.retourner[3], "hiverina");
    
        change.parcourir = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.parcourir[i] = (char*)malloc(4 * sizeof(char)); 
	}
	if (change.parcourir == NULL){
		printf("erreur d'allocation ! '");
		exit(1);
	}
	strcpy(change.parcourir[0], " mitady ");
    strcpy(change.parcourir[1], " amin'ny laharana ");
    strcpy(change.parcourir[2], " amin'ny anarana ");
    strcpy(change.parcourir[3], "hiverina");
    
    change.option = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.option[i] = (char*)malloc(4 * sizeof(char)); 
	}
	if (change.option == NULL){
			printf("erreur d'allocation ! '");
			exit(1);
		}
	strcpy(change.option[0], " safidy  ");
    strcpy(change.option[1], " fiteny  ");
    strcpy(change.option[2], " endrika ");
    strcpy(change.option[3], " hiverina");
    
    change.quitter = (char**)malloc(sizeof(char*));
	change.quitter[0] = (char*)malloc(50 * sizeof(char));
	if (change.quitter == NULL || change.quitter[0] == NULL) {
		printf("Erreur d'allocation pour change.quitter");
		exit(1);
	}
	strcpy(change.quitter[0], "quitter le programme");

    
     change.langueP = (char**)malloc(5 * sizeof(char*));
    for (int i=0; i<5; i++){
		change.langueP[i] = (char*)malloc(5 * sizeof(char)); 
	}
	if (change.langueP == NULL){
		printf("erreur d'allocation ! '");
		exit(1);
	}
	strcpy(change.langueP[0], " fiteny ");
    strcpy(change.langueP[1], " frantsay ");
    strcpy(change.langueP[2], " anglisy ");
    strcpy(change.langueP[3], " malagasy ");
    strcpy(change.langueP[4], "hiverina");
    
    return change;
}
modify_langue modify_anglais ( modify_langue change){
	change.menu= (char**)malloc(6 * sizeof(char*));
	for (int i=0; i<6; i++){
		change.menu[i] = (char*)malloc(6 * sizeof(char)); 
	}
		if (change.menu== NULL){
			printf("erreur d'allocation ! '");
			exit(1);
		}
	strcpy(change.menu[0], " MAIN");
    strcpy(change.menu[1], "check");
    strcpy(change.menu[2], "list");
    strcpy(change.menu[3], "browse");
    strcpy(change.menu[4], "option");
    strcpy(change.menu[5], "leave");
    
    change.checker = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.checker[i] = (char*)malloc(4 * sizeof(char)); 
	}
	if (change.checker == NULL){
		printf("erreur d'allocation ! ");
		exit(1);
	}
	strcpy(change.checker[0], " check ");
    strcpy(change.checker[1], " by number");			
    strcpy(change.checker[2], "by name");
    strcpy(change.checker[3], "go back");

    change.retourner = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.retourner[i] = (char*)malloc(4 * sizeof(char)); 
	}
	if (change.retourner == NULL){
		printf("erreur d'allocation !");
		exit(1);
	}
	strcpy(change.retourner[0], " LIST  ");
    strcpy(change.retourner[1], " date  ");
    strcpy(change.retourner[2], " student");
    strcpy(change.retourner[3], "go back");
    
    change.parcourir = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.parcourir[i] = (char*)malloc(4 * sizeof(char)); 
	}
	if (change.parcourir == NULL){
		printf("erreur d'allocation ! '");
		exit(1);
	}
	strcpy(change.parcourir[0], " browse  ");
    strcpy(change.parcourir[1], " by number  ");
    strcpy(change.parcourir[2], " by name ");
    strcpy(change.parcourir[3], "go back");
    
    change.option = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.option[i] = (char*)malloc(4 * sizeof(char)); 
	}
	if (change.option == NULL){
			printf("erreur d'allocation ! '");
			exit(1);
		}
	strcpy(change.option[0], " option  ");
    strcpy(change.option[1], " language ");
    strcpy(change.option[2], " theme ");
    strcpy(change.option[3], "go back");
    
    change.quitter = (char**)malloc(sizeof(char*));
	change.quitter[0] = (char*)malloc(50 * sizeof(char));
	if (change.quitter == NULL || change.quitter[0] == NULL) {
		printf("Erreur d'allocation pour change.quitter");
		exit(1);
	}
	strcpy(change.quitter[0], "leaving program");
    
    change.langueP = (char**)malloc(5 * sizeof(char*));
    for (int i=0; i<5; i++){
		change.langueP[i] = (char*)malloc(5 * sizeof(char)); 
	}
		if (change.langueP == NULL){
			printf("erreur d'allocation ! '");
			exit(1);
		}
	strcpy(change.langueP[0], " language ");
    strcpy(change.langueP[1], " french ");
    strcpy(change.langueP[2], " english ");
    strcpy(change.langueP[3], " malagasy ");
    strcpy(change.langueP[4], " go back ");
    
    return change;
}
modify_langue modify_francais ( modify_langue change){
	change.menu = (char**)malloc(6 * sizeof(char*));
	for (int i=0; i<6; i++){
		change.menu[i] = (char*)malloc(6 * sizeof(char)); 
	}
		if (change.menu == NULL){
			printf("erreur d'allocation ! '");
			exit(1);
	}
	strcpy(change.menu[0], " MENU PRINCIPALE ");
    strcpy(change.menu[1], "checker");
    strcpy(change.menu[2], "lister");
    strcpy(change.menu[3], "parcourir");
    strcpy(change.menu[4], "option");
    strcpy(change.menu[5], "quitter");
    
    change.checker = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.checker[i] = (char*)malloc(4 * sizeof(char)); 
	}
	if (change.checker == NULL){
		printf("erreur d'allocation ! '");
		exit(1);
	}
	strcpy(change.checker[0], " checker ");
    strcpy(change.checker[1], " par numero ");			
    strcpy(change.checker[2], "par nom");
    strcpy(change.checker[3], "retour");

	change.retourner = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.retourner[i] = (char*)malloc(4 * sizeof(char)); 
	}
		if (change.retourner == NULL){
			printf("erreur d'allocation ! '");
			exit(1);
		}
	strcpy(change.retourner[0], " lister ");
    strcpy(change.retourner[1], " date ");
    strcpy(change.retourner[2], "ekeve");
    strcpy(change.retourner[3], "retour");
    
    change.parcourir = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.parcourir[i] = (char*)malloc(4 * sizeof(char)); 
	}
		if (change.parcourir == NULL){
			printf("erreur d'allocation ! '");
			exit(1);
		}
	strcpy(change.parcourir[0], " parcourir  ");
    strcpy(change.parcourir[1], "  par numero ");
    strcpy(change.parcourir[2], " par nom ");
    strcpy(change.parcourir[3], "retour");
    
    change.option = (char**)malloc(4 * sizeof(char*));
    for (int i=0; i<4; i++){
		change.option[i] = (char*)malloc(4 * sizeof(char)); 
	}
	if (change.option == NULL){
			printf("erreur d'allocation ! '");
			exit(1);
		}
	strcpy(change.option[0], " option  ");
    strcpy(change.option[1], " langue  ");
    strcpy(change.option[2], " thème ");
    strcpy(change.option[3], " retour ");
    
    change.quitter = (char**)malloc(sizeof(char*));
	change.quitter[0] = (char*)malloc(50 * sizeof(char));
	if (change.quitter == NULL || change.quitter[0] == NULL) {
		printf("Erreur d'allocation pour change.quitter");
		exit(1);
	}
	strcpy(change.quitter[0], "quitter le programme");
	
    
    change.langueP = (char**)malloc(5 * sizeof(char*));
    for (int i=0; i<5; i++)
		change.langueP[i] = (char*)malloc(5 * sizeof(char)); 
		if (change.langueP == NULL){
			printf("erreur d'allocation ! '");
			exit(1);
		}
    strcpy(change.langueP[0], " langue ");
    strcpy(change.langueP[1], " français ");
    strcpy(change.langueP[2], " anglais ");
    strcpy(change.langueP[3], " malagasy ");
    strcpy(change.langueP[4], " retour ");
    
    return change;
}

/*--------------------------------------------*/
void check()
{
    FILE* A=NULL;
	open(&A);
	refresh();
    while(option(A));
    refresh();
}

void name_check()
{
    FILE* files=NULL;
    char nom[200];
    char op;
    char result[100]="";
	data students[76];
    files=fopen("l1.csv","r+");
    getData(files, students);
    rewind(files);
    clear();
    refresh();
    printw("nom:");
    refresh();
	getstr(nom);
	/*int a=1;	
	for(int i=0;i<strlen(phrase);i++){
		if(phrase[i]==' '){
				if (phrase[i+1]!=' ')a++;
		}
	}
	if(phrase[0]==' ') a--;
	if(phrase[strlen(phrase)-1]==' ') a--;
	printf("\n%d",a);
	*/
	
	int num=search_student(students,nom);
	clear();
    //fclose(files);
    name(files,num);
    //printw("\n");
    mvprintw(4,0,"r:annuler\no:oui\nn:non\np:perso\n");
	loop:
	printw(":");
	refresh();
	op=getch();
	switch(op)
	{
            case 'r':
            ///printf("retour");
            break;
            case 'o':
            sprintf(result,"OUI ");
            ///printf("OUI");
            break;
            case 'n':
				sprintf(result,"NON ");
			//~ else
				//~ printf("deja fait");	
            break;
            case 'p':
				sprintf(result,"PRS ");
				///printf("PERSO");
				
			//~ else
				//~ printf("deja fait");	            
            break;
            case 'q':
            //printf("FERMETURE DU PROGRAMME\n");
            default:
			printw("\ncommande invalide\n");
            goto loop;
            break;        
     }
     fputs(result,files);
     rewind(files);
    refresh();
}


