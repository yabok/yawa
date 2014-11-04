add_executable(yawa yawa.c)
target_link_libraries (yawa X11)
target_link_libraries (yawa Imlib2)

install(TARGETS yawa DESTINATION bin)
