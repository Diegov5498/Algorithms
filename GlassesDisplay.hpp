#pragma once
#include <string>
#include <unordered_map>
#include <vector>
using std::string;

//******************************
// Struct and classes
//******************************

// struct to store all the info about a particular pair of glasses
struct Glasses{
  string glassesColor_;
  string glassesShape_;
  string glassesBrand_;
  unsigned int barcode_;
  Glasses(string glassesColor="", string glassesShape="", string glassesBrand="", unsigned int barcode=1000000);
};

// TO BE COMPLETED: unary function to return the hash value based on
// the first digit of some unique 7-digit key
unsigned int hashfct1(unsigned int);

// TO BE COMPLETED: unary function to return the hash value based on
// the second digit of some unique 7-digit key
unsigned int hashfct2(unsigned int);

// TO BE COMPLETED: unary function to return the hash value based on
// the third digit of some unique 7-digit key
unsigned int hashfct3(unsigned int);

// TO BE COMPLETED: unary function to return the hash value based on
// the fourth digit of some unique 7-digit key
unsigned int hashfct4(unsigned int);

// TO BE COMPLETED: unary function to return the hash value based on
// the fifth digit of some unique 7-digit key
unsigned int hashfct5(unsigned int);

// TO BE COMPLETED: unary function to return the hash value based on
// the sixth digit of some unique 7-digit key
unsigned int hashfct6(unsigned int);

// TO BE COMPLETED: unary function to return the hash value based on
// the seventh digit of some unique 7-digit key
unsigned int hashfct7(unsigned int);

//******************************
// Typedef for custom hash table
//******************************
typedef std::unordered_map<unsigned int, Glasses, decltype(&hashfct1)> CustomHashTable;


// class to store the bow collection
class GlassesDisplay {
public:
  // function that adds the specified pair of glasses to main display. TO BE COMPLETED
  void addGlasses(string glassesColor, string glassesShape, string glassesBrand, unsigned int barcode);

  // removes a specified pair of glasses from the main display; if successful,
  // then it returns true; TO BE COMPLETED
  bool removeGlasses(unsigned int barcode);

  // identifies which hash function (among the seven provided, fct1 - fct7)
  // computes the most balanced hash table; TO BE COMPLETED
  unsigned int bestHashing();

  // Load information from a text file
  // with the given filename; THIS FUNCTION IS COMPLETE
  void readTextfile(string filename);

  //Adding Size function
  size_t size();

  //Constructor
  GlassesDisplay();
  
private:
  CustomHashTable hT1, hT2, hT3, hT4, hT5, hT6, hT7;
  // Function to count the number of populated buckets in a hashtable
  int countBuckets(const CustomHashTable& hashtable);
};
