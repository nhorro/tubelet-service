add_executable( tubelet-service main.cpp)

target_include_directories( tubelet-service
	PRIVATE
		${Boost_INCLUDE_DIRS}		
)