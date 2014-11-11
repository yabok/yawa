find_package(Sphinx REQUIRED)

add_custom_target(man ALL
	${SPHINX_EXECUTABLE}
	-q -b man
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	COMMENT "Building man page with Sphinx"
)

INSTALL(FILES "yawa.1" DESTINATION "share/man/man1")
