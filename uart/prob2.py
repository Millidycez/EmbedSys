import uart

with open("uart/prob2.txt") as f:
    s = f.readline()

print(uart.decodeStr(s,8))
