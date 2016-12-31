//
//  main_aux.h
//  Ex2
//
//  Created by Ilai Fallach on 30/12/2016.
//  Copyright © 2016 ilai. All rights reserved.
//

#ifndef main_aux_h
#define main_aux_h

#include "SPBPriorityQueue.h"
#include "SPPoint.h"
#include <stdlib.h>

#include <stdio.h>

// Main function to run from main.c
void run();

/**
 * Fill given array of points from user input.
 *
 */
void fillPointsArray(SPPoint** arr, int d, int n);

/**
 * Create a point from user input.
 *
 */
double* createPointFromInput(int d);

/**
 * Given an array of points in length n and a reference point, return a priority queue of the squared distances of all points of the array from the reference point.
 *
 */
SPBPQueue* createSquaredDistancePriorityQueue(SPPoint** arr, int n, SPPoint* q);

/**
 * Print the k smallest items in the given queue.
 */
void printKFirstInQueue(SPBPQueue* queue, int k);

/**
 * Free all allocated memory.
 */
void cleanup(SPPoint** arr, int n, SPPoint* q, SPBPQueue* queue);

#endif /* main_aux_h */
