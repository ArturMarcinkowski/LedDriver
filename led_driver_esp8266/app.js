const myButton = document.getElementById("my-test-button");
const brightRange = document.getElementById("brightness-range");
const speedRange = document.getElementById("speed-range");
const sizeRange = document.getElementById("size-range");

myButton.addEventListener("click", async function () {
    myButton.style.height = 100 + "px";
    await fetch("http://192.168.8.116/LED?brightness=" + 
    brightRange.value + "&mode=addOne");
})

let isIntervalInProgress = false;
setInterval(async () => {
    if (isIntervalInProgress === false) {
        // isIntervalInProgress = true;
        await fetch("http://192.168.8.116/LED?brightness=" + 
        brightRange.value + "&speed=" + speedRange.value + "&size=" + sizeRange.value);
        isIntervalInProgress = false;
    }
}, 1000);