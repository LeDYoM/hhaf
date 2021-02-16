function(generate_pack name)
    set(CPACK_GENERATOR "ZIP")
    set(CPACK_SOURCE_GENERATOR "ZIP")
#    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
#    set(CPACK_RESOURCE_FILE_README "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
#    set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/package")

    # not .gitignore as its regex syntax is distinct from CMake
    #file(READ ${CMAKE_CURRENT_LIST_DIR}/.cpack_ignore _cpack_ignore)
    #string(REGEX REPLACE "\n" ";" _cpack_ignore ${_cpack_ignore})
    #set(CPACK_SOURCE_IGNORE_FILES "${_cpack_ignore}")

#    install(FILES ${CPACK_RESOURCE_FILE_README} ${CPACK_RESOURCE_FILE_LICENSE}
#      DESTINATION share/docs/${PROJECT_NAME})

include(CPack)
    set(CPACK_GENERATOR "DEB")
    set(CPACK_DEBIAN_PACKAGE_NAME "${name}")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ismael Gonzalez")
    set(CPACK_DEBIAN_FILE_NAME "${name}.deb")
    set(CPACK_DEBIAN_PACKAGE_VERSION "1.1.1")
#    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://muhammetkucuk.com")
#    set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Debian package test with CPack")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Test for Deb")
#    set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
#        "${CMAKE_SOURCE_DIR}/deployment/prerm;${CMAKE_SOURCE_DIR}/deployment/postinst")
#    include(CPack)
endfunction()
