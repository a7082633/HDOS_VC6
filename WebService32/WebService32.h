#ifndef WEBSERVICE32_H
#define WEBSERVICE32_H


#ifdef __cplusplus
extern "C" {
#endif
char * __stdcall Authentication(char *addr,char *account,char *password,int doctype,int action);
char * __stdcall Test1();
int __stdcall Test2();
void __stdcall DeleteMemry();
#ifdef __cplusplus
}
#endif
#endif
