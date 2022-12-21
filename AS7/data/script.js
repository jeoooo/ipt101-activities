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
    document.getElementById("data").innerHTML = this.responseText;
}
