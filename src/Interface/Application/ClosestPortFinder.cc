/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2012 Scientific Computing and Imaging Institute,
   University of Utah.

   License for the specific language governing rights and limitations under
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

#include <QtGui>
#include <boost/range/join.hpp>
#include <Interface/Application/ClosestPortFinder.h>
#include <Interface/Application/ModuleProxyWidget.h>
#include <Interface/Application/ModuleWidget.h>
#include <Interface/Application/Port.h>

using namespace SCIRun::Gui;

ClosestPortFinder::ClosestPortFinder(QGraphicsScene* scene) : scene_(scene) {}

PortWidget* ClosestPortFinder::closestPort(const QPointF& pos)
{
  Q_FOREACH (QGraphicsItem* item, scene_->items(pos))
  {
    if (auto mpw = dynamic_cast<ModuleProxyWidget*>(item))
    {
      auto overModule = mpw->getModuleWidget();

      auto ports = boost::join(overModule->getInputPorts(), overModule->getOutputPorts());
      return *std::min_element(ports.begin(), ports.end(), [=](PortWidget* lhs, PortWidget* rhs) {return lessPort(pos, lhs, rhs); });
    }
  }
  return 0;
}

int ClosestPortFinder::distance(const QPointF& pos, PortWidget* port) const
{
  return (pos - port->position()).manhattanLength();
}

bool ClosestPortFinder::lessPort(const QPointF& pos, PortWidget* lhs, PortWidget* rhs) const
{
  return distance(pos, lhs) < distance(pos, rhs);
}

