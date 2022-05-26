from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
import os
import sys

from rsa import decrypt



g = open('key.bin','rb')
gs = g.read()
g.close()
key = gs[0:32]
algo = algorithms.AES(key)
iv = gs[32:]
cip = Cipher(algo,mode=modes.CTR(iv))
decrypto = cip.decryptor()
f = open(sys.argv[1],'rb')
fr = decrypto.update(f.read())
f.close()
f = open(sys.argv[2],'wb')
f.write(fr)
f.close()