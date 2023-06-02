###########################
# micro ui with g474
###########################
import time
import machine
import framebuf
import gc

#import ili9488
import st7789
import xpt2046
import microui

###########################
# LCD and TSC Initialization
###########################
lcd_baudrate = 50_000_000
tsc_baudrate = 1_000_000
lcd_spi_sck = machine.Pin( machine.Pin.cpu.E2, machine.Pin.OUT )
lcd_spi_mosi= machine.Pin( machine.Pin.cpu.E6, machine.Pin.OUT )
lcd_spi_miso= machine.Pin( machine.Pin.cpu.E5, machine.Pin.IN, machine.Pin.PULL_UP  )

tsc_spi_sck = machine.Pin( machine.Pin.cpu.C10, machine.Pin.OUT )
tsc_spi_mosi= machine.Pin( machine.Pin.cpu.C12, machine.Pin.OUT )
tsc_spi_miso= machine.Pin( machine.Pin.cpu.C11, machine.Pin.IN, machine.Pin.PULL_UP  )

lcd_dc  = machine.Pin( machine.Pin.cpu.D9, machine.Pin.OUT )
lcd_rst = machine.Pin( machine.Pin.cpu.D8, machine.Pin.OUT )
lcd_bl  = machine.Pin( machine.Pin.cpu.D10, machine.Pin.OUT )

lcd_cs  = machine.Pin( machine.Pin.cpu.E10, machine.Pin.OUT )
tsc_cs  = machine.Pin( machine.Pin.cpu.C13, machine.Pin.OUT )
tsc_irq = None

# TSC calibration values
AX, BX = 0.257, -25.074
AY, BY = 0.169, -14.307
tsc = xpt2046.Xpt2046( tsc_baudrate, tsc_cs, tsc_spi_sck, tsc_spi_mosi, tsc_spi_miso, ax=AX, bx=BX, ay=AY, by=BY )

lcd = st7789.St7789( lcd_baudrate, lcd_cs, lcd_spi_sck, lcd_spi_mosi, lcd_spi_miso, lcd_dc, lcd_rst, lcd_bl )
#lcd = ili9488.Ili9488( lcd_baudrate, lcd_cs, lcd_spi_sck, lcd_spi_mosi, lcd_spi_miso, lcd_dc, lcd_rst, lcd_bl )
lcd.clear( 0x0000 )
lcd.bl.value(1)


###########################
# FB and UI initialization
###########################
WIDTH, HEIGHT = 480, 320
WIDTH_DIV, HEIGHT_DIV = 1, 4

gc.collect()
fb_buf = bytearray( WIDTH*HEIGHT//(HEIGHT_DIV*WIDTH_DIV)*2 )
print( "len( fb_buf )", len( fb_buf ) )

fb = framebuf.FrameBuffer( fb_buf, WIDTH//WIDTH_DIV, HEIGHT//HEIGHT_DIV, framebuf.RGB565 )

mu = microui.microui()


###########################
# User Interface
###########################
def build_ui( ctx ):
    ctx.begin()
    if( ctx.begin_window_ex( "Demo", (50,50,200,150), 0 ) ):
        ctx.layout_row( ( 80, 80 ), 20 )
        if( ctx.button( "Button 1" ) ):
            print( "Button 1" )
        if( ctx.button( "Button 2" ) ):
            print( "Button 2" )
        ctx.end_window()
    ctx.end()



###########################
# Main loop
###########################
down_bck = 0
try:
    while( True ):
        # Read TSC
        x, y = tsc.read()
        if( x and x > 10 and y > 10 ):
            #print( x, y )
            down = 1
            x2 = x
            y2 = y
        else:
            down = 0
        
        # GUI events
        # Note: We need to process UI twice when on TSC events
        if( down and not down_bck ):
            mu.input_mousemove( x2, y2 )
            build_ui(mu)
            mu.input_mousedown( x2, y2, mu.MOUSE_LEFT )

        if( down and down_bck ):
            mu.input_mousemove( x2, y2 )
        
        if( not down and down_bck ):
            mu.input_mousemove( x2, y2 )
            build_ui(mu)
            mu.input_mouseup( x2, y2, mu.MOUSE_LEFT )

        elif( not down and not down_bck ):
            pass
        down_bck = down
        
        # GUI build
        build_ui(mu)
        
        # LCD draw
        lcd.spi_init() # Reinit LCD SPI in the case is shared with TSC spi
        for i in range( HEIGHT_DIV ):
            for j in range( WIDTH_DIV ):
                # Draw UI on FB
                fb.fill(0x0000)
                # This methid draws microui commands into the frame buffer using upy fb methods
                mu.draw(
                    j*WIDTH//WIDTH_DIV, i*HEIGHT//HEIGHT_DIV,
                    fb
                )
                
                # Draw FB on LCD
                lcd.draw_bitmap(
                    j*WIDTH//WIDTH_DIV, i*HEIGHT//HEIGHT_DIV,
                    WIDTH//WIDTH_DIV, HEIGHT//HEIGHT_DIV,
                    fb_buf
                )
        
        time.sleep_ms( 10 )
    
except KeyboardInterrupt as e:
    print( "KeyboardInterrupt", e )

finally:   
    pass

print("done")


