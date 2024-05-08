# Project 4 - Dynamic vs. Exhaustive
    Calorie-Limited Weight-Maximization Problem
    Group members: Diego Vela, dvela2@csu.fullerton.edu

## Dynamic Algorithm PseudoCode
    source = foods                                                                              //1 step
    best = []                                                                                   //1 step 

    n = foods.size()                                                                            //2 steps
    m = maxCalories                                                                             //1 step
    dpTable = [[0 for _ in maxCalories] for _ in size]                                          //n * m steps

    for i = 1 to n:                                                                             //n steps
        for int j = 0 to m:                                                                     //m steps
            if source[i-1].calories <= j:                                                       //2 steps
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - source[i-1].calories]+ item[i-1].weight) //8 steps
            else:                                                                               
                dp[i][j] = dp[i-1][j]                                                           //2 steps

    while n > 0 and m > 0:                                                                      //3+n steps
        if dp[n][m] != dp[n-1][m]:                                                              //2 steps
            add food at source[n-1] to best                                                     //2 steps
            m = m - source[n-1].calories                                                        //3 steps
        n = n-1                                                                                 //2 steps
    
    return best                                                                                     


