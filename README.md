# Hack Assembler
Hack Assembler is an assembler to translate Hack Assembly to Hack Machine code written in C. This assembler is part of a project from 
[Nand2Tetris Part 1](https://www.coursera.org/learn/build-a-computer?) where students design a simple 16 Bit Computer which is called the "Hack Computer". Students
starts off with creating logic gates from NAND to eventually build a simple operating computer.

Although I have made my solutions for the other projects in this course private (as well as most of my assignments from University), due to academic integrity. I felt that there was some flexibility to the very last assignment 
of this course that it would be very obvious to anyone if students plagarized my solution. The last assignment is about creating an assembler to translate Hack
Assembly to Hack Machine Code but there are two options for students to complete the assignment. The first method is to have students program an assembler in 
any language of their choice, and the other option is to have students manually translate assembly to machine code by hand to compensate for students who may not
have much programming knowledge.

This leads to a lot of possible solutions compare to the previous assignments where there is only so many ways to answer them in a somewhat acceptable manner.
I have decided to use C as my language of choice to create the assembler because a lot of assemblers that were written in high leve languages are actually 
written in C (from what I know). Writting an assembler in Java (the recommended way in the course), Python, or in Perl is probably a much "easier" way to 
write an assembler and is perhaps the main languages students use to implement the assembler. However, I want to first tackle this assignment in C to practice
my C programming skills. Perhaps I'll also implement the Hack Assembler in other languages such as C++, Perl and Rust as the complexity and size is just right
to refresh or learn the language in a decent enough depth.

The first version of this implementation will not be written as efficiently as I would have wanted it to be due to laziness. For instance, the current plan is to
have a linkedlist to store the symbol table rather than using a Hash Table so searching in the table would be O(n). I chose to implement the symbol table in my 
first version of the assembler using Linkedlist simply because it's easy to write and it's better than writting it using an array since the size is not known so
trying to expand the array could potentially increase runtime since memory may need to be copied to a new location
