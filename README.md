Group Members:
Diego Vela

This program simulates a list of 2n disks of alternating colors light(0) and dark(1) being sorted
through an alternate algorithm and a lawnmower algorithm

PseudoCode for Lawnmower:
    
    for i= 0 < (n+1)/2 {
        for j = 0 < n-1 do {
            if j == dark and j+1 == light {
                swap elements at j
            }
        }
        for j = n > 0 do {
            if j == light and j-1 == dark {
                swap elements at j-1
            }
        }
    }

Mathematical Analysis for Lawnmower:

    SUMM(i = 0 to (n+1)/2 -1) * (SUMM(j = 0 to n-1 -1)*(4+1) + SUMM(j = n-1 to 0 +1)*(4+2)
    (n+1)/2   *  ((n-1)5 + (n-1)6)
    (n+1)/2   *  ((5n-5)+(6n-6))
    (n+1)/2   *   (11n-11)
    (11n^2 - 11n + 11n -11)/2
    (11n^2-11)/2 == O(n^2)

    Prove Lawnmower Algorithm exists in O(n^2) using limit
    for (11n^2-11)/2 >= cn^2 ==> Divide both sides by n^2
    (11n^2-11)/2n^2 >= c
    As the limit of n goes to infinity, 11n^2/2n^2 approaches 5.5
                                        -11/2n^2 approaches 0
    Since 5.5 > 0 we can say (11n^2-11)/2 exists in O(n^2)

PseudoCode for Alternate:
    
    for i=0 < n do {
        for j = i%2 < n do
            if j == 1 and j+1 == dark 
                swap elements at j
    }
    
Mathematical Analysis for Alternate:

    (SUMM(i = 1 to n) * (SUMM(j = 1 to n) * (4 + 1)))-n/2
    n * n * 5 - n/2
    5n^2 - 1/2(n) == O(n^2)

    Prove Alternate Algorithm exists in O(n^2) using limit
    for (5n^2-n/2) >= cn^2 ==> Divide both sides by n^2
    (5n^2-n/2)/2n^2 >= c
    As the limit of n goes to infinity, 5n^2/2n^2 approaches 5
                                        -n/4n^2 approaches 0
    Since 5 > 0 we can say (5n^2-n/2) exists in O(n^2)


