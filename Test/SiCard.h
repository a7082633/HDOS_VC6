#ifndef HD_SiCard_H
#define HD_SiCard_H


#ifdef __cplusplus
extern "C" {
#endif

int __stdcall IOpenPort(char *Dest);
int __stdcall IClosePort(char *Dest);
int __stdcall IReadCard(char *Source,char *Dest);
int __stdcall IWriteCard(const char *Source,char *Dest);

#ifdef __cplusplus
}
#endif
#endif
