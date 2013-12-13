////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2013 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_ALCHECK_HPP
#define SFML_ALCHECK_HPP
#ifndef NEPHILIM_ANDROID

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.hpp>
#include <iostream>
#include <string>
#include <AL/al.h>
#include <AL/alc.h>


namespace sf
{
namespace priv
{
////////////////////////////////////////////////////////////
/// Let's define a macro to quickly check every OpenAL API calls
////////////////////////////////////////////////////////////
#ifdef SFML_DEBUG

    // If in debug mode, perform a test on every call
    #define alCheck(Func) ((Func), priv::alCheckError(__FILE__, __LINE__))

#else

    // Else, we don't add any overhead
    #define alCheck(Func) (Func)

#endif


////////////////////////////////////////////////////////////
/// Check the last OpenAL error
///
/// \param file Source file where the call is located
/// \param line Line number of the source file where the call is located
///
////////////////////////////////////////////////////////////
void alCheckError(const std::string& file, unsigned int line);

////////////////////////////////////////////////////////////
/// Make sure that OpenAL is initialized
///
////////////////////////////////////////////////////////////
void ensureALInit();

} // namespace priv

} // namespace sf

#endif
#endif // SFML_ALCHECK_HPP
