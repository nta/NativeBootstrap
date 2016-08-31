; Due to the nature of SSE we need to do some stack alignment for x64.
; This function replaces the __asm jmp OriginalEP used for x86.

_TEXT SEGMENT

; Set by PEReplacement.cpp
EXTERN OriginalEP:qword

; Called from PRReplacement.cpp::BootstrapCallback
PUBLIC ASM_Stackalign
ASM_Stackalign PROC

and rsp, 0FFFFFFFFFFFFFFF0h
mov rax, 0DEADDEADDEADDEADh
push rax

mov rax, qword ptr [OriginalEP]
jmp rax

ASM_Stackalign ENDP
_TEXT ENDS
END
