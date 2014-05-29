/*
   For more information, please see: http://software.sci.utah.edu

   The MIT License

   Copyright (c) 2009 Scientific Computing and Imaging Institute,
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

#ifndef SCI_project_GenericIEPlugin_h
#define SCI_project_GenericIEPlugin_h 1

#include <Core/Logging/LoggerFwd.h>
#include <Core/Thread/Mutex.h>
#include <map>
#include <Core/ImportExport/share.h>

namespace SCIRun {

//----------------------------------------------------------------------
template <class Data>
class SCISHARE GenericIEPluginInterface
{
public:
  virtual ~GenericIEPluginInterface() {}
  virtual std::string pluginname() const = 0;
  virtual std::string fileExtension() const = 0;
  virtual std::string fileMagic() const = 0;

  virtual boost::shared_ptr<Data> readFile(const std::string& filename, Core::Logging::Log& log) const = 0;
  virtual bool writeFile(boost::shared_ptr<Data> f, const std::string& filename, Core::Logging::Log& log) const = 0;
  virtual bool equals(const GenericIEPluginInterface<Data>& other) const = 0;
};

template <class Data>
bool operator==(const GenericIEPluginInterface<Data>& lhs, const GenericIEPluginInterface<Data>& rhs)
{
  return lhs.equals(rhs);
}

template <class Data>
bool operator!=(const GenericIEPluginInterface<Data>& lhs, const GenericIEPluginInterface<Data>& rhs)
{
  return !(lhs == rhs);
}

template <class Data>
class SCISHARE GenericIEPluginManager 
{
public:
  static Core::Thread::Mutex& getLock();
  typedef std::map<std::string, GenericIEPluginInterface<Data>*> PluginMap;
  static PluginMap& getMap();
  static void createMap();
  static void destroyMap();

  size_t numPlugins() const;
  void get_importer_list(std::vector<std::string>& results) const;
  void get_exporter_list(std::vector<std::string>& results) const;
  GenericIEPluginInterface<Data>* get_plugin(const std::string& name) const;
private:
  static Core::Thread::Mutex lock_;
  static PluginMap* pluginTable_;
};


template <class Data>
Core::Thread::Mutex GenericIEPluginManager<Data>::lock_("fieldIE");

template <class Data>
typename GenericIEPluginManager<Data>::PluginMap* GenericIEPluginManager<Data>::pluginTable_ = 0;

template <class Data>
Core::Thread::Mutex& GenericIEPluginManager<Data>::getLock()
{
  return lock_;
}

template <class Data>
typename GenericIEPluginManager<Data>::PluginMap& GenericIEPluginManager<Data>::getMap()
{
  if (!pluginTable_)
    createMap();
  return *pluginTable_;
}

template <class Data>
void GenericIEPluginManager<Data>::createMap()
{
  if (!pluginTable_)
  {
    pluginTable_ = new typename GenericIEPluginManager<Data>::PluginMap();
  }
}

template <class Data>
size_t GenericIEPluginManager<Data>::numPlugins() const
{
  return pluginTable_ ? pluginTable_->size() : 0;
}

template <class Data>
void GenericIEPluginManager<Data>::get_importer_list(std::vector<std::string>& results) const
{
  if (!pluginTable_) 
  {
    return;
  }

  Core::Thread::Guard s(lock_.get());
  auto itr = pluginTable_->begin();
  while (itr != pluginTable_->end())
  {
    results.push_back((*itr).first);
    ++itr;
  }
}

template <class Data>
void GenericIEPluginManager<Data>::get_exporter_list(std::vector<std::string>& results) const
{
  if (!pluginTable_) 
  {
    return;
  }

  Core::Thread::Guard s(lock_.get());
  auto itr = pluginTable_->begin();
  while (itr != pluginTable_->end())
  {
    results.push_back((*itr).first);
    ++itr;
  }
}

template <class Data>
GenericIEPluginInterface<Data>* GenericIEPluginManager<Data>::get_plugin(const std::string &name) const
{
  if (!pluginTable_)
    return 0;

  Core::Thread::Guard s(lock_.get());
  // Should check for invalid name.
  auto loc = pluginTable_->find(name);
  if (loc == pluginTable_->end())
  {
    return 0;
  }
  else
  {
    return loc->second;
  }
}

template <class Data>
void GenericIEPluginManager<Data>::destroyMap()
{
  delete pluginTable_;
  pluginTable_ = 0;
}

}

#endif
