var x = setInterval(function () { loadData("data.txt", updateData)}, 500); // i want faster updates 

function loadData(url, callback) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            callback.apply(xhttp);
        }
    };
    xhttp.open("GET", url, true);
    xhttp.send();
}

function updateData() {
    document.getElementById("SensorValue").innerHTML = this.responseText;


    // DISPLAYS LED STATE, IF ITS ON OR OFF DEPENDING ON THE SENSOR VALUE
    if (parseFloat(this.responseText) >= 512) {
        document.getElementById("LEDSTATE").innerHTML = "ON";
        
    } else if (parseFloat(this.responseText) < 512) {
        document.getElementById("LEDSTATE").innerHTML = "OFF";
    }
}
