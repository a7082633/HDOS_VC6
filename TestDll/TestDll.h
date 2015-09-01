#ifndef MHC_CARDINTERFACE_H
#define MHC_CARDINTERFACE_H


#define MHC_CARDINTERFACE_API  extern "C" __declspec(dllexport)


MHC_CARDINTERFACE_API int __stdcall WriteData(char * data) ; //slot 1  User; slot 0x11 SAM1

#endif