# 2/12/2015
Ok, parsing now seems to work although I guess some more thorough testing should probably
be done before I get too excited. anyway the virtual machine has a million compile errors.
a lot of them seem to relate to some map, so that should be relatively easy to fix.

# 29/11/2015
ok motherfuckers, it's time to think! no wait actually all i'm doing is altering all of
parsing, loading and saving of instructions although mostly parsing so that it works with
the new label features. once that's done, it's time to make the compiler which goes from
some higher level code down to written assembly which can then be assembled by this down
to the binary format.

Ok so I need to alter the label manager so that it writes values into byte arrays rather
than actual single variables, in order to do so i'm also going to have to alter danylib,
meaning it will have to go to version 2.0.
Then I can get back to finishing the parser, which shouldn't take long after that since
only jump instructions use labels.

# 25/11/2015
no wait, it can write the addresses in at compile time. it will use a label manager which
both lets you make a reference to a label, or set the location of the label. In order to
put the addresses into the references to the label at the end, pointers to all of the
references can be registered with the label manager along with the label they point to,
and then they can just be filled in at the end.

# 24/11/2015
When the virtual machine reaches the end of the script it segmentation faults because I
didn't add end instructions, but I think I won't i'll just make it figure out that the end
is nigh.

Ok, so the feature that is still missing is labels. I need to make it that the parser
reads them and turns them into variables, the only problem is that the label doesn't come
first. but wait!! it still works, symbolise will simply create the label symbol if it
doesn't exist, and then when it gets to the label definition it sets it's value in the
symbol table. then somehow it needs to make virtual machine know these values. maybe it
can simply append some set instructions to the start of the program. the other problem
then is that labels will be taking up space meant for variables, and although this isn't
really designed or large programs, a maximum of 256 variables and labels seem a bit
restrictive. Instead I can have a separate label table and have them addressed with 2
bytes, then I can have special jump instructions that really do jump to the address in a
variable if I find I need them, but then also I can have jump instructions that use the
label table instead, and it can be provided at the start of the compiled code.

# 19/11/2015
ok so for some reason the arguments that call has are fucked in some way. Other than that
saving seems to work nicely.

# 18/11/2015
I'm making it that call instructions hold the length of all their arguments in their first
argument so that it can be saved, since otherwise you can't know when it is being written
what is a string and what is a variable.

ARRGGG wait since each argument is only a single char, it can't store the length. fear not
i'll make it 2 bytes and then it will be easily long enough.

# 15/11/2015
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
