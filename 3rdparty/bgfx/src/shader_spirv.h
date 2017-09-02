/*
<<<<<<< HEAD
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
=======
 * Copyright 2011-2017 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
>>>>>>> upstream/master
 */

#ifndef BGFX_SHADER_SPIRV_H
#define BGFX_SHADER_SPIRV_H

#include <bx/readerwriter.h>

<<<<<<< HEAD
=======
BX_ERROR_RESULT(BGFX_SHADER_SPIRV_INVALID_HEADER,      BX_MAKEFOURCC('S', 'H', 0, 1) );
BX_ERROR_RESULT(BGFX_SHADER_SPIRV_INVALID_INSTRUCTION, BX_MAKEFOURCC('S', 'H', 0, 2) );

#define SPV_CHUNK_HEADER BX_MAKEFOURCC(0x03, 0x02, 0x23, 0x07)

>>>>>>> upstream/master
namespace bgfx
{
	// Reference: https://www.khronos.org/registry/spir-v/specs/1.0/SPIRV.html

<<<<<<< HEAD
	struct SpirvOpcode
=======
	struct SpvOpcode
>>>>>>> upstream/master
	{
		enum Enum
		{
			Nop,
<<<<<<< HEAD
			Source,
			SourceExtension,
			Extension,
			ExtInstImport,
			MemoryModel,
			EntryPoint,
			ExecutionMode,
=======
			Undef,
			SourceContinued,
			Source,
			SourceExtension,
			Name,
			MemberName,
			String,
			Line,
			Invalid9,
			Extension,
			ExtInstImport,
			ExtInst,
			Invalid13,
			MemoryModel,
			EntryPoint,
			ExecutionMode,
			Capability,
			Invalid18,
>>>>>>> upstream/master
			TypeVoid,
			TypeBool,
			TypeInt,
			TypeFloat,
			TypeVector,
			TypeMatrix,
<<<<<<< HEAD
			TypeSampler,
			TypeFilter,
=======
			TypeImage,
			TypeSampler,
			TypeSampledImage,
>>>>>>> upstream/master
			TypeArray,
			TypeRuntimeArray,
			TypeStruct,
			TypeOpaque,
			TypePointer,
			TypeFunction,
			TypeEvent,
			TypeDeviceEvent,
			TypeReserveId,
			TypeQueue,
			TypePipe,
<<<<<<< HEAD
=======
			TypeForwardPointer,
			Invalid40,
>>>>>>> upstream/master
			ConstantTrue,
			ConstantFalse,
			Constant,
			ConstantComposite,
			ConstantSampler,
<<<<<<< HEAD
			ConstantNullPointer,
			ConstantNullObject,
=======
			ConstantNull,
			Invalid47,
>>>>>>> upstream/master
			SpecConstantTrue,
			SpecConstantFalse,
			SpecConstant,
			SpecConstantComposite,
<<<<<<< HEAD
			Variable,
			VariableArray,
=======
			SpecConstantOp,
			Invalid53,
>>>>>>> upstream/master
			Function,
			FunctionParameter,
			FunctionEnd,
			FunctionCall,
<<<<<<< HEAD
			ExtInst,
			Undef,
			Load,
			Store,
			Phi,
			DecorationGroup,
			Decorate,
			MemberDecorate,
			GroupDecorate,
			GroupMemberDecorate,
			Name,
			MemberName,
			String,
			Line,
=======
			Invalid58,
			Variable,
			ImageTexelPointer,
			Load,
			Store,
			CopyMemory,
			CopyMemorySized,
			AccessChain,
			InBoundsAccessChain,
			PtrAccessChain,
			ArrayLength,
			GenericPtrMemSemantics,
			InBoundsPtrAccessChain,
			Decorate,
			MemberDecorate,
			DecorationGroup,
			GroupDecorate,
			GroupMemberDecorate,
			Invalid76,
>>>>>>> upstream/master
			VectorExtractDynamic,
			VectorInsertDynamic,
			VectorShuffle,
			CompositeConstruct,
			CompositeExtract,
			CompositeInsert,
			CopyObject,
<<<<<<< HEAD
			CopyMemory,
			CopyMemorySized,
			Sampler,
			TextureSample,
			TextureSampleDref,
			TextureSampleLod,
			TextureSampleProj,
			TextureSampleGrad,
			TextureSampleOffset,
			TextureSampleProjLod,
			TextureSampleProjGrad,
			TextureSampleLodOffset,
			TextureSampleProjOffset,
			TextureSampleGradOffset,
			TextureSampleProjLodOffset,
			TextureSampleProjGradOffset,
			TextureFetchTexelLod,
			TextureFetchTexelOffset,
			TextureFetchSample,
			TextureFetchTexel,
			TextureGather,
			TextureGatherOffset,
			TextureGatherOffsets,
			TextureQuerySizeLod,
			TextureQuerySize,
			TextureQueryLod,
			TextureQueryLevels,
			TextureQuerySamples,
			AccessChain,
			InBoundsAccessChain,
			SNegate,
			FNegate,
			Not,
			Any,
			All,
=======
			Transpose,
			Invalid85,
			SampledImage,
			ImageSampleImplicitLod,
			ImageSampleExplicitLod,
			ImageSampleDrefImplicitLod,
			ImageSampleDrefExplicitLod,
			ImageSampleProjImplicitLod,
			ImageSampleProjExplicitLod,
			ImageSampleProjDrefImplicitLod,
			ImageSampleProjDrefExplicitLod,
			ImageFetch,
			ImageGather,
			ImageDrefGather,
			ImageRead,
			ImageWrite,
			Image,
			ImageQueryFormat,
			ImageQueryOrder,
			ImageQuerySizeLod,
			ImageQuerySize,
			ImageQueryLod,
			ImageQueryLevels,
			ImageQuerySamples,
			Invalid108,
>>>>>>> upstream/master
			ConvertFToU,
			ConvertFToS,
			ConvertSToF,
			ConvertUToF,
			UConvert,
			SConvert,
			FConvert,
<<<<<<< HEAD
			ConvertPtrToU,
			ConvertUToPtr,
			PtrCastToGeneric,
			GenericCastToPtr,
			Bitcast,
			Transpose,
			IsNan,
			IsInf,
			IsFinite,
			IsNormal,
			SignBitSet,
			LessOrGreater,
			Ordered,
			Unordered,
			ArrayLength,
=======
			QuantizeToF16,
			ConvertPtrToU,
			SatConvertSToU,
			SatConvertUToS,
			ConvertUToPtr,
			PtrCastToGeneric,
			GenericCastToPtr,
			GenericCastToPtrExplicit,
			Bitcast,
			Invalid125,
			SNegate,
			FNegate,
>>>>>>> upstream/master
			IAdd,
			FAdd,
			ISub,
			FSub,
			IMul,
			FMul,
			UDiv,
			SDiv,
			FDiv,
			UMod,
			SRem,
			SMod,
			FRem,
			FMod,
			VectorTimesScalar,
			MatrixTimesScalar,
			VectorTimesMatrix,
			MatrixTimesVector,
			MatrixTimesMatrix,
			OuterProduct,
			Dot,
<<<<<<< HEAD
			ShiftRightLogical,
			ShiftRightArithmetic,
			ShiftLeftLogical,
			LogicalOr,
			LogicalXor,
			LogicalAnd,
			BitwiseOr,
			BitwiseXor,
			BitwiseAnd,
			Select,
			IEqual,
			FOrdEqual,
			FUnordEqual,
			INotEqual,
			FOrdNotEqual,
			FUnordNotEqual,
			ULessThan,
			SLessThan,
			FOrdLessThan,
			FUnordLessThan,
			UGreaterThan,
			SGreaterThan,
			FOrdGreaterThan,
			FUnordGreaterThan,
			ULessThanEqual,
			SLessThanEqual,
			FOrdLessThanEqual,
			FUnordLessThanEqual,
			UGreaterThanEqual,
			SGreaterThanEqual,
			FOrdGreaterThanEqual,
			FUnordGreaterThanEqual,
=======
			IAddCarry,
			ISubBorrow,
			UMulExtended,
			SMulExtended,
			Invalid153,
			Any,
			All,
			IsNan,
			IsInf,
			IsFinite,
			IsNormal,
			SignBitSet,
			LessOrGreater,
			Ordered,
			Unordered,
			LogicalEqual,
			LogicalNotEqual,
			LogicalOr,
			LogicalAnd,
			LogicalNot,
			Select,
			IEqual,
			INotEqual,
			UGreaterThan,
			SGreaterThan,
			UGreaterThanEqual,
			SGreaterThanEqual,
			ULessThan,
			SLessThan,
			ULessThanEqual,
			SLessThanEqual,
			FOrdEqual,
			FUnordEqual,
			FOrdNotEqual,
			FUnordNotEqual,
			FOrdLessThan,
			FUnordLessThan,
			FOrdGreaterThan,
			FUnordGreaterThan,
			FOrdLessThanEqual,
			FUnordLessThanEqual,
			FOrdGreaterThanEqual,
			FUnordGreaterThanEqual,
			Invalid192,
			Invalid193,
			ShiftRightLogical,
			ShiftRightArithmetic,
			ShiftLeftLogical,
			BitwiseOr,
			BitwiseXor,
			BitwiseAnd,
			Not,
			BitFieldInsert,
			BitFieldSExtract,
			BitFieldUExtract,
			BitReverse,
			BitCount,
			Invalid206,
>>>>>>> upstream/master
			DPdx,
			DPdy,
			Fwidth,
			DPdxFine,
			DPdyFine,
			FwidthFine,
			DPdxCoarse,
			DPdyCoarse,
			FwidthCoarse,
<<<<<<< HEAD
=======
			Invalid216,
			Invalid217,
>>>>>>> upstream/master
			EmitVertex,
			EndPrimitive,
			EmitStreamVertex,
			EndStreamPrimitive,
<<<<<<< HEAD
			ControlBarrier,
			MemoryBarrier,
			ImagePointer,
			AtomicInit,
=======
			Invalid222,
			Invalid223,
			ControlBarrier,
			MemoryBarrier,
			Invalid226,
>>>>>>> upstream/master
			AtomicLoad,
			AtomicStore,
			AtomicExchange,
			AtomicCompareExchange,
			AtomicCompareExchangeWeak,
			AtomicIIncrement,
			AtomicIDecrement,
			AtomicIAdd,
			AtomicISub,
<<<<<<< HEAD
			AtomicUMin,
=======
			AtomicSMin,
			AtomicUMin,
			AtomicSMax,
>>>>>>> upstream/master
			AtomicUMax,
			AtomicAnd,
			AtomicOr,
			AtomicXor,
<<<<<<< HEAD
=======
			Invalid243,
			Invalid244,
			Phi,
>>>>>>> upstream/master
			LoopMerge,
			SelectionMerge,
			Label,
			Branch,
			BranchConditional,
			Switch,
			Kill,
			Return,
			ReturnValue,
			Unreachable,
			LifetimeStart,
			LifetimeStop,
<<<<<<< HEAD
			CompileFlag,
			AsyncGroupCopy,
			WaitGroupEvents,
=======
			Invalid258,
			GroupAsyncCopy,
			GroupWaitEvents,
>>>>>>> upstream/master
			GroupAll,
			GroupAny,
			GroupBroadcast,
			GroupIAdd,
			GroupFAdd,
			GroupFMin,
			GroupUMin,
			GroupSMin,
			GroupFMax,
			GroupUMax,
			GroupSMax,
<<<<<<< HEAD
			GenericCastToPtrExplicit,
			GenericPtrMemSemantics,
=======
			Invalid272,
			Invalid273,
>>>>>>> upstream/master
			ReadPipe,
			WritePipe,
			ReservedReadPipe,
			ReservedWritePipe,
			ReserveReadPipePackets,
			ReserveWritePipePackets,
			CommitReadPipe,
			CommitWritePipe,
			IsValidReserveId,
			GetNumPipePackets,
			GetMaxPipePackets,
			GroupReserveReadPipePackets,
			GroupReserveWritePipePackets,
			GroupCommitReadPipe,
			GroupCommitWritePipe,
<<<<<<< HEAD
=======
			Invalid289,
			Invalid290,
>>>>>>> upstream/master
			EnqueueMarker,
			EnqueueKernel,
			GetKernelNDrangeSubGroupCount,
			GetKernelNDrangeMaxSubGroupSize,
			GetKernelWorkGroupSize,
			GetKernelPreferredWorkGroupSizeMultiple,
			RetainEvent,
			ReleaseEvent,
			CreateUserEvent,
			IsValidEvent,
			SetUserEventStatus,
			CaptureEventProfilingInfo,
			GetDefaultQueue,
			BuildNDRange,
<<<<<<< HEAD
			SatConvertSToU,
			SatConvertUToS,
			AtomicIMin,
			AtomicIMax,
=======
			ImageSparseSampleImplicitLod,
			ImageSparseSampleExplicitLod,
			ImageSparseSampleDrefImplicitLod,
			ImageSparseSampleDrefExplicitLod,
			ImageSparseSampleProjImplicitLod,
			ImageSparseSampleProjExplicitLod,
			ImageSparseSampleProjDrefImplicitLod,
			ImageSparseSampleProjDrefExplicitLod,
			ImageSparseFetch,
			ImageSparseGather,
			ImageSparseDrefGather,
			ImageSparseTexelsResident,
			NoLine,
			AtomicFlagTestAndSet,
			AtomicFlagClear,
			ImageSparseRead,
>>>>>>> upstream/master

			Count
		};
	};

<<<<<<< HEAD
	struct SpirvBuiltin
=======
	const char* getName(SpvOpcode::Enum _opcode);

	struct SpvBuiltin
>>>>>>> upstream/master
	{
		enum Enum
		{
			Position,
			PointSize,
<<<<<<< HEAD
			ClipVertex,
=======
>>>>>>> upstream/master
			ClipDistance,
			CullDistance,
			VertexId,
			InstanceId,
<<<<<<< HEAD
			BuiltInPrimitiveId,
=======
			PrimitiveId,
>>>>>>> upstream/master
			InvocationId,
			Layer,
			ViewportIndex,
			TessLevelOuter,
			TessLevelInner,
			TessCoord,
			PatchVertices,
			FragCoord,
			PointCoord,
			FrontFacing,
			SampleId,
			SamplePosition,
			SampleMask,
<<<<<<< HEAD
			FragColor,
=======
>>>>>>> upstream/master
			FragDepth,
			HelperInvocation,
			NumWorkgroups,
			WorkgroupSize,
			WorkgroupId,
			LocalInvocationId,
			GlobalInvocationId,
			LocalInvocationIndex,
			WorkDim,
			GlobalSize,
			EnqueuedWorkgroupSize,
			GlobalOffset,
			GlobalLinearId,
<<<<<<< HEAD
			WorkgroupLinearId,
=======
>>>>>>> upstream/master
			SubgroupSize,
			SubgroupMaxSize,
			NumSubgroups,
			NumEnqueuedSubgroups,
			SubgroupId,
			SubgroupLocalInvocationId,
<<<<<<< HEAD
		};
	};

	struct SpirvExecutionModel
=======
			VertexIndex,
			InstanceIndex,

			Count
		};
	};

	const char* getName(SpvBuiltin::Enum _enum);

	struct SpvExecutionModel
>>>>>>> upstream/master
	{
		enum Enum
		{
			Vertex,
			TessellationControl,
			TessellationEvaluation,
			Geometry,
			Fragment,
			GLCompute,
			Kernel,

			Count
		};
	};

<<<<<<< HEAD
	struct SpirvMemoryModel
=======
	struct SpvAddressingModel
	{
		enum Enum
		{
			Logical,
			Physical32,
			Physical64,

			Count
		};
	};

	struct SpvMemoryModel
>>>>>>> upstream/master
	{
		enum Enum
		{
			Simple,
			GLSL450,
<<<<<<< HEAD
			OpenCL12,
			OpenCL20,
			OpenCL21,
=======
			OpenCL,
>>>>>>> upstream/master

			Count
		};
	};

<<<<<<< HEAD
	struct SpirvStorageClass
=======
	struct SpvStorageClass
>>>>>>> upstream/master
	{
		enum Enum
		{
			UniformConstant,
			Input,
			Uniform,
			Output,
<<<<<<< HEAD
			WorkgroupLocal,
			WorkgroupGlobal,
			PrivateGlobal,
			Function,
			Generic,
			Private,
			AtomicCounter,
		};
	};

	struct SpirvResourceDim
=======
			Workgroup,
			CrossWorkgroup,
			Private,
			Function,
			Generic,
			PushConstant,
			AtomicCounter,
			Image,

			Count
		};
	};

	const char* getName(SpvStorageClass::Enum _enum);

	struct SpvResourceDim
>>>>>>> upstream/master
	{
		enum Enum
		{
			Texture1D,
			Texture2D,
			Texture3D,
			TextureCube,
			TextureRect,
			Buffer,
<<<<<<< HEAD
		};
	};

	struct SpirvDecoration
	{
		enum Enum
		{
			PrecisionLow,
			PrecisionMedium,
			PrecisionHigh,
=======
			SubpassData,
		};
	};

	struct SpvDecoration
	{
		enum Enum
		{
			RelaxedPrecision,
			SpecId,
>>>>>>> upstream/master
			Block,
			BufferBlock,
			RowMajor,
			ColMajor,
<<<<<<< HEAD
			GLSLShared,
			GLSLStd140,
			GLSLStd430,
			GLSLPacked,
			Smooth,
			Noperspective,
=======
			ArrayStride,
			MatrixStride,
			GLSLShared,
			GLSLPacked,
			CPacked,
			BuiltIn,
			Unknown12,
			NoPerspective,
>>>>>>> upstream/master
			Flat,
			Patch,
			Centroid,
			Sample,
			Invariant,
			Restrict,
			Aliased,
			Volatile,
			Constant,
			Coherent,
<<<<<<< HEAD
			Nonwritable,
			Nonreadable,
			Uniform,
			NoStaticUse,
			CPacked,
=======
			NonWritable,
			NonReadable,
			Uniform,
			Unknown27,
>>>>>>> upstream/master
			SaturatedConversion,
			Stream,
			Location,
			Component,
			Index,
			Binding,
			DescriptorSet,
			Offset,
<<<<<<< HEAD
			Alignment,
			XfbBuffer,
			Stride,
			BuiltIn,
=======
			XfbBuffer,
			XfbStride,
>>>>>>> upstream/master
			FuncParamAttr,
			FPRoundingMode,
			FPFastMathMode,
			LinkageAttributes,
<<<<<<< HEAD
			SpecId,
=======
			NoContraction,
			InputAttachmentIndex,
			Alignment,
>>>>>>> upstream/master

			Count
		};
	};

<<<<<<< HEAD
	struct SpirvOperand
	{
	};

	struct SpirvInstruction
	{
		SpirvOpcode::Enum opcode;
		uint16_t length;

		uint8_t numOperands;
		SpirvOperand operand[6];

		union
		{
			struct ResultTypeId
			{
				uint32_t resultType;
				uint32_t id;
			};

			ResultTypeId constant;
			ResultTypeId constantComposite;

			uint32_t value[8];
		} un;
	};

	int32_t read(bx::ReaderI* _reader, SpirvInstruction& _instruction);
	int32_t write(bx::WriterI* _writer, const SpirvInstruction& _instruction);
	int32_t toString(char* _out, int32_t _size, const SpirvInstruction& _instruction);

	struct SpirvShader
	{
		stl::vector<uint8_t> byteCode;
	};

	int32_t read(bx::ReaderSeekerI* _reader, SpirvShader& _shader);
	int32_t write(bx::WriterI* _writer, const SpirvShader& _shader);

	typedef void (*SpirvParseFn)(uint32_t _offset, const SpirvInstruction& _instruction, void* _userData);
	void parse(const SpirvShader& _src, SpirvParseFn _fn, void* _userData);

	typedef void (*SpirvFilterFn)(SpirvInstruction& _instruction, void* _userData);
	void filter(SpirvShader& _dst, const SpirvShader& _src, SpirvFilterFn _fn, void* _userData);

	struct Spirv
	{
=======
	const char* getName(SpvDecoration::Enum _enum);

	struct SpvOperand
	{
		SpvOperand() { /* not pod */ }

		enum Enum
		{
			AccessQualifier,
			AddressingModel,
			Base,
			Capability,
			Component,
			ComponentType,
			Composite,
			Condition,
			Coordinate,
			Decoration,
			Dim,
			Dref,
			ElementType,
			ExecutionModel,
			Function,
			FunctionControl,
			Id,
			IdRep,
			ImageFormat,
			ImageOperands,
			LinkageType,
			LiteralNumber,
			LiteralRep,
			LiteralString,
			Matrix,
			MemoryAccess,
			MemoryModel,
			Object,
			Pointer,
			SampledType,
			SampledImage,
			SamplerAddressingMode,
			SamplerFilterMode,
			Scalar,
			SourceLanguage,
			StorageClass,
			StructureType,
			Vector,

			Count
		};

		Enum type;
		uint32_t data;

		stl::string literalString;
	};

	struct SpvInstruction
	{
		SpvInstruction() { /* not pod */ }

		SpvOpcode::Enum opcode;
		uint16_t length;
		uint16_t numOperands;

		uint32_t type;
		uint32_t result;
		bool hasType;
		bool hasResult;

		SpvOperand operand[10];
	};

	int32_t read(bx::ReaderI* _reader, SpvInstruction& _instruction, bx::Error* _err);
	int32_t write(bx::WriterI* _writer, const SpvInstruction& _instruction, bx::Error* _err);
	int32_t toString(char* _out, int32_t _size, const SpvInstruction& _instruction);

	struct SpvShader
	{
		SpvShader() { /* not pod */ }

		stl::vector<uint8_t> byteCode;
	};

	int32_t read(bx::ReaderSeekerI* _reader, SpvShader& _shader, bx::Error* _err);
	int32_t write(bx::WriterI* _writer, const SpvShader& _shader, bx::Error* _err);

	typedef bool (*SpvParseFn)(uint32_t _offset, const SpvInstruction& _instruction, void* _userData);
	void parse(const SpvShader& _src, SpvParseFn _fn, void* _userData, bx::Error* _err = NULL);

	typedef void (*SpvFilterFn)(SpvInstruction& _instruction, void* _userData);
	void filter(SpvShader& _dst, const SpvShader& _src, SpvFilterFn _fn, void* _userData, bx::Error* _err = NULL);

	struct SpirV
	{
		SpirV() { /* not pod */ }

>>>>>>> upstream/master
		struct Header
		{
			uint32_t magic;
			uint32_t version;
			uint32_t generator;
			uint32_t bound;
			uint32_t schema;
		};

		Header header;
<<<<<<< HEAD
		SpirvShader shader;
	};

	int32_t read(bx::ReaderSeekerI* _reader, Spirv& _spirv);
	int32_t write(bx::WriterSeekerI* _writer, const Spirv& _spirv);
=======
		SpvShader shader;
	};

	int32_t read(bx::ReaderSeekerI* _reader, SpirV& _spirv, bx::Error* _err);
	int32_t write(bx::WriterSeekerI* _writer, const SpirV& _spirv, bx::Error* _err);
>>>>>>> upstream/master

} // namespace bgfx

#endif // BGFX_SHADER_SPIRV_H
