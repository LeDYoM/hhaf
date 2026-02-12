export module hogl : blend_mode;

namespace haf::ogl
{
struct BlendMode
{
    enum class Factor
    {
        Zero,              ///< (0, 0, 0, 0)
        One,               ///< (1, 1, 1, 1)
        SrcColor,          ///< (src.r, src.g, src.b, src.a)
        OneMinusSrcColor,  ///< (1, 1, 1, 1) - (src.r, src.g, src.b, src.a)
        DstColor,          ///< (dst.r, dst.g, dst.b, dst.a)
        OneMinusDstColor,  ///< (1, 1, 1, 1) - (dst.r, dst.g, dst.b, dst.a)
        SrcAlpha,          ///< (src.a, src.a, src.a, src.a)
        OneMinusSrcAlpha,  ///< (1, 1, 1, 1) - (src.a, src.a, src.a, src.a)
        DstAlpha,          ///< (dst.a, dst.a, dst.a, dst.a)
        OneMinusDstAlpha   ///< (1, 1, 1, 1) - (dst.a, dst.a, dst.a, dst.a)
    };

    enum class Equation
    {
        Add,             ///< Pixel = Src * SrcFactor + Dst * DstFactor
        Subtract,        ///< Pixel = Src * SrcFactor - Dst * DstFactor
        ReverseSubtract, ///< Pixel = Dst * DstFactor - Src * SrcFactor
        Min,
        Max
    };

    constexpr BlendMode() noexcept :
        colorSrcFactor(BlendMode::Factor::SrcAlpha),
        colorDstFactor(BlendMode::Factor::OneMinusSrcAlpha),
        colorEquation(BlendMode::Equation::Add),
        alphaSrcFactor(BlendMode::Factor::One),
        alphaDstFactor(BlendMode::Factor::OneMinusSrcAlpha),
        alphaEquation(BlendMode::Equation::Add)
    {}

    constexpr BlendMode(Factor sourceFactor,
                        Factor destinationFactor,
                        Equation blendEquation) noexcept :
        colorSrcFactor(sourceFactor),
        colorDstFactor(destinationFactor),
        colorEquation(blendEquation),
        alphaSrcFactor(sourceFactor),
        alphaDstFactor(destinationFactor),
        alphaEquation(blendEquation)
    {}

    constexpr BlendMode(Factor colorSourceFactor,
                        Factor colorDestinationFactor,
                        Equation colorBlendEquation,
                        Factor alphaSourceFactor,
                        Factor alphaDestinationFactor,
                        Equation alphaBlendEquation) noexcept :
        colorSrcFactor(colorSourceFactor),
        colorDstFactor(colorDestinationFactor),
        colorEquation(colorBlendEquation),
        alphaSrcFactor(alphaSourceFactor),
        alphaDstFactor(alphaDestinationFactor),
        alphaEquation(alphaBlendEquation)
    {}

    bool operator==(const BlendMode& right) const = default;

    Factor colorSrcFactor;  ///< Source blending factor for the color channels
    Factor
        colorDstFactor;  ///< Destination blending factor for the color channels
    Equation colorEquation;  ///< Blending equation for the color channels
    Factor alphaSrcFactor;   ///< Source blending factor for the alpha channel
    Factor
        alphaDstFactor;  ///< Destination blending factor for the alpha channel
    Equation alphaEquation;  ///< Blending equation for the alpha channel
};

export constexpr BlendMode BlendAlpha(
    BlendMode::Factor::SrcAlpha,
    BlendMode::Factor::OneMinusSrcAlpha,
    BlendMode::Equation::Add,
    BlendMode::Factor::One,
    BlendMode::Factor::OneMinusSrcAlpha,
    BlendMode::Equation::Add);  ///< Blend source and dest according to dest
                                ///< alpha

export constexpr BlendMode BlendAdd(
    BlendMode::Factor::SrcAlpha,
    BlendMode::Factor::One,
    BlendMode::Equation::Add,
    BlendMode::Factor::One,
    BlendMode::Factor::One,
    BlendMode::Equation::Add);  ///< Add source to dest

export const BlendMode BlendMultiply(BlendMode::Factor::DstColor,
                                     BlendMode::Factor::Zero,
                                     BlendMode::Equation::Add);

export const BlendMode BlendMin(BlendMode::Factor::One,
                                BlendMode::Factor::One,
                                BlendMode::Equation::Min);

export const BlendMode BlendMax(BlendMode::Factor::One,
                                BlendMode::Factor::One,
                                BlendMode::Equation::Max);

export const BlendMode BlendNone(BlendMode::Factor::One,
                                 BlendMode::Factor::Zero,
                                 BlendMode::Equation::Add);

}  // namespace haf::ogl
