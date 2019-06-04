<?php
if(!function_exists('b1gzip_create')) die("b1gZip ist nicht installiert");

// Archiv erstellen
$res = b1gzip_create();
b1gzip_add($res, "Dies ist ein Test!", "test.txt");
b1gzip_add($res, "Dies ist noch ein Test!", "demo/demo.txt");
$zip = b1gzip_final($res);

// Archiv zum Download ausgeben
header('Content-Type: application/zip');
header('Content-Disposition: attachment; filename="test.zip"');
header('Content-Length: ' . strlen($zip));
print $zip;