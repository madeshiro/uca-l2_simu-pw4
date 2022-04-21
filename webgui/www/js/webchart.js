
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


    }
}

class Histogram extends Chart {

}

class BarChart extends Chart {

}

class LineChart extends Chart {

}