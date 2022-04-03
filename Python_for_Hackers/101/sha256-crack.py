#!/usr/bin/env python3
import sys
from pwn import *

def sha256_crack():
    """SHA256 password cracking"""

    wanted_hash = sys.argv[1]
    attempts = 0

    with open('/home/ret2basic/Arsenal/rockyou.txt', 'r', encoding='latin-1') as password_list,\
        log.progress(f'Attempting to crack: {wanted_hash}\n') as p:
        for password in password_list:
            password = password.strip('\n').encode('latin-1')
            password_hash = sha256sumhex(password)
            p.status(f'[{attempts}] {password.decode("latin-1")} == {password_hash}')

            if password_hash == wanted_hash:
                p.success(f'Password hash found after {attempts} attempts! {password} hashes to {wanted_hash}')
                exit()

            attempts += 1
        p.failure("Password cracking failed.")

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print('Usage: {sys.argv[0]} <sha256sum>')
        exit()

    sha256_crack()