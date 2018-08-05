The program was running on my mac on ubuntu. But because of issues with my memory stick/ubuntu. (I am in contact with A.J.) I was forced to use my mac for working on this lab over the weekend. Now I am getting a segfault. Attached is a copy of the gdb session. The issue with the segfault is the “scanf("%d ",tempload[i][j]);” in the loadMatrix function. It seems as if its trying to access memory at 0x0. not sure why.

in gdb it shows that the pointer to the first slot of the array is an actual address. Not 0x0.

The method I chose to dynamically allocate the array is such that, accessing the array is easier, in that, I can just use subscript indexes [i][j]. 

I know the error causing the segfault is minor. Everything else works as is.
