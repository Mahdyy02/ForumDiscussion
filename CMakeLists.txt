cmake_minimum_required(VERSION 3.10)

project(ForumDeDiscussion C)

add_executable(Forum main.c date.c forum.c message.c rubrique.c utilisateur.c linked_lists.c)

target_compile_options(Forum PRIVATE -Wall -Wextra)

target_include_directories(Forum PRIVATE include)

target_link_libraries(Forum PRIVATE m)