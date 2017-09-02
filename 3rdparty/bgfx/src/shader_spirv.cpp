/*
<<<<<<< HEAD
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
=======
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
>>>>>>> upstream/master
 */

#include "bgfx_p.h"
#include "shader_spirv.h"

namespace bgfx
{
<<<<<<< HEAD
	struct SpirvOpcodeInfo
	{
		uint8_t numOperands;
		uint8_t numValues;
		bool    hasVariable;
	};

	static const SpirvOpcodeInfo s_sprivOpcodeInfo[] =
	{
		{ 0, 0, false }, // Nop,
		{ 0, 0, true  }, // Source
		{ 0, 0, true  }, // SourceExtension
		{ 0, 0, false }, // Extension
		{ 0, 1, true  }, // ExtInstImport
		{ 0, 2, false }, // MemoryModel
		{ 0, 2, false }, // EntryPoint
		{ 0, 0, false }, // ExecutionMode
		{ 0, 1, false }, // TypeVoid
		{ 0, 1, false }, // TypeBool
		{ 0, 3, false }, // TypeInt
		{ 0, 2, false }, // TypeFloat
		{ 0, 3, false }, // TypeVector
		{ 0, 3, false }, // TypeMatrix
		{ 1, 7, false }, // TypeSampler
		{ 0, 0, false }, // TypeFilter
		{ 0, 0, false }, // TypeArray
		{ 0, 0, false }, // TypeRuntimeArray
		{ 0, 0, false }, // TypeStruct
		{ 0, 0, false }, // TypeOpaque
		{ 0, 3, false }, // TypePointer
		{ 0, 2, true  }, // TypeFunction
		{ 0, 0, false }, // TypeEvent
		{ 0, 0, false }, // TypeDeviceEvent
		{ 0, 0, false }, // TypeReserveId
		{ 0, 0, false }, // TypeQueue
		{ 0, 0, false }, // TypePipe
		{ 0, 0, false }, // ConstantTrue
		{ 0, 0, false }, // ConstantFalse
		{ 0, 2, true  }, // Constant
		{ 0, 2, true  }, // ConstantComposite
		{ 0, 0, false }, // ConstantSampler
		{ 0, 0, false }, // ConstantNullPointer
		{ 0, 0, false }, // ConstantNullObject
		{ 0, 0, false }, // SpecConstantTrue
		{ 0, 0, false }, // SpecConstantFalse
		{ 0, 0, false }, // SpecConstant
		{ 0, 0, false }, // SpecConstantComposite
		{ 0, 3, true  }, // Variable
		{ 0, 0, false }, // VariableArray
		{ 0, 4, false }, // Function
		{ 0, 0, false }, // FunctionParameter
		{ 0, 0, false }, // FunctionEnd
		{ 0, 0, false }, // FunctionCall
		{ 0, 0, false }, // ExtInst
		{ 0, 0, false }, // Undef
		{ 0, 0, false }, // Load
		{ 0, 2, true  }, // Store
		{ 0, 0, false }, // Phi
		{ 0, 0, false }, // DecorationGroup
		{ 0, 2, true  }, // Decorate
		{ 0, 0, false }, // MemberDecorate
		{ 0, 0, false }, // GroupDecorate
		{ 0, 0, false }, // GroupMemberDecorate
		{ 0, 1, true  }, // Name
		{ 0, 1, true  }, // MemberName
		{ 0, 0, false }, // String
		{ 0, 0, false }, // Line
		{ 0, 0, false }, // VectorExtractDynamic
		{ 0, 0, false }, // VectorInsertDynamic
		{ 0, 0, false }, // VectorShuffle
		{ 0, 0, false }, // CompositeConstruct
		{ 0, 0, false }, // CompositeExtract
		{ 0, 0, false }, // CompositeInsert
		{ 0, 0, false }, // CopyObject
		{ 0, 0, false }, // CopyMemory
		{ 0, 0, false }, // CopyMemorySized
		{ 0, 0, false }, // Sampler
		{ 0, 0, false }, // TextureSample
		{ 0, 0, false }, // TextureSampleDref
		{ 0, 0, false }, // TextureSampleLod
		{ 0, 0, false }, // TextureSampleProj
		{ 0, 0, false }, // TextureSampleGrad
		{ 0, 0, false }, // TextureSampleOffset
		{ 0, 0, false }, // TextureSampleProjLod
		{ 0, 0, false }, // TextureSampleProjGrad
		{ 0, 0, false }, // TextureSampleLodOffset
		{ 0, 0, false }, // TextureSampleProjOffset
		{ 0, 0, false }, // TextureSampleGradOffset
		{ 0, 0, false }, // TextureSampleProjLodOffset
		{ 0, 0, false }, // TextureSampleProjGradOffset
		{ 0, 0, false }, // TextureFetchTexelLod
		{ 0, 0, false }, // TextureFetchTexelOffset
		{ 0, 0, false }, // TextureFetchSample
		{ 0, 0, false }, // TextureFetchTexel
		{ 0, 0, false }, // TextureGather
		{ 0, 0, false }, // TextureGatherOffset
		{ 0, 0, false }, // TextureGatherOffsets
		{ 0, 0, false }, // TextureQuerySizeLod
		{ 0, 0, false }, // TextureQuerySize
		{ 0, 0, false }, // TextureQueryLod
		{ 0, 0, false }, // TextureQueryLevels
		{ 0, 0, false }, // TextureQuerySamples
		{ 0, 0, false }, // AccessChain
		{ 0, 0, false }, // InBoundsAccessChain
		{ 0, 0, false }, // SNegate
		{ 0, 0, false }, // FNegate
		{ 0, 0, false }, // Not
		{ 0, 0, false }, // Any
		{ 0, 0, false }, // All
		{ 0, 0, false }, // ConvertFToU
		{ 0, 0, false }, // ConvertFToS
		{ 0, 0, false }, // ConvertSToF
		{ 0, 0, false }, // ConvertUToF
		{ 0, 0, false }, // UConvert
		{ 0, 0, false }, // SConvert
		{ 0, 0, false }, // FConvert
		{ 0, 0, false }, // ConvertPtrToU
		{ 0, 0, false }, // ConvertUToPtr
		{ 0, 0, false }, // PtrCastToGeneric
		{ 0, 0, false }, // GenericCastToPtr
		{ 0, 0, false }, // Bitcast
		{ 0, 0, false }, // Transpose
		{ 0, 0, false }, // IsNan
		{ 0, 0, false }, // IsInf
		{ 0, 0, false }, // IsFinite
		{ 0, 0, false }, // IsNormal
		{ 0, 0, false }, // SignBitSet
		{ 0, 0, false }, // LessOrGreater
		{ 0, 0, false }, // Ordered
		{ 0, 0, false }, // Unordered
		{ 0, 0, false }, // ArrayLength
		{ 0, 0, false }, // IAdd
		{ 0, 0, false }, // FAdd
		{ 0, 0, false }, // ISub
		{ 0, 0, false }, // FSub
		{ 0, 0, false }, // IMul
		{ 0, 0, false }, // FMul
		{ 0, 0, false }, // UDiv
		{ 0, 0, false }, // SDiv
		{ 0, 0, false }, // FDiv
		{ 0, 0, false }, // UMod
		{ 0, 0, false }, // SRem
		{ 0, 0, false }, // SMod
		{ 0, 0, false }, // FRem
		{ 0, 0, false }, // FMod
		{ 0, 0, false }, // VectorTimesScalar
		{ 0, 0, false }, // MatrixTimesScalar
		{ 0, 0, false }, // VectorTimesMatrix
		{ 0, 0, false }, // MatrixTimesVector
		{ 0, 0, false }, // MatrixTimesMatrix
		{ 0, 0, false }, // OuterProduct
		{ 0, 0, false }, // Dot
		{ 0, 0, false }, // ShiftRightLogical
		{ 0, 0, false }, // ShiftRightArithmetic
		{ 0, 0, false }, // ShiftLeftLogical
		{ 0, 0, false }, // LogicalOr
		{ 0, 0, false }, // LogicalXor
		{ 0, 0, false }, // LogicalAnd
		{ 0, 0, false }, // BitwiseOr
		{ 0, 0, false }, // BitwiseXor
		{ 0, 0, false }, // BitwiseAnd
		{ 0, 0, false }, // Select
		{ 0, 0, false }, // IEqual
		{ 0, 0, false }, // FOrdEqual
		{ 0, 0, false }, // FUnordEqual
		{ 0, 0, false }, // INotEqual
		{ 0, 0, false }, // FOrdNotEqual
		{ 0, 0, false }, // FUnordNotEqual
		{ 0, 0, false }, // ULessThan
		{ 0, 0, false }, // SLessThan
		{ 0, 0, false }, // FOrdLessThan
		{ 0, 0, false }, // FUnordLessThan
		{ 0, 0, false }, // UGreaterThan
		{ 0, 0, false }, // SGreaterThan
		{ 0, 0, false }, // FOrdGreaterThan
		{ 0, 0, false }, // FUnordGreaterThan
		{ 0, 0, false }, // ULessThanEqual
		{ 0, 0, false }, // SLessThanEqual
		{ 0, 0, false }, // FOrdLessThanEqual
		{ 0, 0, false }, // FUnordLessThanEqual
		{ 0, 0, false }, // UGreaterThanEqual
		{ 0, 0, false }, // SGreaterThanEqual
		{ 0, 0, false }, // FOrdGreaterThanEqual
		{ 0, 0, false }, // FUnordGreaterThanEqual
		{ 0, 0, false }, // DPdx
		{ 0, 0, false }, // DPdy
		{ 0, 0, false }, // Fwidth
		{ 0, 0, false }, // DPdxFine
		{ 0, 0, false }, // DPdyFine
		{ 0, 0, false }, // FwidthFine
		{ 0, 0, false }, // DPdxCoarse
		{ 0, 0, false }, // DPdyCoarse
		{ 0, 0, false }, // FwidthCoarse
		{ 0, 0, false }, // EmitVertex
		{ 0, 0, false }, // EndPrimitive
		{ 0, 0, false }, // EmitStreamVertex
		{ 0, 0, false }, // EndStreamPrimitive
		{ 0, 0, false }, // ControlBarrier
		{ 0, 0, false }, // MemoryBarrier
		{ 0, 0, false }, // ImagePointer
		{ 0, 0, false }, // AtomicInit
		{ 0, 0, false }, // AtomicLoad
		{ 0, 0, false }, // AtomicStore
		{ 0, 0, false }, // AtomicExchange
		{ 0, 0, false }, // AtomicCompareExchange
		{ 0, 0, false }, // AtomicCompareExchangeWeak
		{ 0, 0, false }, // AtomicIIncrement
		{ 0, 0, false }, // AtomicIDecrement
		{ 0, 0, false }, // AtomicIAdd
		{ 0, 0, false }, // AtomicISub
		{ 0, 0, false }, // AtomicUMin
		{ 0, 0, false }, // AtomicUMax
		{ 0, 0, false }, // AtomicAnd
		{ 0, 0, false }, // AtomicOr
		{ 0, 0, false }, // AtomicXor
		{ 0, 0, false }, // LoopMerge
		{ 0, 0, false }, // SelectionMerge
		{ 0, 1, false }, // Label
		{ 0, 1, false }, // Branch
		{ 0, 0, false }, // BranchConditional
		{ 0, 0, false }, // Switch
		{ 0, 0, false }, // Kill
		{ 0, 0, false }, // Return
		{ 0, 0, false }, // ReturnValue
		{ 0, 0, false }, // Unreachable
		{ 0, 0, false }, // LifetimeStart
		{ 0, 0, false }, // LifetimeStop
		{ 0, 0, false }, // CompileFlag
		{ 0, 0, false }, // AsyncGroupCopy
		{ 0, 0, false }, // WaitGroupEvents
		{ 0, 0, false }, // GroupAll
		{ 0, 0, false }, // GroupAny
		{ 0, 0, false }, // GroupBroadcast
		{ 0, 0, false }, // GroupIAdd
		{ 0, 0, false }, // GroupFAdd
		{ 0, 0, false }, // GroupFMin
		{ 0, 0, false }, // GroupUMin
		{ 0, 0, false }, // GroupSMin
		{ 0, 0, false }, // GroupFMax
		{ 0, 0, false }, // GroupUMax
		{ 0, 0, false }, // GroupSMax
		{ 0, 0, false }, // GenericCastToPtrExplicit
		{ 0, 0, false }, // GenericPtrMemSemantics
		{ 0, 0, false }, // ReadPipe
		{ 0, 0, false }, // WritePipe
		{ 0, 0, false }, // ReservedReadPipe
		{ 0, 0, false }, // ReservedWritePipe
		{ 0, 0, false }, // ReserveReadPipePackets
		{ 0, 0, false }, // ReserveWritePipePackets
		{ 0, 0, false }, // CommitReadPipe
		{ 0, 0, false }, // CommitWritePipe
		{ 0, 0, false }, // IsValidReserveId
		{ 0, 0, false }, // GetNumPipePackets
		{ 0, 0, false }, // GetMaxPipePackets
		{ 0, 0, false }, // GroupReserveReadPipePackets
		{ 0, 0, false }, // GroupReserveWritePipePackets
		{ 0, 0, false }, // GroupCommitReadPipe
		{ 0, 0, false }, // GroupCommitWritePipe
		{ 0, 0, false }, // EnqueueMarker
		{ 0, 0, false }, // EnqueueKernel
		{ 0, 0, false }, // GetKernelNDrangeSubGroupCount
		{ 0, 0, false }, // GetKernelNDrangeMaxSubGroupSize
		{ 0, 0, false }, // GetKernelWorkGroupSize
		{ 0, 0, false }, // GetKernelPreferredWorkGroupSizeMultiple
		{ 0, 0, false }, // RetainEvent
		{ 0, 0, false }, // ReleaseEvent
		{ 0, 0, false }, // CreateUserEvent
		{ 0, 0, false }, // IsValidEvent
		{ 0, 0, false }, // SetUserEventStatus
		{ 0, 0, false }, // CaptureEventProfilingInfo
		{ 0, 0, false }, // GetDefaultQueue
		{ 0, 0, false }, // BuildNDRange
		{ 0, 0, false }, // SatConvertSToU
		{ 0, 0, false }, // SatConvertUToS
		{ 0, 0, false }, // AtomicIMin
		{ 0, 0, false }, // AtomicIMax
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_sprivOpcodeInfo) == SpirvOpcode::Count);

	const char* s_spirvOpcode[] =
	{
		"Nop",
		"Source",
		"SourceExtension",
		"Extension",
		"ExtInstImport",
		"MemoryModel",
		"EntryPoint",
		"ExecutionMode",
=======
#define SPV_OPERAND_1(_a0) SpvOperand::_a0
#define SPV_OPERAND_2(_a0, _a1) SPV_OPERAND_1(_a0), SPV_OPERAND_1(_a1)
#define SPV_OPERAND_3(_a0, _a1, _a2) SPV_OPERAND_1(_a0), SPV_OPERAND_2(_a1, _a2)
#define SPV_OPERAND_4(_a0, _a1, _a2, _a3) SPV_OPERAND_1(_a0), SPV_OPERAND_3(_a1, _a2, _a3)
#define SPV_OPERAND_5(_a0, _a1, _a2, _a3, _a4) SPV_OPERAND_1(_a0), SPV_OPERAND_4(_a1, _a2, _a3, _a4)
#define SPV_OPERAND_6(_a0, _a1, _a2, _a3, _a4, _a5) SPV_OPERAND_1(_a0), SPV_OPERAND_5(_a1, _a2, _a3, _a4, _a5)
#define SPV_OPERAND_7(_a0, _a1, _a2, _a3, _a4, _a5, _a6) SPV_OPERAND_1(_a0), SPV_OPERAND_6(_a1, _a2, _a3, _a4, _a5, _a6)
#define SPV_OPERAND_8(_a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7) SPV_OPERAND_1(_a0), SPV_OPERAND_7(_a1, _a2, _a3, _a4, _a5, _a6, _a7)
#define SPV_OPERAND_9(_a0, _a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8) SPV_OPERAND_1(_a0), SPV_OPERAND_8(_a1, _a2, _a3, _a4, _a5, _a6, _a7, _a8)
#if BX_COMPILER_MSVC
// Workaround MSVS bug...
#	define SPV_OPERAND(...) { BX_MACRO_DISPATCHER(SPV_OPERAND_, __VA_ARGS__) BX_VA_ARGS_PASS(__VA_ARGS__) }
#else
#	define SPV_OPERAND(...) { BX_MACRO_DISPATCHER(SPV_OPERAND_, __VA_ARGS__)(__VA_ARGS__) }
#endif // BX_COMPILER_MSVC
#define _ Count

	bool isDebug(SpvOpcode::Enum _opcode)
	{
		return (SpvOpcode::SourceContinued <= _opcode && SpvOpcode::Line >= _opcode)
			||  SpvOpcode::NoLine == _opcode
			;
	}

	struct SpvOpcodeInfo
	{
		bool hasType;
		bool hasResult;
		SpvOperand::Enum operands[8];
	};

	static const SpvOpcodeInfo s_spvOpcodeInfo[] =
	{
		{ false, false, /* Nop,                                     //   0 */ SPV_OPERAND(_) },
		{ true,  true,  /* Undef,                                   //   1 */ SPV_OPERAND(_) },
		{ false, false, /* SourceContinued,                         //   2 */ SPV_OPERAND(_) },
		{ false, false, /* Source,                                  //   3 */ SPV_OPERAND(SourceLanguage, LiteralNumber, Id, LiteralString) },
		{ false, false, /* SourceExtension,                         //   4 */ SPV_OPERAND(LiteralString) },
		{ false, true,  /* Name,                                    //   5 */ SPV_OPERAND(LiteralString) },
		{ false, true,  /* MemberName,                              //   6 */ SPV_OPERAND(LiteralNumber, LiteralString) },
		{ false, false, /* String,                                  //   7 */ SPV_OPERAND(_) },
		{ false, false, /* Line,                                    //   8 */ SPV_OPERAND(_) },
		{ false, false, /* ------------------------------- Invalid9 //   9 */ SPV_OPERAND(_) },
		{ false, false, /* Extension,                               //  10 */ SPV_OPERAND(LiteralString) },
		{ false, true,  /* ExtInstImport,                           //  11 */ SPV_OPERAND(LiteralString) },
		{ true,  true,  /* ExtInst,                                 //  12 */ SPV_OPERAND(LiteralNumber) },
		{ false, false, /* ------------------------------ Invalid13 //  13 */ SPV_OPERAND(_) },
		{ false, false, /* MemoryModel,                             //  14 */ SPV_OPERAND(AddressingModel, MemoryModel) },
		{ false, false, /* EntryPoint,                              //  15 */ SPV_OPERAND(ExecutionModel, Id, LiteralString) },
		{ true,  true,  /* ExecutionMode,                           //  16 */ SPV_OPERAND(_) },
		{ false, false, /* Capability,                              //  17 */ SPV_OPERAND(Capability   ) },
		{ false, false, /* ------------------------------ Invalid18 //  18 */ SPV_OPERAND(_) },
		{ false, true,  /* TypeVoid,                                //  19 */ SPV_OPERAND(LiteralNumber) },
		{ false, true,  /* TypeBool,                                //  20 */ SPV_OPERAND(LiteralNumber) },
		{ false, true,  /* TypeInt,                                 //  21 */ SPV_OPERAND(LiteralNumber) },
		{ false, true,  /* TypeFloat,                               //  22 */ SPV_OPERAND(LiteralNumber) },
		{ false, true,  /* TypeVector,                              //  23 */ SPV_OPERAND(ComponentType, LiteralNumber) },
		{ false, true,  /* TypeMatrix,                              //  24 */ SPV_OPERAND(LiteralNumber) },
		{ false, true,  /* TypeImage,                               //  25 */ SPV_OPERAND(SampledType, Dim, LiteralNumber, LiteralNumber, LiteralNumber, LiteralNumber, ImageFormat, AccessQualifier) },
		{ false, true,  /* TypeSampler,                             //  26 */ SPV_OPERAND(LiteralNumber) },
		{ false, true,  /* TypeSampledImage,                        //  27 */ SPV_OPERAND(LiteralNumber) },
		{ false, true,  /* TypeArray,                               //  28 */ SPV_OPERAND(ElementType, LiteralNumber) },
		{ false, true,  /* TypeRuntimeArray,                        //  29 */ SPV_OPERAND(ElementType) },
		{ false, true,  /* TypeStruct,                              //  30 */ SPV_OPERAND(IdRep) },
		{ false, true,  /* TypeOpaque,                              //  31 */ SPV_OPERAND(LiteralString) },
		{ false, true,  /* TypePointer,                             //  32 */ SPV_OPERAND(StorageClass, Id) },
		{ false, true,  /* TypeFunction,                            //  33 */ SPV_OPERAND(Id, Id, Id, Id, Id) },
		{ false, true,  /* TypeEvent,                               //  34 */ SPV_OPERAND(_) },
		{ false, true,  /* TypeDeviceEvent,                         //  35 */ SPV_OPERAND(_) },
		{ false, true,  /* TypeReserveId,                           //  36 */ SPV_OPERAND(_) },
		{ false, true,  /* TypeQueue,                               //  37 */ SPV_OPERAND(_) },
		{ false, true,  /* TypePipe,                                //  38 */ SPV_OPERAND(_) },
		{ false, true,  /* TypeForwardPointer,                      //  39 */ SPV_OPERAND(_) },
		{ false, false, /* ------------------------------ Invalid40 //  40 */ SPV_OPERAND(_) },
		{ true,  true,  /* ConstantTrue,                            //  41 */ SPV_OPERAND(_) },
		{ true,  true,  /* ConstantFalse,                           //  42 */ SPV_OPERAND(_) },
		{ true,  true,  /* Constant,                                //  43 */ SPV_OPERAND(LiteralRep) },
		{ true,  true,  /* ConstantComposite,                       //  44 */ SPV_OPERAND(LiteralRep) },
		{ true,  true,  /* ConstantSampler,                         //  45 */ SPV_OPERAND(SamplerAddressingMode, LiteralNumber, SamplerFilterMode) },
		{ true,  true,  /* ConstantNull,                            //  46 */ SPV_OPERAND(_) },
		{ false, false, /* ------------------------------ Invalid47 //  47 */ SPV_OPERAND(_) },
		{ true,  true,  /* SpecConstantTrue,                        //  48 */ SPV_OPERAND(_) },
		{ true,  true,  /* SpecConstantFalse,                       //  49 */ SPV_OPERAND(_) },
		{ true,  true,  /* SpecConstant,                            //  50 */ SPV_OPERAND(_) },
		{ true,  true,  /* SpecConstantComposite,                   //  51 */ SPV_OPERAND(_) },
		{ true,  true,  /* SpecConstantOp,                          //  52 */ SPV_OPERAND(_) },
		{ false, false, /* ------------------------------ Invalid53 //  53 */ SPV_OPERAND(_) },
		{ true,  true,  /* Function,                                //  54 */ SPV_OPERAND(FunctionControl, Id) },
		{ true,  true,  /* FunctionParameter,                       //  55 */ SPV_OPERAND(_) },
		{ false, false, /* FunctionEnd,                             //  56 */ SPV_OPERAND(_) },
		{ true,  true,  /* FunctionCall,                            //  57 */ SPV_OPERAND(Function, IdRep) },
		{ false, false, /* ------------------------------ Invalid58 //  58 */ SPV_OPERAND(_) },
		{ true,  true,  /* Variable,                                //  59 */ SPV_OPERAND(StorageClass, Id) },
		{ true,  true,  /* ImageTexelPointer,                       //  60 */ SPV_OPERAND(_) },
		{ true,  true,  /* Load,                                    //  61 */ SPV_OPERAND(Pointer, MemoryAccess) },
		{ false, false, /* Store,                                   //  62 */ SPV_OPERAND(Pointer, Object, MemoryAccess) },
		{ false, false, /* CopyMemory,                              //  63 */ SPV_OPERAND(_) },
		{ false, false, /* CopyMemorySized,                         //  64 */ SPV_OPERAND(_) },
		{ true,  true,  /* AccessChain,                             //  65 */ SPV_OPERAND(Base, IdRep) },
		{ true,  true,  /* InBoundsAccessChain,                     //  66 */ SPV_OPERAND(Base, IdRep) },
		{ true,  true,  /* PtrAccessChain,                          //  67 */ SPV_OPERAND(_) },
		{ true,  true,  /* ArrayLength,                             //  68 */ SPV_OPERAND(_) },
		{ true,  true,  /* GenericPtrMemSemantics,                  //  69 */ SPV_OPERAND(_) },
		{ true,  true,  /* InBoundsPtrAccessChain,                  //  70 */ SPV_OPERAND(_) },
		{ false, false, /* Decorate,                                //  71 */ SPV_OPERAND(Id, Decoration, LiteralRep) },
		{ false, false, /* MemberDecorate,                          //  72 */ SPV_OPERAND(StructureType, LiteralNumber, Decoration, LiteralRep) },
		{ false, false, /* DecorationGroup,                         //  73 */ SPV_OPERAND(_) },
		{ false, false, /* GroupDecorate,                           //  74 */ SPV_OPERAND(_) },
		{ false, false, /* GroupMemberDecorate,                     //  75 */ SPV_OPERAND(_) },
		{ false, false, /* ------------------------------ Invalid76 //  76 */ SPV_OPERAND(_) },
		{ true,  true,  /* VectorExtractDynamic,                    //  77 */ SPV_OPERAND(_) },
		{ true,  true,  /* VectorInsertDynamic,                     //  78 */ SPV_OPERAND(_) },
		{ true,  true,  /* VectorShuffle,                           //  79 */ SPV_OPERAND(Id, Id, LiteralRep) },
		{ true,  true,  /* CompositeConstruct,                      //  80 */ SPV_OPERAND(IdRep) },
		{ true,  true,  /* CompositeExtract,                        //  81 */ SPV_OPERAND(Composite, LiteralRep) },
		{ true,  true,  /* CompositeInsert,                         //  82 */ SPV_OPERAND(Id, Composite, LiteralRep) },
		{ true,  true,  /* CopyObject,                              //  83 */ SPV_OPERAND(Id) },
		{ true,  true,  /* Transpose,                               //  84 */ SPV_OPERAND(Matrix) },
		{ false, false, /* ------------------------------ Invalid85 //  85 */ SPV_OPERAND(_) },
		{ true,  true,  /* SampledImage,                            //  86 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSampleImplicitLod,                  //  87 */ SPV_OPERAND(SampledImage, Coordinate, ImageOperands, IdRep) },
		{ true,  true,  /* ImageSampleExplicitLod,                  //  88 */ SPV_OPERAND(SampledImage, Coordinate, ImageOperands, Id, IdRep) },
		{ true,  true,  /* ImageSampleDrefImplicitLod,              //  89 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSampleDrefExplicitLod,              //  90 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSampleProjImplicitLod,              //  91 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSampleProjExplicitLod,              //  92 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSampleProjDrefImplicitLod,          //  93 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSampleProjDrefExplicitLod,          //  94 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageFetch,                              //  95 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageGather,                             //  96 */ SPV_OPERAND(SampledImage, Coordinate, Component, ImageOperands, IdRep) },
		{ true,  true,  /* ImageDrefGather,                         //  97 */ SPV_OPERAND(SampledImage, Coordinate, Dref, ImageOperands, IdRep) },
		{ true,  true,  /* ImageRead,                               //  98 */ SPV_OPERAND(_) },
		{ false, false, /* ImageWrite,                              //  99 */ SPV_OPERAND(_) },
		{ true,  true,  /* Image,                                   // 100 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageQueryFormat,                        // 101 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageQueryOrder,                         // 102 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageQuerySizeLod,                       // 103 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageQuerySize,                          // 104 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageQueryLod,                           // 105 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageQueryLevels,                        // 106 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageQuerySamples,                       // 107 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid108 // 108 */ SPV_OPERAND(_) },
		{ true,  true,  /* ConvertFToU,                             // 109 */ SPV_OPERAND(_) },
		{ true,  true,  /* ConvertFToS,                             // 110 */ SPV_OPERAND(_) },
		{ true,  true,  /* ConvertSToF,                             // 111 */ SPV_OPERAND(_) },
		{ true,  true,  /* ConvertUToF,                             // 112 */ SPV_OPERAND(_) },
		{ true,  true,  /* UConvert,                                // 113 */ SPV_OPERAND(Id) },
		{ true,  true,  /* SConvert,                                // 114 */ SPV_OPERAND(Id) },
		{ true,  true,  /* FConvert,                                // 115 */ SPV_OPERAND(Id) },
		{ true,  true,  /* QuantizeToF16,                           // 116 */ SPV_OPERAND(_) },
		{ true,  true,  /* ConvertPtrToU,                           // 117 */ SPV_OPERAND(_) },
		{ true,  true,  /* SatConvertSToU,                          // 118 */ SPV_OPERAND(_) },
		{ true,  true,  /* SatConvertUToS,                          // 119 */ SPV_OPERAND(_) },
		{ true,  true,  /* ConvertUToPtr,                           // 120 */ SPV_OPERAND(_) },
		{ true,  true,  /* PtrCastToGeneric,                        // 121 */ SPV_OPERAND(_) },
		{ true,  true,  /* GenericCastToPtr,                        // 122 */ SPV_OPERAND(_) },
		{ true,  true,  /* GenericCastToPtrExplicit,                // 123 */ SPV_OPERAND(_) },
		{ true,  true,  /* Bitcast,                                 // 124 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid125 // 125 */ SPV_OPERAND(_) },
		{ true,  true,  /* SNegate,                                 // 126 */ SPV_OPERAND(Id) },
		{ true,  true,  /* FNegate,                                 // 127 */ SPV_OPERAND(Id) },
		{ true,  true,  /* IAdd,                                    // 128 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* FAdd,                                    // 129 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* ISub,                                    // 130 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* FSub,                                    // 131 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* IMul,                                    // 132 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* FMul,                                    // 133 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* UDiv,                                    // 134 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* SDiv,                                    // 135 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* FDiv,                                    // 136 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* UMod,                                    // 137 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* SRem,                                    // 138 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* SMod,                                    // 139 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* FRem,                                    // 140 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* FMod,                                    // 141 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* VectorTimesScalar,                       // 142 */ SPV_OPERAND(Vector, Scalar) },
		{ true,  true,  /* MatrixTimesScalar,                       // 143 */ SPV_OPERAND(Matrix, Scalar) },
		{ true,  true,  /* VectorTimesMatrix,                       // 144 */ SPV_OPERAND(Vector, Matrix) },
		{ true,  true,  /* MatrixTimesVector,                       // 145 */ SPV_OPERAND(Matrix, Vector) },
		{ true,  true,  /* MatrixTimesMatrix,                       // 146 */ SPV_OPERAND(Matrix, Matrix) },
		{ true,  true,  /* OuterProduct,                            // 147 */ SPV_OPERAND(Vector, Vector) },
		{ true,  true,  /* Dot,                                     // 148 */ SPV_OPERAND(Vector, Vector) },
		{ true,  true,  /* IAddCarry,                               // 149 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* ISubBorrow,                              // 150 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* UMulExtended,                            // 151 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* SMulExtended,                            // 152 */ SPV_OPERAND(Id, Id) },
		{ false, false, /* ----------------------------- Invalid153 // 153 */ SPV_OPERAND(_) },
		{ true,  true,  /* Any,                                     // 154 */ SPV_OPERAND(Vector) },
		{ true,  true,  /* All,                                     // 155 */ SPV_OPERAND(Vector) },
		{ true,  true,  /* IsNan,                                   // 156 */ SPV_OPERAND(Id) },
		{ true,  true,  /* IsInf,                                   // 157 */ SPV_OPERAND(Id) },
		{ true,  true,  /* IsFinite,                                // 158 */ SPV_OPERAND(Id) },
		{ true,  true,  /* IsNormal,                                // 159 */ SPV_OPERAND(Id) },
		{ true,  true,  /* SignBitSet,                              // 160 */ SPV_OPERAND(Id) },
		{ true,  true,  /* LessOrGreater,                           // 161 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* Ordered,                                 // 162 */ SPV_OPERAND(Id, Id) },
		{ true,  true,  /* Unordered,                               // 163 */ SPV_OPERAND(_) },
		{ true,  true,  /* LogicalEqual,                            // 164 */ SPV_OPERAND(_) },
		{ true,  true,  /* LogicalNotEqual,                         // 165 */ SPV_OPERAND(_) },
		{ true,  true,  /* LogicalOr,                               // 166 */ SPV_OPERAND(_) },
		{ true,  true,  /* LogicalAnd,                              // 167 */ SPV_OPERAND(_) },
		{ true,  true,  /* LogicalNot,                              // 168 */ SPV_OPERAND(_) },
		{ true,  true,  /* Select,                                  // 169 */ SPV_OPERAND(Condition, Id, Id) },
		{ true,  true,  /* IEqual,                                  // 170 */ SPV_OPERAND(_) },
		{ true,  true,  /* INotEqual,                               // 171 */ SPV_OPERAND(_) },
		{ true,  true,  /* UGreaterThan,                            // 172 */ SPV_OPERAND(_) },
		{ true,  true,  /* SGreaterThan,                            // 173 */ SPV_OPERAND(_) },
		{ true,  true,  /* UGreaterThanEqual,                       // 174 */ SPV_OPERAND(_) },
		{ true,  true,  /* SGreaterThanEqual,                       // 175 */ SPV_OPERAND(_) },
		{ true,  true,  /* ULessThan,                               // 176 */ SPV_OPERAND(_) },
		{ true,  true,  /* SLessThan,                               // 177 */ SPV_OPERAND(_) },
		{ true,  true,  /* ULessThanEqual,                          // 178 */ SPV_OPERAND(_) },
		{ true,  true,  /* SLessThanEqual,                          // 179 */ SPV_OPERAND(_) },
		{ true,  true,  /* FOrdEqual,                               // 180 */ SPV_OPERAND(_) },
		{ true,  true,  /* FUnordEqual,                             // 181 */ SPV_OPERAND(_) },
		{ true,  true,  /* FOrdNotEqual,                            // 182 */ SPV_OPERAND(_) },
		{ true,  true,  /* FUnordNotEqual,                          // 183 */ SPV_OPERAND(_) },
		{ true,  true,  /* FOrdLessThan,                            // 184 */ SPV_OPERAND(_) },
		{ true,  true,  /* FUnordLessThan,                          // 185 */ SPV_OPERAND(_) },
		{ true,  true,  /* FOrdGreaterThan,                         // 186 */ SPV_OPERAND(_) },
		{ true,  true,  /* FUnordGreaterThan,                       // 187 */ SPV_OPERAND(_) },
		{ true,  true,  /* FOrdLessThanEqual,                       // 188 */ SPV_OPERAND(_) },
		{ true,  true,  /* FUnordLessThanEqual,                     // 189 */ SPV_OPERAND(_) },
		{ true,  true,  /* FOrdGreaterThanEqual,                    // 190 */ SPV_OPERAND(_) },
		{ true,  true,  /* FUnordGreaterThanEqual,                  // 191 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid192 // 192 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid193 // 193 */ SPV_OPERAND(_) },
		{ true,  true,  /* ShiftRightLogical,                       // 194 */ SPV_OPERAND(_) },
		{ true,  true,  /* ShiftRightArithmetic,                    // 195 */ SPV_OPERAND(_) },
		{ true,  true,  /* ShiftLeftLogical,                        // 196 */ SPV_OPERAND(_) },
		{ true,  true,  /* BitwiseOr,                               // 197 */ SPV_OPERAND(_) },
		{ true,  true,  /* BitwiseXor,                              // 198 */ SPV_OPERAND(_) },
		{ true,  true,  /* BitwiseAnd,                              // 199 */ SPV_OPERAND(_) },
		{ true,  true,  /* Not,                                     // 200 */ SPV_OPERAND(_) },
		{ true,  true,  /* BitFieldInsert,                          // 201 */ SPV_OPERAND(_) },
		{ true,  true,  /* BitFieldSExtract,                        // 202 */ SPV_OPERAND(_) },
		{ true,  true,  /* BitFieldUExtract,                        // 203 */ SPV_OPERAND(_) },
		{ true,  true,  /* BitReverse,                              // 204 */ SPV_OPERAND(_) },
		{ true,  true,  /* BitCount,                                // 205 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid206 // 206 */ SPV_OPERAND(_) },
		{ true,  true,  /* DPdx,                                    // 207 */ SPV_OPERAND(_) },
		{ true,  true,  /* DPdy,                                    // 208 */ SPV_OPERAND(_) },
		{ true,  true,  /* Fwidth,                                  // 209 */ SPV_OPERAND(_) },
		{ true,  true,  /* DPdxFine,                                // 210 */ SPV_OPERAND(_) },
		{ true,  true,  /* DPdyFine,                                // 211 */ SPV_OPERAND(_) },
		{ true,  true,  /* FwidthFine,                              // 212 */ SPV_OPERAND(_) },
		{ true,  true,  /* DPdxCoarse,                              // 213 */ SPV_OPERAND(_) },
		{ true,  true,  /* DPdyCoarse,                              // 214 */ SPV_OPERAND(_) },
		{ true,  true,  /* FwidthCoarse,                            // 215 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid216 // 216 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid217 // 217 */ SPV_OPERAND(_) },
		{ false, false, /* EmitVertex,                              // 218 */ SPV_OPERAND(_) },
		{ false, false, /* EndPrimitive,                            // 219 */ SPV_OPERAND(_) },
		{ false, false, /* EmitStreamVertex,                        // 220 */ SPV_OPERAND(_) },
		{ false, false, /* EndStreamPrimitive,                      // 221 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid222 // 222 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid223 // 223 */ SPV_OPERAND(_) },
		{ false, false, /* ControlBarrier,                          // 224 */ SPV_OPERAND(_) },
		{ false, false, /* MemoryBarrier,                           // 225 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid226 // 226 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicLoad,                              // 227 */ SPV_OPERAND(_) },
		{ false, false, /* AtomicStore,                             // 228 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicExchange,                          // 229 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicCompareExchange,                   // 230 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicCompareExchangeWeak,               // 231 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicIIncrement,                        // 232 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicIDecrement,                        // 233 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicIAdd,                              // 234 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicISub,                              // 235 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicSMin,                              // 236 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicUMin,                              // 237 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicSMax,                              // 238 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicUMax,                              // 239 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicAnd,                               // 240 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicOr,                                // 241 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicXor,                               // 242 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid243 // 243 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid244 // 244 */ SPV_OPERAND(_) },
		{ true,  true,  /* Phi,                                     // 245 */ SPV_OPERAND(_) },
		{ false, false, /* LoopMerge,                               // 246 */ SPV_OPERAND(_) },
		{ false, false, /* SelectionMerge,                          // 247 */ SPV_OPERAND(_) },
		{ false, true,  /* Label,                                   // 248 */ SPV_OPERAND(_) },
		{ false, false, /* Branch,                                  // 249 */ SPV_OPERAND(Id) },
		{ false, false, /* BranchConditional,                       // 250 */ SPV_OPERAND(Condition, Id, Id, LiteralRep) },
		{ false, false, /* Switch,                                  // 251 */ SPV_OPERAND(_) },
		{ false, false, /* Kill,                                    // 252 */ SPV_OPERAND(_) },
		{ false, false, /* Return,                                  // 253 */ SPV_OPERAND(_) },
		{ false, false, /* ReturnValue,                             // 254 */ SPV_OPERAND(Id) },
		{ false, false, /* Unreachable,                             // 255 */ SPV_OPERAND(_) },
		{ false, false, /* LifetimeStart,                           // 256 */ SPV_OPERAND(_) },
		{ false, false, /* LifetimeStop,                            // 257 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid258 // 258 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupAsyncCopy,                          // 259 */ SPV_OPERAND(_) },
		{ false, false, /* GroupWaitEvents,                         // 260 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupAll,                                // 261 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupAny,                                // 262 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupBroadcast,                          // 263 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupIAdd,                               // 264 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupFAdd,                               // 265 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupFMin,                               // 266 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupUMin,                               // 267 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupSMin,                               // 268 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupFMax,                               // 269 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupUMax,                               // 270 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupSMax,                               // 271 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid272 // 272 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid273 // 273 */ SPV_OPERAND(_) },
		{ true,  true,  /* ReadPipe,                                // 274 */ SPV_OPERAND(_) },
		{ true,  true,  /* WritePipe,                               // 275 */ SPV_OPERAND(_) },
		{ true,  true,  /* ReservedReadPipe,                        // 276 */ SPV_OPERAND(_) },
		{ true,  true,  /* ReservedWritePipe,                       // 277 */ SPV_OPERAND(_) },
		{ true,  true,  /* ReserveReadPipePackets,                  // 278 */ SPV_OPERAND(_) },
		{ true,  true,  /* ReserveWritePipePackets,                 // 279 */ SPV_OPERAND(_) },
		{ false, false, /* CommitReadPipe,                          // 280 */ SPV_OPERAND(_) },
		{ false, false, /* CommitWritePipe,                         // 281 */ SPV_OPERAND(_) },
		{ true,  true,  /* IsValidReserveId,                        // 282 */ SPV_OPERAND(_) },
		{ true,  true,  /* GetNumPipePackets,                       // 283 */ SPV_OPERAND(_) },
		{ true,  true,  /* GetMaxPipePackets,                       // 284 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupReserveReadPipePackets,             // 285 */ SPV_OPERAND(_) },
		{ true,  true,  /* GroupReserveWritePipePackets,            // 286 */ SPV_OPERAND(_) },
		{ false, false, /* GroupCommitReadPipe,                     // 287 */ SPV_OPERAND(_) },
		{ false, false, /* GroupCommitWritePipe,                    // 288 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid289 // 289 */ SPV_OPERAND(_) },
		{ false, false, /* ----------------------------- Invalid290 // 290 */ SPV_OPERAND(_) },
		{ true,  true,  /* EnqueueMarker,                           // 291 */ SPV_OPERAND(_) },
		{ true,  true,  /* EnqueueKernel,                           // 292 */ SPV_OPERAND(_) },
		{ true,  true,  /* GetKernelNDrangeSubGroupCount,           // 293 */ SPV_OPERAND(_) },
		{ true,  true,  /* GetKernelNDrangeMaxSubGroupSize,         // 294 */ SPV_OPERAND(_) },
		{ true,  true,  /* GetKernelWorkGroupSize,                  // 295 */ SPV_OPERAND(_) },
		{ true,  true,  /* GetKernelPreferredWorkGroupSizeMultiple, // 296 */ SPV_OPERAND(_) },
		{ false, false, /* RetainEvent,                             // 297 */ SPV_OPERAND(_) },
		{ false, false, /* ReleaseEvent,                            // 298 */ SPV_OPERAND(_) },
		{ true,  true,  /* CreateUserEvent,                         // 299 */ SPV_OPERAND(_) },
		{ true,  true,  /* IsValidEvent,                            // 300 */ SPV_OPERAND(_) },
		{ false, false, /* SetUserEventStatus,                      // 301 */ SPV_OPERAND(_) },
		{ false, false, /* CaptureEventProfilingInfo,               // 302 */ SPV_OPERAND(_) },
		{ true,  true,  /* GetDefaultQueue,                         // 303 */ SPV_OPERAND(_) },
		{ true,  true,  /* BuildNDRange,                            // 304 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseSampleImplicitLod,            // 305 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseSampleExplicitLod,            // 306 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseSampleDrefImplicitLod,        // 307 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseSampleDrefExplicitLod,        // 308 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseSampleProjImplicitLod,        // 309 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseSampleProjExplicitLod,        // 310 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseSampleProjDrefImplicitLod,    // 311 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseSampleProjDrefExplicitLod,    // 312 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseFetch,                        // 313 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseGather,                       // 314 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseDrefGather,                   // 315 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseTexelsResident,               // 316 */ SPV_OPERAND(_) },
		{ false, false, /* NoLine,                                  // 317 */ SPV_OPERAND(_) },
		{ true,  true,  /* AtomicFlagTestAndSet,                    // 318 */ SPV_OPERAND(_) },
		{ false, false, /* AtomicFlagClear,                         // 319 */ SPV_OPERAND(_) },
		{ true,  true,  /* ImageSparseRead,                         // 320 */ SPV_OPERAND(_) },
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_spvOpcodeInfo) == SpvOpcode::Count);

	const char* s_spvOpcode[] =
	{
		"Nop",
		"Undef",
		"SourceContinued",
		"Source",
		"SourceExtension",
		"Name",
		"MemberName",
		"String",
		"Line",
		"Invalid9",
		"Extension",
		"ExtInstImport",
		"ExtInst",
		"Invalid13",
		"MemoryModel",
		"EntryPoint",
		"ExecutionMode",
		"Capability",
		"Invalid18",
>>>>>>> upstream/master
		"TypeVoid",
		"TypeBool",
		"TypeInt",
		"TypeFloat",
		"TypeVector",
		"TypeMatrix",
<<<<<<< HEAD
		"TypeSampler",
		"TypeFilter",
=======
		"TypeImage",
		"TypeSampler",
		"TypeSampledImage",
>>>>>>> upstream/master
		"TypeArray",
		"TypeRuntimeArray",
		"TypeStruct",
		"TypeOpaque",
		"TypePointer",
		"TypeFunction",
		"TypeEvent",
		"TypeDeviceEvent",
		"TypeReserveId",
		"TypeQueue",
		"TypePipe",
<<<<<<< HEAD
=======
		"TypeForwardPointer",
		"Invalid40",
>>>>>>> upstream/master
		"ConstantTrue",
		"ConstantFalse",
		"Constant",
		"ConstantComposite",
		"ConstantSampler",
<<<<<<< HEAD
		"ConstantNullPointer",
		"ConstantNullObject",
=======
		"ConstantNull",
		"Invalid47",
>>>>>>> upstream/master
		"SpecConstantTrue",
		"SpecConstantFalse",
		"SpecConstant",
		"SpecConstantComposite",
<<<<<<< HEAD
		"Variable",
		"VariableArray",
=======
		"SpecConstantOp",
		"Invalid53",
>>>>>>> upstream/master
		"Function",
		"FunctionParameter",
		"FunctionEnd",
		"FunctionCall",
<<<<<<< HEAD
		"ExtInst",
		"Undef",
		"Load",
		"Store",
		"Phi",
		"DecorationGroup",
		"Decorate",
		"MemberDecorate",
		"GroupDecorate",
		"GroupMemberDecorate",
		"Name",
		"MemberName",
		"String",
		"Line",
=======
		"Invalid58",
		"Variable",
		"ImageTexelPointer",
		"Load",
		"Store",
		"CopyMemory",
		"CopyMemorySized",
		"AccessChain",
		"InBoundsAccessChain",
		"PtrAccessChain",
		"ArrayLength",
		"GenericPtrMemSemantics",
		"InBoundsPtrAccessChain",
		"Decorate",
		"MemberDecorate",
		"DecorationGroup",
		"GroupDecorate",
		"GroupMemberDecorate",
		"Invalid76",
>>>>>>> upstream/master
		"VectorExtractDynamic",
		"VectorInsertDynamic",
		"VectorShuffle",
		"CompositeConstruct",
		"CompositeExtract",
		"CompositeInsert",
		"CopyObject",
<<<<<<< HEAD
		"CopyMemory",
		"CopyMemorySized",
		"Sampler",
		"TextureSample",
		"TextureSampleDref",
		"TextureSampleLod",
		"TextureSampleProj",
		"TextureSampleGrad",
		"TextureSampleOffset",
		"TextureSampleProjLod",
		"TextureSampleProjGrad",
		"TextureSampleLodOffset",
		"TextureSampleProjOffset",
		"TextureSampleGradOffset",
		"TextureSampleProjLodOffset",
		"TextureSampleProjGradOffset",
		"TextureFetchTexelLod",
		"TextureFetchTexelOffset",
		"TextureFetchSample",
		"TextureFetchTexel",
		"TextureGather",
		"TextureGatherOffset",
		"TextureGatherOffsets",
		"TextureQuerySizeLod",
		"TextureQuerySize",
		"TextureQueryLod",
		"TextureQueryLevels",
		"TextureQuerySamples",
		"AccessChain",
		"InBoundsAccessChain",
		"SNegate",
		"FNegate",
		"Not",
		"Any",
		"All",
=======
		"Transpose",
		"Invalid85",
		"SampledImage",
		"ImageSampleImplicitLod",
		"ImageSampleExplicitLod",
		"ImageSampleDrefImplicitLod",
		"ImageSampleDrefExplicitLod",
		"ImageSampleProjImplicitLod",
		"ImageSampleProjExplicitLod",
		"ImageSampleProjDrefImplicitLod",
		"ImageSampleProjDrefExplicitLod",
		"ImageFetch",
		"ImageGather",
		"ImageDrefGather",
		"ImageRead",
		"ImageWrite",
		"Image",
		"ImageQueryFormat",
		"ImageQueryOrder",
		"ImageQuerySizeLod",
		"ImageQuerySize",
		"ImageQueryLod",
		"ImageQueryLevels",
		"ImageQuerySamples",
		"Invalid108",
>>>>>>> upstream/master
		"ConvertFToU",
		"ConvertFToS",
		"ConvertSToF",
		"ConvertUToF",
		"UConvert",
		"SConvert",
		"FConvert",
<<<<<<< HEAD
		"ConvertPtrToU",
		"ConvertUToPtr",
		"PtrCastToGeneric",
		"GenericCastToPtr",
		"Bitcast",
		"Transpose",
		"IsNan",
		"IsInf",
		"IsFinite",
		"IsNormal",
		"SignBitSet",
		"LessOrGreater",
		"Ordered",
		"Unordered",
		"ArrayLength",
=======
		"QuantizeToF16",
		"ConvertPtrToU",
		"SatConvertSToU",
		"SatConvertUToS",
		"ConvertUToPtr",
		"PtrCastToGeneric",
		"GenericCastToPtr",
		"GenericCastToPtrExplicit",
		"Bitcast",
		"Invalid125",
		"SNegate",
		"FNegate",
>>>>>>> upstream/master
		"IAdd",
		"FAdd",
		"ISub",
		"FSub",
		"IMul",
		"FMul",
		"UDiv",
		"SDiv",
		"FDiv",
		"UMod",
		"SRem",
		"SMod",
		"FRem",
		"FMod",
		"VectorTimesScalar",
		"MatrixTimesScalar",
		"VectorTimesMatrix",
		"MatrixTimesVector",
		"MatrixTimesMatrix",
		"OuterProduct",
		"Dot",
<<<<<<< HEAD
		"ShiftRightLogical",
		"ShiftRightArithmetic",
		"ShiftLeftLogical",
		"LogicalOr",
		"LogicalXor",
		"LogicalAnd",
		"BitwiseOr",
		"BitwiseXor",
		"BitwiseAnd",
		"Select",
		"IEqual",
		"FOrdEqual",
		"FUnordEqual",
		"INotEqual",
		"FOrdNotEqual",
		"FUnordNotEqual",
		"ULessThan",
		"SLessThan",
		"FOrdLessThan",
		"FUnordLessThan",
		"UGreaterThan",
		"SGreaterThan",
		"FOrdGreaterThan",
		"FUnordGreaterThan",
		"ULessThanEqual",
		"SLessThanEqual",
		"FOrdLessThanEqual",
		"FUnordLessThanEqual",
		"UGreaterThanEqual",
		"SGreaterThanEqual",
		"FOrdGreaterThanEqual",
		"FUnordGreaterThanEqual",
=======
		"IAddCarry",
		"ISubBorrow",
		"UMulExtended",
		"SMulExtended",
		"Invalid153",
		"Any",
		"All",
		"IsNan",
		"IsInf",
		"IsFinite",
		"IsNormal",
		"SignBitSet",
		"LessOrGreater",
		"Ordered",
		"Unordered",
		"LogicalEqual",
		"LogicalNotEqual",
		"LogicalOr",
		"LogicalAnd",
		"LogicalNot",
		"Select",
		"IEqual",
		"INotEqual",
		"UGreaterThan",
		"SGreaterThan",
		"UGreaterThanEqual",
		"SGreaterThanEqual",
		"ULessThan",
		"SLessThan",
		"ULessThanEqual",
		"SLessThanEqual",
		"FOrdEqual",
		"FUnordEqual",
		"FOrdNotEqual",
		"FUnordNotEqual",
		"FOrdLessThan",
		"FUnordLessThan",
		"FOrdGreaterThan",
		"FUnordGreaterThan",
		"FOrdLessThanEqual",
		"FUnordLessThanEqual",
		"FOrdGreaterThanEqual",
		"FUnordGreaterThanEqual",
		"Invalid192",
		"Invalid193",
		"ShiftRightLogical",
		"ShiftRightArithmetic",
		"ShiftLeftLogical",
		"BitwiseOr",
		"BitwiseXor",
		"BitwiseAnd",
		"Not",
		"BitFieldInsert",
		"BitFieldSExtract",
		"BitFieldUExtract",
		"BitReverse",
		"BitCount",
		"Invalid206",
>>>>>>> upstream/master
		"DPdx",
		"DPdy",
		"Fwidth",
		"DPdxFine",
		"DPdyFine",
		"FwidthFine",
		"DPdxCoarse",
		"DPdyCoarse",
		"FwidthCoarse",
<<<<<<< HEAD
		"EmitVertex",
		"EndPrimitive",
		"EmitStreamVertex",
		"EndStreamPrimitive",
		"ControlBarrier",
		"MemoryBarrier",
		"ImagePointer",
		"AtomicInit",
=======
		"Invalid216",
		"Invalid217",
		"EmitVertex",
		"EndPrimitive",
		"EmitStreamVertex",
		"Invalid222",
		"Invalid223",
		"EndStreamPrimitive",
		"ControlBarrier",
		"MemoryBarrier",
		"Invalid226",
>>>>>>> upstream/master
		"AtomicLoad",
		"AtomicStore",
		"AtomicExchange",
		"AtomicCompareExchange",
		"AtomicCompareExchangeWeak",
		"AtomicIIncrement",
		"AtomicIDecrement",
		"AtomicIAdd",
		"AtomicISub",
<<<<<<< HEAD
		"AtomicUMin",
=======
		"AtomicSMin",
		"AtomicUMin",
		"AtomicSMax",
>>>>>>> upstream/master
		"AtomicUMax",
		"AtomicAnd",
		"AtomicOr",
		"AtomicXor",
<<<<<<< HEAD
=======
		"Invalid243",
		"Invalid244",
		"Phi",
>>>>>>> upstream/master
		"LoopMerge",
		"SelectionMerge",
		"Label",
		"Branch",
		"BranchConditional",
		"Switch",
		"Kill",
		"Return",
		"ReturnValue",
		"Unreachable",
		"LifetimeStart",
		"LifetimeStop",
<<<<<<< HEAD
		"CompileFlag",
		"AsyncGroupCopy",
		"WaitGroupEvents",
=======
		"Invalid258",
		"GroupAsyncCopy",
		"GroupWaitEvents",
>>>>>>> upstream/master
		"GroupAll",
		"GroupAny",
		"GroupBroadcast",
		"GroupIAdd",
		"GroupFAdd",
		"GroupFMin",
		"GroupUMin",
		"GroupSMin",
		"GroupFMax",
		"GroupUMax",
		"GroupSMax",
<<<<<<< HEAD
		"GenericCastToPtrExplicit",
		"GenericPtrMemSemantics",
=======
		"Invalid272",
		"Invalid273",
>>>>>>> upstream/master
		"ReadPipe",
		"WritePipe",
		"ReservedReadPipe",
		"ReservedWritePipe",
		"ReserveReadPipePackets",
		"ReserveWritePipePackets",
		"CommitReadPipe",
		"CommitWritePipe",
		"IsValidReserveId",
		"GetNumPipePackets",
		"GetMaxPipePackets",
		"GroupReserveReadPipePackets",
		"GroupReserveWritePipePackets",
		"GroupCommitReadPipe",
		"GroupCommitWritePipe",
<<<<<<< HEAD
=======
		"Invalid289",
		"Invalid290",
>>>>>>> upstream/master
		"EnqueueMarker",
		"EnqueueKernel",
		"GetKernelNDrangeSubGroupCount",
		"GetKernelNDrangeMaxSubGroupSize",
		"GetKernelWorkGroupSize",
		"GetKernelPreferredWorkGroupSizeMultiple",
		"RetainEvent",
		"ReleaseEvent",
		"CreateUserEvent",
		"IsValidEvent",
		"SetUserEventStatus",
		"CaptureEventProfilingInfo",
		"GetDefaultQueue",
		"BuildNDRange",
<<<<<<< HEAD
		"SatConvertSToU",
		"SatConvertUToS",
		"AtomicIMin",
		"AtomicIMax",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_spirvOpcode) == SpirvOpcode::Count);

	const char* getName(SpirvOpcode::Enum _opcode)
	{
		BX_CHECK(_opcode < SpirvOpcode::Count, "Unknown opcode id %d.", _opcode);
		return s_spirvOpcode[_opcode];
	}

	int32_t read(bx::ReaderI* _reader, SpirvOperand& _operand)
	{
		int32_t size = 0;

		BX_UNUSED(_operand);
		uint32_t token;
		size += bx::read(_reader, token);
=======
		"ImageSparseSampleImplicitLod",
		"ImageSparseSampleExplicitLod",
		"ImageSparseSampleDrefImplicitLod",
		"ImageSparseSampleDrefExplicitLod",
		"ImageSparseSampleProjImplicitLod",
		"ImageSparseSampleProjExplicitLod",
		"ImageSparseSampleProjDrefImplicitLod",
		"ImageSparseSampleProjDrefExplicitLod",
		"ImageSparseFetch",
		"ImageSparseGather",
		"ImageSparseDrefGather",
		"ImageSparseTexelsResident",
		"NoLine",
		"AtomicFlagTestAndSet",
		"AtomicFlagClear",
		"ImageSparseRead",
		"",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_spvOpcode)-1 == SpvOpcode::Count);

	const char* getName(SpvOpcode::Enum _opcode)
	{
		BX_WARN(_opcode <= SpvOpcode::Count, "Unknown opcode id %d.", _opcode);
		return _opcode <= SpvOpcode::Count
			?  s_spvOpcode[_opcode]
			: "?SpvOpcode?"
			;
	}

	struct SpvDecorationInfo
	{
		SpvOperand::Enum operands[2];
	};

	static const SpvDecorationInfo s_spvDecorationInfo[] =
	{
		{ /* RelaxedPrecision     */ SPV_OPERAND(_) },
		{ /* SpecId               */ SPV_OPERAND(LiteralNumber) },
		{ /* Block                */ SPV_OPERAND(_) },
		{ /* BufferBlock          */ SPV_OPERAND(_) },
		{ /* RowMajor             */ SPV_OPERAND(_) },
		{ /* ColMajor             */ SPV_OPERAND(_) },
		{ /* ArrayStride          */ SPV_OPERAND(LiteralNumber) },
		{ /* MatrixStride         */ SPV_OPERAND(LiteralNumber) },
		{ /* GLSLShared           */ SPV_OPERAND(_) },
		{ /* GLSLPacked           */ SPV_OPERAND(_) },
		{ /* CPacked              */ SPV_OPERAND(_) },
		{ /* BuiltIn              */ SPV_OPERAND(LiteralNumber) },
		{ /* Unknown12            */ SPV_OPERAND(_) },
		{ /* NoPerspective        */ SPV_OPERAND(_) },
		{ /* Flat                 */ SPV_OPERAND(_) },
		{ /* Patch                */ SPV_OPERAND(_) },
		{ /* Centroid             */ SPV_OPERAND(_) },
		{ /* Sample               */ SPV_OPERAND(_) },
		{ /* Invariant            */ SPV_OPERAND(_) },
		{ /* Restrict             */ SPV_OPERAND(_) },
		{ /* Aliased              */ SPV_OPERAND(_) },
		{ /* Volatile             */ SPV_OPERAND(_) },
		{ /* Constant             */ SPV_OPERAND(_) },
		{ /* Coherent             */ SPV_OPERAND(_) },
		{ /* NonWritable          */ SPV_OPERAND(_) },
		{ /* NonReadable          */ SPV_OPERAND(_) },
		{ /* Uniform              */ SPV_OPERAND(_) },
		{ /* Unknown27            */ SPV_OPERAND(_) },
		{ /* SaturatedConversion  */ SPV_OPERAND(_) },
		{ /* Stream               */ SPV_OPERAND(LiteralNumber) },
		{ /* Location             */ SPV_OPERAND(LiteralNumber) },
		{ /* Component            */ SPV_OPERAND(LiteralNumber) },
		{ /* Index                */ SPV_OPERAND(LiteralNumber) },
		{ /* Binding              */ SPV_OPERAND(LiteralNumber) },
		{ /* DescriptorSet        */ SPV_OPERAND(LiteralNumber) },
		{ /* Offset               */ SPV_OPERAND(LiteralNumber) },
		{ /* XfbBuffer            */ SPV_OPERAND(LiteralNumber) },
		{ /* XfbStride            */ SPV_OPERAND(LiteralNumber) },
		{ /* FuncParamAttr        */ SPV_OPERAND(_) },
		{ /* FPRoundingMode       */ SPV_OPERAND(_) },
		{ /* FPFastMathMode       */ SPV_OPERAND(_) },
		{ /* LinkageAttributes    */ SPV_OPERAND(LiteralString, LinkageType) },
		{ /* NoContraction        */ SPV_OPERAND(_) },
		{ /* InputAttachmentIndex */ SPV_OPERAND(LiteralNumber) },
		{ /* Alignment            */ SPV_OPERAND(LiteralNumber) },
	};

	static const char* s_spvDecoration[] =
	{
		"RelaxedPrecision",
		"SpecId",
		"Block",
		"BufferBlock",
		"RowMajor",
		"ColMajor",
		"ArrayStride",
		"MatrixStride",
		"GLSLShared",
		"GLSLPacked",
		"CPacked",
		"BuiltIn",
		"Unknown12",
		"NoPerspective",
		"Flat",
		"Patch",
		"Centroid",
		"Sample",
		"Invariant",
		"Restrict",
		"Aliased",
		"Volatile",
		"Constant",
		"Coherent",
		"NonWritable",
		"NonReadable",
		"Uniform",
		"Unknown27",
		"SaturatedConversion",
		"Stream",
		"Location",
		"Component",
		"Index",
		"Binding",
		"DescriptorSet",
		"Offset",
		"XfbBuffer",
		"XfbStride",
		"FuncParamAttr",
		"FPRoundingMode",
		"FPFastMathMode",
		"LinkageAttributes",
		"NoContraction",
		"InputAttachmentIndex",
		"Alignment",
		""
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_spvDecoration)-1 == SpvDecoration::Count);

	const char* getName(SpvDecoration::Enum _enum)
	{
		BX_UNUSED(s_spvDecorationInfo);
		BX_CHECK(_enum <= SpvDecoration::Count, "Unknown decoration id %d.", _enum);
		return _enum <= SpvDecoration::Count
			?  s_spvDecoration[_enum]
			: "?SpvDecoration?"
			;
	}

#undef _
#undef SPV_OPERAND

	static const char* s_spvStorageClass[] =
	{
		"UniformConstant",
		"Input",
		"Uniform",
		"Output",
		"Workgroup",
		"CrossWorkgroup",
		"Private",
		"Function",
		"Generic",
		"PushConstant",
		"AtomicCounter",
		"Image",
		""
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_spvStorageClass)-1 == SpvStorageClass::Count);

	const char* getName(SpvStorageClass::Enum _enum)
	{
		BX_CHECK(_enum <= SpvStorageClass::Count, "Unknown storage class id %d.", _enum);
		return _enum <= SpvStorageClass::Count
			?  s_spvStorageClass[_enum]
			: "?SpvStorageClass?"
			;
	}

	static const char* s_spvBuiltin[] =
	{
		"Position",
		"PointSize",
		"ClipDistance",
		"CullDistance",
		"VertexId",
		"InstanceId",
		"PrimitiveId",
		"InvocationId",
		"Layer",
		"ViewportIndex",
		"TessLevelOuter",
		"TessLevelInner",
		"TessCoord",
		"PatchVertices",
		"FragCoord",
		"PointCoord",
		"FrontFacing",
		"SampleId",
		"SamplePosition",
		"SampleMask",
		"FragDepth",
		"HelperInvocation",
		"NumWorkgroups",
		"WorkgroupSize",
		"WorkgroupId",
		"LocalInvocationId",
		"GlobalInvocationId",
		"LocalInvocationIndex",
		"WorkDim",
		"GlobalSize",
		"EnqueuedWorkgroupSize",
		"GlobalOffset",
		"GlobalLinearId",
		"SubgroupSize",
		"SubgroupMaxSize",
		"NumSubgroups",
		"NumEnqueuedSubgroups",
		"SubgroupId",
		"SubgroupLocalInvocationId",
		"VertexIndex",
		"InstanceIndex",
		"",
	};
	BX_STATIC_ASSERT(BX_COUNTOF(s_spvBuiltin)-1 == SpvBuiltin::Count);

	const char* getName(SpvBuiltin::Enum _enum)
	{
		BX_CHECK(_enum <= SpvBuiltin::Count, "Unknown builtin id %d.", _enum);
		return _enum <= SpvBuiltin::Count
			?  s_spvBuiltin[_enum]
			: "?SpvBuiltin?"
			;
	}

	int32_t read(bx::ReaderI* _reader, SpvOperand& _operand, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t token;
		_operand.literalString = "";

		switch (_operand.type)
		{
		case SpvOperand::LiteralString:
			do
			{
				size += bx::read(_reader, token, _err);
				_operand.literalString.append( (char*)&token, (char*)&token + sizeof(token) );
			}
			while (0 != (token & 0xff000000) && _err->isOk() );
			break;

		default:
			size += bx::read(_reader, _operand.data, _err);
			break;
		}
>>>>>>> upstream/master

		return size;
	}

<<<<<<< HEAD
	int32_t read(bx::ReaderI* _reader, SpirvInstruction& _instruction)
=======
	int32_t read(bx::ReaderI* _reader, SpvInstruction& _instruction, bx::Error* _err)
>>>>>>> upstream/master
	{
		int32_t size = 0;

		uint32_t token;
<<<<<<< HEAD
		size += bx::read(_reader, token);

		_instruction.opcode = SpirvOpcode::Enum( (token & UINT32_C(0x0000ffff) )      );
		_instruction.length =          uint16_t( (token & UINT32_C(0xffff0000) ) >> 16);

		uint32_t currOp = 0;

		const SpirvOpcodeInfo& info = s_sprivOpcodeInfo[_instruction.opcode];

		if (0 < info.numValues)
		{
			size += read(_reader, _instruction.un.value, info.numValues*sizeof(uint32_t) );
		}

		if (info.hasVariable)
		{
			while (size/4 != _instruction.length)
			{
				uint32_t tmp;
				size += bx::read(_reader, tmp);
			}
		}
		else
		{
			_instruction.numOperands = info.numOperands;
			switch (info.numOperands)
			{
			case 6: size += read(_reader, _instruction.operand[currOp++]);
			case 5: size += read(_reader, _instruction.operand[currOp++]);
			case 4: size += read(_reader, _instruction.operand[currOp++]);
			case 3: size += read(_reader, _instruction.operand[currOp++]);
			case 2: size += read(_reader, _instruction.operand[currOp++]);
			case 1: size += read(_reader, _instruction.operand[currOp++]);
			case 0:
				break;

			default:
				BX_WARN(false, "Instruction %s with invalid number of operands %d (numValues %d)."
						, getName(_instruction.opcode)
						, info.numOperands
						, info.numValues
						);
				break;
			}

			BX_WARN(size/4 == _instruction.length, "read %d, expected %d, %s"
					, size/4
					, _instruction.length
					, getName(_instruction.opcode)
					);
			while (size/4 != _instruction.length)
			{
				uint32_t tmp;
				size += bx::read(_reader, tmp);
			}
		}

		return size;
	}

	int32_t write(bx::WriterI* _writer, const SpirvInstruction& _instruction)
	{
		int32_t size = 0;
		BX_UNUSED(_writer, _instruction);
		return size;
	}

	int32_t toString(char* _out, int32_t _size, const SpirvInstruction& _instruction)
	{
		int32_t size = 0;
		size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
					, "%s %d (%d, %d)"
					, getName(_instruction.opcode)
					, _instruction.numOperands
					, _instruction.un.value[0]
					, _instruction.un.value[1]
					);

		return size;
	}

	int32_t read(bx::ReaderSeekerI* _reader, SpirvShader& _shader)
	{
		int32_t size = 0;

		uint32_t len = uint32_t(bx::getSize(_reader) - bx::seek(_reader) );
		_shader.byteCode.resize(len);
		size += bx::read(_reader, _shader.byteCode.data(), len);
=======
		size += bx::read(_reader, token, _err);

		_instruction.opcode = SpvOpcode::Enum( (token & UINT32_C(0x0000ffff) )      );
		_instruction.length =        uint16_t( (token & UINT32_C(0xffff0000) ) >> 16);

		if (_instruction.opcode >= SpvOpcode::Count)
		{
			BX_ERROR_SET(_err, BGFX_SHADER_SPIRV_INVALID_INSTRUCTION, "SPIR-V: Invalid instruction.");
			return size;
		}

		if (0 == _instruction.length)
		{
			return size;
		}

		const SpvOpcodeInfo& info = s_spvOpcodeInfo[_instruction.opcode];
		_instruction.hasType   = info.hasType;
		_instruction.hasResult = info.hasResult;

		if (info.hasType)
		{
			size += read(_reader, _instruction.type, _err);
		}
		else
		{
			_instruction.type = UINT32_MAX;
		}

		if (info.hasResult)
		{
			size += read(_reader, _instruction.result, _err);
		}
		else
		{
			_instruction.result = UINT32_MAX;
		}

		uint16_t currOp = 0;
		switch (_instruction.opcode)
		{
		case SpvOpcode::EntryPoint:
			_instruction.operand[currOp].type = info.operands[currOp];
			size += read(_reader, _instruction.operand[currOp++], _err);
			_instruction.operand[currOp].type = info.operands[currOp];
			size += read(_reader, _instruction.operand[currOp++], _err);
			_instruction.operand[currOp].type = info.operands[currOp];
			size += read(_reader, _instruction.operand[currOp++], _err);

			_instruction.operand[currOp].type = SpvOperand::Id;
			for (uint32_t ii = 0, num = _instruction.length - size/4; ii < num; ++ii)
			{
				size += read(_reader, _instruction.operand[currOp], _err);
			}
			break;

		default:
			for (
				;  size/4 != _instruction.length
				&& _err->isOk()
				&& currOp < BX_COUNTOF(_instruction.operand)
				; ++currOp)
			{
				_instruction.operand[currOp].type = info.operands[currOp];
				size += read(_reader, _instruction.operand[currOp], _err);
			}
			break;
		}

		_instruction.numOperands = currOp;

		return size;
	}

	int32_t write(bx::WriterI* _writer, const SpvInstruction& _instruction, bx::Error* _err)
	{
		int32_t size = 0;
		BX_UNUSED(_writer, _instruction, _err);
		return size;
	}

	int32_t toString(char* _out, int32_t _size, const SpvInstruction& _instruction)
	{
		int32_t size = 0;

		if (_instruction.hasResult)
		{
			if (_instruction.hasType)
			{
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, " r%d.t%d = "
							, _instruction.result
							, _instruction.type
							);
			}
			else
			{
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, " r%d = "
							, _instruction.result
							);
			}
		}

		size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
					, "%s"
					, getName(_instruction.opcode)
					);

		for (uint32_t ii = 0, num = _instruction.numOperands; ii < num; ++ii)
		{
			const SpvOperand& operand = _instruction.operand[ii];
			switch (operand.type)
			{
			case SpvOperand::AddressingModel:
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%sAddressingModel(%d)"
							, 0 == ii ? " " : ", "
							, operand.data
							);
				break;

			case SpvOperand::Decoration:
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%s%s"
							, 0 == ii ? " " : ", "
							, getName(SpvDecoration::Enum(operand.data) )
							);
				break;

			case SpvOperand::FunctionControl:
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%s0x%08x"
							, 0 == ii ? " " : ", "
							, operand.data
							);
				break;

			case SpvOperand::LiteralNumber:
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%s%d"
							, 0 == ii ? " " : ", "
							, operand.data
							);
				break;

			case SpvOperand::LiteralString:
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%s%s"
							, 0 == ii ? " " : ", "
							, operand.literalString.c_str()
							);
				break;

			case SpvOperand::MemoryModel:
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%sMemoryModel(%d)"
							, 0 == ii ? " " : ", "
							, operand.data
							);
				break;

			case SpvOperand::StorageClass:
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%s%s"
							, 0 == ii ? " " : ", "
							, getName(SpvStorageClass::Enum(operand.data) )
							);
				break;

			case SpvOperand::Count:
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%s__%d__"
							, 0 == ii ? " " : ", "
							, operand.data
							);
				break;

			default:
				size += bx::snprintf(&_out[size], bx::uint32_imax(0, _size-size)
							, "%sr%d"
							, 0 == ii ? " " : ", "
							, operand.data
							);
				break;

			}
		}

		return size;
	}

	int32_t read(bx::ReaderSeekerI* _reader, SpvShader& _shader, bx::Error* _err)
	{
		int32_t size = 0;

		uint32_t numBytes = uint32_t(bx::getSize(_reader) - bx::seek(_reader) );
		_shader.byteCode.resize(numBytes);
		size += bx::read(_reader, _shader.byteCode.data(), numBytes, _err);
>>>>>>> upstream/master

		return size;
	}

<<<<<<< HEAD
	int32_t write(bx::WriterI* _writer, const SpirvShader& _shader)
	{
		int32_t size = 0;
		BX_UNUSED(_writer, _shader);
=======
	int32_t write(bx::WriterI* _writer, const SpvShader& _shader, bx::Error* _err)
	{
		int32_t size = 0;
		BX_UNUSED(_writer, _shader, _err);
>>>>>>> upstream/master
		return size;
	}

#define SPIRV_MAGIC 0x07230203

<<<<<<< HEAD
	int32_t read(bx::ReaderSeekerI* _reader, Spirv& _spirv)
	{
		int32_t size = 0;

		size += bx::read(_reader, _spirv.header);

		if (size != sizeof(Spirv::Header)
		||  _spirv.header.magic != SPIRV_MAGIC
		   )
		{
			// error
			return -size;
		}

		size += read(_reader, _spirv.shader);
=======
	int32_t read(bx::ReaderSeekerI* _reader, SpirV& _spirv, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err);

		int32_t size = 0;

		size += bx::read(_reader, _spirv.header, _err);

		if (!_err->isOk()
		||  size != sizeof(SpirV::Header)
		||  _spirv.header.magic != SPIRV_MAGIC
		   )
		{
			BX_ERROR_SET(_err, BGFX_SHADER_SPIRV_INVALID_HEADER, "SPIR-V: Invalid header.");
			return size;
		}

		size += read(_reader, _spirv.shader, _err);
>>>>>>> upstream/master

		return size;
	}

<<<<<<< HEAD
	int32_t write(bx::WriterSeekerI* _writer, const Spirv& _spirv)
	{
		int32_t size = 0;
		BX_UNUSED(_writer, _spirv);
		return size;
	}

	void parse(const SpirvShader& _src, SpirvParseFn _fn, void* _userData)
	{
		bx::MemoryReader reader(_src.byteCode.data(), uint32_t(_src.byteCode.size() ) );

		for (uint32_t token = 0, numTokens = uint32_t(_src.byteCode.size() / sizeof(uint32_t) ); token < numTokens;)
		{
			SpirvInstruction instruction;
			uint32_t size = read(&reader, instruction);
			BX_CHECK(size/4 == instruction.length, "read %d, expected %d, %s"
					, size/4
					, instruction.length
					, getName(instruction.opcode)
					);
			BX_UNUSED(size);

			_fn(token * sizeof(uint32_t), instruction, _userData);
=======
	int32_t write(bx::WriterSeekerI* _writer, const SpirV& _spirv, bx::Error* _err)
	{
		int32_t size = 0;
		BX_UNUSED(_writer, _spirv, _err);
		return size;
	}

	void parse(const SpvShader& _src, SpvParseFn _fn, void* _userData, bx::Error* _err)
	{
		BX_ERROR_SCOPE(_err);

		uint32_t numBytes = uint32_t(_src.byteCode.size() );
		bx::MemoryReader reader(_src.byteCode.data(), numBytes);

		for (uint32_t token = 0, numTokens = uint32_t(_src.byteCode.size() / sizeof(uint32_t) ); token < numTokens;)
		{
			SpvInstruction instruction;
			uint32_t size = read(&reader, instruction, _err);

			if (!_err->isOk() )
			{
				return;
			}

			if (size/4 != instruction.length)
			{
				BX_TRACE("read %d, expected %d, %s"
						, size/4
						, instruction.length
						, getName(instruction.opcode)
						);
				BX_ERROR_SET(_err, BGFX_SHADER_SPIRV_INVALID_INSTRUCTION, "SPIR-V: Invalid instruction.");
				return;
			}

			bool cont = _fn(token * sizeof(uint32_t), instruction, _userData);
			if (!cont)
			{
				return;
			}
>>>>>>> upstream/master

			token += instruction.length;
		}
	}

} // namespace bgfx
