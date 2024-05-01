cmake_minimum_required(VERSION 3.1.0)

project(clang-reflect)

set(CMAKE_CXX_STANDARD 20)

# Set LLVM_SRC and LLVM_BUILD variables from command line
if(NOT LLVM_SRC)
    message(FATAL_ERROR "LLVM_SRC not provided. Please specify LLVM source directory.")
endif()

if(WIN32)
	if(NOT LLVM_BUILD)
		message(FATAL_ERROR "LLVM_BUILD not provided. Please specify LLVM build directory.")
	endif()
endif(WIN32)

set(LLVM_DIR_STR "LLVM")
set(CLANG_DIR_STR "CLANG")

string(REGEX MATCH "llvm-.*.src$" LLVM_DIR_STR ${LLVM_SRC})
string(REPLACE "llvm" "clang" CLANG_DIR_STR ${LLVM_DIR_STR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

message(STATUS "Project name: ${PROJECT_NAME}")
message(STATUS ${LLVM_DIR_STR})
message(STATUS ${CLANG_DIR_STR})
message(STATUS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

if(WIN32)
	# Linker library directories for the target
	link_directories(
		${LLVM_BUILD}/$(CONFIGURATION)/lib
		${LLVM_BUILD}/$(CONFIGURATION)/lib/$(CONFIGURATION)
	)
endif (WIN32)

# Add executable target
SET(CXX_EXE_NAME clang-reflect)
ADD_EXECUTABLE(${CXX_EXE_NAME} "")

if(WIN32)
	# Linker library directories for the target
	link_directories(
		${LLVM_BUILD}/$(CONFIGURATION)/lib
		${LLVM_BUILD}/$(CONFIGURATION)/lib/$(CONFIGURATION)
	)

	include_directories(
		${LLVM_SRC}/include
		${LLVM_BUILD}/include
		${LLVM_SRC}/tools/${CLANG_DIR_STR}/include
		${LLVM_SRC}/tools/${CLANG_DIR_STR}/tools/extra
		${LLVM_BUILD}/tools/${CLANG_DIR_STR}/include
		${CMAKE_SOURCE_DIR}/inc
	)

	# Link libraries
	target_link_libraries(${CXX_EXE_NAME}
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
	message(STATUS "LLVM Include dirs: ${LLVM_INCLUDE_DIRS}")
endif (WIN32)


if(UNIX)
	find_package(LLVM REQUIRED CONFIG)
	if (LLVM_FOUND)
		set(CLANG_LIBS
			libclangFrontend.a
			libclangDriver.a
			libclangRewrite.a
			libclangParse.a
			libclangSema.a
			libclangEdit.a
			libclangAnalysis.a
			libclangTooling.a
			libclangAST.a
			libclangLex.a
			libclangBasic.a
			libclangSerialization.a
			libclangStaticAnalyzerFrontend.a
			libclangStaticAnalyzerCore.a
			libclangStaticAnalyzerCheckers.a
			libclangASTMatchers.a
			libclangRewrite.a
			libclangTidy.a
			libclangTidyUtils.a
			libclangToolingCore.a
			libclangFormat.a
			libclangTidyBoostModule.a
			libclangTidyBugproneModule.a
			libclangTidyCERTModule.a
			libclangTidyCppCoreGuidelinesModule.a
			libclangTidyFuchsiaModule.a
			libclangTidyGoogleModule.a
			libclangTidyHICPPModule.a
			libclangTidyLLVMModule.a
			libclangTidyMiscModule.a
			libclangTidyModernizeModule.a
			libclangTidyMPIModule.a
			libclangTidyObjCModule.a
			libclangTidyPerformanceModule.a
			libclangTidyReadabilityModule.a
			libLLVMFrontendOpenMP.a
			libclangTidyConcurrencyModule.a
			libclangCrossTU.a
			libclangToolingInclusions.a
			libclangDaemon.a
			libclangIndex.a
			libclangSupport.a
			libclangTransformer.a
			libclangAnalysisFlowSensitive.a
			libclangAnalysisFlowSensitiveModels.a
			libLLVMObject.a
			libLLVMTextAPI.a
			libLLVMDebugInfoDWARF.a
			libLLVMWindowsDriver.a
			libLLVMTargetParser.a
			libLLVMIRReader.a
			libLLVMAsmParser.a
			libclangToolingInclusionsStdlib.a
			libclangIncludeCleaner.a
			libLLVMTransformUtils.a
			libLLVMScalarOpts.a
			libLLVMAnalysis.a
			# List all other libraries as before...
		)
		
		llvm_map_components_to_libnames(LLVM_LIBS core analysis codegen libdriver support)

		add_definitions(${LLVM_DEFINITIONS})
		include_directories(${LLVM_INCLUDE_DIRS})
		target_link_libraries(${CXX_EXE_NAME} ${LLVM_LIBS})
		target_link_libraries(${CXX_EXE_NAME} ${CLANG_LIBS})

		message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
		message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
		message(STATUS "Clang Libraries: ${CLANG_LIBS}")
		message(STATUS "LLVM Include dirs: ${LLVM_INCLUDE_DIRS}")
		message(STATUS "LLVM Linker dirs: ${LLVM_LIBRARY_DIRS}")
		message(STATUS "LLVM Libraries: ${LLVM_LIBS}")	
	endif (LLVM_FOUND)
endif (UNIX)

# Add subdirectories
include(inc/CMakeLists.txt)
include(src/CMakeLists.txt)