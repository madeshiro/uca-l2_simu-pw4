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
 *
 * @param color {String}
 */
function toggleColorPicker(color) {
    if (color===null)
    {
        localStorage.removeItem("color-picker");
        document.documentElement.removeAttribute("color-picker");
    }
    else
    {
        localStorage.setItem("color-picker", color);
        document.documentElement.setAttribute("color-picker", color);
    }
}

class Chart {
    /**
     *
     * @param {Object} jsonObject
     */
    constructor(jsonObject) {
        /**
         * @type {Object}
         */
        this.meta = jsonObject.chart;
        /**
         * @type {Array}
         */
        this.data = jsonObject.data;
        this.isdraw = false;
        this.htmlBody = document.createElement("chart-body");
        this.htmlChartData = document.createElement("chart-data");
        this.htmlBody.appendChild(this.htmlChartData);

        if (this.xLabel != null) {
            let xLabel = document.createElement("a");
            let xText = document.createTextNode(this.xLabel);
            xLabel.classList.add("axis-x-label");
            xLabel.appendChild(xText);
            this.htmlBody.appendChild(xLabel);
        }

        // y label must always exist !
        let yLabel = document.createElement("a");
        let yText  = document.createTextNode(this.yLabel);
        console.assert(yText != null);
        yLabel.classList.add("axis-y-label");
        yLabel.appendChild(yText);
        this.htmlBody.appendChild(yLabel);

        this.sets = []
    }

    /**
     * X-axis's label
     * @returns {string}
     */
    get xLabel() {
        return this.meta.axis.x;
    }

    /**
     * Y-axis's label
     * @returns {string}
     */
    get yLabel() {
        return this.meta.axis.y;
    }

    get xMin() {
        return this.meta.dimension.minX;
    }

    get xMax() {
        return this.meta.dimension.maxX;
    }

    get yMin() {
        return this.meta.dimension.minY;
    }

    get yMax() {
        return this.meta.dimension.maxY;
    }

    /**
     *
     * @param {HTMLElement} htmlChart
     * @returns {HTMLElement}
     */
    loadIn(htmlChart) {
        this.htmlChart = htmlChart
        this.htmlChart.innerHTML = '';
        this.htmlChart.setAttribute("type", this.type);
        this.htmlChart.appendChild(this.createHeader());
        this.htmlChart.appendChild(this.htmlBody);

        this.htmlChartData.setAttribute("frame-height", this.htmlChartData.offsetHeight.toString());
        this.htmlChartData.setAttribute("frame-width", this.htmlChartData.offsetWidth.toString());

        return this.htmlChart;
    }

    createHeader() {
        this.htmlHeader = document.createElement("chart-header");

        let spacing = document.createElement("a");
        spacing.classList.add("flex-space");
        this.htmlHeader.appendChild(spacing);

        let titleHtml = document.createElement("chart-title");
        let titleText = document.createTextNode(this.title);
        titleHtml.appendChild(titleText);
        this.htmlHeader.appendChild(titleHtml);

        let colorPicker = [
            null,
            'red',
            'green',
            'blue'
        ]
        let colorPickerHtml = document.createElement("chart-colorpicker");
        for (let color of colorPicker) {
            let aPicker = document.createElement("a");
            if (color == null) {
                aPicker.classList.add("colorpicker-classic");
                aPicker.onclick = () => {toggleColorPicker(null);};
            } else {
                aPicker.classList.add("colorpicker-colorblind-" + color);
                aPicker.onclick = () => {toggleColorPicker(color);};
            }
            colorPickerHtml.appendChild(aPicker);
        }
        this.htmlHeader.appendChild(colorPickerHtml);
        return this.htmlHeader;
    }

    createAxis() {
        let incrementX = (this.xMax - this.xMin) / 10;
        let incrementY = (this.yMax - this.yMin) / 10;

        let axisHorizontal = document.createElement("axis");
        axisHorizontal.classList.add("axis-horizontal");
        let axisHLabel = document.createElement("label");
        for (let i = 1; i <= 10; i++) {
            let a = document.createElement("a");
            let xValue = this.xMin + (incrementX*i);
            xValue = xValue % 1 === 0 ? xValue.toString() : xValue.toPrecision(2);
            let aText = document.createTextNode(xValue);
            a.appendChild(aText);
            axisHLabel.appendChild(a);
        }
        axisHorizontal.appendChild(axisHLabel);

        let axisVertical = document.createElement("axis");
        axisVertical.classList.add("axis-vertical");
        let axisVLabel = document.createElement("label");
        for (let i = 10; i > 0; i--) {
            let a = document.createElement("a");
            let value = this.yMin+(incrementY*(i));
            value = (value >= 10000) ? value.toExponential(1) : value.toString();

            let aText = document.createTextNode(value);
            a.appendChild(aText);
            axisVLabel.appendChild(a);
        }
        axisVertical.appendChild(axisVLabel);

        return [axisHorizontal, axisVertical];
    }

    clearChartData(htmlChartData) {
        for (let items of htmlChartData.getElementsByTagName("items")) {
            htmlChartData.removeChild(items);
        }

        for (let caption of this.htmlBody.getElementsByTagName("chart-caption")) {
            this.htmlBody.removeChild(caption);
        }
        if (this.createCaption) {
            this.htmlBody.appendChild(this.createCaption());
        }
    }

    get isDraw() {
        return this.meta.isdraw;
    }

    /**
     *
     * @returns {String}
     */
    get title() {
        return this.meta.title;
    }

    /**
     *
     * @returns {String}
     */
    get type() {
        return this.meta.type;
    }

    /**
     * @param {string|Object} jsonData
     */
    static fromJson(jsonData) {
        if (typeof jsonData === 'string' || jsonData instanceof String)
            jsonData = JSON.parse(jsonData);
        else if (!(jsonData instanceof Object))
            return null;

        switch (jsonData.chart.type) {
            case 'linechart':
                return new LineChart(jsonData);
            case 'barchart':
                return new BarChart(jsonData);
            case 'histogram':
                return new Histogram(jsonData);
            default:
                return null;
        }
    }
}

class Histogram extends Chart {

}

class BarChart extends Chart {

    /**
     *
     * @param jsonObject {Object}
     */
    constructor(jsonObject) {
        super(jsonObject);

        this.sets = [];
        for (let set of jsonObject.data) {
            this.sets.push(set);
        }

        this.htmlChartData.setAttribute("min-y", this.yMin);
        this.htmlChartData.setAttribute("max-y", this.yMax);
        this.htmlChartData.appendChild(this.createAxis()[1]); // add y axis
    }

    loadIn(htmlParent) {
        super.loadIn(htmlParent)

        this.htmlChart.classList.add("barchart");
        this.drawBars();

        return this.htmlChart;
    }

    get labels() {
        return this.meta.labels;
    }

    /**
     *
     * @param index {number}
     * @returns {string}
     */
    getLabel(index) {
        return this.labels[index];
    }

    /**
     *
     * @param setPosition {number}
     * @returns {number}  0x0 if set hasn't neightbour, 0x1 left, 0x2 right, 0x1 | 0x2 right & left
     */
    neighbour(setPosition) {
        let neighbour = 0;
        if (setPosition > 0) neighbour |= 0x1;
        if (setPosition < (this.sets.length-1)) neighbour |= 0x2;

        return neighbour;
    }

    drawBars() {
        this.isdraw = true;
        this.clearChartData(this.htmlChartData);

        for (let i = 0; i < this.sets.length; i++) {
            let set = this.sets[i];

            let itemsHtml = this.createSection(set.name, this.neighbour(i));
            for (let j = 0; j < set.value.length; j++) {
                itemsHtml.appendChild(this.createBar(set.value[j], set.name, this.labels[j]));
            }

            this.htmlChartData.appendChild(itemsHtml);
        }
    }

    /**
     *
     * @param name {string}
     * @param neighbour {number}
     */
    createSection(name, neighbour) {
        let itemsHtml = document.createElement("items");
        if (neighbour & 0x1)
            itemsHtml.classList.add("barchart-section-border-left");
        if (neighbour & 0x2)
            itemsHtml.classList.add("barchart-section-border-right");

        let a = document.createElement("a");
        a.classList.add("barchart-items-title");
        a.innerHTML = name;

        itemsHtml.appendChild(a);
        return itemsHtml;
    }

    /**
     *
     * @param y {number}
     * @param set {number}
     * @param label {string}
     * @returns {boolean}
     */
    setBar(y, set, label) {
        if (this.sets.length < set && this.labels.contains(label)) {
            let values = this.sets.value;
            while (values.length-1 < this.labels.indexOf(label))
                values.add(0);
            values[this.labels.indexOf(label)] = y;

            if (this.isdraw) {
                let itemsHtml = this.htmlChartData.getElementsByTagName("items")[set];
                let itemIndex = 0;

                for (let itemHtml of itemsHtml.children) {
                    if (itemHtml.getAttribute("name") === label) {
                        break;
                    }
                    itemIndex++;
                }

                let itemHtml = this.createBar(y, this.sets[set].name, label);
                if (itemIndex < itemsHtml.getElementsByTagName("items").length) {
                    itemsHtml.children[itemIndex] = itemHtml;
                } else {
                    itemsHtml.appendChild(itemHtml);
                }
            }
            return true;
        } else return false;
    }

    /**
     *
     * @param y {number}
     * @param set {string|null}
     * @param label {string}
     */
    createBar(y, set, label) {
        let barItem = document.createElement("item");
        barItem.classList.add("barchart-bar");
        barItem.setAttribute("y", y.toString());
        barItem.setAttribute("name", label);
        barItem.style.setProperty("--bar-y", (this.yRatio(y)*100).toString() + "%");
        barItem.style.setProperty("--chart-draw-color", `var(--colorpicker-${this.labels.indexOf(label)+1}`);

        let barDetail    = document.createElement("div");
        let detailHeader = document.createElement("div");
        let detailBody   = document.createElement("div");
        barDetail.classList.add("chart-detail");
        detailHeader.classList.add("detail-header");
        detailBody.classList.add("detail-body");

        let a1 = document.createElement("a");
        let a1Text = document.createTextNode(label);
        a1.appendChild(a1Text);
        detailHeader.appendChild(a1);

        if (set !== null || set !== '') {
            let a2 = document.createElement("a");
            let a2Text = document.createTextNode(`${set}`);
            a2.appendChild(a2Text);
            detailBody.appendChild(a2);
        }

        let a3 = document.createElement("a");
        let a3Text = document.createTextNode(`${this.yLabel}: ${y.toString()}`);
        a3.appendChild(a3Text);
        detailBody.appendChild(a3);

        barDetail.appendChild(detailHeader);
        barDetail.appendChild(detailBody);
        barItem.appendChild(barDetail);
        return barItem;
    }

    createCaption() {
        let captionHtml = document.createElement("chart-caption");

        let colorpickerNb = 1;
        for (let label of this.labels) {
            let item = document.createElement("item");
            let emptyDiv = document.createElement("div");
            let text = document.createTextNode(this.labels[colorpickerNb-1]);

            item.style.setProperty("--chart-draw-color", `var(--colorpicker-${colorpickerNb}`);
            item.appendChild(emptyDiv);
            item.appendChild(text);

            captionHtml.appendChild(item);
            colorpickerNb++;
        }

        return captionHtml;
    }

    yRatio(y) {
        return y / (this.yMax - this.yMin);
    }
}

class LineChart extends Chart {
    /**
     *
     * @param {Object} jsonObject
     */
    constructor(jsonObject) {
        super(jsonObject);

        this.sets = [];
        for (let set of jsonObject.data) {
            this.sets.push(set);
        }

        this.htmlChartData.setAttribute("min-x", this.xMin);
        this.htmlChartData.setAttribute("max-x", this.xMax);
        this.htmlChartData.setAttribute("min-y", this.yMin);
        this.htmlChartData.setAttribute("max-y", this.yMax);
        for (let axis of this.createAxis()) {
            this.htmlChartData.appendChild(axis);
        }
    }

    /**
     *
     * @param point {{x: number, y: number}}
     * @returns {number}
     */
    xRatio(point) {
        return point.x / (this.xMax - this.xMin);
    }

    /**
     *
     * @param point {{x: number, y: number}}
     * @returns {number}
     */
    yRatio(point) {
        return point.y / (this.yMax - this.yMin);
    }

    /**
     * @param {number} set
     * @param {number} x
     * @param {number} y
     */
    addPoint(set, x, y) {
        if (set > this.sets.length)
            return false;

        let setname = this.sets[set-1].name;
        this.sets[set-1].points += {"x": x, "y": y};

        if (this.isdraw) {
            if (this.sets[set-1].points.length > 1) {
                /**
                 *
                 * @type {{x: number, y: number}}
                 */
                let prevPoint = this.sets[set-1].points[this.sets[set-1].points.length-2];
                let dp = {
                    "x": x - prevPoint.x,
                    "y": y - prevPoint.y
                }

                this.drawSegment(set,
                    this.xRatio(prevPoint), this.yRatio(prevPoint),
                    this.xRatio(dp), this.yRatio(dp)
                );
            }
        }

        return true;
    }

    get setCount() {
        return this.sets.length;
    }

    /**
     *
     * @returns {number} the setNumber
     */
    addSet(name) {
        this.sets.push({name: name, points: []});
        return this.sets.length;
    }

    loadIn(htmlParent) {
        super.loadIn(htmlParent)

        this.htmlChart.classList.add("linechart");

        this.drawPoints();
        return this.htmlChart;
    }

    createCaption() {
        let captionHtml = document.createElement("chart-caption");

        let colorpickerNb = 1;
        for (let set of this.sets) {
            let item = document.createElement("item");
            let emptyDiv = document.createElement("div");
            let text = document.createTextNode(set.name);

            item.style.setProperty("--chart-draw-color", `var(--colorpicker-${colorpickerNb}`);
            item.appendChild(emptyDiv);
            item.appendChild(text);

            captionHtml.appendChild(item);
            colorpickerNb++;
        }

        return captionHtml;
    }

    /**
     *
     * @param point {{x: number, y: number}}
     * @param setName {string}
     * @returns {HTMLElement}
     */
    createPoint(point, setName) {
        let pointItem = document.createElement("item");
        pointItem.classList.add("linechart-dot");
        pointItem.setAttribute("x", point.x.toString());
        pointItem.setAttribute("y", point.y.toString());
        pointItem.style.setProperty("--point-x", (this.xRatio(point)*100).toString() + "%");
        pointItem.style.setProperty("--point-y", (this.yRatio(point)*100).toString() + "%");

        let pointDetail  = document.createElement("div");
        let detailHeader = document.createElement("div");
        let detailBody   = document.createElement("div");
        pointDetail.classList.add("chart-detail");
        detailHeader.classList.add("detail-header");
        detailBody.classList.add("detail-body");

        let a1 = document.createElement("a");
        let a1Text = document.createTextNode(setName);
        a1.appendChild(a1Text);

        let a2 = document.createElement("a");
        let a2Text = document.createTextNode(`${this.xLabel}: ${point.x.toString()}`);
        a2.appendChild(a2Text);

        let a3 = document.createElement("a");
        let a3Text = document.createTextNode(`${this.yLabel}: ${point.y.toString()}`);
        a3.appendChild(a3Text);

        detailHeader.appendChild(a1);
        detailBody.appendChild(a2);
        detailBody.appendChild(a3);
        pointDetail.appendChild(detailHeader);
        pointDetail.appendChild(detailBody);
        pointItem.appendChild(pointDetail);
        return pointItem;
    }

    drawPoints(clearItems = true) {
        this.isdraw = true;
        let htmlChartData = this.htmlBody.getElementsByTagName("chart-data")[0];

        if (clearItems) {
            this.clearChartData(htmlChartData);
        }

        let colorId = 1;
        for (let set of this.sets) {
            let htmlItems;
            if (clearItems) {
                htmlItems = document.createElement("items");
                this.htmlChartData.appendChild(htmlItems);
            } else {
                htmlItems = document.getElementsByTagName("items")[colorId-1]
            }
            htmlItems.style.setProperty("--chart-draw-color", `var(--colorpicker-${colorId})`);
            let points = set.points;

            points.sort((a, b) => {
                if (a.x < b.x) return -1;
                else if (a.x > b.x) return 1;
                else return 0;
            });

            /**
             *
             * @type {{x: number, y: number}|null}
             */
            let prevPoint = null;
            for (let /** @type {{x: number, y: number}} */ point of points) {
                if (prevPoint != null) {
                    let dp = {
                        "x": point.x - prevPoint.x,
                        "y": point.y - prevPoint.y
                    };

                    this.drawSegment(colorId,
                        this.xRatio(prevPoint), this.yRatio(prevPoint),
                        this.xRatio(dp), this.yRatio(dp));
                }

                htmlItems.appendChild(this.createPoint(point, set.name));
                prevPoint = point;
            }

            colorId++;
        }
    }

    drawSegments(clearItems = true) {
        if (clearItems) {

        }
    }

    /**
     *
     * @param set {number}
     * @param x {number}
     * @param y {number}
     * @param dx {number}
     * @param dy {number}
     * @returns {HTMLElement}
     */
    drawSegment(set, x, y, dx, dy) {
        x = x*100;
        y = y*100;

        let segHtml = document.createElement("item");
        segHtml.classList.add("linechart-seg");
        segHtml.setAttribute("dx", dx.toPrecision(2));
        segHtml.setAttribute("dy", dy.toPrecision(2));
        segHtml.style.setProperty("--point-x", x.toString() + "%");
        segHtml.style.setProperty("--point-y", y.toString() + "%");

        let sideXpx = dx * this.htmlChartData.offsetWidth;
        let sideYpx = dy * this.htmlChartData.offsetHeight;
        let sideHyp = Math.sqrt(Math.pow(sideXpx, 2) + Math.pow(sideYpx, 2));
        let angle = -Math.asin(sideYpx / sideHyp);

        segHtml.style.setProperty('--seg-angle', angle.toString() + "rad");
        segHtml.style.setProperty('--seg-hyp', sideHyp.toString( )+ "px");

        let itemsHtml = this.htmlBody.getElementsByTagName("items")[set-1];
        itemsHtml.appendChild(segHtml);
        return segHtml;
    }
}

let charts = {};

function getChartsByTitle(title) {
    let chartsList = [];

    for (let name of charts.keys) {
        if (charts[name].title === title) {
            chartsList.add(charts[name]);
        }
    }

    return chartsList;
}

function getChartsByType(type) {
    let chartsList = [];

    for (let name of charts.keys) {
        if (charts[name].type === type) {
            chartsList.add(charts[name]);
        }
    }

    return chartsList;
}

window.onresize = function() {
    /**
     *
     * @type {HTMLCollectionOf<Element>}
     */
    let chartsData = document.getElementsByTagName("chart-data");

    for (let elem of chartsData) {
        elem.setAttribute("frame-height", elem.offsetHeight);
        elem.setAttribute("frame-width", elem.offsetWidth);

        for (let segment of elem.getElementsByClassName("linechart-seg")) {
            let dxp = parseFloat(segment.getAttribute("dx"));
            let dyp = parseFloat(segment.getAttribute("dy"));

            let sideX = dxp * elem.offsetWidth;
            let sideY = dyp * elem.offsetHeight;
            let sideHyp = Math.sqrt(Math.pow(sideX, 2) + Math.pow(sideY, 2));
            let angle = -Math.asin(sideY / sideHyp);

            segment.style.setProperty('--seg-angle', angle.toString() + "rad");
            segment.style.setProperty('--seg-hyp', sideHyp.toString( )+ "px");
        }
    }
}

for (let htmlChart of document.getElementsByTagName('chart')) {
    if (htmlChart.getAttribute("href")) {
        let href = htmlChart.getAttribute("href");
        let name = htmlChart.getAttribute("name");
        if (href !== "") {
            readResource(href, (buf) => {
                let chart = Chart.fromJson(buf);
                if (chart) {
                    chart.loadIn(htmlChart);
                    if (name !== null && name !== '') {
                        charts[name] = chart;
                    }
                }
            });
        }
    }
}
