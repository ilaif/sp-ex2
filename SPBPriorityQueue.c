//
//  SPBPriorityQueue.c
//  Ex2
//
//  Created by Ilai Fallach on 24/12/2016.
//  Copyright © 2016 ilai. All rights reserved.
//

#include <stdlib.h>
#include <math.h>
#include "stdbool.h"
#include "string.h"
#include "assert.h"

#include "SPBPriorityQueue.h"

struct sp_bp_queue_t {
    int max_size;
    int size;
    BPQueueElement* arr;
};

// Utility Methods

void swapQueueElements(BPQueueElement *A, BPQueueElement *B) {
    BPQueueElement temp = *A;
    *A = *B;
    *B = temp;
}

// Public Methods

SPBPQueue* spBPQueueCreate(int maxSize) {
    if (maxSize <= 0) {
        return NULL;
    }
    
    SPBPQueue* queue = (SPBPQueue*) malloc(sizeof(queue));
    queue->max_size = maxSize;
    BPQueueElement arr[maxSize];
    queue->arr = arr;
    queue->size = 0;
    
    if (queue->arr == NULL) {
        return NULL;
    }
    
    return queue;
}

SPBPQueue* spBPQueueCopy(SPBPQueue* source) {
    assert(source != NULL);
    
    SPBPQueue* queue = spBPQueueCreate(source->max_size);
    memcpy(queue->arr, source->arr, sizeof(sizeof(BPQueueElement) * source->max_size));
    queue->size = spBPQueueSize(source);
    
    return queue;
}

void spBPQueueDestroy(SPBPQueue* source) {
    if (source == NULL) {
        return;
    }
    
    free(source);
}

void spBPQueueClear(SPBPQueue* source) {
    //memset(source->arr, 0, sizeof(source->max_size * sizeof(BPQueueElement)));
    source->size = 0;
}

int spBPQueueSize(SPBPQueue* source) {
    return source->size;
}

int spBPQueueGetMaxSize(SPBPQueue* source) {
    return source->max_size;
}

SP_BPQUEUE_MSG spBPQueueEnqueue(SPBPQueue* source, int index, double value) {
    if (source == NULL) {
        return SP_BPQUEUE_INVALID_ARGUMENT;
    }
    
    BPQueueElement e = {index, value};
    
    int cur_size = spBPQueueSize(source);
    if (cur_size == 0) {
        source->arr[0] = e;
        return SP_BPQUEUE_SUCCESS;
    }
    
    bool is_full = spBPQueueIsFull(source);
    
    // Queue is full and the new value is larger than the maximum
    if (is_full && value > source->arr[0].value) {
        return SP_BPQUEUE_SUCCESS;
    }
    
    if (is_full) {
        bool started_replace = false;
        BPQueueElement last_e = {}; // TODO: Is this legal?
        BPQueueElement tmp_e;
        for (int i = cur_size - 1; i >= 0; i--) {
            if (started_replace) {
                tmp_e = source->arr[i];
                source->arr[i] = last_e;
                last_e = tmp_e;
            }
            else if (value <= source->arr[i].value) {
                started_replace = true;
                last_e = source->arr[i];
                source->arr[i] = e;
            }
        }
    } else {
        for (int i = cur_size - 1; i >= 0; i--) {
            source->arr[i+1] = source->arr[i];
            if (value <= source->arr[i].value) {
                source->arr[i+1] = e;
                break;
            }
        }
        if (value > source->arr[0].value) {
            source->arr[0] = e;
        }
    }
    
    return SP_BPQUEUE_SUCCESS;
}

SP_BPQUEUE_MSG spBPQueueDequeue(SPBPQueue* source) {
    if (source == NULL) {
        return SP_BPQUEUE_INVALID_ARGUMENT;
    }
    
    int cur_size = spBPQueueSize(source);
    if (cur_size == 0) {
        return SP_BPQUEUE_EMPTY;
    }
    
    source->size--;
    return SP_BPQUEUE_SUCCESS;
}

SP_BPQUEUE_MSG spBPQueuePeek(SPBPQueue* source, BPQueueElement* res) {
    if (source == NULL) {
        return SP_BPQUEUE_INVALID_ARGUMENT;
    }
    
    int cur_size = spBPQueueSize(source);
    if (cur_size == 0) {
        return SP_BPQUEUE_EMPTY;
    }
    
    res->index = source->arr[cur_size - 1].index;
    res->value = source->arr[cur_size - 1].value;
    return SP_BPQUEUE_SUCCESS;
}

SP_BPQUEUE_MSG spBPQueuePeekLast(SPBPQueue* source, BPQueueElement* res) {
    if (source == NULL) {
        return SP_BPQUEUE_INVALID_ARGUMENT;
    }
    
    int cur_size = spBPQueueSize(source);
    if (cur_size == 0) {
        return SP_BPQUEUE_EMPTY;
    }
    
    res->index = source->arr[0].index;
    res->value = source->arr[0].value;
    return SP_BPQUEUE_SUCCESS;
}

double spBPQueueMinValue(SPBPQueue* source) {
    if (source == NULL) {
        return SP_BPQUEUE_INVALID_ARGUMENT;
    }
    
    int cur_size = spBPQueueSize(source);
    if (cur_size == 0) {
        return SP_BPQUEUE_EMPTY;
    }
    
    return source->arr[cur_size - 1].value;
}

double spBPQueueMaxValue(SPBPQueue* source) {
    if (source == NULL) {
        return SP_BPQUEUE_INVALID_ARGUMENT;
    }
    
    int cur_size = spBPQueueSize(source);
    if (cur_size == 0) {
        return SP_BPQUEUE_EMPTY;
    }
    
    return source->arr[0].value;
}

bool spBPQueueIsEmpty(SPBPQueue* source) {
    if (source == NULL) {
        return SP_BPQUEUE_INVALID_ARGUMENT;
    }
    
    return spBPQueueSize(source) == 0;
}

bool spBPQueueIsFull(SPBPQueue* source) {
    if (source == NULL) {
        return SP_BPQUEUE_INVALID_ARGUMENT;
    }
    
    return spBPQueueSize(source) == spBPQueueGetMaxSize(source);
}
