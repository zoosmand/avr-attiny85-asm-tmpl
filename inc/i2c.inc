;
; ATTiny85 Assembller Template
; 12c.inc
; This file contains 12c peripheral code.
;
; Created: 03.05.2025 1:21pm
; Author : Dmitry Slobodchikov
;

; --- I2C Start Condition
I2CM_START:
  sbi I2CPORT, SCL
  nop
  nop
  nop
  nop
  nop
  cbi I2CPORT, SDA
  nop
  nop
  nop
  nop
  cbi I2CPORT, SCL
  sbi I2CPORT, SDA
  in tmp, USISR
  sbr tmp, (1<<USISIF)
  out USISR, tmp
  ret

; --- I2C Stop Condition
I2CM_STOP:
  cbi I2CPORT, SDA
  sbi I2CPORT, SCL
  _I2CM_WAIT_SCK_HIGH:
    sbis I2CPIN, SCL
    rjmp _I2CM_WAIT_SCK_HIGH
  nop
  nop
  nop
  nop
  sbi I2CPORT, SDA
  nop
  nop
  nop
  nop
  in tmp, USISR
  sbr tmp, (1<<USIPF)
  out USISR, tmp
  ret

; --- I2C Transfer
I2CM_TRANSFER:
  in tmp, USICR
  sbr tmp, (1<<USITC)
  _I2CM_TRANSFER_START:
    nop
    nop
    nop
    nop
    nop
    out USICR, tmp
    _I2CM_TRANSFER_WAIT_SCL_HIGH:
      sbis I2CPIN, SCL
      rjmp _I2CM_TRANSFER_WAIT_SCL_HIGH
    nop
    nop  
    nop
    nop
    out USICR, tmp
    sbis USISR, USIOIF  
    rjmp _I2CM_TRANSFER_START
  nop
  nop
  nop
  nop
  nop
  ser tmp
  out USIDR, tmp
  sbi I2CDDR, SDA
  ret

; --- I2C Transfer Buffer
I2CM_TRANSFER_BUFFER:
  cbi I2CPORT, SCL
  in tmp, USISR
  sbr tmp, (1<<USIOIF)
  cbr tmp, (0xe<<USICNT0)
  out USISR, tmp
  rcall I2CM_TRANSFER
  ret

; --- I2C Transfer ACK/NACK
I2CM_TRANSFER_ACK:
  cbi I2CDDR, SDA ; Input
  in tmp, USISR
  sbr tmp, (1<<USIOIF)|(0xe<<USICNT0)
  out USISR, tmp
  rcall I2CM_TRANSFER
  ret

; --- I2C Send Slave Address
I2CM_SEND_ADDRESS:
  lsl txByte
  sbrs _EREG_, _I2CRWF_
  rjmp _I2CM_SEND_ADDRESS
  sbr txByte, (1<<0) ; 0 - write byte, 1 - read byte

  _I2CM_SEND_ADDRESS: 
    out USIDR, txByte
    rcall I2CM_TRANSFER_BUFFER
    rcall I2CM_TRANSFER_ACK
    sbic USIDR, 0
    rjmp _I2CM_SEND_ADDRESS_EXIT
    sbr _EREG_, (1<<_I2CERF_)
    rcall I2CM_STOP
  _I2CM_SEND_ADDRESS_EXIT:
    ret

; --- I2C Send Packet to Slave
I2CM_SEND_PACKET:
  out USIDR, txByte
  rcall I2CM_TRANSFER_BUFFER
  rcall I2CM_TRANSFER_ACK
  sbic USIDR, 0
  rjmp _I2CM_SEND_PACKET_EXIT
  sbr _EREG_, (1<<_I2CERF_)
  rcall I2CM_STOP
  _I2CM_SEND_PACKET_EXIT:
    ret

; --- I2C Receive Packet from Slave
I2CM_RECEIVE_PACKET:
  cbi I2CDDR, SDA ; Input
  rcall I2CM_TRANSFER_BUFFER
  in rxByte, USIDR
  rcall I2CM_TRANSFER_ACK
  ret

; --- 1602A Send Address
A1602_SEND_ADDRESS:
  mov txByte, tmp ; tmp (r16) carring the I2C device address
  rcall I2CM_SEND_ADDRESS
  ret

; --- 1602A Send Half Byte
A1602_SEND_NIBBLE:
  andi txByte, 0xf0
  sbrc _EREG_, _1602RSF_
  sbr txByte, (1<<_Rs)
  sbr txByte, (1<<_E)
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
  cbr _EREG_, (1<<_1602RSF_)
  rcall A1602_SEND_PACKET
  ret

; --- 1602A Send Data
A1602_SEND_DATA:
  sbr _EREG_, (1<<_1602RSF_)
  rcall A1602_SEND_PACKET
  ret
