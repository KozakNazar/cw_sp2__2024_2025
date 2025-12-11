#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: generator.h                 *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/config.h"

// TODO: CHENGE BY fRESET() TO END
#define C_CODER_MODE                   0x01
#define ASSEMBLY_X86_WIN32_CODER_MODE  0x02
#define MACHINE_X86_WIN32_CODER_MODE   0x04

extern unsigned char generatorMode;

//#define CODEGEN_DATA_TYPE int /*!*/

//#define START_DATA_OFFSET 0x800
//#define OUT_DATA_OFFSET (START_DATA_OFFSET + 0x800)

//#define M1 1024
//#define M2 1024

#define dataOffsetMinusCodeOffset 0x00004000ull
//#define dataOffsetMinusCodeOffset 0x00003000ull

#define baseOperationObjectOffset 0x000001D6ull
#define baseOperationOffset 0x000004FAull
#define putProcOffset 0x0000001Eull
#define getProcOffset 0x00000047ull


//unsigned long long int startCodeSize = 64 - 14; // 50 // -1

unsigned char detectMultiToken(struct LexemInfo* lexemInfoTable, enum TokenStructName tokenStructName);
unsigned char createMultiToken(struct LexemInfo** lexemInfoTable, enum TokenStructName tokenStructName);
#define MAX_ACCESSORY_STACK_SIZE 128
extern struct NonContainedLexemInfo lexemInfoTransformationTempStack[MAX_ACCESSORY_STACK_SIZE];
extern unsigned long long int lexemInfoTransformationTempStackSize;
unsigned char* outBytes2Code(unsigned char* currBytePtr, unsigned char* fragmentFirstBytePtr, unsigned long long int bytesCout);

#if 1
unsigned char* getObjectCodeBytePtr(unsigned char* baseBytePtr, unsigned char generatorMode);
unsigned char* getImageCodeBytePtr(unsigned char* baseBytePtr, unsigned char generatorMode);
unsigned char* makeCode(struct LexemInfo** lastLexemInfoInTable/*TODO:...*/, unsigned char* currBytePtr, unsigned char generatorMode);
void viewCode(unsigned char* outCodePtr, unsigned long long int outCodePrintSize, unsigned char align);
#endif

unsigned long long int buildTemplateForCodeObject(unsigned char* byteImage);
unsigned long long int buildTemplateForCodeImage(unsigned char* byteImage);
void writeBytesToFile(const char* output_file, unsigned char* byteImage, unsigned long long int imageSize);