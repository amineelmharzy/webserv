<?php

include_once('cookies.php');

$_COOKIE = parse_cookie();

if (!file_exists('/tmp/sessions/')) {
    mkdir('/tmp/sessions/', 0777, true);
}

// Define session management functions
function generate_session_id()
{
    return bin2hex(random_bytes(16));
}

function get_session_file_path($session_id)
{
    return "/tmp/sessions/{$session_id}.json";
}

function start_session()
{
    // Check if session ID is in the cookie
    $session_id = isset($_COOKIE['SESSION_ID']) ? $_COOKIE['SESSION_ID'] : null;

    if ($session_id && file_exists(get_session_file_path($session_id))) {
        $session_data = json_decode(file_get_contents(get_session_file_path($session_id)), true);
        if (isset($session_data['expires']) && $session_data['expires'] < time()) {
            delete_session_file($session_id);
            $session_id = null;
            $session_data = null;
        }
    }
    if (!$session_id || !file_exists(get_session_file_path($session_id))) {
        // Generate a new session ID if not present
        $session_id = generate_session_id();
        $session_data = [];
        $expires = time() + 600; // 10 minutes expiration
        $session_data['expires'] = $expires;
		set_cookie('SESSION_ID', $session_id, $expires);
    }
    return ['id' => $session_id, 'data' => $session_data];
}

function save_session($session)
{
    if (!$session)
        return;
    $session_file = get_session_file_path($session['id']);
    file_put_contents($session_file, json_encode($session['data']));
}

function delete_session_file($session_id)
{
    $session_file = get_session_file_path($session_id);
    if (file_exists($session_file)) {
        unlink($session_file);
    }
}

function destroy_session($session_id = null)
{
    if (!isset($session_id))
        $session_id = isset($_COOKIE['SESSION_ID']) ? $_COOKIE['SESSION_ID'] : null;

    if ($session_id) {
        // Delete the session file
        delete_session_file($session_id);
		set_cookie('SESSION_ID', '', 0);
    }
}
