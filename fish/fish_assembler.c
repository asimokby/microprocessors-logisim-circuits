#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 

void convertToMachineCode(int* program, int * counter, char* op1, char* op2, char* op3, int opcode){
    int decimal_rep_instruction;
    // convert the chars to ints then place the the fields according to fish's order
    decimal_rep_instruction = (op1[0]-48)| (op2[0]-48)<<10 | (op3[0]-48)<<7 | (opcode<<3); 
    program[*counter]= decimal_rep_instruction;

}
 
main()
{     
    FILE *fp;
    char line[100];
    char *token = NULL;
    char *op1, *op2, *op3, *label;
    char ch;
    int  chch;
    int opcode;
 
    int program[1000];
    int counter=0;  //holds the address of the machine code instruction
    char * placeholder = "0"; // for dont care 
 
    fp = fopen("example_instructions.txt","r");
 
    while(fgets(line,sizeof line,fp)!= NULL)
    {
            token=strtok(line,"\n\t\r ");  //get the instruction's label(add, sub,..etc)

            if (strcmp(token,"add")==0) 
            {   
                op1 = strtok(NULL,"\n\t\r ");
                op2 = strtok(NULL,"\n\t\r ");
                op3 = strtok(NULL,"\n\t\r ");
                opcode = 0;
                convertToMachineCode(&program, &counter, op1, op2, op3, opcode);
                counter++;  

            }
            else if (strcmp(token,"sub")==0) 
            {
                op1 = strtok(NULL,"\n\t\r ");
                op2 = strtok(NULL,"\n\t\r ");
                op3 = strtok(NULL,"\n\t\r ");
                opcode = 1;
                convertToMachineCode(&program, &counter, op1, op2, op3, opcode);
                counter++;  
            }
            else if (strcmp(token,"and")==0) 
            {
                op1 = strtok(NULL,"\n\t\r ");
                op2 = strtok(NULL,"\n\t\r ");
                op3 = strtok(NULL,"\n\t\r ");
                opcode = 2;
                convertToMachineCode(&program, &counter, op1, op2, op3, opcode);
                counter++;  
            }
            else if (strcmp(token,"or")==0)
            {   
                op1 = strtok(NULL,"\n\t\r ");
                op2 = strtok(NULL,"\n\t\r ");
                op3 = strtok(NULL,"\n\t\r ");
                opcode = 3;
                convertToMachineCode(&program, &counter, op1, op2, op3, opcode);
                counter++;  
            }
            else if (strcmp(token,"xor")==0)
            {   
                op1 = strtok(NULL,"\n\t\r ");
                op2 = strtok(NULL,"\n\t\r ");
                op3 = strtok(NULL,"\n\t\r ");
                opcode = 4;
                convertToMachineCode(&program, &counter, op1, op2, op3, opcode);
                counter++;  
            }                        
            else if (strcmp(token,"not")==0)
            {  
                op1 = strtok(NULL,"\n\t\r ");
                op2 = strtok(NULL,"\n\t\r ");
                op3 = placeholder;
                opcode = 5;
                convertToMachineCode(&program, &counter, op1, op2, op3, opcode);
                counter++;    
            }
            else if (strcmp(token,"mov")==0)
            {
                op1 = strtok(NULL,"\n\t\r ");
                op2 = strtok(NULL,"\n\t\r ");
                op3 = placeholder;
                opcode = 6;
                convertToMachineCode(&program, &counter, op1, op2, op3, opcode);
                counter++;    
            }
            else if (strcmp(token,"inc")==0)
            {   
                op1 = strtok(NULL,"\n\t\r ");
                op3 = placeholder;
                opcode = 7;
                convertToMachineCode(&program, &counter, op1, op1, op3, opcode);
                counter++;    
            }
            else if (strcmp(token,"dec")==0)
            {
                op1 = strtok(NULL,"\n\t\r ");
                op3 = placeholder;
                opcode = 8;
                convertToMachineCode(&program, &counter, op1, op1, op3, opcode);
                counter++;   
            }
            else //------WHAT IS ENCOUNTERED IS NOT A VALID INSTRUCTION OPCODE
            {
                     printf("no valid opcode\n");
            } 
     } //while
 
   
     fclose(fp);
     fp = fopen("RAM","w");
     fprintf(fp,"v2.0 raw\n");  //needed for logisim, remove this line for verilog..
     for (int i=0;i<counter;i++)  //complete this for memory size in verilog 
            fprintf(fp,"%04x\n",program[i]); // print at least 4 hexadecimal digits 

    
} 