/*
 * UCA-L2 simulation "practical work #4" : a realistic simulation of rabbit population growth
 * Copyright (C) 2022 -- Rin Baudelet
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
function detectColorScheme() {
    let theme = "light";

    if(localStorage.getItem("theme")) {
        if(localStorage.getItem("theme") === "dark") {
            theme = "dark";
        }
    } else if(!window.matchMedia) {
        return false;
    } else if(window.matchMedia("(prefers-color-scheme: dark)").matches) {
        theme = "dark";
    }

    if(theme === "dark") {
        document.documentElement.setAttribute("data-theme", "dark");
        document.getElementById("input-light-button").checked = true;
    }
}

/**
 *
 * @param {HTMLInputElement} checkbox
 */
function toggleDarkMode(checkbox) {
    if (checkbox.checked) {
        localStorage.setItem("theme", "dark");
        document.documentElement.setAttribute("data-theme", "dark");
    } else {
        localStorage.setItem("theme", "light");
        document.documentElement.setAttribute("data-theme", "light");
    }
}

/***
 *
 * @returns {null|number}
 */
function detectCppApplication() {
    let portRange = CppApplication.portRange;
    let app = new CppApplication('localhost', portRange[0]);

    for (let port=portRange[0]; port < portRange[1]; port++)
    {
        app.port = port;
        if (app.ping()) {
            return port;
        }
    }

    return null;
}

function displayPopup(msg, icon)
{
    let popup = document.getElementsByTagName("popup-window")[0];

    if (popup !== null && popup instanceof HTMLElement)
    {
        popup.style.visibility = "visible";

        setTimeout(hidePopup, 5000, true);
    }
}

/**
 *
 * @param {HTMLInputElement|boolean} obj
 */
function hidePopup(obj) {
    /**
     * @type {HTMLInputElement}
     */
    let closeButton;
    /**
     * @type {HTMLElement}
     */
    let popup = document.getElementsByTagName("popup-window")[0];

    if (obj instanceof HTMLInputElement) {
        closeButton = obj;
    }
    else {
        closeButton = document.getElementById("popup-close-button").getElementsByTagName("input");
        closeButton.checked = obj;
    }

    if (closeButton.checked) {
        popup.style.visibility = "hidden";
    } else {
        popup.style.visibility = "visible";
    }
}

window.onload = function () {
    detectColorScheme();
    document.documentElement.dataset.scroll = window.scrollY;

    let port = detectCppApplication();
    if (port !== null) {
        document.getElementById("cpp-apps-button")
            .children[0].children[0]
            .style.filter = "brightness(100%)";

        document.getElementById("cpp-apps-button")
            .children[0].href += `?port=${port}`;
    }
}

document.onscroll = function () {
    document.documentElement.dataset.scroll = window.scrollY;
}

function al() {
    let a = {"a":"b", "c": {
            "d": [10,11,12],
            "e": false
        }
    };
    alert(JSON.stringify(a));
}