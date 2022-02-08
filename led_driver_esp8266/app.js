const uploadButton = document.getElementById("upload-button");
const saveButton = document.getElementById("save-to-memory-button");
const loadButton = document.getElementById("load-from-memory-button");
const brightRange = document.getElementById("brightness-range");
const speedRange = document.getElementById("speed-range");
const sizeRange = document.getElementById("size-range");
const URL = "http://192.168.8.105/";

uploadButton.addEventListener("click", async function () {
    await sendMessage();
})

saveButton.addEventListener("click", async function () {
    await fetch(URL + "save-settings", {method: "GET"});
})

loadButton.addEventListener("click", async function () {
    await fetch(URL + "load-settings", {method: "GET"});
})

let isIntervalInProgress = false;
let counter = 0;
// setInterval(async () => {
//     if (isIntervalInProgress === false) {
//         // isIntervalInProgress = true;
//         await sendMessage()
//     }
// }, 1000);

async function sendMessage(){
    // counter++;
        await fetch(URL + "change-settings?" + brightnessStr() + speedStr() + sizeStr(), {method: "POST"});
}

function brightnessStr() {
    return "brightness=" + brightRange.value + "&";
}

function speedStr() {
    return "speed=" + speedRange.value + "&";
}

function sizeStr() {
    return "size=" + sizeRange.value + "&";
}
