;
; ATTiny85 Assembller Template
; display.inc
; This file contains display code. e.g. 1602A - two lines LCD display
;
; Created: 03.05.2025 1:19pm
; Author : Dmitry Slobodchikov
;

INIT_1602A:
  ; DELAY_MACRO 0x05, 0xc4 // TCCR0B (1<<CS02)|(1<<CS00) - 1024, 196, 25ms
  ; DELAY_MACRO 0x05, 0xc4 // TCCR0B (1<<CS02)|(1<<CS00) - 1024, 196, 25ms

  ; DELAY 50ms

  ; ldi ZH, high(2*A1602_init_bytes)
  ; ldi ZL, low(2*A1602_init_bytes)
  ; lpm lcdAddr, Z+
  ; ldi tmp, 0x07
  ; mov R0, tmp
  ; rcall CLEAR_TIMER
  
  ; _INIT_1602A_BYTE:
  ;   rcall I2CM_START
  ;   rcall A1602_SEND_ADDRESS
  ;   lpm txByte, Z+
  ;   rcall A1602_SEND_COMMAND
  ;   rcall I2CM_STOP
  ; lpm dClock, Z+
  ; lpm dRate, Z+
  ; rcall DELAY
  ;   dec R0
  ;   brne _INIT_1602A_BYTE
  
  ; rcall INIT_TIMER

