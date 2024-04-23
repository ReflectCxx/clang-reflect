# Header files
set(INC_HEADERS
    ASTParser.h
    ClangDriver.h
	ClangReflectActionFactory.h
	ClangReflectDiagnosticConsumer.h
	CommandLineParser.h
	FileManager.h
	FindRecordDeclsVisitor.h
	IncludesManager.h
	Logger.h
	Constants.h
	ReflectableInterface.h
    # Add more header files as needed
)

# Add headers to the library target
add_library(inc_lib INTERFACE)
target_include_directories(inc_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
