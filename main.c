#include <ncurses.h>
#include "check.h"
int main()
{
	int last_choice;
	initscr();
	cbreak();
	curs_set(0);
	interface();
	endwin();
	loop:
	///fandefasana any am main.csv
	printf("est ce la derniere fois que vous modifier le fichier aujourdhui?\n0-Oui\n1-Non\n:");
	scanf("%d", &last_choice);
	switch (last_choice)
	{
		case 0:
		printf("sauvegarde dans le fichier principale\n");
		abs_thg();
		date("l1.csv","main.csv");
		break;
		
		case 1:
		printf("fermeture");
		break;
		default:
		goto loop;
		break;
	}
	return 0;
}
