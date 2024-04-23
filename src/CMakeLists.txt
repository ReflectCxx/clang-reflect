# Source files
set(SOURCES
    ASTParser.cpp
    ClangDriver.cpp
	ClangReflectActionFactory.cpp
	ClangReflectDiagnosticConsumer.cpp
	clang-reflect-main.cpp
	CommandLineParser.cpp
	FileManager.cpp
	FindRecordDeclsVisitor.cpp
	cxxIncludeScanner.lex.c
	IncludesManager.cpp
	Logger.cpp
	ReflectableInterface.cpp
    # Add more source files as needed
)


SET_SOURCE_FILES_PROPERTIES("cxxIncludeScanner.lex.c" PROPERTIES LANGUAGE CXX COMPILE_FLAGS "-std=c++14")


# Linker library directories for the target
link_directories(
    ${LLVM_BUILD}/$(CONFIGURATION)/lib
    ${LLVM_BUILD}/$(CONFIGURATION)/lib/$(CONFIGURATION)
)

# Add executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link inc_lib library
target_link_libraries(clang-reflect PRIVATE inc_lib)

SET(LLVM_DIR_NAME "LLVM")
SET(CLANG_DIR_NAME "CLANG")

STRING(REGEX MATCH "llvm-.*.src$" LLVM_DIR_NAME ${LLVM_SRC})
STRING(REPLACE "llvm" "clang" CLANG_DIR_NAME ${LLVM_DIR_NAME})
MESSAGE(STATUS ${LLVM_DIR_NAME})
MESSAGE(STATUS ${CLANG_DIR_NAME})

# Include directories
include_directories(
    ${LLVM_SRC}/include
    ${LLVM_SRC}/tools/${CLANG_DIR_NAME}/include
    ${LLVM_SRC}/tools/${CLANG_DIR_NAME}/tools/extra
    ${LLVM_BUILD}/include
    ${LLVM_BUILD}/tools/${CLANG_DIR_NAME}/include
)

# Link libraries
target_link_libraries(clang-reflect
    PRIVATE
	Version.lib
	LLVMCore.lib
	LLVMProfileData.lib
	LLVMSupport.lib
	LLVMBinaryFormat.lib
	LLVMBitReader.lib
	LLVMBitstreamReader.lib
	LLVMBitWriter.lib
	LLVMDemangle.lib
	LLVMRemarks.lib
	LLVMFrontendOpenMP.lib
	clangToolingInclusions.lib
	clangDaemon.lib
	clangIndex.lib
	clangast.lib
	clangfrontend.lib
	clangbasic.lib
	clangTooling.lib
	clangLex.lib
	clangParse.lib
	clangSerialization.lib
	clangSema.lib
	clangDriver.lib
	LLVMOption.lib
	clangEdit.lib
	clangCrossTU.lib
	LLVMMC.lib
	LLVMMCParser.lib
	clangAnalysis.lib
	clangStaticAnalyzerCore.lib
	clangStaticAnalyzerFrontend.lib
	clangRewriteFrontend.lib
	clangStaticAnalyzerCheckers.lib
	clangASTMatchers.lib
	clangRewrite.lib
	clangTidy.lib
	clangTidyUtils.lib
	clangToolingCore.lib
	clangFormat.lib
	clangTidyBoostModule.lib
	clangTidyBugproneModule.lib
	clangTidyCERTModule.lib
	clangTidyCppCoreGuidelinesModule.lib
	clangTidyFuchsiaModule.lib
	clangTidyGoogleModule.lib
	clangTidyHICPPModule.lib
	clangTidyLLVMModule.lib
	clangTidyMiscModule.lib
	clangTidyModernizeModule.lib
	clangTidyMPIModule.lib
	clangTidyObjCModule.lib
	clangTidyPerformanceModule.lib
	clangTidyReadabilityModule.lib
	clangTidyConcurrencyModule.lib
	Shlwapi.lib
	clangSupport.lib
	clangTransformer.lib
	clangAnalysisFlowSensitive.lib
	clangAnalysisFlowSensitiveModels.lib
	LLVMObject.lib
	LLVMTextAPI.lib
	LLVMDebugInfoDWARF.lib
	LLVMWindowsDriver.lib
	LLVMTargetParser.lib
	LLVMIRReader.lib
	LLVMAsmParser.lib
	clangToolingInclusionsStdlib.lib
	clangIncludeCleaner.lib
	LLVMTransformUtils.lib
	LLVMScalarOpts.lib
	LLVMAnalysis.lib
    # List all other libraries as before...
)
