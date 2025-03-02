It sounds like you're asking about the trade-offs of using recursion in problem-solving and when recursion is preferred or not preferred based on certain criteria. Here's an answer that should address your questions:

**1. When is recursion less accepted?**

Recursion might not be the best choice when:

a. **Space Efficiency is Crucial**: Recursive solutions often consume more memory than iterative counterparts due to the use of the call stack. Each recursive call adds a new layer to the stack. If memory consumption is a major concern, recursion might not be the best choice.

b. **Performance is a Top Priority**: Recursive functions usually have overhead due to the function calls. In some scenarios, the iterative version of a solution could be faster.

c. **Predictability is Important**: For problems with potentially high recursive depth, there's always a risk of a stack overflow error. Iterative solutions tend to be more predictable in terms of memory usage.

d. **Platform or Language Limitations**: Some programming languages or platforms might have limitations or might not optimize recursive calls as well as others.

**2. When is the recursive approach preferred?**

Recursion is often the first choice when:

a. **Problem Breaks Down Naturally**: If the problem can be naturally divided into smaller sub-problems of the same kind, recursion can be a straightforward approach. For instance, problems like tree traversals, the Tower of Hanoi, and the Fibonacci sequence can be intuitively understood using recursion.

b. **Clarity and Elegance**: Recursive solutions are often more concise and easier to understand than their iterative counterparts, especially for problems that are inherently recursive. This can make the code more maintainable.

c. **Backtracking is Needed**: In problems where you need to explore multiple solutions and backtrack if a certain path is not viable (like many combinatorial problems), recursion can be a natural fit.

d. **Divide and Conquer**: For problems where the divide and conquer strategy is applicable (e.g., merge sort), recursion provides an elegant solution.

In conclusion, the decision to use recursion or iteration often depends on the nature of the problem, the constraints of the environment, and sometimes personal or team preferences. Both approaches have their merits and can be powerful when applied in the right context.