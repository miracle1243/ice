// **********************************************************************
//
// Copyright (c) 2003-2016 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************

#ifndef ICE_FACTORYTABLEINIT_H
#define ICE_FACTORYTABLEINIT_H

#include <Ice/FactoryTable.h>
#include <Ice/DefaultValueFactory.h>

namespace IceInternal
{

class ICE_API FactoryTableInit
{
public:

    FactoryTableInit();
    ~FactoryTableInit();
};

static FactoryTableInit factoryTableInitializer;    // Dummy variable to force initialization of factoryTable

extern ICE_API FactoryTable* factoryTable;


class ICE_API CompactIdInit
{
public:

    CompactIdInit(const char*, int);
    ~CompactIdInit();

private:

    const int _compactId;
};

template<class E>
class DefaultUserExceptionFactoryInit
{
public:

    DefaultUserExceptionFactoryInit(const char* tId) : typeId(tId)
    {
        factoryTable->addExceptionFactory(typeId, new DefaultUserExceptionFactory<E>(typeId));
    }

    ~DefaultUserExceptionFactoryInit()
    {
        factoryTable->removeExceptionFactory(typeId);
    }

    const ::std::string typeId;
};

template<class O>
class DefaultValueFactoryInit
{
public:

    DefaultValueFactoryInit(const char* tId) : typeId(tId)
    {
#ifdef ICE_CPP11_MAPPING
        factoryTable->addValueFactory(typeId,
                                      [](const std::string&)
                                      {
                                          return ::std::make_shared<O>();
                                      });
#else
        factoryTable->addValueFactory(typeId, new DefaultValueFactory<O>(typeId));
#endif
    }

    ~DefaultValueFactoryInit()
    {
        factoryTable->removeValueFactory(typeId);
    }

    const ::std::string typeId;
};

}

#endif
