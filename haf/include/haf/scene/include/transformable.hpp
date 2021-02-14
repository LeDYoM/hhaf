#ifndef HAF_SCENE_TRANSFORMABLE_INCLUDE_HPP
#define HAF_SCENE_TRANSFORMABLE_INCLUDE_HPP

#include "matrix4x4.hpp"
#include "transformation_properties.hpp"
#include "transformation.hpp"
#include <mtypes/include/vector.hpp>
#include <mtypes/include/vector2d.hpp>
#include <mtypes/include/rect.hpp>
#include <mtypes/include/propertystate.hpp>

namespace haf::scene
{
/**
 * @brief This class adds methods needed for an object to be Transformable,
 * that is, providing a @b Transformation and methods to modify this
 * Transformation.
 * @see Transofrmation
 */
class Transformable : public Transformation
{
public:
    using BaseClass = Transformation;  ///< Shortcut for the baseclass
    using BaseClass::prop;             ///< Export properties

    using Scalar = Matrix4x4::Scalar;  ///< Type Scalar for this class
    using VectorScalar =
        mtps::vector2d<Scalar>;  ///< Type VectorScalar for this class
    using RectScalar =
        mtps::Rect<Scalar>;  ///< Type of RectScalar for this class

    /**
     * @brief Construct a new Transformable object. The object will be
     * initialized with default properties
     */
    Transformable() noexcept;

    /**
     * @brief Destroy the Transformable object
     */
    virtual ~Transformable();

    /**
     * @brief Get a copy of the current stored global transformation. No
     * updates will be performed.
     * @return Matrix4x4 const& The global transformation.
     */
    Matrix4x4 const& globalTransform() const noexcept;

    /**
     * @brief Get a copy of the current stored local transformation. No
     * updates will be performed.
     * @return Matrix4x4 const& The local transformation.
     */
    Matrix4x4 const& localTransform() const noexcept;

    /**
     * @brief Export @b Transformable::rotateAround
     * @see Transformable
     */
    using Transformation::rotateAround;

    /**
     * @brief Export @b Transformable::scaleAround
     * @see Transformable
     */
    using Transformation::scaleAround;

    /**
     * @brief Add a new @b Transformation to the extra transformations of the
     * object.
     * @return mtps::size_type Index to refer to new added @b Transformation
     */
    mtps::size_type addTransformation();

    /**
     * @brief Remove last @b Transformation grom the extra transformations of
     * the object.
     * @note If no extra transformations are contained
     * (numTransformations() == 1U), the you have UB.
     * @return mtps::size_type Count of extra transformations.
     */
    mtps::size_type removeTransformation();

    /**
     * @brief Total number of @b Transformation objects
     * @return mtps::size_type 1 + the number of extra transformations
     */
    mtps::size_type numTransformations() const noexcept;

    /**
     * @brief Get the Transformation object at a given index
     * @note If index is invalid ypu will have UB.
     * @param index Index of the transformation. Starting at 0
     * @return Transformation& Object at the specified index
     */
    Transformation& getTransformation(mtps::size_type const index) noexcept;

    bool updateTransformations(bool const parentTransformationChanged,
                               Matrix4x4 const& parentTransformation) noexcept;

    bool updateLocalTransformationsIfNecessary() noexcept;

private:
    void updateGlobalTransformation(Matrix4x4 const&) noexcept;

    Matrix4x4 global_transform_;  ///< Global Transformation Matrix cached
    Matrix4x4 local_transform_;   ///< Current local Transformation cached

    /**
     * Extra transformations contained in this object. One is at least always
     * there
     */
    mtps::vector<Transformation> extra_transformations_;
};
}  // namespace haf::scene

#endif
