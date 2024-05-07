#include <fstream>
#include <iostream>
#include <iomanip>
#include <fstream>

#include "maxweight.hh"
#include "timer.hh"

using namespace std;

int main()
{
  ofstream exhaustive("exhaustive.csv");
  exhaustive << "n,seconds" << endl;
  exhaustive << fixed << setprecision(10);

  auto all_foods = load_food_database("food.csv");
  auto filtered_foods = filter_food_vector(*all_foods, 1, 2500, all_foods->size());
    
  for(int i = 0; i < 22; i++)
  {
    int n = i + 1;
    auto small_foods = filter_food_vector(*filtered_foods, 1, 2000, n);

    Timer timer;
    auto solution = exhaustive_max_weight(*small_foods, 2000);
    exhaustive << n << "," << timer.elapsed() << endl;
  }
  exhaustive.close();
    
  ofstream dynamic("dynamic.csv");
  dynamic << "n,seconds" << endl;
  dynamic << fixed << setprecision(10);

 

  for(int i = 0; i < 200; i++)
  {
    int n = i + 1;
    auto small_foods = filter_food_vector(*filtered_foods, 1, 2000, n);

    Timer timer;
    auto solution = dynamic_max_weight(*small_foods, 2000);
    dynamic << n << "," << timer.elapsed() << endl;
  }
  dynamic.close();

}
