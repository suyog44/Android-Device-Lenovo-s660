#ifndef _CFG_CUST_COUNTRY_CODE_FILE_H
#define _CFG_CUST_COUNTRY_CODE_FILE_H

typedef struct
{
   char CUST_COUNTRY_CODE[16];
}File_CUST_COUNTRY_CODE_Struct;

#define CFG_FILE_CUST_COUNTRY_CODE_REC_SIZE    sizeof(File_CUST_COUNTRY_CODE_Struct)
#define CFG_FILE_CUST_COUNTRY_CODE_REC_TOTAL   1

#endif

