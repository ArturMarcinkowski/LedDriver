const uploadButton = document.getElementById("upload-button");
const saveButton = document.getElementById("save-to-memory-button");
const loadButton = document.getElementById("load-from-memory-button");
const brightRange = document.getElementById("brightness-range");
const speedRange = document.getElementById("speed-range");
const sizeRange = document.getElementById("size-range");
const URL = "http://192.168.8.105/";

let brightness = brightRange.value;
let speed = speedRange.value;
let size = sizeRange.value;

uploadButton.addEventListener("click", async function () {
    await fetch(URL + "change-settings?" + brightnessStr() + speedStr() + sizeStr(), {method: "POST"});
})
saveButton.addEventListener("click", async function () {
    await fetch(URL + "save-settings", {method: "GET"});
})
loadButton.addEventListener("click", async function () {
    await fetch(URL + "load-settings", {method: "GET"});
})

// brightRange.addEventListener("change", async function () {
//     await fetch(URL + "change-settings?" + brightnessStr(), {method: "POST"});
// })
// speedRange.addEventListener("change", async function () {
//     await fetch(URL + "change-settings?" + speedStr(), {method: "POST"});
// })
// sizeRange.addEventListener("change", async function () {
//     await fetch(URL + "change-settings?" + sizeStr(), {method: "POST"});
// })

function brightnessStr() {
    return "brightness=" + brightRange.value + "&";
}
function speedStr() {
    return "speed=" + speedRange.value + "&";
}
function sizeStr() {
    return "size=" + sizeRange.value + "&";
}

let isIntervalInProgress = false;
let counter = 0;
// setInterval(async () => {
// //     if (isIntervalInProgress === false) {
// //         // isIntervalInProgress = true;
// //         await fetch(URL + "change-settings?" + brightnessStr() + speedStr() + sizeStr(), {method: "POST"});
// //     }
// // }, 100);

setInterval(async () => {
    let str = "";
    if(brightness !== brightRange.value){
        brightness = brightRange.value;
        str += brightnessStr();
    }
    if(speed !== speedRange.value){
        speed = speedRange.value;
        str += speedStr();
    }
    if(size !== sizeRange.value){
        size = sizeRange.value;
        str += sizeStr();
    }
    if(str !== "") {
        await fetch(URL + "change-settings?" + str, {method: "POST"});
    }
}, 150);
