cmake_minimum_required(VERSION 3.20)

project(clang-reflect)

set(CMAKE_CXX_STANDARD 20)

if(WIN32)
	if(NOT LLVM_BUILD)
		message(FATAL_ERROR "LLVM_BUILD not provided. Please specify LLVM build directory.")
	endif()
endif(WIN32)

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Output dir: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

if(WIN32)
	# Linker library directories for the target
	link_directories(
		${LLVM_BUILD}/$(CONFIGURATION)/lib
		${LLVM_BUILD}/$(CONFIGURATION)/lib/$(CONFIGURATION))
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
		"${CMAKE_SOURCE_DIR}/dependencies/windows/llvm-17.0.5.src/include"
		"${CMAKE_SOURCE_DIR}/dependencies/windows/llvm-17.0.5.src/build/include"
		"${CMAKE_SOURCE_DIR}/dependencies/windows/clang-17.0.5.src/include"
		"${CMAKE_SOURCE_DIR}/dependencies/windows/clang-17.0.5.src/clang-tools-extra"
		"${CMAKE_SOURCE_DIR}/dependencies/windows/clang-17.0.5.src/build/include"
		"${CMAKE_SOURCE_DIR}/clang-reflect/inc"
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
		add_definitions(${LLVM_DEFINITIONS})
		llvm_map_components_to_libnames(LLVM_LIBS core analysis codegen libdriver support)		
		set(CLANG_LIBS
			${LLVM_LIBRARY_DIRS}/libclangFrontend.a
			${LLVM_LIBRARY_DIRS}/libclangDriver.a
			${LLVM_LIBRARY_DIRS}/libclangRewrite.a
			${LLVM_LIBRARY_DIRS}/libclangParse.a
			${LLVM_LIBRARY_DIRS}/libclangSema.a
			${LLVM_LIBRARY_DIRS}/libclangEdit.a
			${LLVM_LIBRARY_DIRS}/libclangAnalysis.a
			${LLVM_LIBRARY_DIRS}/libclangTooling.a
			${LLVM_LIBRARY_DIRS}/libclangAST.a
			${LLVM_LIBRARY_DIRS}/libclangLex.a
			${LLVM_LIBRARY_DIRS}/libclangBasic.a
			${LLVM_LIBRARY_DIRS}/libclangSerialization.a
			${LLVM_LIBRARY_DIRS}/libclangStaticAnalyzerFrontend.a
			${LLVM_LIBRARY_DIRS}/libclangStaticAnalyzerCore.a
			${LLVM_LIBRARY_DIRS}/libclangStaticAnalyzerCheckers.a
			${LLVM_LIBRARY_DIRS}/libclangASTMatchers.a
			${LLVM_LIBRARY_DIRS}/libclangRewrite.a
			${LLVM_LIBRARY_DIRS}/libclangTidy.a
			${LLVM_LIBRARY_DIRS}/libclangTidyUtils.a
			${LLVM_LIBRARY_DIRS}/libclangToolingCore.a
			${LLVM_LIBRARY_DIRS}/libclangFormat.a
			${LLVM_LIBRARY_DIRS}/libLLVMFrontendOpenMP.a
			${LLVM_LIBRARY_DIRS}/libclangCrossTU.a
			${LLVM_LIBRARY_DIRS}/libclangToolingInclusions.a
			${LLVM_LIBRARY_DIRS}/libclangDaemon.a
			${LLVM_LIBRARY_DIRS}/libclangIndex.a
			${LLVM_LIBRARY_DIRS}/libclangSupport.a
			${LLVM_LIBRARY_DIRS}/libclangTransformer.a
			${LLVM_LIBRARY_DIRS}/libclangAnalysisFlowSensitive.a
			${LLVM_LIBRARY_DIRS}/libclangAnalysisFlowSensitiveModels.a
			${LLVM_LIBRARY_DIRS}/libLLVMObject.a
			${LLVM_LIBRARY_DIRS}/libLLVMTextAPI.a
			${LLVM_LIBRARY_DIRS}/libLLVMDebugInfoDWARF.a
			${LLVM_LIBRARY_DIRS}/libLLVMWindowsDriver.a
			${LLVM_LIBRARY_DIRS}/libLLVMTargetParser.a
			${LLVM_LIBRARY_DIRS}/libLLVMIRReader.a
			${LLVM_LIBRARY_DIRS}/libLLVMAsmParser.a
			${LLVM_LIBRARY_DIRS}/libclangToolingInclusionsStdlib.a
			${LLVM_LIBRARY_DIRS}/libclangIncludeCleaner.a
			${LLVM_LIBRARY_DIRS}/libLLVMTransformUtils.a
			${LLVM_LIBRARY_DIRS}/libLLVMScalarOpts.a
			${LLVM_LIBRARY_DIRS}/libLLVMAnalysis.a
			# List all other libraries as before...
		)
		
		include_directories("${CMAKE_SOURCE_DIR}/clang-reflect/inc")
		include_directories("${CMAKE_SOURCE_DIR}/dependencies/linux/include")
		target_link_libraries(${CXX_EXE_NAME} ${LLVM_LIBS})
		target_link_libraries(${CXX_EXE_NAME} ${CLANG_LIBS})

		message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
		message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
		message(STATUS "Clang Libraries: ${CLANG_LIBS}")
		message(STATUS "LLVM Linker dirs: ${LLVM_LIBRARY_DIRS}")
		message(STATUS "LLVM Libraries: ${LLVM_LIBS}")
	endif (LLVM_FOUND)
endif (UNIX)

# Add subdirectories
include(inc/CMakeLists.txt)
include(src/CMakeLists.txt)