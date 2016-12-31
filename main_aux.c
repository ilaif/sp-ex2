//
//  main_aux.c
//  Ex2
//
//  Created by Ilai Fallach on 28/12/2016.
//  Copyright © 2016 ilai. All rights reserved.
//

#include "main_aux.h"
#include <assert.h>

void run() {
    int n,d,k;
    scanf("%d %d %d", &n, &d, &k);
    assert(k <= n);
    
    SPPoint** arr = (SPPoint**) malloc(sizeof(SPPoint*) * n);
    assert (arr != NULL);
    
    fillPointsArray(arr, d, n);
    
    SPPoint* q = spPointCreate(createPointFromInput(d), d, 0);
    
    SPBPQueue* queue = createSquaredDistancePriorityQueue(arr, n, q);
    
    printKFirstInQueue(queue, k);
    
    cleanup(arr, n, q, queue);
}

void fillPointsArray(SPPoint** arr, int d, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = spPointCreate(createPointFromInput(d), d, i);
    }
}

double* createPointFromInput(int d) {
    double* pointArr = (double*) malloc(sizeof(double) * d);
    assert (pointArr != NULL);
    
    for (int j = 0; j < d; j++) {
        scanf ("%lf", &pointArr[j]);
    }
    
    return pointArr;
}

SPBPQueue* createSquaredDistancePriorityQueue(SPPoint** arr, int n, SPPoint* q) {
    SPBPQueue* queue = spBPQueueCreate(n);
    
    double sq_d;
    for (int i = 0; i < n; i++) {
        sq_d = spPointL2SquaredDistance(arr[i], q);
        spBPQueueEnqueue(queue, i, sq_d);
    }
    
    return queue;
}

void printKFirstInQueue(SPBPQueue* queue, int k)
{
    BPQueueElement* e = (BPQueueElement*) malloc(sizeof(BPQueueElement));
    assert (e != NULL);
    
    for (int i = 0; i < k - 1; i++)  {
        spBPQueuePeek(queue, e);
        printf("%d, ", e->index + 1);
        spBPQueueDequeue(queue);
    }
    
    spBPQueuePeek(queue, e);
    printf("%d\n", e->index + 1);
    spBPQueueDequeue(queue);
    
    free(e);
}

void cleanup(SPPoint** arr, int n, SPPoint* q, SPBPQueue* queue) {
    for (int i = 0; i < n; i++) {
        spPointDestroy(arr[i]);
    }
    spPointDestroy(q);
    spBPQueueDestroy(queue);
}
