#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

typedef struct line{
    struct line * prior;
    int data;
    struct line * next;
}line;

line* put_head;


int local_put_perflow();

void display();

void display2();

int main()
{

     put_head=(line*)malloc(sizeof(line));    
     local_put_perflow();
    
   
}


int local_put_perflow(){

    int i = 1;
    for(i; i < 5 ;i++){



    line * in_state = NULL;
    in_state = (line*)malloc(sizeof(line)); 
    in_state->data = i; 
     printf("in_state:data %d\n", in_state->data);
    in_state -> prior = NULL;
    if(put_head != NULL){
         put_head->prior = in_state;
	 in_state->next = put_head; 
	}
    else{
	
	in_state->next = NULL;
	}
    put_head = in_state;
    
	}

    display2(put_head);   
}




void display(){
    while (put_head) {
        
        if (put_head->next==NULL) {
            printf("%d\n",put_head->data);
        }else{
            printf("%d <-> ",put_head->data);
        }
        put_head=put_head->next;
    }
}


void display2(){
    while (put_head-> next) {
        
        printf("%d <-> ",put_head->data);
        put_head=put_head->next;
    }
}
