#15/11/2015
I need to make it that script has a vector of pointers to instructions now since they are
uncopyable and therefore cannot be put directly into a vector in any way.

Passing out pointers to pointers is pretty unsafe, particularly since they can't be const
for some reason. I think I need to figure out some other way. Actually I can just iterate
over the vector of them or something storing the index and changing it on jumps, then
stopping when it hits an end instruction or it reaches the end.

# 12/11/2015
nopppp it shall be a single array of chars, this means that there can only be a maximum
of 256 variables, but that's a heap since they are basically the same as registers in
assembly language, and if I ever need more I can do what you would do in assembly language
and add stack functionality or something. yeah so then also strings will be held in this
beautiful array and shall be null terminated.

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
