/*****************************************************************************
*
* Copyright (c) 2000 - 2012, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#ifndef INTERNALRESAMPLEATTRIBUTES_H
#define INTERNALRESAMPLEATTRIBUTES_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>


// ****************************************************************************
// Class: InternalResampleAttributes
//
// Purpose:
//    This class contains attributes to specify a resampling.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class STATE_API InternalResampleAttributes : public AttributeSubject
{
public:
    // These constructors are for objects of this class
    InternalResampleAttributes();
    InternalResampleAttributes(const InternalResampleAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    InternalResampleAttributes(private_tmfs_t tmfs);
    InternalResampleAttributes(const InternalResampleAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~InternalResampleAttributes();

    virtual InternalResampleAttributes& operator = (const InternalResampleAttributes &obj);
    virtual bool operator == (const InternalResampleAttributes &obj) const;
    virtual bool operator != (const InternalResampleAttributes &obj) const;
private:
    void Init();
    void Copy(const InternalResampleAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectArbitratorVarName();

    // Property setting methods
    void SetUseTargetVal(bool useTargetVal_);
    void SetTargetVal(int targetVal_);
    void SetWidth(int width_);
    void SetHeight(int height_);
    void SetDepth(int depth_);
    void SetPrefersPowersOfTwo(bool prefersPowersOfTwo_);
    void SetDefaultVal(float defaultVal_);
    void SetUseBounds(bool useBounds_);
    void SetMinX(double minX_);
    void SetMinY(double minY_);
    void SetMinZ(double minZ_);
    void SetMaxX(double maxX_);
    void SetMaxY(double maxY_);
    void SetMaxZ(double maxZ_);
    void SetUseArbitrator(bool useArbitrator_);
    void SetArbitratorLessThan(bool arbitratorLessThan_);
    void SetArbitratorVarName(const std::string &arbitratorVarName_);
    void SetDistributedResample(bool distributedResample_);

    // Property getting methods
    bool              GetUseTargetVal() const;
    int               GetTargetVal() const;
    int               GetWidth() const;
    int               GetHeight() const;
    int               GetDepth() const;
    bool              GetPrefersPowersOfTwo() const;
    float             GetDefaultVal() const;
    bool              GetUseBounds() const;
    double            GetMinX() const;
    double            GetMinY() const;
    double            GetMinZ() const;
    double            GetMaxX() const;
    double            GetMaxY() const;
    double            GetMaxZ() const;
    bool              GetUseArbitrator() const;
    bool              GetArbitratorLessThan() const;
    const std::string &GetArbitratorVarName() const;
          std::string &GetArbitratorVarName();
    bool              GetDistributedResample() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;


    // IDs that can be used to identify fields in case statements
    enum {
        ID_useTargetVal = 0,
        ID_targetVal,
        ID_width,
        ID_height,
        ID_depth,
        ID_prefersPowersOfTwo,
        ID_defaultVal,
        ID_useBounds,
        ID_minX,
        ID_minY,
        ID_minZ,
        ID_maxX,
        ID_maxY,
        ID_maxZ,
        ID_useArbitrator,
        ID_arbitratorLessThan,
        ID_arbitratorVarName,
        ID_distributedResample,
        ID__LAST
    };

private:
    bool        useTargetVal;
    int         targetVal;
    int         width;
    int         height;
    int         depth;
    bool        prefersPowersOfTwo;
    float       defaultVal;
    bool        useBounds;
    double      minX;
    double      minY;
    double      minZ;
    double      maxX;
    double      maxY;
    double      maxZ;
    bool        useArbitrator;
    bool        arbitratorLessThan;
    std::string arbitratorVarName;
    bool        distributedResample;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define INTERNALRESAMPLEATTRIBUTES_TMFS "biiiibfbddddddbbsb"

#endif
