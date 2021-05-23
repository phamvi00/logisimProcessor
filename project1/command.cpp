#include <iostream>
#include "string"
#include "command.h"
using namespace std;

string command::add(string reg1, string reg2, string reg3){
  op = "000000";
  shamt = "00000";
  string addBinary = "100000";
  regBin1 = search(reg1); //search for equivalent binary values
  regBin2 = search(reg2);
  regBin3 = search(reg3);
  save = op + regBin2 + regBin3 + regBin1 + shamt + addBinary;
  return save;
}

string command::addi(string reg1, string reg2, int number){
  op = "001000";
  string binNumber;
  regBin1 = search(reg1);
  regBin2 = search(reg2);
  binNumber = decToBinary(number, 16); //convert number to decimal
  save = op+regBin2+regBin1+binNumber;
  return save;
}

string command::sub(string reg1, string reg2, string reg3){
  op = "000000";
  shamt = "00000";
  string subBinary = "100010";
  regBin1 = search(reg1);
  regBin2 = search(reg2);
  regBin3 = search(reg3);
  save = op + regBin2 + regBin3 + regBin1 + shamt + subBinary;
  return save;
}

string command::mult(string reg1, string reg2){
  op = "000000";
  shamt = "00000";
  string multBinary = "011000";
  string rd = "00000";
  regBin1 = search(reg1);
  regBin2 = search(reg2);
  save = op + regBin1 + regBin2 + rd + shamt + multBinary;
  return save;
}

string command::mflo(string reg1){
  op = "000000";
  shamt = "00000";
  string mfloBinary = "010010";
  string rs = "00000";
  string rt = "00000";
  regBin1 = search(reg1);
  save = op + rs + rt + regBin1 + shamt + mfloBinary;
  return save;
}

string command::sll(string reg1, string reg2, int number){
  op = "000000";
  string rs = "00000";
  string sllBinary = "000000";
  string shamt = decToBinary(number, 5);
  regBin1 = search(reg1);
  regBin2 = search(reg2);
  save = op + rs + regBin2 + regBin1 + shamt + sllBinary;
  return save;
}

string command::srl(string reg1, string reg2, int number){
  op = "000000";
  string rs = "00000";
  string sllBinary = "000010";
  string shamt = decToBinary(number, 5);
  string funct = "000000";
  regBin1 = search(reg1);
  regBin2 = search(reg2);
  save = op + rs + regBin2 + regBin1 + shamt + sllBinary;
  return save;
}

string command::lw(string reg1, int offset, string address){
  op = "100011";
  regBin1 = search(address);
  regBin2 = search(reg1);
  string offS = decToBinary(offset, 16);
  save = op + regBin1 + regBin2 + offS;
  return save;

}

string command::sw(string reg1, int offset, string address){
  op = "101011";
  regBin1 = search(address);
  regBin2 = search(reg1);
  string offS = decToBinary(offset, 16);
  save = op + regBin1 + regBin2 + offS;
  return save;
}

string command::slt(string reg1, string reg2, string reg3){
  op = "000000";
  shamt = "00000";
  string sltBinary = "101010";
  regBin1 = search(reg1);
  regBin2 = search(reg2);
  regBin3 = search(reg3);
  save = op + regBin2 + regBin3 + regBin1 + shamt + sltBinary;
  return save;
}

string command::beq(string reg1, string reg2, int reg3){
  op = "000100";
  regBin1 = search(reg1);
  regBin2 = search(reg2);
  regBin3 = decToBinary(reg3, 16);
  save = op + regBin1 + regBin2 + regBin3;
  return save;
}

string command::bne(string reg1, string reg2, int reg3){
  op = "000101";
  regBin1 = search(reg1);
  regBin2 = search(reg2);
  regBin3 = decToBinary(reg3, 16);
  save = op + regBin1 + regBin2 + regBin3;
  return save;
}

string command::j(int reg1){
  op = "000010";
  regBin1 = decToBinary(reg1, 26);
  save = op + regBin1;
  return save;
}

string command::jal(int reg1){
  op = "000011";
  regBin1 = decToBinary(reg1, 26);
  save = op + regBin1;
  return save;
}

string command::jr(string reg1){
  op = "000000";
  string jrBinary = "001000";
  regBin1 = search(reg1);
  save = op + regBin1 + "000000000000000" + jrBinary;
  return save;
}

string command::convertBinToHex(string bin){
  string hexString;
  string temp;
  int index;
  for (int i = 0; i<32; i=i+4) { //going throufh the binary string
    temp = bin.substr(i,4); //extract substrings of 4 units
    bool found = false;
    string findHex;
    string binary;
    //check the fourBitBinary list
  	for (int i = 0; i < 16; ++i) {
  		if (fourBitBinary[i] == temp) {
  			found = true;
        index = i;
        break;
  		}
  	}
    hexString = hexString + hex[index];
  }
  return hexString;
}

string command::decToBinary(int n, int bits) {
  string decBin;
  for (int i = bits-1; i >= 0; i--) {
    int k = n >> i; //shifting
    if (k & 1){
      decBin=decBin+"1";}
    else{
      decBin=decBin+"0";}
   }
   return decBin;
}

string command::search(string reg){
  bool found = false;
  string findString;
  int index;
  string binary;
  //check the letterRegister
	for (int i = 0; i < numRegister; ++i) {
		if (letterRegister[i] == reg) {
			found = true;
      index = i;
      break;
		}
	}

  //check the numericRegister
  if (found==false) {
    for (int i = 0; i < numRegister; ++i) {
      if (numericRegister[i] == reg) {
        found = true;
        index = i;
        break;
      }
    }
  }
  //the wanted binary is in binaryRegister[index]
  binary = binaryRegister[index];
  return binary;
}
