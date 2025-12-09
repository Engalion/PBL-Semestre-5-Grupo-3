<?php
ini_set('display_errors', 1);
error_reporting(E_ALL);
 
$servername = "127.0.0.1";
$username = "root";           // ou outro usuário
$password = "";               // senha do root se tiver
$dbname = "datacenter";
 
// Connect to MySQL
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
 
// Get POST values safely
$tipo = isset($_POST['tipo']) ? $_POST['tipo'] : null;
$valor = isset($_POST['valor']) ? floatval($_POST['valor']) : null;
 
if ($tipo === null || $valor === null) {
    die("Error: 'tipo' or 'valor' not provided");
}
 
// Insert into database
$sql = "INSERT INTO sensores (tipo, valor) VALUES ('$tipo', $valor)";
 
if ($conn->query($sql) === TRUE) {
    echo "OK: inserted $tipo = $valor";
} else {
    echo "ERROR: " . $conn->error;
}
 
$conn->close();
?>