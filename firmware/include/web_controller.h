#ifndef WEBCONTROLLER_H
#define WEBCONTROLLER_H

const char *web_html = "<!DOCTYPE html>\n"
"<html lang=\"en\">\n"
"  <head>\n"
"    <meta charset=\"UTF-8\" />\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\" />\n"
"    <title>WeldConnect</title>\n"
"    <style>\n"
"      body,\n"
"      html {\n"
"        height: 100%;\n"
"        margin: 0;\n"
"        display: flex;\n"
"        justify-content: center;\n"
"        align-items: center;\n"
"        background-color: #003647;\n"
"      }\n"
"\n"
"      .dominant_color {\n"
"        background-color: #003647;\n"
"      }\n"
"      .secondary_color {\n"
"        background-color: #6aaec3;\n"
"      }\n"
"      .accent_color {\n"
"        background-color: #c5d4d9;\n"
"      }\n"
"      #hash_container {\n"
"        width: 230px;\n"
"        height: 230px;\n"
"        background-color: #101010;\n"
"        border-radius: 50%;\n"
"        padding: 15px;\n"
"      }\n"
"      .hash {\n"
"        width: 10px;\n"
"        background-color: black;\n"
"        position: relative;\n"
"      }\n"
"      #control_knob {\n"
"        width: 200px;\n"
"        height: 200px;\n"
"        border-radius: 50%;\n"
"        display: flex;\n"
"        justify-content: center;\n"
"        align-items: center;\n"
"        color: white;\n"
"        font-size: 24px;\n"
"        position: relative;\n"
"        cursor: pointer;\n"
"      }\n"
"      #line {\n"
"        width: 10%;\n"
"        height: 30%;\n"
"        position: absolute;\n"
"        top: 0;\n"
"        border-radius: 10px;\n"
"        left: 45%;\n"
"      }\n"
"      #inner_circle {\n"
"        width: 180px;\n"
"        height: 180px;\n"
"        background-color: #565565;\n"
"        border-radius: 50%;\n"
"      }\n"
"    </style>\n"
"  </head>\n"
"  <body>\n"
"\n"
"    <div id=\"control_knob\" class=\"accent_color\">\n"
"      <div id=\"line\" class=\"accent_color\"></div>\n"
"      <div id=\"inner_circle\"></div>\n"
"    </div>\n"
"\n"
"    <script>\n"
"      const circle = document.getElementById(\"control_knob\");\n"
"      const line = document.getElementById(\"line\");\n"
"      let isMouseDown = false;\n"
"      let prevAngle = 0;\n"
"      let currentRotation = 0;\n"
"\n"
"      // Function to calculate angle between two points\n"
"      function getAngle(center, point) {\n"
"        const deltaY = point.clientY - center.clientY;\n"
"        const deltaX = point.clientX - center.clientX;\n"
"        const angle = Math.atan2(deltaY, deltaX);\n"
"        return angle;\n"
"      }\n"
"\n"
"      // Function to rotate the circle\n"
"      function rotateCircle(event) {\n"
"        event.preventDefault();\n"
"        let touch = event;\n"
"        if (event.touches) {\n"
"          touch = event.touches[0];\n"
"        }\n"
"        if (isMouseDown) {\n"
"          const center = {\n"
"            clientX: circle.offsetLeft + circle.offsetWidth / 2,\n"
"            clientY: circle.offsetTop + circle.offsetHeight / 2,\n"
"          };\n"
"          const angle = getAngle(center, touch);\n"
"          const rotation = angle - prevAngle;\n"
"          currentRotation += rotation;\n"
"          circle.style.transform = `rotate(${currentRotation}rad)`;\n"
"          prevAngle = angle;\n"
"        }\n"
"      }\n"
"\n"
"      // Event listeners for mouse down, move, and up\n"
"      circle.addEventListener(\"mousedown\", (event) => {\n"
"        isMouseDown = true;\n"
"        const center = {\n"
"          clientX: circle.offsetLeft + circle.offsetWidth / 2,\n"
"          clientY: circle.offsetTop + circle.offsetHeight / 2,\n"
"        };\n"
"        prevAngle = getAngle(center, event);\n"
"      });\n"
"\n"
"      document.addEventListener(\"mousemove\", rotateCircle);\n"
"\n"
"      document.addEventListener(\"mouseup\", () => {\n"
"        isMouseDown = false;\n"
"      });\n"
"\n"
"      // Event listeners for touch events\n"
"      circle.addEventListener(\"touchstart\", (event) => {\n"
"        isMouseDown = true;\n"
"        const touch = event.touches[0];\n"
"        const center = {\n"
"          clientX: circle.offsetLeft + circle.offsetWidth / 2,\n"
"          clientY: circle.offsetTop + circle.offsetHeight / 2,\n"
"        };\n"
"        prevAngle = getAngle(center, touch);\n"
"      });\n"
"\n"
"      document.addEventListener(\"touchmove\", rotateCircle);\n"
"\n"
"      document.addEventListener(\"touchend\", () => {\n"
"        isMouseDown = false;\n"
"      });\n"
"    </script>\n"
"  </body>\n"
"</html>\n"
"\n"
""
                      "";

#endif