CREATE DATABASE IF NOT EXISTS datacenter;
USE datacenter;

CREATE TABLE IF NOT EXISTS sensores (
    id INT AUTO_INCREMENT PRIMARY KEY,
    tipo ENUM('movimento','temperatura','humidade') NOT NULL,
    valor FLOAT DEFAULT NULL,
    data_hora DATETIME DEFAULT CURRENT_TIMESTAMP
);


CREATE TABLE IF NOT EXISTS acessos (
    id INT AUTO_INCREMENT PRIMARY KEY,
    id_usuario VARCHAR(50),
    estado ENUM('entrada','saida','nao_autorizado') NOT NULL,
    data_hora DATETIME DEFAULT CURRENT_TIMESTAMP
);