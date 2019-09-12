#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
  ifstream DNAlist;
  string line;
  int ACount = 0;
  int CCount = 0;
  int TCount = 0;
  int GCount = 0;
  int AACount = 0;
  int ACCount = 0;
  int ATCount = 0;
  int AGCount = 0;
  int CACount = 0;
  int CCCount = 0;
  int CTCount = 0;
  int CGCount = 0;
  int TACount = 0;
  int TCCount = 0;
  int TTCount = 0;
  int TGCount = 0;
  int GACount = 0;
  int GCCount = 0;
  int GTCount = 0;
  int GGCount = 0;
  int sum = 0;
  int lineCount = 0;
  float mean = 0.0f;
  DNAlist.open(argv[1]);
  if(DNAlist.is_open()){
    while (getline(DNAlist, line)){
      sum += line.length();
      ++lineCount;
      for(int i = 0; i < line.length(); ++i){
        char nucleotide = toupper(line.at(i));
        string bigram;
        bigram.push_back(line.at(i));
        bigram.push_back(line.at(i+1));
        switch (nucleotide) {
          case 'A':
            ACount++;
            if(bigram == "AA"){
              AACount++;
            } else if(bigram == "AC"){
              ACCount++;
            } else if(bigram == "AT"){
              ATCount++;
            } else if(bigram == "AG"){
              AGCount++;
            }
            break;
          case 'C':
            CCount++;
            if(bigram == "CA"){
              CACount++;
            } else if(bigram == "CC"){
              CCCount++;
            } else if(bigram == "CT"){
              CTCount++;
            } else if(bigram == "CG"){
              CGCount++;
            }
            break;
          case 'T':
            TCount++;
            if(bigram == "TA"){
              TACount++;
            } else if(bigram == "TC"){
              TCCount++;
            } else if(bigram == "TT"){
              TTCount++;
            } else if(bigram == "TG"){
              TGCount++;
            }
            break;
          case 'G':
            GCount++;
            break;
          default:
            break;
        }
      }
    }
    mean = sum/lineCount;
  }
}
