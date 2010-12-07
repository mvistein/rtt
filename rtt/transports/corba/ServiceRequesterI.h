/***************************************************************************
  tag: The SourceWorks  Tue Sep 7 00:55:18 CEST 2010  ServiceRequesterI.h

                        ServiceRequesterI.h -  description
                           -------------------
    begin                : Tue September 07 2010
    copyright            : (C) 2010 The SourceWorks
    email                : peter@thesourceworks.com

 ***************************************************************************
 *   This library is free software; you can redistribute it and/or         *
 *   modify it under the terms of the GNU General Public                   *
 *   License as published by the Free Software Foundation;                 *
 *   version 2 of the License.                                             *
 *                                                                         *
 *   As a special exception, you may use this file as part of a free       *
 *   software library without restriction.  Specifically, if other files   *
 *   instantiate templates or use macros or inline functions from this     *
 *   file, or you compile this file and link it with other files to        *
 *   produce an executable, this file does not by itself cause the         *
 *   resulting executable to be covered by the GNU General Public          *
 *   License.  This exception does not however invalidate any other        *
 *   reasons why the executable file might be covered by the GNU General   *
 *   Public License.                                                       *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     *
 *   Lesser General Public License for more details.                       *
 *                                                                         *
 *   You should have received a copy of the GNU General Public             *
 *   License along with this library; if not, write to the Free Software   *
 *   Foundation, Inc., 59 Temple Place,                                    *
 *   Suite 330, Boston, MA  02111-1307  USA                                *
 *                                                                         *
 ***************************************************************************/


// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html

// TAO_IDL - Generated from 
// ../../../ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1133

#ifndef ORO_CORBA_SERVICEREQUESTERI_H_
#define ORO_CORBA_SERVICEREQUESTERI_H_

#include "corba.h"
#ifdef CORBA_IS_TAO
#include "ServiceRequesterS.h"
#else
#include "ServiceRequesterC.h"
#endif

#include "../../ServiceRequester.hpp"
#include <map>

#if !defined (ACE_LACKS_PRAGMA_ONCE)
#pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

class  RTT_corba_CServiceRequester_i
    : public virtual POA_RTT::corba::CServiceRequester, public virtual PortableServer::RefCountServantBase
{
protected:
    RTT::ServiceRequester* mservice;
    std::map<std::string, std::pair<RTT::corba::CServiceRequester_var, PortableServer::ServantBase_var> > mrequests;
    PortableServer::POA_var mpoa;
public:
  // Constructor 
    RTT_corba_CServiceRequester_i (RTT::ServiceRequester* service, PortableServer::POA_ptr poa);
  
  // Destructor 
  virtual ~RTT_corba_CServiceRequester_i (void);
  
  virtual RTT::corba::CServiceRequester_ptr activate_this() {
      PortableServer::ObjectId_var oid = mpoa->activate_object(this); // ref count=2
      //_remove_ref(); // ref count=1
      return _this();
  }

  virtual
  char * getRequestName (
      void);
  
  virtual
  ::RTT::corba::CRequestNames * getRequestNames (
      void);
  
  virtual
  ::RTT::corba::COperationCallerNames * getOperationCallerNames (
      void);
  
  virtual
  ::RTT::corba::CServiceRequester_ptr getRequest (
      const char * name);
  
  virtual
  ::CORBA::Boolean hasRequest (
      const char * name);
  
  virtual
  ::CORBA::Boolean connectTo (
      ::RTT::corba::CService_ptr svc);
  
  virtual
  ::CORBA::Boolean connectCallerTo (
      const char * name,
      ::RTT::corba::CService_ptr svc);

  virtual
  ::CORBA::Boolean disconnectCaller (
      const char * name);

  virtual
  ::CORBA::Boolean callerReady (
      const char * name);

  virtual
  ::CORBA::Boolean ready (
      void);
  
  virtual
  void disconnect (
      void);
};


#endif /* SERVICEREQUESTERI_H_  */

