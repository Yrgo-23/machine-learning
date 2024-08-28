#include "device.h"

// -----------------------------------------------------------------------------
Device::Device(const char* manufacturer, const char* model, const unsigned revision,
               const unsigned yearOfManufacture, const char* color, 
               const ProductStatus productStatus)
    : myManufacturer{manufacturer}
    , myModel{model}
    , myRevision{revision}
    , myYearOfManufacture{yearOfManufacture}
    , myColor{color}
    , myProductStatus{productStatus} {}

// -----------------------------------------------------------------------------
const char* Device::manufacturer() const { return myManufacturer; }

// -----------------------------------------------------------------------------
const char* Device::model() const { return myModel; }

// -----------------------------------------------------------------------------
unsigned Device::revision() const { return myRevision; }

// -----------------------------------------------------------------------------
unsigned Device::yearOfManufacture() const { return myYearOfManufacture; }

// -----------------------------------------------------------------------------
const char* Device::color() const { return myColor; }

// -----------------------------------------------------------------------------
ProductStatus Device::productStatus() const { return myProductStatus; }

// -----------------------------------------------------------------------------
void Device::setColor(const char* newColor) { myColor = newColor; }

// -----------------------------------------------------------------------------
void Device::setProductStatus(const ProductStatus newProductStatus) 
{ 
    myProductStatus = newProductStatus; 
}

// -----------------------------------------------------------------------------
void Device::print(std::ostream& ostream) const
{
    ostream << "--------------------------------------------------------------------------------\n";
    ostream << "Manufacturer:\t\t" << myManufacturer << "\n";
    ostream << "Model:\t\t\t" << myModel << "\n";
    ostream << "Revision:\t\t" << myRevision << "\n";
    ostream << "Year of manufacture:\t" << myYearOfManufacture << "\n";
    ostream << "Color:\t\t\t" << myColor << "\n";
    ostream << "Product status:\t\t" << productStatusAsText() << "\n";
    ostream << "--------------------------------------------------------------------------------\n\n";
}

// -----------------------------------------------------------------------------
const char* Device::productStatusAsText() const
{
    if (myProductStatus == ProductStatus::Prototype)   { return "Prototype"; }
    else if (myProductStatus == ProductStatus::Active) { return "Active"; }
    else                                               { return "Discontinued"; }
}
