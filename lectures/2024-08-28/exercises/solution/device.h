/*******************************************************************************
 * @brief Software implementation of devices.
 ******************************************************************************/
#pragma once

#include <iostream>

/*******************************************************************************
 * @brief Enum class implementation of product status.
 ******************************************************************************/
enum class ProductStatus 
{ 
    Prototype,   // Product is a prototype.
    Active,      // Product is active.
    Discontinued // Product is discontinued.
};

/*******************************************************************************
 * @brief Class implementation of devices.
 ******************************************************************************/
class Device
{
public:

    /** @brief Default destructor deleted. */
    Device() = delete; 

    /*******************************************************************************
     * @brief Creates new device.
     * 
     * @param manufacturer      Device manufacturer.
     * @param model             Device model.
     * @param revision          Device revision.
     * @param yearOfManufacture The year the device was manufactured.
     * @param color             Device color.
     * @param productStatus     Product status of the device (default = active).
     ******************************************************************************/
    Device(const char* manufacturer, const char* model, const unsigned revision,
           const unsigned yearOfManufacture, const char* color, 
           const ProductStatus productStatus = ProductStatus::Active);

    /*******************************************************************************
     * @brief Provides the device manufacturer.
     * 
     * @return The device manufacturer as text.
     ******************************************************************************/
    const char* manufacturer() const;

    /*******************************************************************************
     * @brief Provides the device model.
     * 
     * @return The device model as text.
     ******************************************************************************/
    const char* model() const;

    /*******************************************************************************
     * @brief Provides the device revision.
     * 
     * @return The revision as an unsigned integer.
     ******************************************************************************/
    unsigned revision() const;

    /*******************************************************************************
     * @brief Provides the year the device was manufactured.
     * 
     * @return The year the device was manufactured as an unsigned integer.
     ******************************************************************************/
    unsigned yearOfManufacture() const;

   
    /*******************************************************************************
     * @brief Provides the device color.
     * 
     * @return The device color as text.
     ******************************************************************************/
    const char* color() const;
    
    /*******************************************************************************
     * @brief Provides the product status of the device.
     * 
     * @return The product status of the device as an enumerator of enum class
     *         ProductStatus.
     ******************************************************************************/
    ProductStatus productStatus() const;

    /*******************************************************************************
     * @brief Sets the color of the device.
     * 
     * @param newColor The new device color.
     ******************************************************************************/
    void setColor(const char* newColor);

    /*******************************************************************************
     * @brief Sets the product status of the device.
     * 
     * @param newProductStatus The new product status of the device.
     ******************************************************************************/
    void setProductStatus(const ProductStatus newProductStatus);

    /*******************************************************************************
     * @brief Prints device information.
     * 
     * @param ostream Reference to output stream (default = terminal print).
     ******************************************************************************/
    void print(std::ostream& ostream = std::cout) const;

private:

    /*******************************************************************************
     * @brief Provides the product status of the device as text.
     * 
     * @return The product status of the device as text.
     ******************************************************************************/
    const char* productStatusAsText() const;

    const char* myManufacturer;    // Device manufacturer. 
    const char* myModel;           // Device model.
    unsigned myRevision;           // Device revision.
    unsigned myYearOfManufacture;  // Year of manufacture for the device.
    const char* myColor;           // Device color.
    ProductStatus myProductStatus; // Product status of this device.
};