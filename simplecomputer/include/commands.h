#ifndef COMMANDS_H
#define COMMANDS_H

#define NOP 0x0
#define CPUINFO 0x1

#define READ 0xA
#define WRITE 0xB

#define LOAD 0x14
#define STORE 0x15

#define ADD 0x1E
#define SUB 0x1F
#define DIVIDE 0x20
#define MUL 0x21

#define JUMP 0x28
#define JNEG 0x29
#define JZ 0x2A
#define HALT 0x2B

#define JNS 0x37
#define JP 0x3A
#define SUBC 0x42

#endif
