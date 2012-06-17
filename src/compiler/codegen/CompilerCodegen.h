/*
 * Copyright (C) 2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ART_SRC_COMPILER_COMPILERCODEGEN_H_
#define ART_SRC_COMPILER_COMPILERCODEGEN_H_

#include "../CompilerIR.h"

namespace art {

LIR* rawLIR(CompilationUnit* cUnit, int dalvikOffset, int opcode, int op0 = 0,
            int op1 = 0, int op2 = 0, int op3 = 0, int op4 = 0,
            LIR* target = NULL);

int oatGetInsnSize(LIR* lir);

void genFusedLongCmpBranch(CompilationUnit* cUnit, BasicBlock* bb, MIR* mir);
void genFusedFPCmpBranch(CompilationUnit* cUnit, BasicBlock* bb, MIR* mir,
                         bool gtBias, bool isDouble);

CallInfo* oatNewCallInfo(CompilationUnit* cUnit, BasicBlock* bb, MIR* mir,
                         InvokeType type, bool isRange);

/* Lower middle-level IR to low-level IR for the whole method */
void oatMethodMIR2LIR(CompilationUnit* cUnit);

/* Bitcode conversions */
void oatMethodMIR2Bitcode(CompilationUnit* cUnit);
void oatMethodBitcode2LIR(CompilationUnit* cUnit);

/* Lower middle-level IR to low-level IR for the simple methods */
void oatSpecialMIR2LIR(CompilationUnit* cUnit, SpecialCaseHandler specialCase );

/* Assemble LIR into machine code */
void oatAssembleLIR(CompilationUnit* cUnit);
AssemblerStatus oatAssembleInstructions(CompilationUnit* cUnit,
                                        intptr_t startAddr);
void oatAssignOffsets(CompilationUnit* cUnit);
int oatAssignInsnOffsets(CompilationUnit* cUnit);

/* Implemented in the codegen/<target>/ArchUtility.c */
void oatCodegenDump(CompilationUnit* cUnit);
void oatDumpPromotionMap(CompilationUnit* cUnit);
std::string buildInsnString(const char* fmt, LIR* lir,
                            unsigned char* baseAddr);


/* Implemented in codegen/<target>/Ralloc.c */
void oatSimpleRegAlloc(CompilationUnit* cUnit);

/* Implemented in codegen/<target>/Thumb<version>Util.c */
void oatInitializeRegAlloc(CompilationUnit* cUnit);

/* Implemented in codegen/<target>/<target_variant>/ArchVariant.c */
InstructionSet oatInstructionSet();

/*
 * Implemented in codegen/<target>/<target_variant>/ArchVariant.c
 * Architecture-specific initializations and checks
 */
bool oatArchVariantInit(void);

/* Implemented in codegen/<target>/<target_variant>/ArchVariant.c */
int oatTargetOptHint(int key);

/* Implemented in codegen/<target>/<target_variant>/ArchVariant.c */
void oatGenMemBarrier(CompilationUnit* cUnit, int barrierKind);

}  // namespace art

#endif  // ART_SRC_COMPILER_COMPILERCODEGEN_H_
