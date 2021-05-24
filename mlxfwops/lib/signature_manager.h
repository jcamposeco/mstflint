/*                                                                         
 * Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.   
 *                                                                          
 * This software is available to you under a choice of one of two           
 * licenses.  You may choose to be licensed under the terms of the GNU      
 * General Public License (GPL) Version 2, available from the file          
 * COPYING in the main directory of this source tree, or the                
 * OpenIB.org BSD license below:                                            
 *                                                                          
 *     Redistribution and use in source and binary forms, with or           
 *     without modification, are permitted provided that the following      
 *     conditions are met:                                                  
 *                                                                          
 *      - Redistributions of source code must retain the above              
 *        copyright notice, this list of conditions and the following       
 *        disclaimer.                                                       
 *                                                                          
 *      - Redistributions in binary form must reproduce the above           
 *        copyright notice, this list of conditions and the following       
 *        disclaimer in the documentation and/or other materials            
 *        provided with the distribution.                                   
 *                                                                          
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND                    
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS      
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN       
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN        
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE         
 * SOFTWARE.                                                                
 *                                                                          
 */                                                                         
 

#pragma once
#include <stdio.h>
#include "flint_base.h"
#include "mtcr.h"

class Fs3Operations;
class Flash;


class ISignatureManager : public FlintErrMsg
{
public:
    virtual bool AddSignature(mfile* mf, Fs3Operations* imageOps, Flash *f, u_int32_t imageOffset) = 0;
    virtual bool GetSecureBootInfo() = 0;
    virtual bool IsLifeCycleSupported() = 0;
    virtual bool IsCableQuerySupported() = 0;
    virtual ~ISignatureManager() {}
};

class AbstractSignatureManager : public ISignatureManager {
public:
    AbstractSignatureManager() {}
    virtual ~AbstractSignatureManager() {}
    virtual bool GetSecureBootInfo()
    {
        return false;
    }
    virtual bool IsCableQuerySupported()
    {
        return false;
    }
    virtual bool AddSignature(mfile*, Fs3Operations*, Flash*, u_int32_t)
    {
        return true;
    }
    virtual bool IsLifeCycleSupported()
    {
        return false;
    }
};

class FwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    FwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~FwOperationsSignatureManager() {}
};

class BluefieldFwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    BluefieldFwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~BluefieldFwOperationsSignatureManager() {}
    virtual bool AddSignature(mfile* mf, Fs3Operations* imageOps, Flash *f, u_int32_t imageOffset);
};


class ConnectX6FwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    ConnectX6FwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~ConnectX6FwOperationsSignatureManager() {}
    virtual bool AddSignature(mfile* mf, Fs3Operations* imageOps, Flash *f, u_int32_t imageOffset);
    virtual bool IsLifeCycleSupported();
    virtual bool IsCableQuerySupported()
    {
        return true;
    }
};

class RavenSwitchSignatureManager : public AbstractSignatureManager
{
public:
    RavenSwitchSignatureManager() : AbstractSignatureManager() {}
    virtual ~RavenSwitchSignatureManager() {}
    virtual bool IsCableQuerySupported()
    {
        return true;
    }
};

class ConnectX6DXFwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    ConnectX6DXFwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~ConnectX6DXFwOperationsSignatureManager() {}
    virtual bool GetSecureBootInfo()
    {
        return true;
    }
};

class ConnectX6LXFwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    ConnectX6LXFwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~ConnectX6LXFwOperationsSignatureManager() {}
    virtual bool GetSecureBootInfo()
    {
        return true;
    }
};

class ConnectX7FwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    ConnectX7FwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~ConnectX7FwOperationsSignatureManager() {}
    virtual bool GetSecureBootInfo()
    {
        return true;
    }
};

class Bluefield2FwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    Bluefield2FwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~Bluefield2FwOperationsSignatureManager() {}
    virtual bool GetSecureBootInfo()
    {
        return true;
    }
};

class Bluefield3FwOperationsSignatureManager : public AbstractSignatureManager
{
public:
    Bluefield3FwOperationsSignatureManager() : AbstractSignatureManager() {}
    virtual ~Bluefield3FwOperationsSignatureManager() {}
    virtual bool GetSecureBootInfo()
    {
        return true;
    }
};

class GearBoxSignatureManager : public AbstractSignatureManager
{
public:
    GearBoxSignatureManager() : AbstractSignatureManager() {}
    virtual ~GearBoxSignatureManager() {}
    virtual bool AddSignature(mfile*, Fs3Operations*, Flash*, u_int32_t)
    {
        return false;
    }
};



