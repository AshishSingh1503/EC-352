/*The average lifetime of an element in a stack is the expected number of push/pop operations that occur after an element is pushed and before it is popped.
This is an algorithm analysis concept, not a code-based one.

When you push an element into a stack:
New elements get pushed above it.
They must all be popped before your element is popped.
So the lifetime depends on how many elements are pushed after it.

If pushes and pops occur with equal probability (50% push, 50% pop), on average:
 Half of the pushes will go above the element
 Those elements must be popped first

Hence, the average number of operations before the element is popped is approximately equal to half the stack height after insertion.


If we assume:
Push and pop operations are equally likely,
Stack never underflows,
Sequence is long,

Then:
Average lifetime of an element in a stack = 2 operations
(1 push to insert it, on average 1 pop later to remove it)
This is a classical result in amortized analysis of stacks.

Why is average lifetime ≈ 2?
When push = pop in probability:
Half the time you push before popping → element stays longer
Half the time a pop happens soon → element leaves sooner
Over a long sequence, the expected number of extra operations before popping is 1.

So total:

Lifetime = Push operation + Expected wait time before pop
          = 1 + 1
          = 2 operations

The average lifetime of an element in a stack is 2 operations (1 push + 1 pop), assuming push and pop operations are equally likely.
*/