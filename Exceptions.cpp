//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Exceptions.h"
namespace Gaming {
    void GamingException::setName(std::string name) {

    }

    DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {

    }

    unsigned DimensionEx::getExpWidth() const {
        return 0;
    }

    unsigned DimensionEx::getExpHeight() const {
        return 0;
    }

    unsigned DimensionEx::getWidth() const {
        return 0;
    }

    unsigned DimensionEx::getHeight() const {
        return 0;
    }

    void DimensionEx::__print_args(std::ostream &os) const {

    }

    void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
        DimensionEx::__print_args(os);
    }

    InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth,unsigned minHeight, unsigned width, unsigned height)
            : DimensionEx(minWidth, minHeight, width, height) {



    }

    void OutOfBoundsEx::__print_args(std::ostream &os) const {
        DimensionEx::__print_args(os);
    }

    OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(maxWidth, maxHeight, width, height){

    }
}
