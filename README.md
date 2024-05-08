# Project 4 - Dynamic vs. Exhaustive
    Calorie-Limited Weight-Maximization Problem
    Group members: Diego Vela, dvela2@csu.fullerton.edu

## Dynamic Algorithm PseudoCode
    source = foods
    best = []

    size = foods.size()
    dpTable = [[0 for _ in maxCalories] for _ in size]

    for i = 1 to size:
        for int j = 0 to maxCalories:
            if source[i-1].calories <= j:
                dp[i][j] = max(dp[i-1][j], dp[i-1][j - source[i-1].calories]+ item[i-1].weight)
            else:
                dp[i][j] = dp[i-1][j]
    
    int i = size
    int cal = totalCalories

    while i > 0 and cal > 0:
        if dp[i][cal] != dp[i-1][cal]:
            add food at source[i-1] to best
            cal -= source[i-1].calories
        i = i-1
    
    return best


