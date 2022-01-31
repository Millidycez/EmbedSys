import re

# 30 Jan 2022
# Simple UART encoder/decoder for Embedded Sys homework.

# 31 Jan 2022 - Added decodeStr function.

def bin2hex(bitstr):
    i = int(bitstr,2)
    return hex(i)

def bin2char(bitstr):
    return chr(int(bitstr,2))
def char2bin(char):
    return bin(ord(char))[2:].zfill(8)

# Store every decoded char as list element.
def decode(bitstr, samplingRate = 4, payloadLength = 8):
    arr = []
    # Finding (inside) bits starting with "0000"
    query = "0" * samplingRate
    # (inside) payload size 
    query += "(.{" + str(payloadLength*samplingRate) + "})"
    bitsArr = re.findall(query,bitstr,re.M)

    # Iterating through each packet
    for bits in bitsArr:
        i = payloadLength * samplingRate - 1
        s = ""
        while i > 0:
            s += bits[i] # Get the last elem from "0000" or "1111" Note that this might not work if real world example has noises like "1110", this function will get the "0" out, which is wrong.
            i -= samplingRate
        arr.append(bin2char(s))
    return arr
def decodeStr(bitstr, samplingRate = 4, payloadLength = 8):
    return ''.join(decode(bitstr,samplingRate,payloadLength))

def encode(charArr, samplingRate = 4, noiseLength = 1):
    noise = "1" * noiseLength # High value when not sending
    output = ""
    output += noise
    for char in charArr:
        b = char2bin(char)
        enc = "0" * samplingRate
        for bit in b[::-1]:
            enc += bit * samplingRate
        enc += "1" * samplingRate
        output += enc
        output += noise
    return output
    