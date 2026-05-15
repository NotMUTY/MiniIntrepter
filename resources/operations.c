//operations.c
#include <stdio.h>
#include <stdlib.h>
#include "..\headers\operations.h"
#include "..\headers\util.h"

#define true 1
#define false 0

int resolve(char* str, int* mem){
    // constant way
    if (str[0] == '$'){
        if (s_strtoint(&str[1]) < 0){
            return -1;
        }
        return s_strtoint(&str[1]);
    }
    // memory way
    else{
        if (s_strtoint(str) < 0){
            return -1;
        }
        return mem[s_strtoint(str)];
    }
}

void opIp(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void)arg, arg1;
    mem[*memp] = *insp;
}

void opGmp(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void)arg, arg1;
    mem[*memp] = *memp;
}

void opSmp(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void)arg1;
    int tmp = resolve(arg, mem);

    if (tmp < 0){
        fprintf(stderr, "invalid argument at smp '%s', which it must be greater than '0' and less than '256'. \n", arg);
        *ef = true;
        return;
    }

    *memp = tmp;
}

void opImm(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void)arg1;
    
    int tmp = resolve(arg, mem);

    if (tmp < 0){
        fprintf(stderr, "invalid argument at smp '%s', which it must be greater than '0'. \n", arg);
        *ef = true;
        return;
    }

    mem[*memp] = tmp;
}

void opAdd(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    int tmp = resolve(arg, mem);
    int tmp1 = resolve(arg1, mem);

    if (tmp < 0 || tmp1 < 0){
        fprintf(stderr, "invalid argument at add '%s' or '%s' , which both must be greater than '0'. \n", arg, arg1);
        *ef = true;
        return;
    } 

    mem[s_strtoint(arg1)] = tmp + tmp1;
}

void opSub(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    int tmp = resolve(arg, mem);
    int tmp1 = resolve(arg1, mem);

    if (tmp < 0 || tmp1 < 0){
        fprintf(stderr, "invalid argument at sub '%s' or '%s' , which both must be greater than '0'. \n", arg, arg1);
        *ef = true;
        return;
    } 

    int tmp2 = tmp - tmp1;
    if (tmp2 < 0){
        tmp2 = 0;
    }

    mem[s_strtoint(arg1)] = tmp2;
    
}

void opMul(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    int tmp = resolve(arg, mem);
    int tmp1 = resolve(arg1, mem);

    if (tmp < 0 || tmp1 < 0){
        fprintf(stderr, "invalid argument at mul '%s' or '%s' , which both must be greater than '0'. \n", arg, arg1);
        *ef = true;
        return;
    } 

    int tmp2 = tmp * tmp1;
    if (tmp2 < 0){
        tmp2 = 0;
    }

    mem[s_strtoint(arg1)] = tmp2;
}

void opDvd(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    int tmp = resolve(arg, mem);
    int tmp1 = resolve(arg1, mem);

    if (tmp < 0 || tmp1 < 0){
        fprintf(stderr, "invalid argument at mul '%s' or '%s' , which both must be greater or equal than '0'. \n", arg, arg1);
        *ef = true;
        return;
    } 
    if (tmp1 == 0){
        fprintf(stderr, "cannot divide by 0, at dvd %s '%s'. \n", arg, arg1);
        *ef = true;
        return;
    }

    int tmp2 = tmp / tmp1;
    if (tmp2 < 0){
        tmp2 = 0;
    }

    mem[s_strtoint(arg1)] = tmp2;
}

void opCeq(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void) arg1;
    int tmp = resolve(arg, mem);

    if (tmp < 0){
        fprintf(stderr, "invalid argument at ceq '%s', which it must be greater than '0'. \n", arg);
        *ef = true;
        return;
    }

    *cf = mem[*memp] == tmp;
}

void opCls(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void) arg1;
    int tmp = resolve(arg, mem);

    if (tmp < 0){
        fprintf(stderr, "invalid argument at cls '%s', which it must be greater than '0'. \n", arg);
        *ef = true;
        return;
    }

    *cf = mem[*memp] < tmp;
}

void opCgt(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void) arg1;
    int tmp = resolve(arg, mem);

    if (tmp < 0){
        fprintf(stderr, "invalid argument at cgt '%s', which it must be greater than '0'. \n", arg);
        *ef = true;
        return;
    }

    *cf = mem[*memp] > tmp;
}

void opJmp(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void) arg1;
    int tmp = resolve(arg, mem);

    if (tmp < 0){
        fprintf(stderr, "invalid argument at jmp '%s', which it must be greater than '0' or equal to '0' . \n", arg);
        *ef = true;
        return;
    }

    if (*cf){
        *ovrr = true;
        *insp = tmp - 1;
    }
}

void opNjp(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void) arg1;
    int tmp = resolve(arg, mem);

    if (tmp < 0){
        fprintf(stderr, "invalid argument at njp '%s', which it must be greater than '0' or equal to '0', current: %d . \n", arg, tmp);
        *ef = true;
        return;
    }

    if (!(*cf)){
        *ovrr = true;
        *insp = tmp - 1;
    }
}

void opPrnt(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void) arg1;
    
    int tmp = resolve(arg, mem);

    if (tmp < 0){
        fprintf(stderr, "invalid argument at prnt '%s', which it must be greater than '0'. \n", arg);
        *ef = true;
        return;
    }

    printf("%d\n", tmp);

}

void opHalt(char* arg, char* arg1, int* mem, int* memp, int* insp, int* cf, int* ef, int* ovrr){
    (void)arg1;
    int tmp = resolve(arg, mem);

    if (tmp < 0){
        fprintf(stderr, "invalid argument at halt '%s', which it must be greater than '0'. \n", arg);
        *ef = true;
        return;
    }

    printf("program exit with code (%d)\n", tmp);
    *ef = true;

}
