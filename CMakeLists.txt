project(rpgsfml)
cmake_minimum_required(VERSION 3.0)

file(GLOB CPPS "*.cpp")
file(GLOB HPPS "*.hpp")

add_executable(${PROJECT_NAME} ${CPPS} ${HPPS}) 

target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libsfml-audio.so)
target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libsfml-graphics.so)
target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libsfml-network.so)
target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libsfml-system.so)
target_link_libraries(${PROJECT_NAME} /usr/lib/x86_64-linux-gnu/libsfml-window.so)

# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-audio.so)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-audio.so.2.5)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-audio.so.2.5.0)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-graphics.so)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-graphics.so.2.5)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-graphics.so.2.5.0)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-network.so)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-network.so.2.5)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-network.so.2.5.0)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-system.so)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-system.so.2.5)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-system.so.2.5.0)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-window.so)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-window.so.2.5)
# target_link_libraries(${PROJECT_NAME} /home/leonid/rpgSFML/build/SFML/lib/libsfml-window.so.2.5.0)