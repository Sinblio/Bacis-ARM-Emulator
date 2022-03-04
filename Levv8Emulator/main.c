#include <stdio.h>
#include <stdlib.h>
#include <nss.h>

uint32_t endianConverter(uint32_t number);

void executeInstruction(uint32_t num);

void dump(uint32_t);

//global variables
long long mainmemory[32];
long long globalmemory[128];
int flags[14];

int main() {
    for(int i = 0; i < 32; i++) {
        mainmemory[i] = 0;
    }

    for(int i = 0; i < 128; i++) {
        globalmemory[i] = 0;
    }

    for(int i = 0; i < sizeof(flags); i++) {
        flags[i] = 0;
    }

    char *filename = "/home/ben/Downloads/test.machine";

    FILE *file;
    unsigned int *buffer;
    unsigned long length;

    //Open file
    file = fopen(filename, "rb");
    if (!file) {
        fprintf(stderr, "Unable to open file %s", filename);
        return 1;
    }

    fseek (file, 0, SEEK_END);
    length = ftell (file);
    fseek (file, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
        fread (buffer, 1, length, file);
    }
    fclose (file);
    uint32_t hex[length];

    for (int i = 0; i < length; i++) {
        hex[i] = endianConverter(buffer[i]);
        printf("\n%x ", hex[i]);
    }

    free(buffer);

    for (mainmemory[28] = 0; mainmemory[28] < sizeof(hex) / 4; mainmemory[28]++) {
        executeInstruction(hex[mainmemory[28]]);
    }

    dump(0);

    return 0;
}

uint32_t endianConverter(uint32_t number) {
    uint32_t num = number;
    uint32_t b0,b1,b2,b3;
    uint32_t res;

    b0 = (num & 0x000000ff) << 24u;
    b1 = (num & 0x0000ff00) << 8u;
    b2 = (num & 0x00ff0000) >> 8u;
    b3 = (num & 0xff000000) >> 24u;

    res = b0 | b1 | b2 | b3;

    return res;
}

void resetflags() {
    for(int i = 0; i < sizeof(flags); i++) {
        flags[i] = 0;
    }
}

void setflags(long long value) {
    resetflags();
    //EQ
    if (value == 0) {
        flags[0] = 1;
    }
    //NE
    if (value != 0) {
        flags[1] = 1;
    }
    //HS
    if (value >= 0) {
        flags[2] = 1;
    }
    //LO
    if (value < 0) {
        flags[3] = 1;
    }
    //MI
    if (value < 0) {
        flags[4] = 1;
    }
    //PL
    if (value >= 0) {
        flags[5] = 1;
    }
    //VS

    //VC

    //HI
    if (value > 0) {
        flags[8] = 1;
    }
    //LS
    if (value <= 0) {
        flags[9] = 1;
    }
    //GE
    if (value >= 0) {
        flags[10] = 1;
    }
    //LT
    if (value < 0) {
        flags[11] = 1;
    }
    //GT
    if (value > 0) {
        flags[11] = 1;
    }
    //LE
    if (value <= 0) {
        flags[11] = 1;
    }
}

uint32_t parsehigh(uint32_t num, int shift) {
    return (num << shift);
}

uint32_t parselow(uint32_t num, int shift) {
    return (num >> shift);
}

uint32_t parserm(uint32_t num) {
    uint32_t value = parsehigh(num, 11);
    value = parselow(value, 27);
    return value;
}

uint32_t parseshamnt(uint32_t num) {
    uint32_t value = parsehigh(num, 16);
    value = parselow(value, 26);
    return value;
}

uint32_t parsern(uint32_t num) {
    uint32_t value = parsehigh(num, 22);
    value = parselow(value, 27);
    return value;
}

uint32_t parserd(uint32_t num) {
    uint32_t value = parsehigh(num, 27);
    value = parselow(value, 27);
    return value;
}

uint32_t parsealu(uint32_t num) {
    uint32_t value = parsehigh(num, 10);
    value = parselow(value, 20);
    return value;
}

uint32_t parseopmini(uint32_t num) {
    uint32_t value = parsehigh(num, 20);
    value = parselow(value, 29);
    return value;
}

uint32_t parsedt(uint32_t num) {
    uint32_t value = parsehigh(num, 11);
    value = parselow(value, 22);
    return value;
}

uint32_t parsebr(uint32_t num) {
    uint32_t value = parsehigh(num, 6);
    value = parselow(value, 6);
    return value;
}

uint32_t parsecondbr(uint32_t num) {
    uint32_t value = parsehigh(num, 8);
    value = parselow(value, 13);
    return value;
}

uint32_t parsemov(uint32_t num) {
    uint32_t value = parsehigh(num, 11);
    value = parselow(value, 16);
    return value;
}

uint32_t parseop(uint32_t num) {
    return parselow(num, 21);
}

void add(uint32_t num) {
    int rm = parserm(num);
    int rn = parsern(num);
    int rd = parserd(num);
    mainmemory[rd] = mainmemory[rn] + mainmemory[rm];
}

void addi(uint32_t num) {
    uint32_t alu = parsealu(num);
    int rn = parsern(num);
    int rd = parserd(num);
    mainmemory[rd] = mainmemory[rn] + alu;
}

void and(uint32_t num) {
    uint64_t rm = mainmemory[parserm(num)];
    uint64_t rn = mainmemory[parsern(num)];
    int rd = parserd(num);
    int counter = 31;
    while (counter > -1) {
        int temp = 1 << counter;
        if (temp < rn && temp < rm) {
            mainmemory[rd] += temp;
        }
        if (temp < rn) {
            rn -= temp;
        }
        if (temp < rm) {
            rm -= temp;
        }
        counter -= 1;
    }
}

void andi(uint32_t num) {
    long long alu = parsealu(num);
    long long rn = mainmemory[parsern(num)];
    int rd = parserd(num);
    int counter = 31;
    while (counter > -1) {
        int temp = 1 << counter;
        if (temp < rn && temp < alu) {
            mainmemory[rd] += temp;
        }
        if (temp < rn) {
            rn -= temp;
        }
        if (temp < alu) {
            alu -= temp;
        }
        counter -= 1;
    }
}

void b(uint32_t num) {
    int b = parsebr(num);
    mainmemory[28] = b >> 2;
}

void bcond(uint32_t num) {
    int rd = parserd(num);
    if (flags[rd] == 1) {
        int b = parsecondbr(num);
        mainmemory[28] = b >> 2;
    }
}

void br(uint32_t num) {
    int rt = parserd(num);
    mainmemory[28] = mainmemory[rt];
}

void bl(uint32_t num) {
    int b = parsebr(num);
    mainmemory[30] = mainmemory[28];
    mainmemory[28] = b >> 2;
}

void cbnz(uint32_t num) {
    int rd = parserd(num);
    if (mainmemory[rd] != 0) {
        int b = parsecondbr(num);
        mainmemory[28] = b >> 2;
    }
}

void cbz(uint32_t num) {
    int rd = parserd(num);
    if (mainmemory[rd] == 0) {
        int b = parsecondbr(num);
        mainmemory[28] = b >> 2;
    }
}



void dump(uint32_t num) {
    printf("\nRegisters:\n");
    for (int i = 0; i < 32; i++) {
        uint64_t temp = mainmemory[i];
        printf("X%d 0x%08lx(%ld)\n", i, temp, temp);
    }

    printf("\n");

    for (int i = 0; i < sizeof(mainmemory) / 4; i ++) {
        printf("%08x   ", i * 8);

        uint64_t temp = mainmemory[i];
        int counter = 63;
        while (counter >= 0) {
            if (temp >= (1 << counter)) {
                printf("1");
                temp = temp - (1 << counter);
            } else {
                printf("0");
            }
            if (counter % 2 == 0) {
                printf(" ");
            }
            if (counter % 32 == 0) {
                printf(" ");
            }
            counter--;
        }

        printf("\n");
    }

    printf("\n\nMain Memory:\n");

    for (int i = 0; i < sizeof(globalmemory) / 4; i ++) {
        printf("%08x   ", i * 8);

        uint64_t temp = globalmemory[i];
        int counter = 63;
        while (counter >= 0) {
            if (temp >= (1 << counter)) {
                printf("1");
                temp = temp - (1 << counter);
            } else {
                printf("0");
            }
            if (counter % 2 == 0) {
                printf(" ");
            }
            if (counter % 32 == 0) {
                printf(" ");
            }
            counter--;
        }

        printf("\n");
    }
}

void eori(uint32_t num) {
    long long alu = parsealu(num);
    long long rn = mainmemory[parsern(num)];
    int rd = parserd(num);
    int counter = 31;
    while (counter > -1) {
        int temp = 1 << counter;
        if ((temp < rn || temp < alu) && !(temp < rn && temp < alu)) {
            mainmemory[rd] += temp;
        }
        if (temp < rn) {
            rn -= temp;
        }
        if (temp < alu) {
            alu -= temp;
        }
        counter -= 1;
    }
}

void halt(uint32_t num) {
    dump(num);
}

void ldur(uint32_t num) {
    int rn = parsern(num);
    int rd = parserd(num);
    int dt = parsedt(num);
    mainmemory[rd] = globalmemory[(rn + dt)/ 8];
}

void lsl(uint32_t num) {
    int shamnt = parseshamnt(num);
    int rn = parsern(num);
    int rd = parserd(num);
    mainmemory[rd] = mainmemory[rn] << shamnt;
}

void lsr(uint32_t num) {
    int shamnt = parseshamnt(num);
    int rn = parsern(num);
    int rd = parserd(num);
    mainmemory[rd] = mainmemory[rn] >> shamnt;
}

void mul(uint32_t num) {
    int rm = parserm(num);
    int rn = parsern(num);
    int rd = parserd(num);
    mainmemory[rd] = mainmemory[rn] * mainmemory[rm];
}

void orr(uint32_t num) {
    long long rm = mainmemory[parserm(num)];
    long long rn = mainmemory[parsern(num)];
    int rd = parserd(num);
    int counter = 31;
    while (counter > -1) {
        int temp = 1 << counter;
        if (temp < rn || temp < rm) {
            mainmemory[rd] += temp;
        }
        if (temp < rn) {
            rn -= temp;
        }
        if (temp < rm) {
            rm -= temp;
        }
        counter -= 1;
    }
}

void orri(uint32_t num) {
    long long alu = parsealu(num);
    long long rn = mainmemory[parsern(num)];
    int rd = parserd(num);
    int counter = 31;
    while (counter > -1) {
        int temp = 1 << counter;
        if (temp < rn || temp < alu) {
            mainmemory[rd] += temp;
        }
        if (temp < rn) {
            rn -= temp;
        }
        if (temp < alu) {
            alu -= temp;
        }
        counter -= 1;
    }
}

void prnl(uint32_t num) {
    printf("\n");
}

void prnt(uint32_t num) {
    int rd = parserd(num);
    printf("hex: %x dec: %d\n", rd, rd);
}

void stur(uint32_t num) {
    int rn = parsern(num);
    int rd = parserd(num);
    int dt = parsedt(num);
    globalmemory[(rn + dt)/ 8] = mainmemory[rd];
}

void sub(uint32_t num) {
    int rm = parserm(num);
    int rn = parsern(num);
    int rd = parserd(num);
    mainmemory[rd] = mainmemory[rn] - mainmemory[rm];
}

void subi(uint32_t num) {
    uint32_t alu = parsealu(num);
    int rn = parsern(num);
    int rd = parserd(num);
    mainmemory[rd] = mainmemory[rn] - alu;
}

void subis(uint32_t num) {
    uint32_t alu = parsealu(num);
    int rn = parsern(num);
    int rd = parserd(num);
    long long flag = mainmemory[rn] - alu;
    setflags(flag);
    mainmemory[rd] = mainmemory[rn] - alu;
}

void subs(uint32_t num) {
    int rm = parserm(num);
    int rn = parsern(num);
    int rd = parserd(num);
    long long flag = mainmemory[rn] - mainmemory[rm];
    setflags(flag);
    mainmemory[rd] = mainmemory[rn] - mainmemory[rm];
}

void udiv(uint32_t num) {
    int rm = parserm(num);
    int rn = parsern(num);
    int rd = parserd(num);
    mainmemory[rd] = mainmemory[rn] / mainmemory[rm];
}

void executeInstruction(uint32_t num) {
    int op = parseop(num);

    //ADD
    if (op == 0x458) {
        add(num);
    }

    //ANDI
    if (op >= 0x488 && op <= 0x489) {
        addi(num);
    }

    //AND
    if (op == 0x450) {
        and(num);
    }

    //ANDI
    if (op >= 0x490 && op <= 0x491) {
        andi(num);
    }

    //B
    if (op >= 0x0A0 && op <= 0x0BF) {
        b(num);
    }

    //B.cond
    if (op >= 0x2A0 && op <= 0x2A7) {
        bcond(num);
    }

    //BL
    if (op >= 0x4A0 && op <= 0x4BF) {
        bl(num);
    }

    //BR
    if (op == 0x6B0) {
        br(num);
    }

    //CBNZ
    if (op >= 0x5A8 && op <= 0x5AF) {
        cbnz(num);
    }

    //CBZ
    if (op >= 0x5A0 && op <= 0x5A7) {
        cbz(num);
    }

    //DUMP
    if (op == 0x7FE) {
        dump(num);
    }

    //EORI
    if (op >= 0x690 && op <= 0x691) {
        eori(num);
    }

    //HALT
    if (op == 0x7FF) {
        halt(num);
    }

    //LDUR
    if (op == 0x7C2) {
        ldur(num);
    }

    //LSL
    if (op == 0x69B) {
        lsl(num);
    }

    //LSR
    if (op == 0x69A) {
        lsr(num);
    }

    //MUL
    if (op == 0x48D || parseshamnt(num) == 0x1F) {
        mul(num);
    }

    //ORR
    if (op == 0x550) {
        orr(num);
    }

    //ORRI
    if (op >= 0x590 && op <= 0x591) {
        orri(num);
    }

    //PRNL
    if (op == 0x7FC) {
        prnl(num);
    }

    //PRNT
    if (op == 0x3FD) {
        prnt(num);
    }

    //STUR
    if (op == 0x7C0) {
        stur(num);
    }

    //SUB
    if (op == 0x658) {
        sub(num);
    }

    //SUBI
    if (op >= 0x688 && op <= 0x689) {
        subi(num);
    }

    //SUBIS
    if (op >= 0x788 && op <= 0x789) {
        subis(num);
    }

    //SUBS
    if (op == 0x758) {
        subs(num);
    }

    //UDIV
    if (op == 0x4DE || parseshamnt(num) == 0x03) {
        udiv(num);
    }
};
