//vmemu.c

#include <stdio.h>
#include <stdlib.h>
#include "..\headers\vmemu.h"
#include "..\headers\operations.h"
#include "..\headers\util.h"

#define true 1
#define false 0



struct Opcode {
    int argCount;
    void (*opfunc)(char* arg, char* arg1, int* mem,
                   int* memi, int* insi, int* cf, int* ef, int* ovrr);
};

struct Opcode ip,
              gmp,smp,
              imm,
              add, sub, mul, dvd,
              ceq, cls, cgt,
              jmp, njp,
              prnt,
              halt;

typedef enum {
    OP_IP,
    OP_GMP,
    OP_SMP,
    OP_IMM,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DVD,
    OP_CEQ,
    OP_CLS,
    OP_CGT,
    OP_JMP,
    OP_NJP,
    OP_PRNT,
    OP_HALT
} OP;

void initOps(){
    ip.argCount = 0;
    ip.opfunc = opIp;

    gmp.argCount = 0;
    gmp.opfunc = opGmp;

    smp.argCount = 1;
    smp.opfunc = opSmp;

    imm.argCount = 1;
    imm.opfunc = opImm;

    add.argCount = 2;
    add.opfunc = opAdd;

    sub.argCount = 2;
    sub.opfunc = opSub;

    mul.argCount = 2;
    mul.opfunc = opMul;

    dvd.argCount = 2;
    dvd.opfunc= opDvd;
    
    ceq.argCount = 1;
    ceq.opfunc = opCeq;

    cls.argCount = 1;
    cls.opfunc = opCls;

    cgt.argCount = 1;
    cgt.opfunc = opCgt;

    jmp.argCount = 1;
    jmp.opfunc = opJmp;

    njp.argCount = 1;
    njp.opfunc = opNjp;

    prnt.argCount = 1;
    prnt.opfunc = opPrnt;

    halt.argCount = 1;
    halt.opfunc = opHalt;
}

void parseAndExecute(char** instructions, int iLen){
    
    /*
    printf("-----------DEBUGS-----------\n");
    for (int i = 0; i < iLen; i++){
        printf("token %d = [%s]\n", i, instructions[i]);
    }
    printf("-----------DEBUGE-----------\n\n\n");
    */

    int memory[256] = {0};
    int instructionI = -1;
    int memoryI = 0;
    int compareFlag = false;
    int errFlag = false;
    int overrideFlag = false;

    initOps();

    OP opNum;

    while (instructionI < iLen){
        if (overrideFlag){
            overrideFlag = false;
            continue;
        }
        
        instructionI++;

        {
        //decode the opcode
        if (compStr(instructions[instructionI], "ip"))
            opNum = OP_IP;

        else if (compStr(instructions[instructionI], "gmp"))
            opNum = OP_GMP;

        else if (compStr(instructions[instructionI], "smp"))
            opNum = OP_SMP;

        else if (compStr(instructions[instructionI], "imm"))
            opNum = OP_IMM;

        else if (compStr(instructions[instructionI], "add"))
            opNum = OP_ADD;

        else if (compStr(instructions[instructionI], "sub"))
            opNum = OP_SUB;

        else if (compStr(instructions[instructionI], "mul"))
            opNum = OP_MUL;

        else if (compStr(instructions[instructionI], "dvd"))
            opNum = OP_DVD;

        else if (compStr(instructions[instructionI], "ceq"))
            opNum = OP_CEQ;

        else if (compStr(instructions[instructionI], "cls"))
            opNum = OP_CLS;

        else if (compStr(instructions[instructionI], "cgt"))
            opNum = OP_CGT;

        else if (compStr(instructions[instructionI], "jmp"))
            opNum = OP_JMP;

        else if (compStr(instructions[instructionI], "njp"))
            opNum = OP_NJP;

        else if (compStr(instructions[instructionI], "prnt"))
            opNum = OP_PRNT;
        
        else if (compStr(instructions[instructionI], "halt"))
            opNum = OP_HALT;
        
        else{
            fprintf(stderr, "no valid operation: %s at token %d", instructions[instructionI], instructionI);
            freeInstructions(instructions, iLen);
            exit(1);
        }
        }

        switch (opNum)
        {
        case OP_IP:
            ip.opfunc(NULL, NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += ip.argCount;
            break;

        case OP_GMP:
            gmp.opfunc(NULL, NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += gmp.argCount;
            break;

        case OP_SMP:
            smp.opfunc(instructions[instructionI + 1], NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += smp.argCount;
            break;

        case OP_IMM:
            imm.opfunc(instructions[instructionI + 1], NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += imm.argCount;
            break;

        case OP_ADD:
            add.opfunc(instructions[instructionI + 1], instructions[instructionI + 2], memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += add.argCount;
            break;

        case OP_SUB:
            sub.opfunc(instructions[instructionI + 1], instructions[instructionI + 2], memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += sub.argCount;
            break;

        case OP_MUL:
            mul.opfunc(instructions[instructionI + 1], instructions[instructionI + 2], memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += mul.argCount;
            break;

        case OP_DVD:
            dvd.opfunc(instructions[instructionI + 1], instructions[instructionI + 2], memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += dvd.argCount;
            break;

        case OP_CEQ:
            ceq.opfunc(instructions[instructionI + 1], NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += ceq.argCount;
            break;

        case OP_CLS:
            cls.opfunc(instructions[instructionI + 1], NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += cls.argCount;
            break;

        case OP_CGT:
            cgt.opfunc(instructions[instructionI + 1], NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += cgt.argCount;
            break;

        case OP_JMP:
            jmp.opfunc(instructions[instructionI + 1], NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += jmp.argCount;
            break;

        case OP_NJP:
            njp.opfunc(instructions[instructionI + 1], NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += njp.argCount;
            break;

        case OP_PRNT:
            prnt.opfunc(instructions[instructionI + 1], NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += prnt.argCount;
            break;

        case OP_HALT:
            halt.opfunc(instructions[instructionI + 1], NULL, memory, &memoryI, &instructionI, &compareFlag, &errFlag, &overrideFlag);
            if (overrideFlag) break;
            instructionI += halt.argCount;
            break;

            
        default:
            freeInstructions(instructions, iLen);
            fprintf(stderr, "unexpected command: '%s'. \n", instructions[instructionI]);
            exit(1);
        }

        if (errFlag == true){
            freeInstructions(instructions, iLen);
            fprintf(stderr, "program exited due error or halt.");
            exit(1);
        }
        
    }

    /*
    printf("-----------DEBUGS-----------\n");
    for (int i = 0; i < 256; i++){
        printf("mem[%i] = %d \n", i,memory[i]);
    }
    printf("compareFlag: %d \n", compareFlag);
    printf("-----------DEBUGE-----------\n\n\n");
    */

    freeInstructions(instructions, iLen);
}
