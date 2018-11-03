# RTTI
A simple example to show how to remove dynamic_cast from a code base

CMake based project, so it should be multi platform, but this is just an afternoons work, so don't blame me if that turns out to be hard.
There are two branches. 

master - here a show a project that uses two "widget" types and makes a widget list.
         For some reason, not shown, this fake-project finds it need to treat the widgets differently based on type.
         Around 4-commits in, it's starts to use RTTI - dynamic-cast to do this.
         While this is a contrived example, this a quite common problem on real projects.
         The next commits show one method of moving back to strongly typed code-base. This is done in steps.
         1) Disable RTTI (GCC flags, I'm afraid), introduce a non-compiler solution.
         2) Introduce a "policy" enum to seperate the type from decision of what action to take.
         3) Move the the action selection into the base object.
         4) Make the policy part of the base object description. I only use an enum value, but obviously the policy 
            could be an object in the syle of the policy pattern, (see wikipedia) something that is capable of manipluating the 
            object directly, but this is step too far for most projects.
 
 alternative-solution:
        here I explore the viewpoint that we made a key mistake when we decided to design the system to make iteration of a list
        the easiest part to write. Iterating through a list is rarely the most complicated operation of a system. Design should
        be used to make the most complicated thing simpler, not to make simple things even simpler.
        To show this I make a more complex ObjectList container. We remove the base type, and instead store the derived "widgets"
        in strongly typed containers. This also removes possible bugs from missing a virtual destructor, and many other common-traps.
        The "visitor-pattern" is used to model the iteration. The same effect could be achieved by implementing specialised iterators,
        but lists like this rarely need anything more than for_each loops.
        I then benchmarks the code to show the relative costs of
        a) iterating a list of unique pointers to base.
        b) A vector of variants (a nice quick and easy way of acheiving much the same thing)
        c) A tuple-of-vectors, with the object order stored as seperate list.
        both b+c are type-safe mathods, coming with much better error detection from the compiler.

I get these results on my machine. All 3 are O(n), as expected, but 
a) is 4-10 times slower than c
b) is .5 to 2 times slower than c (not bad actually and far less effort)
c) is obviously the fastest, as well as being type safe. Seems like a no brainer to me, especially as the templated code 
   can be easily reused.
   
   Much of the speed difference will be the difference between lists and vectors.
---------------------------------------------------------
Benchmark                  Time           CPU Iterations
---------------------------------------------------------
BM_OldList/100         10175 ns      10058 ns      69584
BM_OldList/500         50487 ns      49530 ns      14147
BM_OldList/1000       104610 ns     102713 ns       7066
BM_OldList/10000     1055900 ns    1026406 ns        705
BM_OldList/100000   19958377 ns   19164850 ns         43
BM_OldList/500000   89823990 ns   86676572 ns         14
BM_OldList_BigO       180.39 N     174.03 N 
BM_OldList_RMS             5 %          4 % 
BM_AltList/100          3615 ns       3483 ns     202312
BM_AltList/500         11328 ns      11157 ns      62753
BM_AltList/1000        21549 ns      21214 ns      33135
BM_AltList/10000      259935 ns     239418 ns       2865
BM_AltList/100000    3268405 ns    3243692 ns        216
BM_AltList/500000   16204747 ns   16021963 ns         43
BM_AltList_BigO        32.42 N      32.06 N 
BM_AltList_RMS             1 %          1 % 
BM_NewList/100          2677 ns       2614 ns     269666
BM_NewList/500          6853 ns       6461 ns     108485
BM_NewList/1000        11368 ns      11094 ns      63459
BM_NewList/10000       97891 ns      94380 ns       7450
BM_NewList/100000    1511307 ns    1503673 ns        467
BM_NewList/500000    7724882 ns    7638775 ns         90
BM_NewList_BigO        15.43 N      15.27 N 
BM_NewList_RMS             2 %          2 % 

     
