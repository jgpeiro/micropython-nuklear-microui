import time
import machine
import uctypes

class Ili9488:
    HRES = 320
    VRES = 480

    CASET = 0x2A
    RASET = 0x2B
    RAMWR = 0x2C 
    def __init__( self, baudrate, cs, sck, mosi, miso, dc, rst, bl ):
        self.buf1 = bytearray( 1 )
        self.buf2 = bytearray( 2 )
        self.buf4 = bytearray( 4 )
        
        self.baudrate = baudrate
        self.cs  = cs
        self.sck = sck
        self.mosi= mosi
        self.miso= miso
        self.dc  = dc
        self.rst = rst
        self.bl = bl
        
        self.rst.value( 0 )
        self.cs.value( 1 )
        self.dc.value( 1 )
        self.bl.value( 1 )
        
        self.spi_init()
        self.reset()
        self.config()
    
    def reset( self ):
        self.rst.value( 0 )
        time.sleep_ms( 100 )
        self.rst.value( 1 )
        time.sleep_ms( 100 )
    
    def spi_init( self ):
        self.spi = machine.SPI( 
            4, 
            baudrate=self.baudrate, 
            polarity=0,
            phase=0,
            #sck=self.sck, 
            #mosi=self.mosi, 
            #miso=self.miso
        )
    
    def write_register( self, reg, buf ):
        #print("write_register", hex(reg), buf[0:10] )
        self.buf1[0] = reg

        self.dc.value( 0 )
        self.cs.value( 0 )
        self.spi.write( self.buf1 )
        self.cs.value( 1 )
        
        if( buf ):
            self.dc.value( 1 )
            self.cs.value( 0 )
            self.spi.write( buf )
            self.cs.value( 1 )
    
    def config( self ):
        #print( "config" )
        self.write_register( 0x01, b"" ) # Software Reset
        time.sleep_ms( 100 )
        self.write_register( 0x11, b"" ) # Sleep Out 
        time.sleep_ms( 20 )
        self.write_register( 0x3A, b"\x01" ) # Interface Pixel Format
        self.write_register( 0x36, bytearray([ # Memory Access Control
            0x00 << 2 | # Horizontal Refresh ORDER
            0x00 << 3 | # RGB-BGR Order
            0x01 << 4 | # Vertical Refresh Order
            0x00 << 5 | # Row/Column Exchange
            0x00 << 6 | # Column Address Order
            0x01 << 7   # Row Address Order
        ])  )
        self.write_register( 0x29, b"" ) # Display ON
        
    def set_window( self, x, y, w, h ):
        #print("set_window", x, y, w, h )
        x0 = x
        y0 = y
        x1 = x0 + w - 1
        y1 = y0 + h - 1

        self.buf4[0] = x0 >> 8
        self.buf4[1] = x0 & 0xFF
        self.buf4[2] = x1 >> 8
        self.buf4[3] = x1 & 0xFF
        self.write_register( Ili9488.CASET, self.buf4 )

        self.buf4[0] = y0 >> 8
        self.buf4[1] = y0 & 0xFF
        self.buf4[2] = y1 >> 8
        self.buf4[3] = y1 & 0xFF
        self.write_register( Ili9488.RASET, self.buf4 )
    
    def draw_bitmap( self, x, y, w, h, buf ):
        #print("draw_bitmap")
        self.set_window( x, y, w, h )
        self.write_register( Ili9488.RAMWR, buf )
    
    def clear( self, color ):
        #print("clear")
        color2 = color&0x07
        color2 |= color << 3
        
        buf = bytearray( self.HRES )
        for i in range( len(buf) ):
            buf[i] = color2
        
        self.set_window( 0, 0, self.HRES, self.VRES  )
        self.write_register( Ili9488.RAMWR, b"" )

        self.dc.value( 1 )
        self.cs.value( 0 )
        for j in range( self.VRES ):
            self.spi.write( buf )
        self.cs.value( 1 )


def test_ili9488():
    baudrate = 50_000_000
    print( "baudrate", baudrate )  

    rst = machine.Pin( machine.Pin.cpu.D8, machine.Pin.OUT )
    # SPI3
    #cs  = machine.Pin( machine.Pin.cpu.C13, machine.Pin.OUT )
    #sck = machine.Pin( machine.Pin.cpu.C10, machine.Pin.OUT )
    #mosi= machine.Pin( machine.Pin.cpu.C12, machine.Pin.OUT )
    #miso= machine.Pin( machine.Pin.cpu.C11, machine.Pin.IN  )
    
    # SPI4
    cs  = machine.Pin( machine.Pin.cpu.E10, machine.Pin.OUT )
    sck = machine.Pin( machine.Pin.cpu.E2, machine.Pin.OUT )
    mosi= machine.Pin( machine.Pin.cpu.E6, machine.Pin.OUT )
    miso= machine.Pin( machine.Pin.cpu.E5, machine.Pin.IN  )
    
    dc  = machine.Pin( machine.Pin.cpu.D9, machine.Pin.OUT )

    bl  = machine.Pin( machine.Pin.cpu.D10, machine.Pin.OUT )

    lcd = Ili9488( baudrate, cs, sck, mosi, miso, dc, rst, bl )
    print( "lcd.spi", lcd.spi )
    lcd.clear( 0x07 )
    
    buf = bytearray( 100//2 )
    for i in range( 100 ):
        lcd.draw_bitmap( 100, 100+i, 100, 1, buf )
    
    
    for i in range( 10 ):
        buf[i] = (0b0001 << 3) | 0b0001
    lcd.draw_bitmap( 100, 120, 100, 1, buf )
    for i in range( 10 ):
        buf[i] = (0b0010 << 3) | 0b0010
    lcd.draw_bitmap( 100, 125, 100, 1, buf )
    for i in range( 10 ):
        buf[i] = (0b0100 << 3) | 0b0100
    lcd.draw_bitmap( 100, 130, 100, 1, buf )
    
    
    for i in range( 10 ):
        buf[i] = (0b0001 << 3) | 0b0001
    lcd.draw_bitmap( 120, 100, 1, 100, buf )
    for i in range( 10 ):
        buf[i] = (0b0010 << 3) | 0b0010
    lcd.draw_bitmap( 125, 100, 1, 100, buf )
    for i in range( 10 ):
        buf[i] = (0b0100 << 3) | 0b0100
    lcd.draw_bitmap( 130, 100, 1, 100, buf )
    
    
    import framebuf
    WIDTH, HEIGHT = 100, 100
    fb_buf = bytearray( WIDTH*HEIGHT//2 )
    print( "len( fb_buf )", len( fb_buf ) )
    fb = framebuf.FrameBuffer(
        fb_buf,
        WIDTH,
        HEIGHT,
        framebuf.RGB111
    )
    fb.text("0x01", 0,  0, 0x01 )
    fb.text('0x01', 0, 10, 0x02)
    fb.text('0x01', 0, 20, 0x04)
    fb.text('0x01', 0, 30, 0x07)
    
    fb.fill_rect( 50,  0, 10, 10, 0x01 )
    fb.fill_rect( 50, 10, 10, 10, 0x02 )
    fb.fill_rect( 50, 20, 10, 10, 0x04 )
    fb.fill_rect( 50, 30, 10, 10, 0x07 )
    
    
    fb.hline(0, 50, 100, 0x01)
    fb.hline(0, 60, 100, 0x02)
    fb.hline(0, 70, 100, 0x04)
    
    fb.vline(50, 0, 100, 0x01)
    fb.vline(60, 0, 100, 0x02)
    fb.vline(70, 0, 100, 0x04)
    
    
    #for i in range( 100 ):
    #    fb.pixel(i, i, 0xFF )
    
    t0 = time.ticks_us()
    lcd.draw_bitmap( 100, 200, 100, 100, fb_buf )
    t1 = time.ticks_us()
    print( t1-t0 )
    print( (t1-t0)*(3.2*4.8) )
    print( 1e6/((t1-t0)*(3.2*4.8)) )
    
    
#test_ili9488()

#print("done")
