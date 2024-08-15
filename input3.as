.entry START
.extern func1
.extern VAR2

; Main program
START:  mov r2, ARR        
        mov r3, STR         
        add r2, r4          
        jsr func1          
        sub r3, VAR2        
        cmp r2, #0          
        bne PROCESS         
        inc r3             
        lea STR, r5         
        prn *r5             
PROCESS: add r1, ARR        
         mov r1, *r2        
         cmp r4, #-10       
         bne END            
         clr VAR1          
         jmp START
; Jump back to START
END:     stop     

; Data section
ARR:    .data 5, -15, 20, 25 
VAR1:   .data 10             
STR:    .string "hello"     
.entry VAR1
.extern VAR2