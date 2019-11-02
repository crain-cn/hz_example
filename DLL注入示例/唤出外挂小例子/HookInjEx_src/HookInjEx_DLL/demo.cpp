#include <Windows.h>
/*
*/
/**
@name  加密函数
*/
void WINAPI encrypt(int addr, int val) 
{ 
        __asm 
        { 
          pushad; 
                 MOV EBX,8 
          MOV ECX,0x1BD4FA0; 
          MOV ECX,DWORD PTR DS:[ECX] 
          MOV EDI,DWORD PTR SS:[EBX+EBP] 
          MOV EAX,DWORD PTR DS:[EDI] 
                 MOV ECX,DWORD PTR DS:[ECX+44h] 
          MOV EDI,0x1BD51A0 
          MOV EDI,DWORD PTR DS:[EDI] 
                   SHL EAX,2 
          LEA ESI,DWORD PTR DS:[EAX+ECX] 
                  XOR ESI,EDI 
          XOR ESI,DWORD PTR SS:[EBX+EBP+4] 
          MOV DWORD PTR DS:[EAX+ECX],ESI 
          popad; 
                  NOP 
          NOP 
        } 
 
} 



DWORD WINAPI Decrypt(DWORD Val) 
{ 
        __asm 
        { 
     mov eax, 0x1BD51A0; 
     mov eax, [eax]; 
     mov ebx, eax; 
 
         mov eax, 0x1ECCDF4; 
     mov eax, [eax]; 
     mov ecx, eax; 
 
         mov eax, Val 
     mov edx, [ecx+44h] 
     shl eax,2; 
     mov esi, [edx+eax]; 
     add edx, eax; 
     xor esi, edx; 
     mov edx, [ecx+48h]; 
     add eax, edx; 
     mov edx, [eax] 
     xor edx, eax 
     xor esi, ebx 
         mov eax, esi 
 
        } 
} 


/**
	adrr   需要提供十进制的人物基址
	X  轴距离水平方向
	Y  轴距离 从你看屏幕的方向出发，前后位置
	Z  轴距离 人物的上下位置
	Val 这里是技能的伤害，但是有些技能不能调节伤害，所以也就无效，不过通常是有效的
	ID, 这里是技能的ID，需要什么技能就在这里填写相关的代码就可以了。
*/
void WINAPI perattact(DWORD adrr,DWORD X,DWORD Y,DWORD Z,DWORD Val,DWORD Id)
{
	__asm 
    {
		mov esi,[ebp+08h]
		mov esi,[esi]
		mov eax,01031AF0h
		mov eax,[eax]
		mov ecx,01031AF4h
		mov ecx,[ecx]
		push 00h
		push 00h
		mov edx,[esi]
		push eax
		push ecx
		push 00h
		push 04h
		push [ebp+14h]
		push [ebp+10h]
		push [ebp+0Ch]
		push 00h
		push 00h
		push [ebp+18h]
		push [ebp+1Ch]
		mov ecx,esi
		call [edx+000002D4h]

	}

}
/**
人物石化功能
*/
void stoney(DWORD addr)
{
	perattact (addr, -40, -40, 0, 999999, 899987);
	perattact (addr, 20, 20, 0, 999999, 899987);
	perattact (addr, 0, 0, 0, 999999, 899987);
	perattact (addr, 40, 40, 0, 999999, 899987);
	perattact (addr, 20, 20, 0, 999999, 899987);

}