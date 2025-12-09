<?php
$host = 'localhost';
$user = 'root';
$pass = ''; 
$db   = 'datacenter';

$conn = new mysqli($host, $user, $pass, $db);

if ($conn->connect_error) {
    die("Erro na ligação à BD: " . $conn->connect_error);
}

// opcional: definir charset
$conn->set_charset("utf8");
?>
