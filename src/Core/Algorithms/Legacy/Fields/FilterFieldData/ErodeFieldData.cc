/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2020 Scientific Computing and Imaging Institute,
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


#include <Core/Algorithms/Legacy/Fields/FilterFieldData/ErodeFieldData.h>

#include <Core/Algorithms/Base/AlgorithmVariableNames.h>
#include <Core/Algorithms/Base/AlgorithmPreconditions.h>
#include <Core/Datatypes/DenseMatrix.h>
#include <Core/Datatypes/SparseRowMatrix.h>
#include <Core/Datatypes/Legacy/Field/FieldInformation.h>
#include <Core/GeometryPrimitives/Vector.h>
#include <Core/GeometryPrimitives/Point.h>
#include <Core/Datatypes/MatrixTypeConversions.h>
#include <Core/Datatypes/Legacy/Field/VMesh.h>
#include <Core/Datatypes/Legacy/Field/VField.h>
#include <Core/Datatypes/Matrix.h>
#include <Core/Datatypes/Legacy/Field/Mesh.h>
#include <Core/Datatypes/Legacy/Field/Field.h>
#include <Core/Datatypes/Legacy/Field/FieldInformation.h>
#include <Core/GeometryPrimitives/Vector.h>
#include <Core/Algorithms/Base/AlgorithmVariableNames.h>


using namespace SCIRun;
using namespace SCIRun::Core::Datatypes;
using namespace SCIRun::Core::Algorithms;
using namespace SCIRun::Core::Utility;
using namespace SCIRun::Core::Algorithms::Fields;
using namespace SCIRun::Core::Geometry;

ErodeFieldDataAlgo::ErodeFieldDataAlgo()
{
  addParameter(Variables::MaxIterations, 2);
}

namespace detail {

template<class DATA>
bool ErodeFieldDataNodeV(const AlgorithmBase* algo,
                           FieldHandle input,
                           FieldHandle& output);

template<class DATA>
bool ErodeFieldDataElemV(const AlgorithmBase* algo,
                          FieldHandle input,
                          FieldHandle& output);
}

bool ErodeFieldDataAlgo::runImpl(FieldHandle input, FieldHandle& output) const
{
  ScopedAlgorithmStatusReporter asr(this, "ErodeFieldData");

  // Check whether we have an input field
  if (!input)
  {
    error("No input field");
    return (false);
  }

  // Figure out what the input type and output type have to be
  FieldInformation fi(input);

  if (fi.is_nonlinear())
  {
    error("This function has not yet been defined for non-linear elements");
    return (false);
  }

  if (fi.is_nodata())
  {
    error("There is no data defined in the input field");
    return (false);
  }

  if (!fi.is_scalar())
  {
    error("The field data is not scalar data");
    return (false);
  }

  using namespace detail;
  if (fi.is_constantdata())
  {
    if (fi.is_char()) return(ErodeFieldDataElemV<char>(this,input,output));
    if (fi.is_unsigned_char()) return(ErodeFieldDataElemV<unsigned char>(this,input,output));
    if (fi.is_short()) return(ErodeFieldDataElemV<short>(this,input,output));
    if (fi.is_unsigned_short()) return(ErodeFieldDataElemV<unsigned short>(this,input,output));
    if (fi.is_int()) return(ErodeFieldDataElemV<int>(this,input,output));
    if (fi.is_unsigned_int()) return(ErodeFieldDataElemV<unsigned int>(this,input,output));
    if (fi.is_longlong()) return(ErodeFieldDataElemV<long long>(this,input,output));
    if (fi.is_unsigned_longlong()) return(ErodeFieldDataElemV<unsigned long long>(this,input,output));
    if (fi.is_float()) return(ErodeFieldDataElemV<float>(this,input,output));
    if (fi.is_double()) return(ErodeFieldDataElemV<double>(this,input,output));
  }
  else if (fi.is_lineardata())
  {
    if (fi.is_char()) return(ErodeFieldDataNodeV<char>(this,input,output));
    if (fi.is_unsigned_char()) return(ErodeFieldDataNodeV<unsigned char>(this,input,output));
    if (fi.is_short()) return(ErodeFieldDataNodeV<short>(this,input,output));
    if (fi.is_unsigned_short()) return(ErodeFieldDataNodeV<unsigned short>(this,input,output));
    if (fi.is_int()) return(ErodeFieldDataNodeV<int>(this,input,output));
    if (fi.is_unsigned_int()) return(ErodeFieldDataNodeV<unsigned int>(this,input,output));
    if (fi.is_longlong()) return(ErodeFieldDataNodeV<long long>(this,input,output));
    if (fi.is_unsigned_longlong()) return(ErodeFieldDataNodeV<unsigned long long>(this,input,output));
    if (fi.is_float()) return(ErodeFieldDataNodeV<float>(this,input,output));
    if (fi.is_double()) return(ErodeFieldDataNodeV<double>(this,input,output));  }

  return (false);
}


template <class DATA>
bool detail::ErodeFieldDataNodeV(const AlgorithmBase *algo, FieldHandle input1, FieldHandle& output)
{
  int num_iter = algo->get(Variables::MaxIterations).toInt();

  /// Create output field
  output.reset(input1->deep_clone());

  if (!output)
  {
    algo->error("Could not allocate output field");
    return (false);
  }

  FieldHandle buffer(input1->deep_clone());

  if (!buffer)
  {
    algo->error("Could not allocate buffer field");
    return (false);
  }

  VMesh* vmesh = output->vmesh();
  vmesh->synchronize(Mesh::NODE_NEIGHBORS_E);

  VMesh::Node::size_type sz;
  vmesh->size(sz);

  DATA* idata = reinterpret_cast<DATA*>(buffer->vfield()->fdata_pointer());
  DATA* odata = reinterpret_cast<DATA*>(output->vfield()->fdata_pointer());

  for (int p=0; p <num_iter; p++)
  {
    VMesh::Node::array_type nodes;
    DATA val, nval;

    for(VMesh::Node::index_type idx=0; idx<sz; ++idx)
    {
      vmesh->get_neighbors(nodes,idx);
      val = idata[idx];

      for (size_t j=0; j<nodes.size(); j++)
      {
        nval = idata[nodes[j]];
        if (nval < val) val = nval;
      }
      odata[idx] = val;
    }

    buffer->vfield()->copy_values(output->vfield());
  }

  return (true);
}


template <class DATA>
bool detail::ErodeFieldDataElemV(const AlgorithmBase *algo, FieldHandle input1, FieldHandle& output)
{
  int num_iter = algo->get(Variables::MaxIterations).toInt();

  /// Create output field
  output.reset(input1->deep_clone());

  if (!output)
  {
    algo->error("Could not allocate output field");
    return (false);
  }

  FieldHandle buffer(input1->deep_clone());

  if (!buffer)
  {
    algo->error("Could not allocate buffer field");
    return (false);
  }

  VMesh* vmesh = output->vmesh();
  vmesh->synchronize(Mesh::ELEM_NEIGHBORS_E);

  VMesh::Elem::size_type sz;
  vmesh->size(sz);

  DATA* idata = reinterpret_cast<DATA*>(buffer->vfield()->fdata_pointer());
  DATA* odata = reinterpret_cast<DATA*>(output->vfield()->fdata_pointer());

  for (int p=0; p <num_iter; p++)
  {
    VMesh::Elem::array_type elems;
    DATA val, nval;

    for(VMesh::Elem::index_type idx=0; idx<sz; ++idx)
    {
      vmesh->get_neighbors(elems,idx);
      val = idata[idx];

      for (size_t j=0; j<elems.size(); j++)
      {
        nval = idata[elems[j]];
        if (nval < val) val = nval;
      }
      odata[idx] = val;
    }

    buffer->vfield()->copy_values(output->vfield());
  }

  return (true);
}

AlgorithmOutput ErodeFieldDataAlgo::run(const AlgorithmInput& input) const
{
  auto field = input.get<Field>(Variables::InputField);
  FieldHandle outputField;

  if (!runImpl(field, outputField))
    THROW_ALGORITHM_PROCESSING_ERROR("False returned on legacy run call.");
  AlgorithmOutput output;
  output[Variables::OutputField] = outputField;
  return output;
}
