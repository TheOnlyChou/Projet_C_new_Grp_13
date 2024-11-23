#ifndef UNTITLED1_STACK_H
#define UNTITLED1_STACK_H

/**
 * @brief Structure for the stack of pointers
 */
typedef struct s_stack
{
    void **values;
    int size;
    int nbElts;
} t_stack;

/**
 * @brief Function to create a stack
 * @param size : the size of the stack
 * @return the stack
 */
t_stack createStack(int);

/**
 * @brief Function to push a value in the stack
 * @param pointer to the stack
 * @param value : the value to push
 * @return none
 */
void push(t_stack *, void *);

/**
 * @brief Function to pop a value from the stack
 * @param : pointer to the stack
 * @return the value popped
 */
void *pop(t_stack *);

/**
 * @brief Function to get the top value of the stack
 * @param stack : the stack
 * @return the top value
 */
void *top(t_stack);

#endif //UNTITLED1_STACK_H