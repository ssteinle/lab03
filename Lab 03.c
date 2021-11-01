#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

long long int busyCount;
long long int countNumber = 20000000;

void doBusyWork()
{
    long long int x = countNumber;

    for(long long int a=0; a<x; a++)
    {
        busyCount++;
    }
}

//Use 4000000
void algorithm_A(int N, double list[])
{
    int a=0; 
    int b=N;

    while ( a<b ) { 
        if (list[a]<list[b]) { 
            a = a + 1;
            doBusyWork();
        } else { 
            b = b - 1;
            doBusyWork();
        } 
    } 

}

//Use 10000000
int algorithm_B(int N, double list[])
{
    for(int q=1;q<N;q=2*q){
        for(int i=0;i<N-q;i=i+2*q){
            if(list[i]<list[i+q]){ 
                int tmp=list[i]; 
                list[i]=list[i+q]; 
                list[i+q]=tmp;
                doBusyWork();
            } 
        }
    } 


    return list[0];
}

//NOTE: this algorithm is always called *initially* with startIndex=0 and endIndex=N-1 
//      startIndex,endIndex represent the start/end index of a sub-range of the list 
//      recursive calls only will set a, endIndex to something else 
//      calculate the step count based on the initial or "top level" call 
//      Input size, N = endIndex-startIndex+1 (so initial, top level calls always have N=endIndex+1) 


void algorithm_C(double list[], int startIndex, int endIndex){ 
    if (endIndex>startIndex) { 
    //phase 1   
        for(int i=startIndex;i<=(startIndex+endIndex)/2;i++) { 
            int x = list[i]; 
            list[i] = 2.0*list[endIndex+startIndex-i]; 
            list[endIndex+startIndex-i] = x; 
        } 

        //phase 2: recursion 
        algorithm_C(list, startIndex, startIndex+floor(.5*(endIndex-startIndex)) ); 

        algorithm_C(list, startIndex+ceil(.25*(endIndex-startIndex)), startIndex+floor(.75*(endIndex-startIndex)) ); 

        algorithm_C(list, startIndex+ceil(.5*(endIndex-startIndex)), endIndex ); 

        //phase 3 
        for(int i=startIndex;i<=(startIndex+endIndex)/2;i++) { 
            int x = list[i]; 
            list[i] = list[endIndex+startIndex-i] / 2.0; 
            list[endIndex+startIndex-i] = x; 
        }   
    }  
} 

int algorithm_D(int N) 
{ 
    if (N<=1)
    {
        doBusyWork();
        return 1;
    }
    else
    {
        doBusyWork();
        return ( algorithm_D(N-1) + algorithm_D(N-2) ); 
    }
} 

int main()
{
    int N;
    int p;

    clock_t start, end;
    double total;

    printf("\nSet N: ");
    scanf("%d", &N);

    double *mList = malloc(N * sizeof(double));

    for(p=0; p<N; p++)
        mList[p] = p;

    if(1==0)
    for(p=1; p<=N; p=p*2)
    {
        //*****************************************************

        printf("\n========================================");

        start = clock();
        algorithm_A(p, mList);
        end = clock();

        total = (double)(end - start) / CLOCKS_PER_SEC;

        if(total > 0.0001)
        {
            printf("\n\nAlgorithm A: for N=%d", p);

            printf("\n\nExperimental Time Raw: %f", total);

            printf("\n\n========================================");
        }
        //*****************************************************
    }

    printf("\n\n********************************************************************************");

    if(1==0)
    for(p=1; p<=N; p=p*2)
    {
        //*****************************************************

        printf("\n========================================");

        start = clock();
        algorithm_B(p, mList);
        end = clock();

        total = (double)(end - start) / CLOCKS_PER_SEC;

        if(total > 0.0001)
        {
            printf("\n\nAlgorithm B: for N=%d", p);

            printf("\n\nExperimental Time Raw: %f", total);

            printf("\n\n========================================");
        }
        //*****************************************************
    }

    printf("\n\n********************************************************************************");

    if(1==0)
    for(p=1; p<=N; p=p*2)
    {
        //*****************************************************
        start = clock();
        algorithm_C(mList, 0, p-1);
        end = clock();

        printf("\n\nAlgorithm C: for N=%u", p);

        total = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n\nExperimental Time Raw: %f", total);

        printf("\n\n========================================");
        //*****************************************************
    }

    printf("\n\n********************************************************************************");

    //if(1==0)
    for(p=1; p<=N; p=p*2)
    {
        //*****************************************************
        start = clock();
        algorithm_D(p);
        end = clock();

        printf("\n\nAlgorithm D: for N=%u", p);

        total = (double)(end - start) / CLOCKS_PER_SEC;
        printf("\n\nExperimental Time Raw: %f", total);

        printf("\n\n========================================");
        //*****************************************************
    }

    printf("\n");

    free(mList);
    
    return 0;
}