Readme:


If we compare the real times when running the program in 1 thread all the way to 8 threads, we can see a pattern:

No. of threads     Real time 			User Time

1                  0m47.552s			0m47.568s
2		   0m23.919s			0m47.612s
4		   0m11.987s			0m47.644s
8		   0m6.457s			0m50.098s

The user time remains at about the same value, and the real time is 
 approximately User Time/No. of Threads. This points to the fact that 
 this program is 'Embarrasingly Parallel', and that the compiler doesn't
 need to work hard to make it run on multiple threads

