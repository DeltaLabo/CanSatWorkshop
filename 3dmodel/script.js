let scene, camera, renderer, model;
let loader = new THREE.OBJLoader();

function parentWidth(elem) {
    return elem.parentElement.clientWidth;
}

function parentHeight(elem) {
    return elem.parentElement.clientHeight;
}

function init3D(){
    scene = new THREE.Scene();
    scene.background = new THREE.Color(0xffffff);

    camera = new THREE.PerspectiveCamera(75, parentWidth(document.getElementById("3Dmodel")) / parentHeight(document.getElementById("3Dmodel")), 0.1, 1000);

    renderer = new THREE.WebGLRenderer({ antialias: true });
    renderer.setSize(parentWidth(document.getElementById("3Dmodel")), parentHeight(document.getElementById("3Dmodel")));

    document.getElementById('3Dmodel').appendChild(renderer.domElement);

    // Load the .obj model
    loader.load(
        '3dmodel.obj',
        function (obj) {
            model = obj;
            scene.add(model);
            model.position.set(0, 0, 0); // Position the model
            render();
        },
        undefined,
        function (error) {
            console.error('An error happened:', error);
        }
    );

    camera.position.z = 5;
    render();
}

// Resize the 3D object when the browser window changes size
function onWindowResize(){
    camera.aspect = parentWidth(document.getElementById("3Dmodel")) / parentHeight(document.getElementById("3Dmodel"));
    camera.updateProjectionMatrix();
    renderer.setSize(parentWidth(document.getElementById("3Dmodel")), parentHeight(document.getElementById("3Dmodel")));
}

window.addEventListener('resize', onWindowResize, false);

function render() {
    renderer.render(scene, camera);
}

// Create the 3D representation
init3D();

// Create events for the sensor readings
if (!!window.EventSource) {
    var source = new EventSource('/events');

    source.addEventListener('open', function(e) {
        console.log("Events Connected");
    }, false);

    source.addEventListener('error', function(e) {
        if (e.target.readyState != EventSource.OPEN) {
            console.log("Events Disconnected");
        }
    }, false);

    source.addEventListener('gyro_readings', function(e) {
        var obj = JSON.parse(e.data);
        document.getElementById("gyroX").innerHTML = obj.gyroX;
        document.getElementById("gyroY").innerHTML = obj.gyroY;
        document.getElementById("gyroZ").innerHTML = obj.gyroZ;

        // Update model rotation based on gyro readings
        if (model) {
            model.rotation.x = obj.gyroY;
            model.rotation.z = obj.gyroX;
            model.rotation.y = obj.gyroZ;
        }
        render();
    }, false);

    source.addEventListener('accelerometer_readings', function(e) {
        var obj = JSON.parse(e.data);
        document.getElementById("accX").innerHTML = obj.accX;
        document.getElementById("accY").innerHTML = obj.accY;
        document.getElementById("accZ").innerHTML = obj.accZ;
    }, false);

    // Handle speed readings
    source.addEventListener('speed_reading', function(e) {
        var obj = JSON.parse(e.data);
        document.getElementById("speed").innerHTML = obj.speed;

        // Optional: Update model position or other properties based on speed
        // Example: Move model along the z-axis based on speed
        if (model) {
            model.position.z += obj.speed * 0.01; // Adjust scaling factor as needed
        }
        render();
    }, false);
}

function resetPosition(element){
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "/"+element.id, true);
    xhr.send();
}