###########################
# nuklear ui with g474
###########################
import time
import machine
import framebuf
import gc

import st7789
import xpt2046
import nuklear

###########################
# LCD and TSC Initialization
###########################
lcd_baudrate = 25_000_000
tsc_baudrate = 1_00_000
spi_sck = machine.Pin( machine.Pin.cpu.A5, machine.Pin.OUT )
spi_mosi= machine.Pin( machine.Pin.cpu.A7, machine.Pin.OUT )
spi_miso= machine.Pin( machine.Pin.cpu.A6, machine.Pin.IN, machine.Pin.PULL_UP  )
lcd_dc  = machine.Pin( machine.Pin.cpu.A8, machine.Pin.OUT )

lcd_rst = None
lcd_bl  = machine.Pin( machine.Pin.cpu.C7, machine.Pin.OUT )
lcd_cs  = machine.Pin( machine.Pin.cpu.B6, machine.Pin.OUT )
tsc_cs  = machine.Pin( machine.Pin.cpu.B5, machine.Pin.OUT )
tsc_irq = machine.Pin( machine.Pin.cpu.B3, machine.Pin.IN, machine.Pin.PULL_UP )

# TSC calibration values
AX, BX = 0.17571,-29.9520
AY, BY =-0.12669, 251.321
tsc = xpt2046.Xpt2046( tsc_baudrate, tsc_cs, spi_sck, spi_mosi, spi_miso, ax=AX, bx=BX, ay=AY, by=BY )


lcd = st7789.St7789( lcd_baudrate, lcd_cs, spi_sck, spi_mosi, spi_miso, lcd_dc, lcd_rst, lcd_bl )
#lcd = st7789.St7789( lcd_baudrate, lcd_cs, lcd_spi_sck, lcd_spi_mosi, lcd_spi_miso, lcd_dc, lcd_rst, lcd_bl )
lcd.clear( 0x0000 )
lcd.bl.value(1)

###########################
# FB and UI initialization
###########################
WIDTH, HEIGHT = 320, 240
WIDTH_DIV, HEIGHT_DIV = 1, 4

gc.collect()
buf = bytearray( 2*(WIDTH*HEIGHT)//(HEIGHT_DIV*WIDTH_DIV) )
print( "len(buf)", len(buf) )

fb = framebuf.FrameBuffer( buf, WIDTH//WIDTH_DIV, HEIGHT//HEIGHT_DIV, framebuf.RGB565 )

cmds = bytearray( 1024 )
pool = bytearray( 1024 )

nk = nuklear.Nk( cmds, pool )
nk.set_style(3)

###########################
# User Interface
###########################
def build_ui( nk ):
    if( nk.begin( "Nuklear for MicroPython!", [20, 20, 250, 100], nk.WINDOW_TITLE | nk.WINDOW_BORDER | nk.WINDOW_MOVABLE ) ):
        nk.layout_row_dynamic( 20, 2 )
        nk.label( "Label", nk.TEXT_CENTERED )
        if( nk.button_label( "Button" ) ):
            print( "Pressed" )
        nk.layout_row_end()
    nk.end()


###########################
# Main loop
###########################
try:
    x2, y2 = 0, 0
    while( True ):
        # Read TSC
        tsc.spi_init()
        x, y = tsc.read()
        if( x ):
            down = 1
            x2 = 320-x
            y2 = 240-y
        else:
            down = 0
        
        # GUI events
        nk.input_begin()
        nk.input_motion( x2, y2 )
        nk.input_button( 0, x2, y2, down )
        nk.input_end()
        
        # GUI build
        build_ui( nk )
        
        # LCD draw
        lcd.spi_init() # Reinit LCD SPI in the case is shared with TSC spi
        for i in range( HEIGHT_DIV ):
            for j in range( WIDTH_DIV ):
                # Draw UI on FB
                fb.fill(0x0000)
                # This methid draws nuklear commands into the frame buffer using upy fb methods
                nk.draw(
                    j*WIDTH//WIDTH_DIV,
                    i*HEIGHT//HEIGHT_DIV,
                    fb
                )
                # Draw FB on LCD
                lcd.draw_bitmap(
                    j*WIDTH//WIDTH_DIV,
                    i*HEIGHT//HEIGHT_DIV,
                    WIDTH//WIDTH_DIV,
                    HEIGHT//HEIGHT_DIV,
                    buf
                )
        nk.clear()
        time.sleep_ms( 10 )

except KeyboardInterrupt as e:
    print( "KeyboardInterrupt", e )

finally:   
    pass

print("done")