#include "cxx/simulation/statisticaltools.h"
#include "mt19937ar.h"

namespace UCA_L2INFO_PW4
{
    PgfPlotsData::Dimension::Dimension(double width, double height):
        _F_xMin(.0), _F_xMax(-1.0), _F_yMin(.0), _F_yMax(-1.0),
        _F_width(width), _F_height(height)
    { /* ... */ }

    PgfPlotsData::Dimension::Dimension(double xmin, double xmax, double ymin, double ymax):
        _F_xMin(xmin), _F_xMax(xmax), _F_yMin(ymin), _F_yMax(ymax),
        _F_width(.0), _F_height(.0)
    { /* ... */ }

    inline double PgfPlotsData::Dimension::xMin() const
    {
        return _F_xMin;
    }

    inline double PgfPlotsData::Dimension::xMax() const
    {
        return _F_xMax;
    }

    inline double PgfPlotsData::Dimension::yMin() const
    {
        return _F_yMin;
    }

    inline double PgfPlotsData::Dimension::yMax() const
    {
        return _F_yMax;
    }

    void PgfPlotsData::Dimension::setXMin(double x)
    {
        _F_xMin = x;
    }

    void PgfPlotsData::Dimension::setXMax(double x)
    {
        _F_xMax = x;
    }

    void PgfPlotsData::Dimension::setYMin(double y)
    {
        _F_yMin = y;
    }

    void PgfPlotsData::Dimension::setYMax(double y)
    {
        _F_yMax = y;
    }

    inline double PgfPlotsData::Dimension::width() const
    {
        return _F_width;
    }

    inline double PgfPlotsData::Dimension::height() const
    {
        return _F_height;
    }

    void PgfPlotsData::Dimension::setWidth(double width)
    {
        _F_width = width;
    }

    void PgfPlotsData::Dimension::setHeight(double height)
    {
        _F_height = height;
    }

    String PgfPlotsData::Dimension::toString() const
    {
        String str;
        if (_F_width > 0)
        {
            str.append(String("width={0},").format(_F_width));
        }
        if (_F_height > 0)
        {
            str.append(String("height={0},\n").format(_F_height));
        }

        str.append(String("xmin={0},").format(_F_xMin));
        if (_F_xMax > _F_xMin)
            str.append(String("xmax={0},").format(_F_xMax));

        str.append(String("ymin={0},").format(_F_yMin));
        if (_F_yMax > _F_yMin)
            str.append(String("ymax={0},\n").format(_F_yMax));

        return str;
    }

    PgfPlotsData::PgfPlotsData(Dimension dimension): _F_dimension(dimension)
    {/* ... */}

    String PgfPlotsData::generatePlotHeader() const
    {
        String str("\\pgfplotsset { \n"
                   "title={{0}},\n"
                   "compat=1.17,\n"
                   "scale=only axis,\n");
        str = str.format(this->toString());
        str.append(_F_dimension.toString());
        str.append("}");
        return str;
    }

    String PgfPlotsData::toPgfPlots() const
    {
        return generatePlotHeader().concat(generatePlot());
    }

    ProbabilityDF::ProbabilityDF(String name): _F_name(name), _F_pdf()
    { /* ... */ }

    ProbabilityDF::ProbabilityDF(const ProbabilityDF &obj): _F_pdf(obj._F_pdf)
    { /* ... */ }

    void ProbabilityDF::addGroup(String group, double probability)
    {
        _F_pdf.set(group, probability);
    }

    void ProbabilityDF::removeGroup(String group)
    {
        _F_pdf.remove(group);
    }

    double ProbabilityDF::getProbabilityFrom(String group) const
    {
        double* v(_F_pdf.get(group));
        if (v)
        {
            return *v;
        }
        else return -1.;
    }

    String ProbabilityDF::generatePlot() const
    {
        // TODO ProbabilityDF::generatePlot
        return String();
    }

    int ProbabilityDF::getType() const
    {
        return BarChart | Graph2D;
    }

    String ProbabilityDF::toString() const
    {
        return _F_name;
    }

    uint_t ProbabilityDF::size() const
    {
        return _F_pdf.size();
    }

    CumulativeDF::CDFNode::CDFNode(String _name, double _cumul): name(_name), cumul(_cumul)
    { /* ... */ }

    CumulativeDF::CumulativeDF(const ProbabilityDF &df): _F_probabilityDF(df),
        _F_cdf(new CDFNode[df.size()])
    { /* ... */ }

    CumulativeDF::CumulativeDF(const CumulativeDF &obj): _F_probabilityDF(obj.getPDF()),
        _F_cdf(new CDFNode[obj.getPDF().size()])
    {
        for (uint_t i(0); i < _F_probabilityDF.size(); i++)
            _F_cdf[i] = obj._F_cdf[i];
    }

    CumulativeDF::~CumulativeDF()
    {
        if (_F_cdf)
            delete[] _F_cdf;
    }

    const ProbabilityDF& CumulativeDF::getPDF() const
    {
        return _F_probabilityDF;
    }

    int CumulativeDF::draw()
    {
        double variate = genrand_real1();
        for (uint_t i(0); i < _F_probabilityDF.size(); i++)
        {
            if (variate <= _F_cdf[i].cumul)
                return (int) i;
        }
        return (int) _F_probabilityDF.size()-1;
    }

    int CumulativeDF::getGroupID(String name)
    {
        for (uint_t i(0); i < _F_probabilityDF.size(); i++)
        {
            if (_F_cdf[i].name == name)
                return (int) i;
        }

        return -1;
    }

    String CumulativeDF::getGroupName(int id)
    {
        if (id >= 0 && (uint_t) id < _F_probabilityDF.size())
        {
            return _F_cdf[id].name;
        }
        else
        {
            return String();
        }
    }



    String CumulativeDF::generatePlot() const
    {
        // TODO CumulativeDF::generatePlot
        return String();
    }

    int CumulativeDF::getType() const
    {
        return BarChart | Graph2D;
    }

    String CumulativeDF::toString() const
    {
        return _F_probabilityDF.toString();
    }



    hash_t Histogram::Interval::hashCode() const
    {
        union {
            double v;
            void*  ptr;
        } b1, b2;

        b1.v = min;
        b2.v = max;

        return (hash_t) b1.ptr << 32 | (hash_t) b2.ptr;
    }

    Coordinates::Coordinates(double _x, double _y): x(_x), y(_y)
    { /* ... */ }

    String Coordinates::toString() const
    {
        return String("({0}, {1}) ").format(x, y);
    }

    LineChart::LineChart(String title, double xmin, double xscale): _F_values(),
        _F_xmin(xmin), _F_xscale(xscale), _F_title(title)
    {
        /* ... */
    }

    double LineChart::registerValue(double val)
    {
        double x = _F_xmin + (_F_xscale*_F_values.size());
        _F_values.add(Coordinates(x, val));
        return x;
    }

    String LineChart::generatePlot() const
    {
        // TODO LineChart::generatePlot
        return String();
    }

    int LineChart::getType() const
    {
        return Graph2D | Type::LineChart;
    }

    String LineChart::toString() const
    {
        return _F_title;
    }

    uint_t LineChart::size() const
    {
        return _F_values.size();
    }

    double LineChart::sum() const
    {
        double _sum(0);
        for (uint_t i(0); i < _F_values.size(); i++)
        {
            _sum += _F_values[i].y;
        }

        return _sum;
    }

    double LineChart::avg() const
    {
        return sum() / (double) _F_values.size();
    }
}