#ifndef CPP_STATISTICALTOOLS_H
#define CPP_STATISTICALTOOLS_H
#include "cxx/oop/container.hpp"
#include "cxx/json/json.h"
#include "cxx/oop/binary.h"
#include "cxx/oop/object"

namespace UCA_L2INFO_PW4
{
    using json::JsonStringifyable;

    struct Drawable : public Object
    {
        virtual int draw() = 0;
    };

    class PgfPlotsData : public Object
    {
    public:
        class Dimension : public Object
        {
            double _F_xMin, _F_xMax, _F_yMin, _F_yMax;
            double _F_width, _F_height;
        public:
            Dimension() = default;
            Dimension(double width, double height);
            Dimension(double xmin, double xmax, double ymin, double ymax);
            Dimension(const Dimension& dim) = default;
            ~Dimension() = default;

            inline double xMin() const;
            inline double xMax() const;
            inline double yMin() const;
            inline double yMax() const;

            void setXMin(double x);
            void setXMax(double x);
            void setYMin(double y);
            void setYMax(double y);

            inline double width() const;
            inline double height() const;

            void setWidth(double width);
            void setHeight(double height);

            virtual String toString() const override;
        };

        enum Type : int
        {
            Graph2D = 0x10,
            // Graph3D = 0x20,

            Histogram = 0x100,
            BarChart  = 0x200,
            LineChart = 0x400
        };

    protected:
        Dimension _F_dimension;
    public:
        PgfPlotsData() = default;
        PgfPlotsData(Dimension dimension);
        ~PgfPlotsData() = default;

        virtual String generatePlotHeader() const;
        virtual String toPgfPlots() const;

        virtual String generatePlot() const = 0;
        virtual int getType() const = 0;
    };

    class ProbabilityDF : public PgfPlotsData
    {
        String _F_name;
        HashMap<String, double> _F_pdf;
    public:
        ProbabilityDF(String name);
        ProbabilityDF(const ProbabilityDF& obj);
        virtual ~ProbabilityDF() = default;

        void addGroup(String group, double probability);
        void removeGroup(String group);
        double getProbabilityFrom(String group) const;

        uint_t size() const;

        virtual String generatePlot() const override;
        virtual int getType() const override;
        virtual String toString() const override;

        ProbabilityDF& operator =(const ProbabilityDF& pdf);
    };

    class CumulativeDF : public PgfPlotsData, Drawable
    {
        struct CDFNode
        {
            String name;
            double cumul;

            CDFNode() = default;
            CDFNode(String _name, double _cumul);
            ~CDFNode() = default;
        };

        const ProbabilityDF _F_probabilityDF;
        CDFNode* _F_cdf;
    public:
        CumulativeDF(const ProbabilityDF& df);
        CumulativeDF(const CumulativeDF& obj);
        virtual ~CumulativeDF();

        const ProbabilityDF& getPDF() const;
        int draw() override;
        int drawFromId();

        int getGroupID(String name);
        String getGroupName(int id);

        virtual String generatePlot() const override;
        virtual int getType() const override;
        virtual String toString() const override;
    };

    class BarChart : public JsonStringifyable, Binaries, PgfPlotsData
    {
        String _F_name;
    protected:
        HashMap<String, ulong_t> _F_bins;
        ulong_t _F_total;
        ulong_t _F_pop;
    public:
        BarChart(String name);
        BarChart(const BarChart& histo);
        virtual ~BarChart() = default;

        virtual ulong_t getPopulation() const;
        virtual ulong_t getValuesSum() const;

        virtual ulong_t set(const Object& which, ulong_t amount);
        virtual void    remove(const Object& which);

        virtual String generatePlot() const override;
        virtual int getType() const override;
        virtual String toString() const override;
    };

    class Histogram : public PgfPlotsData, JsonStringifyable, Binaries
    {
        struct Interval : public Object
        {
            double min, max;
            long_t value = 0;

            Interval(double _min, double _max);
            virtual hash_t hashCode() const override;
        };

        Vector<Interval> _F_intervals;
    public:
        Histogram(double min, double interval, uint_t count);
        virtual ~Histogram() override;

        long_t increment(double which, long_t many = 1);

        virtual String generatePlot() const override;
        virtual int getType() const override;
    };

    struct Coordinates : public Object
    {
        double x, y;

        Coordinates(double _x, double _y);
        ~Coordinates() = default;

        String toString() const override;
    };

    class LineChart : public PgfPlotsData, Iterable<Coordinates>
    {
        Vector<Coordinates> _F_values;
        double _F_xmin, _F_xscale;

        String _F_title;
    public:
        LineChart(String title, double xmin, double xscale);
        ~LineChart() = default;

        double registerValue(double val);
        uint_t size() const;

        virtual String generatePlot() const override;
        virtual int getType() const override;
        virtual String toString() const override;

        double sum() const;
        double avg() const;
    };
}

#endif //CPP_STATISTICALTOOLS_H
