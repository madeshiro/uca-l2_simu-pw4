
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

        this.htmlBody = document.createElement("chart-body");
    }

    /**
     *
     * @param {HTMLElement} htmlParent
     * @returns {HTMLElement}
     */
    loadIn(htmlParent) {
        this.htmlChart = document.createElement("chart");
        this.htmlChart.setAttribute("type", this.type);
        this.htmlChart.appendChild(this.createHeader());
        this.htmlChart.appendChild(this.htmlBody);

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

    createCaption() {
        return null;
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
     * @param {string} jsonData
     */
    static fromJson(jsonData) {
        let obj = JSON.parse(jsonData);
        if (obj === null) {
            return null;
        }

        switch (obj.chart.type) {
            case 'linechart':
                return new LineChart(obj);
            case 'barchart':
                return new BarChart(obj);
            case 'histogram':
                return new Histogram(obj);
            default:
                return null;
        }
    }
}

class Histogram extends Chart {

}

class BarChart extends Chart {

}

class LineChart extends Chart {
    /**
     *
     * @param {Object} jsonObject
     */
    constructor(jsonObject) {
        super(jsonObject);

        /**
         *
         * @type {Array}
         */
        this.sets = [];
        for (let set of jsonObject.data) {
            this.sets.push(set);
        }

        let xLabel = document.createElement("a");
        let yLabel = document.createElement("a");
        let xText  = document.createTextNode(this.xLabel);
        let yText  = document.createTextNode(this.yLabel);
        xLabel.appendChild(xText);
        yLabel.appendChild(yText);
    }

    get xLabel() {
        return this.meta.axis.x;
    }

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

    createCaption() {
        document.createElement("chart-caption");

        let colorpickerNb = 1;
        for (let set in this.sets) {
            let item = document.createElement("item");
            let emptyDiv = document.createElement("div");
            let text = document.createTextNode(set.name);

            item.style.setProperty("--chart-draw-color", `var(--colorpicker-${colorpickerNb}`);
            item.appendChild(emptyDiv);
            item.appendChild(text);

            colorpickerNb++;
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
     * @param {number} setNumber
     * @param {number} x
     * @param {number} y
     */
    addPoint(setNumber, x, y) {
        if (setNumber > this.sets.length)
            return false;

        this.sets[setNumber-1].points.add({"x": x, "y": y});
        return true;
    }

    get setCount() {
        return this.sets.length;
    }

    /**
     *
     * @returns {number} the setNumber
     */
    addSet() {
        this.sets.push([]);
        return this.sets.length;
    }

    drawPoints(clearItems = true) {
        let colorId = 1;
        for (let set of this.sets) {
            let htmlChartData = this.htmlBody.getElementsByTagName("chart-data")[0];
            let points = set.points;

            if (clearItems) {
                for (let items in htmlChartData.getElementsByTagName("items")) {
                    htmlChartData.removeChild(items);
                }
            }

            points.sort((a, b) => {
                if (a.x < b.x) return -1;
                else if (a.x > b.x) return 1;
                else return 0;
            });

            let prevPoint = null;
            for (let point of points) {
                if (prevPoint != null) {
                    let segItem = document.createElement("item");
                    segItem.classList.add("linechart-seg");


                }

                let pointItem = document.createElement("item");
                pointItem.classList.add("linechart-dot");
                pointItem.setAttribute("x", point.x);
                pointItem.setAttribute("y", point.y);

                prevPoint = point;
            }

            colorId++;
        }
    }
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