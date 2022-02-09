#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int FramesNumber;
int *frames,*count, *use_bit;


int FIFO_ptr=0, LRU_usage=0, clock_ptr=0;

int FIFO( int input){

int found =0, empty=0,fault = 0;
 
// loop to find an empty spot or find if it's already there 
for(int i = 0; i<FramesNumber; i++){

if(frames[i] == input){

found = 1;
break;
}

else if( frames[i] == -1){

found = 0;
empty = 1;
break;

}
}
if(!found){

//replace in order since it's fifo
frames[FIFO_ptr]=input;
FIFO_ptr++;

if(FIFO_ptr==FramesNumber) 
FIFO_ptr=0;
// if there was an empty spot then no page fault 
if(empty){
fault =0 ;
return fault;
}
//page fault occurs
else {
fault = 1;
return fault;
}
}
// if found then no page faults or replacement 
else {
fault =0; 
return fault;
}

}

// helper function to get the least recently used to use it in the replacement policy 
int getLRU(int FramesNumber){

int least_used=count[0];

int replace_index=0;

for(int i =1; i<FramesNumber; i++){

if(count[i]<least_used){
least_used=count[i];
replace_index = i;
}
}

return replace_index;
}

int LRU(int input){


int found =0, empty=0,fault = 0,j=0;
 
// loop to find an empty spot or find if it's already there 
for(int i = 0; i<FramesNumber; i++){

if(frames[i] == input){

found = 1;
j=i;
break;
}

else if( frames[i] == -1){

found = 0;
empty = 1;
j=i;
break;

}
}
// not found and there is an empty place then no page fault occurs 
if(!found && empty){

frames[j]=input;

// update that it has been used 
count[j]=LRU_usage;
LRU_usage++;

fault=0;
return fault;

}
// not found and full frames then page fault occurs
else if(!found && !empty){
// get the index that we'll replace 
j=getLRU(FramesNumber);

frames[j]=input;

// update that it has been used 
count[j]=LRU_usage;
LRU_usage++;

fault=1;
return fault;

}
// if found then no page fault occurs 
else {
// just update that it has been used 

count[j]=LRU_usage;
LRU_usage++;

fault=0;
return fault;
}
}


void printingOutput(int fault,int input){
// printing if there was a page fault 
if(fault>0){
printf("%02d F   ",input);  
for(int i=0; i<FramesNumber ; i++){

if(frames[i] == -1) 
break;
else printf("%02d ",frames[i]);
 
}
printf("\n");

}
// if the input was not a page fault
else {

printf("%02d     ",input);  
for(int i=0; i<FramesNumber ; i++){

if(frames[i] == -1) 
break;
else printf("%02d ",frames[i]);
 
}
printf("\n"); // PUT IT TA7T
}

}

 

int main(){

char policy [8];
int inputs,faults = 0,sumOfpageFaults=0 ;;
//scan number of frames 
scanf("%d",&FramesNumber);

// scan the policy that will be used 
do{
scanf("%s",policy);
}while(strlen(policy)<0);


// initialize frames and used count for LRU,CLOCK  
frames = (int *) malloc(FramesNumber * sizeof(int));
count = (int *) malloc(FramesNumber * sizeof(int));
use_bit = (int *) malloc(FramesNumber * sizeof(int));

for(int i=0; i<FramesNumber ; i++){
frames[i]=-1;
count[i]=0;
use_bit[i]=0;
}

// scan the 1st input 
scanf("%d",&inputs);

printf("Replacement Policy = %s\n",policy);
printf("-------------------------------------\n");
printf("Page   Content of Frames\n");
printf("----   -----------------\n");

while(inputs != -1){

  if (strcasecmp(policy,"FIFO")==0)
    {
        faults = FIFO(inputs);
        sumOfpageFaults = sumOfpageFaults + faults;
        printingOutput(faults,inputs);

    }
    //else if (strcasecmp(policy,"OPTIMAL")==0)
    //{
      //  optimal(inputs);
    //}
    else if (strcasecmp(policy,"LRU")==0)
    {
       faults = LRU(inputs);
       sumOfpageFaults = sumOfpageFaults + faults;
       printingOutput(faults,inputs);
    }
    //else if(strcasecmp(policy,"CLOCK")==0)
    //{
      //  faults = clock(inputs);
        //sumOfpageFaults = sumOfpageFaults + faults;
        //printingOutput(faults,inputs);
    //}
    else
    {
        printf("Method doesn't exist");
        break;
    }
    

scanf("%d",&inputs);

}
printf("-------------------------------------\n");
printf("Number of page faults = %d\n",sumOfpageFaults);


  
return 0;
}
