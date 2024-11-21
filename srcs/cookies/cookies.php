<?php

$timezone_offset = 3600;

function parse_cookie($cookie_header = null)
{
	if (!isset($cookie_header))
		$cookie_header = $_SERVER['HTTP_COOKIE'];
	$cookies = [];
	foreach (explode(';', $cookie_header) as $cookie) {
		list($name, $value) = explode('=', trim($cookie), 2) + [NULL, NULL];
		if ($name) {
			$cookies[$name] = $value;
		}
	}
	return $cookies;
}

function set_cookie($cookie_name, $cookie_value, $expires, $path = '/', $domain = '', $secure = false, $httponly = true)
{
	global $timezone_offset;

	$cookie_header = "Set-Cookie: $cookie_name=$cookie_value; expires=" . gmdate('D, d-M-Y H:i:s T', $expires + $timezone_offset) . "; path=$path";
	
	// Optionally add domain, secure, and httponly flags
	if ($domain) {
		$cookie_header .= "; domain=$domain";
	}
	if ($secure) {
		$cookie_header .= "; secure";
	}
	if ($httponly) {
		$cookie_header .= "; HttpOnly";
	}
	echo $cookie_header . PHP_EOL;
}
