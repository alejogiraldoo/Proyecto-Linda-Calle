CREATE DATABASE coordgeo;
USE coordgeo;

CREATE TABLE usuario(
	cedula VARCHAR(10) NOT NULL,
    nombre VARCHAR(30) NOT NULL,
    apellido VARCHAR(30) NOT NULL,
    PRIMARY KEY(cedula)
);

CREATE TABLE locacion(
	cedula VARCHAR(10) NOT NULL,
	latitud VARCHAR(20) NOT NULL,
	longitud VARCHAR(20) NOT NULL,
    fecha TIMESTAMP NOT NULL,
    FOREIGN KEY(cedula) references usuario(cedula)
);