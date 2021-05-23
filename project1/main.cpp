#include "iostream"
#include "fstream"
#include "string"
#include "vector"
#include "sstream"
#include "command.h"
#include <unordered_map>
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {

  //Check for the correct number of command line parameters
  if (argc != 3) {
    //error message
    cerr << "Usage: " << argv[0] << " ASSEMBLE [input file] [output file]" << endl;
    exit(1);
  }

  //open the file for reading
  ifstream infile(argv[1]);
  //open the file for writing
  ofstream outfile(argv[2]);

  //if files can't be opended, report an Error
  if (!infile.is_open()) {
    cerr << "Error: could not open file: " << argv[1] << endl;
    exit(1);
  }
  if (!outfile.is_open()) {
    cerr << "Error: could not open file: " << argv[2] << endl;
    exit(1);
  }

  //Check if infile is empty
  if (infile.eof()) {
    infile.close();
    outfile.close();
    return 0;
  }

  //Write first sentence in output file:
  outfile << "v3.0 hex words plain\n";

  //have vectors to store data
  string cmd; //stores a command
  string line; //stores a line of input file
  string label; //stores a label of input file
  int numIns =0; //keeps track of the nummber of ins
  int numLine =0; //keeps track of the nummber of lines

  string reg1; //register 1
  string reg2; //register 2
  string reg3; //register 3
  command translate;
  vector<string> binaryInsList; //stores the list of translated binary codes

  //find total no of instructions
  string insNum;
  ifstream ins(argv[1]);
  unordered_map<string, int> umap;
  while (getline(ins>>ws, insNum)) {
    stringstream ssInsNum (insNum);
    getline (ssInsNum,cmd, ' '); //extracts commands
    if(cmd.empty()){
      continue;
    }
    if (cmd=="add" || cmd=="addi" || cmd=="sub" ||cmd=="mult" ||cmd=="mflo" ||
    cmd=="sll" ||cmd=="srl" ||cmd=="lw" ||cmd=="sw" ||cmd=="slt" ||cmd=="beq" ||
    cmd=="bne" ||cmd=="j" ||cmd=="jal" ||cmd=="jr"){
      numIns+=1;
    }
    else{
      cmd.pop_back();
      umap[cmd]=numIns;
    }

  }


  while (getline(infile>>ws, line)) {
    stringstream ss (line);
    getline (ss,cmd, ' '); //extracts commands
    if(cmd.empty()){
      continue;
    }
    if (cmd=="add") { //adder
      numLine+=1;
      getline(ss, reg1, ','); //extracting registers
      getline(ss, reg2, ',');
      getline(ss, reg3, ' '); //read the next white space
      getline(ss, reg3, ' ');
      reg2.erase(0,1); //deletes white space
      binaryInsList.push_back(translate.add(reg1, reg2, reg3)); //call on add method and add to the vector list
    }
    else if (cmd=="addi"){
      numLine+=1;
      getline(ss, reg1, ',');
      getline(ss, reg2, ',');
      getline(ss, reg3, ' '); //read the next white space
      getline(ss, reg3, ' '); //read the immediate
      reg2.erase(0,1); //delete the white space

      stringstream number(reg3);
      int x = 0;
      number >> x;
      binaryInsList.push_back(translate.addi(reg1, reg2, x));
    }
    else if (cmd=="sub") {
      numLine+=1;
      getline(ss, reg1, ',');
      getline(ss, reg2, ',');
      getline(ss, reg3, ' '); //read the next white space
      getline(ss, reg3, ' ');

      reg2.erase(0,1);

      binaryInsList.push_back(translate.sub(reg1, reg2, reg3));
    }
    else if (cmd=="mult") {
      numLine+=1;
      getline(ss, reg1, ',');
      getline(ss, reg2, ',');
      reg2.erase(0,1);
      binaryInsList.push_back(translate.mult(reg1, reg2));
    }
    else if (cmd=="mflo") {
      numLine+=1;
      getline(ss, reg1, ' ');
      binaryInsList.push_back(translate.mflo(reg1));
    }
    else if (cmd=="sll"){
      numLine+=1;
      getline(ss, reg1, ',');
      getline(ss, reg2, ',');
      getline(ss, reg3, ' '); //read the next white space
      getline(ss, reg3, ' ');
      reg2.erase(0,1); //delete the white space
      stringstream number(reg3);
      int x = 0;
      number >> x;
      binaryInsList.push_back(translate.sll(reg1, reg2, x));
    }
    else if (cmd=="srl"){
      numLine+=1;
      getline(ss, reg1, ',');
      getline(ss, reg2, ',');
      getline(ss, reg3, ' '); //read the next white space
      getline(ss, reg3, ' ');

      reg2.erase(0,1); //delete the white space
      stringstream number(reg3); //convert string reg3 into an int
      int x = 0;
      number >> x;
      binaryInsList.push_back(translate.srl(reg1, reg2, x));
    }
    else if (cmd=="lw"){
      numLine+=1;
      getline(ss, reg1, ',');
      getline(ss, reg2, '(');
      getline(ss, reg3, ')');
      reg2.erase(0,1); //delete the white space
      stringstream number(reg2);
      int x = 0;
      number >> x;
      binaryInsList.push_back(translate.lw(reg1, x, reg3));
    }
    else if (cmd=="sw"){
      numLine+=1;
      getline(ss, reg1, ',');
      getline(ss, reg2, '(');
      getline(ss, reg3, ')');
      reg2.erase(0,1); //delete the white space
      stringstream number(reg2);
      int x = 0;
      number >> x;
      binaryInsList.push_back(translate.sw(reg1, x, reg3));
    }
    else if (cmd=="slt"){
      numLine+=1;
      getline(ss, reg1, ',');
      getline(ss, reg2, ',');
      getline(ss, reg3, ' '); //read the next white space
      getline(ss, reg3, ' ');
      reg2.erase(0,1);
      binaryInsList.push_back(translate.slt(reg1, reg2, reg3));
    }
    else if (cmd=="beq"){
      numLine+=1;
      getline(ss, reg1, ',');
      getline(ss, reg2, ',');
      getline(ss, reg3, ' '); //read the next white space
      getline(ss, reg3, ' ');
      reg2.erase(0,1);
      int offset = 0;
      offset = umap[reg3] - numLine+1; //the difference between the lable line index and the bqe line index
      int absOffset = offset;

      binaryInsList.push_back(translate.beq(reg1, reg2, absOffset));
    }
    else if (cmd=="bne"){
      numLine+=1;
      getline(ss, reg1, ',');
      getline(ss, reg2, ',');
      getline(ss, reg3, ' '); //read the next white space
      getline(ss, reg3, ' ');
      reg2.erase(0,1);
      int offset = 0;
      offset = umap[reg3] - numLine+1; //the difference between the lable line index and the bqe line index
      int absOffset = offset;
      binaryInsList.push_back(translate.bne(reg1, reg2, absOffset));
    }
    else if (cmd=="j"){
      numLine+=1;
      getline(ss, reg1, ' ');
      int labelLine = umap[reg1];
      binaryInsList.push_back(translate.j(labelLine));
    }
    else if (cmd=="jal"){
      numLine+=1;
      getline(ss, reg1, ' ');
      int labelLine = umap[reg1];
      binaryInsList.push_back(translate.jal(labelLine));
    }
    else if (cmd=="jr"){
      numLine+=1;
      getline(ss, reg1, ' ');
      binaryInsList.push_back(translate.jr(reg1));
    }
  } //end while

  //go through binaryInsList and convert it to hexadecimal
  //write it to the output file
  for (auto i : binaryInsList){
    outfile<<translate.convertBinToHex(i)<<'\n';
  }

  // error if reading infile fails
  if (infile.fail() && !infile.eof()){
      cerr << "Error: bad file format: " << argv[1] << endl;
      exit(1);
  }


  //close the two files
  infile.close();
  outfile.close();


  return 0;
}
