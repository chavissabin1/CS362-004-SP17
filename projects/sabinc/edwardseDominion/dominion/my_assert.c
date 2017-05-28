/*
 * edwardse
 * CS 362 SW Eng II
 * Spring 2017
 *
 * Assignment 3
 * my_assert.c
 * Very basic true/false functionality.  Will not abort the program.
 */
 
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int my_assert(int first, int second){
    if( first == second){
        //printf("PASSED!!!\n");
        return 1;
    }
    else{
        //printf("FAILED D:\n");
        return 0;
    }
}