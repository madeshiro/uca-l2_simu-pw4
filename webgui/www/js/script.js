
function test() {
    let asideElm = document.getElementsByClassName("popup-menu").item(0);
    for (let i = 0; i < 10; i++) {
        let button = document.createElement("button");
        button.textContent = "Button #" + i;
        asideElm.appendChild(button);
    }
}

window.onload = function () {
    document.getElementById("testIt").onclick = test
}