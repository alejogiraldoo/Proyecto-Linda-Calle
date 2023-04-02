<?php
    require "connection.php";
        if (isset($_POST["userId"]) and isset($_POST["latitud"]) and isset($_POST["longitud"])) {
            // RECUPERA LA INFORMACIÓN ENVIADA POR EL ESP8266
            $latitud = $_POST["latitud"];
            $longitud = $_POST["longitud"];
            $userId = $_POST["userId"];

            date_default_timezone_set('America/Bogota');
 
            $fecha_actual = date("Y-m-d H:i:s");

            // HACEMOS UN CHECK PARA VISUALIZAR SI YA SE HA ENVIADO LA LOCALIZACIÓN DEL USUARIO ANTERIORMENTE
            $consulta = "SELECT * FROM locacion WHERE cedula = '$userId'";
            $resultado = $con->query($consulta)->fetch_all(); // GUARDAMOS LOS REGISTROS COMO UN ARRAY
            // VERIFICA SI HAY UN USUARIO YA REGISTRADO PARA INSERTARLO
            if(empty($resultado)){
                // INSERTA LA NUEVA LOCALIZACIÓN Y EL USUARIO
                $consulta = "INSERT INTO locacion(cedula,latitud,longitud,fecha)  VALUES('$userId','$latitud','$longitud','$fecha_actual')";
            }else{
                // NOTA: SI EL USUARIO YA HABÍA ENVIADO SU LOCALIZACIÓN LA ACTUALIZA
                // ACTUALIZA LA LOCALIZACIÓN DEL USUARIO
                $consulta = "UPDATE locacion SET latitud = '$latitud', longitud = '$longitud', fecha = '$fecha_actual' WHERE cedula = $userId";
            }

            // RESPUESTA DE LA BASE DE DATOS
            if ($con->query($consulta)) {
                // RESPUESTA DEL SERVIDOR
                echo "Los datos se han guardado con EXITO :D...";
            }else{
                echo "Los datos no se han guardado :(...";
            }
        }
?>