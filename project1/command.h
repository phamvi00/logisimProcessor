#include <iostream>
#include "string"
using namespace std;

class command{
  public:
    string regBin1;
    string regBin2;
    string regBin3;
    string save;
    string op;
    string shamt;
    string decToBinary(int n, int bits); //translate decimal to 'bits' bits binary
    string convertBinToHex(string bin); //find hexadecimal equivalent of binary method
    string search(string reg); //translate a register to binary

    string add(string reg1, string reg2, string reg3); //add method
    string addi(string reg1, string reg2, int number); //addi method
    string sub(string reg1, string reg2, string reg3); //subtract method
    string mult(string reg1, string reg2); //multiply method
    string mflo(string reg1); //lo method
    string sll(string reg1, string reg2, int number); //shift left logical method
    string srl(string reg1, string reg2, int number); //shift right logical method
    string lw(string reg1, int offset, string address); //load word method
    string sw(string reg1, int offset, string address); //store word method
    string slt(string reg1, string reg2, string reg3); //set less than method
    string beq(string reg1, string reg2, int reg3); //beq method
    string bne(string reg1, string reg2, int reg3); //bne method
    string j(int reg1); //jump method
    string jal(int reg1); //jump and link method
    string jr(string reg1); //jump to register address method


    static const int numRegister = 32;
    string numericRegister[numRegister]={"$0","$1","$2","$3","$4","$5","$6","$7","$8",
    "$9","$10","$11","$12","$13","$14","$15","$16","$17","$18","$19",
    "$20","$21","$22","$23","$24","$25","$26","$27","$28","$29","$30",
    "$31"};
    string letterRegister[numRegister]={"$zero","$r1","$v0","$v1","$a0","$a1","$a2",
    "$r3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1",
    "$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$r26","$r27","$gp",
    "$sp","$fp","$ra"};
    string binaryRegister[numRegister]={"00000","00001","00010","00011","00100",
    "00101","00110","00111","01000","01001","01010","01011","01100",
    "01101","01110","01111","10000","10001","10010","10011","10100",
    "10101","10110","10111","11000","11001","11010","11011","11100",
    "11101","11110","11111"};
    string fourBitBinary [16] ={"0000","0001","0010","0011","0100","0101",
    "0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    char hex[16] = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d',
    'e','f'};
};
