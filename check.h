#include <ncurses.h>
#include <stdio.h>
//~ typedef enum bool
//~ {
	//~ false,
	//~ true
//~ }bool;

 typedef struct data
    {
        char* name;
        char* surname;
        int number;
        char* check;
        char* date;
    }data;

    enum computer
    {
        YES,
        NO,
        OWN_COMPUTER
    };
    
    enum menu_principale{
	MENU,
	CHECK,
	LIST,
	PARCOURIR,
	OPTION,
	QUITTER
};
enum check_and_return{
	tmp,
	by_num,
	by_name,
	go_back
};

enum by_num
{
	checky,
	retour,
	oui,
	non,
	perso,
};
enum options{
	temporary,
	langue,
	theme,
	back
};
enum langue{
	temp,
	francais,
	anglais,
	malagasy,
	goback
};

typedef struct modify_langue{
	char** menu;
	char** checker;
	char** retourner;
	char** parcourir;
	char** option;
	char** quitter;
	char** langueP;
}modify_langue;

modify_langue modify_francais ( modify_langue change);
modify_langue modify_anglais ( modify_langue change);
modify_langue modify_malagasy ( modify_langue change);

int open(FILE** A);
int ask_check_num();
bool lgoto(FILE* A,int b);
bool name(FILE* A,int b);
bool option(FILE* A);
void abs_thg();
void to_lower_str(char* dest, const char* src);
void date(const char *source, const char *dest);

void getData(FILE* file,data students[]);
int studentNumber(FILE* file);
data* allocation(int studentsNumbers);
char** split(char* string);
int occurence(char str[], char ch);

int search_student(data* students, char part_of_name[]);

int menu(WINDOW* win,int count, ...);
void interface();
void check();
void name_check();

