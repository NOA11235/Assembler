LONG TEXTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT
;extranous text at the beginning and end of macro definition
macr macro_a I'M_EXTRANOUS_TEXT
sub #1,r1
add #2,r2
cmp #3,r2
endmacr I'M_EXTRANOUS_TEXT
;main:
MAIN: macro_a
prn r1
prn r2
bne END
mov r2,r3
END: stop