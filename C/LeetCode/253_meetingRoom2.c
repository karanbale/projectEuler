/*
Given an array of meeting time intervals consisting of start and end times [[s1,e1],[s2,e2],...] (si < ei), 
find the minimum number of conference rooms required.

Example 1:
Input: [[0, 30],[5, 10],[15, 20]]
Output: 2

Example 2:
Input: [[7,10],[2,4]]
Output: 1

*/

#include "../standardHeaders.h"

void printArr(int **A, int r, int c){
    for (int i = 0; i <  r; i++){
        printf("[");
        for (int j = 0; j < c; j++){
            printf(" %d ", A[i][j]);
        }
        printf("]\n");
    }
}

int cmpfunc(const void *pa, const void *pb)
{
    const int *a = *(const int **)pa;
    const int *b = *(const int **)pb;
    if(a[0] != b[0])
        return a[0] - b[0];
    else
        return b[0] - a[0];
}

// int cmp(const void *a, const void **b){
//     if ((*(int **)(a)[0]) != ((*(int *)(b)[0])))    return ((*(int *)a - *(int *)b));
//     else                       return (*(int *)b - *(int *)a);
// }

int minMeetingRooms(int** intervals, int intervalsSize, int* intervalsColSize){
    
    if((intervals == NULL) || (intervalsSize == 0)){
        return 0;
    }
    
    qsort((void *)intervals, intervalsSize, sizeof intervals[0], cmpfunc);
    
    int max = 0;
    
    // put all time in a array, mark 1 as start and mark -1 as end
    int **events=NULL;
    events = (int**) malloc(intervalsSize*2*sizeof(int*));
    for(int i=0;i<intervalsSize;i++)
    {   
        events[i*2] = (int*) malloc(2*sizeof(int));
        events[i*2][0] = intervals[i][0];
        events[i*2][1] = 1;
        events[i*2+1] = (int*) malloc(2*sizeof(int));
        events[i*2+1][0] = intervals[i][1];
        events[i*2+1][1] = -1;
    }
    
    // sort entire array so that start and end times are organized in correct sequence
    qsort(events,intervalsSize*2,sizeof(int*), cmpfunc);
    
    // printArr(events, intervalsSize*2, 2);
    // track running sum and max
    // acquiring and releasing rooms in orderly fashion
    // will keep the room count in check
    int runningSum = 0;
    for(int i=0;i<intervalsSize*2;i++)
    {
        // everytime we acquire a room
        if(events[i][1] > 0)
            runningSum++;
        // everytime we leave a room
        else
            runningSum--;
        printf("remaining sum: %d\n", runningSum);
        // keep track of how many rooms are we occupying
        if(runningSum > max)
            max = runningSum;
        free(events[i]);
    }
    free(events);
    return max;   
}

