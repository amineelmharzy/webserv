#!/usr/bin/python3

import os
import json
import time
import binascii
import secrets
import cookies

_cookies = cookies.parse_cookie(None)

# Path to store session files
sessions_dir = '/tmp/sessions/'
os.makedirs(sessions_dir, exist_ok=True)
os.chmod(sessions_dir, 0o777)

def generate_session_id():
    return binascii.hexlify(secrets.token_bytes(16)).decode()

def get_session_file_path(session_id):
    return os.path.join(sessions_dir, f'{session_id}.json')

def start_session():
    session_id = _cookies['SESSION_ID'].value if 'SESSION_ID' in _cookies else None

    if session_id and os.path.exists(get_session_file_path(session_id)):
        with open(get_session_file_path(session_id), 'r') as f:
            session_data = json.load(f)
        if 'expires' in session_data and session_data['expires'] < time.time():
            delete_session_file(session_id)
            session_id = None
            session_data = None
    if not session_id or not os.path.exists(get_session_file_path(session_id)):
        session_id = generate_session_id()
        session_data = {}
        expires = time.time() + 600  # 10 minutes expiration
        session_data['expires'] = expires
        cookies.set_cookie('SESSION_ID', session_id, expires)
    
    return {'id': session_id, 'data': session_data}

def save_session(session):
    if not session:
        return
    session_file = get_session_file_path(session['id'])
    with open(session_file, 'w') as f:
        json.dump(session['data'], f)

def delete_session_file(session_id):
    session_file = get_session_file_path(session_id)
    if os.path.exists(session_file):
        os.remove(session_file)

def destroy_session(session_id = None):
    if session_id is None:
        session_id = _cookies['SESSION_ID'].value if 'SESSION_ID' in _cookies else None
    
    if session_id:
        delete_session_file(session_id)
        cookies.set_cookie('SESSION_ID', '', 0)

