/// -*- tab-width: 4; c-basic-offset: 4; indent-tabs-mode: t -*-
///
/// \file   rendererfactory.cpp
/// \author Martin Reddy
/// \brief  A factory object to create IRenderer instances.
///
/// Copyright (c) 2010, Martin Reddy. All rights reserved.
/// Distributed under the X11/MIT License. See LICENSE.txt.
/// See http://APIBook.com/ for the latest version.
///

/**
 1/30/17 -- Tal
 -- using nullptr instead of NULL
 -- switched to auto for mRenders.find()
   see Tweak_Explainations.md (https://github.com/tlanc007/APIBookTweaks/blob/master/Tweak_Explainations.md#auto)
 -- switched to unique_ptr/make_unique rather than needing to
   use new() and remembering to call delete.
   see Tweak_Explainations.md (https://github.com/tlanc007/APIBookTweaks/blob/master/Tweak_Explainations.md#smartpointer)
   see Tweak_Explainations.md (https://github.com/tlanc007/APIBookTweaks/blob/master/Tweak_Explainations.md#makeshared)
 
 **/

#include <iostream>

#include "rendererfactory.h"

// instantiate the static variable in RendererFactory
RendererFactory::CallbackMap RendererFactory::mRenderers;

void RendererFactory::RegisterRenderer(const std::string &type,
                                       CreateCallback cb)
{
    mRenderers[type] = cb;
}

void RendererFactory::UnregisterRenderer(const std::string &type)
{
    mRenderers.erase(type);
}

RendererFactory::UniqueIRendererPtr RendererFactory::CreateRenderer (const std::string &type)
{
    auto found {mRenderers.find(type) };
    if (found != std::end (mRenderers) )
    {
        // call the creation callback to construct this derived type
        return (found->second)();
    }

    return nullptr;
}
