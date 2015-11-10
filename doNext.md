# 10/11/2015
Ok so now I think having an array of ints that are either int literals or variables or
pointers to strings is not going to work because the size of a pointer can vary.
What I can do however is just make it that they have one array for ints/variables and
another for string literals. It won't even be much less readable since it is already
pretty unreadable.


# 9/11/2015
Functors are classes that just kinda encapsulate a function, and apparantly this is the
normal way to do this rather than function pointers. when you think about it, it won't be
any less efficient, or not much.
