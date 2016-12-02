// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All right reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Alessandro Tasora, Radu Serban
// =============================================================================

#ifndef CHLINKBASE_H
#define CHLINKBASE_H

#include "chrono/core/ChLog.h"
#include "chrono/physics/ChPhysicsItem.h"

namespace chrono {

// Unique link type identifiers (for detecting type faster than with RTTI)
// The corresponding identifier can be obtained with GetLinkType().
// Also, the ChLinkLock family of constraints supports ChangeLinkType().
//  TODO: remove these defines, maybe obsoleted, use RTTI instead when needed; 
//  maybe keep only for ChangeLinkType()

#define LNK_LOCK 0
#define LNK_SPHERICAL 1
#define LNK_POINTPLANE 2
#define LNK_POINTLINE 3
#define LNK_CYLINDRICAL 4
#define LNK_PRISMATIC 5
#define LNK_PLANEPLANE 6
#define LNK_OLDHAM 7
#define LNK_REVOLUTE 8
#define LNK_RACKPIN 9
#define LNK_FREE 10
#define LNK_SCREW 12
#define LNK_ALIGN 13
#define LNK_PARALLEL 14
#define LNK_PERPEND 15
#define LNK_UNIVERSAL 16
#define LNK_GEAR 17
#define LNK_COUPLER 18
#define LNK_DISTANCE 19
#define LNK_POINTSPLINE 20
#define LNK_TRAJECTORY 22
#define LNK_REVOLUTESPHERICAL 23
#define LNK_REVOLUTETRANSLATIONAL 24
#define LNK_SPRING 25
#define LNK_WHEEL 26
#define LNK_LINACTUATOR 27
#define LNK_BASE 29
#define LNK_SPRING_CALLBACK 30
#define LNK_ENGINE 31
#define LNK_BRAKE 32
#define LNK_PNEUMATIC 33
#define LNK_CLEARANCE 34
#define LNK_FASTCONTACT 35
#define LNK_GEOMETRICDISTANCE 37
#define LNK_PULLEY 38
#define LNK_CONTACT 40
#define LNK_MATE 41
#define LNK_MATEGENERIC 42
#define LNK_MATEPLANE 43
#define LNK_MATECOAXIAL 44
#define LNK_MATESPHERICAL 45
#define LNK_MATEXDISTANCE 48
#define LNK_MATEPARALLEL 46
#define LNK_MATEORTHOGONAL 47
#define LNK_REVOLUTEPRISMATIC 48
#define LNK_MATEFIX 49

/// Base class for all types of constraints that act like
/// mechanical joints ('links') in 3D space.
///
/// Note that there are many specializations of this base class,
/// for example the ChLinkEngine class inherits this base class and
/// implements specific functions to represent an engine between two
/// bodies, etc. etc. (In fact, this base ChLink class does basically
/// _nothing_ unless it is specialized by some child class).

class ChApi ChLinkBase : public ChPhysicsItem {

    // Tag needed for class factory in archive (de)serialization:
    CH_FACTORY_TAG(ChLinkBase)

  protected:
    bool disabled;  ///< all constraints of link disabled because of user needs
    bool valid;     ///< link data is valid
    bool broken;    ///< link is broken because of excessive pulling/pushing.

  public:
    ChLinkBase() : broken(false), valid(true), disabled(false) {}
    ChLinkBase(const ChLinkBase& other);
    virtual ~ChLinkBase() {}

    /// Tells if the link data is currently valid.
    /// (i.e. pointers to other items are correct)
    bool IsValid() { return valid; }
    /// Set the status of link validity
    void SetValid(bool mon) { valid = mon; }

    /// Tells if all constraints of this link are currently turned on or off by the user.
    bool IsDisabled() { return disabled; }
    /// User can use this to enable/disable all the constraint of the link as desired.
    virtual void SetDisabled(bool mdis) { disabled = mdis; }

    /// Tells if the link is broken, for excess of pulling/pushing.
    bool IsBroken() { return broken; }
    /// Set the 'broken' status vof this link.
    virtual void SetBroken(bool mon) { broken = mon; }

    /// An important function!
    /// Tells if the link is currently active, in general,
    /// that is tells if it must be included into the system solver or not.
    /// This method cumulates the effect of various flags (so a link may
    /// be not active either because disabled, or broken, or not valid)
    bool IsActive() { return (valid && !disabled && !broken); }

    /// Get the type identifier of this link. Use if you don't want to use RTTI for performance.
    virtual int GetType() const { return LNK_BASE; }

    /// Get the number of scalar variables affected by constraints in this link
    virtual int GetNumCoords() = 0;

    /// Get the link coordinate system in absolute reference.
    /// This represents the 'main' reference of the link: reaction forces
    /// and reaction torques are expressed in this coordinate system.
    /// Child classes should implement this.
    virtual ChCoordsys<> GetLinkAbsoluteCoords() { return CSYSNORM; }

    /// Get the master coordinate system for the assets, in absolute reference.
    /// (should be implemented by children classes)
    virtual ChFrame<> GetAssetsFrame(unsigned int nclone = 0) { return ChFrame<>(GetLinkAbsoluteCoords()); }

    /// To get reaction force, expressed in link coordinate system:
    virtual ChVector<> Get_react_force() { return VNULL; }
    /// To get reaction torque,  expressed in link coordinate system:
    virtual ChVector<> Get_react_torque() { return VNULL; }
    // (Note, functions above might fit better in a specialized subclass, but here for easier GUI interface)

    /// Tells if this link requires that the connected ChBody objects
    /// must be waken if they are sleeping. By default =true, i.e. always keep awaken, but
    /// child classes might return false for optimizing sleeping, in case no time-dependant.
    virtual bool IsRequiringWaking() { return true; }

    //
    // SERIALIZATION
    //

    /// Method to allow serialization of transient data to archives.
    virtual void ArchiveOUT(ChArchiveOut& marchive) override;

    /// Method to allow deserialization of transient data from archives.
    virtual void ArchiveIN(ChArchiveIn& marchive) override;
};

}  // end namespace

#endif
