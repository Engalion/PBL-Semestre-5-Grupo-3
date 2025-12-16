<?php
ini_set('display_errors', 1);
error_reporting(E_ALL);
 
$servername = "127.0.0.1";
$username = "root";
$password = "";     
$dbname = "datacenter";
 
// Cria a conexão MySQL e verifica se falhou
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
 
// Lê os dados enviados via POST
$tipo = isset($_POST['tipo']) ? $_POST['tipo'] : null;
$valor = isset($_POST['valor']) ? floatval($_POST['valor']) : null;
 
// Se algum campo obrigatório não for inserido vai acabar o script
if ($tipo === null || $valor === null) {
    die("Error: 'tipo' or 'valor' not provided");
}
 
// Comando SQL que grava os dados do sensor na base de dados
$sql = "INSERT INTO sensores (tipo, valor) VALUES ('$tipo', $valor)";

// Executa o INSERT e confirma sucesso ou erro
if ($conn->query($sql) === TRUE) {
    echo "OK: inserted $tipo = $valor";
} else {
    echo "ERROR: " . $conn->error;
}

// Fecha a conexão ao MySQL
$conn->close();
?>
