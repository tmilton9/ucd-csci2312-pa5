//
// Created by Travis Milton on 12/10/15.
//

#include <iosfwd>
#include "Exceptions.h"
namespace Gaming {
	//************************************
	// Method:    operator<<
	// FullName:  Gaming::operator<<
	// Access:    public
	// Returns:   std::ostream&
	// Qualifier:
	// Parameter: std::ostream & os
	// Parameter: const GamingException & ex
	//************************************
	std::ostream &operator<<(std::ostream &os, const GamingException &ex) {
		os << "Exception occured: " << ex.getName() << " ";
		ex.__print_args(os);
		return os;
	}

	//************************************
	// Method:    DimensionEx
	// FullName:  Gaming::DimensionEx::DimensionEx
	// Access:    public
	// Returns:
	// Qualifier:
	// Parameter: unsigned expWidth
	// Parameter: unsigned expHeight
	// Parameter: unsigned width
	// Parameter: unsigned height
	//************************************
	DimensionEx::DimensionEx(unsigned expWidth, unsigned expHeight, unsigned width, unsigned height) {
		__exp_width  = expWidth;
		__exp_height = expHeight;
		__width      = width;
		__height     = height;
	}

	//************************************
	// Method:    InsufficientDimensionsEx
	// FullName:  Gaming::InsufficientDimensionsEx::InsufficientDimensionsEx
	// Access:    public
	// Returns:
	// Qualifier: : DimensionEx(minWidth, minHeight, width, height)
	// Parameter: unsigned minWidth
	// Parameter: unsigned minHeight
	// Parameter: unsigned width
	// Parameter: unsigned height
	//************************************
	InsufficientDimensionsEx::InsufficientDimensionsEx(unsigned minWidth, unsigned minHeight, unsigned width,
	                                                   unsigned height) : DimensionEx(minWidth, minHeight, width,
	                                                                                  height) {
		setName("InsufficientDimensionsEx");
	}

	//************************************
	// Method:    __print_args
	// FullName:  Gaming::InsufficientDimensionsEx::__print_args
	// Access:    private
	// Returns:   void
	// Qualifier: const
	// Parameter: std::ostream & os
	//************************************
	void InsufficientDimensionsEx::__print_args(std::ostream &os) const {
		os << "(__exp_width: " << __exp_width << ", __exp_height: " << __exp_height << ", PassedWidth: "
		<< __width << ", PassedHeight: " << __height << ")";
	}

	//************************************
	// Method:    OutOfBoundsEx
	// FullName:  Gaming::OutOfBoundsEx::OutOfBoundsEx
	// Access:    public
	// Returns:
	// Qualifier: : DimensionEx(maxWidth, maxHeight, width, height)
	// Parameter: unsigned maxWidth
	// Parameter: unsigned maxHeight
	// Parameter: unsigned width
	// Parameter: unsigned height
	//************************************
	OutOfBoundsEx::OutOfBoundsEx(unsigned maxWidth, unsigned maxHeight, unsigned width, unsigned height) : DimensionEx(
			maxWidth, maxHeight, width, height) { setName("OutOfBoundsEx"); }

	//************************************
	// Method:    __print_args
	// FullName:  Gaming::OutOfBoundsEx::__print_args
	// Access:    private
	// Returns:   void
	// Qualifier: const
	// Parameter: std::ostream & os
	//************************************
	void OutOfBoundsEx::__print_args(std::ostream &os) const {
		os << "(maxWIdth: " << __exp_width << ", maxHeight: " << __exp_height << ", PassedWidth: " << __width
		<< ", PassedHeight:" << __height << ")";
	}
}