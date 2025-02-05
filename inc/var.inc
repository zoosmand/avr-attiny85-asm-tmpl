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
;                   PIN             delup   deldw
;                   00              02      04
LedBluePrm:     .dw (1<<LEDBLUE),   25,     25
LedGreenPrm:    .dw (1<<LEDGREEN),  25,     25
LedRedPrm:      .dw (1<<LEDRED),    25,     25


; --- SRAM data segment
.dseg
.org 0x0060
;                   cntr    owfcnt
QntCnt:         .dw 0x0000, 0x0000

;                   cntr
SecCnt:         .dw 0x0000

;                   prmadr  stkadr
;                    00 01   02 03
LedCache:       .dw 0x0000, 0x0000

;                   schcnt  delcnt  cmd
;                    00 01   02 03   04 05
.org 0x080
LedBlueStack:   .dw 0x0000, 0x0000, 0x0000
.org 0x090
LedGreenStack:  .dw 0x0000, 0x0000, 0x0000
.org 0x0a0
LedRedStack:    .dw 0x0000, 0x0000, 0x0000


; --- EEPROM data segment
.eseg
;  StartParam:	.db "Ready"
