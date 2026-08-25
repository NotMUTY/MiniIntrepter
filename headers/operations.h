//operations.h

void opIp(char* arg, char* arg1);

void opGmp(char* arg, char* arg1);

void opSmp(char* arg, char* arg1);

void opImm(char* arg, char* arg1);

void opImm(char* arg, char* arg1);

void opAdd(char* arg, char* arg1);

void opSub(char* arg, char* arg1);

void opMul(char* arg, char* arg1);

void opDvd(char* arg, char* arg1);

void opCeq(char* arg, char* arg1);

void opCls(char* arg, char* arg1);

void opCgt(char* arg, char* arg1);

void opJmp(char* arg, char* arg1);

void opNjp(char* arg, char* arg1);

void opPrnt(char* arg, char* arg1);

void opHalt(char* arg, char* arg1);

void setupOps(int* _mem, int* _memp, int* _insp, int* _cf, int* _ef, int* _ovrr);
