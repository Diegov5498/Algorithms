////////////////////////////////////////////////////////////////////////////////
// maxweight.hh
//
// Compute the set of foods that maximizes the weight in foods, within 
// a given maximum calorie value with the greedy method or exhaustive search.
//
///////////////////////////////////////////////////////////////////////////////


#pragma once


#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>


// One food item available for purchase.
class FoodItem
{
	//
	public:
		
		//
		FoodItem
		(
			const std::string& description,
			double calories,
            double weight_ounces
		)
			:
			_description(description),
			_calories(calories),
            _weight_ounces(weight_ounces),
			_cal_weight(_calories/_weight_ounces)
		{
			assert(!description.empty());
			assert(calories > 0);
		}
		
		//
		const std::string& description() const { return _description; }
        double calorie() const { return _calories; }
		double weight() const { return _weight_ounces; }
		double calWeight() const { return _cal_weight; }
		
	//
	private:
		
		// Human-readable description of the food, e.g. "spicy chicken breast". Must be non-empty.
		std::string _description;
		
		// Calories; Must be positive
		double _calories;
    
    	// Food weight, in ounces; most be non-negative.
		double _weight_ounces;

		// Calories to weight ratio
		double _cal_weight;	

};


// Alias for a vector of shared pointers to FoodItem objects.
typedef std::vector<std::shared_ptr<FoodItem>> FoodVector;


// Load all the valid food items from the CSV database
// Food items that are missing fields, or have invalid values, are skipped.
// Returns nullptr on I/O error.
std::unique_ptr<FoodVector> load_food_database(const std::string& path)
{
	std::unique_ptr<FoodVector> failure(nullptr);
	
	std::ifstream f(path);
	if (!f)
	{
		std::cout << "Failed to load food database; Cannot open file: " << path << std::endl;
		return failure;
	}
	
	std::unique_ptr<FoodVector> result(new FoodVector);
	
	size_t line_number = 0;
	for (std::string line; std::getline(f, line); )
	{
		line_number++;
		
		// First line is a header row
		if ( line_number == 1 )
		{
			continue;
		}
		
		std::vector<std::string> fields;
		std::stringstream ss(line);
		
		for (std::string field; std::getline(ss, field, '^'); )
		{
			fields.push_back(field);
		}
		
		if (fields.size() != 3)
		{
			std::cout
				<< "Failed to load food database: Invalid field count at line " << line_number << "; Want 3 but got " << fields.size() << std::endl
				<< "Line: " << line << std::endl
				;
			return failure;
		}
		
		std::string
			descr_field = fields[0],
			calories_field = fields[1],
            weight_ounces_field = fields[2]
			;
		
		auto parse_dbl = [](const std::string& field, double& output)
		{
			std::stringstream ss(field);
			if ( ! ss )
			{
				return false;
			}
			
			ss >> output;
			
			return true;
		};
		
		std::string description(descr_field);
		double calories, weight_ounces;
		if (
			parse_dbl(calories_field, calories)
			&& parse_dbl(weight_ounces_field, weight_ounces)
		)
		{
			result->push_back(
				std::shared_ptr<FoodItem>(
					new FoodItem(
						description,
						calories,
                        weight_ounces
					)
				)
			);
		}
	}

	f.close();
	
	return result;
}


// Convenience function to compute the total weight and calories in 
// a FoodVector.
// Provide the FoodVector as the first argument
// The next two arguments will return the weight and calories back to 
// the caller.
void sum_food_vector
(
	const FoodVector& foods,
	double& total_calories,
    double& total_weight
)
{
	total_calories = total_weight = 0;
	for (auto& food : foods)
	{
		total_calories += food->calorie();
        total_weight += food->weight();
	}
}


// Convenience function to print out each FoodItem in a FoodVector,
// followed by the total weight and calories of it.
void print_food_vector(const FoodVector& foods)
{
	std::cout << "*** food Vector ***" << std::endl;
	
	if ( foods.size() == 0 )
	{
		std::cout << "[empty food list]" << std::endl;
	}
	else
	{
		for (auto& food : foods)
		{
			std::cout
				<< "Ye olde " << food->description()
				<< " ==> "
				<< "; calories = " << food->calorie()
                << "Weight of " << food->weight() << " ounces"
				<< std::endl
				;
		}
		
		double total_calories, total_weight;
		sum_food_vector(foods, total_calories, total_weight);
		std::cout
			<< "> Grand total calories: " << total_calories
			<< std::endl
            << "> Grand total weight: " << total_weight << " ounces" << std::endl
			;
	}
}


// Filter the vector source, i.e. create and return a new FoodVector
// containing the subset of the food items in source that match given
// criteria.
// This is intended to:
//	1) filter out food with zero or negative weight that are irrelevant to // our optimization
//	2) limit the size of inputs to the exhaustive search algorithm since it // will probably be slow.
//
// Each food item that is included must have at minimum min_weight and 
// at most max_weight.
//	(i.e., each included food item's weight must be between min_weight
// and max_weight (inclusive).
//
// In addition, the vector includes only the first total_size food items
// that match these criteria.
std::unique_ptr<FoodVector> filter_food_vector
(
	const FoodVector& source,
	double min_weight,
	double max_weight,
	int total_size
)
{
	auto filtered_vector = std::make_unique<FoodVector>();
	int current_size = 0;
	for (auto& food: source){
		if (current_size >= total_size) {
			return filtered_vector;
		}
		if(food->weight() >= min_weight && food->weight() <= max_weight) {
			filtered_vector->push_back(food);
			current_size++;
		}
	}
	return filtered_vector;
}


// Compute the optimal set of food items with a greedy algorithm.
// Specifically, among the food items that fit within a total_calorie,
// choose the foods whose weight-per-calorie is greatest.
// Repeat until no more food items can be chosen, either because we've 
// run out of food items, or run out of space.
std::unique_ptr<FoodVector> greedy_max_weight
(
	const FoodVector& foods,
	double total_calorie
)
{
	auto todo = foods;
    auto result = std::make_unique<FoodVector>();
    double current_calorie = 0;
	while (!todo.empty() && current_calorie <= total_calorie) {
        	// Find the food item with the minimum calWeight
        	auto minimum = std::min_element(todo.begin(), todo.end(), [](const auto& a, const auto& b) {
            return a->calWeight() < b->calWeight();
        });
        	if (current_calorie + (*minimum)->calorie() <= total_calorie) {
            	// Add the minimum weight food item to the result
            	result->emplace_back(*minimum);
            	current_calorie += (*minimum)->calorie();
				// Erase the minimum element from the todo list
				todo.erase(minimum);
        	} else {
				// Erase the minimum weight element if it is too large to be valid
            	todo.erase(minimum);
        	}
    	}
    return result;
}


// Compute the optimal set of food items with a exhaustive search algorithm.
// Specifically, among all subsets of food items, return the subset 
// whose weight in ounces fits within the total_weight one can carry and
// whose total calories is greatest.
// To avoid overflow, the size of the food items vector must be less than 64.
std::unique_ptr<FoodVector> exhaustive_max_weight
(
	const FoodVector& foods,
	double total_calorie
)
{
	std::unique_ptr<FoodVector> best = std::make_unique<FoodVector>();
	double bestWeight = 0;
	for(int i = 0; i<(1 <<foods.size()); i++) {
		FoodVector current;
		double current_calorie = 0;
		double current_weight = 0;
		for(int j = 0; j<foods.size(); j++) {
			if (i & (1 << j)) {
				current.push_back(foods[j]);
			}
		}
		sum_food_vector(current, current_calorie, current_weight);
		//Check Subset
		if (current_calorie <= total_calorie && current_weight > bestWeight) {
			best = std::make_unique<FoodVector>(current);
			bestWeight = current_weight;
		}
	}
	return best;
}