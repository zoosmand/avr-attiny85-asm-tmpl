;
; ATTiny85 Assembller Template
; var.inc
; This file contains the code dedicated to definition of variables.
;
; Created: 25.01.2025 4:40pm
; Author : Dmitry Slobodchikov
;



; --- Program data segment
.cseg
;  WH1602A_symb: .db "Hallo!!!"
;                   PIN             empty
;                   00              01
LedBluePrm:     .db (1<<LEDBLUE),   0
LedGreenPrm:    .db (1<<LEDGREEN),  0
LedRedPrm:      .db (1<<LEDRED),    0


; --- SRAM data segment
.dseg
.org 0x0060
;                   cntr    owfcnt
QntCnt:         .dw 0x0000, 0x0000
;                   cntr
SecCnt:         .dw 0x0000
;                   schcnt  delcnt  cmd
;                    00 01   02 03   04 05
.org 0x070
LedBlueStack:   .dw 0x0000, 0x0000, 0x0000
.org 0x080
LedGreenStack:  .dw 0x0000, 0x0000, 0x0000
.org 0x090
LedRedStack:    .dw 0x0000, 0x0000, 0x0000


; --- EEPROM data segment
.eseg
;  StartParam:	.db "Ready"
