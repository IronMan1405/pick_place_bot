let socket = null;
let emergency = false;

const handle = document.getElementById('dial-handle');
handle.setAttribute('transform', "rotate(-90, 60, 60)");


function initWebSocket() {
    if (!location.hostname) {
    console.log('Local mode: WebSocket disabled');
    return;
    }

    socket = new WebSocket(`ws://${location.hostname}:81`);

    socket.onopen = () => console.log('WebSocket Connected.');
    socket.onclose = () => console.log('WebSocket disconnected.');
}

initWebSocket();

function wsSend(msg) {
    if (socket && socket.readyState === 1) {
    socket.send(msg);
    } else {
    console.log('WS > ', msg);
}
}

function sendServo(id, angle) {
    wsSend(`S,${id},${angle}`);
}

function toggleEStop() {
    emergency = !emergency;
    wsSend(`E,${emergency ? 1 : 0}`);
    document.getElementById('estop').style.background = emergency
    ? 'darkred'
    : 'red';
}

const joystick = document.getElementById('joystick');
const stick = document.getElementById('stick');

const joystickStyle = window.getComputedStyle(joystick);
const stickStyle = window.getComputedStyle(stick);

const joystickRadius = parseInt(joystickStyle.width) / 2;
const stickRadius = parseInt(stickStyle.width) / 2;


let dragging = false;
const center = joystickRadius;
const maxDist = joystickRadius - stickRadius;

const dial = document.getElementById('circular-dial');
const valueDisplay = document.getElementById('dial-value');
let draggingDial = false;
const centerX = 60;
const centerY = 60;



function handleMove(clientX, clientY) {
    const rect = joystick.getBoundingClientRect();
    let x = clientX - rect.left - center;
    let y = clientY - rect.top - center;

    const dist = Math.hypot(x, y);
    if (dist > maxDist) {
    x *= maxDist / dist;
    y *= maxDist / dist;
    }

    stick.style.left = `${center + x - stickRadius}px`;
    stick.style.top = `${center + y - stickRadius}px`;

    const normX = (x / maxDist).toFixed(2);
    const normY = (-y / maxDist).toFixed(2);
    //console.log(normX, normY) ;

    wsSend(`D,${normX},${normY}`);
}





function updateDial(clientX, clientY) {
    // Calculate angle based on mouse position
    const rect = dial.getBoundingClientRect();
    const mouseX = clientX - rect.left - centerX * (rect.width / 120);
    const mouseY = clientY - rect.top - centerY * (rect.height / 120);
    let angle = Math.atan2(mouseY, mouseX) * (180 / Math.PI) ;
    angle = parseInt(angle);
    if(angle >=90 && angle <= 180){angle = -180}
    if(angle < 90 && angle > 0){angle = 0}

    

    handle.setAttribute('transform', `rotate(${angle}, ${centerX}, ${centerY})`);
    
    
    toSend = -1 * parseInt(angle);
    valueDisplay.textContent = toSend ;
    sendServo(3, toSend) ;
}






dial.addEventListener('mousedown', function (e) {
    draggingDial = true;
    updateDial(e.clientX, e.clientY);
});

joystick.addEventListener('mousedown', (e) => {
    dragging = true;
    handleMove(e.clientX, e.clientY);
});

window.addEventListener('mousemove', (e) => {
    if (dragging) handleMove(e.clientX, e.clientY);
    if (draggingDial) updateDial(e.clientX, e.clientY);
});

window.addEventListener('mouseup', () => {
    dragging = false;
    draggingDial = false;
    stick.style.left = '70px';
    stick.style.top = '70px';
    wsSend('D,0,0');
});

joystick.addEventListener("touchstart", e => {
    dragging = true;
    draggingDial = true ;
    handleMove(e.touches[0].clientX, e.touches[0].clientY);
});

joystick.addEventListener("touchmove", e => {
    if (dragging) handleMove(e.touches[0].clientX, e.touches[0].clientY);
    if (draggingDial) updateDial(e.clientX, e.clientY);
});

joystick.addEventListener("touchend", () => {
    dragging = false;
    draggingDial = false;
    stick.style.left = "70px";
    stick.style.top = "70px";
    wsSend("D,0,0");
});
