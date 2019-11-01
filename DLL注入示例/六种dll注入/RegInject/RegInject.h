#ifndef _REGINJECT_H_
#define _REGINJECT_H_

#ifdef _cplusplus
extern "C"{
#endif

//
//利用AppInit_Dlls键值会被user32.dll调用LoadLibrary所加载
//
bool RegInject(PINJECT_PARAM);



#ifdef _cplusplus
}
#endif
#endif