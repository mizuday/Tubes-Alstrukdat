#include <stdio.h>
#include <stdlib.h>
#include "../header/state.h"


void CreateSTATE(STATE* state, PLAYER p, MAP map, Queue queue, float startTime)
{
    CURR_TIME(*state) = startTime;
    CURR_MAP(*state) = map;
    CURR_QUEUE(*state) = queue;
    CURR_PLAYER(*state) = p;
}


void incrementWaktu(STATE *state){
    float deltaTime = 0;
    if(pSpdDur(CURR_PLAYER(*state)) > 0 && hCount(CURR_TAS(*state)) == 0){
        pSpdDur(CURR_PLAYER(*state))  -= 1;
        deltaTime += 0.5;
    }
    else if(hCount(CURR_TAS(*state)) > 0){
        deltaTime += hCount(CURR_TAS(*state)) + 1;
        pSpdDur(CURR_PLAYER(*state))  = 0;
    }
    else{
        deltaTime += 1;
    }
    CURR_TIME(*state) += deltaTime;
    boolean found = false;
    while (!isEmptyQ(CURR_QUEUE(*state)) && HEAD(CURR_QUEUE(*state)).waktudatang <= CURR_TIME(*state))
    {
        Item item;
        dequeue(&CURR_QUEUE(*state), &item);
        insertFirstTodoList(&CURR_TODO(*state), item);
    }
    // CEK DELTA TIME
    // KURANGIN MASING MASING INTERNAL TIME PERISHABLE ITEM DALAM TAS DENGAN DELTA TIME
    
}

void mesinWaktu(STATE *state){
    if(CURR_TIME(*state) >= 50){
        CURR_TIME(*state) -= 50;
    }
    else{
        CURR_TIME(*state) = 0;
    }
}

void updateStatus(STATE *s){
    int i;
    int idx;
    char c;
    Address ADR = CURR_TODO(*s);
    c = getBuilding(CURR_MAP(*s),CURR_PLAYER(*s).loc.X ,CURR_PLAYER(*s).loc.Y );
    idx = getIdxBld(c,CURR_MAP(*s));
    for(i=0;i<nEffBuilding(CURR_MAP(*s));i++){
        ELMTTP(CURR_MAP(*s),i) = 'b';
    }
    clearReachable(&CURR_MAP(*s));
    for(i=0;i<nEffBuilding(CURR_MAP(*s));i++){
        if(ELMTADJ(CURR_MAP(*s),idx,i) == '1'){
            ELMTTP(CURR_MAP(*s),i) = 'r';
            insertLast(&CURR_MAP(*s).reachable,LOK(CURR_MAP(*s),i));
        } 
    }
    while(ADR != NULL){
        if(!isContainItem(CURR_TAS(*s), INFO(ADR))){
            idx = getIdxBld(INFO(ADR).locAwal,CURR_MAP(*s));
            ELMTTP(CURR_MAP(*s),idx) = 'p';
        }
        ADR = NEXT(ADR);
    }
    if(!isEmptyTas(pTas(CURR_PLAYER(*s)))){
        idx = getIdxBld(TOP(pTas(CURR_PLAYER(*s))).locAkhir,CURR_MAP(*s));
        ELMTTP(CURR_MAP(*s),idx) = 'd';
    }
    idx = getIdxBld(c,CURR_MAP(*s));
    ELMTTP(CURR_MAP(*s),idx) = 'm';
}