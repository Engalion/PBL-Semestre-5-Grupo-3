<?php
ini_set('display_errors', 1);
error_reporting(E_ALL);

$servername = "127.0.0.1";
$username = "root";
$password = "";
$dbname = "datacenter";

// Cria a ligação à base de dados MySQL
$conn = new mysqli($servername, $username, $password, $dbname);

// Lê o ID do utilizador enviado pelo Arduino e o estado de acesso entrada, saída ou não autorizado
$id_usuario = isset($_POST['id_usuario']) ? $_POST['id_usuario'] : null;
$estado = isset($_POST['estado']) ? $_POST['estado'] : null;

// Se algum dos parâmetros obrigatórios não foi enviado, o script termina e envia um erro
if ($id_usuario === null || $estado === null) {
    die("Error: 'id_usuario' or 'estado' not provided");
}

// Comando SQL que insere um novo registo na tabela 'acessos'
$sql = "INSERT INTO acessos (id_usuario, estado) VALUES ('$id_usuario', '$estado')";

// Executa o INSERT e confirma sucesso ou erro
if ($conn->query($sql) === TRUE) {
    echo "OK: inserted $id_usuario = $estado";
} else {
    echo "ERROR: " . $conn->error;
}

// Fecha a conexão ao MySQL
$conn->close();
?> 
