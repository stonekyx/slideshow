#ifndef PARAMETER_H

#define PARAMETER_H

#include <string>

namespace Slideshow {
    class Parameter {
        private:
        protected:
            Parameter() {}
        public:
            virtual ~Parameter() = 0;
    };
    inline Parameter::~Parameter() {}

    class StrParameter : public Parameter {
        private:
        protected:
            std::string value;
        public:
            StrParameter(const std::string &v):value(v) {}
            const std::string &get_value() const {
                return value;
            }
    };

    class IntParameter : public Parameter {
        private:
        protected:
            int value;
        public:
            IntParameter(const int v):value(v) {}
            int get_value() const {
                return value;
            }
    };

    class BoolParameter : public Parameter {
        private:
        protected:
            bool value;
        public:
            BoolParameter(const bool v):value(v) {}
            bool get_value() const {
                return value;
            }
    };

    class RGBParameter : public Parameter {
        private:
        protected:
            unsigned r, g, b;
        public:
            RGBParameter(unsigned r, unsigned g, unsigned b) :
                r(r), g(g), b(b) {}
            unsigned int get_value() const {
                return (r<<16) + (g<<8) + b;
            }
            unsigned int get_r() const { return r; }
            unsigned int get_g() const { return g; }
            unsigned int get_b() const { return b; }
    };
}

#endif
