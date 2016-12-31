//
//  SPBPriorityQueue.c
//  Ex2
//
//  Created by Ilai Fallach on 24/12/2016.
//  Copyright © 2016 ilai. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "SPBPriorityQueue.h"

struct sp_bp_queue_t {
    int max_size;
    struct BPQueueElement* list;
};

SPBPQueue* spBPQueueCreate(int maxSize) {
    if (maxSize <= 0) {
        return NULL;
    }
    
    SPBPQueue* queue = (SPBPQueue*) malloc(sizeof(queue));
    queue->max_size = maxSize;
    queue->list = (struct BPQueueElement*) malloc(sizeof(BPQueueElement) * maxSize);
    if (queue->list == NULL) {
        return NULL;
    }
    
    // TODO: Kill myself.
    
    Q->list = L;
    Q->max = maxSize;
    return Q;
}

SPBPQueue spBPQueueCopy(SPBPQueue source) {
    SPBPQueue Q = spBPQueueCreate(source->max);
    spListDestroy(Q->list);
    Q->list = spListCopy(source->list);
    return Q;
}

void spBPQueueDestroy(SPBPQueue source) {
    if (source == NULL)
        return;
    
    spListDestroy(source->list);
    free(source);
}

void spBPQueueClear(SPBPQueue source) {
    spListClear(source->list);
}

int spBPQueueSize(SPBPQueue source) {
    return spListGetSize(source->list);
}

int spBPQueueGetMaxSize(SPBPQueue source) {
    return source->max;
}

SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue source, SPListElement element) {
    if (source == NULL || element == NULL)
        return SP_BPQUEUE_INVALID_ARGUMENT;
    
    int max = spBPQueueGetMaxSize(source);
    SPListElement elm = spListElementCopy(element);
    SP_LIST_MSG res1;
    
    res1 = Util_insert(source, source->list, elm);
    //	res1 = SP_LIST_INVALID_CURRENT;
    switch (res1) {
        case SP_LIST_SUCCESS:
            if (spListGetSize(source->list) > max) {
                SPListElement temp = spBPQueuePeekLast(source); //assuming internal pointer stays on last
                spListRemoveCurrent(source->list);   //source->list cant be null
                spListElementDestroy(temp);
            }
            return SP_BPQUEUE_SUCCESS;
        case SP_LIST_OUT_OF_MEMORY:
            spListElementDestroy(elm);
            return SP_BPQUEUE_OUT_OF_MEMORY;
        case SP_LIST_INVALID_CURRENT:
            spListElementDestroy(elm);
            return SP_BPQUEUE_INVALID_ARGUMENT;
        case SP_LIST_NULL_ARGUMENT:
            spListElementDestroy(elm);
            return SP_BPQUEUE_INVALID_ARGUMENT;
        default:
            spListElementDestroy(elm);
            return SP_BPQUEUE_FULL;
    }
    
    return (SP_BPQUEUE_MSG) NULL;
}

SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue source) { //can we assume it isnt null
    if (source == NULL)
        return SP_BPQUEUE_INVALID_ARGUMENT;
    
    if (spListGetSize(source->list) == 0) {
        return SP_BPQUEUE_EMPTY;
    } else {
        spListGetFirst(source->list);
        SP_LIST_MSG res1 = spListRemoveCurrent(source->list);
        switch (res1) {
            case SP_LIST_NULL_ARGUMENT:
                return SP_BPQUEUE_INVALID_ARGUMENT;
            case SP_LIST_INVALID_CURRENT:
                return SP_BPQUEUE_INVALID_ARGUMENT;
            case SP_LIST_OUT_OF_MEMORY:
                return SP_BPQUEUE_OUT_OF_MEMORY;
            case SP_LIST_SUCCESS:
                return SP_BPQUEUE_SUCCESS;
        }
    }
    
    return (SP_BPQUEUE_MSG) NULL;
}

SPListElement spBPQueuePeek(SPBPQueue source) {
    return spListElementCopy(spListGetFirst(source->list));
}

SPListElement spBPQueuePeekLast(SPBPQueue source) {
    SPListElement current = spListGetFirst(source->list);
    int size = spListGetSize(source->list);
    int c = 1;
    while (c < size) {
        current = spListGetNext(source->list);
        c++;
    }
    return spListElementCopy(current);
}

double spBPQueueMinValue(SPBPQueue source) {
    SPListElement first = spBPQueuePeek(source);
    double value = spListElementGetValue(first);
    spListElementDestroy(first);
    return value;
    
}

double spBPQueueMaxValue(SPBPQueue source) {
    SPListElement last = spBPQueuePeekLast(source);
    double value = spListElementGetValue(last);
    spListElementDestroy(last);
    return value;
}

bool spBPQueueIsEmpty(SPBPQueue source) {
    if (source == NULL)
        return NULL;
    
    return (spListGetSize(source->list) == 0);
}

bool spBPQueueIsFull(SPBPQueue source) {
    if (source == NULL)
        return NULL;
    
    return (spListGetSize(source->list) == source->max);
}
