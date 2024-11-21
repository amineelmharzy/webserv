#!/usr/bin/python3

import os
import time
from http.cookies import SimpleCookie

# Timezone offset
timezone_offset = 3600

def parse_cookie(cookie_header = None):
    cookies = {}
    if not cookie_header:
        cookie_header = os.getenv('HTTP_COOKIE')
    cookies = SimpleCookie(cookie_header)
    return cookies

def set_cookie(cookie_name, cookie_value, expires, path = '/', domain = '', secure = False, httponly = True):

    set_cookie_header = f'Set-Cookie: {cookie_name}={cookie_value}; expires={time.strftime("%a, %d %b %Y %H:%M:%S GMT", time.gmtime(expires + timezone_offset))}; path=/'

    if domain:
        set_cookie_header += f"; domain={domain}"

    if secure:
        set_cookie_header += f"; secure"

    if httponly:
        set_cookie_header += f"; HttpOnly"

    print(f'{set_cookie_header}');

