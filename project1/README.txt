*This program is to translate MIPS assembly code into a hexadecimal encoding
1/ Files:
-Command.h: header file for command.cpp file.
-Command.cpp: the implementations of the methods stated in command.h.
-main.cpp: the file contains main function, taking in two arguments: input file and output file.
-makefile: the makefile file of the program.

2/ Classes:
-command: the class has methods that assists the program with translating MIPS assembly code into a hexadecimal encoding

3/ Object:
-translate: an object created from class command, is used in main.

4/ Methods:
string decToBinary(int n, int bits): translates integer n to 'bits' bits binary
string convertBinToHex(string bin): finds hexadecimal equivalent of 4-bit binary
string search(string reg): finds a binary equivalent to the passed in register, takes in the string register

*All methods below return a string of binary code:
string add(string reg1, string reg2, string reg3): add method takes in 3 strings for 3 registers
string addi(string reg1, string reg2, int number): addi method takes in 2 strings for 2 registers, and one integer
string sub(string reg1, string reg2, string reg3): subtract method takes in 3 strings for 3 registers
string mult(string reg1, string reg2): multiply method takes in 2 strings for 2 registers
string mflo(string reg1): lo method takes in 1 string for rd
string sll(string reg1, string reg2, int number): shift left logical method takes in 2 strings for 2 registers, and one integer for shifting
string srl(string reg1, string reg2, int number): shift right logical method takes in 2 strings for 2 registers, and one integer for shifting
string lw(string reg1, int offset, string address): load word method takes in 2 strings for 2 registers, and one integer for offset
string sw(string reg1, int offset, string address): store word method takes in 2 strings for 2 registers, and one integer for offset
string slt(string reg1, string reg2, string reg3): set less than method takes in 3 strings for 3 registers
string beq(string reg1, string reg2, int reg3): beq method takes in 3 strings for 3 registers
string bne(string reg1, string reg2, int reg3): bne method takes in 3 strings for 3 registers
string j(int reg1): jump method takes in label reg1
string jal(int reg1): jump and link method takes in label reg1
string jr(string reg1): jump to register address method takes in string reg1

5. Variables:
string regBin1: stores the first register/string of the instruction
string regBin2: stores the second register/string of the instruction
string regBin3: stores the third register/string of the instruction
string save: stores the complete string of binary code for an instruction
string op: stores ops value of according commands
string shamt: stores shame value of according commands
static const int numRegister = 32: The number of registers (32)
string letterRegister[numRegister]: string list of 32 numeric registers
string binaryRegister[numRegister]: string list of 32 letter registers
string fourBitBinary [16]: string list of 16 four-bit binary numbers
vector<string> binaryInsList: stores the list of translated binary codes 
char hex[16]: string list of 16 hexadecimals

6. Classes/objects interaction:
When main reads lines of inputs and processes/breaks down the elements in an instruction. getline() will try to capture the command of the instruction and compare it to existing commands (methods) to decide which appropriate method to call.
After processing the command and convert it into strings of binary stored in vector binaryInsList. Then, main will run through the vector list and call on the convertBinToHex method to convert the strings into hexadecimals. The return values of convertBinToHex will be written on the output file.
