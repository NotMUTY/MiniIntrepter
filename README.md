# MiniInterpreter
i made c-- intrepeter in c

to use it
  >> main.exe filename.cnn

and it should work.

also i have an example for getting factorial

the command set goes by:

a, b is integer >= 0, $a and $b is constant values.

n -> memory[n],
$n -> n

example>
 imm 5 executes memory[memory pointer] = memory[5]

 imm $5 executes memory[memory pointer] = 5
<


ip -> sets instruction pointer value to memory[memory pointer]

gmp -> sets memory pointer value to memory[memory pointer]
smp a or $a -> sets memory pointer to a (if a >= 0)

imm a or $a -> sets the value of the memory address to a

operations:
    example<
        add 1 5 executes memory[5] = memory[1] + memory[5]
    >

add a b -> set the value of b to a + b
sub a b -> set the value of b to a - b (if result is less than 0, result will be 0)
mul a b -> set the value of b to a * b
dvd a b -> set the value of b to a / b (if result is float, returns high integer)

ceq a -> sets the compareFlag to 1 if the value of the memory value of pointer equals to a
cls a -> sets the compareFlag to 1 if the value of the memory value of pointer less than a
cgt a -> sets the compareFlag to 1 if the value of the memory value of pointer greater than a

jmp a or $a -> sets the instruction pointer to a (if compareFlag equals to 1)
njp a or $a-> sets the instruction pointer to a (if compareFlag equals to 0)

prnt a or $a -> prints the value of address

halt a or $a-> quits the program with exit code a



it parses in runtime and executes.

idk what to say so...

if you have gcc just run in compile.bat and run in builds
