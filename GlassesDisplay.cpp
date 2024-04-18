#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "GlassesDisplay.hpp"
#include <algorithm>
#include <limits.h>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;
using std::max;
using std::min;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int barcode) {
  return barcode/1000000;
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int barcode) {
  return (barcode/100000)%10;
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int barcode) {
  return (barcode/10000)%10;
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int barcode) {
  return (barcode/1000)%10;
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int barcode) {
  return (barcode/100)%10;
}

// function to return the hash value based on the sixth digit
unsigned int hashfct6(unsigned int barcode) {
  return (barcode/10)%10;
}

// function to return the hash value based on the seventh digit
unsigned int hashfct7(unsigned int barcode) {
  return barcode%10;
}

// Constructor for struct Item
Glasses::Glasses(string glassesColor, string glassesShape, string glassesBrand, unsigned int barcode): glassesColor_(glassesColor), glassesShape_(glassesShape), glassesBrand_(glassesBrand), barcode_(barcode)
{};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void GlassesDisplay::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string glassesColor;
    string glassesShape;
    string glassesBrand;
    unsigned int barcode;
    while (myfile >> glassesColor >> glassesShape >> glassesBrand >> barcode) {
			if (glassesColor.size() > 0)
      	addGlasses(glassesColor, glassesShape, glassesBrand, barcode);
    }
    myfile.close();
  }
  else
    throw std::invalid_argument("Could not open file " + filename);
}

void GlassesDisplay::addGlasses(string glassesColor, string glassesShape, string glassesBrand, unsigned int barcode) {
  Glasses newGlasses(glassesColor, glassesShape, glassesBrand, barcode);
  hT1[newGlasses.barcode_] = newGlasses;
  hT2[newGlasses.barcode_] = newGlasses;
  hT3[newGlasses.barcode_] = newGlasses;
  hT4[newGlasses.barcode_] = newGlasses;
  hT5[newGlasses.barcode_] = newGlasses;
  hT6[newGlasses.barcode_] = newGlasses;
  hT7[newGlasses.barcode_] = newGlasses;
}

bool GlassesDisplay::removeGlasses(unsigned int barcode) {
  if (hT1.find(barcode) != hT1.end()) {
    hT1.erase(barcode);
    hT2.erase(barcode);
    hT3.erase(barcode);
    hT4.erase(barcode);
    hT5.erase(barcode);
    hT6.erase(barcode);
    hT7.erase(barcode);
    return true;
  } else {
    return false;
  }
  
}

//Helper to find the bucket count
int GlassesDisplay::countBuckets(const CustomHashTable& table) {
  //Find the max distance between cubbies for the 10 buckets
  int max = 0;
  int min = INT_MAX;
  for (size_t i = 0; i < 10; ++i) {
    auto first = table.begin(i);
    auto last = table.end(i);
    int count = std::distance(first, last);
    //Compare
    if (count > max || max == 0) {max = count;}
    if (count < min || min == INT_MAX) {min = count;}
  }
  return max - min;
}

unsigned int GlassesDisplay::bestHashing() {
  int bestDistance = countBuckets(hT1);
  unsigned int bestTable = 1;
  int next = countBuckets(hT2);
  if (next < bestDistance) {
    bestDistance = next;
    bestTable = 2;
  }
  next = countBuckets(hT3);
  if (next < bestDistance) {
    bestDistance = next;
    bestTable = 3;
  }
  next = countBuckets(hT4);
  if (next < bestDistance) {
    bestDistance = next;
    bestTable = 4;
  }
  next = countBuckets(hT5);
  if (next < bestDistance) {
    bestDistance = next;
    bestTable = 5;
  }
  next = countBuckets(hT6);
  if (next < bestDistance) {
    bestDistance = next;
    bestTable = 6;
  }
  next = countBuckets(hT7);
  if (next < bestDistance) {
    bestDistance = next;
    bestTable = 7;
  }
  return bestTable;
}

// ALREADY COMPLETED
size_t GlassesDisplay::size() {
  if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) || (hT1.size() != hT4.size()) || (hT1.size() != hT5.size())|| (hT1.size() != hT6.size()) || (hT1.size() != hT7.size()))
    throw std::length_error("Hash table sizes are not the same");
	return hT1.size();
}

//Constructor 
GlassesDisplay::GlassesDisplay()
    : hT1(1, hashfct1), hT2(1, hashfct2), hT3(1, hashfct3), hT4(1, hashfct4),
      hT5(1, hashfct5), hT6(1, hashfct6), hT7(1, hashfct7) {}
    