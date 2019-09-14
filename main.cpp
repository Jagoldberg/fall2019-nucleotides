#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int main(int argc, char** argv){
  ifstream DNAlist;
  string line;
  double ACount = 0.0f;
  double CCount = 0.0f;
  double TCount = 0.0f;
  double GCount = 0.0f;
  double AACount = 0.0f;
  double ACCount = 0.0f;
  double ATCount = 0.0f;
  double AGCount = 0.0f;
  double CACount = 0.0f;
  double CCCount = 0.0f;
  double CTCount = 0.0f;
  double CGCount = 0.0f;
  double TACount = 0.0f;
  double TCCount = 0.0f;
  double TTCount = 0.0f;
  double TGCount = 0.0f;
  double GACount = 0.0f;
  double GCCount = 0.0f;
  double GTCount = 0.0f;
  double GGCount = 0.0f;
  double sum = 0.0f;
  int lineCount = 0;
  double mean = 0.0f;
  double stdDev = 0.0f;
  double stdDevSum = 0.0f;
  double var = 0.0f;
  string bigram;
  DNAlist.open(argv[1]);

  do {
    if(DNAlist.is_open()){ //Verifies that a list is being accessed
      while (getline(DNAlist, line)){ //Iterates through the file, accessing each line one by one
        //Calculating sum, and determining probability of each nucleotide and bigram
        sum += line.length();
        ++lineCount;
        for(int i = 0; i < line.length(); ++i){
          char nucleotide = toupper(line.at(i));
          if (i != line.length() -1){
            bigram.push_back(toupper(line.at(i)));
            bigram.push_back(toupper((line.at(i+1))));
          }
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
              if(bigram == "GA"){
                GACount++;
              } else if(bigram == "GC"){
                GCCount++;
              } else if(bigram == "GT"){
                GTCount++;
              } else if(bigram == "GG"){
                GGCount++;
              }
              break;
            default:
              break;
          }
          bigram.clear();
        }
      }
      mean = sum/lineCount;
      //Calculating standard deviation and variance
      while(getline(DNAlist, line)){
        stdDevSum += pow((line.length() - mean),2);
      }
      var = stdDevSum/(lineCount-1);
      stdDev = sqrt(var);
    }
    DNAlist.close();
    //Writing results to the file
    ofstream summary;
    summary.open("JacksonGoldberg.txt");
    summary << "Jackson Goldberg\n2316634\njagoldberg@chapman.edu\nCPSC 350-01\nAssignment 1\n\n";

    summary << "Sum: " << sum << "\n";
    summary << "Mean: " << mean << "\n";
    summary << "Variance: " << var << "\n";
    summary << "Standard Deviation: " << stdDev << "\n";

    summary << "Probability:\n";
    summary << "\tNucleotides:\n";
    summary << "\t\tA: " << (ACount/sum) << "\n";
    summary << "\t\tC: " << (CCount/sum) << "\n";
    summary << "\t\tT: " << (TCount/sum) << "\n";
    summary << "\t\tG: " << (GCount/sum) << "\n";

    summary << "\tBigrams:\n";
    summary << "\t\tAA: " << (AACount/(sum/2)) << "\n";
    summary << "\t\tAC: " << (ACCount/(sum/2)) << "\n";
    summary << "\t\tAT: " << (ATCount/(sum/2)) << "\n";
    summary << "\t\tAG: " << (AGCount/(sum/2)) << "\n";
    summary << "\t\tCA: " << (CACount/(sum/2)) << "\n";
    summary << "\t\tCC: " << (CCCount/(sum/2)) << "\n";
    summary << "\t\tCT: " << (CTCount/(sum/2)) << "\n";
    summary << "\t\tCG: " << (CGCount/(sum/2)) << "\n";
    summary << "\t\tTA: " << (TACount/(sum/2)) << "\n";
    summary << "\t\tTC: " << (TCCount/(sum/2)) << "\n";
    summary << "\t\tTT: " << (TTCount/(sum/2)) << "\n";
    summary << "\t\tTG: " << (TGCount/(sum/2)) << "\n";
    summary << "\t\tGA: " << (GACount/(sum/2)) << "\n";
    summary << "\t\tGC: " << (GCCount/(sum/2)) << "\n";
    summary << "\t\tGT: " << (GTCount/(sum/2)) << "\n";
    summary << "\t\tGG: " << (GGCount/(sum/2)) << "\n";

//Creating new DNA Strands
    double gaussianD = 0.0f;
    double gaussianC = 0.0f;
    summary << "DNA Strands:\n";
    for(int i = 0; i < 1000; ++i){
      double rand_a = rand() % 2;
      double rand_b = rand() % 2;
      gaussianC = sqrt(-2*log(rand_a))*cos(2*3.14159*rand_b);
      gaussianD = stdDev*gaussianC + mean;
      string strand;
      for(int i = 0; i < gaussianD; ++i){
        double rand_n = (rand() % 2)/4;
        if(rand_n <= (ACount/sum)){
          strand += "A";
        } else if (rand_n <= (CCount/sum)){
          strand += "C";
        } else if (rand_n <= (TCount/sum)){
          strand += "T";
        } else if (rand_n <= (GCount/sum)){
          strand += "G";
        }
      }
      summary << strand << "\n";
      strand = "";
    }
    summary.close();
    //Asking for user input to continue running the program
    char continueChar;
    cout << "Would you like to enter another list?(Y/N)" << endl;
    cin >> continueChar;
    string newFile;
    switch (continueChar){
      case 'Y':
      case 'y':
        cout << "Enter the file name of the new list: " << endl;
        cin >> newFile;
        DNAlist.open(newFile);
        break;
      case 'N':
      case 'n':
        cout << "Exiting program";
        break;
      default:
        cout << "Invalid option, exiting program";
        break;
    }
  } while(DNAlist.is_open());
  return 0;
}
