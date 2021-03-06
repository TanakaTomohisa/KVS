/*****************************************************************************/
/**
 *  @file   GL.cpp
 *  @author Naohisa Sakamoto
 */
/*----------------------------------------------------------------------------
 *
 *  Copyright (c) Visualization Laboratory, Kyoto University.
 *  All rights reserved.
 *  See http://www.viz.media.kyoto-u.ac.jp/kvs/copyright/ for details.
 *
 *  $Id$
 */
/*****************************************************************************/
#include "GL.h"
#include <string>
#include <kvs/Message>
#include <kvs/IgnoreUnusedVariable>


namespace kvs
{

namespace GL
{

namespace detail
{

bool HasError( const char* file, const int line, const char* func, const char* command )
{
#if defined( KVS_ENABLE_OPENGL )
    GLenum error = glGetError();
    if ( error == GL_NO_ERROR ) return false;

    // Output message tag.
    std::string message_tag( "KVS GL ERROR" );
    std::cerr << KVS_MESSAGE_SET_COLOR( KVS_MESSAGE_RED );
    std::cerr << message_tag;
    std::cerr << KVS_MESSAGE_RESET_COLOR;

    // Output message with an error string.
    std::string error_string;
#if defined( KVS_ENABLE_GLU )
    const GLubyte* c = gluErrorString( error );
    while ( *c ) { error_string += *c++; }
#else
    error_string = "Unknown error. (GLU is not enabled)";
#endif
    std::cerr << ": " << error_string << std::endl;
    std::cerr << "\t" << "FILE: " << file << " (" << line << ")" << std::endl;
    std::cerr << "\t" << "FUNC: " << func << std::endl;
    std::cerr << "\t" << "GL COMMAND: " << command << std::endl;

    return true;
#else
    kvs::IgnoreUnusedVariable( file );
    kvs::IgnoreUnusedVariable( line );
    kvs::IgnoreUnusedVariable( func );
    kvs::IgnoreUnusedVariable( command );
    return false;
#endif
}

} // end of namespace detail

} // end of namespace GL

} // end of namespace kvs
