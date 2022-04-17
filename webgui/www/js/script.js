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
function test() {
    let asideElm = document.getElementsByClassName("popup-menu").item(0);
    for (let i = 0; i < 10; i++) {
        let button = document.createElement("button");
        button.textContent = "Button #" + i;
        asideElm.appendChild(button);
    }
}

window.onload = function () {
    document.getElementById("testIt").onclick = test
}