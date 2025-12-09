<?php
ini_set('display_errors', 1);
error_reporting(E_ALL);
 
$servername = "127.0.0.1";
$username = "root";
$password = "";
$dbname = "datacenter";
 
$conn = new mysqli($servername, $username, $password, $dbname);
 
$id_usuario = isset($_POST['id_usuario']) ? $_POST['id_usuario'] : null;
$acao = isset($_POST['acao']) ? $_POST['acao'] : null;
 
if ($id_usuario === null || $acao === null) {
    die("Error: 'id_usuario' or 'acao' not provided");
}
 
$sql = "INSERT INTO acessos (id_usuario, acao) VALUES ('$id_usuario', '$acao')";
 
if ($conn->query($sql) === TRUE) {
    echo "OK: inserted $id_usuario = $acao";
} else {
    echo "ERROR: " . $conn->error;
}
 
$conn->close();
?>