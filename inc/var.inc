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
;                   PIN             delup   deldw
;                   00              02      04
LedBluePrm:     .dw (1<<LEDBLUE),   12,     25
LedGreenPrm:    .dw (1<<LEDGREEN),  25,     25
LedRedPrm:      .dw (1<<LEDRED),    25,     25


A1602_init_bytes: .db 0x27, 0x03, 0x04, 0x82, 0x03, 0x04, 0x82, 0x03, 0x04, 0x05, 0x02, 0x04, 0x30, 0x28, 0x03, 0x05, 0x0c, 0x03, 0x05, 0x01, 0x04, 0x30
/*
  0x27 - LCD WH1602 I2C address
  0x03 - init command, 0x04, 0x82 - TCCR0B (1<<CS02) - 265, 130, 4.1ms
  0x03 - init command, 0x04, 0x82 - TCCR0B (1<<CS02) - 265, 130, 4.1ms
  0x03 - init command, 0x04, 0x05 - TCCR0B (1<<CS02) - 265, 5, 150us
  0x02 - init command, 0x04, 0x30 - TCCR0B (1<<CS02) - 265, 48, 1.53ms
  0x28 - init command, 0x03, 0x05 - TCCR0B (1<<CS01)|(1<<CS00) - 64, 5, 39us
  0x0c - init command, 0x03, 0x05 - TCCR0B (1<<CS01)|(1<<CS00) - 64, 5, 39us
  0x01 - init command, 0x04, 0x30 - TCCR0B (1<<CS02) - 265, 48, 1.53ms

  0x03 - 4-bit initialization
  0x02 - Cursor at the top-left position
  0x28 - 4-bit bus, 2 lines display (1602 model)
  0x0c - Allow output without cursor
  0x01 - Clear display
*/
A1602_symb: .db "Hallo!!!"
/*
	0x80 - Clear display
	0x48 - H
	0x54 - T
	0x87 - R
*/


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
