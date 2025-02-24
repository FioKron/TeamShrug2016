// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "ObjectBase.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef TEAMSHRUG_TeamShrugCharacter_generated_h
#error "TeamShrugCharacter.generated.h already included, missing '#pragma once' in TeamShrugCharacter.h"
#endif
#define TEAMSHRUG_TeamShrugCharacter_generated_h

#define TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_RPC_WRAPPERS
#define TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS
#define TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesATeamShrugCharacter(); \
	friend TEAMSHRUG_API class UClass* Z_Construct_UClass_ATeamShrugCharacter(); \
	public: \
	DECLARE_CLASS(ATeamShrugCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/TeamShrug"), NO_API) \
	DECLARE_SERIALIZER(ATeamShrugCharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_INCLASS \
	private: \
	static void StaticRegisterNativesATeamShrugCharacter(); \
	friend TEAMSHRUG_API class UClass* Z_Construct_UClass_ATeamShrugCharacter(); \
	public: \
	DECLARE_CLASS(ATeamShrugCharacter, ACharacter, COMPILED_IN_FLAGS(0), 0, TEXT("/Script/TeamShrug"), NO_API) \
	DECLARE_SERIALIZER(ATeamShrugCharacter) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API ATeamShrugCharacter(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ATeamShrugCharacter) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATeamShrugCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATeamShrugCharacter); \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API ATeamShrugCharacter(const ATeamShrugCharacter& InCopy); \
public:


#define TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
	/** Private copy-constructor, should never be used */ \
	NO_API ATeamShrugCharacter(const ATeamShrugCharacter& InCopy); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, ATeamShrugCharacter); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ATeamShrugCharacter); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(ATeamShrugCharacter)


#define TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_9_PROLOG
#define TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_RPC_WRAPPERS \
	TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_INCLASS \
	TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_INCLASS_NO_PURE_DECLS \
	TeamShrug_Source_TeamShrug_TeamShrugCharacter_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID TeamShrug_Source_TeamShrug_TeamShrugCharacter_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
