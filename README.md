# Microprosessors Logisim Circuits 

### Circuits
This repository contains a sequence of 5 CPUs' Logisim designs. The designs are taught in the course **CSE4117** at Marmara University. The Lecture notes can be found [here](http://www.marmaralectures.com/). You may find this repo helpful if you are taking the course or if you are just learning Logisim.

These CPUs are named after the evolutionary sequence of animals: Invertebrate, fish, frog, reptile, and bird. The properties of each are as follows:

- **Invertebrate**: A very simple: It consists a register bank and an ALU. At every clock edge, it performs a given ALU operation on any two given registers and writes the result back to any register. It does not have an external program or data memory and is not programmable. A human operator is necessary so set the necessary control signals between the clock edges.

- **Fish**: Same as Invertebrate, but has an external code memory. The desired ALU operations with the desired source and target registers are written into external memory as a sequence of ALU instructions, and at each clock edge one instruction is fetched from memory and executed. These ALU instructions are executed sequentially. There is no looping (ie, JUMP instruction) and no data memory (ie, Load, Load immediate and Store instructions)

- **Frog**: Load Immediate operation is added to fish.

- **Reptile**: Load, load immediate, store, jump and jump if zero instructions are added to frog.

- **Bird**: Stack instructions (push, pop, call and return) are added.

### Content
Each folder contains the circuts used to build a CPU along with an assembler, which is used to convert the assembly code to machine code that gets uploaded to the Memory elements in Logisim. The instruction formats, the Finite State Machines, and the Hardware designs for each CPU can be found in the lecture [notes](http://www.marmaralectures.com/).
