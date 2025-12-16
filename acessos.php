<?php
ini_set('display_errors', 1);
error_reporting(E_ALL);
 
$servername = "127.0.0.1";
$username = "root";
$password = "";
$dbname = "datacenter";
 
// Dados de conexão ao MySQL (Ligação XAMPP)
$conn = new mysqli($servername, $username, $password, $dbname);

// Lê os valores enviados pelo POST
$id_usuario = isset($_POST['id_usuario']) ? $_POST['id_usuario'] : null;
$acao = isset($_POST['acao']) ? $_POST['acao'] : null;

// Se faltar algum parâmetro, o script termina aqui
if ($id_usuario === null || $acao === null) {
    die("Error: 'id_usuario' or 'acao' not provided");
}

// Comando SQL que insere o acesso na tabela da bse de dados
$sql = "INSERT INTO acessos (id_usuario, acao) VALUES ('$id_usuario', '$acao')";

// Executa o INSERT e confirma se deu certo
if ($conn->query($sql) === TRUE) {
    echo "OK: inserted $id_usuario = $acao";
} else {
    echo "ERROR: " . $conn->error;
}

// Fecha a conexão com o MySQL
$conn->close();
?>
