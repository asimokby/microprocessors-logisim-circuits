#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Converts a hexadecimal string to integer.
int hex2int( char* hex)  
{
    int result=0;

    while ((*hex)!='\0')
    {
        if (('0'<=(*hex))&&((*hex)<='9'))
            result = result*16 + (*hex) -'0';
        else if (('a'<=(*hex))&&((*hex)<='f'))
            result = result*16 + (*hex) -'a'+10;
        else if (('A'<=(*hex))&&((*hex)<='F'))
            result = result*16 + (*hex) -'A'+10; 
        hex++;
    }
    return(result);
}

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
    char *op1, *op2, *op3;
    char ch;
    int  chch;
    int aluop;
    int program[1000];
    int counter=0;  //holds the address of the machine code instruction


    fp = fopen("example_instructions.txt","r");

    while(fgets(line,sizeof line,fp)!= NULL)
    {
            token=strtok(line,"\n\t\r ");  //get the instruction mnemonic or labe

            if (strcmp(token,"ldi")==0)        //---------------LDI INSTRUCTION--------------------
            {
                    op1 = strtok(NULL,"\n\t\r ");                                //get the 1st operand of ldi, which is the register that ldi loads
                    op2 = strtok(NULL,"\n\t\r ");                                //get the 2nd operand of ldi, which is the data that is to be loaded
                    program[counter]=0x2000+hex2int(op1);                        //generate the first 16-bit of the ldi instruction
                    counter++;                                                   //move to the second 16-bit of the ldi instruction
                    if ((op2[0]=='0')&&(op2[1]=='x'))                            //if the 2nd operand is twos complement hexadecimal
                        program[counter]=hex2int(op2+2)&0xffff;              //convert it to integer and form the second 16-bit 
                    else if ((  (op2[0])=='-') || ((op2[0]>='0')&&(op2[0]<='9')))       //if the 2nd operand is decimal 
                        program[counter]=atoi(op2)&0xffff;                         //convert it to integer and form the second 16-bit 
                    else                                                           //if the second operand is not decimal or hexadecimal, it is a laber or a variable.
                    {                                                               //in this case, the 2nd 16-bits of the ldi instruction cannot be generated.
                        printf("unrecognizable LDI offset\n");
                    }        
                    counter++;                                                     //skip to the next memory location 
            }                                       
            else if (strcmp(token,"add")==0) //----------------- ADD -------------------------------
            {       
                aluop = 0;
                op1 = strtok(NULL,"\n\t\r ");    
                op2 = strtok(NULL,"\n\t\r ");
                op3 = strtok(NULL,"\n\t\r ");
                chch = (op1[0]-48)| ((op2[0]-48)<<6)|((op3[0]-48)<<3) | (aluop<<8) | (0b0001)<<12;  
                program[counter]= chch;
                counter++; 
            }
            else if (strcmp(token,"sub")==0)
            {   
                aluop = 1;
                op1 = strtok(NULL,"\n\t\r ");    
                op2 = strtok(NULL,"\n\t\r ");
                op3 = strtok(NULL,"\n\t\r ");
                chch = (op1[0]-48)| ((op2[0]-48)<<6)|((op3[0]-48)<<3) | (aluop<<8) | (0b0001)<<12;  
                program[counter]= chch;
                counter++; 
            }
            else if (strcmp(token,"and")==0)
            {
                aluop = 2;
                op1 = strtok(NULL,"\n\t\r ");    
                op2 = strtok(NULL,"\n\t\r ");
                op3 = strtok(NULL,"\n\t\r ");
                chch = (op1[0]-48)| ((op2[0]-48)<<6)|((op3[0]-48)<<3) | (aluop<<8) | (0b0001)<<12;  
                program[counter]= chch;
                counter++; 
            }
            else if (strcmp(token,"or")==0)
            {
                aluop = 3;
                op1 = strtok(NULL,"\n\t\r ");    
                op2 = strtok(NULL,"\n\t\r ");
                op3 = strtok(NULL,"\n\t\r ");
                chch = (op1[0]-48)| ((op2[0]-48)<<6)|((op3[0]-48)<<3) | (aluop<<8) | (0b0001)<<12;  
                program[counter]= chch;
                counter++; 
            }
            else if (strcmp(token,"xor")==0)
            {
                aluop = 4;
                op1 = strtok(NULL,"\n\t\r ");    
                op2 = strtok(NULL,"\n\t\r ");
                op3 = strtok(NULL,"\n\t\r ");
                chch = (op1[0]-48)| ((op2[0]-48)<<6)|((op3[0]-48)<<3) | (aluop<<8) | (0b0001)<<12;  
                program[counter]= chch;
                counter++; 
            }                        
            else if (strcmp(token,"not")==0)
            {
                aluop = 5;
                op1 = strtok(NULL,"\n\t\r ");    
                op2 = strtok(NULL,"\n\t\r ");
                chch = (op1[0]-48)| ((op2[0]-48)<<6)|(0b00<<3) | (aluop<<8) | (0b0001)<<12;  
                program[counter]= chch;
                counter++; 
            }
            else if (strcmp(token,"mov")==0)
            {
                aluop = 6;
                op1 = strtok(NULL,"\n\t\r ");    
                op2 = strtok(NULL,"\n\t\r ");
                chch = (op1[0]-48)| ((op2[0]-48)<<6)|(0b00<<3) | (aluop<<8) | (0b0001)<<12;  
                program[counter]= chch;
                counter++; 
            }
            else if (strcmp(token,"inc")==0)
            {
                aluop = 7;
                op1 = strtok(NULL,"\n\t\r ");    
                chch = (op1[0]-48)| ((op1[0]-48)<<6)|(0b00<<3) | (aluop<<8) | (0b0001)<<12;  
                program[counter]= chch;
                counter++; 
            }
            else if (strcmp(token,"dec")==0)
            {
                aluop = 8;
                op1 = strtok(NULL,"\n\t\r ");    
                chch = (op1[0]-48)| ((op1[0]-48)<<6)|(0b00<<3) | (aluop<<8) | (0b0001)<<12;  
                program[counter]= chch;
                counter++; 
            }
            else //------WHAT IS ENCOUNTERED IS NOT A VALID INSTRUCTION OPCODE
            {
                     printf("no valid opcode\n");
            } 
     } //while

     fclose(fp);
     fp = fopen("frog_machine_code","w");
     fprintf(fp,"v2.0 raw\n");  //needed for logisim, remove this line for verilog..
     for (int i=0;i<counter;i++)  //complete this for memory size in verilog
            fprintf(fp,"%04x\n",program[i]);
} //main