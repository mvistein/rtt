/***************************************************************************
  tag: Peter Soetens  Tue Dec 21 22:43:07 CET 2004  PeerParser.cxx 

                        PeerParser.cxx -  description
                           -------------------
    begin                : Tue December 21 2004
    copyright            : (C) 2004 Peter Soetens
    email                : peter.soetens@mech.kuleuven.ac.be
 
 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU Lesser General Public            *
 *   License as published by the Free Software Foundation; either          *
 *   version 2.1 of the License, or (at your option) any later version.    *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/
 
 

#include "execution/PeerParser.hpp"
#include "execution/parser-debug.hpp"
#include "execution/parse_exception.hpp"
#include "execution/TaskContext.hpp"
#include "execution/parser-types.hpp"

#include <boost/bind.hpp>
#include <iostream>

namespace ORO_Execution
{
    using boost::bind;
    using namespace detail;
    using namespace std;

    namespace {
        enum PeerErrors { peer_not_found };
        guard<PeerErrors> my_guard;

        /**
         * set by locatepeer, read by handle_no_peer
         */
        static std::ptrdiff_t advance_on_error = 0;
    }

    error_status<> handle_no_peer(scanner_t const& scan, parser_error<PeerErrors, iter_t>&e )
    {
        //std::cerr<<"Returning accept, advance "<<advance_on_error<<std::endl;
        scan.first += advance_on_error;
        // ok, got as far as possible, _peer contains the furthest we got.
        return error_status<>( error_status<>::accept, advance_on_error  );
    }

        void PeerParser::done()
        {
            //std::cerr<<"Peerparser operating in "<<  context->getName()<<std::endl;

            // if size() > 1, it must be a peer 
            while ( callqueue.size() > 0 && _peer->hasPeer( callqueue.front() ) ) {
                //std::cerr<< _peer->getName() <<" has peer " << callqueue.front()<<std::endl;
                _peer = _peer->getPeer( callqueue.front() );
                callqueue.pop();
            }

            // Something went wrong, a subtask was not found
            if ( callqueue.size() > 1 ) {
                // print to user the mismatch :
                std::string object = callqueue.front();
                while ( !callqueue.empty() )
                    callqueue.pop();
                iter_t begin;
                throw_(begin, "From TaskContext '"+context->getName()+"': Task '"+_peer->getName()+"' has no task or object '"+object+"'." );
            }
            if ( callqueue.empty() )
                callqueue.push("this");

            mcurobject = callqueue.front();
            callqueue.pop();
        }

        PeerParser::PeerParser(TaskContext* c)
            : mcurobject("this"),context(c), _peer(context)
        {
            BOOST_SPIRIT_DEBUG_RULE( peerpath );
            BOOST_SPIRIT_DEBUG_RULE( peerlocator );
            peerpath = 
                ( +(commonparser.notassertingidentifier >> ".")[bind( &PeerParser::seenobjectname, this, _1, _2 ) ] )[bind(&PeerParser::done, this)];

            // find as far as possible a peer without throwing an exception
            // outside our interface
            peerlocator =
                !(my_guard
                  ( +((commonparser.notassertingidentifier >> ".")[bind( &PeerParser::locatepeer, this, _1, _2 ) ]))
                [ &handle_no_peer ]);
        }

    TaskContext* PeerParser::setContext( TaskContext* tc )
    {
        //std::cerr<< "Peers: context: "<< tc->getName()<<std::endl;
        TaskContext* ret = context;
        context = tc;
        this->reset();
        return ret;
    }

    void PeerParser::reset()
    {
        _peer = context;
        mcurobject = "this";
        advance_on_error = 0;
    }

    void PeerParser::seenobjectname( iter_t begin, iter_t end )
    {
        std::string name( begin, end );
        name.erase( name.length() -1  ); // compensate for extra "."
        callqueue.push( name );
        //std::cerr << "seen " << name <<std::endl;
    }

    void PeerParser::locatepeer( iter_t begin, iter_t end )
    {
        std::string name( begin, end );
        name.erase( name.length() -1  ); // compensate for extra "."

        if ( _peer->hasPeer( name ) ) {
            _peer = _peer->getPeer( name );
            advance_on_error += end - begin;

            //cout << "PP located "<<name <<endl;
        }
        else {
            //cout << "PP failed "<<name <<endl;
            // store object name for higher level access.
            // do not consume it though.
            mcurobject = name;
            throw_(begin, peer_not_found );
        }
    }

    rule_t& PeerParser::parser()
    {
        return peerpath;
    }

    rule_t& PeerParser::locator()
    {
        return peerlocator;
    }

    TaskContext* PeerParser::peer()
    {
        return _peer;
    }

    std::string PeerParser::object()
    {
        return mcurobject;
    }

}
            
