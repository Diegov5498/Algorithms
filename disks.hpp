///////////////////////////////////////////////////////////////////////////////
// disks.hpp
// 
// Definitions for two algorithms that each solve the alternating disks
// problem.
//
// As provided, this header has four functions marked with TODO comments.
// You need to write in your own implementation of these functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

// TODO
#include <functional>
#include <iostream>

enum disk_color { DISK_DARK, DISK_LIGHT};

class disk_state {
private:
  std::vector<disk_color> _colors;

public:
  disk_state(size_t light_count)
    : _colors(light_count * 2, DISK_DARK) {

    assert(light_count > 0);

    for (size_t i = 0; i < _colors.size(); i += 2) {
      _colors[i] = DISK_LIGHT;
    }
  }

  bool operator== (const disk_state& rhs) const {
    return std::equal(_colors.begin(), _colors.end(), rhs._colors.begin());
  }

  size_t total_count() const {
    return _colors.size();
  }

  size_t light_count() const {
    return total_count() / 2;
  }

  size_t dark_count() const {
    return light_count();
  }

  bool is_index(size_t i) const {
    return (i < total_count());
  }

  disk_color get(size_t index) const {
    assert(is_index(index));
    return _colors[index];
  }

  void swap(size_t left_index) {
    assert(is_index(left_index));
    auto right_index = left_index + 1;
    assert(is_index(right_index));
    std::swap(_colors[left_index], _colors[right_index]);
  }

  std::string to_string() const {
    std::stringstream ss;
    bool first = true;
    for (auto color : _colors) {
      if (!first) {
        ss << " ";
      }

      if (color == DISK_LIGHT) {
        ss << "L";
      } else {
        ss << "D";
      }

      first = false;
    }
    return ss.str();
  }

  // Return true when this disk_state is in alternating format.
  bool is_initialized() const {
    //Traverse through vector and return false when condition fails requirements
    //else return true

    for(int i =0; i < _colors.size(); i++) {
      if(i%2 == 0 && _colors[i] == 0) {
        return false;
      } 
      if(i%2 == 1 && _colors[i] == 1) {
        return false;
      }
    } 
    return true;
  }

  // Return true when this disk_state is fully sorted, with all dark disks
  // on the left (low indices) and all light disks on the right (high
  // indices).
  bool is_sorted() const {
    int curr = 0;
    for(int i = 0; i < _colors.size();i++) {
      if(_colors[i] == 1 && curr == 0) {
        curr = 1;
      } else if (_colors[i] == 0 && curr == 1) {
        return false;
      }
    }
    return true;  
  }
};

// Data structure for the output of the alternating disks problem. That
// includes both the final disk_state, as well as a count of the number
// of swaps performed.
class sorted_disks {
private:
  disk_state _after;
  unsigned _swap_count;
  
public:
  
  sorted_disks(const disk_state& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }
  
  sorted_disks(disk_state&& after, unsigned swap_count)
    : _after(after), _swap_count(swap_count) { }
  
  const disk_state& after() const {
    return _after;
  }
  
  unsigned swap_count() const {
    return _swap_count;
  }
};

// Algorithm that sorts disks using the alternate algorithm.
sorted_disks sort_alternate(const disk_state& before) {
  //Initialize 2 vars. One to hold swap and one to modify object
  int swapCount = 0;
  disk_state after = before;
  //Algorithm Loop
  for(int i = 0; i < after.total_count(); i ++) {
    for(int j = i%2; j < after.total_count()-1; j+=2) {
      if(after.get(j) == 1 && after.get(j+1) == 0) {
        after.swap(j);
        swapCount++;
      }
    }
  }
  //Return new object initialized with sorted object and swapCount
  return sorted_disks(after, swapCount);
}


// Algorithm that sorts disks using the lawnmower algorithm.
sorted_disks sort_lawnmower(const disk_state& before) {
  //Initialize 2 vars. One to hold swap and one to modify object
  int swapCount = 0;
  disk_state after = before;
  //Algorithm Loop
  for(int i = 0; i < (after.total_count()+1)/2; i++) {
    //Loop once to n
    for(int j = 0; j < after.total_count()-1; j++) {
      if(after.get(j) == 1 && after.get(j+1) == 0) {
        after.swap(j);
        swapCount++;
      }
    }
    //Return loop back to start
    for(int j = after.total_count()-1; j > 0; j--) {
      if(after.get(j) == 0 && after.get(j-1) == 1) {
        after.swap(j-1);
        swapCount++;
      }
    }
  }
  //Return object initialized with sorted object and swapCount
  return sorted_disks(after, swapCount);
}
  

