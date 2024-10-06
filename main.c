/*-------------------------------------------
Program 3: TwentyFour Part 2
Course: CS 211, Spring 2023, UIC
System: CLion
Author: Alex Arroyo, starter code provided by Professor Ellen Kidane
------------------------------------------- */


#include <stdio.h> //allows for input and output
#include <stdlib.h> //allows use for srand and rand
#include <ctype.h> //allows for use of "is" functions
#include <string.h> //allows for use of string functions

//declaration of a node struct with char data
typedef struct charNodePtr {
    char data;
    struct charNodePtr *next;
} CharNode;

//declaration of a node struct with char data
typedef struct intNodePtr {
    int data;
    struct intNodePtr *next;
} IntNode;

//declaration of a linked list struct of CharNodes
typedef struct charLinkedList {
    CharNode *head;
    CharNode *tail;
    CharNode *current;
} CharLinkedList;

//declaration of a linked list struct of IntNodes
typedef struct intLinkedList {
    IntNode *head;
    IntNode *tail;
    IntNode *current;
} IntLinkedList;

//initialization function for a linked list struct of CharNodes
void initializeCharList(CharLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
}

//initialization function for a linked list struct of IntNodes
void initializeIntList(IntLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
}

//declaration of a Stack struct made from a CharLinkedList
typedef CharLinkedList CharStack;
//declaration of a Stack struct made from an IntLinkedList
typedef IntLinkedList IntStack;

//initialization function for a charStack
void initializeCharStack(CharStack *stack) {
    initializeCharList(stack);
}

//initialization function for an IntStack
void initializeIntStack(IntStack *stack) {
    initializeIntList(stack);
}

//function that add a CharNode to a charLinkedList
void addCharHead(CharLinkedList *list, const char *data) {
    CharNode *node = (CharNode*) malloc(sizeof(CharNode));
    node->data = *data;
    if (list->head == NULL) {
        list->tail = node;
        node->next = NULL;
    } else {
        node->next = list->head;
    }
    list->head = node;
}

//function that pushes a CharNode onto a CharStack
void pushChar(CharStack *stack, char *data) {
    addCharHead(stack, data);
}

//function that add an IntNode to an IntLinkedList
void addIntHead(IntLinkedList *list, const int data) {
    IntNode *node = (IntNode*) malloc(sizeof(IntNode));
    node->data = data;
    if (list->head == NULL) {
        list->tail = node;
        node->next = NULL;
    } else {
        node->next = list->head;
    }
    list->head = node;
}

//function that pushes an IntNode onto an IntStack
void pushInt(IntStack *stack, int data) {
    addIntHead(stack, data);
}

//function that pops a CharNode from a CharStack
char popChar(CharStack *stack) {
    CharNode *node = stack->head;
    if (node == stack->tail) {
        stack->head = stack->tail = NULL;
        char data = node->data;
        free(node);
        return data;
    }
    else {
        stack->head = stack->head->next;
        char data = node->data;
        free(node);
        return data;
    }
}

//function that pop an IntNode from an IntStack
int popInt(IntStack *stack) {
    IntNode *node = stack->head;
    if (node == stack->tail) {
        stack->head = stack->tail = NULL;
        int data = node->data;
        free(node);
        return data;
    }
    else {
        stack->head = stack->head->next;
        int data = node->data;
        free(node);
        return data;
    }
}

//function that return the precedence level of a given operator
int precedence(char operator){
    if (operator == '-'){return 1;}
    else if (operator == '+'){return 2;}
    else if (operator == '/'){return 3;}
    else if (operator == '*'){return 4;}
    else {return 0;}
}

//main function
int main() {

    int play = 2; //int variable to track whether the user wants to play again or not
    int puzzleNum; //int variables to hold which puzzle is currently being presented
    int i; //counting variable
    int j; //counting variable
    int k; //counting variable
    int invalidOp; //int variable to check if a valid operator was inputted by the user
    int allFour; // int variable to check whether or not all game operands were used only once
    char a; //char variable to hold data when using popChar
    char inputString[32]; //char array to hold file lines
    char hardMode[13][5]; //string array to hold all hard mode puzzles
    char mediumMode[25][5]; //string array to hold all medium mode puzzles
    char easyMode[14][5]; //string array to hold all easy mode puzzles
    char modeType; //char variable to track the level of difficulty
    char answer[32]; //char array to hold the user inputted solution
    char postfix[7]; //char array to hold the user inputted solution in postfix notation
    srand(1); //initialize random number generator.


    //create and open file easy.txt
    char easy[] = "easy.txt";
    FILE *filePtr1 = fopen(easy, "r"); // "r" means we open the file for reading

    //check that the file was able to be opened
    if (filePtr1 == NULL) {
        printf("Error: could not open %s for reading\n", easy);
        exit(-1);
    }

    //read each puzzle from file, and add them to array easyMode one by one
    i = 0;
    while (fgets(inputString, 10, filePtr1) != NULL) {

        k = 0;
        for(j = 0; j < strlen(inputString); j++) {
            if(isdigit(inputString[j])){
                easyMode[i][k] = inputString[j];
                k++;
            }
        }
        i++;
    }
    fclose(filePtr1); // Close the file

    //create and open file medium.txt
    char medium[] = "medium.txt";
    FILE *filePtr2 = fopen(medium, "r"); // "r" means we open the file for reading

    //check that the file was able to be opened
    if (filePtr2 == NULL) {
        printf("Error: could not open %s for reading\n", medium);
        exit(-1);
    }

    //read each puzzle from file, and add them to array mediumMode one by one
    i = 0;
    while (fgets(inputString, 10, filePtr2) != NULL) {

        k = 0;
        for(j = 0; j < strlen(inputString); j++) {
            if(isdigit(inputString[j])){
                mediumMode[i][k] = inputString[j];
                k++;
            }
        }
        i++;
    }
    fclose(filePtr2); // Close the file

    //create and open file hard.txt
    char hard[] = "hard.txt";
    FILE *filePtr3 = fopen(hard, "r"); // "r" means we open the file for reading

    //check that the file was able to be opened
    if (filePtr3 == NULL) {
        printf("Error: could not open %s for reading\n", hard);
        exit(-1);
    }

    //read each puzzle from file, and add them to array mediumMode one by one
    i = 0;
    while (fgets(inputString, 10, filePtr3) != NULL) {

        k = 0;
        for(j = 0; j < strlen(inputString); j++) {
            if(isdigit(inputString[j])){
                hardMode[i][k] = inputString[j];
                k++;
            }
        }
        i++;
    }
    fclose(filePtr3); // Close the file

    //print introduction
    printf("Welcome to the game of TwentyFour Part Two!\n");

    //print instructions
    printf("Use each of the four numbers shown exactly once, \n");
    printf("combining them somehow with the basic mathematical operators (+,-,*,/) \n");
    printf("to yield the value twenty-four.\n\n");

    //while the player still wants to play
    while(play == 1 || play == 2){

        //if the player want to choose a difficulty
        if(play == 2) {

            //print difficulty instructions
            printf("Choose your difficulty level: E for easy, M for medium, and H for hard (default is easy).\n");

            fflush(stdin); //flush the input stream
            scanf("%c", &modeType); //scan for user input

        }

        //if easy mode is on
        if ((modeType == 'E' || modeType == 'e') || ((modeType != 'M' && modeType != 'm') && (modeType != 'H' && modeType != 'h'))) {
            puzzleNum = ((rand() % 12)); //choose a random puzzle from easy mode

            //print the puzzle
            printf("The numbers to use are: %c, %c, %c, %c\n", easyMode[puzzleNum][0], easyMode[puzzleNum][1],
                   easyMode[puzzleNum][2], easyMode[puzzleNum][3]);
        }


        //if medium mode is on
        else if (modeType == 'M' || modeType == 'm') {
            puzzleNum = ((rand() % 25)); //choose a random puzzle from medium mode

            //print the puzzle
            printf("The numbers to use are: %c, %c, %c, %c\n", mediumMode[puzzleNum][0], mediumMode[puzzleNum][1],
                   mediumMode[puzzleNum][2], mediumMode[puzzleNum][3]);
        }

        //if hard mode is on
        else if (modeType == 'H' || modeType == 'h') {
            puzzleNum = ((rand() % 11)); //choose a random puzzle from hard mode

            //print the puzzle
            printf("The numbers to use are: %c, %c, %c, %c", hardMode[puzzleNum][0], hardMode[puzzleNum][1],
                   hardMode[puzzleNum][2], hardMode[puzzleNum][3]);
        }

        printf("Enter your solution: "); //ask the user for a solution
        scanf("%s", answer); //scan for user answer

        //declaration of two char stacks, one for operators and one for output
        CharStack operatorStack;
        CharStack outputStack;

        //declaration of an int stack, for the postfix evaluation process
        IntStack postfixEvaluation;

        //initialize all 3 stacks
        initializeCharStack(&operatorStack);
        initializeCharStack(&outputStack);
        initializeIntStack(&postfixEvaluation);

        //loop through the user's answer to translate it into postfix notation
        for(i = 0; i < strlen(answer); i++){

            if (isdigit(answer[i]) == 1){pushChar(&outputStack, &answer[i]);}
            else if (answer[i] == '('){
                a = answer[i];
                pushChar(&operatorStack, &a);
            }
            else if (answer[i] == ')'){
                while (operatorStack.head != NULL && operatorStack.head->data != '(') {
                    a = popChar(&operatorStack);
                    pushChar(&outputStack, &a);
                }
                popChar(&operatorStack);
            }
            else if ((((answer[i] == '*' || answer[i] == '/') || answer[i] == '+') || answer[i] == '-')){
                while(operatorStack.head != NULL && precedence(answer[i]) <= precedence(operatorStack.head->data)){
                    a = popChar(&operatorStack);
                    pushChar(&outputStack, &a);
                }
                pushChar(&operatorStack, &answer[i]);
            }
        }

        while(operatorStack.head != NULL){
            a = popChar(&operatorStack);
            pushChar(&outputStack, &a);
        }

        i = 0;
        while(outputStack.head != NULL){
            a = popChar(&outputStack);
            postfix[i] = a;
            i++;
        }

        //evaluate the user's postfix answer
        for (i = 6; i >= 0; i--) {

            if (isdigit(postfix[i])) {
                pushInt(&postfixEvaluation, postfix[i] - '0');
            }

            else {
                int val1 = popInt(&postfixEvaluation);
                int val2 = popInt(&postfixEvaluation);

                switch (postfix[i]) {
                    case '+':
                        pushInt(&postfixEvaluation, val2 + val1);
                        printf("%d + %d  =  %d.\n", val2, val1, (val2 + val1));
                        break;
                    case '-':
                        pushInt(&postfixEvaluation, val2 - val1);
                        printf("%d - %d  =  %d.\n", val2, val1, (val2 - val1));
                        break;
                    case '*':
                        pushInt(&postfixEvaluation, val2 * val1);
                        printf("%d * %d  =  %d.\n", val2, val1, (val2 * val1));
                        break;
                    case '/':
                        pushInt(&postfixEvaluation, val2 / val1);
                        printf("%d / %d  =  %d.\n", val2, val1, (val2 / val1));
                        break;

                }
            }
        }

        i = popInt(&postfixEvaluation); //set the answer equal to i

        //if the final operation is equal to 24
        if (i == 24) {printf("Well done! You are a math genius.\n\n");} //print a victory message

        //if the final operation is not equal to 24
        else {printf("Sorry. Your solution did not evaluate to 24.\n\n");} //print a loss message

        //ask the user if they would like to play again
        printf("Enter: \t1 to play again,\n");
        printf("\t2 to change the difficulty level and then play again, or\n");
        printf("\t3 to exit the program.\n");
        printf("Your choice --> ");

        fflush(stdin); //flush the input stream
        scanf("%d", &play); //scan for user input and update variable play accordingly
    }

    //print a final thank-you message
    printf("\nThanks for playing!\n");
    printf("Exiting...\n");

    return 0;
}
