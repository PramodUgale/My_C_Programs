/*************************************************************************
 * File Name:  my_timer.c
 *
 * 
 *************************************************************************/
#include "my_timer.h"

int main() {
	int command = 0;
	char name[64];
	int ticks=0;
	int done=0;

    menu();
    while(1) {
        printf("\nEnter a command(0-7,-1 to quit):");
        scanf("%d",&command);

        if(command == -1)
            break;
        switch(command) {
        case 0:
            menu();
            break;
        case 1:
			traverseList(display);
			break;
        case 2:
            printf("\nPlease enter Timer name:");
            scanf("%s",name);
            printf("\nPlease enter Time in secs:");
            scanf("%d",&ticks);
            done = addTimer(name,ticks);
			if(done) printf("\nTimer '%s' added.",name);
			else printf("\nTimer '%s' not added or already exists.",name);
            break;
        case 3:
            printf("\nPlease enter Timer name:");
            scanf("%s",name);
            done = removeTimer(name);
            if(done) printf("Timer '%s' removed",name);
            else printf("Timer '%s' not found",name);
            break;
        case 4:
            printf("\nPlease enter Timer name:");
            scanf("%s",name);
            done = isTimerExists(name);
            if(done) printf("Timer '%s' found",name);
            else printf("Timer '%s' not found",name);
            break;
        case 5:
            printf("\nPlease enter Timer name:");
            scanf("%s",name);
            done = isTimerDone(name);
            if(done) printf("Timer '%s' finished",name);
            else printf("Timer '%s' not finished",name);
            break;
        case 6:
            printf("\nPlease enter Timer name:");
            scanf("%s",name);
            ticks = getTimerTicksLeft(name);
            printf("Timer '%s' has %d ticks left",name,ticks);
            break;
        case 7:
            printf("\nPlease enter Timer name:");
            scanf("%s",name);
            printf("\nPlease enter new Time in secs:");
            scanf("%d",&ticks);
            done = resetTimer(name,ticks);
			if(done) printf("\nTimer '%s' resetted.",name);
			else printf("\nTimer '%s' not found.",name);
            break;
        }
    }
    disposeTimers();
    return 0;
}
