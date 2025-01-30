;
; ATTiny85 Assembller Template
; var.inc
; This file contains the code dedicated to definition of variables.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;



; --- Variables & data
; Static data stored with the code
.cseg
;  WH1602A_symb: .db "Hallo!!!"


; SRAM data segment
.dseg
.org 0x0060
QntCnt:         .dw 0x0000, 0x0000
SecCnt:         .dw 0x0000
SchCnt:         .dw 0x0000
LedCnt:         .dw 0x0000
LedReg:         .dw 0x0000


; EEPROM data
.eseg
;  StartParam:	.db "Ready"
