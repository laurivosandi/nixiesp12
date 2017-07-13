from time import sleep, localtime
from machine import Pin, Timer

clock = Pin(3, mode=Pin.OUT)
latch = Pin(0, mode=Pin.OUT)
data = Pin(2, mode=Pin.OUT)

lut = [
    0b1011, # 0
    0b1001, # 1
    0b1100, # 2
    0b1000, # 3
    0b0000, # 4
    0b0100, # 5
    0b0001, # 6
    0b0011, # 7
    0b0010, # 8
    0b1010, # 9
]  

def bitbang_bit(value):
    if value & 1:
        data.on()
    else:
        data.off()
    clock.on()
    clock.off()

def bitbang_digit(digit, width=4):
    for i in range(0,width):
        bitbang_bit(lut[digit] << i << 1 >> width)        
        
def bitbang_latch():
    latch.on()
    latch.off()

state = 0

timer = Timer(-1)

def schedule(delay=0):
    if delay:
        timer.init(period=1000, mode=Timer.ONE_SHOT, callback=dump)
    else:
        dump()
        
def dump_time(hour, minute, second):
    bitbang_bit(state)
    bitbang_digit(hour // 10)
    bitbang_bit(state)
    bitbang_bit(state)
    bitbang_bit(state)

    bitbang_bit(state)
    bitbang_digit(hour % 10)
    bitbang_bit(state)
    bitbang_bit(state)
    bitbang_bit(state)

    bitbang_bit(state)
    bitbang_digit(minute // 10)
    bitbang_bit(state)
    bitbang_bit(state)
    bitbang_bit(state)
    
    bitbang_bit(state)
    bitbang_digit(minute % 10)
    bitbang_bit(state)
    bitbang_bit(state)
    bitbang_bit(state)
    
    bitbang_bit(state)
    bitbang_digit(second // 10)
    bitbang_bit(state)
    bitbang_bit(state)
    bitbang_bit(state)

    bitbang_bit(state)
    bitbang_digit(second % 10)
    bitbang_bit(state)
    bitbang_bit(state)
    bitbang_bit(state)


def dump(t=None):
    global state
    year, month, day, hour, minute, second, _, millis = localtime()
    dump_time((hour + 3) % 24, minute, second)
    bitbang_latch()
    state = 1-state
    schedule(1000-millis)

schedule()
