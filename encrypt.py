from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
import os
import sys

key = os.urandom(32)
algo = algorithms.AES(key)
iv = os.urandom(16)
g = open('key.bin','wb')
g.write(key+iv)
g.close()
cip = Cipher(algo,mode=modes.CTR(iv))
encrypto = cip.encryptor()
f = open(sys.argv[1],'rb')
ct = encrypto.update(f.read())
f.close()
f = open(sys.argv[2],'wb')
f.write(ct)
f.close()