#ifndef SXSMK_HD_H
#define SXSMK_HD_H
#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

int WINAPI st_init(int port,long baud);

int WINAPI st_exit(int icdev); 

int WINAPI st_card(int icdev,unsigned char _Mode,unsigned long *_Snr); 

int WINAPI st_request(int icdev,unsigned char _Mode,unsigned int *TagType); 

int WINAPI st_anticoll(int icdev,unsigned char _Bcnt,unsigned long *_Snr); 

int WINAPI st_select(int icdev,unsigned long _Snr,unsigned char *_Size); 

int WINAPI st_pro_reset(int icdev,unsigned char *rlen, unsigned char *rbuff); 

int WINAPI st_pro_command (int icdev, unsigned char slen, unsigned char * sbuff, unsigned char *rlen, unsigned char * rbuff); 

int WINAPI st_pro_halt(int icdev); 

int WINAPI st_setcardid (int icdev, int cardid); 

int WINAPI st_setcpupara (int icdev, int cardid,int cputype); 

int WINAPI st_cpureset (int icdev,unsigned char *rlen, unsigned char *rbuff); 

int WINAPI st_cpucommand (int icdev, unsigned char slen, unsigned char * sbuff, unsigned char *rlen, unsigned char * rbuff);

int WINAPI st_kb_open(int port, long baud); 

int WINAPI st_kb_close(int icdev); 

int WINAPI st_kb_downloadmainkey(int icdev,int destype,int mainkeyno,unsigned char *mainkey); 

int WINAPI st_kb_downloaduserkey(int icdev, int destype, int mainkeyno, int userkeyno, unsigned char *userkey); 

int WINAPI st_kb_activekey(int icdev, int mainkeyno,int userkeyno); 

int WINAPI st_kb_setpasslen(int icdev, int passlen); 

int WINAPI st_kb_settimeout(int icdev, int timeout); 

int WINAPI st_kb_getpin(int icdev, int type, unsigned char *planpin); 

int WINAPI st_kb_getenpin(int icdev, int type, unsigned char *cardno, unsigned char *planpin); 

int WINAPI st_SetTermID(int icdev, unsigned char *TermID); 

int WINAPI st_getTermID(int icdev, int type,unsigned char* TermID);

int WINAPI st_getDes(int icdev, int type, int mainkeyno, int userkeyno, char *src,  char *dst);




#ifdef __cplusplus
}
#endif

#endif