/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2015 Scientific Computing and Imaging Institute,
   University of Utah.


   Permission is hereby granted, free of charge, to any person obtaining a
   copy of this software and associated documentation files (the "Software"),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
   THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
   FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
   DEALINGS IN THE SOFTWARE.
   */
/// @todo Documentation Core/Datatypes/ColorMap.cc

#include <Core/Math/MiscMath.h>
#include <Core/Datatypes/ColorMap.h>
#include <Core/Logging/Log.h>
#include <iostream>
#include <boost/functional/factory.hpp>
#include <boost/function.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm/copy.hpp>

using namespace SCIRun;
using namespace SCIRun::Core::Datatypes;
using namespace SCIRun::Core::Geometry;
using namespace SCIRun::Core::Logging;

ColorMap::ColorMap(ColorMapStrategyHandle color, const std::string& name, const size_t resolution, const double shift,
  const bool invert, const double rescale_scale, const double rescale_shift, const std::vector<double>& alphaPoints)
  : color_(color), nameInfo_(name), resolution_(resolution), shift_(shift),
  invert_(invert), rescale_scale_(rescale_scale), rescale_shift_(rescale_shift),
  alphaLookup_(alphaPoints)
{

}

ColorMap* ColorMap::clone() const
{
  return new ColorMap(*this);
}



namespace detail
{

  class Rainbow : public ColorMapStrategy
  {
  public:
    virtual ColorRGB getColorMapVal(double v) const override;
  };

  class OldRainbow : public ColorMapStrategy
  {
  public:
    virtual ColorRGB getColorMapVal(double v) const override;
  };

  class Blackbody : public ColorMapStrategy
  {
  public:
    virtual ColorRGB getColorMapVal(double v) const override;
  };

  class Grayscale : public ColorMapStrategy
  {
  public:
    virtual ColorRGB getColorMapVal(double v) const override;
  };

  class OrangeBlackLime : public ColorMapStrategy
  {
  public:
    virtual ColorRGB getColorMapVal(double v) const override;
  };

  class Darkhue : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class Lighthue : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class Don : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class RedTint : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class OrangeTint : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class YellowTint : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class GreenTint : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class CyanTint : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class BlueTint : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class PurpleTint : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class Turbo : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class Magma : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class Inferno : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class Plasma : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class Viridis : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class Cividis : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class BPSeismic : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class MixedRainbow : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class MixedGrayScale : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  class PinkWhiteBlue : public ColorMapStrategy
  {
  public:
    virtual Core::Datatypes::ColorRGB getColorMapVal(double v) const override;
  };

  typedef boost::function<ColorMapStrategy*()> ColorMapMaker;
  static std::map<std::string, ColorMapMaker> colorMapFactoryMap =
  {
    { "Rainbow", boost::factory<Rainbow*>() },
    { "Old Rainbow", boost::factory<OldRainbow*>() },
    { "Blackbody", boost::factory<Blackbody*>() },
    { "Grayscale", boost::factory<Grayscale*>() },
    { "Orange,Black,Lime", boost::factory<OrangeBlackLime*>() },
    { "Darkhue", boost::factory<Darkhue*>() },
    { "Lighthue", boost::factory<Lighthue*>() },
    { "Don", boost::factory<Don*>() },
    { "Red Tint", boost::factory<RedTint*>() },
    { "Orange Tint", boost::factory<OrangeTint*>() },
    { "Yellow Tint", boost::factory<YellowTint*>() },
    { "Green Tint", boost::factory<GreenTint*>() },
    { "Cyan Tint", boost::factory<CyanTint*>() },
    { "Blue Tint", boost::factory<BlueTint*>() },
    { "Purple Tint", boost::factory<PurpleTint*>() },
    { "Turbo", boost::factory<Turbo*>() },
    { "Magma", boost::factory<Magma*>() },
    { "Inferno", boost::factory<Inferno*>() },
    { "Plasma", boost::factory<Plasma*>() },
    { "Viridis", boost::factory<Viridis*>() },
    { "Cividis", boost::factory<Cividis*>() },
    { "BP Seismic", boost::factory<BPSeismic*>() },
    { "Mixed Rainbow", boost::factory<MixedRainbow*>() },
    { "Mixed GrayScale", boost::factory<MixedGrayScale*>() },
    { "Pink,White,Blue", boost::factory<PinkWhiteBlue*>() }
  };
}

ColorMapHandle StandardColorMapFactory::create(const std::string& name, const size_t &res,
  const double &shift, const bool &invert,
  const double &rescale_scale, const double &rescale_shift, const std::vector<double>& alphaPoints)
{
  using namespace detail;
  ColorMapStrategyHandle color;
  auto maker = colorMapFactoryMap.find(name);
  if (maker != colorMapFactoryMap.end())
    color.reset(maker->second());
  else
  {
    logError("Color map name not implemented/recognized. Returning Rainbow.");
    color.reset(new Rainbow);
  }

  return boost::make_shared<ColorMap>(color, name, res, shift, invert, rescale_scale, rescale_shift, alphaPoints);
}

StandardColorMapFactory::NameList StandardColorMapFactory::getList()
{
  std::vector<std::string> names;
  boost::copy(detail::colorMapFactoryMap | boost::adaptors::map_keys, std::back_inserter(names));
  return names;
}

/**
 * @name getTransformedColor
 * @brief This method transforms the raw data into ColorMap space.
 * This includes the resolution, the gamma shift, and data rescaling (using data min/max)
 * @param v The input value from raw data that will be transformed (usually into {0,1} space).
 * @return The scalar double value transformed into ColorMap space from raw data.
 */
double ColorMap::getTransformedValue(double f) const
{
  const double rescaled01 = static_cast<double>((f + rescale_shift_) * rescale_scale_);

  double v = std::min(std::max(0., rescaled01), 1.);
  double shift = shift_;
  if (invert_) {
    v = 1.f - v;
    shift *= -1.;
  }
  //apply the resolution
  v = static_cast<double>((static_cast<int>(v *
    static_cast<double>(resolution_)))) /
    static_cast<double>(resolution_ - 1);
  // the shift is a gamma.
  double denom = std::tan(M_PI_2 * (0.5 - std::min(std::max(shift, -0.99), 0.99) * 0.5));
  // make sure we don't hit divide by zero
  if (std::isnan(denom)) denom = 0.f;
  denom = std::max(denom, 0.001);
  v = std::pow(v, (1. / denom));
  return std::min(std::max(0.,v),1.);
}
/**
 * @name getColorMapVal
 * @brief This method returns the RGB value for the current colormap parameters.
 * The input comes from raw data values. To scale to data, ColorMap
 *           must be created with those parameters. The input is transformed, then
 *           used to select a color from a set of color maps (currently defined by
 *           strings.
 * @param v The input value from raw data that will be mapped to a color.
 * @return The RGB value mapped from the transformed input into the ColorMap's named map.
 */
ColorRGB ColorMap::getColorMapVal(double v) const
{
  double f = getTransformedValue(v);
  auto colorWithoutAlpha = color_->getColorMapVal(f);
  return applyAlpha(f, colorWithoutAlpha);
}

ColorRGB ColorMap::applyAlpha(double transformed, ColorRGB colorWithoutAlpha) const
{
  double a = alpha(transformed);
  return ColorRGB(colorWithoutAlpha.r(), colorWithoutAlpha.g(), colorWithoutAlpha.b(), a);
}

double ColorMap::alpha(double transformedValue) const
{
  if(alphaLookup_.size() == 0) return 0.5;
  uint i;
  for(i = 0; (i < alphaLookup_.size()) && (alphaLookup_[i] < transformedValue); i += 2);

  double startx = 0.0f, starty, endx = 1.0f, endy;
  if(i == 0)
  {
    endx = alphaLookup_[0];
    starty = endy = alphaLookup_[1];
  }
  else if(i == alphaLookup_.size())
  {
    startx = alphaLookup_[i - 2];
    endy = starty = alphaLookup_[i - 1];
  }
  else
  {
    startx = alphaLookup_[i - 2];
    starty = alphaLookup_[i - 1];
    endx = alphaLookup_[i + 0];
    endy = alphaLookup_[i + 1];
  }

  double interp = (transformedValue - startx) / (endx - startx);
  double value = ((1.0f - interp) * starty + (interp) * endy);
  return value;
}


/**
 * @name valueToColor
 * @brief Takes a scalar value and directly passes into getColorMap.
 * @param The raw data value as a scalar double.
 * @return The RGB value mapped from the scalar.
 */
ColorRGB ColorMap::valueToColor(double scalar) const
{
  return getColorMapVal(scalar);
}

/**
 * @name valueToColor
 * @brief Takes a tensor value and creates an RGB value based on the magnitude of the eigenvalues.
 * @param The raw data value as a tensor.
 * @return The RGB value mapped from the tensor.
 */
ColorRGB ColorMap::valueToColor(Tensor &tensor) const
{
  double eigen1, eigen2, eigen3;
  tensor.get_eigenvalues(eigen1, eigen2, eigen3);
  double magnitude = Vector(eigen1, eigen2, eigen3).length();
  return getColorMapVal(magnitude);
}

/**
 * @name valueToColor
 * @brief Takes a vector value and creates an RGB value.
 * @param The raw data value as a vector.
 * @return The RGB value mapped from the vector.
 */
ColorRGB ColorMap::valueToColor(const Vector &vector) const
{
    //TODO this is probably not implemented correctly.
   // return ColorRGB(getTransformedColor(fabs(vector.x())),getTransformedColor(fabs(vector.y())), getTransformedColor(fabs(vector.z())));
  return getColorMapVal(vector.length());
}

// This Rainbow takes into account scientific visualization recommendations.
// It tones down the yellow/cyan values so they don't appear to
// be "brighter" than the other colors. All colors "appear" to be the
// same brightness.
// Blue -> Dark Cyan -> Green -> Orange -> Red
ColorRGB detail::Rainbow::getColorMapVal(double f) const
{
  ColorRGB col;
  if (f < 0.25)
    col = ColorRGB(0., f*3., 1. - f);
  else if (0.25 <= f && f < 0.5)
    col = ColorRGB(0., f + 0.5, 1.5 - f*3.);
  else if (0.5 <= f && f < 0.75)
    col = ColorRGB(4.*f - 2., 2. - 2.*f, 0.);
  else
    col = ColorRGB(1., 2. - 2.*f, 0.);
  return col;
}

//The Old Rainbow that simply transitions from blue to red 1 color at a time.
// Blue -> Cyan -> Green -> Yellow -> Red
ColorRGB detail::OldRainbow::getColorMapVal(double f) const
{
  ColorRGB col;
  if (f < 0.25)
    col = ColorRGB(0., 4.*f, 1.);
  else if (0.25 <= f && f < 0.5)
    col = ColorRGB(0., 1., (.5 - f)*4.);
  else if (0.5 <= f && f < 0.75)
    col = ColorRGB((f - 0.5)*4., 1., 0.);
  else
    col = ColorRGB(1., (1. - f)*4., 0.);
  return col;
}

// This map is designed to appear like a heat-map, where "cooler" (lower) values
// are darker and approach black, and "hotter" (higher) values are lighter
// and approach white. In between, you have the red, orange, and yellow transitions.
ColorRGB detail::Blackbody::getColorMapVal(double f) const
{
  ColorRGB col;
  if (f < 0.333333)
    col = ColorRGB(f * 3., 0., 0.);
  else if (f < 0.6666666)
    col = ColorRGB(1., (f - 0.333333) * 3., 0.);
  else
    col = ColorRGB(1., 1., (f - 0.6666666) * 3.);
  return col;
}

// A very simple black to white map with grays in between.
ColorRGB detail::Grayscale::getColorMapVal(double f) const
{
  ColorRGB col;
  col = ColorRGB(f, f, f);
  return col;
}

// This color scheme sets a transition of color that goes
// Orange -> Black -> Lime
ColorRGB detail::OrangeBlackLime::getColorMapVal(double f) const
{
  ColorRGB col;
  if (f < 0.5)
    col = ColorRGB((0.5 - f) * 2., 0.5 - f, 0.);
  else
    col = ColorRGB(0., (f - 0.5) * 2., 0.);
  return col;
}

// This color scheme sets a transition of color that goes
// Blue -> White -> Red
ColorRGB detail::BPSeismic::getColorMapVal(double f) const
{
  ColorRGB col;
  if (f < 0.5)
    col = ColorRGB(f*2, f*2, 1);
  else
    col = ColorRGB(1, (1-f)*2, (1-f)*2);
  return col;
}

ColorRGB detail::Darkhue::getColorMapVal(double f) const
{
  ColorRGB col;
  if (f < 0.25)
    col = ColorRGB(0., 0., (f * 4.) * 0.333333);
  else if (0.25 <= f && f < 0.5)
    col = ColorRGB((f - 0.25) * 2., 0., f + ((0.5 - f) * 0.333333));
  else if (0.5 <= f && f < 0.75)
    col = ColorRGB(f + (f - 0.5), 0., f - ((f - 0.5) * 3.));
  else
    col = ColorRGB(1., (f - 0.75) * 4., (f - 0.75) * 2.6666666);
  return col;
}

static double mix(double a, double b, double c)
{
  return a * ( 1.0 - c) + b * c;
}

static ColorRGB readColorFromArray(const std::vector<ColorRGB>& v, double f)
{
  int segments = v.size() - 1;
  double m = f * segments;
  int index = int(m);
  ColorRGB c0 = v[index];
  ColorRGB c1 = v[std::min(index + 1, segments)];
  m = m - index;

  return ColorRGB(mix(c0.r(), c1.r(), m), mix(c0.g(), c1.g(), m), mix(c0.b(), c1.b(), m));
}

ColorRGB detail::PinkWhiteBlue::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v =
  {{0.800000, 0.000000, 0.600000}, {0.807843, 0.058824, 0.623529}, {0.815686, 0.125490, 0.643137}, {0.823529, 0.188235, 0.666667}, {0.827451, 0.254902, 0.686275}, {0.835294, 0.317647, 0.709804}, {0.843137, 0.384314, 0.729412}, {0.850980, 0.447059, 0.752941}, {0.858824, 0.513726, 0.772549}, {0.866667, 0.576471, 0.796078}, {0.874510, 0.643137, 0.815686}, {0.878431, 0.705882, 0.839216}, {0.886275, 0.768627, 0.858824}, {0.894118, 0.835294, 0.882353}, {1.000000, 1.000000, 1.000000}, {0.835294, 0.835294, 1.000000}, {0.768627, 0.768627, 1.000000}, {0.705882, 0.705882, 1.000000}, {0.643137, 0.643137, 1.000000}, {0.576471, 0.576471, 1.000000}, {0.513726, 0.513726, 1.000000}, {0.447059, 0.447059, 1.000000}, {0.384314, 0.384314, 1.000000}, {0.317647, 0.317647, 1.000000}, {0.254902, 0.254902, 1.000000}, {0.188235, 0.188235, 1.000000}, {0.125490, 0.125490, 1.000000}, {0.058824, 0.058824, 1.000000}, {0.000000, 0.000000, 1.000000}};

  return readColorFromArray(v, f);
}

ColorRGB detail::Lighthue::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v = {
  {0.25098, 0.25098, 0.25098}, {0.25098, 0.313725, 0.329412}, {0.25098, 0.309804, 0.360784},
  {0.25098, 0.282353, 0.435294}, {0.25098, 0.25098, 0.4}, {0.313725, 0.25098, 0.423529},
  {0.313725, 0.25098, 0.423529}, {0.360784, 0.25098, 0.431373}, {0.462745, 0.25098, 0.47451},
  {0.513725, 0.25098, 0.454902}, {0.521569, 0.25098, 0.392157}, {0.596078, 0.25098, 0.329412},
  {0.682353, 0.270588, 0.270588} , {0.701961, 0.309804, 0.25098}, {0.741176, 0.392157, 0.25098},
  {0.752941, 0.596078, 0.321569}, {0.752941, 0.701961, 0.384314}, {0.741176, 0.752941, 0.486275},
  {0.721569, 0.74902, 0.592157}};

  return readColorFromArray(v, f);
}

ColorRGB detail::Don::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v = {
  {0, 0.352941, 1}, {0.2, 0.407843, 1}, {0.403922, 0.458824, 1}, {0.65098, 0.513725, 0.960784},
  {0.709804, 0.509804, 0.847059}, {0.752941, 0.505882, 0.729412}, {0.772549, 0.501961, 0.67451},
  {0.901961, 0.494118, 0.384314}, {0.941176, 0.494118, 0.192157}, {1, 0.521569, 0}};

  return readColorFromArray(v, f);
}

ColorRGB detail::RedTint::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v = {
    {0.0784314, 0, 0}, {1, 0.921569, 0.921569}};

  return readColorFromArray(v, f);
}

ColorRGB detail::OrangeTint::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v = {
    {0.0784314, 0.0392157, 0}, {1, 0.960784, 0.921569}};

  return readColorFromArray(v, f);
}

ColorRGB detail::YellowTint::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v = {
    {0.0784314, 0.0784314, 0}, {1, 1, 0.921569}};

  return readColorFromArray(v, f);
}

//
ColorRGB detail::GreenTint::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v = {
    {0, 0.0784314, 0}, {0.921569, 1, 0.921569}};

  return readColorFromArray(v, f);
}

ColorRGB detail::CyanTint::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v = {
    {0, 0.0784314, 0.0784314}, {0.921569, 1, 1}};

  return readColorFromArray(v, f);
}

ColorRGB detail::BlueTint::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v = {
    {0, 0, 0.0784314}, {0.921569, 0.921569, 1}};

  return readColorFromArray(v, f);
}

ColorRGB detail::PurpleTint::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v = {
    {0.0392157, 0, 0.0784314}, {0.960784, 0.921569, 1}};

  return readColorFromArray(v, f);
}

ColorRGB detail::Turbo::getColorMapVal(double f) const
{
  // Copyright 2019 Google LLC.
  // SPDX-License-Identifier: Apache-2.0
  static std::vector<ColorRGB> v = {{0.18995,0.07176,0.23217},{0.19483,0.08339,0.26149},{0.19956,0.09498,0.29024},{0.20415,0.10652,0.31844},{0.20860,0.11802,0.34607},{0.21291,0.12947,0.37314},{0.21708,0.14087,0.39964},{0.22111,0.15223,0.42558},{0.22500,0.16354,0.45096},{0.22875,0.17481,0.47578},{0.23236,0.18603,0.50004},{0.23582,0.19720,0.52373},{0.23915,0.20833,0.54686},{0.24234,0.21941,0.56942},{0.24539,0.23044,0.59142},{0.24830,0.24143,0.61286},{0.25107,0.25237,0.63374},{0.25369,0.26327,0.65406},{0.25618,0.27412,0.67381},{0.25853,0.28492,0.69300},{0.26074,0.29568,0.71162},{0.26280,0.30639,0.72968},{0.26473,0.31706,0.74718},{0.26652,0.32768,0.76412},{0.26816,0.33825,0.78050},{0.26967,0.34878,0.79631},{0.27103,0.35926,0.81156},{0.27226,0.36970,0.82624},{0.27334,0.38008,0.84037},{0.27429,0.39043,0.85393},{0.27509,0.40072,0.86692},{0.27576,0.41097,0.87936},{0.27628,0.42118,0.89123},{0.27667,0.43134,0.90254},{0.27691,0.44145,0.91328},{0.27701,0.45152,0.92347},{0.27698,0.46153,0.93309},{0.27680,0.47151,0.94214},{0.27648,0.48144,0.95064},{0.27603,0.49132,0.95857},{0.27543,0.50115,0.96594},{0.27469,0.51094,0.97275},{0.27381,0.52069,0.97899},{0.27273,0.53040,0.98461},{0.27106,0.54015,0.98930},{0.26878,0.54995,0.99303},{0.26592,0.55979,0.99583},{0.26252,0.56967,0.99773},{0.25862,0.57958,0.99876},{0.25425,0.58950,0.99896},{0.24946,0.59943,0.99835},{0.24427,0.60937,0.99697},{0.23874,0.61931,0.99485},{0.23288,0.62923,0.99202},{0.22676,0.63913,0.98851},{0.22039,0.64901,0.98436},{0.21382,0.65886,0.97959},{0.20708,0.66866,0.97423},{0.20021,0.67842,0.96833},{0.19326,0.68812,0.96190},{0.18625,0.69775,0.95498},{0.17923,0.70732,0.94761},{0.17223,0.71680,0.93981},{0.16529,0.72620,0.93161},{0.15844,0.73551,0.92305},{0.15173,0.74472,0.91416},{0.14519,0.75381,0.90496},{0.13886,0.76279,0.89550},{0.13278,0.77165,0.88580},{0.12698,0.78037,0.87590},{0.12151,0.78896,0.86581},{0.11639,0.79740,0.85559},{0.11167,0.80569,0.84525},{0.10738,0.81381,0.83484},{0.10357,0.82177,0.82437},{0.10026,0.82955,0.81389},{0.09750,0.83714,0.80342},{0.09532,0.84455,0.79299},{0.09377,0.85175,0.78264},{0.09287,0.85875,0.77240},{0.09267,0.86554,0.76230},{0.09320,0.87211,0.75237},{0.09451,0.87844,0.74265},{0.09662,0.88454,0.73316},{0.09958,0.89040,0.72393},{0.10342,0.89600,0.71500},{0.10815,0.90142,0.70599},{0.11374,0.90673,0.69651},{0.12014,0.91193,0.68660},{0.12733,0.91701,0.67627},{0.13526,0.92197,0.66556},{0.14391,0.92680,0.65448},{0.15323,0.93151,0.64308},{0.16319,0.93609,0.63137},{0.17377,0.94053,0.61938},{0.18491,0.94484,0.60713},{0.19659,0.94901,0.59466},{0.20877,0.95304,0.58199},{0.22142,0.95692,0.56914},{0.23449,0.96065,0.55614},{0.24797,0.96423,0.54303},{0.26180,0.96765,0.52981},{0.27597,0.97092,0.51653},{0.29042,0.97403,0.50321},{0.30513,0.97697,0.48987},{0.32006,0.97974,0.47654},{0.33517,0.98234,0.46325},{0.35043,0.98477,0.45002},{0.36581,0.98702,0.43688},{0.38127,0.98909,0.42386},{0.39678,0.99098,0.41098},{0.41229,0.99268,0.39826},{0.42778,0.99419,0.38575},{0.44321,0.99551,0.37345},{0.45854,0.99663,0.36140},{0.47375,0.99755,0.34963},{0.48879,0.99828,0.33816},{0.50362,0.99879,0.32701},{0.51822,0.99910,0.31622},{0.53255,0.99919,0.30581},{0.54658,0.99907,0.29581},{0.56026,0.99873,0.28623},{0.57357,0.99817,0.27712},{0.58646,0.99739,0.26849},{0.59891,0.99638,0.26038},{0.61088,0.99514,0.25280},{0.62233,0.99366,0.24579},{0.63323,0.99195,0.23937},{0.64362,0.98999,0.23356},{0.65394,0.98775,0.22835},{0.66428,0.98524,0.22370},{0.67462,0.98246,0.21960},{0.68494,0.97941,0.21602},{0.69525,0.97610,0.21294},{0.70553,0.97255,0.21032},{0.71577,0.96875,0.20815},{0.72596,0.96470,0.20640},{0.73610,0.96043,0.20504},{0.74617,0.95593,0.20406},{0.75617,0.95121,0.20343},{0.76608,0.94627,0.20311},{0.77591,0.94113,0.20310},{0.78563,0.93579,0.20336},{0.79524,0.93025,0.20386},{0.80473,0.92452,0.20459},{0.81410,0.91861,0.20552},{0.82333,0.91253,0.20663},{0.83241,0.90627,0.20788},{0.84133,0.89986,0.20926},{0.85010,0.89328,0.21074},{0.85868,0.88655,0.21230},{0.86709,0.87968,0.21391},{0.87530,0.87267,0.21555},{0.88331,0.86553,0.21719},{0.89112,0.85826,0.21880},{0.89870,0.85087,0.22038},{0.90605,0.84337,0.22188},{0.91317,0.83576,0.22328},{0.92004,0.82806,0.22456},{0.92666,0.82025,0.22570},{0.93301,0.81236,0.22667},{0.93909,0.80439,0.22744},{0.94489,0.79634,0.22800},{0.95039,0.78823,0.22831},{0.95560,0.78005,0.22836},{0.96049,0.77181,0.22811},{0.96507,0.76352,0.22754},{0.96931,0.75519,0.22663},{0.97323,0.74682,0.22536},{0.97679,0.73842,0.22369},{0.98000,0.73000,0.22161},{0.98289,0.72140,0.21918},{0.98549,0.71250,0.21650},{0.98781,0.70330,0.21358},{0.98986,0.69382,0.21043},{0.99163,0.68408,0.20706},{0.99314,0.67408,0.20348},{0.99438,0.66386,0.19971},{0.99535,0.65341,0.19577},{0.99607,0.64277,0.19165},{0.99654,0.63193,0.18738},{0.99675,0.62093,0.18297},{0.99672,0.60977,0.17842},{0.99644,0.59846,0.17376},{0.99593,0.58703,0.16899},{0.99517,0.57549,0.16412},{0.99419,0.56386,0.15918},{0.99297,0.55214,0.15417},{0.99153,0.54036,0.14910},{0.98987,0.52854,0.14398},{0.98799,0.51667,0.13883},{0.98590,0.50479,0.13367},{0.98360,0.49291,0.12849},{0.98108,0.48104,0.12332},{0.97837,0.46920,0.11817},{0.97545,0.45740,0.11305},{0.97234,0.44565,0.10797},{0.96904,0.43399,0.10294},{0.96555,0.42241,0.09798},{0.96187,0.41093,0.09310},{0.95801,0.39958,0.08831},{0.95398,0.38836,0.08362},{0.94977,0.37729,0.07905},{0.94538,0.36638,0.07461},{0.94084,0.35566,0.07031},{0.93612,0.34513,0.06616},{0.93125,0.33482,0.06218},{0.92623,0.32473,0.05837},{0.92105,0.31489,0.05475},{0.91572,0.30530,0.05134},{0.91024,0.29599,0.04814},{0.90463,0.28696,0.04516},{0.89888,0.27824,0.04243},{0.89298,0.26981,0.03993},{0.88691,0.26152,0.03753},{0.88066,0.25334,0.03521},{0.87422,0.24526,0.03297},{0.86760,0.23730,0.03082},{0.86079,0.22945,0.02875},{0.85380,0.22170,0.02677},{0.84662,0.21407,0.02487},{0.83926,0.20654,0.02305},{0.83172,0.19912,0.02131},{0.82399,0.19182,0.01966},{0.81608,0.18462,0.01809},{0.80799,0.17753,0.01660},{0.79971,0.17055,0.01520},{0.79125,0.16368,0.01387},{0.78260,0.15693,0.01264},{0.77377,0.15028,0.01148},{0.76476,0.14374,0.01041},{0.75556,0.13731,0.00942},{0.74617,0.13098,0.00851},{0.73661,0.12477,0.00769},{0.72686,0.11867,0.00695},{0.71692,0.11268,0.00629},{0.70680,0.10680,0.00571},{0.69650,0.10102,0.00522},{0.68602,0.09536,0.00481},{0.67535,0.08980,0.00449},{0.66449,0.08436,0.00424},{0.65345,0.07902,0.00408},{0.64223,0.07380,0.00401},{0.63082,0.06868,0.00401},{0.61923,0.06367,0.00410},{0.60746,0.05878,0.00427},{0.59550,0.05399,0.00453},{0.58336,0.04931,0.00486},{0.57103,0.04474,0.00529},{0.55852,0.04028,0.00579},{0.54583,0.03593,0.00638},{0.53295,0.03169,0.00705},{0.51989,0.02756,0.00780},{0.50664,0.02354,0.00863},{0.49321,0.01963,0.00955},{0.47960,0.01583,0.01055}};

  return readColorFromArray(v, f);
}

ColorRGB detail::Magma::getColorMapVal(double f) const
{
  //From matplotlib. License found here: https://github.com/matplotlib/matplotlib/blob/master/LICENSE/LICENSE
  static std::vector<ColorRGB> v =
  {{0.001462, 0.000466, 0.013866}, {0.002258, 0.001295, 0.018331}, {0.003279, 0.002305, 0.023708}, {0.004512, 0.003490, 0.029965}, {0.005950, 0.004843, 0.037130}, {0.007588, 0.006356, 0.044973}, {0.009426, 0.008022, 0.052844}, {0.011465, 0.009828, 0.060750}, {0.013708, 0.011771, 0.068667}, {0.016156, 0.013840, 0.076603}, {0.018815, 0.016026, 0.084584}, {0.021692, 0.018320, 0.092610}, {0.024792, 0.020715, 0.100676}, {0.028123, 0.023201, 0.108787}, {0.031696, 0.025765, 0.116965}, {0.035520, 0.028397, 0.125209}, {0.039608, 0.031090, 0.133515}, {0.043830, 0.033830, 0.141886}, {0.048062, 0.036607, 0.150327}, {0.052320, 0.039407, 0.158841}, {0.056615, 0.042160, 0.167446}, {0.060949, 0.044794, 0.176129}, {0.065330, 0.047318, 0.184892}, {0.069764, 0.049726, 0.193735}, {0.074257, 0.052017, 0.202660}, {0.078815, 0.054184, 0.211667}, {0.083446, 0.056225, 0.220755}, {0.088155, 0.058133, 0.229922}, {0.092949, 0.059904, 0.239164}, {0.097833, 0.061531, 0.248477}, {0.102815, 0.063010, 0.257854}, {0.107899, 0.064335, 0.267289}, {0.113094, 0.065492, 0.276784}, {0.118405, 0.066479, 0.286321}, {0.123833, 0.067295, 0.295879}, {0.129380, 0.067935, 0.305443}, {0.135053, 0.068391, 0.315000}, {0.140858, 0.068654, 0.324538}, {0.146785, 0.068738, 0.334011}, {0.152839, 0.068637, 0.343404}, {0.159018, 0.068354, 0.352688}, {0.165308, 0.067911, 0.361816}, {0.171713, 0.067305, 0.370771}, {0.178212, 0.066576, 0.379497}, {0.184801, 0.065732, 0.387973}, {0.191460, 0.064818, 0.396152}, {0.198177, 0.063862, 0.404009}, {0.204935, 0.062907, 0.411514}, {0.211718, 0.061992, 0.418647}, {0.218512, 0.061158, 0.425392}, {0.225302, 0.060445, 0.431742}, {0.232077, 0.059889, 0.437695}, {0.238826, 0.059517, 0.443256}, {0.245543, 0.059352, 0.448436}, {0.252220, 0.059415, 0.453248}, {0.258857, 0.059706, 0.457710}, {0.265447, 0.060237, 0.461840}, {0.271994, 0.060994, 0.465660}, {0.278493, 0.061978, 0.469190}, {0.284951, 0.063168, 0.472451}, {0.291366, 0.064553, 0.475462}, {0.297740, 0.066117, 0.478243}, {0.304081, 0.067835, 0.480812}, {0.310382, 0.069702, 0.483186}, {0.316654, 0.071690, 0.485380}, {0.322899, 0.073782, 0.487408}, {0.329114, 0.075972, 0.489287}, {0.335308, 0.078236, 0.491024}, {0.341482, 0.080564, 0.492631}, {0.347636, 0.082946, 0.494121}, {0.353773, 0.085373, 0.495501}, {0.359898, 0.087831, 0.496778}, {0.366012, 0.090314, 0.497960}, {0.372116, 0.092816, 0.499053}, {0.378211, 0.095332, 0.500067}, {0.384299, 0.097855, 0.501002}, {0.390384, 0.100379, 0.501864}, {0.396467, 0.102902, 0.502658}, {0.402548, 0.105420, 0.503386}, {0.408629, 0.107930, 0.504052}, {0.414709, 0.110431, 0.504662}, {0.420791, 0.112920, 0.505215}, {0.426877, 0.115395, 0.505714}, {0.432967, 0.117855, 0.506160}, {0.439062, 0.120298, 0.506555}, {0.445163, 0.122724, 0.506901}, {0.451271, 0.125132, 0.507198}, {0.457386, 0.127522, 0.507448}, {0.463508, 0.129893, 0.507652}, {0.469640, 0.132245, 0.507809}, {0.475780, 0.134577, 0.507921}, {0.481929, 0.136891, 0.507989}, {0.488088, 0.139186, 0.508011}, {0.494258, 0.141462, 0.507988}, {0.500438, 0.143719, 0.507920}, {0.506629, 0.145958, 0.507806}, {0.512831, 0.148179, 0.507648}, {0.519045, 0.150383, 0.507443}, {0.525270, 0.152569, 0.507192}, {0.531507, 0.154739, 0.506895}, {0.537755, 0.156894, 0.506551}, {0.544015, 0.159033, 0.506159}, {0.550287, 0.161158, 0.505719}, {0.556571, 0.163269, 0.505230}, {0.562866, 0.165368, 0.504692}, {0.569172, 0.167454, 0.504105}, {0.575490, 0.169530, 0.503466}, {0.581819, 0.171596, 0.502777}, {0.588158, 0.173652, 0.502035}, {0.594508, 0.175701, 0.501241}, {0.600868, 0.177743, 0.500394}, {0.607238, 0.179779, 0.499492}, {0.613617, 0.181811, 0.498536}, {0.620005, 0.183840, 0.497524}, {0.626401, 0.185867, 0.496456}, {0.632805, 0.187893, 0.495332}, {0.639216, 0.189921, 0.494150}, {0.645633, 0.191952, 0.492910}, {0.652056, 0.193986, 0.491611}, {0.658483, 0.196027, 0.490253}, {0.664915, 0.198075, 0.488836}, {0.671349, 0.200133, 0.487358}, {0.677786, 0.202203, 0.485819}, {0.684224, 0.204286, 0.484219}, {0.690661, 0.206384, 0.482558}, {0.697098, 0.208501, 0.480835}, {0.703532, 0.210638, 0.479049}, {0.709962, 0.212797, 0.477201}, {0.716387, 0.214982, 0.475290}, {0.722805, 0.217194, 0.473316}, {0.729216, 0.219437, 0.471279}, {0.735616, 0.221713, 0.469180}, {0.742004, 0.224025, 0.467018}, {0.748378, 0.226377, 0.464794}, {0.754737, 0.228772, 0.462509}, {0.761077, 0.231214, 0.460162}, {0.767398, 0.233705, 0.457755}, {0.773695, 0.236249, 0.455289}, {0.779968, 0.238851, 0.452765}, {0.786212, 0.241514, 0.450184}, {0.792427, 0.244242, 0.447543}, {0.798608, 0.247040, 0.444848}, {0.804752, 0.249911, 0.442102}, {0.810855, 0.252861, 0.439305}, {0.816914, 0.255895, 0.436461}, {0.822926, 0.259016, 0.433573}, {0.828886, 0.262229, 0.430644}, {0.834791, 0.265540, 0.427671}, {0.840636, 0.268953, 0.424666}, {0.846416, 0.272473, 0.421631}, {0.852126, 0.276106, 0.418573}, {0.857763, 0.279857, 0.415496}, {0.863320, 0.283729, 0.412403}, {0.868793, 0.287728, 0.409303}, {0.874176, 0.291859, 0.406205}, {0.879464, 0.296125, 0.403118}, {0.884651, 0.300530, 0.400047}, {0.889731, 0.305079, 0.397002}, {0.894700, 0.309773, 0.393995}, {0.899552, 0.314616, 0.391037}, {0.904281, 0.319610, 0.388137}, {0.908884, 0.324755, 0.385308}, {0.913354, 0.330052, 0.382563}, {0.917689, 0.335500, 0.379915}, {0.921884, 0.341098, 0.377376}, {0.925937, 0.346844, 0.374959}, {0.929845, 0.352734, 0.372677}, {0.933606, 0.358764, 0.370541}, {0.937221, 0.364929, 0.368567}, {0.940687, 0.371224, 0.366762}, {0.944006, 0.377643, 0.365136}, {0.947180, 0.384178, 0.363701}, {0.950210, 0.390820, 0.362468}, {0.953099, 0.397563, 0.361438}, {0.955849, 0.404400, 0.360619}, {0.958464, 0.411324, 0.360014}, {0.960949, 0.418323, 0.359630}, {0.963310, 0.425390, 0.359469}, {0.965549, 0.432519, 0.359529}, {0.967671, 0.439703, 0.359810}, {0.969680, 0.446936, 0.360311}, {0.971582, 0.454210, 0.361030}, {0.973381, 0.461520, 0.361965}, {0.975082, 0.468861, 0.363111}, {0.976690, 0.476226, 0.364466}, {0.978210, 0.483612, 0.366025}, {0.979645, 0.491014, 0.367783}, {0.981000, 0.498428, 0.369734}, {0.982279, 0.505851, 0.371874}, {0.983485, 0.513280, 0.374198}, {0.984622, 0.520713, 0.376698}, {0.985693, 0.528148, 0.379371}, {0.986700, 0.535582, 0.382210}, {0.987646, 0.543015, 0.385210}, {0.988533, 0.550446, 0.388365}, {0.989363, 0.557873, 0.391671}, {0.990138, 0.565296, 0.395122}, {0.990871, 0.572706, 0.398714}, {0.991558, 0.580107, 0.402441}, {0.992196, 0.587502, 0.406299}, {0.992785, 0.594891, 0.410283}, {0.993326, 0.602275, 0.414390}, {0.993834, 0.609644, 0.418613}, {0.994309, 0.616999, 0.422950}, {0.994738, 0.624350, 0.427397}, {0.995122, 0.631696, 0.431951}, {0.995480, 0.639027, 0.436607}, {0.995810, 0.646344, 0.441361}, {0.996096, 0.653659, 0.446213}, {0.996341, 0.660969, 0.451160}, {0.996580, 0.668256, 0.456192}, {0.996775, 0.675541, 0.461314}, {0.996925, 0.682828, 0.466526}, {0.997077, 0.690088, 0.471811}, {0.997186, 0.697349, 0.477182}, {0.997254, 0.704611, 0.482635}, {0.997325, 0.711848, 0.488154}, {0.997351, 0.719089, 0.493755}, {0.997351, 0.726324, 0.499428}, {0.997341, 0.733545, 0.505167}, {0.997285, 0.740772, 0.510983}, {0.997228, 0.747981, 0.516859}, {0.997138, 0.755190, 0.522806}, {0.997019, 0.762398, 0.528821}, {0.996898, 0.769591, 0.534892}, {0.996727, 0.776795, 0.541039}, {0.996571, 0.783977, 0.547233}, {0.996369, 0.791167, 0.553499}, {0.996162, 0.798348, 0.559820}, {0.995932, 0.805527, 0.566202}, {0.995680, 0.812706, 0.572645}, {0.995424, 0.819875, 0.579140}, {0.995131, 0.827052, 0.585701}, {0.994851, 0.834213, 0.592307}, {0.994524, 0.841387, 0.598983}, {0.994222, 0.848540, 0.605696}, {0.993866, 0.855711, 0.612482}, {0.993545, 0.862859, 0.619299}, {0.993170, 0.870024, 0.626189}, {0.992831, 0.877168, 0.633109}, {0.992440, 0.884330, 0.640099}, {0.992089, 0.891470, 0.647116}, {0.991688, 0.898627, 0.654202}, {0.991332, 0.905763, 0.661309}, {0.990930, 0.912915, 0.668481}, {0.990570, 0.920049, 0.675675}, {0.990175, 0.927196, 0.682926}, {0.989815, 0.934329, 0.690198}, {0.989434, 0.941470, 0.697519}, {0.989077, 0.948604, 0.704863}, {0.988717, 0.955742, 0.712242}, {0.988367, 0.962878, 0.719649}, {0.988033, 0.970012, 0.727077}, {0.987691, 0.977154, 0.734536}, {0.987387, 0.984288, 0.742002}, {0.987053, 0.991438, 0.749504}};

  return readColorFromArray(v, f);
}

ColorRGB detail::Inferno::getColorMapVal(double f) const
{
  //From matplotlib. License found here: https://github.com/matplotlib/matplotlib/blob/master/LICENSE/LICENSE
  static std::vector<ColorRGB> v =
  {{0.001462, 0.000466, 0.013866}, {0.002267, 0.001270, 0.018570}, {0.003299, 0.002249, 0.024239}, {0.004547, 0.003392, 0.030909}, {0.006006, 0.004692, 0.038558}, {0.007676, 0.006136, 0.046836}, {0.009561, 0.007713, 0.055143}, {0.011663, 0.009417, 0.063460}, {0.013995, 0.011225, 0.071862}, {0.016561, 0.013136, 0.080282}, {0.019373, 0.015133, 0.088767}, {0.022447, 0.017199, 0.097327}, {0.025793, 0.019331, 0.105930}, {0.029432, 0.021503, 0.114621}, {0.033385, 0.023702, 0.123397}, {0.037668, 0.025921, 0.132232}, {0.042253, 0.028139, 0.141141}, {0.046915, 0.030324, 0.150164}, {0.051644, 0.032474, 0.159254}, {0.056449, 0.034569, 0.168414}, {0.061340, 0.036590, 0.177642}, {0.066331, 0.038504, 0.186962}, {0.071429, 0.040294, 0.196354}, {0.076637, 0.041905, 0.205799}, {0.081962, 0.043328, 0.215289}, {0.087411, 0.044556, 0.224813}, {0.092990, 0.045583, 0.234358}, {0.098702, 0.046402, 0.243904}, {0.104551, 0.047008, 0.253430}, {0.110536, 0.047399, 0.262912}, {0.116656, 0.047574, 0.272321}, {0.122908, 0.047536, 0.281624}, {0.129285, 0.047293, 0.290788}, {0.135778, 0.046856, 0.299776}, {0.142378, 0.046242, 0.308553}, {0.149073, 0.045468, 0.317085}, {0.155850, 0.044559, 0.325338}, {0.162689, 0.043554, 0.333277}, {0.169575, 0.042489, 0.340874}, {0.176493, 0.041402, 0.348111}, {0.183429, 0.040329, 0.354971}, {0.190367, 0.039309, 0.361447}, {0.197297, 0.038400, 0.367535}, {0.204209, 0.037632, 0.373238}, {0.211095, 0.037030, 0.378563}, {0.217949, 0.036615, 0.383522}, {0.224763, 0.036405, 0.388129}, {0.231538, 0.036405, 0.392400}, {0.238273, 0.036621, 0.396353}, {0.244967, 0.037055, 0.400007}, {0.251620, 0.037705, 0.403378}, {0.258234, 0.038571, 0.406485}, {0.264810, 0.039647, 0.409345}, {0.271347, 0.040922, 0.411976}, {0.277850, 0.042353, 0.414392}, {0.284321, 0.043933, 0.416608}, {0.290763, 0.045644, 0.418637}, {0.297178, 0.047470, 0.420491}, {0.303568, 0.049396, 0.422182}, {0.309935, 0.051407, 0.423721}, {0.316282, 0.053490, 0.425116}, {0.322610, 0.055634, 0.426377}, {0.328921, 0.057827, 0.427511}, {0.335217, 0.060060, 0.428524}, {0.341500, 0.062325, 0.429425}, {0.347771, 0.064616, 0.430217}, {0.354032, 0.066925, 0.430906}, {0.360284, 0.069247, 0.431497}, {0.366529, 0.071579, 0.431994}, {0.372768, 0.073915, 0.432400}, {0.379001, 0.076253, 0.432719}, {0.385228, 0.078591, 0.432955}, {0.391453, 0.080927, 0.433109}, {0.397674, 0.083257, 0.433183}, {0.403894, 0.085580, 0.433179}, {0.410113, 0.087896, 0.433098}, {0.416331, 0.090203, 0.432943}, {0.422549, 0.092501, 0.432714}, {0.428768, 0.094790, 0.432412}, {0.434987, 0.097069, 0.432039}, {0.441207, 0.099338, 0.431594}, {0.447428, 0.101597, 0.431080}, {0.453651, 0.103848, 0.430498}, {0.459875, 0.106089, 0.429846}, {0.466100, 0.108322, 0.429125}, {0.472328, 0.110547, 0.428334}, {0.478558, 0.112764, 0.427475}, {0.484789, 0.114974, 0.426548}, {0.491022, 0.117179, 0.425552}, {0.497257, 0.119379, 0.424488}, {0.503493, 0.121575, 0.423356}, {0.509730, 0.123769, 0.422156}, {0.515967, 0.125960, 0.420887}, {0.522206, 0.128150, 0.419549}, {0.528444, 0.130341, 0.418142}, {0.534683, 0.132534, 0.416667}, {0.540920, 0.134729, 0.415123}, {0.547157, 0.136929, 0.413511}, {0.553392, 0.139134, 0.411829}, {0.559624, 0.141346, 0.410078}, {0.565854, 0.143567, 0.408258}, {0.572081, 0.145797, 0.406369}, {0.578304, 0.148039, 0.404411}, {0.584521, 0.150294, 0.402385}, {0.590734, 0.152563, 0.400290}, {0.596940, 0.154848, 0.398125}, {0.603139, 0.157151, 0.395891}, {0.609330, 0.159474, 0.393589}, {0.615513, 0.161817, 0.391219}, {0.621685, 0.164184, 0.388781}, {0.627847, 0.166575, 0.386276}, {0.633998, 0.168992, 0.383704}, {0.640135, 0.171438, 0.381065}, {0.646260, 0.173914, 0.378359}, {0.652369, 0.176421, 0.375586}, {0.658463, 0.178962, 0.372748}, {0.664540, 0.181539, 0.369846}, {0.670599, 0.184153, 0.366879}, {0.676638, 0.186807, 0.363849}, {0.682656, 0.189501, 0.360757}, {0.688653, 0.192239, 0.357603}, {0.694627, 0.195021, 0.354388}, {0.700576, 0.197851, 0.351113}, {0.706500, 0.200728, 0.347777}, {0.712396, 0.203656, 0.344383}, {0.718264, 0.206636, 0.340931}, {0.724103, 0.209670, 0.337424}, {0.729909, 0.212759, 0.333861}, {0.735683, 0.215906, 0.330245}, {0.741423, 0.219112, 0.326576}, {0.747127, 0.222378, 0.322856}, {0.752794, 0.225706, 0.319085}, {0.758422, 0.229097, 0.315266}, {0.764010, 0.232554, 0.311399}, {0.769556, 0.236077, 0.307485}, {0.775059, 0.239667, 0.303526}, {0.780517, 0.243327, 0.299523}, {0.785929, 0.247056, 0.295477}, {0.791293, 0.250856, 0.291390}, {0.796607, 0.254728, 0.287264}, {0.801871, 0.258674, 0.283099}, {0.807082, 0.262692, 0.278898}, {0.812239, 0.266786, 0.274661}, {0.817341, 0.270954, 0.270390}, {0.822386, 0.275197, 0.266085}, {0.827372, 0.279517, 0.261750}, {0.832299, 0.283913, 0.257383}, {0.837165, 0.288385, 0.252988}, {0.841969, 0.292933, 0.248564}, {0.846709, 0.297559, 0.244113}, {0.851384, 0.302260, 0.239636}, {0.855992, 0.307038, 0.235133}, {0.860533, 0.311892, 0.230606}, {0.865006, 0.316822, 0.226055}, {0.869409, 0.321827, 0.221482}, {0.873741, 0.326906, 0.216886}, {0.878001, 0.332060, 0.212268}, {0.882188, 0.337287, 0.207628}, {0.886302, 0.342586, 0.202968}, {0.890341, 0.347957, 0.198286}, {0.894305, 0.353399, 0.193584}, {0.898192, 0.358911, 0.188860}, {0.902003, 0.364492, 0.184116}, {0.905735, 0.370140, 0.179350}, {0.909390, 0.375856, 0.174563}, {0.912966, 0.381636, 0.169755}, {0.916462, 0.387481, 0.164924}, {0.919879, 0.393389, 0.160070}, {0.923215, 0.399359, 0.155193}, {0.926470, 0.405389, 0.150292}, {0.929644, 0.411479, 0.145367}, {0.932737, 0.417627, 0.140417}, {0.935747, 0.423831, 0.135440}, {0.938675, 0.430091, 0.130438}, {0.941521, 0.436405, 0.125409}, {0.944285, 0.442772, 0.120354}, {0.946965, 0.449191, 0.115272}, {0.949562, 0.455660, 0.110164}, {0.952075, 0.462178, 0.105031}, {0.954506, 0.468744, 0.099874}, {0.956852, 0.475356, 0.094695}, {0.959114, 0.482014, 0.089499}, {0.961293, 0.488716, 0.084289}, {0.963387, 0.495462, 0.079073}, {0.965397, 0.502249, 0.073859}, {0.967322, 0.509078, 0.068659}, {0.969163, 0.515946, 0.063488}, {0.970919, 0.522853, 0.058367}, {0.972590, 0.529798, 0.053324}, {0.974176, 0.536780, 0.048392}, {0.975677, 0.543798, 0.043618}, {0.977092, 0.550850, 0.039050}, {0.978422, 0.557937, 0.034931}, {0.979666, 0.565057, 0.031409}, {0.980824, 0.572209, 0.028508}, {0.981895, 0.579392, 0.026250}, {0.982881, 0.586606, 0.024661}, {0.983779, 0.593849, 0.023770}, {0.984591, 0.601122, 0.023606}, {0.985315, 0.608422, 0.024202}, {0.985952, 0.615750, 0.025592}, {0.986502, 0.623105, 0.027814}, {0.986964, 0.630485, 0.030908}, {0.987337, 0.637890, 0.034916}, {0.987622, 0.645320, 0.039886}, {0.987819, 0.652773, 0.045581}, {0.987926, 0.660250, 0.051750}, {0.987945, 0.667748, 0.058329}, {0.987874, 0.675267, 0.065257}, {0.987714, 0.682807, 0.072489}, {0.987464, 0.690366, 0.079990}, {0.987124, 0.697944, 0.087731}, {0.986694, 0.705540, 0.095694}, {0.986175, 0.713153, 0.103863}, {0.985566, 0.720782, 0.112229}, {0.984865, 0.728427, 0.120785}, {0.984075, 0.736087, 0.129527}, {0.983196, 0.743758, 0.138453}, {0.982228, 0.751442, 0.147565}, {0.981173, 0.759135, 0.156863}, {0.980032, 0.766837, 0.166353}, {0.978806, 0.774545, 0.176037}, {0.977497, 0.782258, 0.185923}, {0.976108, 0.789974, 0.196018}, {0.974638, 0.797692, 0.206332}, {0.973088, 0.805409, 0.216877}, {0.971468, 0.813122, 0.227658}, {0.969783, 0.820825, 0.238686}, {0.968041, 0.828515, 0.249972}, {0.966243, 0.836191, 0.261534}, {0.964394, 0.843848, 0.273391}, {0.962517, 0.851476, 0.285546}, {0.960626, 0.859069, 0.298010}, {0.958720, 0.866624, 0.310820}, {0.956834, 0.874129, 0.323974}, {0.954997, 0.881569, 0.337475}, {0.953215, 0.888942, 0.351369}, {0.951546, 0.896226, 0.365627}, {0.950018, 0.903409, 0.380271}, {0.948683, 0.910473, 0.395289}, {0.947594, 0.917399, 0.410665}, {0.946809, 0.924168, 0.426373}, {0.946392, 0.930761, 0.442367}, {0.946403, 0.937159, 0.458592}, {0.946903, 0.943348, 0.474970}, {0.947937, 0.949318, 0.491426}, {0.949545, 0.955063, 0.507860}, {0.951740, 0.960587, 0.524203}, {0.954529, 0.965896, 0.540361}, {0.957896, 0.971003, 0.556275}, {0.961812, 0.975924, 0.571925}, {0.966249, 0.980678, 0.587206}, {0.971162, 0.985282, 0.602154}, {0.976511, 0.989753, 0.616760}, {0.982257, 0.994109, 0.631017}, {0.988362, 0.998364, 0.644924}};

  return readColorFromArray(v, f);
}

ColorRGB detail::Plasma::getColorMapVal(double f) const
{
  //From matplotlib. License found here: https://github.com/matplotlib/matplotlib/blob/master/LICENSE/LICENSE
  static std::vector<ColorRGB> v =
  {{0.050383, 0.029803, 0.527975}, {0.063536, 0.028426, 0.533124}, {0.075353, 0.027206, 0.538007}, {0.086222, 0.026125, 0.542658}, {0.096379, 0.025165, 0.547103}, {0.105980, 0.024309, 0.551368}, {0.115124, 0.023556, 0.555468}, {0.123903, 0.022878, 0.559423}, {0.132381, 0.022258, 0.563250}, {0.140603, 0.021687, 0.566959}, {0.148607, 0.021154, 0.570562}, {0.156421, 0.020651, 0.574065}, {0.164070, 0.020171, 0.577478}, {0.171574, 0.019706, 0.580806}, {0.178950, 0.019252, 0.584054}, {0.186213, 0.018803, 0.587228}, {0.193374, 0.018354, 0.590330}, {0.200445, 0.017902, 0.593364}, {0.207435, 0.017442, 0.596333}, {0.214350, 0.016973, 0.599239}, {0.221197, 0.016497, 0.602083}, {0.227983, 0.016007, 0.604867}, {0.234715, 0.015502, 0.607592}, {0.241396, 0.014979, 0.610259}, {0.248032, 0.014439, 0.612868}, {0.254627, 0.013882, 0.615419}, {0.261183, 0.013308, 0.617911}, {0.267703, 0.012716, 0.620346}, {0.274191, 0.012109, 0.622722}, {0.280648, 0.011488, 0.625038}, {0.287076, 0.010855, 0.627295}, {0.293478, 0.010213, 0.629490}, {0.299855, 0.009561, 0.631624}, {0.306210, 0.008902, 0.633694}, {0.312543, 0.008239, 0.635700}, {0.318856, 0.007576, 0.637640}, {0.325150, 0.006915, 0.639512}, {0.331426, 0.006261, 0.641316}, {0.337683, 0.005618, 0.643049}, {0.343925, 0.004991, 0.644710}, {0.350150, 0.004382, 0.646298}, {0.356359, 0.003798, 0.647810}, {0.362553, 0.003243, 0.649245}, {0.368733, 0.002724, 0.650601}, {0.374897, 0.002245, 0.651876}, {0.381047, 0.001814, 0.653068}, {0.387183, 0.001434, 0.654177}, {0.393304, 0.001114, 0.655199}, {0.399411, 0.000859, 0.656133}, {0.405503, 0.000678, 0.656977}, {0.411580, 0.000577, 0.657730}, {0.417642, 0.000564, 0.658390}, {0.423689, 0.000646, 0.658956}, {0.429719, 0.000831, 0.659425}, {0.435734, 0.001127, 0.659797}, {0.441732, 0.001540, 0.660069}, {0.447714, 0.002080, 0.660240}, {0.453677, 0.002755, 0.660310}, {0.459623, 0.003574, 0.660277}, {0.465550, 0.004545, 0.660139}, {0.471457, 0.005678, 0.659897}, {0.477344, 0.006980, 0.659549}, {0.483210, 0.008460, 0.659095}, {0.489055, 0.010127, 0.658534}, {0.494877, 0.011990, 0.657865}, {0.500678, 0.014055, 0.657088}, {0.506454, 0.016333, 0.656202}, {0.512206, 0.018833, 0.655209}, {0.517933, 0.021563, 0.654109}, {0.523633, 0.024532, 0.652901}, {0.529306, 0.027747, 0.651586}, {0.534952, 0.031217, 0.650165}, {0.540570, 0.034950, 0.648640}, {0.546157, 0.038954, 0.647010}, {0.551715, 0.043136, 0.645277}, {0.557243, 0.047331, 0.643443}, {0.562738, 0.051545, 0.641509}, {0.568201, 0.055778, 0.639477}, {0.573632, 0.060028, 0.637349}, {0.579029, 0.064296, 0.635126}, {0.584391, 0.068579, 0.632812}, {0.589719, 0.072878, 0.630408}, {0.595011, 0.077190, 0.627917}, {0.600266, 0.081516, 0.625342}, {0.605485, 0.085854, 0.622686}, {0.610667, 0.090204, 0.619951}, {0.615812, 0.094564, 0.617140}, {0.620919, 0.098934, 0.614257}, {0.625987, 0.103312, 0.611305}, {0.631017, 0.107699, 0.608287}, {0.636008, 0.112092, 0.605205}, {0.640959, 0.116492, 0.602065}, {0.645872, 0.120898, 0.598867}, {0.650746, 0.125309, 0.595617}, {0.655580, 0.129725, 0.592317}, {0.660374, 0.134144, 0.588971}, {0.665129, 0.138566, 0.585582}, {0.669845, 0.142992, 0.582154}, {0.674522, 0.147419, 0.578688}, {0.679160, 0.151848, 0.575189}, {0.683758, 0.156278, 0.571660}, {0.688318, 0.160709, 0.568103}, {0.692840, 0.165141, 0.564522}, {0.697324, 0.169573, 0.560919}, {0.701769, 0.174005, 0.557296}, {0.706178, 0.178437, 0.553657}, {0.710549, 0.182868, 0.550004}, {0.714883, 0.187299, 0.546338}, {0.719181, 0.191729, 0.542663}, {0.723444, 0.196158, 0.538981}, {0.727670, 0.200586, 0.535293}, {0.731862, 0.205013, 0.531601}, {0.736019, 0.209439, 0.527908}, {0.740143, 0.213864, 0.524216}, {0.744232, 0.218288, 0.520524}, {0.748289, 0.222711, 0.516834}, {0.752312, 0.227133, 0.513149}, {0.756304, 0.231555, 0.509468}, {0.760264, 0.235976, 0.505794}, {0.764193, 0.240396, 0.502126}, {0.768090, 0.244817, 0.498465}, {0.771958, 0.249237, 0.494813}, {0.775796, 0.253658, 0.491171}, {0.779604, 0.258078, 0.487539}, {0.783383, 0.262500, 0.483918}, {0.787133, 0.266922, 0.480307}, {0.790855, 0.271345, 0.476706}, {0.794549, 0.275770, 0.473117}, {0.798216, 0.280197, 0.469538}, {0.801855, 0.284626, 0.465971}, {0.805467, 0.289057, 0.462415}, {0.809052, 0.293491, 0.458870}, {0.812612, 0.297928, 0.455338}, {0.816144, 0.302368, 0.451816}, {0.819651, 0.306812, 0.448306}, {0.823132, 0.311261, 0.444806}, {0.826588, 0.315714, 0.441316}, {0.830018, 0.320172, 0.437836}, {0.833422, 0.324635, 0.434366}, {0.836801, 0.329105, 0.430905}, {0.840155, 0.333580, 0.427455}, {0.843484, 0.338062, 0.424013}, {0.846788, 0.342551, 0.420579}, {0.850066, 0.347048, 0.417153}, {0.853319, 0.351553, 0.413734}, {0.856547, 0.356066, 0.410322}, {0.859750, 0.360588, 0.406917}, {0.862927, 0.365119, 0.403519}, {0.866078, 0.369660, 0.400126}, {0.869203, 0.374212, 0.396738}, {0.872303, 0.378774, 0.393355}, {0.875376, 0.383347, 0.389976}, {0.878423, 0.387932, 0.386600}, {0.881443, 0.392529, 0.383229}, {0.884436, 0.397139, 0.379860}, {0.887402, 0.401762, 0.376494}, {0.890340, 0.406398, 0.373130}, {0.893250, 0.411048, 0.369768}, {0.896131, 0.415712, 0.366407}, {0.898984, 0.420392, 0.363047}, {0.901807, 0.425087, 0.359688}, {0.904601, 0.429797, 0.356329}, {0.907365, 0.434524, 0.352970}, {0.910098, 0.439268, 0.349610}, {0.912800, 0.444029, 0.346251}, {0.915471, 0.448807, 0.342890}, {0.918109, 0.453603, 0.339529}, {0.920714, 0.458417, 0.336166}, {0.923287, 0.463251, 0.332801}, {0.925825, 0.468103, 0.329435}, {0.928329, 0.472975, 0.326067}, {0.930798, 0.477867, 0.322697}, {0.933232, 0.482780, 0.319325}, {0.935630, 0.487712, 0.315952}, {0.937990, 0.492667, 0.312575}, {0.940313, 0.497642, 0.309197}, {0.942598, 0.502639, 0.305816}, {0.944844, 0.507658, 0.302433}, {0.947051, 0.512699, 0.299049}, {0.949217, 0.517763, 0.295662}, {0.951344, 0.522850, 0.292275}, {0.953428, 0.527960, 0.288883}, {0.955470, 0.533093, 0.285490}, {0.957469, 0.538250, 0.282096}, {0.959424, 0.543431, 0.278701}, {0.961336, 0.548636, 0.275305}, {0.963203, 0.553865, 0.271909}, {0.965024, 0.559118, 0.268513}, {0.966798, 0.564396, 0.265118}, {0.968526, 0.569700, 0.261721}, {0.970205, 0.575028, 0.258325}, {0.971835, 0.580382, 0.254931}, {0.973416, 0.585761, 0.251540}, {0.974947, 0.591165, 0.248151}, {0.976428, 0.596595, 0.244767}, {0.977856, 0.602051, 0.241387}, {0.979233, 0.607532, 0.238013}, {0.980556, 0.613039, 0.234646}, {0.981826, 0.618572, 0.231287}, {0.983041, 0.624131, 0.227937}, {0.984199, 0.629718, 0.224595}, {0.985301, 0.635330, 0.221265}, {0.986345, 0.640969, 0.217948}, {0.987332, 0.646633, 0.214648}, {0.988260, 0.652325, 0.211364}, {0.989128, 0.658043, 0.208100}, {0.989935, 0.663787, 0.204859}, {0.990681, 0.669558, 0.201642}, {0.991365, 0.675355, 0.198453}, {0.991985, 0.681179, 0.195295}, {0.992541, 0.687030, 0.192170}, {0.993032, 0.692907, 0.189084}, {0.993456, 0.698810, 0.186041}, {0.993814, 0.704741, 0.183043}, {0.994103, 0.710698, 0.180097}, {0.994324, 0.716681, 0.177208}, {0.994474, 0.722691, 0.174381}, {0.994553, 0.728728, 0.171622}, {0.994561, 0.734791, 0.168938}, {0.994495, 0.740880, 0.166335}, {0.994355, 0.746995, 0.163821}, {0.994141, 0.753137, 0.161404}, {0.993851, 0.759304, 0.159092}, {0.993482, 0.765499, 0.156891}, {0.993033, 0.771720, 0.154808}, {0.992505, 0.777967, 0.152855}, {0.991897, 0.784239, 0.151042}, {0.991209, 0.790537, 0.149377}, {0.990439, 0.796859, 0.147870}, {0.989587, 0.803205, 0.146529}, {0.988648, 0.809579, 0.145357}, {0.987621, 0.815978, 0.144363}, {0.986509, 0.822401, 0.143557}, {0.985314, 0.828846, 0.142945}, {0.984031, 0.835315, 0.142528}, {0.982653, 0.841812, 0.142303}, {0.981190, 0.848329, 0.142279}, {0.979644, 0.854866, 0.142453}, {0.977995, 0.861432, 0.142808}, {0.976265, 0.868016, 0.143351}, {0.974443, 0.874622, 0.144061}, {0.972530, 0.881250, 0.144923}, {0.970533, 0.887896, 0.145919}, {0.968443, 0.894564, 0.147014}, {0.966271, 0.901249, 0.148180}, {0.964021, 0.907950, 0.149370}, {0.961681, 0.914672, 0.150520}, {0.959276, 0.921407, 0.151566}, {0.956808, 0.928152, 0.152409}, {0.954287, 0.934908, 0.152921}, {0.951726, 0.941671, 0.152925}, {0.949151, 0.948435, 0.152178}, {0.946602, 0.955190, 0.150328}, {0.944152, 0.961916, 0.146861}, {0.941896, 0.968590, 0.140956}, {0.940015, 0.975158, 0.131326}};

  return readColorFromArray(v, f);
}

ColorRGB detail::Viridis::getColorMapVal(double f) const
{
  //From matplotlib. License found here: https://github.com/matplotlib/matplotlib/blob/master/LICENSE/LICENSE
  static std::vector<ColorRGB> v =
  {{0.267004, 0.004874, 0.329415}, {0.268510, 0.009605, 0.335427}, {0.269944, 0.014625, 0.341379}, {0.271305, 0.019942, 0.347269}, {0.272594, 0.025563, 0.353093}, {0.273809, 0.031497, 0.358853}, {0.274952, 0.037752, 0.364543}, {0.276022, 0.044167, 0.370164}, {0.277018, 0.050344, 0.375715}, {0.277941, 0.056324, 0.381191}, {0.278791, 0.062145, 0.386592}, {0.279566, 0.067836, 0.391917}, {0.280267, 0.073417, 0.397163}, {0.280894, 0.078907, 0.402329}, {0.281446, 0.084320, 0.407414}, {0.281924, 0.089666, 0.412415}, {0.282327, 0.094955, 0.417331}, {0.282656, 0.100196, 0.422160}, {0.282910, 0.105393, 0.426902}, {0.283091, 0.110553, 0.431554}, {0.283197, 0.115680, 0.436115}, {0.283229, 0.120777, 0.440584}, {0.283187, 0.125848, 0.444960}, {0.283072, 0.130895, 0.449241}, {0.282884, 0.135920, 0.453427}, {0.282623, 0.140926, 0.457517}, {0.282290, 0.145912, 0.461510}, {0.281887, 0.150881, 0.465405}, {0.281412, 0.155834, 0.469201}, {0.280868, 0.160771, 0.472899}, {0.280255, 0.165693, 0.476498}, {0.279574, 0.170599, 0.479997}, {0.278826, 0.175490, 0.483397}, {0.278012, 0.180367, 0.486697}, {0.277134, 0.185228, 0.489898}, {0.276194, 0.190074, 0.493001}, {0.275191, 0.194905, 0.496005}, {0.274128, 0.199721, 0.498911}, {0.273006, 0.204520, 0.501721}, {0.271828, 0.209303, 0.504434}, {0.270595, 0.214069, 0.507052}, {0.269308, 0.218818, 0.509577}, {0.267968, 0.223549, 0.512008}, {0.266580, 0.228262, 0.514349}, {0.265145, 0.232956, 0.516599}, {0.263663, 0.237631, 0.518762}, {0.262138, 0.242286, 0.520837}, {0.260571, 0.246922, 0.522828}, {0.258965, 0.251537, 0.524736}, {0.257322, 0.256130, 0.526563}, {0.255645, 0.260703, 0.528312}, {0.253935, 0.265254, 0.529983}, {0.252194, 0.269783, 0.531579}, {0.250425, 0.274290, 0.533103}, {0.248629, 0.278775, 0.534556}, {0.246811, 0.283237, 0.535941}, {0.244972, 0.287675, 0.537260}, {0.243113, 0.292092, 0.538516}, {0.241237, 0.296485, 0.539709}, {0.239346, 0.300855, 0.540844}, {0.237441, 0.305202, 0.541921}, {0.235526, 0.309527, 0.542944}, {0.233603, 0.313828, 0.543914}, {0.231674, 0.318106, 0.544834}, {0.229739, 0.322361, 0.545706}, {0.227802, 0.326594, 0.546532}, {0.225863, 0.330805, 0.547314}, {0.223925, 0.334994, 0.548053}, {0.221989, 0.339161, 0.548752}, {0.220057, 0.343307, 0.549413}, {0.218130, 0.347432, 0.550038}, {0.216210, 0.351535, 0.550627}, {0.214298, 0.355619, 0.551184}, {0.212395, 0.359683, 0.551710}, {0.210503, 0.363727, 0.552206}, {0.208623, 0.367752, 0.552675}, {0.206756, 0.371758, 0.553117}, {0.204903, 0.375746, 0.553533}, {0.203063, 0.379716, 0.553925}, {0.201239, 0.383670, 0.554294}, {0.199430, 0.387607, 0.554642}, {0.197636, 0.391528, 0.554969}, {0.195860, 0.395433, 0.555276}, {0.194100, 0.399323, 0.555565}, {0.192357, 0.403199, 0.555836}, {0.190631, 0.407061, 0.556089}, {0.188923, 0.410910, 0.556326}, {0.187231, 0.414746, 0.556547}, {0.185556, 0.418570, 0.556753}, {0.183898, 0.422383, 0.556944}, {0.182256, 0.426184, 0.557120}, {0.180629, 0.429975, 0.557282}, {0.179019, 0.433756, 0.557430}, {0.177423, 0.437527, 0.557565}, {0.175841, 0.441290, 0.557685}, {0.174274, 0.445044, 0.557792}, {0.172719, 0.448791, 0.557885}, {0.171176, 0.452530, 0.557965}, {0.169646, 0.456262, 0.558030}, {0.168126, 0.459988, 0.558082}, {0.166617, 0.463708, 0.558119}, {0.165117, 0.467423, 0.558141}, {0.163625, 0.471133, 0.558148}, {0.162142, 0.474838, 0.558140}, {0.160665, 0.478540, 0.558115}, {0.159194, 0.482237, 0.558073}, {0.157729, 0.485932, 0.558013}, {0.156270, 0.489624, 0.557936}, {0.154815, 0.493313, 0.557840}, {0.153364, 0.497000, 0.557724}, {0.151918, 0.500685, 0.557587}, {0.150476, 0.504369, 0.557430}, {0.149039, 0.508051, 0.557250}, {0.147607, 0.511733, 0.557049}, {0.146180, 0.515413, 0.556823}, {0.144759, 0.519093, 0.556572}, {0.143343, 0.522773, 0.556295}, {0.141935, 0.526453, 0.555991}, {0.140536, 0.530132, 0.555659}, {0.139147, 0.533812, 0.555298}, {0.137770, 0.537492, 0.554906}, {0.136408, 0.541173, 0.554483}, {0.135066, 0.544853, 0.554029}, {0.133743, 0.548535, 0.553541}, {0.132444, 0.552216, 0.553018}, {0.131172, 0.555899, 0.552459}, {0.129933, 0.559582, 0.551864}, {0.128729, 0.563265, 0.551229}, {0.127568, 0.566949, 0.550556}, {0.126453, 0.570633, 0.549841}, {0.125394, 0.574318, 0.549086}, {0.124395, 0.578002, 0.548287}, {0.123463, 0.581687, 0.547445}, {0.122606, 0.585371, 0.546557}, {0.121831, 0.589055, 0.545623}, {0.121148, 0.592739, 0.544641}, {0.120565, 0.596422, 0.543611}, {0.120092, 0.600104, 0.542530}, {0.119738, 0.603785, 0.541400}, {0.119512, 0.607464, 0.540218}, {0.119423, 0.611141, 0.538982}, {0.119483, 0.614817, 0.537692}, {0.119699, 0.618490, 0.536347}, {0.120081, 0.622161, 0.534946}, {0.120638, 0.625828, 0.533488}, {0.121380, 0.629492, 0.531973}, {0.122312, 0.633153, 0.530398}, {0.123444, 0.636809, 0.528763}, {0.124780, 0.640461, 0.527068}, {0.126326, 0.644107, 0.525311}, {0.128087, 0.647749, 0.523491}, {0.130067, 0.651384, 0.521608}, {0.132268, 0.655014, 0.519661}, {0.134692, 0.658636, 0.517649}, {0.137339, 0.662252, 0.515571}, {0.140210, 0.665859, 0.513427}, {0.143303, 0.669459, 0.511215}, {0.146616, 0.673050, 0.508936}, {0.150148, 0.676631, 0.506589}, {0.153894, 0.680203, 0.504172}, {0.157851, 0.683765, 0.501686}, {0.162016, 0.687316, 0.499129}, {0.166383, 0.690856, 0.496502}, {0.170948, 0.694384, 0.493803}, {0.175707, 0.697900, 0.491033}, {0.180653, 0.701402, 0.488189}, {0.185783, 0.704891, 0.485273}, {0.191090, 0.708366, 0.482284}, {0.196571, 0.711827, 0.479221}, {0.202219, 0.715272, 0.476084}, {0.208030, 0.718701, 0.472873}, {0.214000, 0.722114, 0.469588}, {0.220124, 0.725509, 0.466226}, {0.226397, 0.728888, 0.462789}, {0.232815, 0.732247, 0.459277}, {0.239374, 0.735588, 0.455688}, {0.246070, 0.738910, 0.452024}, {0.252899, 0.742211, 0.448284}, {0.259857, 0.745492, 0.444467}, {0.266941, 0.748751, 0.440573}, {0.274149, 0.751988, 0.436601}, {0.281477, 0.755203, 0.432552}, {0.288921, 0.758394, 0.428426}, {0.296479, 0.761561, 0.424223}, {0.304148, 0.764704, 0.419943}, {0.311925, 0.767822, 0.415586}, {0.319809, 0.770914, 0.411152}, {0.327796, 0.773980, 0.406640}, {0.335885, 0.777018, 0.402049}, {0.344074, 0.780029, 0.397381}, {0.352360, 0.783011, 0.392636}, {0.360741, 0.785964, 0.387814}, {0.369214, 0.788888, 0.382914}, {0.377779, 0.791781, 0.377939}, {0.386433, 0.794644, 0.372886}, {0.395174, 0.797475, 0.367757}, {0.404001, 0.800275, 0.362552}, {0.412913, 0.803041, 0.357269}, {0.421908, 0.805774, 0.351910}, {0.430983, 0.808473, 0.346476}, {0.440137, 0.811138, 0.340967}, {0.449368, 0.813768, 0.335384}, {0.458674, 0.816363, 0.329727}, {0.468053, 0.818921, 0.323998}, {0.477504, 0.821444, 0.318195}, {0.487026, 0.823929, 0.312321}, {0.496615, 0.826376, 0.306377}, {0.506271, 0.828786, 0.300362}, {0.515992, 0.831158, 0.294279}, {0.525776, 0.833491, 0.288127}, {0.535621, 0.835785, 0.281908}, {0.545524, 0.838039, 0.275626}, {0.555484, 0.840254, 0.269281}, {0.565498, 0.842430, 0.262877}, {0.575563, 0.844566, 0.256415}, {0.585678, 0.846661, 0.249897}, {0.595839, 0.848717, 0.243329}, {0.606045, 0.850733, 0.236712}, {0.616293, 0.852709, 0.230052}, {0.626579, 0.854645, 0.223353}, {0.636902, 0.856542, 0.216620}, {0.647257, 0.858400, 0.209861}, {0.657642, 0.860219, 0.203082}, {0.668054, 0.861999, 0.196293}, {0.678489, 0.863742, 0.189503}, {0.688944, 0.865448, 0.182725}, {0.699415, 0.867117, 0.175971}, {0.709898, 0.868751, 0.169257}, {0.720391, 0.870350, 0.162603}, {0.730889, 0.871916, 0.156029}, {0.741388, 0.873449, 0.149561}, {0.751884, 0.874951, 0.143228}, {0.762373, 0.876424, 0.137064}, {0.772852, 0.877868, 0.131109}, {0.783315, 0.879285, 0.125405}, {0.793760, 0.880678, 0.120005}, {0.804182, 0.882046, 0.114965}, {0.814576, 0.883393, 0.110347}, {0.824940, 0.884720, 0.106217}, {0.835270, 0.886029, 0.102646}, {0.845561, 0.887322, 0.099702}, {0.855810, 0.888601, 0.097452}, {0.866013, 0.889868, 0.095953}, {0.876168, 0.891125, 0.095250}, {0.886271, 0.892374, 0.095374}, {0.896320, 0.893616, 0.096335}, {0.906311, 0.894855, 0.098125}, {0.916242, 0.896091, 0.100717}, {0.926106, 0.897330, 0.104071}, {0.935904, 0.898570, 0.108131}, {0.945636, 0.899815, 0.112838}, {0.955300, 0.901065, 0.118128}, {0.964894, 0.902323, 0.123941}, {0.974417, 0.903590, 0.130215}, {0.983868, 0.904867, 0.136897}, {0.993248, 0.906157, 0.143936}};

  return readColorFromArray(v, f);
}

ColorRGB detail::Cividis::getColorMapVal(double f) const
{
  //From matplotlib. License found here: https://github.com/matplotlib/matplotlib/blob/master/LICENSE/LICENSE
  static std::vector<ColorRGB> v =
  {{0.000000, 0.135112, 0.304751}, {0.000000, 0.138068, 0.311105}, {0.000000, 0.141013, 0.317579}, {0.000000, 0.143951, 0.323982}, {0.000000, 0.146877, 0.330479}, {0.000000, 0.149791, 0.337065}, {0.000000, 0.152673, 0.343704}, {0.000000, 0.155377, 0.350500}, {0.000000, 0.157932, 0.357521}, {0.000000, 0.160495, 0.364534}, {0.000000, 0.163058, 0.371608}, {0.000000, 0.165621, 0.378769}, {0.000000, 0.168204, 0.385902}, {0.000000, 0.170800, 0.393100}, {0.000000, 0.173420, 0.400353}, {0.000000, 0.176082, 0.407577}, {0.000000, 0.178802, 0.414764}, {0.000000, 0.181610, 0.421859}, {0.000000, 0.184550, 0.428802}, {0.000000, 0.186915, 0.435532}, {0.000000, 0.188769, 0.439563}, {0.000000, 0.190950, 0.441085}, {0.000000, 0.193366, 0.441561}, {0.003602, 0.195911, 0.441564}, {0.017852, 0.198528, 0.441248}, {0.032110, 0.201199, 0.440785}, {0.046205, 0.203903, 0.440196}, {0.058378, 0.206629, 0.439531}, {0.068968, 0.209372, 0.438863}, {0.078624, 0.212122, 0.438105}, {0.087465, 0.214879, 0.437342}, {0.095645, 0.217643, 0.436593}, {0.103401, 0.220406, 0.435790}, {0.110658, 0.223170, 0.435067}, {0.117612, 0.225935, 0.434308}, {0.124291, 0.228697, 0.433547}, {0.130669, 0.231458, 0.432840}, {0.136830, 0.234216, 0.432148}, {0.142852, 0.236972, 0.431404}, {0.148638, 0.239724, 0.430752}, {0.154261, 0.242475, 0.430120}, {0.159733, 0.245221, 0.429528}, {0.165113, 0.247965, 0.428908}, {0.170362, 0.250707, 0.428325}, {0.175490, 0.253444, 0.427790}, {0.180503, 0.256180, 0.427299}, {0.185453, 0.258914, 0.426788}, {0.190303, 0.261644, 0.426329}, {0.195057, 0.264372, 0.425924}, {0.199764, 0.267099, 0.425497}, {0.204385, 0.269823, 0.425126}, {0.208926, 0.272546, 0.424809}, {0.213431, 0.275266, 0.424480}, {0.217863, 0.277985, 0.424206}, {0.222264, 0.280702, 0.423914}, {0.226598, 0.283419, 0.423678}, {0.230871, 0.286134, 0.423498}, {0.235120, 0.288848, 0.423304}, {0.239312, 0.291562, 0.423167}, {0.243485, 0.294274, 0.423014}, {0.247605, 0.296986, 0.422917}, {0.251675, 0.299698, 0.422873}, {0.255731, 0.302409, 0.422814}, {0.259740, 0.305120, 0.422810}, {0.263738, 0.307831, 0.422789}, {0.267693, 0.310542, 0.422821}, {0.271639, 0.313253, 0.422837}, {0.275513, 0.315965, 0.422979}, {0.279411, 0.318677, 0.423031}, {0.283240, 0.321390, 0.423211}, {0.287065, 0.324103, 0.423373}, {0.290884, 0.326816, 0.423517}, {0.294669, 0.329531, 0.423716}, {0.298421, 0.332247, 0.423973}, {0.302169, 0.334963, 0.424213}, {0.305886, 0.337681, 0.424512}, {0.309601, 0.340399, 0.424790}, {0.313287, 0.343120, 0.425120}, {0.316941, 0.345842, 0.425512}, {0.320595, 0.348565, 0.425889}, {0.324250, 0.351289, 0.426250}, {0.327875, 0.354016, 0.426670}, {0.331474, 0.356744, 0.427144}, {0.335073, 0.359474, 0.427605}, {0.338673, 0.362206, 0.428053}, {0.342246, 0.364939, 0.428559}, {0.345793, 0.367676, 0.429127}, {0.349341, 0.370414, 0.429685}, {0.352892, 0.373153, 0.430226}, {0.356418, 0.375896, 0.430823}, {0.359916, 0.378641, 0.431501}, {0.363446, 0.381388, 0.432075}, {0.366923, 0.384139, 0.432796}, {0.370430, 0.386890, 0.433428}, {0.373884, 0.389646, 0.434209}, {0.377371, 0.392404, 0.434890}, {0.380830, 0.395164, 0.435653}, {0.384268, 0.397928, 0.436475}, {0.387705, 0.400694, 0.437305}, {0.391151, 0.403464, 0.438096}, {0.394568, 0.406236, 0.438986}, {0.397991, 0.409011, 0.439848}, {0.401418, 0.411790, 0.440708}, {0.404820, 0.414572, 0.441642}, {0.408226, 0.417357, 0.442570}, {0.411607, 0.420145, 0.443577}, {0.414992, 0.422937, 0.444578}, {0.418383, 0.425733, 0.445560}, {0.421748, 0.428531, 0.446640}, {0.425120, 0.431334, 0.447692}, {0.428462, 0.434140, 0.448864}, {0.431817, 0.436950, 0.449982}, {0.435168, 0.439763, 0.451134}, {0.438504, 0.442580, 0.452341}, {0.441810, 0.445402, 0.453659}, {0.445148, 0.448226, 0.454885}, {0.448447, 0.451053, 0.456264}, {0.451759, 0.453887, 0.457582}, {0.455072, 0.456718, 0.458976}, {0.458366, 0.459552, 0.460457}, {0.461616, 0.462405, 0.461969}, {0.464947, 0.465241, 0.463395}, {0.468254, 0.468083, 0.464908}, {0.471501, 0.470960, 0.466357}, {0.474812, 0.473832, 0.467681}, {0.478186, 0.476699, 0.468845}, {0.481622, 0.479573, 0.469767}, {0.485141, 0.482451, 0.470384}, {0.488697, 0.485318, 0.471008}, {0.492278, 0.488198, 0.471453}, {0.495913, 0.491076, 0.471751}, {0.499552, 0.493960, 0.472032}, {0.503185, 0.496851, 0.472305}, {0.506866, 0.499743, 0.472432}, {0.510540, 0.502643, 0.472550}, {0.514226, 0.505546, 0.472640}, {0.517920, 0.508454, 0.472707}, {0.521643, 0.511367, 0.472639}, {0.525348, 0.514285, 0.472660}, {0.529086, 0.517207, 0.472543}, {0.532829, 0.520135, 0.472401}, {0.536553, 0.523067, 0.472352}, {0.540307, 0.526005, 0.472163}, {0.544069, 0.528948, 0.471947}, {0.547840, 0.531895, 0.471704}, {0.551612, 0.534849, 0.471439}, {0.555393, 0.537807, 0.471147}, {0.559181, 0.540771, 0.470829}, {0.562972, 0.543741, 0.470488}, {0.566802, 0.546715, 0.469988}, {0.570607, 0.549695, 0.469593}, {0.574417, 0.552682, 0.469172}, {0.578236, 0.555673, 0.468724}, {0.582087, 0.558670, 0.468118}, {0.585916, 0.561674, 0.467618}, {0.589753, 0.564682, 0.467090}, {0.593622, 0.567697, 0.466401}, {0.597469, 0.570718, 0.465821}, {0.601354, 0.573743, 0.465074}, {0.605211, 0.576777, 0.464441}, {0.609105, 0.579816, 0.463638}, {0.612977, 0.582861, 0.462950}, {0.616852, 0.585913, 0.462237}, {0.620765, 0.588970, 0.461351}, {0.624654, 0.592034, 0.460583}, {0.628576, 0.595104, 0.459641}, {0.632506, 0.598180, 0.458668}, {0.636412, 0.601264, 0.457818}, {0.640352, 0.604354, 0.456791}, {0.644270, 0.607450, 0.455886}, {0.648222, 0.610553, 0.454801}, {0.652178, 0.613664, 0.453689}, {0.656114, 0.616780, 0.452702}, {0.660082, 0.619904, 0.451534}, {0.664055, 0.623034, 0.450338}, {0.668008, 0.626171, 0.449270}, {0.671991, 0.629316, 0.448018}, {0.675981, 0.632468, 0.446736}, {0.679979, 0.635626, 0.445424}, {0.683950, 0.638793, 0.444251}, {0.687957, 0.641966, 0.442886}, {0.691971, 0.645145, 0.441491}, {0.695985, 0.648334, 0.440072}, {0.700008, 0.651529, 0.438624}, {0.704037, 0.654731, 0.437147}, {0.708067, 0.657942, 0.435647}, {0.712105, 0.661160, 0.434117}, {0.716177, 0.664384, 0.432386}, {0.720222, 0.667618, 0.430805}, {0.724274, 0.670859, 0.429194}, {0.728334, 0.674107, 0.427554}, {0.732422, 0.677364, 0.425717}, {0.736488, 0.680629, 0.424028}, {0.740589, 0.683900, 0.422131}, {0.744664, 0.687181, 0.420393}, {0.748772, 0.690470, 0.418448}, {0.752886, 0.693766, 0.416472}, {0.756975, 0.697071, 0.414659}, {0.761096, 0.700384, 0.412638}, {0.765223, 0.703705, 0.410587}, {0.769353, 0.707035, 0.408516}, {0.773486, 0.710373, 0.406422}, {0.777651, 0.713719, 0.404112}, {0.781795, 0.717074, 0.401966}, {0.785965, 0.720438, 0.399613}, {0.790116, 0.723810, 0.397423}, {0.794298, 0.727190, 0.395016}, {0.798480, 0.730580, 0.392597}, {0.802667, 0.733978, 0.390153}, {0.806859, 0.737385, 0.387684}, {0.811054, 0.740801, 0.385198}, {0.815274, 0.744226, 0.382504}, {0.819499, 0.747659, 0.379785}, {0.823729, 0.751101, 0.377043}, {0.827959, 0.754553, 0.374292}, {0.832192, 0.758014, 0.371529}, {0.836429, 0.761483, 0.368747}, {0.840693, 0.764962, 0.365746}, {0.844957, 0.768450, 0.362741}, {0.849223, 0.771947, 0.359729}, {0.853515, 0.775454, 0.356500}, {0.857809, 0.778969, 0.353259}, {0.862105, 0.782494, 0.350011}, {0.866421, 0.786028, 0.346571}, {0.870717, 0.789572, 0.343333}, {0.875057, 0.793125, 0.339685}, {0.879378, 0.796687, 0.336241}, {0.883720, 0.800258, 0.332599}, {0.888081, 0.803839, 0.328770}, {0.892440, 0.807430, 0.324968}, {0.896818, 0.811030, 0.320982}, {0.901195, 0.814639, 0.317021}, {0.905589, 0.818257, 0.312889}, {0.910000, 0.821885, 0.308594}, {0.914407, 0.825522, 0.304348}, {0.918828, 0.829168, 0.299960}, {0.923279, 0.832822, 0.295244}, {0.927724, 0.836486, 0.290611}, {0.932180, 0.840159, 0.285880}, {0.936660, 0.843841, 0.280876}, {0.941147, 0.847530, 0.275815}, {0.945654, 0.851228, 0.270532}, {0.950178, 0.854933, 0.265085}, {0.954725, 0.858646, 0.259365}, {0.959284, 0.862365, 0.253563}, {0.963872, 0.866089, 0.247445}, {0.968469, 0.869819, 0.241310}, {0.973114, 0.873550, 0.234677}, {0.977780, 0.877281, 0.227954}, {0.982497, 0.881008, 0.220878}, {0.987293, 0.884718, 0.213336}, {0.992218, 0.888385, 0.205468}, {0.994847, 0.892954, 0.203445}, {0.995249, 0.898384, 0.207561}, {0.995503, 0.903866, 0.212370}, {0.995737, 0.909344, 0.217772}};

  return readColorFromArray(v, f);
}

ColorRGB detail::MixedRainbow::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v =
  {{0.000000, 0.000000, 0.513726}, {0.000000, 0.266667, 1.000000}, {0.015686, 1.000000, 0.984314}, {0.764706, 1.000000, 0.235294}, {1.000000, 0.486275, 0.000000}, {0.733333, 0.000000, 0.000000}, {0.000000, 0.000000, 0.529412}, {0.000000, 0.282353, 1.000000}, {0.031373, 1.000000, 0.968627}, {0.780392, 1.000000, 0.219608}, {1.000000, 0.470588, 0.000000}, {0.717647, 0.000000, 0.000000}, {0.000000, 0.000000, 0.545098}, {0.000000, 0.298039, 1.000000}, {0.047059, 1.000000, 0.952941}, {0.796078, 1.000000, 0.203922}, {1.000000, 0.454902, 0.000000}, {0.701961, 0.000000, 0.000000}, {0.000000, 0.000000, 0.560784}, {0.000000, 0.313726, 1.000000}, {0.062745, 1.000000, 0.937255}, {0.811765, 1.000000, 0.188235}, {1.000000, 0.439216, 0.000000}, {0.686275, 0.000000, 0.000000}, {0.000000, 0.000000, 0.576471}, {0.000000, 0.329412, 1.000000}, {0.078431, 1.000000, 0.921569}, {0.827451, 1.000000, 0.172549}, {1.000000, 0.423529, 0.000000}, {0.670588, 0.000000, 0.000000}, {0.000000, 0.000000, 0.592157}, {0.000000, 0.345098, 1.000000}, {0.094118, 1.000000, 0.905882}, {0.843137, 1.000000, 0.156863}, {1.000000, 0.407843, 0.000000}, {0.654902, 0.000000, 0.000000}, {0.000000, 0.000000, 0.607843}, {0.000000, 0.360784, 1.000000}, {0.109804, 1.000000, 0.890196}, {0.858824, 1.000000, 0.141176}, {1.000000, 0.392157, 0.000000}, {0.639216, 0.000000, 0.000000}, {0.000000, 0.000000, 0.623529}, {0.000000, 0.376471, 1.000000}, {0.125490, 1.000000, 0.874510}, {0.874510, 1.000000, 0.125490}, {1.000000, 0.376471, 0.000000}, {0.623529, 0.000000, 0.000000}, {0.000000, 0.000000, 0.639216}, {0.000000, 0.392157, 1.000000}, {0.141176, 1.000000, 0.858824}, {0.890196, 1.000000, 0.109804}, {1.000000, 0.360784, 0.000000}, {0.607843, 0.000000, 0.000000}, {0.000000, 0.000000, 0.654902}, {0.000000, 0.407843, 1.000000}, {0.156863, 1.000000, 0.843137}, {0.905882, 1.000000, 0.094118}, {1.000000, 0.345098, 0.000000}, {0.592157, 0.000000, 0.000000}, {0.000000, 0.000000, 0.670588}, {0.000000, 0.423529, 1.000000}, {0.172549, 1.000000, 0.827451}, {0.921569, 1.000000, 0.078431}, {1.000000, 0.329412, 0.000000}, {0.576471, 0.000000, 0.000000}, {0.000000, 0.000000, 0.686275}, {0.000000, 0.439216, 1.000000}, {0.188235, 1.000000, 0.811765}, {0.937255, 1.000000, 0.062745}, {1.000000, 0.313726, 0.000000}, {0.560784, 0.000000, 0.000000}, {0.000000, 0.000000, 0.701961}, {0.000000, 0.454902, 1.000000}, {0.203922, 1.000000, 0.796078}, {0.952941, 1.000000, 0.047059}, {1.000000, 0.298039, 0.000000}, {0.545098, 0.000000, 0.000000}, {0.000000, 0.000000, 0.717647}, {0.000000, 0.470588, 1.000000}, {0.219608, 1.000000, 0.780392}, {0.968627, 1.000000, 0.031373}, {1.000000, 0.282353, 0.000000}, {0.529412, 0.000000, 0.000000}, {0.000000, 0.000000, 0.733333}, {0.000000, 0.486275, 1.000000}, {0.235294, 1.000000, 0.764706}, {0.984314, 1.000000, 0.015686}, {1.000000, 0.266667, 0.000000}, {0.513726, 0.000000, 0.000000}, {0.000000, 0.000000, 0.749020}, {0.000000, 0.501961, 1.000000}, {0.250980, 1.000000, 0.749020}, {1.000000, 1.000000, 0.000000}, {1.000000, 0.250980, 0.000000}, {0.501961, 0.000000, 0.000000}, {0.000000, 0.000000, 0.764706}, {0.000000, 0.513726, 1.000000}, {0.266667, 1.000000, 0.733333}, {1.000000, 0.984314, 0.000000}, {1.000000, 0.235294, 0.000000}, {0.000000, 0.000000, 0.780392}, {0.000000, 0.529412, 1.000000}, {0.282353, 1.000000, 0.717647}, {1.000000, 0.968627, 0.000000}, {1.000000, 0.219608, 0.000000}, {0.000000, 0.000000, 0.796078}, {0.000000, 0.545098, 1.000000}, {0.298039, 1.000000, 0.701961}, {1.000000, 0.952941, 0.000000}, {1.000000, 0.203922, 0.000000}, {0.000000, 0.000000, 0.811765}, {0.000000, 0.560784, 1.000000}, {0.313726, 1.000000, 0.686275}, {1.000000, 0.937255, 0.000000}, {1.000000, 0.188235, 0.000000}, {0.000000, 0.000000, 0.827451}, {0.000000, 0.576471, 1.000000}, {0.329412, 1.000000, 0.670588}, {1.000000, 0.921569, 0.000000}, {1.000000, 0.172549, 0.000000}, {0.000000, 0.000000, 0.843137}, {0.000000, 0.592157, 1.000000}, {0.345098, 1.000000, 0.654902}, {1.000000, 0.905882, 0.000000}, {1.000000, 0.156863, 0.000000}, {0.000000, 0.000000, 0.858824}, {0.000000, 0.607843, 1.000000}, {0.360784, 1.000000, 0.639216}, {1.000000, 0.890196, 0.000000}, {1.000000, 0.141176, 0.000000}, {0.000000, 0.000000, 0.874510}, {0.000000, 0.623529, 1.000000}, {0.376471, 1.000000, 0.623529}, {1.000000, 0.874510, 0.000000}, {1.000000, 0.125490, 0.000000}, {0.000000, 0.000000, 0.890196}, {0.000000, 0.639216, 1.000000}, {0.392157, 1.000000, 0.607843}, {1.000000, 0.858824, 0.000000}, {1.000000, 0.109804, 0.000000}, {0.000000, 0.000000, 0.905882}, {0.000000, 0.654902, 1.000000}, {0.407843, 1.000000, 0.592157}, {1.000000, 0.843137, 0.000000}, {1.000000, 0.094118, 0.000000}, {0.000000, 0.000000, 0.921569}, {0.000000, 0.670588, 1.000000}, {0.423529, 1.000000, 0.576471}, {1.000000, 0.827451, 0.000000}, {1.000000, 0.078431, 0.000000}, {0.000000, 0.000000, 0.937255}, {0.000000, 0.686275, 1.000000}, {0.439216, 1.000000, 0.560784}, {1.000000, 0.811765, 0.000000}, {1.000000, 0.062745, 0.000000}, {0.000000, 0.000000, 0.952941}, {0.000000, 0.701961, 1.000000}, {0.454902, 1.000000, 0.545098}, {1.000000, 0.796078, 0.000000}, {1.000000, 0.047059, 0.000000}, {0.000000, 0.000000, 0.968627}, {0.000000, 0.717647, 1.000000}, {0.470588, 1.000000, 0.529412}, {1.000000, 0.780392, 0.000000}, {1.000000, 0.031373, 0.000000}, {0.000000, 0.000000, 0.984314}, {0.000000, 0.733333, 1.000000}, {0.486275, 1.000000, 0.513726}, {1.000000, 0.764706, 0.000000}, {1.000000, 0.015686, 0.000000}, {0.000000, 0.000000, 1.000000}, {0.000000, 0.749020, 1.000000}, {0.501961, 1.000000, 0.501961}, {1.000000, 0.749020, 0.000000}, {1.000000, 0.000000, 0.000000}, {0.000000, 0.015686, 1.000000}, {0.000000, 0.764706, 1.000000}, {0.513726, 1.000000, 0.486275}, {1.000000, 0.733333, 0.000000}, {0.984314, 0.000000, 0.000000}, {0.000000, 0.031373, 1.000000}, {0.000000, 0.780392, 1.000000}, {0.529412, 1.000000, 0.470588}, {1.000000, 0.717647, 0.000000}, {0.968627, 0.000000, 0.000000}, {0.000000, 0.047059, 1.000000}, {0.000000, 0.796078, 1.000000}, {0.545098, 1.000000, 0.454902}, {1.000000, 0.701961, 0.000000}, {0.952941, 0.000000, 0.000000}, {0.000000, 0.062745, 1.000000}, {0.000000, 0.811765, 1.000000}, {0.560784, 1.000000, 0.439216}, {1.000000, 0.686275, 0.000000}, {0.937255, 0.000000, 0.000000}, {0.000000, 0.078431, 1.000000}, {0.000000, 0.827451, 1.000000}, {0.576471, 1.000000, 0.423529}, {1.000000, 0.670588, 0.000000}, {0.921569, 0.000000, 0.000000}, {0.000000, 0.094118, 1.000000}, {0.000000, 0.843137, 1.000000}, {0.592157, 1.000000, 0.407843}, {1.000000, 0.654902, 0.000000}, {0.905882, 0.000000, 0.000000}, {0.000000, 0.109804, 1.000000}, {0.000000, 0.858824, 1.000000}, {0.607843, 1.000000, 0.392157}, {1.000000, 0.639216, 0.000000}, {0.890196, 0.000000, 0.000000}, {0.000000, 0.125490, 1.000000}, {0.000000, 0.874510, 1.000000}, {0.623529, 1.000000, 0.376471}, {1.000000, 0.623529, 0.000000}, {0.874510, 0.000000, 0.000000}, {0.000000, 0.141176, 1.000000}, {0.000000, 0.890196, 1.000000}, {0.639216, 1.000000, 0.360784}, {1.000000, 0.607843, 0.000000}, {0.858824, 0.000000, 0.000000}, {0.000000, 0.156863, 1.000000}, {0.000000, 0.905882, 1.000000}, {0.654902, 1.000000, 0.345098}, {1.000000, 0.592157, 0.000000}, {0.843137, 0.000000, 0.000000}, {0.000000, 0.172549, 1.000000}, {0.000000, 0.921569, 1.000000}, {0.670588, 1.000000, 0.329412}, {1.000000, 0.576471, 0.000000}, {0.827451, 0.000000, 0.000000}, {0.000000, 0.188235, 1.000000}, {0.000000, 0.937255, 1.000000}, {0.686275, 1.000000, 0.313726}, {1.000000, 0.560784, 0.000000}, {0.811765, 0.000000, 0.000000}, {0.000000, 0.203922, 1.000000}, {0.000000, 0.952941, 1.000000}, {0.701961, 1.000000, 0.298039}, {1.000000, 0.545098, 0.000000}, {0.796078, 0.000000, 0.000000}, {0.000000, 0.219608, 1.000000}, {0.000000, 0.968627, 1.000000}, {0.717647, 1.000000, 0.282353}, {1.000000, 0.529412, 0.000000}, {0.780392, 0.000000, 0.000000}, {0.000000, 0.235294, 1.000000}, {0.000000, 0.984314, 1.000000}, {0.733333, 1.000000, 0.266667}, {1.000000, 0.513726, 0.000000}, {0.764706, 0.000000, 0.000000}, {0.000000, 0.250980, 1.000000}, {0.000000, 1.000000, 1.000000}, {0.749020, 1.000000, 0.250980}, {1.000000, 0.501961, 0.000000}, {0.749020, 0.000000, 0.000000}};

  return readColorFromArray(v, f);
}

ColorRGB detail::MixedGrayScale::getColorMapVal(double f) const
{
  static std::vector<ColorRGB> v =
  {{0.000000, 0.000000, 0.000000}, {0.188235, 0.188235, 0.188235}, {0.376471, 0.376471, 0.376471}, {0.564706, 0.564706, 0.564706}, {0.752941, 0.752941, 0.752941}, {0.941176, 0.941176, 0.941176}, {0.003922, 0.003922, 0.003922}, {0.192157, 0.192157, 0.192157}, {0.380392, 0.380392, 0.380392}, {0.568627, 0.568627, 0.568627}, {0.756863, 0.756863, 0.756863}, {0.945098, 0.945098, 0.945098}, {0.007843, 0.007843, 0.007843}, {0.196078, 0.196078, 0.196078}, {0.384314, 0.384314, 0.384314}, {0.572549, 0.572549, 0.572549}, {0.760784, 0.760784, 0.760784}, {0.949020, 0.949020, 0.949020}, {0.011765, 0.011765, 0.011765}, {0.200000, 0.200000, 0.200000}, {0.388235, 0.388235, 0.388235}, {0.576471, 0.576471, 0.576471}, {0.764706, 0.764706, 0.764706}, {0.952941, 0.952941, 0.952941}, {0.015686, 0.015686, 0.015686}, {0.203922, 0.203922, 0.203922}, {0.392157, 0.392157, 0.392157}, {0.580392, 0.580392, 0.580392}, {0.768627, 0.768627, 0.768627}, {0.956863, 0.956863, 0.956863}, {0.019608, 0.019608, 0.019608}, {0.207843, 0.207843, 0.207843}, {0.396078, 0.396078, 0.396078}, {0.584314, 0.584314, 0.584314}, {0.772549, 0.772549, 0.772549}, {0.960784, 0.960784, 0.960784}, {0.023529, 0.023529, 0.023529}, {0.211765, 0.211765, 0.211765}, {0.400000, 0.400000, 0.400000}, {0.588235, 0.588235, 0.588235}, {0.776471, 0.776471, 0.776471}, {0.964706, 0.964706, 0.964706}, {0.027451, 0.027451, 0.027451}, {0.215686, 0.215686, 0.215686}, {0.403922, 0.403922, 0.403922}, {0.592157, 0.592157, 0.592157}, {0.780392, 0.780392, 0.780392}, {0.968627, 0.968627, 0.968627}, {0.031373, 0.031373, 0.031373}, {0.219608, 0.219608, 0.219608}, {0.407843, 0.407843, 0.407843}, {0.596078, 0.596078, 0.596078}, {0.784314, 0.784314, 0.784314}, {0.972549, 0.972549, 0.972549}, {0.035294, 0.035294, 0.035294}, {0.223529, 0.223529, 0.223529}, {0.411765, 0.411765, 0.411765}, {0.600000, 0.600000, 0.600000}, {0.788235, 0.788235, 0.788235}, {0.976471, 0.976471, 0.976471}, {0.039216, 0.039216, 0.039216}, {0.227451, 0.227451, 0.227451}, {0.415686, 0.415686, 0.415686}, {0.603922, 0.603922, 0.603922}, {0.792157, 0.792157, 0.792157}, {0.980392, 0.980392, 0.980392}, {0.043137, 0.043137, 0.043137}, {0.231373, 0.231373, 0.231373}, {0.419608, 0.419608, 0.419608}, {0.607843, 0.607843, 0.607843}, {0.796078, 0.796078, 0.796078}, {0.984314, 0.984314, 0.984314}, {0.047059, 0.047059, 0.047059}, {0.235294, 0.235294, 0.235294}, {0.423529, 0.423529, 0.423529}, {0.611765, 0.611765, 0.611765}, {0.800000, 0.800000, 0.800000}, {0.988235, 0.988235, 0.988235}, {0.050980, 0.050980, 0.050980}, {0.239216, 0.239216, 0.239216}, {0.427451, 0.427451, 0.427451}, {0.615686, 0.615686, 0.615686}, {0.803922, 0.803922, 0.803922}, {0.992157, 0.992157, 0.992157}, {0.054902, 0.054902, 0.054902}, {0.243137, 0.243137, 0.243137}, {0.431373, 0.431373, 0.431373}, {0.619608, 0.619608, 0.619608}, {0.807843, 0.807843, 0.807843}, {0.996078, 0.996078, 0.996078}, {0.058824, 0.058824, 0.058824}, {0.247059, 0.247059, 0.247059}, {0.435294, 0.435294, 0.435294}, {0.623529, 0.623529, 0.623529}, {0.811765, 0.811765, 0.811765}, {1.000000, 1.000000, 1.000000}, {0.062745, 0.062745, 0.062745}, {0.250980, 0.250980, 0.250980}, {0.439216, 0.439216, 0.439216}, {0.627451, 0.627451, 0.627451}, {0.815686, 0.815686, 0.815686}, {0.066667, 0.066667, 0.066667}, {0.254902, 0.254902, 0.254902}, {0.443137, 0.443137, 0.443137}, {0.631373, 0.631373, 0.631373}, {0.819608, 0.819608, 0.819608}, {0.070588, 0.070588, 0.070588}, {0.258824, 0.258824, 0.258824}, {0.447059, 0.447059, 0.447059}, {0.635294, 0.635294, 0.635294}, {0.823529, 0.823529, 0.823529}, {0.074510, 0.074510, 0.074510}, {0.262745, 0.262745, 0.262745}, {0.450980, 0.450980, 0.450980}, {0.639216, 0.639216, 0.639216}, {0.827451, 0.827451, 0.827451}, {0.078431, 0.078431, 0.078431}, {0.266667, 0.266667, 0.266667}, {0.454902, 0.454902, 0.454902}, {0.643137, 0.643137, 0.643137}, {0.831373, 0.831373, 0.831373}, {0.082353, 0.082353, 0.082353}, {0.270588, 0.270588, 0.270588}, {0.458824, 0.458824, 0.458824}, {0.647059, 0.647059, 0.647059}, {0.835294, 0.835294, 0.835294}, {0.086275, 0.086275, 0.086275}, {0.274510, 0.274510, 0.274510}, {0.462745, 0.462745, 0.462745}, {0.650980, 0.650980, 0.650980}, {0.839216, 0.839216, 0.839216}, {0.090196, 0.090196, 0.090196}, {0.278431, 0.278431, 0.278431}, {0.466667, 0.466667, 0.466667}, {0.654902, 0.654902, 0.654902}, {0.843137, 0.843137, 0.843137}, {0.094118, 0.094118, 0.094118}, {0.282353, 0.282353, 0.282353}, {0.470588, 0.470588, 0.470588}, {0.658824, 0.658824, 0.658824}, {0.847059, 0.847059, 0.847059}, {0.098039, 0.098039, 0.098039}, {0.286275, 0.286275, 0.286275}, {0.474510, 0.474510, 0.474510}, {0.662745, 0.662745, 0.662745}, {0.850980, 0.850980, 0.850980}, {0.101961, 0.101961, 0.101961}, {0.290196, 0.290196, 0.290196}, {0.478431, 0.478431, 0.478431}, {0.666667, 0.666667, 0.666667}, {0.854902, 0.854902, 0.854902}, {0.105882, 0.105882, 0.105882}, {0.294118, 0.294118, 0.294118}, {0.482353, 0.482353, 0.482353}, {0.670588, 0.670588, 0.670588}, {0.858824, 0.858824, 0.858824}, {0.109804, 0.109804, 0.109804}, {0.298039, 0.298039, 0.298039}, {0.486275, 0.486275, 0.486275}, {0.674510, 0.674510, 0.674510}, {0.862745, 0.862745, 0.862745}, {0.113725, 0.113725, 0.113725}, {0.301961, 0.301961, 0.301961}, {0.490196, 0.490196, 0.490196}, {0.678431, 0.678431, 0.678431}, {0.866667, 0.866667, 0.866667}, {0.117647, 0.117647, 0.117647}, {0.305882, 0.305882, 0.305882}, {0.494118, 0.494118, 0.494118}, {0.682353, 0.682353, 0.682353}, {0.870588, 0.870588, 0.870588}, {0.121569, 0.121569, 0.121569}, {0.309804, 0.309804, 0.309804}, {0.498039, 0.498039, 0.498039}, {0.686275, 0.686275, 0.686275}, {0.874510, 0.874510, 0.874510}, {0.125490, 0.125490, 0.125490}, {0.313726, 0.313726, 0.313726}, {0.501961, 0.501961, 0.501961}, {0.690196, 0.690196, 0.690196}, {0.878431, 0.878431, 0.878431}, {0.129412, 0.129412, 0.129412}, {0.317647, 0.317647, 0.317647}, {0.505882, 0.505882, 0.505882}, {0.694118, 0.694118, 0.694118}, {0.882353, 0.882353, 0.882353}, {0.133333, 0.133333, 0.133333}, {0.321569, 0.321569, 0.321569}, {0.509804, 0.509804, 0.509804}, {0.698039, 0.698039, 0.698039}, {0.886275, 0.886275, 0.886275}, {0.137255, 0.137255, 0.137255}, {0.325490, 0.325490, 0.325490}, {0.513726, 0.513726, 0.513726}, {0.701961, 0.701961, 0.701961}, {0.890196, 0.890196, 0.890196}, {0.141176, 0.141176, 0.141176}, {0.329412, 0.329412, 0.329412}, {0.517647, 0.517647, 0.517647}, {0.705882, 0.705882, 0.705882}, {0.894118, 0.894118, 0.894118}, {0.145098, 0.145098, 0.145098}, {0.333333, 0.333333, 0.333333}, {0.521569, 0.521569, 0.521569}, {0.709804, 0.709804, 0.709804}, {0.898039, 0.898039, 0.898039}, {0.149020, 0.149020, 0.149020}, {0.337255, 0.337255, 0.337255}, {0.525490, 0.525490, 0.525490}, {0.713726, 0.713726, 0.713726}, {0.901961, 0.901961, 0.901961}, {0.152941, 0.152941, 0.152941}, {0.341176, 0.341176, 0.341176}, {0.529412, 0.529412, 0.529412}, {0.717647, 0.717647, 0.717647}, {0.905882, 0.905882, 0.905882}, {0.156863, 0.156863, 0.156863}, {0.345098, 0.345098, 0.345098}, {0.533333, 0.533333, 0.533333}, {0.721569, 0.721569, 0.721569}, {0.909804, 0.909804, 0.909804}, {0.160784, 0.160784, 0.160784}, {0.349020, 0.349020, 0.349020}, {0.537255, 0.537255, 0.537255}, {0.725490, 0.725490, 0.725490}, {0.913725, 0.913725, 0.913725}, {0.164706, 0.164706, 0.164706}, {0.352941, 0.352941, 0.352941}, {0.541176, 0.541176, 0.541176}, {0.729412, 0.729412, 0.729412}, {0.917647, 0.917647, 0.917647}, {0.168627, 0.168627, 0.168627}, {0.356863, 0.356863, 0.356863}, {0.545098, 0.545098, 0.545098}, {0.733333, 0.733333, 0.733333}, {0.921569, 0.921569, 0.921569}, {0.172549, 0.172549, 0.172549}, {0.360784, 0.360784, 0.360784}, {0.549020, 0.549020, 0.549020}, {0.737255, 0.737255, 0.737255}, {0.925490, 0.925490, 0.925490}, {0.176471, 0.176471, 0.176471}, {0.364706, 0.364706, 0.364706}, {0.552941, 0.552941, 0.552941}, {0.741176, 0.741176, 0.741176}, {0.929412, 0.929412, 0.929412}, {0.180392, 0.180392, 0.180392}, {0.368627, 0.368627, 0.368627}, {0.556863, 0.556863, 0.556863}, {0.745098, 0.745098, 0.745098}, {0.933333, 0.933333, 0.933333}, {0.184314, 0.184314, 0.184314}, {0.372549, 0.372549, 0.372549}, {0.560784, 0.560784, 0.560784}, {0.749020, 0.749020, 0.749020}, {0.937255, 0.937255, 0.937255}};

  return readColorFromArray(v, f);
}

std::string ColorMap::getColorMapName() const { return nameInfo_; }
size_t ColorMap::getColorMapResolution() const { return resolution_; }
double ColorMap::getColorMapShift() const { return shift_; }
bool ColorMap::getColorMapInvert() const { return invert_; }
double ColorMap::getColorMapRescaleScale() const { return rescale_scale_; }
double ColorMap::getColorMapRescaleShift() const { return rescale_shift_; }


//TODO: heavily refactor
ColorMap_OSP_helper::ColorMap_OSP_helper(const std::string& name)
{
  opacityList.push_back(0.5);
  opacityList.push_back(0.5);
  if(name.compare("Rainbow") == 0){
    colorList.push_back(0); colorList.push_back(0);     colorList.push_back(1);
    colorList.push_back(0); colorList.push_back(0.75);  colorList.push_back(0.75);
    colorList.push_back(0); colorList.push_back(1);     colorList.push_back(0);
    colorList.push_back(1); colorList.push_back(0.5);   colorList.push_back(0);
    colorList.push_back(1); colorList.push_back(0);     colorList.push_back(0);
  }else if(name.compare("Old Rainbow") == 0){
    colorList.push_back(0); colorList.push_back(0);  colorList.push_back(1);
    colorList.push_back(0); colorList.push_back(1);  colorList.push_back(1);
    colorList.push_back(0); colorList.push_back(1);  colorList.push_back(0);
    colorList.push_back(1); colorList.push_back(1);  colorList.push_back(0);
    colorList.push_back(1); colorList.push_back(0);  colorList.push_back(0);
  }else if(name.compare("Blackbody") == 0){
    colorList.push_back(0); colorList.push_back(0);  colorList.push_back(0);
    colorList.push_back(1); colorList.push_back(0);  colorList.push_back(0);
    colorList.push_back(1); colorList.push_back(1);  colorList.push_back(0);
    colorList.push_back(1); colorList.push_back(1);  colorList.push_back(1);
  }else if(name.compare("Grayscale") == 0){
    colorList.push_back(0); colorList.push_back(0);     colorList.push_back(0);
    colorList.push_back(1); colorList.push_back(1);     colorList.push_back(1);
  }else if(name.compare("Orange,Black,Lime") == 0){
    colorList.push_back(1); colorList.push_back(0.5); colorList.push_back(0);
    colorList.push_back(0); colorList.push_back(0);   colorList.push_back(0);
    colorList.push_back(0); colorList.push_back(1);   colorList.push_back(0);
  }else if(name.compare("Darkhue") == 0){
    colorList.push_back(0); colorList.push_back(0);   colorList.push_back(0);
    colorList.push_back(0); colorList.push_back(0);   colorList.push_back(0.333333f);
    colorList.push_back(0.5); colorList.push_back(0); colorList.push_back(0.5);
    colorList.push_back(1); colorList.push_back(0);   colorList.push_back(0);
    colorList.push_back(1); colorList.push_back(0);     colorList.push_back(0.25f*2.6666666f);
  }else if(name.compare("BP Seismic") == 0){
    colorList.push_back(0); colorList.push_back(0);  colorList.push_back(1);
    colorList.push_back(1); colorList.push_back(1);  colorList.push_back(1);
    colorList.push_back(1); colorList.push_back(0);  colorList.push_back(0);
  }
}
