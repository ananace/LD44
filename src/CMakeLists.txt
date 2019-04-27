# 
# External dependencies
# 

if (WIN32)
    find_package(SFML 2 REQUIRED COMPONENTS audio graphics main system window)
    add_definitions(-D_USE_MATH_DEFINES)
else ()
    find_package(SFML 2 REQUIRED COMPONENTS audio graphics system window)
endif ()


# 
# Sources
# 

set(headers
    Application.hpp
    Collider.hpp
    CollisionManager.hpp
    IState.hpp
    ParticleManager.hpp
    Particles.hpp
    Projectile.hpp
    ProjectileManager.hpp
    Util.hpp

    Game/Attachement.hpp
    Game/CogShape.hpp
    Game/Hardpoint.hpp
    Game/Mount.hpp
    Game/Player.hpp
    Game/Ship.hpp
    Game/Weapon.hpp

    Game/Weapons/Gun.hpp

    States/DummyState.hpp
    States/GameState.hpp
)

set(sources
    Application.cpp
    Collider.cpp
    CollisionManager.cpp
    ParticleManager.cpp
    Projectile.cpp
    ProjectileManager.cpp
    Util.cpp

    Game/Attachement.cpp
    Game/CogShape.cpp
    Game/Hardpoint.cpp
    Game/Mount.cpp
    Game/Player.cpp
    Game/Ship.cpp
    Game/Weapon.cpp

    Game/Weapons/Gun.cpp

    States/DummyState.cpp
    States/GameState.cpp

    main.cpp
)

# Group source files
set(header_group "Header Files")
set(source_group "Source Files")
source_group(${header_group} FILES ${headers})
source_group(${source_group} FILES ${sources})

# 
# Create executable
# 

# Build executable
add_executable(LD44
    MACOSX_BUNDLE
    ${sources}
    ${headers}
)


# 
# Project options
# 

set_target_properties(LD44
    PROPERTIES
    ${DEFAULT_PROJECT_OPTIONS}
    FOLDER ""
)


# 
# Include directories
# 

target_include_directories(LD44
    PRIVATE
    ${DEFAULT_INCLUDE_DIRECTORIES}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${FontConfig_INCLUDE_DIRS}
    ${SFML_INCLUDE_DIR}
)


# 
# Libraries
# 

target_link_libraries(LD44
    PRIVATE
    ${DEFAULT_LIBRARIES}
    ${SFML_LIBRARIES}
    ${SFML_DEPENDENCIES}
)


# 
# Compile definitions
# 

target_compile_definitions(LD44
    PRIVATE
    ${DEFAULT_COMPILE_DEFINITIONS}
)


# 
# Compile options
# 

target_compile_options(LD44
    PRIVATE
    ${DEFAULT_COMPILE_OPTIONS}
)


# 
# Linker options
# 

target_link_libraries(LD44
    PRIVATE
    ${DEFAULT_LINKER_OPTIONS}
)


# 
# Install information
# 

install(
    TARGETS
    LD44
    RUNTIME DESTINATION bin
)
