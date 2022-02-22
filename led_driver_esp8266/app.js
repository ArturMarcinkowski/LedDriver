const uploadButton = document.getElementById("upload-button");
const saveButton = document.getElementById("save-to-memory-button");
const loadButton = document.getElementById("load-from-memory-button");
const modeButton = document.getElementById("change-mode-button");
const rgbResetButton = document.getElementById("RGB-reset-button");
const rgbUploadButton = document.getElementById("RGB-upload-button");

const brightRange = document.getElementById("brightness-range");
const speedRange = document.getElementById("speed-range");
const sizeRange = document.getElementById("size-range");

const redRange = document.getElementById("R-range");
const greenRange = document.getElementById("G-range");
const blueRange = document.getElementById("B-range");

const URL = "http://192.168.8.105/";

let brightness = brightRange.value;
let speed = speedRange.value;
let size = sizeRange.value;

let red = redRange.value;
let green = greenRange.value;
let blue = blueRange.value;

uploadButton.addEventListener("click", async function () {
    await fetch(URL + "change-settings?" + brightnessStr() + speedStr() + sizeStr(), {method: "POST"});
})
saveButton.addEventListener("click", async function () {
    await fetch(URL + "save-settings", {method: "GET"});
})
loadButton.addEventListener("click", async function () {
    await fetch(URL + "load-settings", {method: "GET"});
})
modeButton.addEventListener("click", async function () {
    await fetch(URL + "change-mode?mode=next", {method: "POST"});
})
rgbResetButton.addEventListener("click", async function () {
    redRange.value = 100;
    greenRange.value = 100;
    blueRange.value = 100;
})
rgbUploadButton.addEventListener("click", async function () {
    await fetch(URL + "change-rgb-balance?" + redStr() + greenStr() + blueStr(), {method: "POST"});
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
function redStr() {
    return "R=" + redRange.value + "&";
}
function greenStr() {
    return "G=" + greenRange.value + "&";
}
function blueStr() {
    return "B=" + blueRange.value + "&";
}

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
    if(red !== redRange.value || green !== greenRange.value || blue !== blueRange.value){
        red = redRange.value;
        green = greenRange.value;
        blue = blueRange.value;
        await fetch(URL + "change-rgb-balance?" + redStr() + greenStr() + blueStr(), {method: "POST"});
    }
}, 150);
