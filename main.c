// RUYA BOZCAN
// 200201044
// CS 363 HW#2
// TERM PROJECT MIPS ASSEMBLER


#include <stdio.h>    // Header file for standard input/output operations
#include <stdlib.h>   // Header file for general-purpose functions and memory management
#include <string.h>   // Header file for string manipulation functions

#define MAX_LINE_LENGTH 100 

// Maximum length for a line of text in this program is set to 100 characters




// Structure for R-Type Instructions
typedef struct 
{
    char opCode[7];// Opcode field for the R-Type instruction
    char rsReg[5]; // Source register field
    char rtReg[5];// Target register field
    char rdReg[5];// Destination register field
    char shamtBits[6]; // Shift amount field
    char functBits[7]; // Function code field
    long rAddress;  // Address for the instruction in hexadecimal
} MyRTypeInstruction;







// Structure for J-Type Instructions
typedef struct 
{
    char opCode[6];           // Opcode field for the J-Type instruction
    char targetAddress[26];   // Target address field for jump instructions
    int lineNumber;            // Line number in the original file
} MyJTypeInstruction;




// Structure for I-Type Instructions
typedef struct 
{
    char opCode[6];       // Opcode field for the I-Type instruction
    char rsReg[5];        // Source register field
    char rtReg[5];        // Target register field
    char immValue[16];    // Immediate value field
    int lineNumber;        // Line number in the original file
} MyITypeInstruction;






// Function to convert a decimal number to binary representation
// Parameters:
//   - decimalNumber: The decimal number to be converted to binary
// Returns:
//   - A dynamically allocated string containing the binary representation

char *decimalToBinary(int decimalNumber)
{    // Allocate memory for the binary representation with a fixed size of 6 characters

    char *binaryArray = (char *)malloc(6 * sizeof(char));
    int i = 4;
    binaryArray[5] = '\0';
  // Convert the decimal number to binary and store the result in the binaryArray

    while (decimalNumber > 0 && i >= 0) 
    {
        binaryArray[i] = (decimalNumber % 2) + '0';
        decimalNumber = decimalNumber / 2;
        i--;
    }
  // If there are remaining bits, fill them with '0'

    while (i >= 0) 
    {
        binaryArray[i] = '0';
        i--;
    }
  // Return the dynamically allocated binary string
    return binaryArray;
}

// Function to extract an integer from a string after removing '$' sign
int extractIntFromDollarSign(char *str)
{
    int i = 0;
    int result = 0;
    while (str[i] != '\0') 
    {
        // Checking for the presence of '$' sign
        if (str[i] == '$')
        {
            i++;
            // Extracting the integer value after '$'
            while (str[i] >= '0' && str[i] <= '9')
              {
                result = result * 10 + (str[i] - '0');
                i++;
            }
        } 
        else
        {
            i++;
        }
    }
    return result;
}

// Function to check if a string contains a comma
int containsComma(char *str) 
{
    int i = 0;
    while (str[i] != '\0') 
    {
        // Checking for the presence of a comma in the string
        if (str[i] == ',')
        {
            return 1;  // Returns true if comma found
        }
        i++;
    }
    return 0;  // Returns false if no comma found
}





// Function to calculate the address based on a hexadecimal string and a total
long calculateAddress(char *addressStr, int total) 
{
    // Converting the hexadecimal string to a long decimal value
    long decimalValue1 = strtol(addressStr, NULL, 16);
    long decimalValue2 = total;
    // Returning the sum of the two decimal values
    return decimalValue1 + decimalValue2;
}




//MAIN Function

int main() 
{
    // Arrays to store R, J, and I type instructions
    MyRTypeInstruction rTypeInstructions[10];
    MyJTypeInstruction jTypeInstructions[10];
    MyITypeInstruction iTypeInstructions[10];



  


    // Opening the input file for reading and the output file for writing
    FILE *inputFile = fopen("mycode.txt", "r");
    FILE *outputFile = fopen("myoutput.txt", "w");



  


    // Checking if the input file was successfully opened
    if (inputFile == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    char *initialAddress = "0x00400000";  // Initial address for instruction memory
  
    int rTypeCounter = 0;  // Counter for R-type instructions
    int jTypeCounter = 0;  // Counter for J-type instructions
    int iTypeCounter = 0;  // Counter for I-type instructions

    int lineNumber = 0;  // Counter for line numbers in the input file



    // Reading the input file line by line
    while (1) 
    {
        int status = fscanf(inputFile, "%s", line);
        if (status == EOF)
        {
            break;
        }
        lineNumber++;  // Incrementing line number



        // Processing R-Type Instruction
        if (strcmp(line, "add") == 0) 
        {
            // Setting constant opcode for R-type instructions
            strcpy(rTypeInstructions[rTypeCounter].opCode, "000000");

            fscanf(inputFile, "%s", rTypeInstructions[rTypeCounter].rdReg);
            fscanf(inputFile, "%s", rTypeInstructions[rTypeCounter].rsReg);



            // Check for the presence of a comma and adjust reading accordingly
            if (containsComma(rTypeInstructions[rTypeCounter].rsReg)) 
            {
                fscanf(inputFile, "%s", rTypeInstructions[rTypeCounter].rsReg);
            }

            fscanf(inputFile, "%s", rTypeInstructions[rTypeCounter].rtReg);
            if (containsComma(rTypeInstructions[rTypeCounter].rtReg))
            {
                fscanf(inputFile, "%s", rTypeInstructions[rTypeCounter].rtReg);
            }




            // Setting constant values for shamt and funct
            strcpy(rTypeInstructions[rTypeCounter].shamtBits, "00000");
            strcpy(rTypeInstructions[rTypeCounter].functBits, "100000");




            // Calculating the address for the instruction
            rTypeInstructions[rTypeCounter].rAddress = calculateAddress(initialAddress, (rTypeCounter + jTypeCounter + iTypeCounter) * 4);

            rTypeCounter++;  // Incrementing R-type instruction counter
        }


        // Processing I-Type Instruction
        else if (strcmp(line, "addi") == 0) 
        {
            fscanf(inputFile, "%s", iTypeInstructions[iTypeCounter].rtReg);
            fscanf(inputFile, "%s", iTypeInstructions[iTypeCounter].rsReg);


            // Check for the presence of a comma and adjust reading accordingly
            if (containsComma(iTypeInstructions[iTypeCounter].rsReg))
            {
                fscanf(inputFile, "%s", iTypeInstructions[iTypeCounter].rsReg);
            }

            fscanf(inputFile, "%s", iTypeInstructions[iTypeCounter].immValue);
            iTypeInstructions[iTypeCounter].lineNumber = lineNumber;  // Storing line number

            iTypeCounter++;  // Incrementing I-type instruction counter
        }


        // Processing J-Type Instruction
        else if (strcmp(line, "j") == 0)
        {
            // Setting constant value for the opcode of J-type instructions
            strcpy(jTypeInstructions[jTypeCounter].opCode, "000010");

            fscanf(inputFile, "%s", jTypeInstructions[jTypeCounter].targetAddress);
            jTypeInstructions[jTypeCounter].lineNumber = lineNumber;  // Storing line number
            jTypeCounter++;  // Incrementing J-type instruction counter
        }
    }



    // Printing R-Type Instructions
    fprintf(outputFile, "R-Type Instructions:\n");
    for (int i = 0; i < rTypeCounter; i++) {
        fprintf(outputFile, "OpCode: %s\n", rTypeInstructions[i].opCode);
        fprintf(outputFile, "Source Register (RS): %s\n", decimalToBinary(extractIntFromDollarSign(rTypeInstructions[i].rsReg)));
        fprintf(outputFile, "Target Register (RT): %s\n", decimalToBinary(extractIntFromDollarSign(rTypeInstructions[i].rtReg)));
        fprintf(outputFile, "RD: %s\n", decimalToBinary(extractIntFromDollarSign(rTypeInstructions[i].rdReg)));
        fprintf(outputFile, "Shamt: %s\n", rTypeInstructions[i].shamtBits);
        fprintf(outputFile, "Function: %s\n", rTypeInstructions[i].functBits);
        fprintf(outputFile, "R-Address: %lX\n", rTypeInstructions[i].rAddress);
        fprintf(outputFile, "\n");
    }




    // Printing I-Type Instructions
    fprintf(outputFile, "I-Type Instructions:\n");
    for (int i = 0; i < iTypeCounter; i++) {
        fprintf(outputFile, "OpCode: %s\n", iTypeInstructions[i].opCode);
        fprintf(outputFile, "Source Register (RS): %s\n", decimalToBinary(extractIntFromDollarSign(iTypeInstructions[i].rsReg)));
        fprintf(outputFile, "Target Register (RT): %s\n", decimalToBinary(extractIntFromDollarSign(iTypeInstructions[i].rtReg)));
        fprintf(outputFile, "Immediate Value: %s\n", iTypeInstructions[i].immValue);
        fprintf(outputFile, "Address: %lX\n", calculateAddress(initialAddress, (rTypeCounter + iTypeCounter + jTypeCounter) * 4));
        fprintf(outputFile, "\n");
    }




    // Printing J-Type Instructions
    fprintf(outputFile, "J-Type Instructions:\n");
    for (int i = 0; i < jTypeCounter; i++) {
        fprintf(outputFile, "OpCode: %s\n", jTypeInstructions[i].opCode);
        fprintf(outputFile, "Target Address: %s\n", jTypeInstructions[i].targetAddress);
        fprintf(outputFile, "Line Number: %d\n", jTypeInstructions[i].lineNumber);
        fprintf(outputFile, "\n");
    }






    // Closing the input and output files
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
// RUYA BOZCAN
// 200201044
// CS 363 HW#2
// TERM PROJECT MIPS ASSEMBLER
