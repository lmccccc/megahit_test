#ifndef INITIALDEF
#define INITIALDEF

#define K 100//kmer��kֵ
#define KMER_MAX_SIZE 100 //�kmer
#define NUM_PER_BYTE 2//ÿ��ACGT��4bit���룬��ÿbyte��2������
#define WORD_WIDTH 8/NUM_PER_BYTE//=4

//Ϊ����ȽϺ�����ʹ������Ĵ洢��ʽ
#define DUMMY 0b00000000//0
#define A 0b00010000//16
#define C 0b00100000//32
#define G 0b00110000//48
#define T 0b01000000//64
#define mA 0b01010000//80
#define mC 0b01100000//96
#define mG 0b01110000//112
#define mT 0b10000000//128
#endif
