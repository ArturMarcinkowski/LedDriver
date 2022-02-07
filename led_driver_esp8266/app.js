const myButton = document.getElementById("my-test-button");
const brightRange = document.getElementById("brightness-range");
const speedRange = document.getElementById("speed-range");
const sizeRange = document.getElementById("size-range");
const URL = "http://192.168.8.116/";

myButton.addEventListener("click", async function () {
    myButton.style.height = 100 + "px";
    // await fetch("http://192.168.8.116/LED?brightness=" +
    // brightRange.value + "&mode=nextMode");
    await sendMessage();
})

let isIntervalInProgress = false;
let counter = 0;
setInterval(async () => {
    if (isIntervalInProgress === false) {
        // isIntervalInProgress = true;
        await sendMessage()
    }
}, 1000);

async function sendMessage(){
    counter++;
    if(counter % 3 === 0)
        await fetch(URL + "LED?brightness=" + brightRange.value, {method: "POST"});
    else if(counter % 3 === 1)
        await fetch(URL + "LED?speed=" + speedRange.value, {method: "POST"});
    else if(counter % 3 === 2)
        await fetch(URL + "LED?size=" + sizeRange.value, {method: "POST"});
    isIntervalInProgress = false;
}
