#ifndef _CFG_FTM_TEST_RESULT_FILE_H
#define _CFG_FTM_TEST_RESULT_FILE_H

typedef struct
{
   char FTM_TEST_RESULT[64];
}File_FTM_TEST_RESULT_Struct;

#define CFG_FILE_FTM_TEST_RESULT_REC_SIZE    sizeof(File_FTM_TEST_RESULT_Struct)
#define CFG_FILE_FTM_TEST_RESULT_REC_TOTAL   1

#endif

