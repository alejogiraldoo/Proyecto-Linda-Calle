<?php
    require "connection.php";

    $consulta = "SELECT L.*,U.nombre,U.apellido FROM locacion AS L INNER JOIN usuario AS U ON L.cedula = U.cedula";
    $resultado = $con->query($consulta);

    if(!$resultado){
        die('Query Error'.mysqli_error($con));
    }
    // GUARDA EL RESULTADO EN FORMATO JSON
    $json = array();
    while($fila = $resultado->fetch_array()){
        $json[] = array(
            'cedula' => $fila['cedula'],
            'latitud' => $fila['latitud'],
            'longitud' => $fila['longitud'],
            'fecha' => $fila['fecha'],
            'nombre' => $fila['nombre'],
            'apellido' => $fila['apellido']
        );
    }
    // CONVIERTE EL FORMATO JSON A STRING
    // NOTA: SE REALIZA ESTE CAMBIO PARA PODER ENVIARLO COMO RESPUESTA
    $jsonString = json_encode($json);
    //Respuesta -> STRING
    echo $jsonString;
?>