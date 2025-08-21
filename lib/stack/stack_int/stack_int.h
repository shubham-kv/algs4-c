#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef __int_stack_h
#define __int_stack_h

/** Stack of integers (LIFO order) */
struct IntegerStack;
typedef struct IntegerStack *IntStack;
typedef int64_t IntStackItem;

#define STACK IntStack
#define ITEM IntStackItem

/** Creates a growable stack of integers (LIFO order) on heap. */
STACK IntStack_Create();
 void IntStack_Free(STACK *stack);

/** Adds an integer to the stack. On success returns `0`, on failure
 * sets `errno` and returns `-1`. */
int IntStack_Push(STACK stack, ITEM integer);

/** Deletes and returns the most recently added integer from the stack, on failure
 * sets `errno` and returns `-1`. Use `IntStack_Size` or `IntStack_IsEmpty` to
 * determine if stack contains items.
 */
ITEM IntStack_Pop(STACK stack);

/** Returns the most recently added item from the stack, on failure
 * sets `errno` and returns `-1`. */
ITEM IntStack_Peek(STACK stack);

size_t IntStack_Size(STACK stack);
bool IntStack_IsEmpty(STACK stack);

/** Iterator to iterate over the integers in `struct IntegerStack` instance in
 * LIFO order. */
struct IntegerStackIterator;
typedef struct IntegerStackIterator *IntStackIter;

#define ITER IntStackIter

/** Creates an Iterator that yields the integers in `struct IntegerStack` in
 * LIFO order. */
ITER IntStackIter_Create(STACK stack);
void IntStackIter_Free(ITER *iterator);
bool IntStackIter_HasNext(ITER iterator);

/** If there is a next item to consume then it sets the out parameter `data` to
 * the next integer on stack and returns `0`, otherwise sets `errno` and returns
 * `-1`. */
int IntStackIter_GetNext(ITER iterator, ITEM *data);

#undef ITER
#undef ITEM
#undef STACK

#endif // __int_stack_h
