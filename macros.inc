
;******************************************************************************
; Function...: i2c_init
; Description: Intialize the controller as an I2C slave with the address
;              I2C_SLAVE_ADDRESS
; In.........: Nothing
; Out........: Nothing
.macro I2C_INIT
    ; Pin function when two-wire mode enabled according to the ATTiny861a
    ; datasheet p. 134:
    ;
    ;   "When the output driver is enabled for the SDA pin, the output
    ;   driver will force the line SDA low if the output of the USI Data
    ;   Register or the corresponding bit in the PORTA register is zero.
    ;   Otherwise, the SDA line will not be driven (i.e., it is released).
    ;   When the SCL pin output driver is enabled the SCL line will be forced
    ;   low if the corresponding bit in the PORTA register is zero, or by
    ;   the start detector. Otherwise the SCL line will not be driven."
    ;
    ; Pin setup for two-wire mode based on the information in the datasheet:
    ;
    ;   Pin | DDR | PORT | Notes
    ;   ----+-----+------+------------------------------------------------------
    ;   SDA |  0  |  1   | DDR selects input or output, value set by USIDR
    ;   CLK |  1  |  1   | DDR=1 enables the USI module to hold the CLK

    ; Pin setup
    cbi DDRB,I2C_SDA                ; SDA as input
    sbi DDRB,I2C_CLK                ; CLK as output, don't touch!
    sbi PORTB,I2C_SDA               ; SDA = high, don't touch!
    sbi PORTB,I2C_CLK               ; CLK = high, don't touch!

    ; Setup USI control & status register
    ldi r16, I2C_IDLE
    out USICR,r16
    ldi r16,I2C_COUNT_BYTE
    out USISR,r16
.endmacro
