# Green-Programming Dubitare

This project tries to achieve extremly low energy consumption and good performance when solving a word-frequency problem.



## Problem:

Given an [large article](test.in) and an integer n, the most n-th frequency words need to be found out and listed. If two words have the same frequency, then the word is considered as more frequent if it comes before another in the dictionary. 

The output should be like [this](test.out.txt).


## GreenCode

The energy consumed will be measured by GreenCode 

https://greencode.cs.txstate.edu/

GreenCode is the web interface of the Marcher system. Students, programmers, and researchers can compile, execute and profile the energy consumption of code within a web browser. 

You can find the information at https://greensoft.cs.txstate.edu/


## My approach:

The optimization related to algorithm design, parallel programing, and knowledge about ideal size of hash table.

My [baseline](./baseline.c) version takes around 57 joules to run, while my [optimized](optimized.c) version  takes about 30 joules, which is also the lowest amoung all participants.


## More details:

You can check the detailed report here: [Green Competition Report](GreenCompetitionReport.pdf)
