#ifndef __MY_TIMER_H__
#define __MY_TIMER_H__

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include <memory.h>

typedef struct timer {
	char name[64];
	time_t start_time;
    int sec_ticks;
    struct timer* next;
}timer;

typedef void (*callback)(timer* data);

void display(timer* n) ;
void menu() ;

timer* createTimer(const char *name, int secs) ;
timer* search(timer* head,const char *name) ;
int addTimer(const char *name, int secs) ;
int removeTimer(char *name) ;
int resetTimer(const char *name,int sec_ticks) ;
int getTimerTicksLeft(const char *name) ;
int isTimerExists(const char *name) ;
int isTimerDone(const char *name) ;
void traverseList(callback f) ;
void disposeTimers() ;


#endif
