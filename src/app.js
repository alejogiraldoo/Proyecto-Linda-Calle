// <!-- CREACIÓN DEL MAPA -->
let map = L.map("map").setView([6.2518400,-75.5635900],13);

// CREANDO MAPA 
L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {
    maxZoom: 19,
    attribution: '&copy; <a href="http://www.openstreetmap.org/copyright">OpenStreetMap</a>'
}).addTo(map);

// PROPIEDADES DEL MARCADOR (ESTILOS)
let iconEstilos = L.icon({
    iconUrl: 'img/red_marker.png',
    iconSize: [40, 40], // Tamaño del Icon
});

//___________________________________________________________________________

// CREACIÓN DE LOS MARCADORES (LECTURA DE LA BD)
// CREAMOS UN GRUPO PARA GUARDAR LOS MARKADORES
let layerGroup = L.layerGroup();

setTimeout(showLocation, 0); // CARGA EL MAPA AL INICIAR LA PAGINA
setInterval(showLocation,10000); // ACTUALIZA LA LOCALIZACIÓN CADA 5 SEGUNDOS

function showLocation(){
    $(document).ready(function (){
        $.ajax({
            url: 'PHP/catchLocation.php',
            type: 'GET',
            success: function(response){
                // Convierte la información a JSON
                let data = JSON.parse(response);
                // console.log(data);

                // ELIMINAMOS LOS MARCADORES DEL GRUPO (LIMPIAMOS EL MAPA)
                layerGroup.clearLayers();

                data.forEach(element => {
                    // CREAMOS EL MARCADOR (INDICA LA POSICIÓN EN QUE ESTOY)
                    let ubiDispositivo = L.marker([element.latitud,element.longitud],{icon: iconEstilos});
                    
                    // AGREGAMOS UNA DESCRIPCIÓN AL MARCADOR
                    let descripcion = ubiDispositivo.bindPopup(`Id: ${element.cedula}<br> Nombre: ${element.nombre}<br> Apellido: ${element.apellido}`).openPopup();
                    // AGREGAMOS LOS MARCADORES AL GRUPO
                    descripcion.addTo(layerGroup);
                });
                // AGREGAMOS LOS MARCADORES EL GRUPO DE MARCADORES AL MAPA
                layerGroup.addTo(map);
            }
        });
    });
}