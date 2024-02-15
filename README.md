
Diego Vela - Dvela2@csu.fullerton.edu

This program simulates a list of 2n disks of alternating colors light(0) and dark(1).
An alternate algorithm is used to sort the light disks to the left and the dark disks to the right with
a O(n^2) run time complexity.

PseudoCode:
    
    for i = 0 to n do 
        for j = i%2 to n do
            if j = light and j+1 = dark
                swap j and j+1
            endif
            j += 2
        endfor
    endfor
    return array

Mathematical Analysis
