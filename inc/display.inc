;
; ATTiny85 Assembller Template
; display.inc
; This file contains display code. e.g. 1602A - two lines LCD display
;
; Created: 03.05.2025 1:19pm
; Author : Dmitry Slobodchikov
;

INIT_1602A:
  ; initial delay 50ms
  SIMPLE_DELAY 50000

  ldi ZH, high(2*A1602_init_bytes)
  ldi ZL, low(2*A1602_init_bytes)
  ldi tmp, 0x07
  mov R0, tmp
  lpm tmp, Z+
  
  _INIT_1602A_BYTE:
    rcall I2CM_START
    rcall A1602_SEND_ADDRESS
    lpm txByte, Z+
    rcall A1602_SEND_COMMAND
    rcall I2CM_STOP
    lpm _cntH, Z+
    lpm _cntL, Z+
    SIMPLE_DELAY
    dec R0
    brne _INIT_1602A_BYTE

  ret


; --- 1602A Send Address
A1602_SEND_ADDRESS:
  mov txByte, tmp ; tmp (r16) carring the I2C device address
  rcall I2CM_SEND_ADDRESS
  ret

; --- 1602A Send Half Byte
A1602_SEND_NIBBLE:
  andi txByte, 0xf0
  ; sbrc _EREG_, _1602RSF_
  CHK_FLAG_CLR DsplReg, _1602RSF_, _1602A_SEND_E
  ; sbr txByte, (1<<_Rs)
  SET_FLAG DsplReg, _Rs
  _1602A_SEND_E:
  ; sbr txByte, (1<<_E)
  SET_FLAG DsplReg, _E
  rjmp _1602A_SEND_NIBBLE_DATA
  _1602A_SEND_NIBBLE_ACK:
    cbr txByte, (1<<_E)
  _1602A_SEND_NIBBLE_DATA:
    rcall I2CM_SEND_PACKET
  sbrc txByte, _E
  rjmp _1602A_SEND_NIBBLE_ACK
  ret
  
; --- 1602A Send Packet
A1602_SEND_PACKET:
  push R0
  mov R0, txByte
  rcall A1602_SEND_NIBBLE
  swap R0
  mov txByte, R0
  rcall A1602_SEND_NIBBLE
  ldi txByte, 0x08
  rcall I2CM_SEND_PACKET
  pop R0
  ret

; --- 1602A Send Command
A1602_SEND_COMMAND:
  ; cbr _EREG_, (1<<_1602RSF_)
  CLR_FLAG DsplReg, _1602RSF_
  rcall A1602_SEND_PACKET
  ret

; --- 1602A Send Data
A1602_SEND_DATA:
  ; sbr _EREG_, (1<<_1602RSF_)
  SET_FLAG DsplReg, _1602RSF_
  rcall A1602_SEND_PACKET
  ret
