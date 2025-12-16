<?php
$host = 'localhost';
$user = 'root';
$pass = ''; 
$db   = 'datacenter';

// Cria a conexão com o servidor MySQL
$conn = new mysqli($host, $user, $pass, $db);

// Verifica se ocorreu erro ao conectar
if ($conn->connect_error) {
    die("Erro na ligação à BD: " . $conn->connect_error);
}

// Define o charset da conexão (evita problemas com acentos)
$conn->set_charset("utf8");
?>
