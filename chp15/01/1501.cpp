#include <map>
#include <iostream>
#include <cassert>
#include <string>

std::map<char, int> m;

void initializeHash(){
  m['I'] = 1;
  m['V'] = 5;
  m['X'] = 10;
  m['L'] = 50;
  m['C'] = 100;
  m['D'] = 500;
  m['M'] = 1000;
}

void error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    throw std::runtime_error(message);
}


int computeValue (std::string romstr) {
  int strlen = romstr.length();
  int result = 0;

  // initiate two arr filled up with 0
  int * arr1 = new int[strlen] ();
  int * arr2 = new int[strlen] ();

  // fill up with int numbers mapped from hash table ,  
  // with arr2 shifted one position forward like this:
  // arr1 = map{mcmlxix}
  // arr2 = mapping{cmlxix0}

  for (int i=0;i<strlen;i++) {
    // check if key is present
    if (m.find(romstr[i]) == m.end())  error( "invalid symbol!");
    arr1[i] = m[romstr[i]];
  }
  for (int i=0;i<strlen-1;i++) {
    arr2[i] = m[romstr[i+1]];
  }
  
  // compare two int arrays , and compute the result 
  for (int i= 0; i<strlen;i++) {
    arr1[i] < arr2[i] ? result -= arr1[i]:result += arr1[i];
  }

  
  return result;
}




int main(int argc, char **argv)

{ 
  // check input sanity
  if (argc < 2) {
      std::cout << "Please provide a string as a command line argument." << std::endl;
      return 1;
  }
  std::string romstr = argv[1];

  // initiate the hash table 
  initializeHash();

  // compute number value
  int result = computeValue(romstr);

  std::cout << result<<std::endl;
  return 0;
}