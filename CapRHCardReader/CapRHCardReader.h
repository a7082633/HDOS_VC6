#ifndef RHCARDREADERAPI_H
#define RHCARDREADERAPI_H

#define RHCARDREADERAPI  extern "C" __declspec(dllexport)


RHCARDREADERAPI int ICC_Reader_Open(void);
RHCARDREADERAPI int ICC_Reader_Close(int ReaderHandle);
RHCARDREADERAPI int ICC_Reader_Reset(int ReaderHandle, int ICC_Slot_No, unsigned char *Response, int *RespLen);
RHCARDREADERAPI int ICC_Reader_PowerOff(int ReaderHandle, int ICC_Slot_No);
RHCARDREADERAPI int ICC_Reader_Application(int ReaderHandle, int ICC_Slot_No, int Length_of_Command_APDU, char *Command_APDU, char *Response_APDU, int *RespLen);
RHCARDREADERAPI int ICC_Reader_Version(char *info);
#endif