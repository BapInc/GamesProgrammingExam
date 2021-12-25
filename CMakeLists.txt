# Add as a subdirectory SimpleRenderEngineProject using add_subdirectory
IF (NOT DEFINED all_libs)
    message( FATAL_ERROR "This CMakeLists.txt must be included using the command add_subdirectory(name)" )
ENDIF (NOT DEFINED all_libs)
# Ensure SimpleRenderEngineProject is up-to-date
IF (WIN32)
    IF (NOT DEFINED DLLFileList)
        message( FATAL_ERROR "The SimpleRenderEngineProject has been updated. Clone the project (https://github.com/mortennobel/SimpleRenderEngineProject) again the project again and start over." )
    ENDIF(NOT DEFINED DLLFileList)
    file(GLOB_RECURSE FMOD_DLLS 
        "ThirdParty/*/lib/x86/*.dll"
    )
ENDIF(WIN32)

# Load FMOD lib files
file(GLOB_RECURSE FMOD_LIBS 
"ThirdParty/*/lib/x86/*.lib"
)

#FMOD banks
file(GLOB_RECURSE FMOD_BANKS 
"FMOD/DungeonGame/Build/Desktop/*.bank"
)

# Add hpp and cpp files to Dungeon variable
file(GLOB Dungeon
        "*.hpp"
        "*.h"
        "*.cpp"
        )

# Add AI files to variables  
file(GLOB AI_HEADERS
    "AI/*.hpp"
    "AI/*.h"
)

file(GLOB AI_SOURCE
    "AI/*.cpp"
)

file(GLOB COMPONENTS_HEADERS
    "Components/*.hpp"
    "Components/*.h"
)

file(GLOB COMPONENTS_SOURCE
    "Components/*.cpp"
)

file(GLOB DUNGEON_HEADERS
    "Dungeon/*.hpp"
    "Dungeon/*.h"
)

file(GLOB DUNGEON_SOURCE
    "Dungeon/*.cpp"
)

file(GLOB GAME_HEADERS
    "Game/*.hpp"
    "Game/*.h"
)

file(GLOB GAME_SOURCE
    "Game/*.cpp"
)

file(GLOB GAMESTATES_HEADERS
    "GameStates/*.hpp"
    "GameStates/*.h"
)

file(GLOB GAMESTATES_SOURCE
    "GameStates/*.cpp"
)

file(GLOB MANAGERS_HEADERS
    "Managers/*.hpp"
    "Managers/*.h"
)

file(GLOB MANAGERS_SOURCE
    "Managers/*.cpp"
)

file(GLOB MISC_HEADERS
    "Misc/*.hpp"
    "Misc/*.h"
)

file(GLOB MISC_SOURCE
    "Misc/*.cpp"
)

file(GLOB PLAYER_HEADERS
    "Player/*.hpp"
    "Player/*.h"
)

file(GLOB PLAYER_SOURCE
    "Player/*.cpp"
)

file(GLOB SPRITES_HEADERS
    "Sprites/*.hpp"
    "Sprites/*.h"
)

file(GLOB SPRITES_SOURCE
    "Sprites/*.cpp"
)

file(GLOB UTILTY_HEADERS
    "Utility/*.hpp"
    "Utility/*.h"
)

file(GLOB UTILITY_SOURCE
    "Utility/*.cpp"
)



# Compe cpp files (from Snake variable)
add_executable(GamesProgrammingExam 
${Dungeon} 
${AI_HEADERS} ${AI_SOURCE}
${COMPONENTS_HEADERS} ${COMPONENTS_SOURCE} 
${DUNGEON_HEADERS} ${DUNGEON_SOURCE} 
${GAME_HEADERS} ${GAME_SOURCE} 
${GAMESTATES_HEADERS} ${GAMESTATES_SOURCE} 
${MISC_HEADERS} ${MISC_SOURCE} 
${MANAGERS_HEADERS} ${MANAGERS_SOURCE} 
${PLAYER_HEADERS} ${PLAYER_SOURCE} 
${SPRITES_HEADERS} ${SPRITES_SOURCE} 
${UTILTY_HEADERS} ${UTILITY_SOURCE} 
)

SET(FMOD_BANK "ThirdParty/fsbank/inc/")
SET(FMOD_STUDIO "ThirdParty/studio/inc/")
SET(FMOD_CORE "ThirdParty/core/inc/")
target_link_libraries(GamesProgrammingExam ${all_libs} ${FMOD_LIBS})
include_directories(${FMOD_BANK} ${FMOD_STUDIO} ${FMOD_CORE})

# copy files to dest
file(COPY spritesheet.png spritesheet.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY spritesheet.png spritesheet.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY spritesheet.png spritesheet.json DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${FMOD_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
file(COPY ${FMOD_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release)
file(COPY ${FMOD_DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${FMOD_BANKS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug/FMOD_Banks)
file(COPY ${FMOD_BANKS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Release/FMOD_Banks)
file(COPY ${FMOD_BANKS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/FMOD_Banks)
# Create sub-folders in visual studio
source_group("Header Files\\AI" FILES ${AI_HEADERS})
source_group("Source Files\\AI" FILES ${AI_SOURCE})
source_group("Header Files\\Components" FILES ${COMPONENTS_HEADERS})
source_group("Source Files\\Components" FILES ${COMPONENTS_SOURCE})
source_group("Header Files\\Dungeon" FILES ${DUNGEON_HEADERS})
source_group("Source Files\\Dungeon" FILES ${DUNGEON_SOURCE})
source_group("Header Files\\Game" FILES ${GAME_HEADERS})
source_group("Source Files\\Game" FILES ${GAME_SOURCE})
source_group("Header Files\\GameStates" FILES ${GAMESTATES_HEADERS})
source_group("Source Files\\GameStates" FILES ${GAMESTATES_SOURCE})
source_group("Header Files\\Managers" FILES ${MANAGERS_HEADERS})
source_group("Source Files\\Managers" FILES ${MANAGERS_SOURCE})
source_group("Header Files\\Misc" FILES ${MISC_HEADERS})
source_group("Source Files\\Misc" FILES ${MISC_SOURCE})
source_group("Header Files\\Player" FILES ${PLAYER_HEADERS})
source_group("Source Files\\Player" FILES ${PLAYER_SOURCE})
source_group("Header Files\\Sprites" FILES ${SPRITES_HEADERS})
source_group("Source Files\\Sprites" FILES ${SPRITES_SOURCE})
source_group("Header Files\\Utility" FILES ${UTILTY_HEADERS})
source_group("Source Files\\Utility" FILES ${UTILITY_SOURCE})

IF (WIN32)
    # Copy dll files to ${CMAKE_CURRENT_BINARY_DIR}/Debug
    file(COPY ${DLLFileList} DESTINATION Debug)
    file(COPY ${DLLFileList} DESTINATION Release)
    file(COPY ${DLLFileList} DESTINATION .)

    # Set working directory to ${CMAKE_CURRENT_BINARY_DIR}/Debug
    set_target_properties(GamesProgrammingExam PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug)

ENDIF(WIN32)
