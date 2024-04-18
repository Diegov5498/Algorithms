#include <iomanip>
#include <iostream>
#include <cassert>

#include "rubrictest.hpp"
#include "GlassesDisplay.hpp"

int main() {
	
  Rubric rubric;
  
  // test hash functions
  rubric.criterion("hash function 1 item 1234567", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct1(1234567)", 1, hashfct1(1234567U) );
		   });
  
  rubric.criterion("hash function 2 item 1234567", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct2(1234567)", 2, hashfct2(1234567U) );
		   });
  
  rubric.criterion("hash function 3 item 1234567", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct3(1234567)", 3, hashfct3(1234567U) );
		   });
  
  rubric.criterion("hash function 4 item 1234567", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct4(1234567)", 4, hashfct4(1234567U) );
		   });
  
  rubric.criterion("hash function 5 item 1234567", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct5(1234567)", 5, hashfct5(1234567U) );
		   });
  
  rubric.criterion("hash function 6 item 1234567", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct6(1234567)", 6, hashfct6(1234567U) );
		   });
  
  rubric.criterion("hash function 7 item 1234567", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct7(1234567)", 7, hashfct7(1234567U) );
		   });
  
  rubric.criterion("hash function 1 item 6789012", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct1(6789012)", 6, hashfct1(6789012U) );
		   });
  
  rubric.criterion("hash function 2 item 6789012", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct2(6789012)", 7, hashfct2(6789012U) );
		   });
  
  rubric.criterion("hash function 3 item 6789012", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct3(6789012)", 8, hashfct3(6789012U) );
		   });
  
  rubric.criterion("hash function 4 item 6789012", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct4(6789012)", 9, hashfct4(6789012U) );
		   });
  
  rubric.criterion("hash function 5 item 6789012", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct5(6789012)", 0, hashfct5(6789012U) );
		   });
  
  rubric.criterion("hash function 6 item 6789012", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct6(6789012)", 1, hashfct6(6789012U) );
		   });
  
  rubric.criterion("hash function 7 item 6789012", 1,
		   [&]() {
		     TEST_EQUAL( "hashfct7(6789012)", 2, hashfct7(6789012U) );
		   });
  
  GlassesDisplay set1;
  set1.addGlasses("red", "butterfly", "smooth", 1234567U);
  set1.addGlasses("pink", "butterfly", "smooth", 2345678U);
  rubric.criterion("size after adding two bows", 1,
		   [&]() {
      TEST_EQUAL( "size after adding two bows", 2, set1.size() );
		   });
  
  GlassesDisplay pairs1;
  pairs1.readTextfile("in1.txt");
  rubric.criterion("size after reading in1.txt", 1,
		   [&]() {
      TEST_EQUAL( "size after reading in1.txt", 18, pairs1.size() );
		   });
  
  rubric.criterion("bestHashing() for in1.txt", 1,
		   [&]() {
     TEST_EQUAL( "bestHashing() for in1.txt", 2, pairs1.bestHashing() );
		   });
  
  GlassesDisplay pairs2;
  pairs2.readTextfile("in2.txt");
  rubric.criterion("size after reading in2.txt", 1,
		   [&]() {
      	     TEST_EQUAL( "size after reading in2.txt", 36, pairs2.size());
		   });
  
  rubric.criterion("bestHashing() for in2.txt", 1,
                   [&]() {
      	     TEST_EQUAL( "bestHashing() for in2.txt", 3, pairs2.bestHashing());
                   });
  
  GlassesDisplay changed_pairs2(pairs2);
  changed_pairs2.removeGlasses(8890123);
  rubric.criterion("size after removing 8890123", 1,
		   [&]() {
      TEST_EQUAL( "size after removing 8890123", 35, changed_pairs2.size() );
		   });
  
  rubric.criterion("hash function 1", 1,
		   [&]() {
TEST_EQUAL( "bestHashing() after removing 8890123", 4, changed_pairs2.bestHashing() );
		   });
  return rubric.run();
}