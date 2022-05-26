import zlib
import sys

x= int(sys.argv[1])

if x==0:
    f = open(sys.argv[2].strip(),'rb')  # 2 is Video File, 3 is audio
    b1 = f.read()
    g = open(sys.argv[3].strip(),'rb')
    b2 = g.read()
    b1l = str(len(b1))
    while len(b1l) < 10:
        b1l = '0'+b1l
    b1l = str.encode(b1l)
    b = b1l + b1 + b2
    t = zlib.compress(b)
    with open(sys.argv[4].strip(),'wb') as f:
        f.write(t)
    f.close()
else:
    f = open(sys.argv[2].strip(),'rb')
    b = f.read()
    t = zlib.decompress(b)
    len1 = int((t[0:10]).decode('ASCII'))
    t = t[10:]
    t1 = t[0:len1]
    t = t[len1:]
    with open(sys.argv[3].strip(),'wb') as f:
        f.write(t1)
    with open(sys.argv[4].strip(),'wb') as f:
        f.write(t)
    f.close()