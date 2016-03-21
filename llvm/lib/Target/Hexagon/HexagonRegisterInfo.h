//==- HexagonRegisterInfo.h - Hexagon Register Information Impl --*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Hexagon implementation of the TargetRegisterInfo
// class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_HEXAGON_HEXAGONREGISTERINFO_H
#define LLVM_LIB_TARGET_HEXAGON_HEXAGONREGISTERINFO_H

#include "llvm/MC/MachineLocation.h"
#include "llvm/Target/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "HexagonGenRegisterInfo.inc"

namespace llvm {
class HexagonRegisterInfo : public HexagonGenRegisterInfo {
public:
  HexagonRegisterInfo();

  /// Code Generation virtual methods...
  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF)
        const override;


  BitVector getReservedRegs(const MachineFunction &MF) const override;

  void eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
        unsigned FIOperandNum, RegScavenger *RS = nullptr) const override;

  /// Returns true since we may need scavenging for a temporary register
  /// when generating hardware loop instructions.
  bool requiresRegisterScavenging(const MachineFunction &MF) const override {
    return true;
  }

  /// Returns true. Spill code for predicate registers might need an extra
  /// register.
  bool requiresFrameIndexScavenging(const MachineFunction &MF) const override {
    return true;
  }

  /// Returns true if the frame pointer is valid.
  bool useFPForScavengingIndex(const MachineFunction &MF) const override;

  bool trackLivenessAfterRegAlloc(const MachineFunction &MF) const override {
    return true;
  }

  // Debug information queries.
  unsigned getRARegister() const;
  unsigned getFrameRegister(const MachineFunction &MF) const override;
  unsigned getFrameRegister() const;
  unsigned getStackRegister() const;

  const MCPhysReg *getCallerSavedRegs(const MachineFunction *MF) const;

  unsigned getFirstCallerSavedNonParamReg() const;

  bool isEHReturnCalleeSaveReg(unsigned Reg) const;
  bool isCalleeSaveReg(unsigned Reg) const;
};

} // end namespace llvm

#endif
