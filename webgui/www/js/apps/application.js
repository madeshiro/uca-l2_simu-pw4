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

/**
 * @file application.js
 * @author Rin Baudelet
 * @version 0.1 alpha
 */

class PacketType {
    static PING = new PacketType("ping", 0x0);
    static STATUS = new PacketType("status", 0x1);

    constructor(name, id) {
        this.name = name;
        this.id = id;
    }

    generate
}

class Packet {

    /**
     *
     * @param {PacketType} type
     * @param {Object} shipment
     */
    constructor(type, shipment) {
        this.header = {
            "type": type.name,
            "size": shipment.stringify()
        }
    }
}

class CppApplication {
    static portRange = [9000, 10000];

    /**
     *
     * @param {string} ip
     * @param {number} port
     */
    constructor(ip, port) {
        this.server_ip = ip;

        if (port < CppApplication.portRange[0] || port > CppApplication.portRange[1])
        {
            throw new Error("Invalid port ! must be in range" +
            `${CppApplication.portRange[0]} -> ${CppApplication.portRange[1]}`);
        }

        this.server_port = port;
    }

    get port() {
        return this.server_port;
    }

    /**
     *
     * @returns {boolean}
     */
    ping() {
        return false;
    }
}
