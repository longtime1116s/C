#include <stdio.h>

// #define DEBUG

typedef enum {
        ERROR           = (1<<0),
        FRAMING_ERROR   = (1<<1),
        PARITY_ERROR    = (1<<2),
        CARRIER_ERROR   = (1<<3),
        CHANNEL_ERROR   = (1<<4),
} ErrorCode;

int main (void)
{
        //         2�ʿ�    10�ʿ�  16�ʿ�
        //      00101011        43      2B
        //      00011010        26      1A

        int         value1 = 43;
        int         value2 = 26;
        int         value3;
        ErrorCode   flags = 0;

        // AND  00001010        10
        printf("value1 & value2 : %d\n", value1 & value2);

        // OR   00111011        59
        printf("value1 | value2 : %d\n", value1 | value2);

        // XOR  00110001        49
        printf("value1 ^ value2 : %d\n", value1^value2);

        // NOT 11010100         -44
        printf("~value1         : %d\n", ~value1);

        // <<1 01010110         86
        value3 = value1 << 1;
        printf("value1 << 1     : %d\n", value3);

        // >>1 00010101         21
        value3 = value1 >> 1;
        printf("value1 >> 1     : %d\n", value3);

        // CHANNEL_ERROR �ե饰��Ω������
        flags |= CHANNEL_ERROR;
        // Ω�äƤʤ��ե饰
        if ( flags & PARITY_ERROR )
            printf("parity error!!\n");
        // Ω�äƤ���ե饰
        if ( flags & CHANNEL_ERROR )
            printf("channel error!!\n");
        // �ե饰�Υ��ꥢ
        flags &= ~CHANNEL_ERROR;
        if ( flags & CHANNEL_ERROR )
            printf("channel error!!\n");


#ifdef DEBUG
        printf("debug mode\n");
#endif // DEBUG
        return 0;
}

