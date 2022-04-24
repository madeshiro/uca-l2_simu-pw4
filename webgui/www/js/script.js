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

/**
 * @param event {Event}
 * @param element {HTMLElement}
 * @param class1 {string}
 * @param class2 {string}
 */
function toggleClass(event, element, class1, class2) {
    element.classList.replace(class1, class2)
    setTimeout(function() {
        element.classList.replace(class2, class1)
    }, 700);
    event.stopImmediatePropagation()
    event.preventDefault()
}

/**
 *
 * @param location {string}
 * @param exploit {function(string)}
 */
function readResource(location, exploit) {
    let ajaxFile = new XMLHttpRequest();
    ajaxFile.open('GET','/'+ location, true);
    ajaxFile.onload = function () {
        exploit(ajaxFile.responseText);
    }
    ajaxFile.send();
}

function displayPopup(msg, icon)
{
    let popup = document.getElementsByTagName("popup-window")[0];
    let popup_text = document.getElementById("popup-text");

    if (popup !== null && popup instanceof HTMLElement)
    {
        popup.style.visibility = "visible";
        popup_text.innerText = msg;

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

function registerUsingForm(formId) {
    /**
     *
     * @type {HTMLFormElement}
     */
    let formHtml = document.getElementById(formId);
    formHtml.submit();
}

function loginUsingForm(formId) {
    /**
     * @type {HTMLFormElement}
     */
    let formHtml = document.getElementById(formId);
    let username = formHtml.elements['username'].value;
    let password = formHtml.elements['userpwd'].value;

    let ajax = new XMLHttpRequest();
    ajax.open('get', `/htbin/login.py?username=${username}&userpwd=${password}`, true)
    ajax.send();
    ajax.onload = function () {
        alert(ajax.responseText);
    }
}

/**
 *
 * @param visible {boolean}
 */
function showChatbox(visible) {
    let chatboxButton = document.getElementById('chatbox-display-button');
    let chatboxHtml = document.getElementById('chatbox');

    chatboxButton.style.visibility = visible ? 'hidden' : 'visible';
    chatboxHtml.style.visibility = visible ? 'visible' : 'hidden';

    if (visible) {
        refreshChatbox();
    }
}

function refreshChatbox() {
    let refreshRqst = new XMLHttpRequest()
    refreshRqst.open('GET', '/htbin/chatget.py', true);
    refreshRqst.onload = function () {
        let responseJSON = JSON.parse(refreshRqst.responseText);
        let chatboxMsgHtml = document.getElementById('chatbox-messages');
        chatboxMsgHtml.innerHTML = ''; // clear all elements

        if (responseJSON) {
            for (let msg of responseJSON) {
                addMsgChatbox(msg.user, msg.msg, `${msg.date} ${msg.time}`);
            }
        }
    }
    refreshRqst.send();
}

/**
 *
 * @param inputElem {HTMLInputElement}
 */
function sendMsgChatbox(inputElem) {
    let msg = inputElem.value;
    if (msg !== '') {
        let ajaxRequest = new XMLHttpRequest();
        ajaxRequest.open('GET',`/htbin/chatsend.py?msg=${msg}`);
        ajaxRequest.onload = function () {
            let response = JSON.parse(ajaxRequest.responseText);
            switch (response.num) {
                case 0:
                    refreshChatbox();
                    break;
                case 1:
                    addMsgChatbox('ChatBox', 'Cannot send empty message');
                    break;
                case -1:
                    addMsgChatbox('ChatBox', 'An error occured while sending the message. Please contact an admin to report it.');
                    break;
            }
            inputElem.value = '';
        }
        ajaxRequest.send();
    }
}

/**
 *
 * @param user  {string}
 * @param msg   {string}
 * @param date  {string|null}
 */
function addMsgChatbox(user, msg, date= null) {
    if (date === null) {
        let today = new Date();
        date = `${today.getDay().toFixed(2)}/${today.getMonth().toFixed(2)}/${today.getFullYear()} `;
        date += `${today.getHours().toFixed(2)}:${today.getMinutes().toFixed(2)}`;
    }
    
    let msgsHtml = document.getElementById('chatbox-messages');
    let msgHtml  = document.createElement('div');
    msgHtml.classList.add('chatbox-message');
    let msgInfoHtml = document.createElement('div');
    msgInfoHtml.classList.add('chatbox-msginfo');
    let aUser = document.createElement('a');
    let aDate = document.createElement('a');
    let pText = document.createElement('p');
    pText.classList.add('chatbox-msgcontent');

    aUser.innerText = user;
    aDate.innerText = date;
    pText.innerText = msg;

    msgInfoHtml.appendChild(aUser);
    msgInfoHtml.appendChild(aDate);
    msgHtml.appendChild(msgInfoHtml);
    msgHtml.appendChild(pText);
    msgsHtml.appendChild(msgHtml);
    msgsHtml.scrollTo(0, msgsHtml.scrollHeight)
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

    document.getElementById('chatbox-send-text').onkeyup = function(e) {
        if (e.keyCode === 13) {
            sendMsgChatbox(document.getElementById('chatbox-send-text'));
        }
    }
}

document.onscroll = function () {
    document.documentElement.dataset.scroll = window.scrollY;
}
