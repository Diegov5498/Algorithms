# project-2
    Spring Camp Food
    Group Memebers: Diego Vela, dvela2@csu.fullerton.edu

### Greedy Algorithm PseudoCode
    todo = foods                                                               //1 step
    result = []                                                                //1 step
    current_calorie = 0                                                        //1 step

    while todo is not empty and current calorie <= total calorie do            //Average of n steps
        minimum = none                                                         //1 step
        
        for each food in todo do                                               //n steps
            if minimum == none or minimum.calWeight > food.calWeight do        //3 steps
                minimum = food                                                 //1 step
            if current_calorie + minimum.calorie <= total_calorie do           //2 steps
                add minimum item to result                                     //1 step
                current_calorie = current_calorie + minimum.calorie            //2 steps
            else do
                delete minimum from todo                                       //1 step

    return result                               

### Alternate Algorithm PseudoCode
    best = []                                                                  //1 step
    bestWeight = 0                                                             //1 step

    for i = 0 to 2^n-1 do                                                      //2^n steps
        current = []                                                           //1 step
        current_calorie = 0                                                    //1 step
        current_weight = 0                                                     //1 step

        for j = 0 to n-1 do                                                    //n steps
            if i & (1 << j) do                                                 //2 steps
                add item to current                                            //1 step
        
        sum_food_vector(current, current_calorie, current_weight)              //1 step

        if current_calorie <= total_calorie and current_weight > bestWeight do //3 steps
            best = current                                                     //1 step
            bestWeight = current_weight                                        //1 step
    
    return best            
