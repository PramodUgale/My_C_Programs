/*************************************************************************
 * File Name:  my_timer.c
 *
 * File contains all function related to Countdown Timer
 *************************************************************************/
#include "my_timer.h"

timer *start = NULL;

/*----------------------------------------------------------------------
	create a new timer	
----------------------------------------------------------------------*/
timer* createTimer(const char *name, int secs) {
	int len=0;
    timer* new_timer = (timer*)malloc(sizeof(timer));
    if(new_timer == NULL) {
        printf("Error creating a new node.\n");
        exit(0);
    }
	len=strlen(name);
    memmove(new_timer->name,name,len) ; new_timer->name[len] = '\0' ;
	time(&new_timer->start_time) ;
	new_timer->sec_ticks = secs ;
    new_timer->next = NULL ;
 
    return new_timer;
}

/*----------------------------------------------------------------------
    add a new timer in the list
----------------------------------------------------------------------*/
int addTimer(const char *name, int secs) {
	timer *cursor ;
	int added = 0 ;

    if(start == NULL) {
		/* create a new node and assign to head */
		start = createTimer(name,secs);
		added = 1 ;
	}else {
		/* go to the last node */
		cursor = start;
		while(cursor->next != NULL)
			cursor = cursor->next;
 
		/* create a new node and assign to tail*/
		cursor->next =  createTimer(name,secs);
		added = 1 ;
	}

    return added;
}

/*----------------------------------------------------------------------
    display a timer
----------------------------------------------------------------------*/
void display(timer* n) {
    if(n != NULL)
		printf("{%s,%d} ", n->name,n->sec_ticks);
}

/*----------------------------------------------------------------------
    traverse the Timer list
----------------------------------------------------------------------*/
void traverseList(callback f) {
    timer* cursor = start;
	printf("\n");
    while(cursor != NULL) {
        f(cursor);
        cursor = cursor->next;
    }
}

/*----------------------------------------------------------------------
    Search for a specific timer with Name
 
    return the first matched timer with given timer name,
    otherwise return NULL
----------------------------------------------------------------------*/
timer* search(timer* head,const char *name) {
	timer *cursor = head;

    while(cursor!=NULL) {
        if(strcmp(cursor->name,name) == 0)
            return cursor;
        cursor = cursor->next;
    }

    return NULL;
}

/*----------------------------------------------------------------------
    remove a specific timer with given Name
    otherwise return NULL
----------------------------------------------------------------------*/
int removeTimer(char *name) {
	timer *previous = NULL;
	timer *cursor = NULL ; 
	timer *found = NULL ;
	int removed = 0 ;

	/* if list is Empty return NULL */
	if(start == NULL)
		return 0 ;
	/* Check head for removal */
	if(strcmp(start->name,name) == 0) {
		previous = start ;
		start = start->next ;
		free(previous);
		removed = 1 ;
	}else {
		previous = start ;
		cursor = start->next;
		while(cursor!=NULL)     {
			if(strcmp(cursor->name,name) == 0) {
				found = cursor;
				break;
			}
			previous = cursor ;
			cursor = cursor->next;
		}
		if(found != NULL) {
			if(found->next != NULL) {
				previous->next = found->next ;
				found->next = NULL;
				free(found);
			}else {
				previous->next = NULL ;
				found->next = NULL;
				free(found);
			}
			removed = 1 ;
		}
	}

    return removed;
}

/*----------------------------------------------------------------------
    remove all timers from the list
----------------------------------------------------------------------*/
void disposeTimers() {
    timer *cursor, *tmp;
 
    if(start != NULL) {
        cursor = start->next;
        start->next = NULL;
        while(cursor != NULL) {
            tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
}

/*----------------------------------------------------------------------
    tells if timers with given name is completed or not
----------------------------------------------------------------------*/
int isTimerDone(const char *name) {
	timer *found ;
	time_t current_time ;

	found = search(start,name);
	if(found != NULL) {
		time(&current_time);
		if((current_time - found->start_time) >= found->sec_ticks) {
			return 1;
		}else {
			return 0;
		}
	}
	return -1;
}

/*----------------------------------------------------------------------
    resets timers with given name
----------------------------------------------------------------------*/
int resetTimer(const char *name,int sec_ticks) {
	timer *found ;

	found = search(start,name);
	if(found != NULL) {
		found->sec_ticks = sec_ticks ;
		time(&found->start_time);
		return 1;
	}

	return 0;
}

/*----------------------------------------------------------------------
    return ticks left for timers with given name
----------------------------------------------------------------------*/
int getTimerTicksLeft(const char *name) {
	timer *found ;
	time_t current_time ;
	int leftTicks ;

	found = search(start,name);
	if(found != NULL) {
		time(&current_time);
		leftTicks = found->sec_ticks - (int)(current_time - found->start_time) ;
		if(leftTicks > 0)
			return leftTicks;
	}

	return 0;
}

/*----------------------------------------------------------------------
    checks if timer with given name exist or not
----------------------------------------------------------------------*/
int isTimerExists(const char *name) {
	timer *temp;

	temp=search(start,name);
	if(temp != NULL) {
		return 1;
	}

	return 0;
}

void menu() {

    printf("--- Timer List Functions--- \n\n");
    printf("0.menu\n");
    printf("1.Traverse Timer List\n");
    printf("2.Add Timer\n");
    printf("3.Remove Timer\n");
    printf("4.Check if Timer Exist\n");
    printf("5.Check if Timer Finished\n");
    printf("6.Read Timer ticks left\n");
    printf("7.Reset Timer\n");
    printf("-1.quit\n");
}

