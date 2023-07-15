from Crypto.Cipher import AES

# Ex 1 - Lab 6

print('----------------------------------')
print('-----------Exercitiu 1 -----------')
print('----------------------------------')

l = int(input("l = "))
c_list = []
for i in range(l):
    c_list.append(int(input('> Coefficient c' + str(i+1) + ' : ')))

c_list.reverse() # So that the first coefficient in the list correlates to the first element of the seed

initial_seed = []
for i in range(l):
    initial_seed.append(int(input('> Stage s' + str(i) + ' : ')))

seed = initial_seed.copy()
output = []
counter = 0
flag = 1
# print(seed)
while flag:
    sum = 0
    for i in range(l):
        sum += seed[i] * c_list[i]

    crt_new_stage = sum % 2
    output.append(str(seed.pop(0)))
    seed.insert(len(seed), crt_new_stage)
    counter += 1
    if seed == initial_seed:
        flag = 0

print('\nPeriod: ' + str(counter))
print('Output: ' + ','.join(output) + '\n\n')

# Ex 2 - Lab 6

from Crypto.Util.Padding import pad

print('----------------------------------')
print('-----------Exercitiu 2 -----------')
print('----------------------------------\n')

key = b'O cheie oarecare'
data = b'testtesttesttesttesttesttesttesttesttesttesttest'

cipher = AES.new(key, AES.MODE_ECB)

print(cipher.encrypt(data))

# A. Un text criptat simetric
# B. Este folosit ECB.
# C. Nu, deoarece textele identice sunt criptate la fel
# D. Dimensiune cheie si bloc: 16 bytes
# E. Ne folosim de padding /68
# F. Am modificat modul de operare cu CBC. Acesta rezolva problema de criptare simetrica a ECB-ului /69

key = b'O cheie oarecare'
data2 = b'test'

cipher = AES.new(key, AES.MODE_ECB)
cipher2 = AES.new(key, AES.MODE_CBC)

print(cipher.encrypt(pad(data2,16)))
print(cipher2.encrypt(data))

# Ex 3 - Lab 6

print('\n\n----------------------------------')
print('-----------Exercitiu 3 -----------')
print('----------------------------------\n')

from Crypto.Cipher import DES


# key1 = '\x?0\x00\x00\x00\x00\x00\x00\x00'
# key2 = '\x?0\x00\x00\x00\x00\x00\x00\x00'
#
# cipher1 = DES.new(key1, DES.MODE_ECB)
# cipher2 = DES.new(key2, DES.MODE_ECB)
#
# plaintext = "Provocare MitM!!"
# ciphertext = cipher2.encrypt(cipher1.encrypt(plaintext))

# => ciphertext = "G\xfd\xdfpd\xa5\xc9'C\xe2\xf0\x84)\xef\xeb\xf9"


def get_key(x: int):
    return (16 * x).to_bytes(1, byteorder="little") + b"\x00\x00\x00\x00\x00\x00\x00"

def encrypt_data(key_part, data):
    key = get_key(key_part)
    cipher = DES.new(key, DES.MODE_ECB)
    return cipher.encrypt(data)


def decrypt_data(key_part, data):
    key = get_key(key_part)
    cipher = DES.new(key, DES.MODE_ECB)
    return cipher.decrypt(data)


def MeetInTheMiddleAttack(plaintext, ciphertext):
    first_cipher = dict()

    for i in range(16):
        test_key_i = encrypt_data(i, plaintext)     # 16 keys tested
        if test_key_i not in first_cipher:
            first_cipher[test_key_i] = i

    results = []

    for i in range(16):
        test_key_i = decrypt_data(i, ciphertext)    # 16 keys tested
        if test_key_i in first_cipher and decrypt_data(first_cipher[test_key_i],
                                                       decrypt_data(i, ciphertext)) == plaintext:
            results.append((first_cipher[test_key_i], i))

    return results      # 32 total keys tested


print(MeetInTheMiddleAttack(b"Provocare MitM!!", b"G\xfd\xdfpd\xa5\xc9'C\xe2\xf0\x84)\xef\xeb\xf9"))