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
; SchCntBlue:     .dw 0x0000
; SchCntGreen:    .dw 0x0000
; SchCntRed:      .dw 0x0000
.org 0x070
LedReg:         .dw 0x0000, 0x0000
;                   schcnt  paucnt  schtld  pautld  pause1  pause2  port    pin tr
;                    00 01   02 03   04 05   06 07   08 09   0a 0b   0c 0d   0e 0f
.org 0x0080
LedPrmBlue:     .dw 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
;                   pau1sr  pau2sr
;                    10 11   12 13   14 15   16 17   18 19   1a 1b   1c 1d   1e 1f
                .dw 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
.org 0x00a0
LedPrmGreen:    .dw 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
.org 0x00c0
LedPrmRed:      .dw 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000


; EEPROM data
.eseg
;  StartParam:	.db "Ready"
