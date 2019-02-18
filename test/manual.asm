global _start
section .rodata
  splash: db "Touringmachine",0
  splashlen: equ $ - splash

section .text

_start:
  ;mov rsi, splash      ;   "Hello, world!\n",
  push splash
  call print

  mov rax, 60       ; exit(
  mov rdi, 0        ;   EXIT_SUCCESS
  syscall           ; );

print:
  push ebp
  mov ebp, esp
  push rax
  push rdi
  push rdx
  push rsi
  mov rax, 1 ;using syscall for print
  mov rdi, 1 ;using stdio
  mov rdx, 1 ;print char by char
  mov rsi, [ebp+8]
  beginprint:
    syscall
    add rsi,1
  cmp dword [rsi], 0
  jne beginprint

  ret