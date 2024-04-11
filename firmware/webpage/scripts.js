const circle = document.getElementById("control_knob");
const slider = document.getElementById("slide-container");
let isMouseDown = false;
let prevAngle = 0;
let currentRotation = 0;
let menuOpen = false;

function menuPressed() {
  console.log("opening");
  var menuItems = document.querySelectorAll(".menu_item");
  menuItems.forEach(function (menuItem) {
    menuItem.classList.toggle("open");
  });
}

// Function to calculate angle between two points
function getAngle(center, point) {
  console.log(
    "%d, %d, %d, %d",
    point.clientY,
    center.top,
    point.clientX,
    center.left
  );
  const deltaY = point.clientY - center.top;
  const deltaX = point.clientX - center.left;
  const angle = Math.atan2(deltaY, deltaX);
  console.log("%f, %f, %f", deltaY, deltaX, angle);
  return angle;
}

// Function to rotate the circle
function rotateCircle(event) {
  event.preventDefault();
  let touch = event;
  if (event.touches) {
    touch = event.touches[0];
  }
  if (isMouseDown) {
    const rect = circle.getBoundingClientRect();
    const center = {
      left: rect.left + rect.width / 2,
      top: rect.top + rect.height / 2,
    };

    const angle = getAngle(center, touch);
    const rotation = angle - prevAngle;
    //console.log(rotation);
    currentRotation += rotation;
    circle.style.transform = `rotate(${currentRotation}rad)`;
    prevAngle = angle;
    //console.log(currentRotation);
  }
}

// Event listeners for mouse down, move, and up
circle.addEventListener(
  "mousedown",
  (event) => {
    isMouseDown = true;
    const rect = circle.getBoundingClientRect();
    const center = {
      left: rect.left + rect.width / 2,
      top: rect.top + rect.height / 2,
    };
    prevAngle = getAngle(center, event);
  },
  { passive: false }
);

slider.addEventListener(
  "mousedown",
  (event) => {
    isMouseDown = true;
    const rect = circle.getBoundingClientRect();
    const center = {
      left: rect.left + rect.width / 2,
      top: rect.top + rect.height / 2,
    };
    prevAngle = getAngle(center, event);
  },
  { passive: false }
);

document.addEventListener("mousemove", rotateCircle, { passive: false });

document.addEventListener(
  "mouseup",
  () => {
    isMouseDown = false;
  },
  { passive: false }
);

// Event listeners for touch events
circle.addEventListener(
  "touchstart",
  (event) => {
    isMouseDown = true;
    const touch = event.touches[0];
    const rect = circle.getBoundingClientRect();
    const center = {
      left: rect.left + rect.width / 2,
      top: rect.top + rect.height / 2,
    };
    prevAngle = getAngle(center, touch);
  },
  { passive: false }
);

slider.addEventListener(
  "touchstart",
  (event) => {
    isMouseDown = true;
    const touch = event.touches[0];
    const rect = circle.getBoundingClientRect();
    const center = {
      left: rect.left + rect.width / 2,
      top: rect.top + rect.height / 2,
    };
    prevAngle = getAngle(center, touch);
  },
  { passive: false }
);

document.addEventListener("touchmove", rotateCircle, { passive: false });

document.addEventListener(
  "touchend",
  () => {
    isMouseDown = false;
  },
  { passive: false }
);

document.getElementById('menu-toggle')
.addEventListener('click', function(){
   document.getElementById("menu-toggle").classList.toggle('nav-open');
});