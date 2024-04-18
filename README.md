# project-3
Balanced Glasses Display
Group members: Diego Vela, dvela2@csu.fullerton.edu

## HashTable Algorithm PseudoCode
First we analyze the helper function "countBuckets" to find the steps:   

    max = 0                                                 //1 step
    min = INT_MAX                                           //1 step
    
    for i in range(10):                                     //10 iterations
        first = firstElement in table                       //1 step
        last = lastElement in table                         //1 step
        distance = distance(first,last)                     //1 step
        
        if (distance > max or max == 0):                    //3 steps
            max = distance                                  //1 step
        if (count < min or min == INT_MAX):                 //3 steps
            min = distance                                  //1 step
    
    return max - min                                        //1 step

This function is a total of 1 + 1 + 110 + 1 = 113 steps
    
Now Let's analyze the main function:

    bestDistance = countBuckets(hashTable1);                //114 steps
    bestTable = 1;                                          //1 step
    
    //Note: In the code, this loop is individually done.
    for each currHT 2 through 7:                            //6 iterations
        currentDistance = countBuckets(currHT)              //114 steps
        if currentDistance < bestDistance:                  //1 step
            bestDistance = currentDistance                  //1 step
            bestTable = currHT                              //1 step
        
    return bestTable                                        

    
