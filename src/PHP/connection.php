<?php
    // <!-- Conexión con Base de datos -->
    $con = new mysqli("localhost","root","alejo123","CoordGeo",3306);
    // Imprime información de la conexion
    // echo $con->host_info;
    if($con->connect_errno){
        die("No se pudo conectar con la base de datos". $con->connect_errno);
    }
?>