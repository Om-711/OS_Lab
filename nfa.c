#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

char dfatable[26][26][26]; // DFA transition table
char table[26][26][26]; // NFA transition table
int visited[26]; // Array to track visited states

int states,transition,dfastatescount=0;
char dfastates[26][26]; // Stores DFA states

// Function to read NFA transition table
void read(){
    printf("Enter transitions:\n");
    for(int i=0;i<states;i++){
        for(int j=0;j<transition;j++){
            scanf("%s ",table[i][j]); // Read state transitions
        }
    }
}

// Function to find the index of a given DFA state
int findidx(char *state){
    for(int i=0;i<dfastatescount;i++){
        if(strcmp(dfastates[i],state)==0) return i;
    }
    return -1; // Return -1 if state is not found
}

// Function to convert NFA to DFA
void dfa(){
    int front=0;
    strcpy(dfastates[dfastatescount++],"A"); // Start with initial state "A"

    while(front<dfastatescount){
        char curr[26];
        strcpy(curr,dfastates[front++]); // Get current state

        for(int i=0;i<transition;i++){
            char nextstate[26]=""; // Initialize next state
            bool present[26]={0}; // Track visited states in transition
            
            for(int j=0;curr[j]!='\0';j++){ // Iterate through each character in current state
                char *trans=table[curr[j]-'A'][i]; // Get transitions from NFA table
                
                for(int k=0;trans[k]!='\0';k++){ // Iterate through transition states
                    if(!present[trans[k]-'A']){ // Avoid duplicate entries
                        present[trans[k]-'A']=true;
                        int len=strlen(nextstate);
                        nextstate[len]=trans[k];
                        nextstate[len+1]='\0';
                    }
                }
            }

            int index=findidx(nextstate); // Check if next state already exists
            if(index==-1){
                strcpy(dfastates[dfastatescount],nextstate); // Add new DFA state
                index=dfastatescount++;
            }
            strcpy(dfatable[front-1][i],nextstate); // Store transition in DFA table
        }
    }
}

// Function to print the DFA transition table
void printDFA() {
    printf("\nDFA Transition Table:\n");
    for (int i = 0; i < dfastatescount; i++) {
        printf("%s: ", dfastates[i]);  // Print the DFA state
        for (int j = 0; j < transition; j++) {
            printf("%s ", dfatable[i][j]);  // Print transitions for each input symbol
        }
        printf("\n");
    }
}

int main() {
    // Read number of states and transitions
    printf("Enter number of states: ");
    scanf("%d", &states);
    printf("Enter number of transitions: ");
    scanf("%d", &transition);
    
    // Read transition table from user
    read();
    
    // Build DFA from NFA
    dfa();
    
    // Print the resulting DFA
    printDFA();
    
    return 0;
}
